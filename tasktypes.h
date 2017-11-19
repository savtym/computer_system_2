#ifndef TASKTYPES
#define TASKTYPES

/*Можливі типи задач для системи.*/
enum TaskTypes{
    Addition,       //Сума двох матриць
    Multiplication, //Добуток двох матриць
    Transposition   //Транспонування однієї матриці
};

/*Можливі способи виконання задачі.*/
enum TaskPerformTypes{
    SingleUnit,             //На одному процесорі
    UnitsWithLocalMemory,     //Згідно типу М1 (багато процесорів, кожен має свою локальну пам'ять)
    UnitsWithSharedMemory   //Згідно типу М2 (багато процесорів, всі спілкуються через загальну пам'ять)
};

#endif // TASKTYPES

