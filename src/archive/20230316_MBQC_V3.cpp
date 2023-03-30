//////////////////////////////////////////////////////////////////////
// Title     : Three qubit in a line entangled
// Author    : Jonathan Miller
// Date      : 20230309
// Aim       : Implement a simple MBQC circuit for ()-()-() circuit
// Flow      : Same row, next column; 
//           : f(0) = 1, f(1) = 2, f(2) = 3
//           : f-1(3) = 2, f-1(2) = 1, f-1(1) = 0

#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include "20230314_Functions_V1.hpp"
using namespace std;



int main() {
    
    // load QuEST
    QuESTEnv env = createQuESTEnv();
    
    // set parameters
    int numberQubits = 3;
	  qreal angles[numberQubits]; 
    qreal x_corrections[numberQubits];
    qreal z_corrections[numberQubits];
    qreal updated_angles[numberQubits]; 
    int measured_qubits[numberQubits];
    
    
    // set initial angles
	for(int i=0;i<numberQubits;i++)
	    angles[i] = M_PI / 4; 
	
    // Set first updated angle to match first original angle
    updated_angles[0] = angles[0];

    // prepare our register
    Qureg qureg = createQureg(numberQubits, env);


    // qureg -> |+><+|
    initPlusState(qureg);  
    
    // apply CZ gate to entangle the circuit
    controlledPhaseFlip(qureg,0,1);
    controlledPhaseFlip(qureg,1,2);

    
    // measure first qubit
    // ()-()-() -> X-()-(), for X being a removed qubit
    rotateZ(qureg,0, angles[0]);
    hadamard(qureg,0);
    measured_qubits[0] = measure(qureg,0);
    x_corrections[0] = 0;
    z_corrections[0] = 0;

    // update second angle
    int sum_neigh_meas_q0 = 0;
    x_corrections[1] = pow(-1, measured_qubits[0])*angles[1];
    z_corrections[1] = M_PI*(sum_neigh_meas_q0);
    updated_angles[1] = x_corrections[1] + z_corrections[1];
    


    // measure second qubit
    // X-()-() -> X-X-(), for X being a removed qubit
    rotateZ(qureg,1, (-1)*updated_angles[1]);
    hadamard(qureg,1);
    measured_qubits[1] = measure(qureg,1);
    
    
    



    // update third angle
    int sum_neigh_meas_q1 = measured_qubits[0];
    x_corrections[2] = pow(-1, measured_qubits[1])*angles[2];
    z_corrections[2] = M_PI*(sum_neigh_meas_q1);
    updated_angles[2] = x_corrections[2] + z_corrections[2];

    // measure third qubit
    // X-X-() -> X-X-X, for X being a removed qubit
    rotateZ(qureg,2, (-1)*updated_angles[2]);
    hadamard(qureg,2);
    measured_qubits[2] = measure(qureg,2);
     
    

    

    // Print data to screen
    printf("Original angles: ");
    for(int i = 0; i < numberQubits; i++)
    {
      printf("%f ", angles[i]);
    }

    printf("\nUpdated angles: ");
    for(int i = 0; i < numberQubits; i++)
    {
      printf("%f ", updated_angles[i]);
    }

    printf("\nMeasured array: ");
    for(int i = 0; i < numberQubits; i++)
    {
      printf("%d ", measured_qubits[i]);
    }

    printf("\nProbability of each outcome: ");
    for (int i = 0; i < numberQubits; i++)
    {
        qreal prob = calcProbOfOutcome(qureg,i,0);
        printf("%f ", prob);
    }

    printf("\nX corection: ");
    for (int i = 0; i < numberQubits; i++)
    {
        printf("%f ", x_corrections[i]);
    }


    printf("\nZ corection: ");
    for (int i = 0; i < numberQubits; i++)
    {
        printf("%f ", z_corrections[i]);
    }
 
    int currentQubit = 0;
    int futureQubit = getFutureQubit(currentQubit);
    int pastQubit = getPastQubit(currentQubit);

    printf("\nPast qubit is %d\n",pastQubit);
    printf("Current qubit is %d\n",currentQubit);
    printf("Future qubit is %d\n",futureQubit);

    
    int size_neighbour_set;
    size_neighbour_set = getOpenNeighbourhoodSizePathGraph(currentQubit,numberQubits);
    printf("Size of neighbour set: %d\n",size_neighbour_set);  

    vector<int> neighbours;
    neighbours = getOpenNeighbourhoodPathGraph(currentQubit,numberQubits);

    printf("For current qubit, %d, the neighbours are ",currentQubit);
    
    for (int i: neighbours)
    {
        cout << i << ' ';
    }

    
  
}






