#include "unitswithsharedmemory.h"
#include "iostream"
#include "constants.h"
#include <unistd.h>

void DoAddition(UnitsWithSharedMemorySystem& target, unsigned int row, unsigned int col){
    target.m.lock();

    target.result.SetAt(row, col, target.result.GetAt(row, col) + target.right->GetAt(row, col));
    usleep(DEFAULT_TICK_LENGTH * DEFAULT_ADD_LENGTH);
    //ЗАТОРМОЗИТЬ

    target.m.unlock();
}

void DoMultiplication(UnitsWithSharedMemorySystem& target,
                      unsigned int leftRow, unsigned int leftCol,
                      unsigned int rightRow, unsigned int rightCol,
                      unsigned int& res){
    target.m.lock();

    res += target.left->GetAt(leftRow, leftCol) * target.right->GetAt(rightRow, rightCol);
    usleep(DEFAULT_TICK_LENGTH * DEFAULT_MUL_LENGTH);
    //ЗАТОРМОЗИТЬ

    target.m.unlock();
}

void DoTransposition(UnitsWithSharedMemorySystem& target, unsigned int row, unsigned int col){
    target.m.lock();

    target.result.SetAt(row, col, target.left->GetAt(col, row));
    usleep(DEFAULT_TICK_LENGTH * DEFAULT_ADD_LENGTH);
    //ЗАТОРМОЗИТЬ

    target.m.unlock();
}

UnitsWithSharedMemorySystem::UnitsWithSharedMemorySystem()
{

}

/*Виконує додавання матриць.*/
IntMatrix UnitsWithSharedMemorySystem::Add(IntMatrix &left, IntMatrix &right)
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
        unsigned int col = 0;
        while(col < result.GetColCount()){
            for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                threads.push_back(thread(DoAddition, std::ref(*this), row, col + unit));
            }

            for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                threads[unit].join();
            }
            threads.clear();
            col += countOfUnits;
        }
    }

    isWorking = false;
    unsigned int end_time = clock();
    time.setTime(end_time - start_time);

    return result;
}

/*Виконує множення матриць.*/
IntMatrix UnitsWithSharedMemorySystem::Multiplicate(IntMatrix &left, IntMatrix &right)
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
        for(unsigned int col = 0; col < result.GetColCount(); col++){
            unsigned int newElement = 0;
            /*for(unsigned int r = 0; r < left.GetColCount(); r++){
                newElement += left.GetAt(row, r) * right.GetAt(r, col);
            }*/
            unsigned int r = 0;
            while(r < left.GetColCount()){
                for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                    threads.push_back(thread(DoMultiplication, std::ref(*this), row, r + unit, r + unit, col, std::ref(newElement)));
                }

                for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                    threads[unit].join();
                }
                threads.clear();
                r += countOfUnits;
            }
            result.SetAt(row, col, newElement);
        }
    }

    unsigned int end_time = clock();
    time.setTime(end_time - start_time);
    isWorking = false;
    return result;
}

/*Виконує транспонування матриці.*/
IntMatrix UnitsWithSharedMemorySystem::Transpose(IntMatrix &source)
{
    result = IntMatrix(source.GetColCount(), source.GetRowCount());

    if(isWorking){
        return IntMatrix();
    }

    unsigned int start_time = clock();
    isWorking = true;
    this->left = &source;

    for(unsigned int row = 0; row < result.GetRowCount(); row++){
        unsigned int col = 0;

        while(col < result.GetColCount()){
            for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                threads.push_back(thread(DoTransposition, std::ref(*this), row, col + unit));
            }

            for(unsigned short int unit = 0; unit < countOfUnits; unit++){
                threads[unit].join();
            }

            threads.clear();
            col += countOfUnits;
        }
    }

    isWorking = false;
    unsigned int end_time = clock();
    time.setTime(end_time - start_time);
    return result;
}

/*Встановлює кількість процесорних елементів, що працюватимуть над задачею.*/
void UnitsWithSharedMemorySystem::SetCountOfUnits(unsigned short newCountOfUnits)
{
    if(!isWorking){
        countOfUnits = newCountOfUnits;
    }
}
