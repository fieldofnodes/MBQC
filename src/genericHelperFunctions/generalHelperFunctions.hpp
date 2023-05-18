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

/*
  Print vector to screen
*/
template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const T& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}





/*
  Get ratio columns in matrix equal to 1
*/

std::vector<double> calculateColumnRatios(const std::vector<std::vector<int>>& matrix) {
    std::vector<double> ratios;

    if (matrix.empty() || matrix[0].empty()) {
        return ratios;  // Empty matrix, return empty ratios vector
    }

    const int numRows = matrix.size();
    const int numCols = matrix[0].size();

    for (int col = 0; col < numCols; col++) {
        int count = 0;
        for (int row = 0; row < numRows; row++) {
            if (matrix[row][col] == 1) {
                count++;
            }
        }
        double ratio = static_cast<double>(count) / numRows;
        ratios.push_back(ratio);
    }

    return ratios;
}