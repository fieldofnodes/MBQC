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
    int numberQubits = 5;
        // prepare our register
    Qureg qureg = createQureg(numberQubits, env);
    // qureg -> |+><+|
    initPlusState(qureg);  


    // Create a vector representing a linear cluster graph
    vector<int> pathGraph = getPathGraph(numberQubits); 
    vector<int> measuredQubitsOutcomes;
    vector<qreal> qubitAngles;
    vector<qreal> updatedQubitAngles;
    vector<qreal> XCorrectionAngle;
    vector<qreal> ZCorrectionAngle;

    // apply CZ gate to entangle the circuit
    for(std::vector<int>::size_type q = 0; q != pathGraph.size()-1; q++) 
    {    
        controlledPhaseFlip(qureg,q,q+1);
    }

    
    // set initial angles
	for(int i=0;i<numberQubits;i++)
	    qubitAngles.push_back(0.0); 
	


    // Set first updated angle to match first original angle
    

    // measure first qubit
    qreal X0 = 0.0;
    qreal Z0 = 0.0;
    int firstQubitIndex=0;
    updatedQubitAngles.push_back(qubitAngles[firstQubitIndex]);
    rotateZ(qureg,firstQubitIndex, (-1)*updatedQubitAngles[firstQubitIndex]);
    hadamard(qureg,firstQubitIndex);
    measuredQubitsOutcomes.push_back(measure(qureg,firstQubitIndex));
    XCorrectionAngle.push_back(X0);
    ZCorrectionAngle.push_back(Z0);
    
    cout << "Qubit: " << firstQubitIndex << " Outcome: " << measuredQubitsOutcomes[firstQubitIndex] << " Updated angle: " << updatedQubitAngles[firstQubitIndex] << "\n"; 
    // measure second qubit
    qreal X1;
    qreal Z1;
    int secondQubitIndex=1;
    X1 = pow((-1),measuredQubitsOutcomes[secondQubitIndex])*qubitAngles[secondQubitIndex];
    updatedQubitAngles[secondQubitIndex] = X1;
    rotateZ(qureg,secondQubitIndex, (-1)*updatedQubitAngles[secondQubitIndex]);
    hadamard(qureg,secondQubitIndex);
    measuredQubitsOutcomes.push_back(measure(qureg,secondQubitIndex));
    XCorrectionAngle.push_back(X1);
    ZCorrectionAngle.push_back(0.0);

    cout << "Qubit: " << secondQubitIndex << " Outcome: " << measuredQubitsOutcomes[secondQubitIndex] << " Updated angle: " << updatedQubitAngles[secondQubitIndex] << "\n"; 
    

    for(int currentQubit=2;currentQubit<numberQubits;currentQubit++)
    {       
        qreal X;
        qreal Z;
        qreal phi;
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
        
        XCorrectionAngle.push_back(X);
        ZCorrectionAngle.push_back(Z);
        updatedQubitAngles.push_back(phiPrime);
        measuredQubitsOutcomes.push_back(outcome);
        cout << "Qubit: " << currentQubit << " Outcome: " << outcome << " Updated angle: " << phiPrime << "\n"; 
    }

}




