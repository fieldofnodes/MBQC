///////////////////////////////////////////////////////////////
// Title  : generalHelperFunctions.hpp                            
// Author : Jonathan Miller                                
// Date   : 20230517                                       
// Aim    : Utility functions to be ord'd                        
//        : The functions:
//        :    + markPosition
//        :    + drawRandomUniformInteger
//        :    + calculateColumnRatios
//        :    + getPaths
//        :    + printVector
//        :    + writeVectorToFile
//        :    + writeArrayToFile
//        :    + writeStateToFile
//        : They perform various tasks such as printing 
//        : values, calculating ratios, writing data to files, 
//        : and obtaining paths.
///////////////////////////////////////////////////////////////








/**
 * \brief Marks the current position.
 *
 * This function marks the current position by printing "Here" to the standard output.
 */
void markPosition() {
    std::cout << "Here" << std::endl;
}






/**
 * \brief Draws a random integer from a uniform distribution within a specified range.
 *
 * \param min The minimum value of the range (inclusive).
 * \param max The maximum value of the range (inclusive).
 * \return A randomly generated integer within the specified range.
 *
 * This function uses the Mersenne Twister pseudo-random number generator to draw a random integer from a uniform distribution
 * within the specified range [min, max]. The minimum and maximum values are inclusive. The function initializes a random device,
 * creates a Mersenne Twister generator, and uses a uniform integer distribution to generate the random number. The generated
 * random integer is then returned.
 */
int drawRandomUniformInteger(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    int randomInt = distribution(generator);
    return randomInt;
}






/**
 * \brief Calculates the ratios of ones in each column of a matrix.
 *
 * \param matrix The matrix for which to calculate the column ratios.
 * \return A vector containing the ratios of ones in each column of the matrix.
 *
 * This function calculates the ratios of ones in each column of the given matrix. It takes a 2D matrix represented by a
 * vector of vectors as input. If the matrix is empty or any of its rows is empty, an empty ratios vector is returned.
 * The function iterates over each column and counts the number of ones in that column. The ratio of ones is calculated
 * by dividing the count by the total number of rows in the matrix. The ratios are stored in a vector, which is then
 * returned.
 *
 * Example usage:
 * \code{.cpp}
 * std::vector<std::vector<int>> matrix = {
 *     {1, 0, 1},
 *     {0, 1, 0},
 *     {1, 1, 1}
 * };
 * std::vector<double> ratios = calculateColumnRatios(matrix);
 * ratios: [0.666667, 0.333333, 0.666667]
 * \endcode
 *
 * \tparam T The type of elements stored in the matrix (should be convertible to int).
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



/**
 * @brief Calculates the outcome probabilities of a single qubit in a quantum register.
 *
 * @param qureg The quantum register.
 * @param qubit The index of the qubit for which to calculate the outcome probabilities.
 * @return A vector containing the outcome probabilities [prob_0, prob_1].
 */
std::vector<qreal> outcomeProbabilitiesSingleQubit(Qureg qureg,int qubit){
    qreal prob_0 = calcProbOfOutcome(qureg,0,0);
    qreal prob_1 = calcProbOfOutcome(qureg,0,1);
    return {prob_0,prob_1};
 }
 



/**
 * @brief Create probability and amplitude paths.
 *
 * This function creates the paths for probability and amplitude files based on the provided parameters.
 *
 * @param dataPath The data path.
 * @param outputDir The output directory.
 * @param qubitInfo The qubit information.
 * @param probability The probability value.
 * @return A vector containing the generated paths for probability and amplitude files.
 */
std::vector<std::string> getPaths(std::string dataPath, std::string outputDir, std::string qubitInfo, qreal probability) {
    const char* homeDir = std::getenv("HOME");
    std::string fslash = "/";
    std::string uscore = "_";
    std::string root = homeDir;
    std::string amps = "amplitudes";
    std::string probs = "probabilities";
    std::string damps;
    std::string csv = ".csv";
    
    
    if(probability < 0){
        damps = "";
    } else{
        int precisionVal = 2;
        std::string prob_str = std::to_string(probability).substr(0, std::to_string(probability).find(".") + precisionVal + 1);
        damps = "mix_damping_prob-"+prob_str;
    }
    
    std::string dataDirPath = homeDir + fslash + dataPath + fslash + outputDir + fslash;
    std::string fileAmp =  dataDirPath + amps + uscore + qubitInfo + uscore + damps + csv;
    std::string fileProb = dataDirPath + probs + uscore + qubitInfo + uscore + damps + csv;

    std::vector<std::string> paths = {fileAmp, fileProb};

    return paths;
}






