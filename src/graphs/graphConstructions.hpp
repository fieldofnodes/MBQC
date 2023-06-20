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


