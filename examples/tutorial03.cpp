/**
 * @page tutorial03 Tutorial 3: 1D Lattice
 * @ingroup GettingStarted
 * 
 * @section intro Introduction 
 * 
 * This tutorial demonstrates some consequences of implementing a MBQC pattern on a one dimensional lattice graph.
 * 
 * \image html ghz_mbqc.png "Example 1D Lattice"
 * 
 * By creating a quantum register, either with a state vector or density matrix in QuEST, applying the Hadamard gate and some rotational angle \f$\theta\f$ on a Pauli-Z gate to each qubit, then entangling the register according the graph \f$G\f$ with the controlled Z gate, we obtain a MBQC graph-circuit. The following code implements the circuit represented by the "Example 1D Lattice" figure.
 * 
 * @code{.cpp}
 * QuESTEnv env = createQuESTEnv();
 * int numQubits = 3;
 * Qureg qubits = createQureg(numQubits, env);
 * initPlusState(qubits);
 * rotateZ(qureg,0,0);
 * rotateZ(qureg,1,0);
 * rotateZ(qureg,2,0);
 * controlledPhaseFlip(qureg,0,1);
 * controlledPhaseFlip(qureg,1,2);		
 * @endcode
 * 
 * QuEST performs mid-circuit measurements that are destructive, thus allowing for projective measurements to be simulated. In the figure, the vertex to the far left will be measured first. Its outcome will inform the basis angle associated with the middle vertex and depending on the first outcome being a \f$0\f$ or \f$1\f$. The basis of measurement adapts to previous measurements in relation to the graph flow. Finally the far right vertex will be informed by the first two measurment outcomes (see Tutorial @ref examples/tutorial04.cpp for a discussion on flow).
 * 
 * @section oneDLatticeResults One Dimensional Results
 * 
 * @subsection oddQubitsZeroAngles Odd number of qubits
 * 
 * In the case there the number of vertices in the graph is an odd number and the angle applied to every qubit is \f$0\f$, then the final measurement of the graph, the last qubit will have an outcome of \f$0\f$. The source code can be foubd at @ref tests/testOddNumberQubitAnglesAllZero.cpp. 
 * 
 * In this referenced script there is a loop, which iterates the test \f$1,000,000\f$ times and runs the `assert` command each iteration to verify the last qubit of the graph is \f$0\f$. Simply change 1e6 to 1 and you will run the simulation once.
 * 
 * @code{.cpp}
 * for(int i = 0; i < 1e6; i++)
    {}
 * @endcode
 * 
 * The script starts by including the necessary package header file:
 *
 * @code{.cpp}
 * #include "packages.hpp"
 * @endcode
 * 
 * Initialise the following code with the necessary variables and sets values for the 1D lattice:
 * 
 * 
 * @code{.cpp}
 * int numRows;
 * int numCols;
 * undirectedGraph latticeGraph;
 * int numVertices;
 * std::vector<qreal> qubitAngles;
 * std::vector<int> measuredQubitsOutcomes;
 * 
 * // Set values to variables
 * numRows = 1;
 * numCols = 11; // Test on an odd number of qubits
 * latticeGraph = createLatticeGraph(numRows, numCols);
 * numVertices = boost::num_vertices(latticeGraph);
 * @endcode
 * 
 * The quantum circuit is created and initialized:
 * 
 * @code{.cpp}
 * // load QuEST environment
 * QuESTEnv env = createQuESTEnv();
 * 
 * // create a quantum register
 * Qureg qureg = createQureg(numVertices, env);
 * 
 * // Initialize qubit angles to 0
 * qubitAngles = initAllAnglesZero(numVertices);
 * 
 * // Initialise in the plus state
 * initPlusState(qureg);
 * 
 * // Add angles to the qubits
 * addAngleRotateZgate(qureg, qubitAngles);
 * @endcode
 * 
 * The graph is entangled and measurements are performed on the lattice:
 * 
 * @code{.cpp}
 * // Entangle graph
 * entangleGraph(qureg, latticeGraph);
 * 
 * // Measure graph
 * measuredQubitsOutcomes = measureGraph(qureg, latticeGraph, qubitAngles, numRows);
 * 
 * assert((measuredQubitsOutcomes.back() == 0) && "The last qubit must be 0, it is not.");
 * @endcode
 * 
 * This test indeen shows that the final qubit is always measured as a \f$0\f$ outcome.
 * 
 * @subsection twoQubiTsPi Two Qubits with angle Pi
 * 
 * This graph, a simple two vertex graph, where both angles \f$\theta = \pi/2\f$ is different from the above as
 * - There are only 2 qubits
 * - Each has a non-zero angle
 * - The angle is \f$\theta = \pi/2\f$ 
 * 
 * The outcome is that the second qubit is always measured a \f$0\f$. The script can be found here @ref tests/testTwoQubitsAnglesPiOnTwo.cpp
 * 
 * @code{.cpp}
 *  // Initialise variable names and types
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
 * @endcode
 *
 * @subsection oddQubitEveryOtherIsZero Odd number of qubits every other is zero
 * 
 * This test has an odd number of qubits and 
 * - Every other qubit, starting from the second qubit, is \f$0\f$
 * - When the sum of the angles is a multiple of \f$2k\pi\f$ then the last qubit is zero
 * - When the sum of the angles is a multiple of \f$2k\pi + \pi\f$ then the last qubit is one
 * 
 * This script performing this test is found here @ref tests/testOddNumberQubitsEverySecondsAngleZero.cpp
 * 
 * To complete this test the `assertFunc` was written
 * 
 * @code{.cpp}
 * void assertFunc(std::vector<int> measuredQubitsOutcomes,int assertValue) {
    if (measuredQubitsOutcomes.back() != assertValue) {
        throw std::runtime_error("The last qubit must be " + std::to_string(assertValue) + ", it is not.");
    }
}
 * @endcode
 *
 * As well to simplify the `main` function the `testEveryOtherAnlgeZeroResults` function was written
 * 
 * @code{.cpp}
 * void testEveryOtherAnlgeZeroResults(int assertValue,int piDenominator,int numberCols){
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

    





    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}
 * @endcode
 * 
 * Finally, the test implemented
 * 
 * @code{.cpp}
    // Include package header file
   #include "packages.hpp"



   // Set up the main function
   int main() {
      
      for (int i = 0;i < 1e1;i++){
         testEveryOtherAnlgeZeroResults(0,4,7);
         testEveryOtherAnlgeZeroResults(1,4,7);
      }
   
      return 0;
   }
   * @endcode
 *
 * In all of these tests, the registers have been pure states and hence constructed with state vectors.
 * 
 * This is how you run a file. For any help, questions or problems see the [MBQC](https://github.com/ediparquantum/MBQC) repository site to create an 
 * - [issue](https://github.com/ediparquantum/MBQC/issues), 
 * - [pull-request](https://github.com/ediparquantum/MBQC/pulls) or 
 * - open a [discussion](https://github.com/ediparquantum/MBQC/discussions).
 */


