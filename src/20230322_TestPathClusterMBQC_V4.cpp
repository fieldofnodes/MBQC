#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include "20230314_Functions_V1.hpp"
using namespace std;

    qreal ComputeXCorrectionAngle(
        vector<int> LinearCluster, 
        vector<int> MeasuredQubitsOutcomes,
        vector<qreal> QubitAngles,
        int CurrentQubit)
    {
        qreal xCorrectionAngle;
        int PastQubit;
        PastQubit = get_past_qubit_linear_cluster_vec(LinearCluster,CurrentQubit);
        int InverseFlowQubitOutcome = MeasuredQubitsOutcomes[PastQubit];
        xCorrectionAngle = pow(-1, InverseFlowQubitOutcome)*QubitAngles[CurrentQubit];

        return xCorrectionAngle;
    }



    qreal ComputeZCorrectionAngle(
        vector<int> LinearCluster, 
        vector<int> MeasuredQubitsOutcomes,
        int CurrentQubit)
    {   
        qreal zCorrectionAngle;
        
        int PastQubit;
        int PastPastQubit;
        int InverseFlowQubitOutcome;
        PastQubit = get_past_qubit_linear_cluster_vec(LinearCluster,CurrentQubit);
        PastPastQubit = get_past_qubit_linear_cluster_vec(LinearCluster,PastQubit);
        InverseFlowQubitOutcome = MeasuredQubitsOutcomes[PastPastQubit];
        zCorrectionAngle = M_PI*InverseFlowQubitOutcome;
               
        return zCorrectionAngle;
    }





