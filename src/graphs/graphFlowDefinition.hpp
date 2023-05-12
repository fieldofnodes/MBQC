#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <functional>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"




// Define a function that takes a graph as a template parameter
template <typename Graph>
void assertFlowFunctionNeighbour(const Graph& g, int v, int numRows, std::function<int(int, int)>flowFunction)
{
    // Call the flow function to get the forward lattice flow
    int fv = flowFunction(v, numRows);
    std::vector<int> neigh = getVertexNeighbours(g,v)
    
    isIntInVector(v, neigh)
    
}


using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;

bool areVerticesConnected(const Graph& g, Graph::vertex_descriptor u, Graph::vertex_descriptor v) {
    auto edge = boost::edge(u, v, g);
    return edge.second; // Returns true if there is an edge between u and v
}



template <typename Graph>
void assertFlowFunctionNeighbourVertex(const Graph& g,int vertex){
    // Assert that for vertex, v, than f(v) is a neighbour
}


void assertFlowFunctionFutureOfVertex(){
    
}


void assertNeighbourFlowFunctionFutureOfVertex(){
    
}



int main()
{
    // Define a graph and add some vertices and edges
    using Graph = boost::adjacency_list<>;
    Graph g(5);
    boost::add_edge(0, 1, g);
    boost::add_edge(1, 2, g);
    boost::add_edge(2, 3, g);

    // Call the assertFlowNeighbour function with the getForwardLatticeFlow function
    assertFlowNeighbour(g, 1, 2, getForwardLatticeFlow);
    // Output: Vertex 3 exists in the graph.

    return 0;
}


