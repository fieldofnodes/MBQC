///////////////////////////////////////////////////////////////
// Filename  : testReadingGraphFromFile.cpp
// Author    : Jonathan Miller
// Date      : 2023-06-28
// Aim       : aim_script
//           : Read a graph in from file.
//           :
///////////////////////////////////////////////////////////////


#include "packages.hpp"


int main() {
    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

    std::ifstream file("/Users/jmille15/Projects/MBQC/graphs_file_io/single_brick_work_state.txt"); // Replace "graph.txt" with your input file path
    if(!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    int numVertices, numEdges;
    file >> numVertices >> numEdges;

    Graph graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int source, target;
        file >> source >> target;
        boost::add_edge(source, target, graph);
    }

    file.close();
 // Print the graph to the screen
    numVertices = boost::num_vertices(graph);
    std::cout << "Graph vertices number:" << numVertices << std::endl;
    
    boost::print_graph(graph);



    return 0;
}