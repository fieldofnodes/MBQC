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
        int NumberQubits = numberQubits;//11;
            // prepare our register
        Qureg qureg = createQureg(NumberQubits, env);
        // qureg -> |+><+|
        initPlusState(qureg);  


        // Create a vector representing a linear cluster graph
        vector<int> LinearCluster = get_linear_cluster_on_n_qubits(NumberQubits); 
        vector<int> MeasuredQubitsOutcomes;
        vector<qreal> QubitAngles;
        vector<qreal> UpdatedQubitAngles;
        

        // apply CZ gate to entangle the circuit
        for(std::vector<int>::size_type q = 0; q != LinearCluster.size()-1; q++) 
        {    
            controlledPhaseFlip(qureg,q,q+1);
        }


        // set initial angles
        for(int i=0;i<NumberQubits;i++)
        {
            QubitAngles.push_back(M_PI/2); 
        }   
        
        // Run MBQC
        // measure first qubit
        int FirstQubitIndex=0;
        UpdatedQubitAngles.push_back(QubitAngles[FirstQubitIndex]);
        rotateZ(qureg,FirstQubitIndex, (-1)*UpdatedQubitAngles[FirstQubitIndex]);
        hadamard(qureg,FirstQubitIndex);
        MeasuredQubitsOutcomes.push_back(measure(qureg,FirstQubitIndex));
        
        
        
        
        
        
        // measure second qubit
        qreal X1;
        //qreal Z1;
        int SecondQubitIndex=1;
        X1 = pow((-1),MeasuredQubitsOutcomes[FirstQubitIndex])*QubitAngles[SecondQubitIndex];
        UpdatedQubitAngles[SecondQubitIndex] = X1;
        rotateZ(qureg,SecondQubitIndex, (-1)*UpdatedQubitAngles[SecondQubitIndex]);
        hadamard(qureg,SecondQubitIndex);
        MeasuredQubitsOutcomes.push_back(measure(qureg,SecondQubitIndex));
        
        //vectUpdatedAngles.push_back(UpdatedQubitAngles);
        lastQubitOutcome.push_back(MeasuredQubitsOutcomes.back());
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

