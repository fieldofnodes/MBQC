#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS,boost::undirectedS,boost::no_property,EdgeWeightProperty> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;
    


undirectedGraph create_grid_lattice_graph(int n, int m) { // create a grid lattice graph with n x m vertices
  undirectedGraph g(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < m-1) add_edge(i*m+j, i*m+j+1, g); // add horizontal edges
      if (i < n-1) add_edge(i*m+j, (i+1)*m+j, g); // add vertical edges
    }
  }

  return g;
}




int main() {
  int n = 4, m = 3;
  undirectedGraph g = create_grid_lattice_graph(n, m); // create a 3 x 4 grid lattice graph

    std::pair<edge_iterator, edge_iterator> ei = edges(g);
 
    std::cout << "Number of edges = " << num_edges(g) << "\n";
    std::cout << "Edge list:\n";
 
    for (edge_iterator it = ei.first; it != ei.second; ++it )
    {
        std::cout << *it << std::endl;
    }
 
    std::cout << std::endl;

    vertex_iterator vi, vi_end;
    std::cout << "Vertex list:\n";
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
        std::cout << *vi << " ";
    }
    std::cout << std::endl;

  return 0;
}
