<img src="https://user-images.githubusercontent.com/19248072/225727493-def23a0b-96e3-4310-aa9b-5f27fb0c6f2a.png"  width="300" height="200">


# Measurement Based Quantum Computation  

## Quick and dirty file run in QuEST library

```
cmake .. -DUSER_SOURCE="QuEST/projects/MBQC/src/mbqcStarterFile.cpp" -DOUTPUT_EXE="mbqcStarterFile" && make && ./mbqcStarterFile
```


template <std::size_t Dimensions,
          typename VertexIndex = std::size_t,
          typename EdgeIndex = VertexIndex>
  class grid_graph;

**This code is ran inside of [QuEST](https://quest.qtechtheory.org/download/). Documentation to follow in future for implementation.**

## Ideas for codebase folder structure
In implementation an MBQC scheme requires the usage of tools from graph theory. Consider the folder tree structure. 

```
MBQC/
├─ src/
│  ├─ genericHelperFunctions
│  │  ├─ generalAssertFunctions.hpp
│  ├─ graphs/
│  │  ├─ graphConstructions.hpp
│  │  ├─ graphTraversalFlows.hpp
│  ├─ quantumGraphs/
│  │  ├─ stateConstruction.hpp
│  │  ├─ angleConstruction.hpp
│  │  ├─ quantumGraphClusterStates.hpp
│  │  ├─ circuitBasedGraphActions.hpp
│  │  ├─ flowMeasurements.hpp
│  ├─ testFunctions/
│  │  ├─ graphAssertFunctions.hpp
│  │  ├─ generalAssertFunctions.hpp
│  ├─ filesToGoThrough/
│  │  ├─ 2023028_TwoQubitsEachPiOn2Angle.cpp
│  │  ├─ 20230314_Functions_V1.hpp
│  │  ├─ 20230328_OddPathGraph0AnglesLastQubitOutcome.cpp
│  │  ├─ 20230328_OddPathGraphEveryOtherAngleZero.cpp
│  │  ├─ 20230330_CreatingMbqcFunction.cpp
│  │  ├─ PrepareMeasureSingleQubit.c
│  │  ├─ copyQureqState.cpp
│  │  ├─ createGraph.hpp
│  │  ├─ createLatticeGraph.cpp
│  │  ├─ createMbqcGraph.cpp
│  │  ├─ createPathGraph.cpp
│  │  ├─ directedGraphExample.cpp
│  │  ├─ edgeWeightundirectedGraphExample.cpp
│  │  ├─ findDijkstraSshortestPathExample.cpp
│  │  ├─ findMinimalSpanningTreeKruskalExample.cpp
│  │  ├─ sample.cpp
│  │  ├─ traverseGraph.cpp
│  │  ├─ undirectedGraphExample.cpp
├─ tests/
│  ├─ testGraphProperties.cpp
│  ├─ verification scripts with known results/
```

here the folders `genericHelperFunctions`, `graphs`, `quantumGraphs`, `testFunctions` and `test` are the working technology used to perform MBQC. **The work is not complete, but will follow this structure.** The folder `filesToGoThrough` contains files the need to be curated.


Building an MBQC simulator. This page will be the landing page for building the MBQC simulator. Links, requirments, user stories, etc will be placed here.

Repository documentation can be found [here](https://ediparquantum.github.io/MBQC/).

From a quick google search there are very few examples of MBQC simmulators. The goal here is to take a 


## Best practices and QuEST

1. [C++ Best practices for projects](https://micro-os-plus.github.io/develop/sutter-101/)
2. [QuEST Documentation](https://quest-kit.github.io/QuEST/index.html)



## Plan for MBQC Development
1. Arbitrary size "linear cluster", like ()-()-()----() for N vertices.
2. Analysis on the linear cluster.

3. Arbitrary size "grid cluster"
4. Analysis on grid cluster
5. Develop brickwork state
    + Universal resource for BQP under X-Y plane measurements
    + Useful to encode arbitrary computations blindly. 
    + [Brickwork graphs](https://arxiv.org/abs/0807.4154)
6. Arbitrary graph cluster

7. Analysis on graph cluster

## General script idea to run MBQC
Note big details are not included here, this is just a general flow with some details


```
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
```



### Linear Cluster example figure
![pathGraph](https://user-images.githubusercontent.com/19248072/225726167-6cf3710d-db2c-479c-be50-f8f9ce9ed101.png)

### Some testing options for linear cluster state


1. The easiest thing one could do would be all zero angles (0,0,...). For an odd total number of qubits, this should always give the outcome 0 of the last qubit.
   + [Circuit](https://algassert.com/quirk#circuit={%22cols%22:[[%22H%22,%22H%22,%22H%22,%22H%22,%22H%22],[%22%E2%80%A2%22,%22Z%22],[1,%22%E2%80%A2%22,%22Z%22],[1,1,%22%E2%80%A2%22,%22Z%22],[1,1,1,%22%E2%80%A2%22,%22Z%22],[%22%E2%80%A6%22],[%22H%22],[%22|0%E2%9F%A9%E2%9F%A80|%22],[1,%22H%22],[1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,%22H%22],[1,1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,1,%22H%22],[1,1,1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,1,1,%22H%22],[1,1,1,1,%22Measure%22]]})
2. Another thing that one could do on 2 qubits are angles (pi/2, pi/2). This should always give a 0 outcome of the second qubit.
    + [Circuit](https://algassert.com/quirk#circuit={%22cols%22:[[%22H%22,%22H%22],[%22%E2%80%A2%22,%22Z%22],[%22%E2%80%A6%22],[%22Z^-%C2%BD%22],[%22H%22],[%22|0%E2%9F%A9%E2%9F%A80|%22],[1,%22Z^-%C2%BD%22],[1,%22H%22],[1,%22Measure%22]]})
3. One more thing that one could do, would be to set every second angle to 0: (alpha_1, 0, alpha_3, 0, alpha_5, 0, ...). If the total number of qubits is odd, and all angles add up to a multiple of 2*pi, then the last measurement outcome should always be 0. If the total number of qubits is odd, and all angles add up to (a multiple of 2*pi) + pi, then the last measurement outcome should always be 1.
    + [Circuit](https://algassert.com/quirk#circuit={%22cols%22:[[%22H%22,%22H%22,%22H%22,%22H%22,%22H%22],[%22%E2%80%A2%22,%22Z%22],[1,%22%E2%80%A2%22,%22Z%22],[1,1,%22%E2%80%A2%22,%22Z%22],[1,1,1,%22%E2%80%A2%22,%22Z%22],[%22%E2%80%A6%22],[%22Z%22],[%22Z^-%C2%BC%22],[%22H%22],[%22|0%E2%9F%A9%E2%9F%A80|%22],[1,%22H%22],[1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,%22Z^-%C2%BD%22],[1,1,%22H%22],[1,1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,1,%22H%22],[1,1,1,%22|0%E2%9F%A9%E2%9F%A80|%22],[1,1,1,1,%22Z^-%C2%BC%22],[1,1,1,1,%22H%22],[1,1,1,1,%22Measure%22]]})

#### Comments on links

1. Instead of actual measurements, postselected for the 0 outcome. This avoids the need of corrections. In your code, you should use actual measurements and corrections, which should yield the same results.
    + T-gate = pi/4-rotation around Z-axis
    + S-gate = pi/2-rotation around Z-axis
    + Z-gate = pi-rotation around Z-axis
    + The example circuit from 3.) uses angles (5*pi/4, 0, pi/2, 0, pi/4).



## Links for a google search of "MBQC software"

1. [Graphix: optimizing and simulating measurement-based quantum computation on local-Clifford decorated graph](https://arxiv.org/abs/2212.11975)
2. [Measurement-based quantum computation](https://pennylane.ai/qml/demos/tutorial_mbqc.html)
3. [Qiskit As a Simulation Platform for Measurement-based Quantum Computation](https://ieeexplore.ieee.org/document/9779844)
4. [Quantum Computing Stack: Understanding Paddle Quantum's MBQC simulation](https://quantumcomputing.stackexchange.com/questions/27239/understanding-paddle-quantums-mbqc-simulation)
5. [MCBeth: A Measurement Based Quantum Programming Language](https://www.cs.yale.edu/homes/soule/pubs/arxiv2022.pdf)
6. [TundraSystems Quantum Software](https://tsgl.xyz/tundrasystems-quantum-software/)
7. [Graphix: optimizing and simulating measurement-based quantum computation on local-Clifford decorated graph different from before](https://inspirehep.net/literature/2617623)
8. [How to create and visualize a cluster state in FlamingPy](https://pennylane.ai/blog/2022/07/how-to-create-and-visualize-a-cluster-state-in-flamingpy/)
9. [Quantomatic/sample-projects](https://github.com/Quantomatic/sample-projects/releases/tag/qpc2018)
10. [Quantomatic](https://quantomatic.github.io/)
11. [Q2Graph: a modelling tool for measurement-based quantum computing](https://www.researchgate.net/publication/364126005_Q2Graph_a_modelling_tool_for_measurement-based_quantum_computing)
12. []()


## Links for a google search of "MBQC"

1. [https://en.wikipedia.org/wiki/One-way_quantum_computer](https://en.wikipedia.org/wiki/One-way_quantum_computer)
2. [https://qml.baidu.com/tutorials/measurement-based-quantum-computation/measurement-based-quantum-computation-module.html](https://qml.baidu.com/tutorials/measurement-based-quantum-computation/measurement-based-quantum-computation-module.html)
3. [https://github.com/PaddlePaddle/Quantum/tree/master/tutorials](https://github.com/PaddlePaddle/Quantum/tree/master/tutorials)
4. [http://pwallden.gr/files/IQC_2018_2019/18_IQC_Lecture16.pdf](http://pwallden.gr/files/IQC_2018_2019/18_IQC_Lecture16.pdf)
5. [https://www.youtube.com/watch?v=zBjAoOW3xHk&ab_channel=RobertRaussendorf](https://www.youtube.com/watch?v=zBjAoOW3xHk&ab_channel=RobertRaussendorf)
6. [https://www.youtube.com/@robertraussendorf9379](https://www.youtube.com/@robertraussendorf9379)
7. [https://www.youtube.com/@robertraussendorf9379](https://www.youtube.com/@robertraussendorf9379)
8. [Universal measurement-based quantum computation in a one-dimensional architecture enabled by dual-unitary circuits](https://arxiv.org/abs/2209.06191)
9. [https://pennylane.ai/qml/demos/tutorial_mbqc.html](https://pennylane.ai/qml/demos/tutorial_mbqc.html)
10. [https://oxfordre.com/physics/display/10.1093/acrefore/9780190871994.001.0001/acrefore-9780190871994-e-31;jsessionid=F048084B725DF72127D45A588315A515](https://oxfordre.com/physics/display/10.1093/acrefore/9780190871994.001.0001/acrefore-9780190871994-e-31;jsessionid=F048084B725DF72127D45A588315A515)
11. [https://www.uibk.ac.at/th-physik/mbqc2022/](https://www.uibk.ac.at/th-physik/mbqc2022/)


## To use in C++ Cmake

```cpp
# Use C++11
set(CMAKE_CXX_STANDARD 11)
```
