#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include "20230314_Functions_V1.hpp"
using namespace std;



int main() {
     
    QuESTEnv env = createQuESTEnv();
    // set parameters
    int NumberQubits = 5;
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
    
    cout << "Qubit: " << FirstQubitIndex << " Outcome: " << MeasuredQubitsOutcomes[FirstQubitIndex] << " Updated angle: " << UpdatedQubitAngles[FirstQubitIndex] << "\n"; 
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

    cout << "Qubit: " << SecondQubitIndex << " Outcome: " << MeasuredQubitsOutcomes[SecondQubitIndex] << " Updated angle: " << UpdatedQubitAngles[SecondQubitIndex] << "\n"; 
    

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
        cout << "Qubit: " << CurrentQubit << " Outcome: " << outcome << " Updated angle: " << phi_prime << "\n"; 
    }

}




