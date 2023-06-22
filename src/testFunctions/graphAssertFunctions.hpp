/////////////////////////////////////////////////////////////
// Title  : graphAssertFunctions.hpp                       //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct assertion functions for graphs       //
/////////////////////////////////////////////////////////////



/*
    Functions to be used to test graph properties. 
    List of functions used in general graph assertions
    1. assertHandShakeLemma
    2. assertPathGraphMinMaxDegrees
    3. assertDegreeSetLatticeGraph

    assertHandShakeLemma
    The hand shake lemma states that the sum of degrees is equivalent to two times the number of edges
    sum(deg(v)) = 2|E| for v in V

    assertPathGraphMinMaxDegrees
    A path graph will degrees 1 and 2

    assertDegreeSetLatticeGraph
    A lattice graph in 2d will have degrees 2,3 and 4
*/




/**
 * @brief Asserts the Handshake Lemma for an undirected graph.
 *
 * This function asserts the Handshake Lemma for an undirected graph. The Handshake Lemma states that the sum of the degrees of all vertices in an undirected graph is equal to twice the number of edges in the graph.
 *
 * @param graph The undirected graph to check.
 * @throws std::runtime_error if the Handshake Lemma is violated.
 */
void assertHandShakeLemma(const undirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    boost::container::vector<int> degree_vector;

    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      undirectedGraph::vertex_descriptor v;
      v = boost::vertex(i, graph); 
      degree_vector.push_back(boost::degree(v, graph));        
    }

    int num_edge = boost::num_edges(graph);   
    int sum = std::accumulate(degree_vector.begin(), degree_vector.end(), 0);
    assert(("total degree is two times the edge set" && sum == 2 * num_edge));
}



/**
 * @brief Asserts the minimum and maximum degrees for a path graph.
 *
 * This function asserts that the minimum degree of a path graph is 1 and the maximum degree is 2. It calculates the degrees of all vertices in the provided graph and checks if the minimum degree is 1 and the maximum degree is 2.
 *
 * @param graph The path graph to check.
 * @throws std::runtime_error if the minimum or maximum degree is violated.
 */
void assertPathGraphMinMaxDegrees(const undirectedGraph& graph) {
    int num_vertices = boost::num_vertices(graph);
    boost::container::vector<int> degree_vector;

    // Calculate the degree of each vertex
    for (int i = 0; i < num_vertices; i++) {
        undirectedGraph::vertex_descriptor v;
        v = boost::vertex(i, graph);
        degree_vector.push_back(boost::degree(v, graph));
    }

    int min_degree = getMin(degree_vector);
    assert(("minimum degree is 1" && min_degree == 1));
    int max_degree = getMax(degree_vector);
    assert(("maximum degree is 2" && max_degree == 2));
}




/**
 * @brief Asserts the degree set for a lattice graph.
 *
 * The function checks whether the degrees of all vertices in the provided lattice graph belong to the set {2, 3, 4}. It calculates the degrees of all vertices in the graph and filters out degrees that are not in the required set. It then asserts that all remaining degrees are either 2, 3, or 4.
 *
 * @param graph The lattice graph to check.
 * @throws std::runtime_error if a degree outside the set {2, 3, 4} is found.
 */
void assertDegreeSetLatticeGraph(const undirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    std::vector<int> degree_vector;
    std::vector<int> required_deg_vector = {2,3,4};
    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      undirectedGraph::vertex_descriptor v;
      v = boost::vertex(i, graph); 
      int d = boost::degree(v, graph);
      degree_vector.push_back(d);        
    }

    sort( degree_vector.begin(), degree_vector.end() );
    
    degree_vector.erase(std::unique( degree_vector.begin(), degree_vector.end() ), degree_vector.end() );


    std::vector<int> filt;
    std::copy_if(degree_vector.begin(), degree_vector.end(), std::back_inserter(filt), [](int i) {
        return i == 2 || i == 3 || i == 4;
    });
 
    for (int &i: filt) {
        assert("Degree must be either 2,3 or 4" && i == 2 || i == 3 || i == 4);
    }

}


/**
 * @brief Asserts the number of vertices in a graph.
 *
 * The function checks whether the number of vertices in the provided graph matches the expected number of vertices. It compares the actual number of vertices in the graph with the expected number and throws an assertion error if they do not match.
 *
 * @param graph The graph to check.
 * @param numVertices The expected number of vertices.
 * @throws std::runtime_error if the number of vertices does not match the expected number.
 */
void assertGraphNumVertices(const undirectedGraph& graph, int numVertices){
  int num_vertices = boost::num_vertices(graph);
  assert("Number of vertices in graph must equal input" && numVertices == num_vertices);
}



