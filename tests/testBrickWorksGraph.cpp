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

// Standard libraries
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <random>
#include <filesystem>



// QuEST
#include <QuEST.h>

// Boost
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>


// Helper functions
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalHelperFunctions.hpp"
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"

// Graph functions
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"

// Quantum functions
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/flowMeasurements.hpp"
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/angleConstruction.hpp"
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/quantumGraphClusterStates.hpp"

// Assert functions
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/generalAssertFunctions.hpp"
#include "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"





using namespace boost;
typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;




int main(){

    undirectedGraph brickWorkGraph;
    int numVertices = 10;
    // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  
  // create a quantum register
  Qureg qureg = createQureg(numVertices, env);
    return 0;
}