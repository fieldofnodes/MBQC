///////////////////////////////////////////////////////////////
// Filename  : testDampingMBQC.cpp
// Author    : Jonathan Miller
// Date      : 2023-06-28
// Aim       : Build GHZ state
//           : Testing damping at various phases of 
//           : implementation
//           : Script not done
//           : Make function to add any single qubit noise 
//           : every time a gate is applied?
//           : some modularity needs to be added into the 
//           : measurement process
///////////////////////////////////////////////////////////////




// Include package header file
#include "packages.hpp"



// Set up the main function
int main() {
  
  // Initialise variable names and types
  int numRows;
  int numCols;
  undirectedGraph latticeGraph;
  int numVertices;
  std::vector<qreal> qubitAngles;
  std::vector<int> measuredQubitsOutcomes;
  std::vector<qreal> outcomeProbabilities;


  
  // Set values to variables
  numRows = 1;
  numCols = 2;
  latticeGraph = createLatticeGraph(numRows,numCols);
  numVertices = boost::num_vertices(latticeGraph);
  
  
  
  // Print graph to file
  // Update with desired directory to view graph.
  std::string figsDir = MBQC_FIGS_DIR;
  std::string graphName = "lattice1DDampingPerQubitGraph";
  std::string format = PNG_FORMAT;
  printGraphToFile(latticeGraph,figsDir,graphName,format);

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  
  // create a quantum register
  Qureg qureg = createDensityQureg(numVertices, env);
  
  
  //qubitAngles = initRandomPiOnNAnglesMod2kPi(numVertices, 4);
  qreal angle = 0.0;
  qubitAngles = initAllAnglesSame(numVertices,angle);
 

  // initialise in the plus state
  initPlusState(qureg);

  
  // add angles to the qubits
  addAngleRotateZgate(qureg,qubitAngles);
  
   
  // entangle graph
  entangleGraph(qureg,latticeGraph);

  // Display probabilities before damping
  std::cout << "Outcome probs" << std::endl;
  outcomeProbabilities = computeAllProbabilityOutcomesToVector(qureg);
  printVector(outcomeProbabilities);

  // Add damping to qubit after entanglement
  qreal prob = 0.1;
  mixDamping(qureg,0,prob);
  mixDamping(qureg,1,prob);


  // Display probabilities after damping
  std::cout << "Outcome probs" << std::endl;
  outcomeProbabilities = computeAllProbabilityOutcomesToVector(qureg);
  printVector(outcomeProbabilities);


 // Measure qubit at a time
 rotateZ(qureg,0, (-1)*qubitAngles[0]);
 hadamard(qureg,0);
 int m0 = measure(qureg,0);
 std::cout << "numQubits: " << qureg.numQubitsRepresented << std::endl;

  // Display probabilities before damping
  std::cout << "Outcome probs after 1 measure" << std::endl;
  outcomeProbabilities = computeAllProbabilityOutcomesToVector(qureg);
  printVector(outcomeProbabilities);


  // Measure qubit at a time 
  int exponent = m0;
  qreal xAngle = std::pow((-1), exponent)*qubitAngles[1];
  rotateZ(qureg,1, (-1)*xAngle);
  hadamard(qureg,1);
  int m = measure(qureg,0);
  std::cout << "numQubits: " << qureg.numQubitsRepresented << std::endl;

  // Display probabilities before damping
  std::cout << "Outcome probs after 1 measure" << std::endl;
  outcomeProbabilities = computeAllProbabilityOutcomesToVector(qureg);
  printVector(outcomeProbabilities);


/*
  // measure graph
  measuredQubitsOutcomes = measureGraph(
        qureg,
        latticeGraph,
        qubitAngles,
        numRows);



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







  // print results to screen
  printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);

  
  
    
*/
  
  // unload QuEST
  destroyQureg(qureg, env); 
  destroyQuESTEnv(env);
  return 0;
}




/*


printArray(float* array, int size)
void printArray(float* array, int size) {
    printf("outcomeProbs[] = {");
    for (int i = 0; i < size; i++) {
        printf("%.2f", array[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

*/