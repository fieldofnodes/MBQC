/////////////////////////////////////////////////////////////
// Title  : angleConstruction.hpp                          //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct angles                               //
/////////////////////////////////////////////////////////////




/**
 * @brief Initializes a vector of qreal values with all angles set to 0.0.
 *
 * This function creates a vector of qreal values with a size of `numQubits`,
 * where each element is initialized to 0.0.
 *
 * @param numQubits The number of qubits.
 * @return A vector of qreal values with all angles set to 0.0.
 */
std::vector<qreal> initAllAnglesZero(int numQubits) {
    std::vector<qreal> qubitAngles(numQubits, 0.0);
    return qubitAngles;
}



/**
 * @brief Initializes a vector of qreal values with all angles set to the same value.
 *
 * This function creates a vector of qreal values with a size of `numQubits`,
 * where each element is initialized to the specified `angle`.
 *
 * @param numQubits The number of qubits.
 * @param angle The angle value to set for all elements.
 * @return A vector of qreal values with all angles set to the same value.
 */
std::vector<qreal> initAllAnglesSame(int numQubits, qreal angle) {
    std::vector<qreal> qubitAngles(numQubits, angle);
    return qubitAngles;
}



/**
 * @brief Initializes a vector of qreal values with random angles.
 *
 * This function creates a vector of qreal values with a size of `numQubits`,
 * where each element is initialized to a random fraction of X*M_PI/piDenominator,
 * where X is uniformly distributed in the range [0, 2*piDenominator).
 *
 * @param numQubits The number of qubits.
 * @param piDenominator The denominator value used to generate the random angles.
 * @return A vector of qreal values with randomly generated angles.
 */
std::vector<qreal> initRandomPiOnNAngles(int numQubits, int piDenominator) {
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2 * piDenominator - 1;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    for (int i = 0; i < numQubits; i++) {
        double numer = 1.0 * drawRandomUniformInteger(min, max);
        qreal angle = (double)(numer / piDenominator) * M_PI;
        qubitAngles[i] = angle;
    }
    
    return qubitAngles;
}





/**
 * @brief Initializes a vector of qreal values with random angles that sum to a multiple of 2M_PI.
 *
 * This function creates a vector of qreal values with a size of `numQubits`,
 * where each element is initialized to a random fraction of X*M_PI/piDenominator,
 * where X is uniformly distributed in the range [0, 2*piDenominator).
 * The sum of the random fractions is adjusted to be a multiple of 2M_PI.
 *
 * @param numQubits The number of qubits.
 * @param piDenominator The denominator value used to generate the random angles.
 * @return A vector of qreal values with randomly generated angles that sum to a multiple of 2M_PI.
 * @pre The sum of the random fractions must be a multiple of 2M_PI.
 * @post The last element of the vector is adjusted to satisfy the sum requirement.
 */
std::vector<qreal> initRandomPiOnNAnglesMod2kPi(int numQubits, int piDenominator) {
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2 * piDenominator - 1;
    int totalPositions = 2 * piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for (int i = 0; i < numQubits - 1; i++) {
        double numer = 1.0 * drawRandomUniformInteger(min, max);
        numeratorVector[i] = numer;
        qreal angle = (double)(numer / piDenominator) * M_PI;
        qubitAngles[i] = angle;
    }
    
    // Compute sum of random numerators
    int totalNumerator = std::accumulate(numeratorVector.begin(), numeratorVector.end(), 0);
    
    // Calculate remaining positions
    int remainingPositions = totalPositions - (totalNumerator % totalPositions);
    int totalNumeratorAndRemainingModPositions = (remainingPositions + totalNumerator) % totalPositions;
    
    assert((totalNumeratorAndRemainingModPositions == 0) && "Total numerator values should be mod total positions equal to 0, indicating a 2kPi multiple");
    
    qreal finalAngle = (1.0) * (remainingPositions / piDenominator) * M_PI;
    qubitAngles[numQubits - 1] = finalAngle;
    
    return qubitAngles;
}





/**
 * @brief Initializes a vector of qreal values with random angles that sum to a multiple of (2M_PI + M_PI).
 *
 * This function creates a vector of qreal values with a size of `numQubits`,
 * where each element is initialized to a random fraction of X*M_PI/piDenominator,
 * where X is uniformly distributed in the range [0, 2*piDenominator).
 * The sum of the random fractions is adjusted to be a multiple of (2M_PI + M_PI).
 *
 * @param numQubits The number of qubits.
 * @param piDenominator The denominator value used to generate the random angles.
 * @return A vector of qreal values with randomly generated angles that sum to a multiple of (2M_PI + M_PI).
 * @pre The sum of the random fractions must be a multiple of (2M_PI + M_PI).
 * @post The last element of the vector is adjusted to satisfy the sum requirement.
 */
std::vector<qreal> initRandomPiOnNAnglesMod2kPiPlusPi(int numQubits, int piDenominator) {
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2 * piDenominator - 1;
    int totalPositions = 2 * piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for (int i = 0; i < numQubits - 1; i++) {
        double numer = 1.0 * drawRandomUniformInteger(min, max);
        numeratorVector[i] = numer;
        qreal angle = (double)(numer / piDenominator) * M_PI;
        qubitAngles[i] = angle;
    }
    
    // Compute sum of random numerators
    int totalNumerator = std::accumulate(numeratorVector.begin(), numeratorVector.end(), 0);
    
    // Calculate remaining positions
    int remainingPositions = totalPositions - (totalNumerator % totalPositions);
    int totalNumeratorAndRemainingModPositions = (remainingPositions + totalNumerator) % totalPositions;
    
    assert((totalNumeratorAndRemainingModPositions == 0) && "Total numerator values should be mod total positions equal to 0, indicating a 2kPi multiple");
    
    qreal finalAngle = (1.0) * (remainingPositions / piDenominator) * M_PI + M_PI;
    qubitAngles[numQubits - 1] = finalAngle;
    
    return qubitAngles;
}