/**
 * @brief Asserts that flow functions perform as expected in a graph.
 *
 * The function checks whether the flow functions in the provided graph produce the expected results. It verifies that the computed vertices from the flow functions match the expected vertices based on the graph structure and the specified number of rows. It throws an assertion error if any mismatch is found.
 *
 * @param graph The graph to check.
 * @param numRows The number of rows in the graph.
 * @throws std::runtime_error if any computed vertex does not match the expected vertex.
 */
void assertFlowFunctionsPerformExpected(const undirectedGraph& graph, int numRows) {
    undirectedGraph::vertex_iterator vi, vi_end;
    int size_graph = boost::num_vertices(graph);

    for (boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi) {
        // Skip vertices that are in the first column
        if (*vi >= numRows) {
            int computedVi = getLattice2DPastVertexGraph(graph, *vi, numRows);
            int expectedVi = *vi - numRows;
            assert(((expectedVi == computedVi) && "Expected vertex does not match computed vertex from getLattice2DPastVertexGraph function"));
        }
    }
    
    for (boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi) {
        // Skip vertices that are in the last column
        if (*vi < (size_graph - numRows)) {
            int computedVi = getLattice2DFutureVertexGraph(graph, *vi, numRows);
            int expectedVi = *vi + numRows;
            assert(((expectedVi == computedVi) && "Expected vertex does not match computed vertex from getLattice2DPastVertexGraph function"));
        }
    }
}

/**
 * @brief Asserts that the computed neighborhood of each vertex in the graph matches the expected neighborhood.
 *
 * The function checks whether the computed neighborhood of each vertex in the provided graph matches the expected neighborhood specified in `expectedNeighbourhood`. It throws an assertion error if any mismatch is found.
 *
 * @param graph The graph to check.
 * @param expectedNeighbourhood The expected neighborhood for each vertex. The outer vector represents vertices, and the inner vectors represent their respective neighborhoods.
 * @throws std::runtime_error if any computed neighborhood does not match the expected neighborhood.
 */
void assertNieghbours(const undirectedGraph& graph,std::vector<std::vector<int>> expectedNeighbourhood){        
    int size_graph = boost::num_vertices(graph);
    for (int vertexIter = 0; vertexIter < size_graph; vertexIter++){
        std::vector<int> computedNeighbours = getVertexNeighbours(graph,vertexIter);
        std::vector<int> expectedNeighbours;
        expectedNeighbours = expectedNeighbourhood[vertexIter];
    
        std::sort(expectedNeighbours.begin(), expectedNeighbours.end());
        std::sort(computedNeighbours.begin(), computedNeighbours.end());
        assert(expectedNeighbours.size() == computedNeighbours.size() && std::equal(expectedNeighbours.begin(), expectedNeighbours.end(), computedNeighbours.begin()));
    }
    return;
}



/**
 * @brief Asserts that the computed corrected angle matches the expected corrected angle.
 *
 * The function computes the corrected angle using the `computeCorrectedAngle` function and compares it with the expected corrected angle. It throws an assertion error if the computed corrected angle does not match the expected corrected angle.
 *
 * @param graph The graph representing the lattice.
 * @param outcomeVector The vector of measured outcomes.
 * @param vertex The vertex for which the corrected angle is computed.
 * @param numRows The number of rows in the lattice.
 * @param inputAngle The input angle for the vertex.
 * @param expectedCorrectedAngle The expected corrected angle.
 * @throws std::runtime_error if the computed corrected angle does not match the expected corrected angle.
 */
void assertCorrection(
    const undirectedGraph& graph,
    std::vector<int> outcomeVector, 
    int vertex,
    int numRows,
    qreal inputAngle,
    qreal expectedCorrectedAngle){
        
        qreal computedCorrectedAngle = computeCorrectedAngle(
            graph,
            outcomeVector, 
            vertex,
            numRows,
            inputAngle);
        
        assert(("New angle and original angle do not match" && computedCorrectedAngle == expectedCorrectedAngle));
}




/**
 * @brief Tests the measurement outcomes with every other angle set to zero.
 *
 * This function performs a test where the measurement outcomes are checked based on the specified assert value, pi denominator, and number of columns. The function initializes variables, sets values, creates a quantum register, sets angles, entangles the graph, measures the graph, and unloads QuEST.
 *
 * @param assertValue The expected value for the measurement outcomes.
 * @param piDenominator The denominator for the angles in the range [0, 2*pi).
 * @param numberCols The number of columns in the lattice.
 */
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
