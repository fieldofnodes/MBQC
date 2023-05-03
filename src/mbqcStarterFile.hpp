// Make sure QuEST.h is included 
#include <QuEST.h>

// same for vector
#include <vector>

// include all needed boost libraries 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
using G = boost::adjacency_list<>; // generic boost graph

// avoids usint std:: for everything under std
using namespace std

// Set up the main function
int main() {
  // create graph
  // needs type of graph
  // compute number of vertices
  int numVertices;
  // compute number of edges
  int numEdges;

  // load QuEST environment
  QuESTEnv env = createQuESTEnv();
  

  // set number of qubits
  int numQubits = numVertices;
  
  // create a quantum register
  Qureg qubits = createQureg(numQubits, env);
  
  // initialise in the plus state
  initPlusState(qubits);

  // if non vanilla MBQC add angle
  // angle list
  vector<qreal> qubitAngles;// input angles in  = {a1,a2,a3,...,an}

  // apply phase shift with corresponding angle to qubit
  for(int qubitIter=0; qubitIter<numQubits; qubitIter++){
    phaseShift (qureg,qubitIter,qubitAngles[qubitIter]);   
  }

  // traverse graph to entangle circuit according to neighbours of 
  // each qubit is connected to its neighbour with CZ gate
  // controlledPhaseFlip (qureg,idQubit1,idQubit2)
  
  // apply flow to measure qubits according to neighbours
  // and flow
  // store qubit is appropriate container
  // vector/matrix -> pure/mix states

  // unload QuEST
  destroyQureg(qubits, env); 
  destroyQuESTEnv(env);
  return 0;
}



