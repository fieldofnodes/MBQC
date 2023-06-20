/**
 * @file packages.hpp
 * @brief Contains the inclusion of various packages and libraries used in the project.
 */

#ifndef PACKAGES_HPP
#define PACKAGES_HPP

// Standard libraries
#include <iostream> ///< Provides basic input/output functionality.
#include <algorithm> ///< Provides a collection of algorithms.
#include <iterator> ///< Provides iterator-related functionality.
#include <vector> ///< Provides a dynamic array-like container.
#include <set> ///< Provides a container that stores unique elements.
#include <numeric> ///< Provides numeric algorithms and operations.
#include <cmath> ///< Provides mathematical functions.
#include <random> ///< Provides random number generation.
#include <filesystem> ///< Provides facilities to manipulate files and directories.
#include <functional> ///< Provides function objects and related functionality.
#include "config.h" ///< Provides configuration settings.
#include <fstream> ///< Provides file stream operations.
#include <cstdio> ///< Provides C-style input/output operations.
#include <string> ///< Provides string manipulation functionality.
#include <ranges> ///< Provides range-based operations.
#include <cstdlib> ///< Provides general purpose functions.
#include <functional> ///< Provides general purpose function objects.
#include <cxxabi.h> ///< Provides support for C++ name demangling.

// QuEST
#include <QuEST.h> ///< Provides the Quantum Exact Simulation Toolkit.

// Boost
#include <boost/graph/adjacency_list.hpp> ///< Provides a generic graph data structure.
#include <boost/graph/grid_graph.hpp> ///< Provides grid graphs.
#include <boost/graph/graphviz.hpp> ///< Provides graph visualization functionality.
#include <boost/array.hpp> ///< Provides fixed-size arrays.
#include <boost/graph/graph_utility.hpp> ///< Provides graph utility functions.
#include <boost/container/vector.hpp> ///< Provides a vector container.
#include <boost/range/algorithm/unique.hpp> ///< Provides range algorithms for uniqueness.
#include <boost/range/algorithm.hpp> ///< Provides various range algorithms.
#include <boost/range/adaptor/filtered.hpp> ///< Provides range adaptors for filtering.
#include <boost/range/adaptor/transformed.hpp> ///< Provides range adaptors for transformation.


using namespace boost;


/**
 * @typedef undirectedGraph
 * @brief Alias for an undirected graph using boost::adjacency_list.
 *
 * This typedef represents an undirected graph using the boost::adjacency_list
 * data structure with boost::vecS as the vertex container and boost::undirectedS
 * as the graph type. It provides an interface for creating and manipulating
 * undirected graphs.
 */
using undirectedGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

/**
 * @typedef edgeIterator
 * @brief Iterator for traversing edges in an undirected graph.
 *
 * This typedef represents an iterator for traversing edges in an undirected graph.
 * It is used to iterate over the edges of an undirectedGraph. You can use it in
 * conjunction with boost::edges() to traverse and operate on the edges of the graph.
 */
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;

/**
 * @typedef vertexIterator
 * @brief Iterator for traversing vertices in an undirected graph.
 *
 * This typedef represents an iterator for traversing vertices in an undirected graph.
 * It is used to iterate over the vertices of an undirectedGraph. You can use it in
 * conjunction with boost::vertices() to traverse and operate on the vertices of the graph.
 */
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;





// Helper functions
#include "generalHelperFunctions.hpp" ///< Provides general helper functions.
#include "writeGraphGraphVizDotFile.hpp" ///< Provides functions to write graph as Graphviz DOT file.

// Graph functions
#include "graphConstructions.hpp" ///< Provides graph construction functions.
#include "graphTraversalFlows.hpp" ///< Provides graph traversal and flow functions.

// Quantum functions
#include "flowMeasurements.hpp" ///< Provides functions for flow measurements.
#include "angleConstruction.hpp" ///< Provides functions for angle construction.
#include "quantumGraphClusterStates.hpp" ///< Provides functions for quantum graph cluster states.

// Assert functions
#include "generalAssertFunctions.hpp" ///< Provides general assertion functions.
#include "graphAssertFunctions.hpp" ///< Provides graph-specific assertion functions.
#include "probabilitiesAmplitudesNoNoiseCircuits.hpp" ///< Provides functions for probabilities and amplitudes without noise circuits.
#include "probabilitiesAmplitudesDampingCircuits.hpp" ///< Provides functions for probabilities and amplitudes with damping circuits.


#endif // PACKAGES_HPP
