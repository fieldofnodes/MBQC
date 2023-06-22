/////////////////////////////////////////////////////////////
// Title  : testOddNumberQubitAnglesAllZero.cpp            //
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
    numCols = 2; // Test on an odd number of qubits
    latticeGraph = createLatticeGraph(numRows,numCols);
    numVertices = boost::num_vertices(latticeGraph);



    // Print graph to file
    // Update with desired directory to view graph.
    //std::string fileDir = "/Users/jmille15/Projects/QuEST/QuEST/projects/MBQC/figs";
    //std::string graphName = "1DLattice2QubitsAnglesPiOn2";
    //std::string format = "png";
    //printGraphToFile(latticeGraph,fileDir,graphName,format);


    // load QuEST environment
    QuESTEnv env = createQuESTEnv();


    // create a quantum register
    Qureg qureg = createQureg(numVertices, env);


    // set angles
    qubitAngles = initAllAnglesSame(numVertices, M_PI/2);


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

    assert((measuredQubitsOutcomes.back()==0) && "The last qubit must be 0, it is not.");
    // print results to screen
    //printResultsToScreen(measuredQubitsOutcomes,numRows,numCols);



    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    
    }
    return 0;
}




