#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
  
typedef boost::property<boost::edge_weight_t, double> EdgeWeight;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeight> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
  
int main(int, char*[])
{
    // 1. Undirected graph - print out the edge weights
    undirectedGraph g;
  
    boost::add_edge(0, 1, 8, g);
    boost::add_edge(0, 5, 2, g);
    boost::add_edge(5, 6, 1, g);
    boost::add_edge(4, 5, 5, g);
    boost::add_edge(3, 5, 7, g);
  
    boost::property_map<undirectedGraph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight_t(), g);
  
    std::pair<edge_iterator, edge_iterator> edgePair;
    for (edgePair = edges(g); edgePair.first != edgePair.second; ++edgePair.first)
    {
        std::cout << *edgePair.first << " " << EdgeWeightMap[*edgePair.first] << std::endl;
    }   
  
    return 0;
}