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
using namespace std;


void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}


int get_future_qubit_linear_cluster(int current_qubit){
  int new_qubit;
  new_qubit = current_qubit + 1;

  return new_qubit;
}

int get_past_qubit_linear_cluster(int current_qubit){
  int new_qubit;
  new_qubit = current_qubit - 1;

  return new_qubit;
}

int get_size_neighbour_set_linear_cluster(int current_qubit,int number_of_qubits){
  int number_qubits;
  // Logic for getting nieghbors
  if (current_qubit == 0) { // qubit is first
    number_qubits = 1;
  } else if (current_qubit == number_of_qubits-1) { // qubit is last
    number_qubits = 1;
  } else { // all else
    number_qubits = 2;
  }

  return number_qubits;
}

vector<int> get_open_neighbour_set_linear_cluster(int current_qubit,int number_of_qubits){
  vector<int> neighbours;
  
  
  if (current_qubit == 0) { // qubit is first in graph
    int first_qubit = current_qubit + 1;
    neighbours.push_back(first_qubit);
  } else if (current_qubit == number_of_qubits-1) { // qubit is last in graph
    int first_qubit = current_qubit - 1;
    neighbours.push_back(first_qubit);
  } else { // all else
    int qubit_before = current_qubit - 1;
    int qubit_after = current_qubit + 1;
    neighbours.push_back(qubit_before);
    neighbours.push_back(qubit_after);
  }

  return neighbours;
}


int main() {
    
    // load QuEST
    QuESTEnv env = createQuESTEnv();
    
    // set parameters
    int number_of_qubits = 3;
	  qreal angles[number_of_qubits]; 
    qreal x_corrections[number_of_qubits];
    qreal z_corrections[number_of_qubits];
    qreal updated_angles[number_of_qubits]; 
    int measured_qubits[number_of_qubits];
    
    
    // set initial angles
	for(int i=0;i<number_of_qubits;i++)
	    angles[i] = M_PI / 4; 
	
    // Set first updated angle to match first original angle
    updated_angles[0] = angles[0];

    // prepare our register
    Qureg qureg = createQureg(number_of_qubits, env);


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
    for(int i = 0; i < number_of_qubits; i++)
    {
      printf("%f ", angles[i]);
    }

    printf("\nUpdated angles: ");
    for(int i = 0; i < number_of_qubits; i++)
    {
      printf("%f ", updated_angles[i]);
    }

    printf("\nMeasured array: ");
    for(int i = 0; i < number_of_qubits; i++)
    {
      printf("%d ", measured_qubits[i]);
    }

    printf("\nProbability of each outcome: ");
    for (int i = 0; i < number_of_qubits; i++)
    {
        qreal prob = calcProbOfOutcome(qureg,i,0);
        printf("%f ", prob);
    }

    printf("\nX corection: ");
    for (int i = 0; i < number_of_qubits; i++)
    {
        printf("%f ", x_corrections[i]);
    }


    printf("\nZ corection: ");
    for (int i = 0; i < number_of_qubits; i++)
    {
        printf("%f ", z_corrections[i]);
    }
 
    int current_qubit = 0;
    int future_qubit = get_future_qubit_linear_cluster(current_qubit);
    int past_qubit = get_past_qubit_linear_cluster(current_qubit);

    printf("\nPast qubit is %d\n",past_qubit);
    printf("Current qubit is %d\n",current_qubit);
    printf("Future qubit is %d\n",future_qubit);

    
    int size_neighbour_set;
    size_neighbour_set = get_size_neighbour_set_linear_cluster(current_qubit,number_of_qubits);
    printf("Size of neighbour set: %d\n",size_neighbour_set);  

    vector<int> neighbours;
    neighbours = get_open_neighbour_set_linear_cluster(current_qubit,number_of_qubits);

    printf("For current qubit, %d, the neighbours are ",current_qubit);
    
    for (int i: neighbours)
    {
        cout << i << ' ';
    }

    
  
}






