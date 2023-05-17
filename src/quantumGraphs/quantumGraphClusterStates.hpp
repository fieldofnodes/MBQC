/////////////////////////////////////////////////////////////
// Title  : quantumGraphClusterStates.hpp                  //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct cluster and graph states from graph  //
/////////////////////////////////////////////////////////////

//#include <boost/graph/adjacency_list.hpp>

typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;

void entangleGraph(Qureg qureg,
    const undirectedGraph& graph){
    // entangle qureg according to the graph with CZ gates
    edgeIterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
        auto source = boost::source(*ei, graph);
        auto target = boost::target(*ei, graph);
        controlledPhaseFlip (qureg,source,target);
    }

 
}