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
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <boost/container/vector.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>





using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;



/*
  inthe hand shake lemma stipulates that the total degree of a graph G,
  is equivalent to 2 times the number of edges
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



/*
  inthe hand shake lemma stipulates that the total degree of a graph G,
  is equivalent to 2 times the number of edges
*/
void assertPathGraphMinMaxDegrees(const undirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    boost::container::vector<int> degree_vector;

    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      undirectedGraph::vertex_descriptor v;
      v = boost::vertex(i, graph); 
      degree_vector.push_back(boost::degree(v, graph));        
    }

    int min_it = getMin(degree_vector);
    assert(("minimum degree is 1" && min_it == 1));
    int max_it = getMax(degree_vector);
    assert(("maximum degree is 1" && max_it == 2));

}



/*
  inthe hand shake lemma stipulates that the total degree of a graph G,
  is equivalent to 2 times the number of edges
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


/*
  Assert that the number of vertices in a graph matches expected input 
*/
void assertGraphNumVertices(const undirectedGraph& graph, int numVertices){
  int num_vertices = boost::num_vertices(graph);
  assert("Number of vertices in graph must equal input" && numVertices == num_vertices);
}


/*
  Test for all flow on vertices
  Iterate over the vertices of the graph
*/
void assertFlowFunctionsPerformExpected(const undirectedGraph& graph,int numRows){
    undirectedGraph::vertex_iterator vi, vi_end;
    int size_graph = boost::num_vertices(graph);

    for (boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi) {
        // skip vertices that are in the first column
        if(*vi >= numRows){
            int computedVi = getLattice2DPastVertexGraph(graph,*vi,numRows);
            int expectedVi = *vi - numRows;
            assert(("Expected vertex does not match computed vertex from getLattice2DPastVertexGraph function",(expectedVi == computedVi)));
        }
    }
    
    for (boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi) {
        // skip vertices that are in the first column
        if(*vi < (size_graph-numRows)){
            int computedVi = getLattice2DFutureVertexGraph(graph,*vi,numRows);
            int expectedVi = *vi + numRows;
            assert(("Expected vertex does not match computed vertex from getLattice2DPastVertexGraph function",(expectedVi == computedVi)));
        }
    }
    return ;
}

/*
  Assert each vertex neighbour has a matchin neighbour to the input
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

/*
  Assert the correction angle is the same as the inputted correction angle
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