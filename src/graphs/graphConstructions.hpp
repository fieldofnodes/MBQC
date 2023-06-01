/////////////////////////////////////////////////////////////
// Title  : graphConstructions.hpp                         //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct graphs                               //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////

typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;


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


/*
  create a 2D lattice graph with n rows, m columns and nxm vertices

undirectedGraph createLatticeGraph(int n, int m) { 
  undirectedGraph g(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < m-1) add_edge(i*m+j, i*m+j+1, g); // add horizontal edges
      if (i < n-1) add_edge(i*m+j, (i+1)*m+j, g); // add vertical edges
    }
  }

  return g;
}
*/
  
undirectedGraph createLatticeGraph(int numRows, int numCols) { 
    std::vector<std::vector<int>>lattice = create_lattice(numRows,numCols);
    int numVertices = numRows * numCols;
    // Create a Boost Graph
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

