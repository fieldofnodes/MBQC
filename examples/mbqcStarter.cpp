///////////////////////////////////////////////////////////////
// Filename  : mbqcStarterFile.cpp
// Author    : Jonathan Miller
// Date      : 2023-06-19
// Aim       : aim_script
//           : Lattice graph NxM
//           : Flow: same row -> column (i+num_rows)
//           : Script overview:
//           :    + It includes the necessary package header file.
//           :    + The main() function serves as the entry point for the program.
//           :    + Several variables of different types are declared and initialized.
//           :    + The program creates a lattice graph based on the specified number of rows and columns.
//           :    + The graph is printed to a file.
//           :    + The QuEST environment is initialized.
//           :    + A quantum register is created with the specified number of vertices.
//           :    + Random angles in the range of π on N angles are initialized and assigned to the qubitAngles vector.
//           :    + The quantum register is initialized in the plus state.
//           :    + Angle rotations around the Z-axis are applied to the qubits based on the qubitAngles vector.
//           :    + The graph is entangled using the entangleGraph function.
//           :    + The graph is measured, and the outcomes are stored in the measuredQubitsOutcomes vector.
//           :    + The results are printed to the screen.
//           :    + The QuEST environment and the quantum register are deallocated.
//           :    + The program returns 0 to indicate successful execution.
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
  
  
  // Set values to variables
  numRows = 4;
  numCols = 4;
  latticeGraph = createLatticeGraph(numRows,numCols);
  numVertices = boost::num_vertices(latticeGraph);
  
  
  
  // Print graph to file
  // Update with desired directory to view graph.
  std::string figsDir = MBQC_FIGS_DIR;
  std::string graphName = "lattice2DGraphCmakeV2";
  std::string format = PNG_FORMAT;
  printGraphToFile(latticeGraph,figsDir,graphName,format);

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  
  // create a quantum register
  Qureg qureg = createQureg(numVertices, env);
  
  
  //qubitAngles = initRandomPiOnNAnglesMod2kPi(numVertices, 4);
  qubitAngles = initRandomPiOnNAnglesMod2kPiPlusPi(numVertices, 4);
 

  // initialise in the plus state
  initPlusState(qureg);

  
  // add angles to the qubits
  addAngleRotateZgate(qureg,qubitAngles);
  
   
  // entangle graph
  entangleGraph(qureg,latticeGraph);


  // measure graph
  measuredQubitsOutcomes = measureGraph(
        qureg,
        latticeGraph,
        qubitAngles,
        numRows);

    
  // print results to screen
  printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);

  
  
  // unload QuEST
  destroyQureg(qureg, env); 
  destroyQuESTEnv(env);
  return 0;
}




