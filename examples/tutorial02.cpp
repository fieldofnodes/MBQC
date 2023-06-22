/**
 * @page tutorial02 Tutorial 2: MBQC Starter
 * @ingroup GettingStarted
 * 
 * @section intro Introduction
 *
 * This tutorial provides an overview of the MBQC Starter File script. The script demonstrates the implementation of Measurement-Based Quantum Computing (MBQC) using the QuEST library. It creates a lattice graph, initializes a quantum register, applies rotations to the qubits, entangles the graph, performs measurements, and prints the results.
 * 
 * For the source code of the tutorial, see the file @ref examples/mbqcStarter.cpp
 *
 * @section overview Script Overview
 *
 * The script performs the following steps:
 *   - Includes the necessary package header file.
 *   - Declares and initializes variables of different types.
 *   - Creates a lattice graph based on the specified number of rows and columns.
 *   - Prints the graph to a file.
 *   - Initializes the QuEST environment and creates a quantum register with the specified number of vertices.
 *   - Initializes random angles in the range of π on N angles and assigns them to the qubitAngles vector.
 *   - Initializes the quantum register in the plus state.
 *   - Applies angle rotations around the Z-axis to the qubits based on the qubitAngles vector.
 *   - Entangles the graph using the entangleGraph function.
 *   - Measures the graph, and stores the outcomes in the measuredQubitsOutcomes vector.
 *   - Prints the results to the screen.
 *   - Deallocates the QuEST environment and the quantum register.
 *
 * @section usage Usage
 *
 * To use the MBQC Starter File script:
 *   - Modify the values of numRows and numCols to set the desired number of rows and columns for the lattice graph.
 *   - Set the figsDir variable to the desired directory to view the graph.
 *   - Compile and run the script.
 *
 * @subsection include Include Package Header File
 *
 * The script starts by including the necessary package header file:
 *
 * @code{.cpp}
 * #include "packages.hpp"
 * @endcode
 *
 * @subsection main Set up the Main Function
 *
 * The main function is set up as follows:
 *
 * @code{.cpp}
 * int main() {
 *     // Initialise variable names and types
 *     int numRows;
 *     int numCols;
 *     undirectedGraph latticeGraph;
 *     int numVertices;
 *     std::vector<qreal> qubitAngles;
 *     std::vector<int> measuredQubitsOutcomes;
 * @endcode
 *
 * @subsection setvalues Set Values to Variables
 *
 * The values for `numRows`, `numCols`, and `latticeGraph` are set as follows:
 *
 * @code{.cpp}
 *     numRows = 4;
 *     numCols = 4;
 *     latticeGraph = createLatticeGraph(numRows, numCols);
 *     numVertices = boost::num_vertices(latticeGraph);
 * @endcode
 *
 * @subsection printgraph Print Graph to File
 *
 * The graph is printed to a file using the specified directory, graph name, and format:
 *
 * @code{.cpp}
 *     // Print graph to file
 *     // Update with desired directory to view graph.
 *     std::string figsDir = MBQC_FIGS_DIR;
 *     std::string graphName = "lattice2DGraphCmakeV2";
 *     std::string format = PNG_FORMAT;
 *     printGraphToFile(latticeGraph, figsDir, graphName, format);
 * @endcode
 *
 * @subsection loadenv Load QuEST Environment
 *
 * The QuEST environment is loaded using the `createQuESTEnv` function:
 *
 * @code{.cpp}
 *     // load QuEST environment
 *     QuESTEnv env = createQuESTEnv();
 * @endcode
 *
 * @subsection createqreg Create Quantum Register
 *
 * The quantum register is created using the specified number of vertices:
 *
 * @code{.cpp}
 *     // create a quantum register
 *     Qureg qureg = createQureg(numVertices, env);
 * @endcode
 *
 * @subsection initangles Initialize Random Angles
 *
 * Random angles in the range of π on N angles are initialized and assigned to the `qubitAngles` vector:
 *
 * @code{.cpp}
 *     //qubitAngles = initRandomPiOnNAnglesMod2kPi(numVertices, 4);
 *     qubitAngles = initRandomPiOnNAnglesMod2kPiPlusPi(numVertices, 4);
 * @endcode
 *
 * @subsection initstate Initialize in Plus State
 *
 * The quantum register is initialized in the plus state using the `initPlusState` function:
 *
 * @code{.cpp}
 *     // initialise in the plus state
 *     initPlusState(qureg);
 * @endcode
 *
 * @subsection addangles Add Angles to Qubits
 *
 * Angle rotations around the Z-axis are added to the qubits based on the `qubitAngles` vector:
 *
 * @code{.cpp}
 *     // add angles to the qubits
 *     addAngleRotateZgate(qureg, qubitAngles);
 * @endcode
 *
 * @subsection entangle Entangle Graph
 *
 * The graph is entangled using the `entangleGraph` function:
 *
 * @code{.cpp}
 *     // entangle graph
 *     entangleGraph(qureg, latticeGraph);
 * @endcode
 *
 * @subsection measure Measure Graph
 *
 * The graph is measured, and the outcomes are stored in the `measuredQubitsOutcomes` vector:
 *
 * @code{.cpp}
 *     // measure graph
 *     measuredQubitsOutcomes = measureGraph(qureg, latticeGraph, qubitAngles, numRows);
 * @endcode
 *
 * @subsection printresults Print Results to Screen
 *
 * The results are printed to the screen using the `printResultsToScreen` function:
 *
 * @code{.cpp}
 *     // print results to screen
 *     printResultsToScreen(measuredQubitsOutcomes, numRows, numCols);
 * @endcode
 *
 * @subsection unloadenv Unload QuEST
 *
 * The QuEST environment and the quantum register are deallocated:
 *
 * @code{.cpp}
 *     // unload QuEST
 *     destroyQureg(qureg, env); 
 *     destroyQuESTEnv(env);
 *     return 0;
 * }
 * @endcode
 * 
 * This is how you run a file. For any help, questions or problems see the [MBQC](https://github.com/ediparquantum/MBQC) repository site to create an 
 * - [issue](https://github.com/ediparquantum/MBQC/issues), 
 * - [pull-request](https://github.com/ediparquantum/MBQC/pulls) or 
 * - open a [discussion](https://github.com/ediparquantum/MBQC/discussions).
 */
