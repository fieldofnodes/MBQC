// packages.hpp

#ifndef PACKAGES_HPP
#define PACKAGES_HPP



// Standard libraries
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <random>
#include <filesystem>
#include <functional>
#include "config.h"
#include <fstream>
#include <cstdio>
#include <string>
#include <ranges>
#include <cstdlib>

// QuEST
#include <QuEST.h>

// Boost
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>



// Helper functions
#include "generalHelperFunctions.hpp"
#include "writeGraphGraphVizDotFile.hpp"

// Graph functions
#include "graphConstructions.hpp"
#include "graphTraversalFlows.hpp"

// Quantum functions
#include "flowMeasurements.hpp"
#include "angleConstruction.hpp"
#include "quantumGraphClusterStates.hpp"

// Assert functions
#include "generalAssertFunctions.hpp"
#include "graphAssertFunctions.hpp"

using namespace boost;

// Define the typedefs
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;


#endif // PACKAGES_HPP
