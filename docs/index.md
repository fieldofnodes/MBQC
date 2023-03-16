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
vector<int> get_linear_cluster_on_n_qubits(int number_of_qubits)
{
  vector<int> linear_cluster;
  for (int i = 0; i < number_of_qubits; i++ )
  {
    linear_cluster.push_back(i);  
  }
  return linear_cluster;
}
```

#### Flow function

Linear cluster state flow is defined as, $f(i) = i + 1$, where $i$ is the current qubit. Consider the graph as a line of qubits, then the flow foward is the next qubit according to the labelled index.

```cpp
int get_future_qubit_linear_cluster(int current_qubit){
  int future_qubit;
  future_qubit = current_qubit + 1;

  return future_qubit;
}
```

Linear flow backwards is defined as, $f^{-1}(i) = i - 1$.

```cpp
int get_past_qubit_linear_cluster(int current_qubit){
  int past_qubit;
  past_qubit = current_qubit - 1;

  return past_qubit;
}
```

Linear cluster vector with the flow, $f$, $f(i) = i + 1$, if $i$ is last element of vector, then throw error.

```cpp
int get_future_qubit_linear_cluster_vec(vector<int> linear_cluster ,int current_qubit)
{
int future_qubit;
auto cluster_size = linear_cluster.size();
if (current_qubit == linear_cluster[cluster_size-1]) {
    assert(current_qubit != linear_cluster[cluster_size-1] && "No past qubit here, re-check your program");
} else {
  future_qubit = get_future_qubit_linear_cluster(current_qubit);
}
  return future_qubit;
}
```

 Linear cluster vector with the flow, $f$, $f^{-1}(i) = i - 1$, if $i$ is first element of vector, then throw error.

```cpp
int get_past_qubit_linear_cluster_vec(vector<int> linear_cluster ,int current_qubit)
{
int past_qubit;

if (current_qubit == linear_cluster[0]) {
  assert(current_qubit != linear_cluster[0] && "No past qubit here, re-check your program");

} else {
  past_qubit = get_past_qubit_linear_cluster(current_qubit);
}
  return past_qubit;
}
```

#### Neighborhood

The neighbor set in a cluster state is technically the open neighbours set, as we do not consider the present or current qubit. Here we get the neighbourhood size by looking at the linear cluster state vector and the current qubit. The logic determines if there are $1$ or $2$ neighbours to the current qubit, based on the qubit position in the linear cluster.

```cpp
int get_size_neighbour_set_linear_cluster(vector<int> linear_cluster ,int current_qubit){
  auto cluster_size = linear_cluster.size();
  int neighbour_size;
  // Logic for getting nieghbors
  if (current_qubit == 0) { // qubit is first
    neighbour_size = 1;
  } else if (current_qubit == linear_cluster[cluster_size-1]) { // qubit is last
    neighbour_size = 1;
  } else { // all else
    neighbour_size = 2;
  }

  return neighbour_size;
}
```

Get the neighbor set of qubits based on the linear cluster and the current qubit

```cpp
vector<int> get_open_neighbour_set_linear_cluster(vector<int> linear_cluster ,int current_qubit){
  vector<int> neighbours;
  auto cluster_size = linear_cluster.size();
  int first_qubit;
  int qubit_before;
  int qubit_after;

  if (current_qubit == linear_cluster[0]) { // qubit is first in graph
    first_qubit = current_qubit + 1;
    neighbours.push_back(first_qubit);
  } else if (current_qubit == linear_cluster[cluster_size-1]) { // qubit is last in graph
    first_qubit = current_qubit - 1;
    neighbours.push_back(first_qubit);
  } else { // all else
    qubit_before = current_qubit - 1;
    qubit_after = current_qubit + 1;
    neighbours.push_back(qubit_before);
    neighbours.push_back(qubit_after);
  }

  return neighbours;
}
```
