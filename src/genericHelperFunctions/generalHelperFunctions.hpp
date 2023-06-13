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