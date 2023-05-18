
/////////////////////////////////////////////////////////////
// Title  : testOddNumberQubitsEverySecondsAngleZero.cpp   //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        : Current implementation can only do square      //
//        : graph repeatedly. Will branch repo to make     //
//        : use different way to create graph by           //
//        : adjacency                                      //
/////////////////////////////////////////////////////////////

// To run
// cmake .. -DUSER_SOURCE="QuEST/projects/MBQC/tests/testOddNumberQubitsEverySecondsAngleZero.cpp" -DOUTPUT_EXE="testOddNumberQubitsEverySecondsAngleZero" && make && ./testOddNumberQubitsEverySecondsAngleZero


// Standard libraries
#include <iostream>
#include <sstream>
#include <stdexcept>
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

void assertFunc(std::vector<int> measuredQubitsOutcomes,int assertValue) {
    if (measuredQubitsOutcomes.back() != assertValue) {
        throw std::runtime_error("The last qubit must be " + std::to_string(assertValue) + ", it is not.");
    }
}

void testEveryOtherAnlgeZeroResults(int assertValue,int piDenominator,int numberCols){
    // Initialise variable names and types
    int numRows;
    int numCols;
    undirectedGraph latticeGraph;
    int numVertices;
    std::vector<qreal> qubitAngles;
    std::vector<int> measuredQubitsOutcomes;
    


    // Set values to variables
    numRows = 1;
    numCols = numberCols; // Test on an odd number of qubits
    latticeGraph = createLatticeGraph(numRows,numCols);
    numVertices = boost::num_vertices(latticeGraph);



    // Print graph to file
    // Update with desired directory to view graph.
    //std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
    //std::string graphName = "1DLatticeOddQubitsAnglesEveryOther0And2PiMultiple";
    //std::string format = "png";
    //printGraphToFile(latticeGraph,fileDir,graphName,format);


    // load QuEST environment
    QuESTEnv env = createQuESTEnv();


    // create a quantum register
    Qureg qureg = createQureg(numVertices, env);

    

    // set angles
    
    if (assertValue == 0){
        qubitAngles = initRandomPiOnNEveryOtherAnglesMod2kPi(numVertices,piDenominator); // end in 0
    }else if (assertValue == 1){
        qubitAngles = initRandomPiOnNEveryOtherAnglesMod2kPiPlusPi(numVertices,piDenominator);  // end in 1
    }else{
        // Nothing
    }

    printVector(qubitAngles);
    // initialise in the plus state
    initPlusState(qureg);

    //Leave angle off qubits
    // add angles to the qubits
    //addAngleRotateZgate(qureg,qubitAngles);


    // entangle graph
    entangleGraph(qureg,latticeGraph);


    // measure graph
    measuredQubitsOutcomes = measureGraph(
        qureg,
        latticeGraph,
        qubitAngles,
        numRows);

    




    /*
    try {
        assertFunc(measuredQubitsOutcomes,assertValue);
    } catch (const std::runtime_error& e) {
        // Handle the exception
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
*/
    
    // print results to screen
    //printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);



    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}

// Set up the main function
int main() {
    
    for (int i = 0;i < 1e1;i++){
        testEveryOtherAnlgeZeroResults(0,4,7);
        testEveryOtherAnlgeZeroResults(1,4,7);
    }
   /*
    for(int i = 0; i < 1; i++)
    {
    // Initialise variable names and types
    int numRows;
    int numCols;
    undirectedGraph latticeGraph;
    int numVertices;
    std::vector<qreal> qubitAngles;
    std::vector<int> measuredQubitsOutcomes;
    int piDenominator;


    // Set values to variables
    numRows = 1;
    numCols = 7; // Test on an odd number of qubits
    latticeGraph = createLatticeGraph(numRows,numCols);
    numVertices = boost::num_vertices(latticeGraph);



    // Print graph to file
    // Update with desired directory to view graph.
    std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
    std::string graphName = "1DLatticeOddQubitsAnglesEveryOther0And2PiMultiple";
    std::string format = "png";
    printGraphToFile(latticeGraph,fileDir,graphName,format);


    // load QuEST environment
    QuESTEnv env = createQuESTEnv();


    // create a quantum register
    Qureg qureg = createQureg(numVertices, env);

    

    // set angles
    piDenominator = 4;
    //qubitAngles = initRandomPiOnNEveryOtherAnglesMod2kPi(numVertices,piDenominator); // end in 0
    qubitAngles = initRandomPiOnNEveryOtherAnglesMod2kPiPlusPi(numVertices,piDenominator);  // end in 1


    // initialise in the plus state
    initPlusState(qureg);

    //Leave angle off qubits
    // add angles to the qubits
    //addAngleRotateZgate(qureg,qubitAngles);


    // entangle graph
    entangleGraph(qureg,latticeGraph);


    // measure graph
    measuredQubitsOutcomes = measureGraph(
        qureg,
        latticeGraph,
        qubitAngles,
        numRows);

    assert((measuredQubitsOutcomes.back()==1) && "The last qubit must be 1, it is not.");
    // print results to screen
    printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);



    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    
    }
    */
    return 0;
}





