#ifndef UNITSWITHLOCALMEMORYSYSTEM_H
#define UNITSWITHLOCALMEMORYSYSTEM_H

#include "thread"
#include "mutex"

#include "vector"

#include "intmatrix.h"
#include "coeficient.h"

using namespace std;


/*Виконує задачу згідно алгоритму М1.*/
class UnitsWithLocalMemorySystem
{
public:
    /*Конструктор за замовченням.*/
    UnitsWithLocalMemorySystem();

    /*Виконує додавання матриць.*/
    IntMatrix Add(IntMatrix& left, IntMatrix& right);

    /*Виконує множення матриць.*/
    IntMatrix Multiplicate(IntMatrix& left, IntMatrix& right);

    /*Виконує транспонування матриці.*/
    IntMatrix Transpose(IntMatrix& source);

    /*Встановлює кількість процесорних елементів, що працюватимуть над задачею.*/
    void SetCountOfUnits(unsigned short int newCountOfUnits);

    void Lock(){
        m.lock();
    }
    void Unlock(){
        m.unlock();
    }

    coeficient time;

private:

    /*Отримує номер наступного вільного рядка.*/
    int GetNextUndoneRow();

    /*Ці функції виконуватиме кожен процесорний елемент в залежності від задачі.*/
    friend void DoAddition(UnitsWithLocalMemorySystem& target);
    friend void DoMultiplication(UnitsWithLocalMemorySystem& target);
    friend void DoTransposition(UnitsWithLocalMemorySystem& target);

    /*Кількість процесорних елементів, що працюватимуть над задачею.*/
    unsigned short int countOfUnits = 4;

    /*Потоки, що відповідають процесорним елементам.*/
    vector<thread> threads;

    /*Ще не оброблені рядки матриці.*/
    vector<unsigned int> undoneRows;

    IntMatrix* left;
    IntMatrix* right;
    IntMatrix result;

    /*Чи працює система в даний момент?*/
    bool isWorking = false;

    /*Для взаємного виключення.*/
    mutex m;
};



#endif // UNITSWITHLOCALMEMORYSYSTEM_H
