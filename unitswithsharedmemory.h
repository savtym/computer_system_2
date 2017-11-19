#ifndef UNITSWITHSHAREDMEMORYSYSTEM_H
#define UNITSWITHSHAREDMEMORYSYSTEM_H

#include "thread"
#include "mutex"

#include "vector"

#include "intmatrix.h"
#include "coeficient.h"


/*Виконує задачу згідно алгоритму М2.*/
class UnitsWithSharedMemorySystem
{
public:
    /*Конструктор за замовченням.*/
    UnitsWithSharedMemorySystem();

    /*Виконує додавання матриць.*/
    IntMatrix Add(IntMatrix& left, IntMatrix& right);

    /*Виконує множення матриць.*/
    IntMatrix Multiplicate(IntMatrix& left, IntMatrix& right);

    /*Виконує транспонування матриці.*/
    IntMatrix Transpose(IntMatrix& source);

    /*Встановлює кількість процесорних елементів, що працюватимуть над задачею.*/
    void SetCountOfUnits(unsigned short int newCountOfUnits);

    coeficient time;

private:

    /*Отримує номер наступного вільного рядка.*/
    int GetNextUndoneRow();

    /*Ці функції виконуватиме кожен процесорний елемент в залежності від задачі.*/
    friend void DoAddition(UnitsWithSharedMemorySystem& target, unsigned int row, unsigned int col);
    friend void DoMultiplication(UnitsWithSharedMemorySystem& target,
                                 unsigned int leftRow, unsigned int leftCol,
                                 unsigned int rightRow, unsigned int rightCol,
                                 unsigned int& res);
    friend void DoTransposition(UnitsWithSharedMemorySystem& target, unsigned int row, unsigned int col);

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

#endif // UNITSWITHSHAREDMEMORYSYSTEM_H
