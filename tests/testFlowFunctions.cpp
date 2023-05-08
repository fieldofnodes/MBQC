/////////////////////////////////////////////////////////////
// Title  : testGraphProperties.cpp                        //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Build graphs and test properties of graphs.    //
//        : As graph types grow in number, separate tests  //
//        : across multiple files                          //
/////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <QuEST.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"

using namespace boost;

typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;









// Quick and dirty angle computation in 2D lattice when using all possible values
// on the Z correction
qreal correctionOutcomesForExampleNotPerm(std::vector<int> outcomeVector,qreal inputAngle){
    qreal expectedCorrectedAngle;
    expectedCorrectedAngle = (pow((-1),outcomeVector[6])*inputAngle) + M_PI*(outcomeVector[1]+outcomeVector[5]+outcomeVector[7]);

    return expectedCorrectedAngle;
}


int main(){
    
    int numRows = 5;
    int numCols = 5;
    int expectedTotalVertices;
    int boostCallTotalVertices;

    undirectedGraph latticeGraph;
    
    

    latticeGraph = createLatticeGraph(numRows, numCols);
    expectedTotalVertices = numRows*numCols;
    boostCallTotalVertices = boost::num_vertices(latticeGraph);

    
    // Print graph to file
    std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
    std::string graphName = "lattice2DGraph";
    std::string format = "png";
    printGraphToFile(latticeGraph,fileDir,graphName,format);


    // Assert each vertex (forward and backward flow) give 
    // as expectd by internal computation of function
    assertFlowFunctionsPerformExpected(latticeGraph,numRows);



    // Test to confirm neighbours are correct
    // Only asserting for a 5x5 graph
    std::vector<std::vector<int>> expectedNeighbourhood = {{1,5},{0,6,2},{1,7,3},{2,8,4},{3,9},{0,6,10},{1,5,7,11},{2,6,8,12},{3,7,9,13},{4,8,14},{5,11,15},{6,10,12,16},{7,11,13,17},{8,12,14,18},{9,13,19},{10,16,20},{11,15,17,21},{12,16,18,22},{13,17,19,23},{14,18,24},{15,21},{16,20,22},{17,21,23},{18,22,24},{19,23}};
    assertNieghbours(latticeGraph,expectedNeighbourhood);
    
    


    // Need to write tests that comfirm the angle updates
    // Select some corner vertices,edge vertices and middle vertices.

    std::vector<int> outcomeVectorZeros(10,0);
    std::vector<int> outcomeVectorOnes(10,1);
    std::vector<int> outcomeVectorOnesAndZeros = {0,1,0,0,0,0,1,0,0,0};
    qreal expectedCorrectedAngleZeros;
    qreal expectedCorrectedAngleOnes;
    qreal expectedCorrectedAngleOnesAndZeros;
    int vertex = 11;
    qreal inputAngle = M_PI / 4.0;
    
    
    // All zero measurement outcomes
    expectedCorrectedAngleZeros = correctionOutcomesForExampleNotPerm(outcomeVectorZeros,inputAngle);
    assertCorrection(latticeGraph,outcomeVectorZeros,vertex,numRows,inputAngle,expectedCorrectedAngleZeros);

    // All one measurement outcomes
    expectedCorrectedAngleOnes = correctionOutcomesForExampleNotPerm(outcomeVectorOnes,inputAngle);
    assertCorrection(latticeGraph,outcomeVectorOnes,vertex,numRows,inputAngle,expectedCorrectedAngleOnes);

    // Some ones and zeros outcomes
    expectedCorrectedAngleOnesAndZeros = correctionOutcomesForExampleNotPerm(outcomeVectorOnesAndZeros,inputAngle);
    assertCorrection(latticeGraph,outcomeVectorOnesAndZeros,vertex,numRows,inputAngle,expectedCorrectedAngleOnesAndZeros);



    
    return 0;
}

