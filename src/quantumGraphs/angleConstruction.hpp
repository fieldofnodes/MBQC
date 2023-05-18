/////////////////////////////////////////////////////////////
// Title  : angleConstruction.hpp                          //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct angles                               //
/////////////////////////////////////////////////////////////



/*
    Initialise a vector of `qreal` values all set to 0.0
*/
std::vector<qreal> initAllAnglesZero(int numQubits){
    std::vector<qreal> qubitAngles(numQubits,0.0); 
    return qubitAngles;
}


/*
    Initialise a vector of `qreal` values all set to some same `angle`
*/
std::vector<qreal> initAllAnglesSame(int numQubits, qreal angle){
    std::vector<qreal> qubitAngles(numQubits,angle); 
    return qubitAngles;
}


/*
    Initialise a vector of `qreal` values all set to a random fraction
    X*M_PI/piDenominator: X ~ Uniform(0,2*piDenominator)
*/
std::vector<qreal> initRandomPiOnNAngles(int numQubits, int piDenominator){
    
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2*piDenominator - 1;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    for(int i=0; i < numQubits; i++){
        double numer = 1.0 * drawRandomUniformInteger(min,max); 
        qreal angle = (double)(numer/piDenominator) * M_PI;
        qubitAngles[i] = angle;
    } 
    
    return qubitAngles;
}




/*
    Initialise a vector of `qreal` values all set to a random fraction
    X*M_PI/piDenominator: X ~ Uniform(0,2*piDenominator)
    The sum of X*M_PI/piDenominator is a multiple of 2M_PI
*/
std::vector<qreal> initRandomPiOnNAnglesMod2kPi(int numQubits, int piDenominator){
    
    
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2*piDenominator - 1;
    int totalPositions = 2*piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for(int i=0; i < numQubits-1; i++){
        double numer = 1.0 * drawRandomUniformInteger(min,max); 
        numeratorVector[i] = numer;
        qreal angle = (double)(numer/piDenominator) * M_PI;
        qubitAngles[i] = angle;
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




/*
    Initialise a vector of `qreal` values all set to a random fraction
    X*M_PI/piDenominator: X ~ Uniform(0,2*piDenominator)
    The sum of X*M_PI/piDenominator is a multiple of 
    2M_PI + M_PI
*/
std::vector<qreal> initRandomPiOnNAnglesMod2kPiPlusPi(int numQubits, int piDenominator){
    
    
    // Create a uniform distribution for the range
    int min = 0;
    int max = 2*piDenominator - 1;
    int totalPositions = 2*piDenominator;
    
    // Populate angle vector
    std::vector<qreal> qubitAngles(numQubits);
    std::vector<int> numeratorVector(numQubits);
    for(int i=0; i < numQubits-1; i++){
        double numer = 1.0 * drawRandomUniformInteger(min,max); 
        numeratorVector[i] = numer;
        qreal angle = (double)(numer/piDenominator) * M_PI;
        qubitAngles[i] = angle;
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

/*
    Apply rotation of angle to qureg
*/
void addAngleRotateZgate(Qureg qureg, std::vector<qreal> qubitAngles){
    for (int i =0; i < qureg.numQubitsRepresented; i++){
        rotateZ (qureg, i, qubitAngles[i]);
    }
}

/*
    Every other angle is (elements: 1,3,5,...) 0
    Total sum of anlges is multiple of 2pi
*/
std::vector<qreal> initRandomPiOnNEveryOtherAnglesMod2kPi(int numQubits, int piDenominator){
    
    
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


/*
    Every other angle is (elements: 1,3,5,...) 0
    Total sum of anlges is multiple of 2pi + pi
*/
std::vector<qreal> initRandomPiOnNEveryOtherAnglesMod2kPiPlusPi(int numQubits, int piDenominator){
    
    
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


