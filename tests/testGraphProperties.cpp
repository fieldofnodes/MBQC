/////////////////////////////////////////////////////////////
// Title  : testGraphProperties.cpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Build graphs and test properties of graphs.    //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/container/vector.hpp>
#include <vector>
#include <numeric>
#include <algorithm>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"


using namespace boost;

typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;



int main(){
    int rows;
    int cols;
    int totalVertices;
    
    undirectedGraph pathGraph;
    undirectedGraph latticeGraph;
    
    rows = 10;
    cols = 10;
    totalVertices = rows*cols;
    


    
    pathGraph = createLatticeGraph(1,cols);
    latticeGraph = createLatticeGraph(rows,cols);


    // Test that the total degree is equivalent to 
    // 2 times the number of edges
    assertHandShakeLemma(pathGraph);
    assertHandShakeLemma(latticeGraph);


    // Test minimum and maximum degree of a path graph is
    // 1 and 2 respectively 
    assertPathGraphMinMaxDegrees(pathGraph);
    assertDegreeSetLatticeGraph(latticeGraph);

    // Assert the number of vertices in the graph
    // equal the inputted number
    assertGraphNumVertices(pathGraph,cols);
    assertGraphNumVertices(latticeGraph,totalVertices);
    
    

    return 0;
}
