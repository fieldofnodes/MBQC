/////////////////////////////////////////////////////////////
// Title  : mbqcStarterFile.cpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        :                                                //
//        :                                                //
/////////////////////////////////////////////////////////////

#include <QuEST.h>
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
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;

// Set up the main function
int main() {
  // create graph - lets do a lattice graph
  int rows;
  int cols;
  int numVertices;
  
  undirectedGraph latticeGraph;
  
  rows = 5;
  cols = 5;
  numVertices = rows*cols;
    
  latticeGraph = createLatticeGraph(rows,cols);
  
  // angle list
  //std::vector<qreal> qubitAngles; // input angles in  = {a1,a2,a3,...,an}
  
  int numEdges;

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  

  // set number of qubits
  int numQubits = numVertices;
  
  // create a quantum register
  Qureg qureg = createQureg(numQubits, env);
  
  // initialise in the plus state
  initPlusState(qureg);

  // if non vanilla MBQC add angle
  // apply phase shift with corresponding angle to qubit
  //for(int qubitIter=0; qubitIter<numQubits; qubitIter++){
  //  phaseShift (qureg,qubitIter,qubitAngles[qubitIter]);   
  //}

  // traverse graph to entangle circuit according to neighbours of 
  // each qubit is connected to its neighbour with CZ gate


  edgeIterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(latticeGraph); ei != ei_end; ++ei) {
      auto source = boost::source(*ei, latticeGraph);
      auto target = boost::target(*ei, latticeGraph);
      controlledPhaseFlip (qureg,source,target);
  }

  
  
  
  // 
  
  // apply flow to measure qubits according to neighbours
  // and flow
  // store qubit is appropriate container
  // vector/matrix -> pure/mix states

  // unload QuEST
  destroyQureg(qureg, env); 
  destroyQuESTEnv(env);
  return 0;
}



