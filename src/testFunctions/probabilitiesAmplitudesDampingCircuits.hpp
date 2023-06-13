/////////////////////////////////////////////////////////////
// Title  : probabilitiesAmplitudesNoNoiseCircuits.hpp     //
// Author : Jonathan Miller                                //
// Date   : 20230613                                       //
// Aim    : Function that apply gates on                   //
//        : single and double qubit circuits               //
//        : damping
/////////////////////////////////////////////////////////////

void applySingleQubitPauliXMixDamping(qreal prob,std::string fileAmp,std::string fileProb){
    int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    pauliX(qureg,0);
    mixDamping(qureg,0,prob);
    
    // Write amplitudes to file
    writeStateToFile(qureg,fileAmp);

    // Compute probabilities
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    
}
void applySingleQubitHGateMixDamping(qreal prob,std::string fileAmp,std::string fileProb){
    int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    hadamard(qureg,0);
    mixDamping(qureg,0,prob);
    
    // Write amplitudes to file
    writeStateToFile(qureg,fileAmp);

    // Compute probabilities
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, fileProb,col_name);

    // unload QuEST
    destroyQureg(qureg, env); 
    destroyQuESTEnv(env);
    
}
void applyOnTwoQubitPauliXEachQubitMixDamping(qreal prob,std::string fileAmp,std::string fileProb){
    int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    pauliX(qureg,0);
    pauliX(qureg,1);
    mixDamping(qureg,0,prob);
    mixDamping(qureg,1,prob);
    
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
void applyOnTwoQubitHGateEachQubitMixDamping(qreal prob,std::string fileAmp,std::string fileProb){
        int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    hadamard(qureg,0);
    hadamard(qureg,1);
    mixDamping(qureg,0,prob);
    mixDamping(qureg,1,prob);
    
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
void applyTwoQubitHCZGateBetweenQubitMixDamping(qreal prob,std::string fileAmp,std::string fileProb){
            int numQubits = 2;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    hadamard(qureg,0);
    hadamard(qureg,1);
    controlledPhaseFlip(qureg,0,1);
    mixDamping(qureg,0,prob);
    mixDamping(qureg,1,prob);
    
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
