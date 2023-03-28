//////////////////////////////////////////////////////////////////////
// Title     : Three qubit in a line entangled
// Author    : Jonathan Miller
// Date      : 20230309
// Aim       : Implement a simple MBQC circuit for ()-()-() circuit
// Flow      : Same row, next column; 
//           : f(0) = 1, f(1) = 2, f(2) = 3
//           : f-1(3) = 2, f-1(2) = 1, f-1(1) = 0

#include <QuEST.h>
#include <stdio.h>





int main() {
    
    // load QuEST
    QuESTEnv env = createQuESTEnv();
    
    // set number of qubits
    int numQubits = 3;
    int qubits[] = {0,1,2};
    
    qreal outcomeProbs[1<<numQubits];

   // Declare angle array and measure qubit array
	qreal angles[numQubits]; 
    int measured_qubits[numQubits];
    
    // set initial angles
	for(int i=0;i<numQubits;i++)
	    angles[i] = M_PI / 4; 
	
    // prepare our register
    Qureg qureg = createQureg(numQubits, env);


    // qureg -> |+><+|
    initPlusState(qureg);  
    
    // apply CZ gate to entangle the circuit
    controlledPhaseFlip(qureg,0,1);
    controlledPhaseFlip(qureg,1,2);

    // measure first qubit
    // ()-()-() -> X-()-(), for X being a removed qubit
    rotateZ(qureg,0, angles[0]);
    hadamard(qureg,0);
    int s0 = measure(qureg,0);
    measured_qubits[0] = s0;
    printf("first angle is %f\n",angles[0]);
    printf("first qubit measure is %d\n",s0);


    // update second angle
    int sum_neigh_meas_q0 = 0;
    qreal x_correction_q1 = pow(-1, s0)*angles[1];
    qreal z_correction_q1 = M_PI*(sum_neigh_meas_q0);
    qreal updated_angle_q1 = x_correction_q1 + z_correction_q1;

    // measure second qubit
    // X-()-() -> X-X-(), for X being a removed qubit
    rotateZ(qureg,1, (-1)*updated_angle_q1);
    hadamard(qureg,1);
    int s1 = measure(qureg,1);
    measured_qubits[1] = s1;
    printf("Original second angle is %f\n",angles[1]);
    printf("Updated second angle is %f\n",updated_angle_q1);
    printf("Second qubit measure is %d\n",s1);


    // update third angle
    int sum_neigh_meas_q1 = s0;
    qreal x_correction_q2 = pow(-1, s1)*angles[2];
    qreal z_correction_q2 = M_PI*(sum_neigh_meas_q1);
    qreal updated_angle_q2 = x_correction_q2 + z_correction_q2;

    // measure third qubit
    // X-X-() -> X-X-X, for X being a removed qubit
    rotateZ(qureg,2, (-1)*updated_angle_q2);
    hadamard(qureg,2);
    int s2 = measure(qureg,2);
    measured_qubits[2] = s2;
    printf("Original third angle is %f\n",angles[2]);
    printf("Updated third angle is %f\n",updated_angle_q2);
    printf("Third qubit measure is %d\n",s2);




    //calcProbOfAllOutcomes(outcomeProbs, qureg, qubits, numQubits);
    qreal prob;
    for (int i = 0; i < numQubits; i++)
    {
        prob = calcProbOfOutcome(qureg,i,0);
        printf("Probability: %f\n ", prob);
    }


    // Print measured qubit vector
    printf("Measured array:");
    for(int loop = 0; loop < numQubits; loop++)
      printf("%d ", measured_qubits[loop]);
    
}





