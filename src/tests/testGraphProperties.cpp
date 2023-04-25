/*
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> Graph;

int main() {
    Graph g;
    boost::add_vertex(g); // Add a vertex with ID 0
    boost::add_vertex(g); // Add a vertex with ID 1
    boost::add_vertex(g); // Add a vertex with ID 2
    boost::add_edge(0, 1, g); // Add an edge between vertices 0 and 1
    boost::add_edge(1, 2, g); // Add an edge between vertices 1 and 2
    
    Graph::vertex_descriptor v = boost::vertex(1, g); // Get vertex descriptor for vertex with ID 1
    
    std::cout << "Number of edges connected to vertex " << v << ": " << boost::degree(v, g) << std::endl;
    
    return 0;
}


*/
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/container/vector.hpp>
#include <vector>
#include <numeric>
#include <algorithm>
#include "createGraph.hpp"
using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<UndirectedGraph>::vertex_iterator vertex_iterator;



int main(){
    int rows;
    int cols;
    int totalVertices;
    
    UndirectedGraph pathGraph;
    UndirectedGraph latticeGraph;
    
    rows = 10;
    cols = 10;
    totalVertices = rows*cols;
    


    
    pathGraph = createLatticeGraph(1,cols);
    latticeGraph = createLatticeGraph(rows,cols);

    
    // Call the function and print the adjacent vertices of vertex 0
    boost::container::vector<int> degree_vector;
    for (int i=0;i<cols;i++)
    {
        // Get the adjacent vertices of vertex i
        UndirectedGraph::vertex_descriptor v = boost::vertex(i, pathGraph);
        auto adjacent_vertices = boost::adjacent_vertices(v, pathGraph);
        
        std::cout << std::endl;
        int deg = boost::degree(v, pathGraph);
        degree_vector.push_back(deg);        

        // Print the adjacent vertices
        std::cout << "Adjacent vertices of vertex " << v << ": ";
        for (auto it = adjacent_vertices.first; it != adjacent_vertices.second; ++it) {
            std::cout << *it << " ";
        }
        std::cout <<  "and has " << deg << " neighbours";
    }
    std::cout << std::endl;

    // Test that the total degree is equivalent to 
    // 2 times the number of edges
    assertHandShakeLemma(pathGraph);
    assertHandShakeLemma(pathGraph);
    assertHandShakeLemma(latticeGraph);


    // Test minimum and maximum degree of a path graph is
    // 1 and 2 respectively 
    assertPathGraphMinMaxDegrees(pathGraph);
    assertDegreeSetLatticeGraph(latticeGraph);

    // Assert the number of vertices in the graph
    // equal the inputted number
    assertGraphNumVertices(pathGraph,cols);
    assertGraphNumVertices(latticeGraph,totalVertices);
    
    

    return 0;
}
