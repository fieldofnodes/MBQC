///////////////////////////////////////////////////////////////
// Filename  : testGeneralGraphConstructions.cpp
// Author    : Jonathan Miller
// Date      : 2023-06-29
// Aim       : Scripts and functioms to generate a
//           : variety of graph
//           : run tests on graph
///////////////////////////////////////////////////////////////



#include "packages.hpp"



int main() {
    
    // From a file
    //std::string brickwork_graph = "/Users/jmille15/Projects/MBQC/graphs_file_io/single_brick_work_state.txt";
    //undirectedGraph graph = createGraphFromFile(brickwork_graph);
    
    // Complete graph
    //int numVertices = 4;
    //int numEdges = 4;
    //undirectedGraph graph = createCompleteGraph(6);
    
    // Random graph
    //undirectedGraph graph = generateRandomGraph(numVertices,numEdges);

    // Bipartite graph
    //int n = 2;
    //int m = 3;
    //undirectedGraph graph = generateCompleteBipartiteGraph(n, m);

    // Multipartite graph
    //std::vector<int> partitions = {1, 1, 1};
    //undirectedGraph graph = createCompleteMultipartiteGraph(partitions);

    

    // Test for Planarity
    /*
    undirectedGraph graph = createCompleteGraph(6);
    if (boyer_myrvold_planarity_test(graph))
        std::cout << "ERROR! K_6 was recognized as planar!" << std::endl;
    else
        std::cout << "K_6 is not planar." << std::endl;
    */

    /*
    Add edges set to a graph to make it connected
    undirectedGraph graph(11);
    add_edge(0,1,graph);
    add_edge(2,3,graph);
    add_edge(3,4,graph);
    add_edge(5,6,graph);
    add_edge(6,7,graph);
    add_edge(8,9,graph);
    add_edge(9,10,graph);
    add_edge(10,8,graph);

    std::vector< graph_traits<undirectedGraph>::vertices_size_type > 
    component(num_vertices(graph));

    std::cout << "Before calling make_connected, the graph has "
            << connected_components(graph, &component[0])
            << " connected components" << std::endl;

    make_connected(graph);

    std::cout << "After calling make_connected, the graph has "
            << connected_components(graph, &component[0])
            << " connected components" << std::endl;

    */

   /*
    Making a graph maximally planar
   
    undirectedGraph graph(10);
    add_edge(0,1,graph);
    add_edge(1,2,graph);
    add_edge(2,3,graph);
    add_edge(3,4,graph);
    add_edge(4,5,graph);
    add_edge(5,6,graph);
    add_edge(6,7,graph);
    add_edge(7,8,graph);
    add_edge(8,9,graph);

    //std::vector<edgeDescriptor> embedding(num_vertices(graph));
   // make_maximal_planar(graph, &embedding[0]);

    std::cout << "Since the input graph is planar with " << num_vertices(graph) 
            << " vertices," << std::endl
            << "The output graph should be planar with " 
            << 3*num_vertices(graph) - 6 << " edges and "
            << 2*num_vertices(graph) - 4 << " faces." << std::endl;

    //Initialize the interior edge index
    property_map<undirectedGraph, edge_index_t>::type e_index = get(edge_index, graph);
    graph_traits<undirectedGraph>::edges_size_type edge_count = 0;
    graph_traits<undirectedGraph>::edge_iterator ei, ei_end;
    for(tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei)
    put(e_index, *ei, edge_count++);


    //Test for planarity; compute the planar embedding as a side-effect
    std::vector<edgeDescriptor> embedding(num_vertices(graph));
    if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = graph,
                                    boyer_myrvold_params::embedding = 
                                        &embedding[0]
                                    )
        )
    std::cout << "Input graph is planar" << std::endl;
    else
    std::cout << "Input graph is not planar" << std::endl;

    make_biconnected_planar(graph, &embedding[0]);

    // Re-initialize the edge index, since we just added a few edges
    edge_count = 0;
    for(tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei)
    put(e_index, *ei, edge_count++);


    //Test for planarity again; compute the planar embedding as a side-effect
    if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = graph,
                                    boyer_myrvold_params::embedding = 
                                        &embedding[0]
                                    )
        )
    std::cout << "After calling make_biconnected, the graph is still planar" 
                << std::endl;
    else
    std::cout << "After calling make_biconnected, the graph is not planar" 
                << std::endl;

    make_maximal_planar(graph, &embedding[0]);


    // Re-initialize the edge index, since we just added a few edges
    edge_count = 0;
    for(tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei)
    put(e_index, *ei, edge_count++);

    // Test for planarity one final time; compute the planar embedding as a 
    // side-effect
    std::cout << "After calling make_maximal_planar, the final graph ";
    if (boyer_myrvold_planarity_test(boyer_myrvold_params::graph = graph,
                                    boyer_myrvold_params::embedding = 
                                        &embedding[0]
                                    )
        )
    std::cout << "is planar." << std::endl;
    else
    std::cout << "is not planar." << std::endl;

    std::cout << "The final graph has " << num_edges(graph) 
            << " edges." << std::endl;

    face_counter count_visitor;
    planar_face_traversal(graph, &embedding[0], count_visitor);
    std::cout << "The final graph has " << count_visitor.count << " faces." 
            << std::endl;



    */

    boost::print_graph(graph);



    // Print graph to file
    // Update with desired directory to view graph.
    /*
    std::string figsDir = MBQC_FIGS_DIR;
    std::string graphName = "CompleteMultiPartiteGraph";
    std::string format = PNG_FORMAT;
    printGraphToFile(graph,figsDir,graphName,format);
    */

    return 0;
}