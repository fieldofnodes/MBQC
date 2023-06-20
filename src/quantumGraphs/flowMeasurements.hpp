/////////////////////////////////////////////////////////////
// Title  : flowMeasurements.hpp                           //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct flow actions reflected in graph      //
/////////////////////////////////////////////////////////////





/**
 * @brief Constructs a lattice representation of qubit measurement outcomes.
 *
 * This function constructs a lattice representation of qubit measurement outcomes based on the provided `measOutcomes` vector,
 * number of rows (`numRows`), and number of columns (`numCols`).
 *
 * @param measOutcomes A vector containing the outcomes of qubit measurements.
 * @param numRows The number of rows in the lattice.
 * @param numCols The number of columns in the lattice.
 * @return A two-dimensional vector representing the lattice with qubit measurement outcomes.
 * @pre `measOutcomes` must contain `numRows * numCols` elements.
 */
std::vector<std::vector<int>> returnMeasQubitOutcomesLattice(std::vector<int> measOutcomes,int numRows, int numCols) {
  /*
    Fill lattice with qubit measurements
  */
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


/**
 * @brief Measures qubits in a graph-based quantum state.
 *
 * This function measures qubits in a graph-based quantum state represented by the provided `qureg` and `graph`.
 * The qubit measurement outcomes are stored in the `measuredQubitsOutcomes` vector.
 *
 * @param qureg The quantum register representing the quantum state.
 * @param graph The undirected graph representing the connectivity of qubits.
 * @param qubitAngles A vector containing the angles for qubit rotations.
 * @param numRows The number of rows in the graph layout.
 * @return A vector containing the outcomes of qubit measurements.
 */
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



/**
 * @brief Prints the measurement results to the screen.
 *
 * This function prints the measurement results to the screen, including the measured qubit outcomes and the outcome lattice.
 *
 * @param measuredQubitsOutcomes A vector containing the outcomes of qubit measurements.
 * @param numRows The number of rows in the outcome lattice.
 * @param numCols The number of columns in the outcome lattice.
 */
void printResultsToScreen(
  std::vector<int> measuredQubitsOutcomes,
  int numRows,
  int numCols){
  /*
  Print results to scree
  */

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