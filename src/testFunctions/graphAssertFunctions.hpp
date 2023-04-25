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
#include "generalAssertFunctions.hpp"




using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<UndirectedGraph>::vertex_iterator vertex_iterator;



/*
  inthe hand shake lemma stipulates that the total degree of a graph G,
  is equivalent to 2 times the number of edges
*/
void assertHandShakeLemma(const UndirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    boost::container::vector<int> degree_vector;

    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      UndirectedGraph::vertex_descriptor v;
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
void assertPathGraphMinMaxDegrees(const UndirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    boost::container::vector<int> degree_vector;

    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      UndirectedGraph::vertex_descriptor v;
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
void assertDegreeSetLatticeGraph(const UndirectedGraph& graph) {
    
    int num_vertices = boost::num_vertices(graph);
    std::vector<int> degree_vector;
    std::vector<int> required_deg_vector = {2,3,4};
    // Call the function and print the adjacent vertices of vertex 0
    for (int i = 0; i < num_vertices; i++) {
      UndirectedGraph::vertex_descriptor v;
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
void assertGraphNumVertices(const UndirectedGraph& graph, int numVertices){
  int num_vertices = boost::num_vertices(graph);
  assert("Number of vertices in graph must equal input" && numVertices == num_vertices);
}