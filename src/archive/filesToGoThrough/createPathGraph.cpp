#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS,boost::undirectedS,boost::no_property,EdgeWeightProperty> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;

//typedef adjacency_list<vecS, vecS, undirectedS> Graph; // define the graph type
//typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator; // define an edge iterator

undirectedGraph create_path_graph(int n) {  // create a path graph with n vertices
  undirectedGraph g(n);

  for (int i = 0; i < n-1; i++) {  // add edges to create a path graph
    add_edge(i, i+1, g);
  }

  return g;
}

int main() {
    int n = 100;
    undirectedGraph g = create_path_graph(n); // create a path graph with 5 vertices

    std::pair<edge_iterator, edge_iterator> ei = edges(g);
 
    std::cout << "Number of edges = " << num_edges(g) << "\n";
    std::cout << "Edge list:\n";
 
    for (edge_iterator it = ei.first; it != ei.second; ++it )
    {
        std::cout << *it << std::endl;
    }
 
    std::cout << std::endl;
 

  return 0;
}
