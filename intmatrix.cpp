#include "intmatrix.h"

#include "iostream"

/*Конструктор за замовченням.*/
IntMatrix::IntMatrix()
{

    rowCount = 0;
    colCount = 0;
    InitializeMatrix();

//    std::cout << "Default constructor called!" << endl;
}

/*Конструктор копіювання.*/
IntMatrix::IntMatrix(const IntMatrix &other)
{
    rowCount = other.rowCount;
    colCount = other.colCount;
    InitializeMatrix();
    CopyMatrix(other);

//    std::cout << "Copy constructor called!" << endl;
}

/*Конструктор з параметрами.*/
IntMatrix::IntMatrix(const unsigned int newRowCount, const unsigned int newColCount)
{
    rowCount = newRowCount;
    colCount = newColCount;
    InitializeMatrix();

//    std::cout << "Parametrized constructor called!" << endl;
}

/*Деструктор.*/
IntMatrix::~IntMatrix()
{
    matrix.clear();
    rowCount = 0;
    colCount = 0;

//    std::cout << "Destructor called!" << endl;
}

//Присвоювання
IntMatrix &IntMatrix::operator =(const IntMatrix &other)
{
    if(this == &other){
        return *this;
    }
    rowCount = other.rowCount;
    colCount = other.colCount;
    matrix = other.matrix;

    return *this;
}

/*Заповнює матрицю випадковими числами.*/
void IntMatrix::RandomMatrixGeneration(unsigned int maxValue)
{
    for(unsigned int row = 0; row < rowCount; row++){

        for(unsigned int col = 0; col < colCount; col++){
            matrix[row][col] = rand() % maxValue;
        }
    }
}

/*Отримує елемент, що знаходиться в матриці на визначеній позиції.*/
unsigned int IntMatrix::GetAt(unsigned int row, unsigned int col) const
{
    if(row < rowCount && col < colCount){
        return matrix[row][col];
    }
    return 0;
}

/*Встановлює елемент, що знаходиться в матриці на визначеній позиції.*/
void IntMatrix::SetAt(unsigned int row, unsigned int col, unsigned int newValue)
{
    if(row < rowCount && col < colCount){
        matrix[row][col] = newValue;
    }
}

/*Отримує текстову інформацію про матрицю.*/
string IntMatrix::ToString()
{
    string ret = "";

    for(unsigned int row = 0; row < rowCount; row++){

        for(unsigned int col = 0; col < colCount; col++){
            ret.append(to_string(matrix[row][col]));
            ret.append("\t");
        }

        ret.append("\n");
    }

    return ret;
}

/*Ініціалізує матрицю.*/
void IntMatrix::InitializeMatrix()
{
    matrix = vector< vector<unsigned int> >();

    for(unsigned int i = 0; i < rowCount; i++){
        matrix.push_back(vector<unsigned int>());

        for(unsigned int j = 0; j < colCount; j++){
            matrix[i].push_back(0);
        }
    }
}

/*Копіює матрицю з іншого об'єкта до матриці цього.*/
void IntMatrix::CopyMatrix(const IntMatrix &other)
{
    if(!SizesAreEqual(other)){
        return;
    }
    matrix = other.matrix;
    /*for(unsigned int row = 0; row < rowCount; row++){
        for(unsigned int col = 0; col < colCount; col++){
            matrix[row][col] = other.matrix[row][col];
        }
    }*/
}

/*Видаляє з матриці всі дані і встановлює розміри у 0.*/
void IntMatrix::Clear()
{
    matrix.clear();
    rowCount = 0;
    colCount = 0;
}

/*Порівнює розміри цієї матриці та іншої.*/
bool IntMatrix::SizesAreEqual(const IntMatrix& other) const
{
    return rowCount == other.rowCount && colCount == other.colCount;
}

