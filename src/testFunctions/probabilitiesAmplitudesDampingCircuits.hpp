/////////////////////////////////////////////////////////////
// Title  : probabilitiesAmplitudesNoNoiseCircuits.hpp     //
// Author : Jonathan Miller                                //
// Date   : 20230613                                       //
// Aim    : Function that apply gates on                   //
//        : single and double qubit circuits               //
//        : damping
/////////////////////////////////////////////////////////////


/**
 * @brief Applies a single-qubit Pauli-X gate followed by mix damping to a quantum system.
 *
 * The function applies a Pauli-X gate followed by mix damping to the specified qubit of the quantum system. It then writes the amplitudes and probabilities of the quantum system to the specified files.
 *
 * @param prob The probability of mix damping.
 * @param fileAmp The file path to write the amplitudes.
 * @param fileProb The file path to write the probabilities.
 */
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

/**
 * @brief Applies a single-qubit Hadamard gate followed by mix damping to a quantum system.
 *
 * The function applies a Hadamard gate followed by mix damping to the specified qubit of the quantum system. It then writes the amplitudes and probabilities of the quantum system to the specified files.
 *
 * @param prob The probability of mix damping.
 * @param fileAmp The file path to write the amplitudes.
 * @param fileProb The file path to write the probabilities.
 */
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




/**
 * @brief Applies Pauli-X gates followed by mix damping to each qubit of a two-qubit quantum system.
 *
 * The function applies Pauli-X gates followed by mix damping to each qubit of the two-qubit quantum system. It then writes the amplitudes and probabilities of the quantum system to the specified files.
 *
 * @param prob The probability of mix damping.
 * @param fileAmp The file path to write the amplitudes.
 * @param fileProb The file path to write the probabilities.
 */
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

/**
 * @brief Applies Hadamard gates followed by mix damping to each qubit of a two-qubit quantum system.
 *
 * The function applies Hadamard gates followed by mix damping to each qubit of the two-qubit quantum system. It then writes the amplitudes and probabilities of the quantum system to the specified files.
 *
 * @param prob The probability of mix damping.
 * @param fileAmp The file path to write the amplitudes.
 * @param fileProb The file path to write the probabilities.
 */
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


/**
 * @brief Applies a controlled-Z gate followed by mix damping to two qubits of a two-qubit quantum system.
 *
 * The function applies a controlled-Z gate followed by mix damping to the specified two qubits of the two-qubit quantum system. It then writes the amplitudes and probabilities of the quantum system to the specified files.
 *
 * @param prob The probability of mix damping.
 * @param fileAmp The file path to write the amplitudes.
 * @param fileProb The file path to write the probabilities.
 */
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










