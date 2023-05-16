/////////////////////////////////////////////////////////////
// Title  : mbqcStarterFile.cpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        : Current implementation can only do square      //
//        : graph repeatedly. Will branch repo to make     //
//        : use different way to create graph by           //
//        : adjacency                                      //
/////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <numeric>
#include <cmath>
#include <random>
#include <QuEST.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/container/vector.hpp>
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphConstructions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/graphs/graphTraversalFlows.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/generalAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/testFunctions/graphAssertFunctions.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/genericHelperFunctions/writeGraphGraphVizDotFile.hpp"
#include "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/src/quantumGraphs/flowMeasurements.hpp"

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
  
  
  numRows = 3;
  numCols = 6;
  
  

  // Create graph (lattice in this case)
  latticeGraph = createLatticeGraph(numRows,numCols);

  std::cout << "The graph has adjacency list:" << std::endl;
  
  print_graph(latticeGraph);
  std::cout << std::endl;
  std::cout << std::endl;
  // Print graph to file
  std::string fileDir = "/home/fieldofnodes/Projects/QuEST/QuEST/projects/MBQC/figs";
  std::string graphName = "lattice2DGraph";
  std::string format = "png";
  printGraphToFile(latticeGraph,fileDir,graphName,format);

  //numVertices = boost::num_vertices(graph);
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

  
  std::cout << "Vertex being measured: ";
  // iterate over graph
  std::vector<int> measuredQubitsOutcomes;
  undirectedGraph::vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = boost::vertices(latticeGraph); vi != vi_end; vi++) {
      // skip vertices that are in the first column
      std::cout << *vi << " ";
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

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Measured outcome vector has " << measuredQubitsOutcomes.size() << " qubits."  << std::endl; 
  std::cout << "The measurements are: ";
  for(int i:measuredQubitsOutcomes){
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;


std::cout << "Measured outcome lattice: " << std::endl;
  std::vector<std::vector<int>> latticeOutcomes = 
    returnMeasQubitOutcomesLattice(measuredQubitsOutcomes,numRows,numCols);

  for (const auto& row : latticeOutcomes) {
            for (int number : row) {
                std::cout << number << ' ';
            }
            std::cout << '\n';
        }



  // Random number
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Random numbers: " << std::endl;
  // Create a random number generator engine
  std::random_device rd;                   // Obtain a random seed from the hardware
  std::mt19937 generator(rd());             // Standard mersenne_twister_engine seeded with rd

  // Define the range for the random integer
  int min = 0;
  int max = 7;

  // Create a uniform distribution for the range
  std::uniform_int_distribution<int> distribution(min, max);

  // Generate a random integer
  std::vector<int> randomNumeratorVector(numVertices);
  for (int i = 0; i < numVertices-1; i++){
    int randomInt = distribution(generator);
    randomNumeratorVector.push_back(randomInt);
  }

  

  // Print the random integer
  std::cout << "Random integer: ";
  for(auto i: randomNumeratorVector){
    std::cout << i <<  " ";
  }
  std::cout << std::endl;

  int total = std::accumulate(randomNumeratorVector.begin(), randomNumeratorVector.end(), 0);
  int totalMod8 = (total % 8);
  std::cout << "Total value of from random vector = " << total << std::endl;
  std::cout << "Total mod 8 = " << totalMod8 << std::endl;
  std::cout << "Total both values mod 8 = " << ((total+totalMod8) % 8) << std::endl;


  // unload QuEST
  destroyQureg(qureg, env); 
  destroyQuESTEnv(env);
  return 0;
}




