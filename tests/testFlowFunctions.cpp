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
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"
using namespace boost;

typedef boost::adjacency_list<boost::vecS, boost::vecS,boost::undirectedS> undirectedGraph;
typedef boost::graph_traits<undirectedGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertex_iterator;




int getLattice2DFutureVertex(int presentVertex, int numRows){
    // For a 2D lattice graph 
    // (1)-(4)-(7)
    // (2)-(5)-(8)
    // (3)-(6)-(9)
    // a flow function for vertex 5
    // has future vertex 8
    // f(i) = i + r, r is numRows
    int futureVertex = presentVertex + numRows;
    
    return futureVertex;
}

int getLattice2DPastVertex(int presentVertex, int numRows){
    // For a 2D lattice graph 
    // (1)-(4)-(7)
    // (2)-(5)-(8)
    // (3)-(6)-(9)
    // a flow function for vertex 5
    // has past vertex 2
    // f(i) = i - r, r is numRows
    int pastVertex = presentVertex - numRows;
    
    return pastVertex;
}

std::vector<int> getVertexNeighbours(const undirectedGraph& graph,int vertex){
    // Choose a vertex to find its adjacent vertices
    undirectedGraph::vertex_descriptor v = vertex;
    // Find the range of adjacent vertices
    typedef boost::graph_traits<undirectedGraph>::adjacency_iterator adjacency_iterator;
    std::pair<adjacency_iterator, adjacency_iterator> neighbors = adjacent_vertices(v, graph);

    std::vector<int> neighbourVector;
    
    for (adjacency_iterator it = neighbors.first; it != neighbors.second; ++it) {
        neighbourVector.push_back(*it);
    }
    return neighbourVector;
}

int getLattice2DFutureVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    int size_graph = boost::num_vertices(graph);
    assert("The vertex inputted needs to be less than the number of vertices - the number of the rows, but it is not" && vertex < (size_graph - numRows));
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int futureVertex = getLattice2DFutureVertex(vertex,numRows);
    auto it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), futureVertex);
    assert(("flow function produced a vertex not in the input v neighbourhodd" && it != vertexNeighbours.end()));
    
    return futureVertex;
}

int getLattice2DPastVertexGraph(const undirectedGraph& graph,int vertex,int numRows){
    assert(("The inputted vertex needs to be greater than or equal to the number of rows." && vertex >= numRows));
    std::vector<int> vertexNeighbours = getVertexNeighbours(graph,vertex);
    int pastVertex = getLattice2DPastVertex(vertex,numRows);
    std::vector<int>::iterator it = std::find(vertexNeighbours.begin(), vertexNeighbours.end(), pastVertex);
    assert(("flow function produced a vertex not in the input vertex neighbourhodd" && it != vertexNeighbours.end()));
    return pastVertex;
}

qreal getVerticesForCorrections(
    const undirectedGraph& graph,
    std::vector<int> measuredOutcomes, 
    int vertex,
    int numRows, 
    qreal angle){

    std::vector<int> neighbourhood = getVertexNeighbours(graph,vertex);
    int xCorrectionVertex;
    std::vector<int> zCorrectionVertices;
    qreal updatedAngle;

    if (vertex < numRows){ // First column - no x correction no z correction
        updatedAngle = angle;
    } else if (vertex >= numRows){ // ensure we are in second column
        xCorrectionVertex = getLattice2DPastVertexGraph(graph,vertex,numRows);
        for (int i: neighbourhood){
            int past;
            if(i >= numRows){
                past = getLattice2DPastVertexGraph(graph,i,numRows);
            } else{
                continue;
            }
            zCorrectionVertices.push_back(past);
        }        

        // Remove vertex in neigbourhood if it is the vertrex
        // we want to measure
        zCorrectionVertices.erase(
                std::remove(
                    zCorrectionVertices.begin(), 
                    zCorrectionVertices.end(), vertex), 
                zCorrectionVertices.end());
        
        int exponent = measuredOutcomes[xCorrectionVertex];
        
        //std::cout << "f-1(j): " << xCorrectionVertex << std::endl;
        //std::cout << "s_f-1(j): " << exponent << std::endl;
        qreal xAngle = std::pow((-1), exponent)*angle;

        std::vector<int> outcomesForZ;
        for (int i:zCorrectionVertices){
            outcomesForZ.push_back(measuredOutcomes[i]);
        }

        int sum = std::accumulate(outcomesForZ.begin(), outcomesForZ.end(), 0);
        qreal zAngle = M_PI*sum;
        updatedAngle = xAngle + zAngle;

        }

        return updatedAngle;
        
}


