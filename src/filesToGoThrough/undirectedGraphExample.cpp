#include <boost/graph/adjacency_list.hpp>
#include <iostream>
 
typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS,boost::undirectedS,boost::no_property,EdgeWeightProperty> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;
 
int main()
{
    UndirectedGraph g;
 
    boost::add_edge (0, 1, 8, g);
    boost::add_edge (0, 3, 18, g);
    boost::add_edge (1, 2, 20, g);
    boost::add_edge (2, 3, 2, g);
    boost::add_edge (1, 3, 7, g);
    boost::add_edge (1, 4, 1, g);
    boost::add_edge (4, 5, 6, g);
    boost::add_edge (2, 5, 7, g);
 
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