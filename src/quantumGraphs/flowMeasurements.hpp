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



std::vector<int> measureGraph(
    Qureg qureg,
    const undirectedGraph& graph,
    std::vector<qreal> qubitAngles,
    int numRows){

    std::vector<int> measuredQubitsOutcomes;
    undirectedGraph::vertex_iterator vi, vi_end;
    for (boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; vi++) {
        // skip vertices that are in the first column
        if(*vi < numRows){
            rotateZ(qureg,*vi, (-1)*qubitAngles[*vi]);
            hadamard(qureg,*vi);
            int m = measure(qureg,*vi);
            measuredQubitsOutcomes.push_back(m);
        }else if(*vi >= numRows){
            qreal correctedAngle;
            correctedAngle = computeCorrectedAngle(graph,measuredQubitsOutcomes,*vi,numRows,qubitAngles[*vi]);
            rotateZ(qureg,*vi, (-1)*correctedAngle);
            hadamard(qureg,*vi);
            int m = measure(qureg,*vi);
            measuredQubitsOutcomes.push_back(m);
        } else {
            std::cout << "attempting to measure nothing?";
        }
    }


    return measuredQubitsOutcomes;
}



/*
  Print results to scree
*/
void printResultsToScreen(
  std::vector<int> measuredQubitsOutcomes,
  int numRows,
  int numCols){

  // Print results to screen
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Measured outcome vector has " << measuredQubitsOutcomes.size() << " qubits."  << std::endl; 
  std::cout << "The measurements are: ";
  for(int i:measuredQubitsOutcomes){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


std::cout << "Measured outcome lattice: " << std::endl;
  std::vector<std::vector<int>> latticeOutcomes = 
    returnMeasQubitOutcomesLattice(measuredQubitsOutcomes,numRows,numCols);

  for (const auto& row : latticeOutcomes) {
            for (int number : row) {
                std::cout << number << ' ';
            }
            std::cout << '\n';
        }

}