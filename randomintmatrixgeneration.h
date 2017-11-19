#ifndef RANDOMINTMATRIXGENERATION
#define RANDOMINTMATRIXGENERATION

#include "random"

#include "vector"

using namespace std;

/*Генерує матрицю випадкових цілих чисел.*/
vector< vector<unsigned int> > RandomMatrixGeneration(unsigned int rowCount, unsigned int colCount, unsigned int maxValue=100){
    vector< vector<unsigned int> > ret = vector< vector<unsigned int> >();

    for(unsigned int i = 0; i < rowCount; i++){
        ret.push_back(vector<unsigned int>());

        for(unsigned int j = 0; j < colCount; j++){
            ret[i].push_back(rand() % maxValue);
        }
    }

    printf("aaa\n");

    return ret;
}

#endif // RANDOMINTMATRIXGENERATION
