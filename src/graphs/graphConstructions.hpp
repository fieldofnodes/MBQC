/////////////////////////////////////////////////////////////
// Title  : graphConstructions.hpp                         //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct graphs                               //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////






/**
 * @brief Creates a lattice graph from two integers
 *
 * This function takes two integers as parameters and returns a littice graph with them as parameters
 *
 * @param numRows The number of rows.
 * @param numCols The number of columns.
 * @return A lattice graph.
 */
std::vector<std::vector<int>> create_lattice(int numRows, int numCols) {
    int numVertices = numRows * numCols;
    std::vector<std::vector<int>> lattice(numRows, std::vector<int>(numCols, -1));
    std::vector<int> numbers(numVertices);
    for (int i = 0; i < numVertices; i++) {
        numbers[i] = i;
    }

    for (int number : numbers) {
        int row = number % numRows;
        int col = number / numRows;
        lattice[row][col] = number;
    }

    return lattice;
}


/**
 * @brief Creates an undirected lattice graph with the specified number of rows and columns.
 *
 * This function creates an undirected lattice graph based on the given number of rows and columns.
 * It uses the create_lattice function to generate the lattice structure and then constructs a
 * corresponding Boost Graph using the undirectedGraph typedef.
 * 
 * 
 * @param numRows The number of rows in the lattice graph.
 * @param numCols The number of columns in the lattice graph.
 * @return The created undirected lattice graph represented by an undirectedGraph.
 */
undirectedGraph createLatticeGraph(int numRows, int numCols) { 
    std::vector<std::vector<int>> lattice = create_lattice(numRows, numCols);
    int numVertices = numRows * numCols;
    undirectedGraph latticeGraph(numVertices);
    
    // Add edges to the graph
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (row + 1 < numRows) {
                boost::add_edge(lattice[row][col], lattice[row + 1][col], latticeGraph);
            }
            if (col + 1 < numCols) {
                boost::add_edge(lattice[row][col], lattice[row][col + 1], latticeGraph);
            }
        }
    }

    return latticeGraph;
}


/**
 * Creates an undirected graph from a file.
 *
 * @param filePath The path to the input file.
 * @return The created undirected graph.
 */
undirectedGraph createGraphFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
    }

    int numVertices, numEdges;
    file >> numVertices >> numEdges;

    undirectedGraph graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int source, target;
        file >> source >> target;
        boost::add_edge(source, target, graph);
    }

    file.close();

    return graph;
}





/**
 * @brief Create a complete graph on N vertices.
 *
 * @param numVertices The number of vertices in the complete graph.
 * @return The created complete graph.
 */
undirectedGraph createCompleteGraph(int numVertices) {
    undirectedGraph graph(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            boost::add_edge(i, j, graph);
        }
    }

    return graph;
}



/**
 * @brief Generate a random graph with a specified number of vertices and edges.
 *
 * @param numVertices The number of vertices in the graph.
 * @param numEdges The number of edges in the graph.
 * @return The generated random graph.
 */
undirectedGraph generateRandomGraph(int numVertices, int numEdges) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numVertices - 1);

    undirectedGraph graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int source = dis(gen);
        int target = dis(gen);

        boost::add_edge(source, target, graph);
    }

    return graph;
}




/**
 * @brief Generate a complete bipartite graph with n vertices on one side and m vertices on the other side.
 *
 * @param n The number of vertices on one side.
 * @param m The number of vertices on the other side.
 * @return The generated complete bipartite graph.
 */
undirectedGraph generateCompleteBipartiteGraph(int n, int m) {
    undirectedGraph graph(n + m);

    for (int i = 0; i < n; ++i) {
        for (int j = n; j < n + m; ++j) {
            boost::add_edge(i, j, graph);
        }
    }

    return graph;
}


/**
 * @brief Generate a complete multipartite graph with given partitions.
 *
 * @param partitions The number of vertices in each partition.
 * @return The generated complete multipartite graph.
 */
undirectedGraph createCompleteMultipartiteGraph(const std::vector<int>& partitions) {
    int numPartitions = partitions.size();
    int numVertices = 0;
    for (int partitionSize : partitions) {
        numVertices += partitionSize;
    }

    undirectedGraph graph(numVertices);

    int vertexOffset = 0;
    for (int partitionSize : partitions) {
        for (int i = vertexOffset; i < vertexOffset + partitionSize; ++i) {
            for (int j = vertexOffset + partitionSize; j < numVertices; ++j) {
                boost::add_edge(i, j, graph);
            }
        }
        vertexOffset += partitionSize;
    }

    return graph;
}

