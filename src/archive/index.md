# MBQC

## Measurement Based Quantum Computation

### Linear Cluster 

#### Used this libraries

```cpp
#include <QuEST.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
```

#### Create a linear cluster

Create vector of digits from $0$ to $N-1$, separated by $1$ to represent a cluster state by a line of nodes connected by edges, similar to this asci art `()-()-()- - - -()` where each `()` represent a node or a qubit when this structure is used to generate the cluster state of qubits.  $(0,2,3,...,N-1)$

```cpp
vector<int> getPathGraph(int numberQubits)
{
  vector<int> pathGraph;
  for (int i = 0; i < numberQubits; i++ )
  {
    pathGraph.push_back(i);  
  }
  return pathGraph;
}
```

#### Flow function

Linear cluster state flow is defined as, $f(i) = i + 1$, where $i$ is the current qubit. Consider the graph as a line of qubits, then the flow foward is the next qubit according to the labelled index.

```cpp
int getFutureQubit(int currentQubit){
  int futureQubit;
  futureQubit = currentQubit + 1;

  return futureQubit;
}
```

Linear flow backwards is defined as, $f^{-1}(i) = i - 1$.

```cpp
int getPastQubit(int currentQubit){
  int pastQubit;
  pastQubit = currentQubit - 1;

  return pastQubit;
}
```

Linear cluster vector with the flow, $f$, $f(i) = i + 1$, if $i$ is last element of vector, then throw error.

```cpp
int getFutureQubitPathGraph(vector<int> pathGraph ,int currentQubit)
{
int futureQubit;
auto graphSize = pathGraph.size();
if (currentQubit == pathGraph[graphSize-1]) {
    assert(currentQubit != pathGraph[graphSize-1] && "No past qubit here, re-check your program");
} else {
  futureQubit = getFutureQubit(currentQubit);
}
  return futureQubit;
}
```

 Linear cluster vector with the flow, $f$, $f^{-1}(i) = i - 1$, if $i$ is first element of vector, then throw error.

```cpp
int getPastQubitPathGraph(vector<int> pathGraph ,int currentQubit)
{
int pastQubit;

if (currentQubit == pathGraph[0]) {
  assert(currentQubit != pathGraph[0] && "No past qubit here, re-check your program");

} else {
  pastQubit = getPastQubit(currentQubit);
}
  return pastQubit;
}
```

#### Neighborhood

The neighbor set in a cluster state is technically the open neighbours set, as we do not consider the present or current qubit. Here we get the neighbourhood size by looking at the linear cluster state vector and the current qubit. The logic determines if there are $1$ or $2$ neighbours to the current qubit, based on the qubit position in the linear cluster.

```cpp
int getOpenNeighbourhoodSizePathGraph(vector<int> pathGraph ,int currentQubit){
  auto graphSize = pathGraph.size();
  int neighbourhoodSize;
  // Logic for getting nieghbors
  if (currentQubit == 0) { // qubit is first
    neighbourhoodSize = 1;
  } else if (currentQubit == pathGraph[graphSize-1]) { // qubit is last
    neighbourhoodSize = 1;
  } else { // all else
    neighbourhoodSize = 2;
  }

  return neighbourhoodSize;
}
```

Get the neighbor set of qubits based on the linear cluster and the current qubit

```cpp
vector<int> getOpenNeighbourhoodPathGraph(vector<int> pathGraph ,int currentQubit){
  vector<int> neighbours;
  auto graphSize = pathGraph.size();
  int firstQubit;
  int pastQubit;
  int futureQubit;

  if (currentQubit == pathGraph[0]) { // qubit is first in graph
    firstQubit = currentQubit + 1;
    neighbours.push_back(firstQubit);
  } else if (currentQubit == pathGraph[graphSize-1]) { // qubit is last in graph
    firstQubit = currentQubit - 1;
    neighbours.push_back(firstQubit);
  } else { // all else
    pastQubit = currentQubit - 1;
    futureQubit = currentQubit + 1;
    neighbours.push_back(pastQubit);
    neighbours.push_back(futureQubit);
  }

  return neighbours;
}
```
