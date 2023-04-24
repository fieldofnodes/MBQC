#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <boost/container/vector.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>




using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<UndirectedGraph>::vertex_iterator vertex_iterator;


/*
  Return true if i == j, else false
*/
bool testTwoValueEquate (int i, int j) {
  return (i==j);
}


/*
  Get minimum value inside a vector
*/
int getMin(const boost::container::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Cannot get max of empty vector");
    }

    int min_val = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min_val) {
            min_val = vec[i];
        }
    }

    return min_val;
}


/*
  Get maximum value inside a vector
*/
int getMax(const boost::container::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Cannot get max of empty vector");
    }

    int max_val = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max_val) {
            max_val = vec[i];
        }
    }

    return max_val;
}


/*
  create a lattice graph with n x m vertices
*/
UndirectedGraph createLatticeGraph(int n, int m) { 
  UndirectedGraph g(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < m-1) add_edge(i*m+j, i*m+j+1, g); // add horizontal edges
      if (i < n-1) add_edge(i*m+j, (i+1)*m+j, g); // add vertical edges
    }
  }

  return g;
}



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


void assertGraphNumVertices(const UndirectedGraph& graph, int numVertices){
  int num_vertices = boost::num_vertices(graph);
  assert("Number of vertices in graph must equal input" && numVertices == num_vertices);
}