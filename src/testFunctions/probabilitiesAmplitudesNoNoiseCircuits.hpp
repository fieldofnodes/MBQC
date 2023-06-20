/////////////////////////////////////////////////////////////
// Title  : probabilitiesAmplitudesNoNoiseCircuits.hpp     //
// Author : Jonathan Miller                                //
// Date   : 20230613                                       //
// Aim    : Function that apply gates on                   //
//        : single and double qubit circuits               //
//        : no noise applied                               //
/////////////////////////////////////////////////////////////


/**
 * Apply single-qubit Pauli-X gate to the quantum state without any damping noise.
 *
 * @param fileAmp The file to write the amplitudes of the quantum state.
 * @param fileProb The file to write the probabilities of the quantum state.
 */
void applySingleQubitPauliX(std::string fileAmp,std::string fileProb){
    int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);
    
    // Apply details to circuit
    pauliX(qureg,0);
    
    
    writeStateToFile(qureg,fileAmp);


    // Compute probabilites
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[1<<numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}





/**
 * Apply single-qubit Hadamard gate to the quantum state without any damping noise.
 *
 * @param fileAmp The file to write the amplitudes of the quantum state.
 * @param fileProb The file to write the probabilities of the quantum state.
 */
void applySingleQubitHGate(std::string fileAmp,std::string fileProb){
        int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);
    
    // Apply details to circuit
    hadamard(qureg,0);
    
    
    writeStateToFile(qureg,fileAmp);


    // Compute probabilites
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[1<<numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}


/**
 * Apply Pauli-X gate to each qubit of a two-qubit system without any damping noise.
 *
 * @param fileAmp The file to write the amplitudes of the quantum state.
 * @param fileProb The file to write the probabilities of the quantum state.
 */
void applyTwoQubitPauliXEachQubit(std::string fileAmp,std::string fileProb){
    int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);
    
    // Apply details to circuit
    pauliX(qureg,0);
    pauliX(qureg,1);
    
    
    writeStateToFile(qureg,fileAmp);


    // Compute probabilites
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[1<<numProbs];
    int qubits[] = {0,1};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}




/**
 * Apply Hadamard gate to each qubit of a two-qubit system without any damping noise.
 *
 * @param fileAmp The file to write the amplitudes of the quantum state.
 * @param fileProb The file to write the probabilities of the quantum state.
 */
void applyTwoQubitHGateEachQubit(std::string fileAmp,std::string fileProb){
    int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);
    
    // Apply details to circuit
    hadamard(qureg,0);
    hadamard(qureg,1);
    
    
    writeStateToFile(qureg,fileAmp);


    // Compute probabilites
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[1<<numProbs];
    int qubits[] = {0,1};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}


/**
 * Apply Hadamard gate to each qubit of a two-qubit system, and a controlled phase flip gate between the qubits,
 * without any damping noise.
 *
 * @param fileAmp The file to write the amplitudes of the quantum state.
 * @param fileProb The file to write the probabilities of the quantum state.
 */
void applyTwoQubitHCZGateBetweenQubit(std::string fileAmp,std::string fileProb){
            int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    hadamard(qureg,0);
    hadamard(qureg,1);
    controlledPhaseFlip(qureg,0,1);
    
    
    // Write amplitudes to file
    writeStateToFile(qureg,fileAmp);

    // Compute probabilities
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[numProbs];
    int qubits[] = {0,1};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
}

