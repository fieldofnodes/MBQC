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
    
    // From a file
    std::string brickwork_graph = "/Users/jmille15/Projects/MBQC/graphs_file_io/single_brick_work_state.txt";
    undirectedGraph graph = createGraphFromFile(brickwork_graph);
    boost::print_graph(graph);

    // Print graph to file
    // Update with desired directory to view graph.
    std::string figsDir = MBQC_FIGS_DIR;
    std::string graphName = "GraphGeneratedFromFile";
    std::string format = PNG_FORMAT;
    printGraphToFile(graph,figsDir,graphName,format);
    

    return 0;
}