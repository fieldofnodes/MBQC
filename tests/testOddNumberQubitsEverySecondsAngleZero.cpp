
/////////////////////////////////////////////////////////////
// Title  : testOddNumberQubitsEverySecondsAngleZero.cpp   //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : Basic start file to run mbqc                   //
//        : Current implementation can only do square      //
//        : graph repeatedly. Will branch repo to make     //
//        : use different way to create graph by           //
//        : adjacency                                      //
/////////////////////////////////////////////////////////////

// Include package header file
#include "packages.hpp"



// Set up the main function
int main() {
    
    for (int i = 0;i < 1e6;i++){
        testEveryOtherAnlgeZeroResults(0,4,7);
        testEveryOtherAnlgeZeroResults(1,4,7);
    }
 
    return 0;
}





