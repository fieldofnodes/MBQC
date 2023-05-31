#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;


/* 
  Create vector of digits from 0 to N, separated by 1
  To represent the a line of nodes connected by one 
  edge ()-()-()- - - -() (1,2,3,...,N)
*/
vector<int> getPathGraph(int numberQubits)
{
  vector<int> pathGraph;
  for (int i = 0; i < numberQubits; i++ )
  {
    pathGraph.push_back(i);  
  }
  return pathGraph;
}

/*
  Linear flow, f(i) = i + 1
*/
int getFutureQubit(int currentQubit){
  int futureQubit;
  futureQubit = currentQubit + 1;

  return futureQubit;
}

/*
  Linear flow, f^{-1}(i) = i - 1
*/
int getPastQubit(int currentQubit){
  int pastQubit;
  pastQubit = currentQubit - 1;

  return pastQubit;
}

/*
  Linear cluster vector with the flow, f.
  f(i) = i + 1, if i is last element of vector, then
  throw error.
*/
int getFutureQubitPathGraph(vector<int> pathGraph ,int currentQubit)
{
int futureQubit;
auto graphSize = pathGraph.size();
if (currentQubit == pathGraph[graphSize-1]) {
    futureQubit = currentQubit;
} else {
  futureQubit = getFutureQubit(currentQubit);
}
  return futureQubit;
}


/*
  Linear cluster vector with the flow, f.
  f^{-1}(i) = i - 1, if i is first element of vector, then
  throw error.
*/
int getPastQubitPathGraph(vector<int> pathGraph ,int currentQubit)
{
int pastQubit;

if (currentQubit == pathGraph[0]) {
  pastQubit = currentQubit;

} else {
  pastQubit = getPastQubit(currentQubit);
}
  return pastQubit;
}


/*
  Get the neighbourhood size
  Look at the linear cluster and the current qubit
  Determine if there are one or two neighbours to the 
  current qubit based on the qubit position in the
  linear cluster
*/
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

/*
  Get the neighbourhood of the qubit based on the linear cluster and the 
  qubits
*/
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


  qreal computeXCorrectionAnglePathGraph(
      vector<int> pathGraph, 
      vector<int> measuredQubitsOutcomes,
      vector<qreal> qubitAngles,
      int currentQubit)
  {
      qreal xCorrectionAngle;
      int pastQubit;
      pastQubit = getPastQubitPathGraph(pathGraph,currentQubit);
      int inverseFlowQubitOutcome = measuredQubitsOutcomes[pastQubit];
      xCorrectionAngle = pow(-1, inverseFlowQubitOutcome)*qubitAngles[currentQubit];

      return xCorrectionAngle;
  }



  qreal computeZCorrectionAnglePathGraph(
      vector<int> pathGraph, 
      vector<int> measuredQubitsOutcomes,
      int currentQubit)
  {   
      qreal zCorrectionAngle;
      
      int pastQubit;
      int pastPastQubit;
      int inverseFlowQubitOutcome;
      pastQubit = getPastQubitPathGraph(pathGraph,currentQubit);
      pastPastQubit = getPastQubitPathGraph(pathGraph,pastQubit);
      inverseFlowQubitOutcome = measuredQubitsOutcomes[pastPastQubit];
      zCorrectionAngle = M_PI*inverseFlowQubitOutcome;
              
      return zCorrectionAngle;
  }

int countElements(vector<int> v, int element) {
    int count = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == element) {
            ++count;
        }
    }
    return count;
}

vector<int> runMbqcPathGraph(
        Qureg qureg,
        vector<int> pathGraph,
        vector<qreal> qubitAngles){


    vector<qreal> updatedQubitAngles;
    vector<int> measuredQubitsOutcomes;
    int numberQubits = pathGraph.size();
    qreal X1;
    int firstQubitIndex=0;
    int secondQubitIndex=1;
    

    // Measure first qubit and update angle
    updatedQubitAngles.push_back(qubitAngles[firstQubitIndex]);
    rotateZ(qureg,firstQubitIndex, (-1)*updatedQubitAngles[firstQubitIndex]);
    hadamard(qureg,firstQubitIndex);
    measuredQubitsOutcomes.push_back(measure(qureg,firstQubitIndex));

    // measure second qubit
    X1 = pow((-1),measuredQubitsOutcomes[firstQubitIndex])*qubitAngles[secondQubitIndex];
    updatedQubitAngles[secondQubitIndex] = X1;
    rotateZ(qureg,secondQubitIndex, (-1)*updatedQubitAngles[secondQubitIndex]);
    hadamard(qureg,secondQubitIndex);
    measuredQubitsOutcomes.push_back(measure(qureg,secondQubitIndex));
                

    for(int currentQubit=2;currentQubit<numberQubits;currentQubit++)
        {       
            qreal X;
            qreal Z;
            qreal phiPrime;
            int outcome;

            X = computeXCorrectionAnglePathGraph(
                    pathGraph, 
                    measuredQubitsOutcomes,
                    qubitAngles,
                    currentQubit);
            Z = computeZCorrectionAnglePathGraph(
                    pathGraph, 
                    measuredQubitsOutcomes,
                    currentQubit);
            phiPrime = X+Z;
            
            rotateZ(qureg,currentQubit, (-1)*phiPrime);
            hadamard(qureg,currentQubit);
            outcome = measure(qureg,currentQubit);
            
            measuredQubitsOutcomes.push_back(outcome);
        }

            return measuredQubitsOutcomes;
}