/////////////////////////////////////////////////////////////
// Title  : mbqcStarterFile.cpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        : Current implementation can only do square      //
//        : graph repeatedly. Will branch repo to make     //
//        : use different way to create graph by           //
//        : adjacency                                      //
/////////////////////////////////////////////////////////////
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




