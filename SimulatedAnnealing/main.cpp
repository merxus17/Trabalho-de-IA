#include <iostream>
#include "TSPFileReader.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main()
{
    TSPFileReader reader;
    //int** matrix = reader.read("B:\\Projetos de IA\\Arquivos de TSP\\brazil58.tsp");
    int** matrix = reader.read("B:\\Projetos de IA\\Arquivos de TSP\\gr48.tsp");
   // int** matrix = reader.read("B:\\Projetos de IA\\Arquivos de TSP\\dantzig42.tsp");
    //int** matrix = reader.read("B:\\Projetos de IA\\Arquivos de TSP\\pa561.tsp");
    //reader.read("B:\\Projetos de IA\\Arquivos de TSP\\gr120.tsp");
    SimulatedAnnealing annealing;
    //auto solution = annealing.run(matrix, 42, 0);
    auto solution = annealing.run(matrix, 48, 0);
    //auto solution = annealing.run(matrix, 58, 0);
    //auto solution = annealing.run(matrix, 561, 0);
    std::cout << "\n\n\n\n\n\n soma total: "  << solution << std::endl;
    return 0;
}