/**
 * \brief Prints the elements of a vector.
 *
 * \param vec The vector to be printed.
 *
 * This function prints the elements of a given vector to the standard output, separated by spaces. It takes a vector as
 * input and iterates over each element, printing it followed by a space. After printing all the elements, it outputs
 * a newline character to create a new line.
 *
 * Example usage:
 * \code{.cpp}
 * std::vector<int> numbers = {1, 2, 3, 4, 5};
 * printVector(numbers); // Output: 1 2 3 4 5
 * \endcode
 *
 * \tparam T The type of elements stored in the vector.
 */
template<typename T>
void printVector(const std::vector<T>& vec) {
    for (const T& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}






/**
 * \brief Writes the elements of a vector to a file.
 *
 * \param values The vector containing the values to be written.
 * \param filename The name of the file to write the values to.
 * \param col_name The name of the column to be written as a header in the file.
 *
 * This function writes the elements of the given vector to a file. It takes a vector of values, a filename, and a column name as inputs.
 * The function creates a file with the specified filename and writes the column name as a header. Then, it iterates over each element
 * in the vector and writes it to a new line in the file. If the file cannot be opened, an error message is displayed.
 * After writing the values, the file is closed, and a success message is displayed on the standard output.
 *
 * \tparam T The type of elements stored in the vector.
 */
template<typename T>
void writeVectorToFile(const std::vector<T>& values, const std::string& filename,const std::string& col_name) {
    std::ofstream file(filename);
    file << col_name << std::endl;
    if (file.is_open()) {
        for (const T& value : values) {
            file << value << std::endl;
        }
        file.close();
        std::cout << "Values written to file successfully." << std::endl;
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
}






/**
 * \brief Writes the elements of an array to a file.
 *
 * \param values The array containing the values to be written.
 * \param size The size of the array.
 * \param filename The name of the file to write the values to.
 * \param col_name The name of the column to be written as a header in the file.
 *
 * This function writes the elements of the given array to a file. It takes an array of values, the size of the array, a filename,
 * and a column name as inputs. The function creates a file with the specified filename and writes the column name as a header.
 * Then, it iterates over each element in the array and writes it to a new line in the file. If the file cannot be opened,
 * an error message is displayed. After writing the values, the file is closed, and a success message is displayed on the standard output.
 *
 * \tparam T The type of elements stored in the array.
 */
template<typename T>
void writeArrayToFile(const T* values, size_t size, const std::string& filename,const std::string& col_name) {
    std::ofstream file(filename);
    file << col_name << std::endl;
    if (file.is_open()) {
        for (size_t i = 0; i < size; ++i) {
            file << values[i] << std::endl;
        }
        file.close();
        std::cout << "Values written to file successfully." << std::endl;
    } else {
        std::cout << "Unable to open the file." << std::endl;
    }
}






/**
 * \brief Writes the state vector of a quantum register to a file.
 *
 * \param qureg The quantum register whose state vector to write.
 * \param filepath The path of the file to write the state vector to.
 *
 * This function writes the state vector of the given quantum register to a file. It takes a quantum register and a filepath as inputs.
 * The function opens the file in write mode and checks if it was opened successfully. If the file is opened successfully,
 * it writes the real and imaginary parts of each amplitude of the quantum register's state vector to a new line in the file.
 * The format used for writing depends on the precision defined by the `QuEST_PREC` preprocessor macro. After writing the state vector,
 * the file is closed, and a success message is displayed on the standard output. If the file cannot be opened, an error message is displayed.
 *
 * \param qureg The quantum register whose state vector to write.
 * \param filepath The path of the file to write the state vector to.
 */
void writeStateToFile(const Qureg& qureg, const std::string& filepath) {
    FILE* state = std::fopen(filepath.c_str(), "w");
    long long int index;
    if (state == nullptr) {
        std::perror("Failed to open file");
        return;
    }

    if (qureg.chunkId == 0) {
        std::fprintf(state, "real, imag\n");
    }

     for(index=0; index<qureg.numAmpsPerChunk; index++){
         # if QuEST_PREC==1 || QuEST_PREC==2
         fprintf(state, "%.12f, %.12f\n", qureg.stateVec.real[index], qureg.stateVec.imag[index]);
         # elif QuEST_PREC == 4
         fprintf(state, "%.12Lf, %.12Lf\n", qureg.stateVec.real[index], qureg.stateVec.imag[index]);
         #endif
     }
     fclose(state);
     std::cout << "Values written to file successfully." << std::endl;
}






