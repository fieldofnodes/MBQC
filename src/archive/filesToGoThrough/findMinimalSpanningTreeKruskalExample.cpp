#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <fstream>
 
int main()
{
  typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
   
  typedef boost::graph_traits <Graph>::edge_descriptor Edge;
  typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
  typedef std::pair<int, int> E;
 
  const int num_nodes = 5;
  E edge_array[] = { E(0, 2), E(1, 3), E(1, 4), E(2, 1), E(2, 3),
    E(3, 4), E(4, 0), E(4, 1)
  };
   
  int weights[] = { 1, 1, 2, 7, 3, 1, 1, 1 };
  std::size_t num_edges = sizeof(edge_array) / sizeof(E);
 
  Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
 
  boost::property_map<Graph, boost::edge_weight_t >::type weight = get(boost::edge_weight, g);
  std::vector < Edge > spanning_tree;
 
  boost::kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
 
  std::cout << "Print the edges in the MST:" << std::endl;
   
  for (std::vector < Edge >::iterator ei = spanning_tree.begin();
        ei != spanning_tree.end(); ++ei) 
  {
    std::cout << source(*ei, g) 
              << " <--> "
              << target(*ei, g)
              << " with weight of "
              << weight[*ei]
              << std::endl;
  }
 
  return 0;
} 