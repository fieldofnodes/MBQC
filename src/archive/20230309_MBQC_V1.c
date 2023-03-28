#include <QuEST.h>
#include <stdio.h>





int main() {
    
    // load QuEST
    QuESTEnv env = createQuESTEnv();
    int numQubits = 3;
    qreal angle = M_PI / 4;
    printf("Angle is measured as %f\n",angle);
     // prepare our register
    Qureg qureg = createQureg(numQubits, env);


    // qureg -> |+><+|
    initPlusState(qureg);  


    // apply CZ gate to entangle the circuit
    controlledPhaseFlip(qureg,0,1);
    controlledPhaseFlip(qureg,1,2);
    controlledPhaseFlip(qureg,0,2);
    
    
    
    printf("Initialising %d qubits\n",numQubits);
    int m0 = measure(qureg,0);
    int m1 = measure(qureg,1);
    int m2 = measure(qureg,2);
    printf("qubit 0 is measured as %d\n",m0);
    printf("qubit 1 is measured as %d\n",m1);
    printf("qubit 2 is measured as %d\n",m2);


}



