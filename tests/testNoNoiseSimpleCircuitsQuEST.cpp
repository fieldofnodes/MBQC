/////////////////////////////////////////////////////////////
// Title  : testNoiseModelsQuEST.cpp                       //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : test noise models using QuEST                  //
//        : Use CBQC first then apply to MBQC              //
/////////////////////////////////////////////////////////////
// Include package header file
#include "packages.hpp"


int main(){
    // Set probability
    qreal noProb = -1;
    std::string dataDir;

    std::string outputNoNoiseDir;
    std::string qubitInfo;
    std::string dataPath = "Projects/exploringNoiseInQuEST/data"; 
    outputNoNoiseDir = "no_noise";

    std::vector<std::string> savePaths;
    std::string fileAmp;
    std::string fileProb;
    


    // Run circuits save output to file no damping
    qubitInfo = "applySingleQubitPauliX";
    savePaths = getPaths(dataPath, outputNoNoiseDir, qubitInfo, noProb);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applySingleQubitPauliX(fileAmp,fileProb);
    
    qubitInfo = "applySingleQubitHGate";
    savePaths = getPaths(dataPath, outputNoNoiseDir, qubitInfo, noProb);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applySingleQubitHGate(fileAmp,fileProb);

    qubitInfo = "applyTwoQubitPauliXEachQubit";
    savePaths = getPaths(dataPath, outputNoNoiseDir, qubitInfo, noProb);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyTwoQubitPauliXEachQubit(fileAmp,fileProb);

    qubitInfo = "applyTwoQubitHGateEachQubit";
    savePaths = getPaths(dataPath, outputNoNoiseDir, qubitInfo, noProb);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyTwoQubitHGateEachQubit(fileAmp,fileProb);
    
    qubitInfo = "applyTwoQubitHCZGateBetweenQubit";
    savePaths = getPaths(dataPath, outputNoNoiseDir, qubitInfo, noProb);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyTwoQubitHCZGateBetweenQubit(fileAmp,fileProb);


    return 0;

}







    


