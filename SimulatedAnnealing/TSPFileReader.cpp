#include "TSPFileReader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>

TSPFileReader::TSPFileReader()
{

}

int** TSPFileReader::read(std::string path)
{
    std::ifstream file(path);
    std::string line;
    std::string weights = "";
    int** matrix;
    while(std::getline(file, line))
    {
        //std::cout << line << std::endl;
        if (line.find("DIMENSION") != std::string::npos && !weight)
        {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
            dimension = std::stoi(line.substr(line.find(":") + 1));
            std::cout << "dimension found: " << dimension << std::endl;
            matrix =  new int*[dimension];
            for(int i = 0; i < dimension; i++)
            {
               matrix[i]= new int[dimension];
            }
            preencherDeZero(matrix);
            rowsLeft = dimension;
        }
        if (line.find("EDGE_WEIGHT_FORMAT") != std::string::npos && !weight)
        {
            line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
            format = line.substr(line.find(":") + 1);
            std::cout << "format found: " << format << std::endl;
        }
        if(line.find("EDGE_WEIGHT_SECTION") != std::string::npos)
        {
           weight = true;
        }
        if(weight)
        {
            if(line.find("DISPLAY_DATA_SECTION") != std::string::npos)
            {
                break;
            }
            if(line.find("EOF") == std::string::npos && line.find("EDGE_WEIGHT_SECTION") == std::string::npos)
            {
                weights+= line;
            }

        }
    }

//    for(int i = 0; i<dimension; i++)
//    {
//        for(int j = 0; j<dimension; j++)
//        {
//            std::cout<< " " << matrix[i][j] << " ";
//        }
//        std::cout<< "\n";
//    }
    std::istringstream iss(weights);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    std::queue<int> numbers;

    for(auto str: results)
    {
        numbers.push(std::stoi(str));
    }

    if(format == "UPPER_ROW")
    {
        for(int i = dimension - rowsLeft; rowsLeft>0 ; rowsLeft--)
        {
            i = dimension - rowsLeft;
            for(int j = i+1; j<dimension; j++)
            {
               // std::cout << "position: i:" << i  << " j:" << j ;
                if(numbers.size() > 0)
                {
                 //   std::cout << "  numero: " << numbers.front();
                    matrix[i][j]= numbers.front();
                   // std::cout << "  numero na matriz: " << matrix[i][j] << std::endl;
                    numbers.pop();
                }
                else
                {
                   // std::cout << "  numero: 0\n";
                }
            }

        }
    }
    else if(format == "LOWER_DIAG_ROW")
    {
        for(int i = dimension - rowsLeft; rowsLeft>0 ; rowsLeft--)
        {
            i = dimension - rowsLeft;
            for(int j = 0; j<= dimension-rowsLeft ; j++)
            {
                //std::cout << "position: i:" << i  << " j:" << j ;
                if(numbers.size() > 0)
                {
                  //  std::cout << "  numero: " << numbers.front();
                    matrix[i][j]= numbers.front();
                    //std::cout << "  numero na matriz: " << matrix[i][j] << std::endl;
                    numbers.pop();
                }
                else
                {
                    //std::cout << "  numero: 0\n";
                }
            }
        }
    }

    espelhaMatrix(matrix);
    for(int i = 0; i<dimension; i++)
    {
        for(int j = 0; j<dimension; j++)
        {
            std::cout<< " " << matrix[i][j] << " ";
        }
        std::cout<< "\n";
    }

    return matrix;
}

void TSPFileReader::preencherDeZero(int** matrix)
{
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
           matrix[i][j] = 0;
        }
    }
}

void TSPFileReader::espelhaMatrix(int **matrix)
{
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
           if(matrix[i][j] == 0)
           {
               matrix[i][j] = matrix[j][i];
           }
        }
    }
}
