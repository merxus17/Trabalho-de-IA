#pragma once
#include <vector>
#include <unordered_set>
#include <limits>

class SimulatedAnnealing
{
public:
    SimulatedAnnealing();



    unsigned int run (int** matrix, int size, int deposito);

    double probabilidade(int delta, double tmp);

    int pegarVizinho(int atual, int size);

    int nIt;

    float Tmp= 1000000000000000000;

    float coolingFactor= 0.9999;

    unsigned int solution;

    unsigned int bestSolution;

    int dpto;

    std::unordered_set<int> nodes;

    std::vector<int> path;

    int** _matrix;
};
