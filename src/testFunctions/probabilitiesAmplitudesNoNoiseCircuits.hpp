/////////////////////////////////////////////////////////////
// Title  : probabilitiesAmplitudesNoNoiseCircuits.hpp     //
// Author : Jonathan Miller                                //
// Date   : 20230613                                       //
// Aim    : Function that apply gates on                   //
//        : single and double qubit circuits               //
//        : no noise applied                               //
/////////////////////////////////////////////////////////////


// Density matrix with no damping noise 
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

