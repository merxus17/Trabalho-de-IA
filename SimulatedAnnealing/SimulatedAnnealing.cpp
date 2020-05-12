#include "SimulatedAnnealing.h"
#include <cmath>
#include <limits>
#include <iostream>

SimulatedAnnealing::SimulatedAnnealing()
{
    srand(5);
}

unsigned int SimulatedAnnealing::run(int **matrix , int size, int deposito)
{
    int lugarAtual = deposito;
    int mt [size][size];
    bestSolution = std::numeric_limits<unsigned int>::max();
    solution = 0;
    for(int i =0; i<size;i++)
    {
        for(int j=0; j<size;j++)
        {
            mt[i][j]=matrix[i][j];
        }
    }

    for(float t = Tmp; t > 1; t *= coolingFactor)
    {
        for(int i=0; i<size; i++)
        {
            nodes.insert(i);
        }
        nodes.erase(nodes.find(deposito));
        lugarAtual = deposito;
        while(nodes.size() > 1)
        {
            int next_node_X = pegarVizinho(lugarAtual, size);
            int next_node_Y = pegarVizinho(lugarAtual, size);
            while(next_node_X == next_node_Y)
            {
                next_node_Y = pegarVizinho(lugarAtual, size);
            }
            if(mt[lugarAtual][next_node_X] < mt[lugarAtual][next_node_Y])
            {
                solution += mt[lugarAtual][next_node_X] + solution;
                nodes.erase(next_node_X);
                lugarAtual = next_node_X;
            }
            else if( rand() > probabilidade(mt[lugarAtual][next_node_X] - mt[lugarAtual][next_node_Y],t))
            {
                solution += mt[lugarAtual][next_node_X] + solution ;
                nodes.erase(next_node_X);
                lugarAtual = next_node_X;
            }
            else if(mt[lugarAtual][next_node_X] >= mt[lugarAtual][next_node_Y])
            {
                solution += mt[lugarAtual][next_node_Y] + solution;
                nodes.erase(next_node_Y);
                lugarAtual = next_node_Y;
            }

        }
        solution += mt[lugarAtual][*nodes.begin()] + solution;
        solution += mt[*nodes.begin()][deposito] + solution;
        nodes.clear();
        if(solution < bestSolution)
        {
            std::cout << "\n\n new best solution: " << solution  << "\n\n" << std::endl;
            bestSolution = solution;
        }
        solution = 0;
    }
    return bestSolution;
}

double SimulatedAnnealing::probabilidade(int delta, double tmp)
{
   return std::exp(delta/tmp);
}

int SimulatedAnnealing::pegarVizinho(int atual, int size)
{
    int next_node = rand()%(size-0+1);
    if((nodes.find(next_node) == nodes.end() || next_node == atual) && next_node < size)
    {
        while((nodes.find(next_node) == nodes.end() || next_node == atual) && next_node < size)
        {
            next_node = rand()%(size-0+1);
        }
    }
    return next_node;
}