int main() {
   
    QuESTEnv env = createQuESTEnv();
    // set parameters
    int NumberQubits = 10;
        // prepare our register
    Qureg qureg = createQureg(NumberQubits, env);
    // qureg -> |+><+|
    initPlusState(qureg);  


    // Create a vector representing a linear cluster graph
    vector<int> LinearCluster = get_linear_cluster_on_n_qubits(NumberQubits);
    vector<int> MeasuredQubitsOutcomes;
    vector<qreal> QubitAngles;
    vector<qreal> UpdatedQubitAngles;
    vector<qreal> XCorrectionAngle;
    vector<qreal> ZCorrectionAngle;

    // apply CZ gate to entangle the circuit
    for(std::vector<int>::size_type q = 0; q != LinearCluster.size()-1; q++) 
    {    
        controlledPhaseFlip(qureg,q,q+1);
    }

    
    // set initial angles
	for(int i=0;i<NumberQubits;i++)
	    QubitAngles.push_back(0.0); 
	


    // Set first updated angle to match first original angle
    

    // measure first qubit
    qreal X0 = 0.0;
    qreal Z0 = 0.0;
    int FirstQubitIndex=0;
    UpdatedQubitAngles.push_back(QubitAngles[FirstQubitIndex]);
    rotateZ(qureg,FirstQubitIndex, (-1)*UpdatedQubitAngles[FirstQubitIndex]);
    hadamard(qureg,FirstQubitIndex);
    MeasuredQubitsOutcomes.push_back(measure(qureg,FirstQubitIndex));
    XCorrectionAngle.push_back(X0);
    ZCorrectionAngle.push_back(Z0);
    
    cout << "Qubit: " << FirstQubitIndex << " Outcome: " << MeasuredQubitsOutcomes[FirstQubitIndex] << "Updated angle: " << UpdatedQubitAngles[FirstQubitIndex] << "\n"; 
    // measure second qubit
    qreal X1;
    qreal Z1;
    int SecondQubitIndex=1;
    X1 = pow((-1),MeasuredQubitsOutcomes[SecondQubitIndex])*QubitAngles[SecondQubitIndex];
    UpdatedQubitAngles[SecondQubitIndex] = X1;
    rotateZ(qureg,SecondQubitIndex, (-1)*UpdatedQubitAngles[SecondQubitIndex]);
    hadamard(qureg,SecondQubitIndex);
    MeasuredQubitsOutcomes.push_back(measure(qureg,SecondQubitIndex));
    XCorrectionAngle.push_back(X1);
    ZCorrectionAngle.push_back(0.0);

    cout << "Qubit: " << SecondQubitIndex << " Outcome: " << MeasuredQubitsOutcomes[SecondQubitIndex] << "Updated angle: " << UpdatedQubitAngles[SecondQubitIndex] << "\n"; 
    

for(int CurrentQubit=2;CurrentQubit<NumberQubits;CurrentQubit++)
{       
    qreal X;
    qreal Z;
    qreal phi;
    qreal phi_prime;
    int outcome;

    
    X = ComputeXCorrectionAngle(
            LinearCluster, 
            MeasuredQubitsOutcomes,
            QubitAngles,
            CurrentQubit);
    Z = ComputeZCorrectionAngle(
            LinearCluster, 
            MeasuredQubitsOutcomes,
            CurrentQubit);
    phi_prime = X+Z;
    
    rotateZ(qureg,CurrentQubit, (-1)*phi_prime);
    hadamard(qureg,CurrentQubit);
    outcome = measure(qureg,CurrentQubit);
    
    XCorrectionAngle.push_back(X);
    ZCorrectionAngle.push_back(Z);
    UpdatedQubitAngles.push_back(phi_prime);
    MeasuredQubitsOutcomes.push_back(outcome);
    cout << "Qubit: " << CurrentQubit << " Outcome: " << outcome << "Updated angle: " << phi_prime << "\n"; 
}


    /*
    int sum_neigh_meas_q0 = 0;
    z_corrections[1] = M_PI*(sum_neigh_meas_q0);
    updated_angles[1] = x_corrections[1] + z_corrections[1];
    


    // measure second qubit
    // X-()-() -> X-X-(), for X being a removed qubit
    rotateZ(qureg,1, (-1)*updated_angles[1]);
    hadamard(qureg,1);
    measured_qubits[1] = measure(qureg,1);
    
    
    



// Iterate over the path cluster
    for (int q: LinearCluster)
    {
        cout << "Qubit: " << q << "\n";
        vector<int> neighbours = 
            get_open_neighbour_set_linear_cluster(
                LinearCluster ,q);
        cout << "Neighbours: ";
        // Get the future qubit using linear_cluster and current qubit
        int FutureQubit = get_future_qubit_linear_cluster_vec(LinearCluster ,q);
        printf("Current qubit: %d future qubit: %d\n",q,FutureQubit);
        // Get the past qubit using linear_cluster and current qubit
        int PastQubit = get_past_qubit_linear_cluster_vec(LinearCluster ,q);
        printf("Current qubit: %d past qubit: %d\n",q,FutureQubit);
        for (int n: neighbours)
        {
            cout << n << ' ';
        }
        printf("\n");
        
    }

}





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
    for(int i = 0; i < NumberQubits; i++)
    {
      printf("%f ", angles[i]);
    }

    printf("\nUpdated angles: ");
    for(int i = 0; i < NumberQubits; i++)
    {
      printf("%f ", updated_angles[i]);
    }

    printf("\nMeasured array: ");
    for(int i = 0; i < NumberQubits; i++)
    {
      printf("%d ", measured_qubits[i]);
    }

    printf("\nProbability of each outcome: ");
    for (int i = 0; i < NumberQubits; i++)
    {
        qreal prob = calcProbOfOutcome(qureg,i,0);
        printf("%f ", prob);
    }

    printf("\nX corection: ");
    for (int i = 0; i < NumberQubits; i++)
    {
        printf("%f ", x_corrections[i]);
    }


    printf("\nZ corection: ");
    for (int i = 0; i < NumberQubits; i++)
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
    size_neighbour_set = get_size_neighbour_set_linear_cluster(current_qubit,NumberQubits);
    printf("Size of neighbour set: %d\n",size_neighbour_set);  

    vector<int> neighbours;
    neighbours = get_open_neighbour_set_linear_cluster(current_qubit,NumberQubits);

    printf("For current qubit, %d, the neighbours are ",current_qubit);
    
    for (int i: neighbours)
    {
        cout << i << ' ';
    }

    
  
    

    // Iterate over all vertices, return neighbours
    
    // Iterate over the path cluster
    for (int q: LinearCluster)
    {
        cout << "Qubit: " << q << "\n";
        vector<int> neighbours = 
            get_open_neighbour_set_linear_cluster(
                LinearCluster ,q);
        cout << "Neighbours: ";
        // Get the future qubit using linear_cluster and current qubit
        int FutureQubit = get_future_qubit_linear_cluster_vec(LinearCluster ,q);
        printf("Current qubit: %d future qubit: %d\n",q,FutureQubit);
        // Get the past qubit using linear_cluster and current qubit
        int PastQubit = get_past_qubit_linear_cluster_vec(LinearCluster ,q);
        printf("Current qubit: %d past qubit: %d\n",q,FutureQubit);
        for (int n: neighbours)
        {
            cout << n << ' ';
        }
        printf("\n");
        
    }
*/
}


