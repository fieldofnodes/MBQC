/////////////////////////////////////////////////////////////
// Title  : generalHelperFunctions.hpp                            //
// Author : Jonathan Miller                                //
// Date   : 20230517                                       //
// Aim    : Un-organised functions                         //
//        : Purpose is to provide general assistance       //
/////////////////////////////////////////////////////////////


/*
    Debug function to print to screen when function is called
*/
void markPosition(){
  std::cout << "Here" << std::endl;
}

/*
 Draw a random uniform integer X~U(min,max)
*/
int drawRandomUniformInteger(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    int randomInt = distribution(generator);
    return randomInt;
}
