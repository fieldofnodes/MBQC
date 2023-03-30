#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>    // std::all_of
#include <string>
#include "20230314_Functions_V1.hpp"
using namespace std;


int main() {

    
    vector<int> lastQubitOutcome;
    int numberRealisations = 1E6;
    int numberQubits = 2;

    
    for(int i=0;i<numberRealisations;i++)
    {  
        QuESTEnv env = createQuESTEnv();
        // set parameters
        int numberQubits = numberQubits;//11;
            // prepare our register
        Qureg qureg = createQureg(numberQubits, env);
        // qureg -> |+><+|
        initPlusState(qureg);  


        // Create a vector representing a linear cluster graph
        vector<int> pathGraph = getPathGraph(numberQubits); 
        vector<int> measuredQubitsOutcomes;
        vector<qreal> qubitAngles;
        vector<qreal> updatedQubitAngles;
        

        // apply CZ gate to entangle the circuit
        for(std::vector<int>::size_type q = 0; q != pathGraph.size()-1; q++) 
        {    
            controlledPhaseFlip(qureg,q,q+1);
        }


        // set initial angles
        for(int i=0;i<numberQubits;i++)
        {
            qubitAngles.push_back(M_PI/2); 
        }   
        
        // Run MBQC
        // measure first qubit
        int firstQubitIndex=0;
        updatedQubitAngles.push_back(qubitAngles[firstQubitIndex]);
        rotateZ(qureg,firstQubitIndex, (-1)*updatedQubitAngles[firstQubitIndex]);
        hadamard(qureg,firstQubitIndex);
        measuredQubitsOutcomes.push_back(measure(qureg,firstQubitIndex));
        
        
        
        
        
        
        // measure second qubit
        qreal X1;
        //qreal Z1;
        int secondQubitIndex=1;
        X1 = pow((-1),measuredQubitsOutcomes[firstQubitIndex])*qubitAngles[secondQubitIndex];
        updatedQubitAngles[secondQubitIndex] = X1;
        rotateZ(qureg,secondQubitIndex, (-1)*updatedQubitAngles[secondQubitIndex]);
        hadamard(qureg,secondQubitIndex);
        measuredQubitsOutcomes.push_back(measure(qureg,secondQubitIndex));
        
        //vectUpdatedAngles.push_back(updatedQubitAngles);
        lastQubitOutcome.push_back(measuredQubitsOutcomes.back());
    }

    
    int numberZeros = countElements(lastQubitOutcome, 0);
    int numberOnes = countElements(lastQubitOutcome, 1);
    double ratioZeros = (numberZeros*(1.0))/numberRealisations*(1.0);
    double ratioOnes = (numberOnes*(1.0))/numberRealisations*(1.0);
    cout << "Number last qubits = 0: " << numberZeros << "\n";
    cout << "Number last qubits = 1: " << numberOnes << "\n";
    cout << "Ratio last qubits = 0: " << ratioZeros << "\n";
    cout << "Ratio last qubits = 1: " << ratioOnes << "\n";
    
    
}

