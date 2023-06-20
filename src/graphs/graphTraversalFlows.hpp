/////////////////////////////////////////////////////////////
// Title  : graphTraversalFlows.hpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct graphs                               //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////





/**
 * @file graphTraversalFlows.hpp
 * @brief Construct graphs and perform various graph traversal operations.
 * @author Jonathan Miller
 * @date 20230425
 */

/**
 * @brief Computes the future vertex in a 2D lattice graph based on a flow function.
 *
 * For a 2D lattice graph, the flow function for a vertex returns the future vertex.
 * The future vertex is calculated as presentVertex + numRows, where numRows is the number of rows in the lattice.
 *
 * @param presentVertex The present vertex for which the future vertex is computed.
 * @param numRows The number of rows in the 2D lattice graph.
 * @return The future vertex.
 */
int getLattice2DFutureVertex(int presentVertex, int numRows){
    // For a 2D lattice graph 
    // (1)-(4)-(7)
    // (2)-(5)-(8)
    // (3)-(6)-(9)
    // a flow function for vertex 5
    // has future vertex 8
    // f(i) = i + r, r is numRows
    int futureVertex = presentVertex + numRows;
    
    return futureVertex;
}

/**
 * @brief Computes the past vertex in a 2D lattice graph based on a flow function.
 *
 * For a 2D lattice graph, the flow function for a vertex returns the past vertex.
 * The past vertex is calculated as presentVertex - numRows, where numRows is the number of rows in the lattice.
 *
 * @param presentVertex The present vertex for which the past vertex is computed.
 * @param numRows The number of rows in the 2D lattice graph.
 * @return The past vertex.
 */
int getLattice2DPastVertex(int presentVertex, int numRows){
    // For a 2D lattice graph 
    // (1)-(4)-(7)
    // (2)-(5)-(8)
    // (3)-(6)-(9)
    // a flow function for vertex 5
    // has past vertex 2
    // f(i) = i - r, r is numRows
    int pastVertex = presentVertex - numRows;
    
    return pastVertex;
}


/**
 * @brief Retrieves the neighboring vertices of a given vertex in an undirected graph.
 *
 * Given an undirected graph and a vertex, this function returns a vector containing the neighboring vertices of the given vertex.
 *
 * @param graph The undirected graph.
 * @param vertex The vertex for which the neighboring vertices are retrieved.
 * @return A vector containing the neighboring vertices.
 */
std::vector<int> getVertexNeighbours(const undirectedGraph& graph,int vertex){
    // Choose a vertex to find its adjacent vertices
    undirectedGraph::vertex_descriptor v = vertex;
    // Find the range of adjacent vertices
    typedef boost::graph_traits<undirectedGraph>::adjacency_iterator adjacency_iterator;
    std::pair<adjacency_iterator, adjacency_iterator> neighbors = adjacent_vertices(v, graph);

    std::vector<int> neighbourVector;
    
    for (adjacency_iterator it = neighbors.first; it != neighbors.second; ++it) {
        neighbourVector.push_back(*it);
    }
    return neighbourVector;
}

/**
 * @brief Computes the future vertex in a 2D lattice graph based on a flow function for a given vertex in the graph.
 *
 * This function calculates the future vertex for a given vertex in a 2D lattice graph based on a flow function.
 * It performs validation checks to ensure the input vertex and the computed future vertex satisfy certain conditions.
 *
 * @param graph The 2D lattice graph.
 * @param vertex The vertex for which the future vertex is computed.
 * @param numRows The number of rows in the 2D lattice graph.
 * @return The future vertex.
 * @pre The vertex inputted needs to be less than the number of vertices minus the number of rows.
 * @pre The flow function produced a vertex that is in the input vertex neighborhood.
 */
int getLattice2DFutureVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    int size_graph = boost::num_vertices(graph);
    assert("The vertex inputted needs to be less than the number of vertices - the number of the rows, but it is not" && vertex < (size_graph - numRows));
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int futureVertex = getLattice2DFutureVertex(vertex,numRows);
    auto it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), futureVertex);
    assert(("flow function produced a vertex not in the input v neighbourhodd" && it != vertexNeighbours.end()));
    
    return futureVertex;
}


/**
 * @brief Computes the past vertex in a 2D lattice graph based on a flow function for a given vertex in the graph.
 *
 * This function calculates the past vertex for a given vertex in a 2D lattice graph based on a flow function.
 * It performs validation checks to ensure the input vertex and the computed past vertex satisfy certain conditions.
 *
 * @param graph The 2D lattice graph.
 * @param vertex The vertex for which the past vertex is computed.
 * @param numRows The number of rows in the 2D lattice graph.
 * @return The past vertex.
 * @pre The inputted vertex needs to be greater than or equal to the number of rows.
 * @pre The flow function produced a vertex that is in the input vertex neighborhood.
 */
int getLattice2DPastVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    assert(("The inputted vertex needs to be greater than or equal to the number of rows." && vertex >= numRows));
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int pastVertex = getLattice2DPastVertex(vertex,numRows);
    std::vector<int>::iterator it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), pastVertex);
    assert(("flow function produced a vertex not in the input vertex neighbourhodd" && it != vertexNeighbours.end()));
    return pastVertex;
}


/**
 * @brief Computes the corrected angle based on measured outcomes and flow functions in an undirected graph.
 *
 * This function computes the corrected angle by considering the measured outcomes and flow functions of vertices in an undirected graph.
 * It takes into account the neighboring vertices, past vertices, and various correction factors to calculate the updated angle.
 *
 * @param graph The undirected graph.
 * @param measuredOutcomes The vector of measured outcomes.
 * @param vertex The vertex for which the corrected angle is computed.
 * @param numRows The number of rows in the 2D lattice graph.
 * @param angle The initial angle.
 * @return The corrected angle.
 */
qreal computeCorrectedAngle(
    const undirectedGraph& graph,
    std::vector<int> measuredOutcomes, 
    int vertex,
    int numRows, 
    qreal angle){

    std::vector<int> neighbourhood = getVertexNeighbours(graph,vertex);
    int xCorrectionVertex;
    std::vector<int> zCorrectionVertices;
    qreal updatedAngle;

    if (vertex < numRows){ // First column - no x correction no z correction
        updatedAngle = angle;
    } else if (vertex >= numRows){ // ensure we are in second column
        xCorrectionVertex = getLattice2DPastVertexGraph(graph,vertex,numRows);
        for (int i: neighbourhood){
            int past;
            if(i >= numRows){
                past = getLattice2DPastVertexGraph(graph,i,numRows);
            } else{
                continue;
            }
            zCorrectionVertices.push_back(past);
        }        

        // Remove vertex in neigbourhood if it is the vertrex
        // we want to measure
        zCorrectionVertices.erase(
                std::remove(
                    zCorrectionVertices.begin(), 
                    zCorrectionVertices.end(), vertex), 
                zCorrectionVertices.end());
        
        int exponent = measuredOutcomes[xCorrectionVertex];
        
        //std::cout << "f-1(j): " << xCorrectionVertex << std::endl;
        //std::cout << "s_f-1(j): " << exponent << std::endl;
        qreal xAngle = std::pow((-1), exponent)*angle;

        std::vector<int> outcomesForZ;
        for (int i:zCorrectionVertices){
            outcomesForZ.push_back(measuredOutcomes[i]);
        }

        int sum = std::accumulate(outcomesForZ.begin(), outcomesForZ.end(), 0);
        qreal zAngle = M_PI*sum;
        updatedAngle = xAngle + zAngle;

        }

        return updatedAngle;
        
}