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
    vector<int> allLastQubitZero;
    int numberRealisations = 1E6;
    int totalQubitNumberIter = 6;
    for(int j=1;j<totalQubitNumberIter;j++)
    {
        int qubitNumber=2*j + 1;
        for(int i=0;i<numberRealisations;i++)
        {  
            QuESTEnv env = createQuESTEnv();
            // set parameters
            int NumberQubits = qubitNumber;//11;
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
                QubitAngles.push_back(0.0); 

            
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
            
            
            for(int CurrentQubit=2;CurrentQubit<NumberQubits;CurrentQubit++)
                {       
                    qreal X;
                    qreal Z;
                    //qreal phi;
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
                    
                    MeasuredQubitsOutcomes.push_back(outcome);
                    
                }

            lastQubitOutcome.push_back(MeasuredQubitsOutcomes.back());
            
        }

        // Confirm all of the last qubits are 0
        if ( std::all_of(
                lastQubitOutcome.begin(), 
                lastQubitOutcome.end(), 
                [](int i){return i==0;}))
                {
                    std::cout << "All the elements on " << qubitNumber << " qubits are 0.\n";
                    allLastQubitZero.push_back(1);
                }
        

    }
    if ( std::all_of(
                allLastQubitZero.begin(), 
                allLastQubitZero.end(), 
                [](int i){return i==1;}))
                {
                    std::cout << "All the odd number qubits circuits returned last qubit as 0.\n";
                }
}

  

