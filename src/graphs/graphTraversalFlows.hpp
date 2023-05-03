/////////////////////////////////////////////////////////////
// Title  : graphTraversalFlows.hpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct graphs                               //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <boost/container/vector.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>




using namespace boost;


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;




