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

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <random>
#include <QuEST.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>

// Helper functions
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalHelperFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"

// Graph functions
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"

// Quantum functions
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/flowMeasurements.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/angleConstruction.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/quantumGraphClusterStates.hpp"

// Assert functions
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"





using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;



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
  numRows = 2;
  numCols = 3;
  latticeGraph = createLatticeGraph(numRows,numCols);
  numVertices = boost::num_vertices(latticeGraph);
  

  
  
  
  // Print graph to file
  std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
  std::string graphName = "lattice2DGraph";
  std::string format = "png";
  printGraphToFile(latticeGraph,fileDir,graphName,format);


  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  
  
  // create a quantum register
  Qureg qureg = createQureg(numVertices, env);
  
  // initialise in the plus state
  initPlusState(qureg);

  //qubitAngles = initRandomPiOnNAnglesMod2kPi(numVertices, 4);
  qubitAngles = initRandomPiOnNAnglesMod2kPiPlusPi(numVertices, 4);
  
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




