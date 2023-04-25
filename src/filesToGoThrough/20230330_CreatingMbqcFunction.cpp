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
        // Create QuEST environment
        QuESTEnv env = createQuESTEnv();
        // set parameters
        int numberQubits = qubitNumber;
        // prepare our register
        Qureg qureg = createQureg(numberQubits, env);
        // qureg -> |+><+|
        initPlusState(qureg);  

        // Create a vector representing a linear cluster graph
        vector<int> pathGraph = getPathGraph(numberQubits); 
        
        vector<qreal> qubitAngles;
        
        

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
        

        vector<int> outcomes = runMbqcPathGraph(qureg,pathGraph,qubitAngles);

        for(int i: outcomes){
            cout << i << " ";
        }
    }


/*
            // Run MBQC
            // measure first qubit
            
            
            
            


            lastQubitOutcome.push_back(measuredQubitsOutcomes.back());
            
        }

        for(int i:lastQubitOutcome){
            cout << i << " ";
        } 

        // Confirm all of the last qubits are 0
        if ( std::all_of(
                lastQubitOutcome.begin(), 
                lastQubitOutcome.end(), 
                [](int i){return i==0;}))
                {
                    std::cout << "All the elements on " << qubitNumber << " qubits are 1.\n";
                    allLastQubitZero.push_back(1);
                }
      */
}

