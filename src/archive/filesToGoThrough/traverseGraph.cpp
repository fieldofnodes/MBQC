#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include "createGraph.hpp"
#include <vector>

using namespace boost;

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS,boost::undirectedS,boost::no_property,EdgeWeightProperty> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;



int main(){
    int rows;
    int cols;
    int pathVertices;
    undirectedGraph pathGraph;
    undirectedGraph latticeGraph;
    
    rows = 100;
    cols = 100;
    pathVertices = 1000;


    pathGraph = createPathGraph(pathVertices);
    latticeGraph = createLatticeGraph(rows,cols);

    // Call the function and print the adjacent vertices of vertex 0
    for (int i=0;i<pathVertices;i++)
    {
        std::vector<undirectedGraph::vertex_descriptor> adj_vertices = get_adjacent_vertices(pathGraph, i);
        for (auto v : adj_vertices)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}