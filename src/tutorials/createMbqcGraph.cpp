#include <boost/graph/adjacency_list.hpp>
#include <QuEST.h>
#include <iostream>

// Define a struct to hold the properties of the vertices
struct VertexProperties {
    Qureg qubit;
};

// Define a struct to hold the properties of the edges
struct EdgeProperties {
    double angle;
};

// Define the graph type
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, VertexProperties, EdgeProperties> CircuitGraph;

int main() {
    // Create a quantum register with 3 qubits
    QuESTEnv env = createQuESTEnv();
    Qureg qubits = createQureg(3, env);

    // Create the graph
    CircuitGraph circuit(3);

    // Add the qubits as vertices and attach them to the graph
    for (int i = 0; i < 3; i++) {
        VertexProperties vp = {qubits};
        boost::add_vertex(vp, circuit);
    }


    // Add the controlled-Z gates as edges and attach them to the graph

    boost::add_edge(0, 1, {M_PI}, circuit);
    boost::add_edge(1, 2, {M_PI/2}, circuit);

    // Perform some operations on the qubits using the graph
    int m = measure(qubits,0);
    
    std::cout << m << " ";
    std::cout << std::endl;

    // Destroy the quantum register and the environment
    destroyQureg(qubits, env);
    destroyQuESTEnv(env);

    return 0;
}