/**
 * @brief Applies rotation gates to a quantum register based on the provided qubit angles.
 *
 * This function applies rotation gates to each qubit in the given quantum register `qureg`,
 * using the corresponding angle from the `qubitAngles` vector. The rotation gate applied is
 * the Z-rotation gate with the angle specified by `qubitAngles[i]` applied to the `i`-th qubit.
 *
 * @param qureg The quantum register to apply the rotation gates to.
 * @param qubitAngles A vector of qreal values representing the rotation angles for each qubit.
 * @pre The size of `qubitAngles` must be equal to or smaller than the number of qubits represented by `qureg`.
 */
void addAngleRotateZgate(Qureg qureg, std::vector<qreal> qubitAngles) {
    /*
    Apply rotation of angle to qureg
    */
    for (int i = 0; i < qureg.numQubitsRepresented; i++) {
        rotateZ(qureg, i, qubitAngles[i]);
    }
}



/**
 * @brief Initializes a vector of `qreal` values with random angles, where every other angle is set to 0.
 *
 * This function initializes a vector of `qreal` values, `qubitAngles`, with random angles between 0 and 2π,
 * where every other angle (elements at indices 1, 3, 5, ...) is set to 0. The total sum of angles is a multiple of 2π.
 *
 * @param numQubits The number of qubits to generate angles for.
 * @param piDenominator The denominator used for generating the angles.
 * @return A vector of `qreal` values representing the generated angles.
 * @pre `numQubits` must be greater than 1.
 * @pre `piDenominator` must be greater than 0.
 */
std::vector<qreal> initRandomPiOnNEveryOtherAnglesMod2kPi(int numQubits, int piDenominator){
    
    /*
    Every other angle is (elements: 1,3,5,...) 0
    Total sum of anlges is multiple of 2pi
*/
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2*piDenominator - 1;
    int totalPositions = 2*piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for(int i=0; i < numQubits-1; i++){
        if(i%2==0){
            double numer = 1.0 * drawRandomUniformInteger(min+1,max); 
            numeratorVector[i] = numer;
            qreal angle = (double)(numer/piDenominator) * M_PI;
            qubitAngles[i] = angle;
        }else if(i%2==1){
            qubitAngles[i] = 0.0;
        }else{
            //nothing
        }
        
    } 
  
    // Compute some of random numerators
    int totalNumerator = std::accumulate(numeratorVector.begin(), numeratorVector.end(), 0);

    // Get remainingPositions
    int remainingPositions = totalPositions - (totalNumerator % totalPositions);
    int totalNumeratorAndRemainingModPositions = (remainingPositions + totalNumerator) % totalPositions;
    
    assert((totalNumeratorAndRemainingModPositions == 0) && "Total numerator values should be  mod total positions equal to 0, indicating 2kPi multiple");

    qreal finalAngle = (1.0)*(remainingPositions/piDenominator)*M_PI;
    qubitAngles[numQubits-1] = finalAngle;


    return qubitAngles;
    
}



/**
 * @brief Initializes a vector of `qreal` values with random angles, where every other angle is set to 0.
 *
 * This function initializes a vector of `qreal` values, `qubitAngles`, with random angles between 0 and 2π,
 * where every other angle (elements at indices 1, 3, 5, ...) is set to 0. The total sum of angles is a multiple of 2π + π.
 *
 * @param numQubits The number of qubits to generate angles for.
 * @param piDenominator The denominator used for generating the angles.
 * @return A vector of `qreal` values representing the generated angles.
 * @pre `numQubits` must be greater than 1.
 * @pre `piDenominator` must be greater than 0.
 */
std::vector<qreal> initRandomPiOnNEveryOtherAnglesMod2kPiPlusPi(int numQubits, int piDenominator){
    /*
        Every other angle is (elements: 1,3,5,...) 0
        Total sum of anlges is multiple of 2pi + pi
    */    
    
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2*piDenominator - 1;
    int totalPositions = 2*piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for(int i=0; i < numQubits-1; i++){
        if(i%2==0){
            double numer = 1.0 * drawRandomUniformInteger(min+1,max); 
            numeratorVector[i] = numer;
            qreal angle = (double)(numer/piDenominator) * M_PI;
            qubitAngles[i] = angle;
        }else if(i%2==1){
            qubitAngles[i] = 0.0;
        }else{
            //nothing
        }
    } 
  
    // Compute some of random numerators
    int totalNumerator = std::accumulate(numeratorVector.begin(), numeratorVector.end(), 0);

    // Get remainingPositions
    int remainingPositions = totalPositions - (totalNumerator % totalPositions);
    int totalNumeratorAndRemainingModPositions = (remainingPositions + totalNumerator) % totalPositions;
    
    assert((totalNumeratorAndRemainingModPositions == 0) && "Total numerator values should be  mod total positions equal to 0, indicating 2kPi multiple");

    qreal finalAngle = (1.0)*(remainingPositions/piDenominator)*M_PI + M_PI;
    qubitAngles[numQubits-1] = finalAngle;

    
    
    
    return qubitAngles;
    
}


