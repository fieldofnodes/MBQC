/////////////////////////////////////////////////////////////
// Title  : prototypeLatticeCreation.cpp                   //
// Author : Jonathan Miller                                //
// Date   : 20230515                                       //
// Aim    : File used to prototype the creation of         //
//        : an arbitrary lattice and presents rows and     //
//        : cols as needed.                                //
/////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <set>
#include <numeric>
#include <cmath>
#include <QuEST.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"


// Define the lattice creation function (same as before)
/*
std::vector<std::vector<int>> create_lattice(int K, int L) {
    int N = K * L;
    std::vector<std::vector<int>> lattice(K, std::vector<int>(L, -1));
    std::vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        numbers[i] = i;
    }

    for (int number : numbers) {
        int row = number % K;
        int col = number / K;
        lattice[row][col] = number;
    }

    return lattice;
}
*/




int main() {
    
    int K = 7;
    int L = 3;
    int N = K*L;

    // Create the lattice using create_lattice function
    std::vector<std::vector<int>> lattice = create_lattice(K, L);

    for (const auto& row : lattice) {
            for (int number : row) {
                std::cout << number << '\t';
            }
            std::cout << '\n';
        }


    // Define the Boost Graph types
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

    // Create a Boost Graph
    Graph graph(N);
    
    // Add edges to the graph
    for (int row = 0; row < K; row++) {
        for (int col = 0; col < L; col++) {
            if (row + 1 < K) {
                boost::add_edge(lattice[row][col], lattice[row + 1][col], graph);
            }
            if (col + 1 < L) {
                boost::add_edge(lattice[row][col], lattice[row][col + 1], graph);
            }
        }
    }

    std::cout << "Num vertices: " << boost::num_vertices(graph) << std::endl;
    std::cout << "Num edges: " << boost::num_edges(graph) << std::endl;
    print_graph(graph);

    // Print graph to file
    std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
    std::string graphName = "lattice2DArrayGraph";
    std::string format = "png";
    printGraphToFile(graph,fileDir,graphName,format);

    return 0;
}
