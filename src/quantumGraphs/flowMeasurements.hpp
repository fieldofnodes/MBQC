/////////////////////////////////////////////////////////////
// Title  : flowMeasurements.hpp                           //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct flow actions reflected in graph      //
/////////////////////////////////////////////////////////////
#include <vector>



/*
  Fill lattice with qubit measurements
*/
std::vector<std::vector<int>> returnMeasQubitOutcomesLattice(std::vector<int> measOutcomes,int numRows, int numCols) {
    int numVertices = numRows * numCols;
    std::vector<std::vector<int>> lattice(numRows, std::vector<int>(numCols, -1));
    std::vector<int> numbers(numVertices);
    for (int i = 0; i < numVertices; i++) {
        numbers[i] = i;
    }

    for (int number : numbers) {
        int row = number % numRows;
        int col = number / numRows;
        lattice[row][col] = measOutcomes[number];
    }

    return lattice;
}