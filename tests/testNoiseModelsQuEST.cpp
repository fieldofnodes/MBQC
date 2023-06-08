/////////////////////////////////////////////////////////////
// Title  : testNoiseModelsQuEST.cpp                       //
// Author : Jonathan Miller                                //
// Date   : 20230503                                       //
// Aim    : test noise models using QuEST                  //
//        : Use CBQC first then apply to MBQC              //
/////////////////////////////////////////////////////////////
// Include package header file
#include "packages.hpp"



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

void applySingleQubitPauliX(){
    int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);
    
    // Apply details to circuit
    pauliX(qureg,0);
    
    // Write amplitudes to file
    std::string file_amp = "/Users/jmille15/Projects/exploringNoiseInQuEST/data/amplitudes_single_qubit-X.csv";
    writeStateToFile(qureg,file_amp);


    // Compute probabilites
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[1<<numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    // Write probabilities to file
    std::string file_prob = "/Users/jmille15/Projects/exploringNoiseInQuEST/data/probabilities_single_qubit-X.csv";
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, file_prob,col_name);
}


void applyMixDampingOnSingleQubitPauliX(qreal prob){
    int numQubits = 1;
    // load QuEST environment
    QuESTEnv env = createQuESTEnv();
    
    // Create qureg
    Qureg qureg = createDensityQureg(numQubits, env);

    // Apply elements to circuit
    pauliX(qureg,0);
    mixDamping(qureg,0,prob);
    
    // Write amplitudes to file
    std::string file_amp = "/Users/jmille15/Projects/exploringNoiseInQuEST/data/amplitudes_single_qubit-X_mix_damping_prob-0.1.csv";
    writeStateToFile(qureg,file_amp);



    // Compute probabilities
    int numProbs = 1<<numQubits;
    qreal outcomeProbs[numProbs];
    int qubits[] = {0};
    calcProbOfAllOutcomes(outcomeProbs,qureg,qubits,numQubits);	    
    
    
    // Write probabilities to file
    std::string file_prob = "/Users/jmille15/Projects/exploringNoiseInQuEST/data/probabilities_single_qubit-X_mix_damping_prob-0.1.csv";
    std::string col_name = "probabilities";
    writeArrayToFile(outcomeProbs, numProbs, file_prob,col_name);

    
}

int main(){
    applySingleQubitPauliX();
    qreal prob = 0.1;
    applyMixDampingOnSingleQubitPauliX(prob);

    return 0;
}





