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
 
    
    



int main(){


    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
  
    // create a quantum register
    Qureg qureg = createQureg(1, env);
    int qubit = 0;
    std::cout << "Probability outcomes single qubit: " << std::endl; 
    std::cout << "Initialised at 0: " << std::endl; 
    std::vector<qreal> init_probs = outcomeProbabilitiesSingleQubit(qureg,qubit);

    printVector(init_probs);

    std::cout << "Pauli X gate applied: " << std::endl;
    pauliX(qureg,0);
    
    std::vector<qreal> init_probs_gate = outcomeProbabilitiesSingleQubit(qureg,qubit);
    printVector(init_probs_gate);

    std::cout << "Pauli X gate applied: " << std::endl;
    pauliX(qureg,0);
    
    std::vector<qreal> init_probs_gate_1 = outcomeProbabilitiesSingleQubit(qureg,qubit);
    printVector(init_probs_gate_1);

    /*

    // Apply Hadamard and test probability
    hadamard(qureg,0);
    hadamard(qureg,1);
    hadamard(qureg,2);
    controlledPhaseFlip(qureg,0,1);
    controlledPhaseFlip(qureg,1,2);
    


    qreal prob_0 = calcProbOfOutcome(qureg,0,0);
    qreal prob_1 = calcProbOfOutcome(qureg,1,0);
    qreal prob_2 = calcProbOfOutcome(qureg,2,0);
    std::cout << "Probability 0: " << prob_0 << std::endl;
    std::cout << "Probability 1: " << prob_1 << std::endl;
    std::cout << "Probability 2: " << prob_2 << std::endl;

    qreal tp = calcTotalProb(qureg);
    std::cout << "Total Probability qureg: " << tp << std::endl;


    int m1 = measure(qureg,0);

*/

    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);



/*
  // Initialise variable names and types
  int numRows;
  int numCols;
  undirectedGraph latticeGraph;
  int numVertices;
  std::vector<qreal> qubitAngles;
  std::vector<int> measuredQubitsOutcomes;
  
  
  // Set values to variables
  numRows = 1;
  numCols = 2;
  latticeGraph = createLatticeGraph(numRows,numCols);
  numVertices = boost::num_vertices(latticeGraph);
  
  
  
  // Print graph to file
  // Update with desired directory to view graph.
  std::string fileDir = "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/figs";
  std::string graphName = "twoQubitGraph";
  std::string format = "png";
  printGraphToFile(latticeGraph,fileDir,graphName,format);

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  
  // create a quantum register
  Qureg qureg = createQureg(numVertices, env);
  
  
  //qubitAngles = initRandomPiOnNAnglesMod2kPi(numVertices, 4);
  qubitAngles = initAllAnglesSame(numVertices, 0);
 

  // initialise in the plus state
  initPlusState(qureg);

  
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
  */
  return 0;
}