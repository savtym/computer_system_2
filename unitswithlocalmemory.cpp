#include "unitswithlocalmemory.h"
#include "iostream"
#include "constants.h"
#include <unistd.h>


void DoAddition(UnitsWithLocalMemorySystem& target){
    while(true){
        unsigned int row = target.GetNextUndoneRow();

        if(-1 == row){
            return;
        }

        for(unsigned int col = 0; col < target.result.GetColCount(); col++){
//            cout << "Adding: " << 100 * (row*target.result.GetColCount() + col) / (target.result.GetRowCount() * target.result.GetColCount()) << endl;
            target.result.SetAt(row, col, target.result.GetAt(row, col) + target.right->GetAt(row, col));
            usleep(DEFAULT_TICK_LENGTH * DEFAULT_ADD_LENGTH);
        }
    }
}

void DoMultiplication(UnitsWithLocalMemorySystem& target){
    while(true){
        unsigned int row = target.GetNextUndoneRow();

        if(-1 == row){
            return;
        }

        for(unsigned int col = 0; col < target.result.GetColCount(); col++){
//            cout << "Multiplicating: " << 100 * (row*target.result.GetColCount() + col) / (target.result.GetRowCount() * target.result.GetColCount()) << endl;
            //target.result.SetAt(row, col, target.result.GetAt(row, col) + target.right->GetAt(row, col));
            unsigned int newElement = 0;
            for(unsigned int r = 0; r < target.left->GetColCount(); r++){
                newElement += target.left->GetAt(row, r) * target.right->GetAt(r, col);
            }
            target.result.SetAt(row, col, newElement);
            usleep(DEFAULT_TICK_LENGTH * DEFAULT_MUL_LENGTH);
        }
    }
}

void DoTransposition(UnitsWithLocalMemorySystem& target){
    while(true){
        unsigned int row = target.GetNextUndoneRow();

        if(-1 == row){
            return;
        }

        for(unsigned int col = 0; col < target.result.GetColCount(); col++){
//            cout << "Transposing: " << 100 * (row*target.result.GetColCount() + col) / (target.result.GetRowCount() * target.result.GetColCount()) << endl;
            //target.result.SetAt(row, col, target.result.GetAt(row, col) + target.right->GetAt(row, col));
            target.result.SetAt(row, col, target.left->GetAt(col, row));
            usleep(DEFAULT_TICK_LENGTH * DEFAULT_ADD_LENGTH);
        }
    }
}

UnitsWithLocalMemorySystem::UnitsWithLocalMemorySystem() {}

/*Виконує додавання матриць.*/
IntMatrix UnitsWithLocalMemorySystem::Add(IntMatrix &left, IntMatrix &right)
{
    result = left;
    if(!left.SizesAreEqual(right) || isWorking){
        return IntMatrix();
    }

    unsigned int start_time = clock();
    isWorking = true;
    this->left = &left;
    this->right = &right;

    for(unsigned int row = 0; row < result.GetRowCount(); row++){
        undoneRows.push_back(row);
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads.push_back(thread(DoAddition, std::ref(*this)));
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads[unit].join();
    }

    threads.clear();

    isWorking = false;

    unsigned int end_time = clock();
    time.setTime(end_time - start_time);
    return result;
}

/*Виконує множення матриць.*/
IntMatrix UnitsWithLocalMemorySystem::Multiplicate(IntMatrix &left, IntMatrix &right)
{
    result = IntMatrix(left.GetRowCount(), right.GetColCount());
    if((left.GetColCount() != right.GetRowCount()) || isWorking){
        return IntMatrix();
    }

    unsigned int start_time = clock();
    isWorking = true;
    this->left = &left;
    this->right = &right;

    for(unsigned int row = 0; row < result.GetRowCount(); row++){
        undoneRows.push_back(row);
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads.push_back(thread(DoMultiplication, std::ref(*this)));
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads[unit].join();
    }

    threads.clear();

    isWorking = false;

    unsigned int end_time = clock();
    time.setTime(end_time - start_time);
    return result;
}

/*Виконує транспонування матриці.*/
IntMatrix UnitsWithLocalMemorySystem::Transpose(IntMatrix &source)
{
    result = IntMatrix(source.GetColCount(), source.GetRowCount());
    if(isWorking){
        return IntMatrix();
    }

    unsigned int start_time = clock();
    isWorking = true;
    this->left = &source;

    for(unsigned int row = 0; row < result.GetRowCount(); row++){
        undoneRows.push_back(row);
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads.push_back(thread(DoTransposition, std::ref(*this)));
    }

    for(unsigned short int unit = 0; unit < countOfUnits; unit++){
        threads[unit].join();
    }

    threads.clear();

    isWorking = false;

    unsigned int end_time = clock();
    time.setTime(end_time - start_time);
    return result;
}

/*Встановлює кількість процесорних елементів, що працюватимуть над задачею.*/
void UnitsWithLocalMemorySystem::SetCountOfUnits(unsigned short newCountOfUnits)
{
    if(!isWorking){
        countOfUnits = newCountOfUnits;
    }
}

/*Отримує номер наступного вільного рядка.*/
int UnitsWithLocalMemorySystem::GetNextUndoneRow()
{
    m.lock();
    if(undoneRows.empty()){
        m.unlock();
        return -1;
    }
    unsigned int row = undoneRows.back();
    undoneRows.pop_back();
    m.unlock();
    return row;
}






