/////////////////////////////////////////////////////////////
// Title  : testDampingSimpleCircuitsQuEST.cpp             //
// Author : Jonathan Miller                                //
// Date   : 20230612                                       //
// Aim    : test damping models using QuEST                //
//        : Use CBQC first then apply to MBQC              //
/////////////////////////////////////////////////////////////
// Include package header file
#include "packages.hpp"


int main(){
    // Set probability
 
    qreal prob = 0.1;
    std::string dataDir;

    std::string outputDampingDir;
    std::string qubitInfo;
    std::string dataPath = "Projects/exploringNoiseInQuEST/data"; 
    outputDampingDir = "damping";

    std::vector<std::string> savePaths;
    std::string fileAmp;
    std::string fileProb;
    

    // Damping applied now
    qubitInfo = "applySingleQubitPauliXMixDamping";
    savePaths = getPaths(dataPath, outputDampingDir, qubitInfo, prob);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applySingleQubitPauliXMixDamping(prob,fileAmp,fileProb);

    qubitInfo = "applySingleQubitHGateMixDamping";
    savePaths = getPaths(dataPath, outputDampingDir, qubitInfo, prob);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applySingleQubitHGateMixDamping(prob,fileAmp,fileProb);

    qubitInfo = "applyOnTwoQubitPauliXEachQubitMixDamping";
    savePaths = getPaths(dataPath, outputDampingDir, qubitInfo, prob);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyOnTwoQubitPauliXEachQubitMixDamping(prob,fileAmp,fileProb);

    qubitInfo = "applyOnTwoQubitHGateEachQubitMixDamping";
    savePaths = getPaths(dataPath, outputDampingDir, qubitInfo, prob);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyOnTwoQubitHGateEachQubitMixDamping(prob,fileAmp,fileProb);

    qubitInfo = "applyTwoQubitHCZGateBetweenQubitMixDamping";
    savePaths = getPaths(dataPath, outputDampingDir, qubitInfo, prob);
    fileAmp = savePaths[0];
    fileProb = savePaths[1];
    applyTwoQubitHCZGateBetweenQubitMixDamping(prob,fileAmp,fileProb);

    return 0;



}