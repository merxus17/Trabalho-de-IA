#pragma once
#include <string>
#include <vector>

class TSPFileReader
{
public:
    TSPFileReader();

    int** read(std::string path);

    void preencherDeZero(int** matrix);

    void espelhaMatrix(int** matrix);

    int dimension = 0;

    int rowsLeft = 0;

    std::string format;

    bool weight = false;
};
