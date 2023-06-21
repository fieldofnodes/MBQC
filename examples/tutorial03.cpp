/**
 * @page tutorial03 Tutorial 3: 1D Odd size angles 0
 * @ingroup GettingStarted
 * 
 * @section intro Introduction
 * 
 * This tutorial demonstrates the creation of a 1D lattice in MBQC where each qubit is initialized with an H gate to be |+>,
 * and each qubit has an angle of 0 on the z-axis. The goal is to show that with an odd number of qubits and specific flow and 
 * basis measurements, the final qubit should always be 0.
 * 
 * The source code can be foubd at @ref tests/testOddNumberQubitAnglesAllZero.cpp. In the code there is a loop, which iterates the test 1e6 times and runs the assert command each iteration. Simply change 1e6 to 1 and you will run the simulation once.
 * 
 * @code{.cpp}
 * for(int i = 0; i < 1e6; i++)
    {}
 * @endcode
 * 
 * @section code Code Description
 * 
 * @subsection include Include Package Header File
 *
 * The script starts by including the necessary package header file:
 *
 * @code{.cpp}
 * #include "packages.hpp"
 * @endcode
 * 
 * @subsection initValues The following code initializes the necessary variables and sets values for the 1D lattice:
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
 * @section conclusion Conclusion
 * 
 * This tutorial demonstrates the creation of a 1D lattice in MBQC where all qubit angles are 0. By following the specified flow
 * and basis measurements, it ensures that the final qubit is always 0.
 */