int main(){
    int presentVertex = 19;
    int numRows = 5;
    int numCols = 5;
    int totalVertices;
    int computedFutureVertex;
    int computedPastVertex;
    int expectedFutureVertex = presentVertex + numRows;
    int expectedPastVertex = presentVertex - numRows;
    

    undirectedGraph latticeGraph;
    
    totalVertices = numRows*numCols;




    computedFutureVertex = getLattice2DFutureVertex(presentVertex,numRows);
    computedPastVertex = getLattice2DPastVertex(presentVertex,numRows);
    assert(("Computed future vertex does not match expected" && computedFutureVertex == expectedFutureVertex));
    assert(("Computed past vertex does not match expected" && computedPastVertex == expectedPastVertex));



    latticeGraph = createLatticeGraph(numRows, numCols);
    std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
    std::string graphName = "lattice2DGraph";
    std::string format = "png";
    printGraphToFile(latticeGraph,fileDir,graphName,format);


    int graphFutureVertex = getLattice2DFutureVertexGraph(latticeGraph,presentVertex,numRows);
    int graphPastVertex = getLattice2DPastVertexGraph(latticeGraph,presentVertex,numRows);

    assert(("Flow forward vertex based on graph does not match expected" && graphFutureVertex==expectedFutureVertex));
    assert(("Flow backward vertex based on graph does not match expected" && graphPastVertex==expectedPastVertex));


    // Need to write tests that comfirm the angle updates
    // Select some corner vertices,edge vertices and middle vertices.
    std::vector<int> fakeResults = {0,1,0,0,0,0};
    int vertex = 6;
    qreal angle = M_PI;
    qreal newAngle = getVerticesForCorrections(
        latticeGraph,
        fakeResults, 
        vertex,
        numRows,
        angle);
    
    assert(("New angle and original angle do not match" && newAngle == (-1)*angle));

    std::cout << newAngle << std::endl;

    /*

    // current vertex to be measured
    int currentVertexToMeasure = 9;
    
    // get vertex for X correction
    int graphPastVertexXCorrection = getLattice2DPastVertexGraph(latticeGraph,currentVertexToMeasure,numRows);
    std::cout << "Vertex needed for X correction: " << graphPastVertexXCorrection << std::endl;



    // get vertex for Z correction
    std::vector<int> pastVerticesZCorrection;
    std::vector<int> graphVertexZCorrectionNeighs = getVertexNeighbours(latticeGraph,currentVertexToMeasure);

    std::cout << "Neighbours of vertex " << currentVertexToMeasure << " : " << std::endl;
    for (int i: graphVertexZCorrectionNeighs){
        int past;
        if(i >= numRows){
            past = getLattice2DPastVertexGraph(latticeGraph,i,numRows);
        } else{
            continue;
        }
        pastVerticesZCorrection.push_back(past);        

        std::cout << "current vertex: " << i << " has past vertex :" << past << " " << std::endl;

        // need to remove past vertex that is the same as current vertrex -- as that is x correction
        // need to remove future non measured vertices
    }
    std::cout << std::endl;

    
    pastVerticesZCorrection.erase(
        std::remove(
            pastVerticesZCorrection.begin(), 
            pastVerticesZCorrection.end(), currentVertexToMeasure), 
        pastVerticesZCorrection.end());
    
    
    for (int n : pastVerticesZCorrection) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
*/
    return 0;
}

