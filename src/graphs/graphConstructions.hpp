/////////////////////////////////////////////////////////////
// Title  : graphConstructions.hpp                         //
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


typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> UndirectedGraph;
typedef boost::graph_traits<UndirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<UndirectedGraph>::vertex_iterator vertex_iterator;




/*
  create a 2D lattice graph with n rows, m columns and nxm vertices
*/
UndirectedGraph createLatticeGraph(int n, int m) { 
  UndirectedGraph g(n * m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j < m-1) add_edge(i*m+j, i*m+j+1, g); // add horizontal edges
      if (i < n-1) add_edge(i*m+j, (i+1)*m+j, g); // add vertical edges
    }
  }

  return g;
}



