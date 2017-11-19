#ifndef INTMATRIX_H
#define INTMATRIX_H

#include "vector"

#include "random"

using namespace std;

/*Матриця цілих чисел.*/
class IntMatrix
{
public:
    /*Конструктор за замовченням.*/
    IntMatrix();

    /*Конструктор копіювання.*/
    IntMatrix(const IntMatrix& other);

    /*Конструктор з параметрами.*/
    IntMatrix(const unsigned int newRowCount, const unsigned int newColCount);

    /*Деструктор.*/
    ~IntMatrix();

    /*Присвоювання.*/
    IntMatrix& operator = (const IntMatrix& other);

    /*Заповнює матрицю випадковими числами.*/
    void RandomMatrixGeneration(unsigned int maxValue=100);

    /*Отримує елемент, що знаходиться в матриці на визначеній позиції.*/
    unsigned int GetAt(unsigned int row, unsigned int col) const;

    /*Встановлює елемент, що знаходиться в матриці на визначеній позиції.*/
    void SetAt(unsigned int row, unsigned int col, unsigned int newValue);

    /*Отримує текстову інформацію про матрицю.*/
    string ToString();

    unsigned int GetRowCount() const{
        return rowCount;
    }

    unsigned int GetColCount() const{
        return colCount;
    }

    /*Видаляє з матриці всі дані і встановлює розміри у 0.*/
    void Clear();

    /*Порівнює розміри цієї матриці та іншої.*/
    bool SizesAreEqual(const IntMatrix& other) const;

private:
    /*Ініціалізує матрицю.*/
    void InitializeMatrix();

    /*Копіює матрицю з іншого об'єкта до матриці цього.*/
    void CopyMatrix(const IntMatrix& other);



    unsigned int rowCount;
    unsigned int colCount;

    vector< vector<unsigned int> > matrix;
};

#endif // INTMATRIX_H
