#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS,boost::undirectedS,boost::no_property,EdgeWeightProperty> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;



// create a 1D path graph on 1xn vertices
undirectedGraph createPathGraph(int n) { 
  undirectedGraph g(n);

  for (int i = 0; i < n-1; i++) {  // add edges to create a path graph
    add_edge(i, i+1, g);
  }

  return g;
}

// create a 2D lattice graph with n x m vertices
undirectedGraph createLatticeGraph(int n, int m) { 
  undirectedGraph g(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < m-1) add_edge(i*m+j, i*m+j+1, g); // add horizontal edges
      if (i < n-1) add_edge(i*m+j, (i+1)*m+j, g); // add vertical edges
    }
  }

  return g;
}



std::vector<undirectedGraph::vertex_descriptor> get_adjacent_vertices(const undirectedGraph& g, const undirectedGraph::vertex_descriptor v)
{
    std::vector<undirectedGraph::vertex_descriptor> adjacent_vertices;
    undirectedGraph::adjacency_iterator ai, ai_end;
    for (boost::tie(ai, ai_end) = boost::adjacent_vertices(v, g); ai != ai_end; ++ai)
    {
        adjacent_vertices.push_back(*ai);
    }
    return adjacent_vertices;
}
