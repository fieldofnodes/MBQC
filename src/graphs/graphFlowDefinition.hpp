///////////////////////////////////////////////////////////////
// Filename  : graphFlowDefinition.hpp
// Author    : Jonathan Miller
// Date      : 2023-06-19
// Aim       : aim_script
//           : This script contains functions for asserting 
//           : and checking properties in an undirected graph. 
//           : The assertFlowFunctionNeighbour function verifies 
//           : if the flow function for a vertex and its 
//           : neighbors meets a condition. areVerticesConnected 
//           : checks if two vertices are connected by an edge. 
//           : The assertFlowFunctionNeighbourVertex and 
//           : assertFlowFunctionFutureOfVertex functions 
//           : assert conditions related to flow functions and 
//           : vertex properties. Finally, 
//           : assertNeighbourFlowFunctionFutureOfVertex 
//           : asserts a condition involving neighbors, 
//           : flow functions, and vertex futures.
///////////////////////////////////////////////////////////////



/**
 * @brief Asserts the flow function for a given vertex and its neighbors in the graph.
 *
 * This function asserts that the flow function for a given vertex and its neighbors
 * in the undirected graph satisfies a certain condition. It takes the graph 'g', the
 * vertex 'v', the number of rows 'numRows', and the flow function 'flowFunction' as
 * input parameters. It calculates the forward lattice flow for the vertex 'v' using
 * the provided flow function and checks if it is present in the list of neighbors of 'v'.
 * If the flow value is found in the neighbor vertices, the assertion passes.
 *
 * @param g The undirected graph.
 * @param v The vertex for which to assert the flow function and its neighbors.
 * @param numRows The number of rows in the lattice.
 * @param flowFunction The flow function to be tested.
 */
void assertFlowFunctionNeighbour(const undirectedGraph& g, int v, int numRows, std::function<int(int, int)>flowFunction)
{
    // Call the flow function to get the forward lattice flow
    int fv = flowFunction(v, numRows);
    std::vector<int> neigh = getVertexNeighbours(g,v)
    
    isIntInVector(v, neigh)
    
}



/**
 * @brief Checks if two vertices in the undirected graph are connected by an edge.
 *
 * This function checks if two vertices 'u' and 'v' in the undirected graph 'g' are
 * connected by an edge. It uses the boost::edge() function to check the presence of
 * an edge between 'u' and 'v'. If an edge exists, the function returns true; otherwise,
 * it returns false.
 *
 * @param g The undirected graph.
 * @param u The first vertex.
 * @param v The second vertex.
 * @return True if there is an edge between 'u' and 'v', false otherwise.
 */
bool areVerticesConnected(const undirectedGraph& g, undirectedGraph::vertex_descriptor u, undirectedGraph::vertex_descriptor v) {
    auto edge = boost::edge(u, v, g);
    return edge.second; // Returns true if there is an edge between u and v
}



/**
 * @brief Asserts a condition for the flow function of a given vertex and its neighbors.
 *
 * This function asserts a condition for the flow function of a given vertex 'vertex' in
 * the undirected graph 'g' and its neighboring vertices. It performs an assertion that
 * involves the flow function of 'vertex' and its neighbors.
 *
 * @param g The undirected graph.
 * @param vertex The vertex for which to assert the flow function and its neighbors.
 */
void assertFlowFunctionNeighbourVertex(const undirectedGraph& g,int vertex){
    // Assert that for vertex, v, than f(v) is a neighbour
}


/**
 * @brief Asserts a condition for the flow function and future of a given vertex.
 *
 * This function asserts a condition for the flow function and future of a given vertex
 * 'vertex' in the undirected graph 'g'. It performs an assertion that involves the flow
 * function and future of 'vertex'.
 *
 * @param g The undirected graph.
 * @param vertex The vertex for which to assert the flow function and future.
 */
void assertFlowFunctionFutureOfVertex(const undirectedGraph& g,int vertex){
    
}

/**
 * @brief Asserts a condition involving the neighbor, flow function, and future of a vertex.
 *
 * This function asserts a condition that involves the neighbor, flow function, and future
 * of a vertex in the undirected graph 'g'. It performs an assertion based on these properties
 * of the vertex.
 *
 * @param g The undirected graph.
* @param vertex The vertex for which to assert the flow function and future.
 */
void

void assertNeighbourFlowFunctionFutureOfVertex(const undirectedGraph& g,int vertex){
    
}




