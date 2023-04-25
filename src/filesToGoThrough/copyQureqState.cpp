#include <QuEST.h>

int main() {
    // Create a quantum register with 3 qubits
    QuESTEnv env = createQuESTEnv();
    Qureg qubits = createQureg(3, env);

    // Perform operations on the qubits

    // Measure the second qubit
    int measurementOutcome = measure(qubits, 1);

    // Create a new register with 4 qubits
    Qureg newQubits = createQureg(4, env);

    // Copy the state of the old register onto the new one
    copyState(qubits, newQubits);

    // Destroy the old register
    destroyQureg(qubits, env);

    // Perform operations on the new register

    // Destroy the new register
    destroyQureg(newQubits, env);

    // Destroy the environment
    destroyQuESTEnv(env);

    return 0;
}
