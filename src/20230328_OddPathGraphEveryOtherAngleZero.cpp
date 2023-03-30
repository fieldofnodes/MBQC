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
    int numberRealisations = 1;
    int qubitNumber=5;

    

    
        for(int i=0;i<numberRealisations;i++)
        {  
            QuESTEnv env = createQuESTEnv();
            // set parameters
            int numberQubits = qubitNumber;//11;
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
            for(int i=0;i<numberQubits;i++){
                if(i % 2 == 0){
                    qubitAngles.push_back(2*M_PI);
                } else {
                    qubitAngles.push_back(0.0); 
                }
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
            
            
            for(int currentQubit=2;currentQubit<numberQubits;currentQubit++)
                {       
                    qreal X;
                    qreal Z;
                    //qreal phi;
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

            lastQubitOutcome.push_back(measuredQubitsOutcomes.back());
            
        }
/*
        for(int i:lastQubitOutcome){
            cout << i << " ";
        } */

        // Confirm all of the last qubits are 0
        if ( std::all_of(
                lastQubitOutcome.begin(), 
                lastQubitOutcome.end(), 
                [](int i){return i==0;}))
                {
                    std::cout << "All the elements on " << qubitNumber << " qubits are 1.\n";
                    allLastQubitZero.push_back(1);
                }
      
}


  
someType runMbqcPathGraph(
    Qureg qureg,
    vector<int> pathGraph,
    vector<qreal> qubitAngles)

