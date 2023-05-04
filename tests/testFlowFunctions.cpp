/////////////////////////////////////////////////////////////
// Title  : testGraphProperties.cpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Build graphs and test properties of graphs.    //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"

using namespace boost;

typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;




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

int getLattice2DFutureVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int futureVertex = getLattice2DFutureVertex(vertex,numRows);
    auto it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), futureVertex);
    assert(("flow function produced a vertex not in the input v neighbourhodd" && it != vertexNeighbours.end()));
    
    return futureVertex;
}

int getLattice2DPastVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int pastVertex = getLattice2DPastVertex(vertex,numRows);
    auto it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), pastVertex);
    assert(("flow function produced a vertex not in the input v neighbourhodd" && it != vertexNeighbours.end()));
    
    return pastVertex;
}




int main(){
    int presentVertex = 4;
    int numRows = 3;
    int numCols = 3;
    int totalVertices;
    int computedFutureVertex;
    int computedPastVertex;
    int expectedFutureVertex = presentVertex + numRows;
    int expectedPastVertex = presentVertex - numRows;
    

    undirectedGraph latticeGraph;
    
    totalVertices = numRows*numCols;




    computedFutureVertex = getLattice2DFutureVertex(presentVertex,numRows);
    computedPastVertex = getLattice2DPastVertex(presentVertex,numRows);
    assert(("Computed future vertex does not match expected" && computedFutureVertex == expectedFutureVertex));
    assert(("Computed past vertex does not match expected" && computedPastVertex == expectedPastVertex));



    latticeGraph = createLatticeGraph(numRows, numCols);
    print_graph(latticeGraph);
    std::cout << "Sets of neighbours per vertex:" << std::endl;
    for (int i=0;i<totalVertices;i++){
        std::cout << "Vertex " << i << " :";
        std::vector<int> neighbourVectorFunctionBased;
        neighbourVectorFunctionBased = getVertexNeighbours(latticeGraph,i);
        int size_neigh = neighbourVectorFunctionBased.size();
        for (int n=0; n<size_neigh;n++){
            std::cout << neighbourVectorFunctionBased[n] << " " ;    
        }
        std::cout << std::endl;
        
    }

    



    int graphFutureVertex = getLattice2DFutureVertexGraph(latticeGraph,presentVertex,numRows);
    int graphPastVertex = getLattice2DPastVertexGraph(latticeGraph,presentVertex,numRows);

    assert((graphFutureVertex==expectedFutureVertex));
    assert((graphPastVertex==expectedPastVertex));

    //getLattice2DPastVertex(presentVertex,numRows)

    return 0;
}

