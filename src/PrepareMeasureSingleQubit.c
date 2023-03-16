#include <QuEST.h>
#include <stdio.h>







int main() {
    
    // load QuEST
    QuESTEnv env = createQuESTEnv();
    int numQubits = 2;
    

     // prepare our register
    Qureg qureg = createQureg(numQubits, env);


    // qureg -> |+><+|
    initPlusState(qureg);  

    printf("Initialising %d qubits\n",numQubits);
    int m0 = measure(qureg,0);

    
    int m1 = measure(qureg,1);
    printf("qubit 0 is measured as %d\n",m0);
    printf("qubit 1 is measured as %d\n",m1);

    
    double *qsr = qureg.stateVec.imag;
    printf("qureg.stateVec.real is %f\n",*qsr);

    int numqubits = Qureg.numQubitsRepresented(qureg);
    printf("Number of qubits in quantum register is %d\n",numqubits);

}


