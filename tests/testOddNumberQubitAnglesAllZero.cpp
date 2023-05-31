/////////////////////////////////////////////////////////////
// Title  : testOddNumberQubitAnglesAllZero.cpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        : Current implementation can only do square      //
//        : graph repeatedly. Will branch repo to make     //
//        : use different way to create graph by           //
//        : adjacency                                      //
/////////////////////////////////////////////////////////////

// To run
// cmake .. -DUSER_SOURCE="QuEST/projects/MBQC/tests/testOddNumberQubitAnglesAllZero.cpp" -DOUTPUT_EXE="testOddNumberQubitAnglesAllZero" && make && ./testOddNumberQubitAnglesAllZero


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



// Set up the main function
int main() {
    for(int i = 0; i < 1e6; i++)
    {
    // Initialise variable names and types
    int numRows;
    int numCols;
    undirectedGraph latticeGraph;
    int numVertices;
    std::vector<qreal> qubitAngles;
    std::vector<int> measuredQubitsOutcomes;


    // Set values to variables
    numRows = 1;
    numCols = 11; // Test on an odd number of qubits
    latticeGraph = createLatticeGraph(numRows,numCols);
    numVertices = boost::num_vertices(latticeGraph);



    // Print graph to file
    // Update with desired directory to view graph.
    //std::string fileDir = "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/figs";
    //std::string graphName = "1DLatticeAllAngles0";
    //std::string format = "png";
    //printGraphToFile(latticeGraph,fileDir,graphName,format);


    // load QuEST environment
    QuESTEnv env = createQuESTEnv();


    // create a quantum register
    Qureg qureg = createQureg(numVertices, env);



    qubitAngles = initAllAnglesZero(numVertices);


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

    assert((measuredQubitsOutcomes.back()==0) && "The last qubit must be 0, it is not.");
    // print results to screen
    //printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);



    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    
    }
    return 0;
}




