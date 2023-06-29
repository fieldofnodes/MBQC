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
#include <boost/graph/boyer_myrvold_planar_test.hpp> ///< Provides the Boyer-Myrvold planarity testing algorithm.
#include <boost/graph/connected_components.hpp> ///< Provides functions for computing connected components in a graph.
#include <boost/graph/make_connected.hpp>     ///< Provides functions for making a graph connected.
#include <boost/graph/make_biconnected_planar.hpp>   ///< Provides functions for making a graph biconnected and planar.
#include <boost/graph/make_maximal_planar.hpp>       ///< Provides functions for making a graph maximal planar.
#include <boost/graph/planar_face_traversal.hpp>     ///< Provides functions for traversing the faces of a planar graph.



using namespace boost;



/**
 * @typedef undirectedGraph
 * @brief Alias for an undirected graph using boost::adjacency_list.
 *
 * This typedef represents an undirected graph using the boost::adjacency_list
 * data structure with boost::vecS as the vertex container, boost::vecS as the edge
 * container, and boost::undirectedS as the graph type. It includes additional
 * properties for vertex and edge indices, specified by property<vertex_index_t, int>
 * and property<edge_index_t, int> respectively. It provides an interface for creating
 * and manipulating undirected graphs.
 */
using undirectedGraph = boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    boost::property<boost::vertex_index_t, int>,
    boost::property<boost::edge_index_t, int>
>;


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
 * @typedef edgeDescriptor
 * @brief Descriptor for an edge in an undirected graph.
 *
 * This typedef represents a descriptor for an edge in an undirected graph.
 * It is used to reference and manipulate individual edges in an undirectedGraph.
 *
 * @note The edgeDescriptor type is defined as a std::vector<graph_traits<undirectedGraph>::edge_descriptor>.
 */
typedef std::vector<graph_traits<undirectedGraph>::edge_descriptor> edgeDescriptor;



/**
 * @typedef vertexIterator
 * @brief Iterator for traversing vertices in an undirected graph.
 *
 * This typedef represents an iterator for traversing vertices in an undirected graph.
 * It is used to iterate over the vertices of an undirectedGraph. You can use it in
 * conjunction with boost::vertices() to traverse and operate on the vertices of the graph.
 */
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;





/**
 * @struct face_counter
 * @brief Visitor for counting the number of faces during planar face traversal.
 *
 * This struct represents a visitor that is used with planar_face_traversal to count
 * the number of faces in a graph. It inherits from planar_face_traversal_visitor.
 * The begin_face() function is overridden to increment the face count.
 *
 * @note The face_counter struct is used in the context of planar face traversal.
 */
struct face_counter : public planar_face_traversal_visitor
{
  /**
   * @brief Default constructor for face_counter.
   */
  face_counter() : count(0) {}

  /**
   * @brief Function called at the beginning of each face.
   * It increments the face count.
   */
  void begin_face() { ++count; }

  int count; ///< The count of faces.
};





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
