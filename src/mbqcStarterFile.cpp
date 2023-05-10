/////////////////////////////////////////////////////////////
// Title  : mbqcStarterFile.cpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        :                                                //
//        :                                                //
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
typedef boost::graph_traits<undirectedGraph>::edge_iterator edgeIterator;
typedef boost::graph_traits<undirectedGraph>::vertex_iterator vertexIterator;

// Set up the main function
int main() {
  // create graph - lets do a lattice graph
  int numRows;
  int numCols;
  int numVertices;
  
  undirectedGraph latticeGraph;
  
  numRows = 1;
  numCols = 5;
  
  // Create graph (lattice in this case)
  latticeGraph = createLatticeGraph(numRows,numCols);



  // Print graph to file
  std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
  std::string graphName = "lattice2DGraph";
  std::string format = "png";
  printGraphToFile(latticeGraph,fileDir,graphName,format);


  numVertices = boost::num_vertices(latticeGraph);
  
  // angle list
  // For initialise all to 0
  std::vector<qreal> qubitAngles(numVertices,0.0); // input angles in  = {a1,a2,a3,...,an}
  
  int numEdges;

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  

  // set number of qubits
  int numQubits = numVertices;
  
  // create a quantum register
  Qureg qureg = createQureg(numQubits, env);
  
  // initialise in the plus state
  initPlusState(qureg);

  // entangle qureg according to the graph with CZ gates
  edgeIterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(latticeGraph); ei != ei_end; ++ei) {
      auto source = boost::source(*ei, latticeGraph);
      auto target = boost::target(*ei, latticeGraph);
      controlledPhaseFlip (qureg,source,target);
  }

  
  
  // iterate over graph
  std::vector<int> measuredQubitsOutcomes;
  undirectedGraph::vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = boost::vertices(latticeGraph); vi != vi_end; ++vi) {
      // skip vertices that are in the first column
      if(*vi < numRows){
        rotateZ(qureg,*vi, (-1)*qubitAngles[*vi]);
        hadamard(qureg,*vi);
        int m = measure(qureg,*vi);
        measuredQubitsOutcomes.push_back(m);
      }else if(*vi >= numRows){
        qreal correctedAngle;
        correctedAngle = computeCorrectedAngle(latticeGraph,measuredQubitsOutcomes,*vi,numRows,qubitAngles[*vi]);
        rotateZ(qureg,*vi, (-1)*correctedAngle);
        hadamard(qureg,*vi);
        int m = measure(qureg,*vi);
        measuredQubitsOutcomes.push_back(m);
      } else {
        std::cout << "attempting to measure nothing?";
      }
  }

  std::cout << "Measured outcome vector is " << measuredQubitsOutcomes.size() << " and the measurements are: ";
  for(int i:measuredQubitsOutcomes){
    std::cout << i << " ";
  }
  std::cout << std::endl;



  // unload QuEST
  destroyQureg(qureg, env); 
  destroyQuESTEnv(env);
  return 0;
}




