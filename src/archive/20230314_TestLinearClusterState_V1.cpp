//////////////////////////////////////////////////////////////////////
// Title     : Three qubit in a line entangled
// Author    : Jonathan Miller
// Date      : 20230309
// Aim       : Implement a simple MBQC circuit for ()-()-() circuit
// Flow      : Same row, next column; 
//           : f(0) = 1, f(1) = 2, f(2) = 3
//           : f-1(3) = 2, f-1(2) = 1, f-1(1) = 0

#include <QuEST.h>
//#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
#include "20230314_Functions_V1.hpp"





int main() {
    
  
    // set parameters
    int numberQubits = 5;
    
    // Select a qubit index
    int currentQubit = 3;

    // Create a vector representing a linear cluster graph
    vector<int> pathGraph = getPathGraph(numberQubits);

    // Get the future qubit using pathGraph and current qubit
    int future_qubit_linear_cluster = getFutureQubitPathGraph(pathGraph ,currentQubit);

    // Get the past qubit using pathGraph and current qubit
    int qubitBefore_linear_cluster = getPastQubitPathGraph(pathGraph ,currentQubit);

    // Get the neighbourhood size
    int size_neighbour_set = getOpenNeighbourhoodSizePathGraph(pathGraph ,currentQubit);
    
    // Ger neighbours
    vector<int> neighbours = getOpenNeighbourhoodPathGraph(pathGraph ,currentQubit);


    printf("The number of qubits is: %d\n", numberQubits);
    printf("The current qubit is: %d\n",currentQubit);
    printf("The Past qubit is: %d\n",qubitBefore_linear_cluster);
    printf("The future qubit is: %d\n",future_qubit_linear_cluster);
    printf("Size of neighbour set: %d\n",size_neighbour_set);  
    printf("The neighbourhoods are: ");
    
    for (int i: neighbours)
    {
        cout << i << ' ';
    }
    
    printf("\n");
    
    printf("The linear cluster is written out as: \n");
    for (int i: pathGraph)
    {
        cout << i << ' ';
    }


    // Assert that the future qubit is equivalent to the current qubit +1
    assert(future_qubit_linear_cluster == currentQubit + 1 && "Incorrect future qubit");

    // Assert that the future qubit is equivalent to the current qubit -1
    assert(qubitBefore_linear_cluster == currentQubit - 1 && "Incorrect past qubit");

    /* 
        Assert that the number of qubits initialised is equivalent to the 
        size of the linear cluster vector
    */
    assert(numberQubits == pathGraph.size() && "The linear cluster is not the same size as the number of qubits initialised.");


    /*
        Test that the size of the neighbours is equivalent to the
        function output based on the qubit location in the vector
    */
    if (currentQubit == pathGraph[0])
    {
        assert(size_neighbour_set == 1 && "Neighbour set shoud be size 1");
    } else if (currentQubit == pathGraph[pathGraph.size()-1]){
        assert(size_neighbour_set == 1 && "Neighbour set shoud be size 1");
    } else {
        assert(size_neighbour_set == 2 && "Neighbour set shoud be size 2");
    }

    /*
        Test that the size of the neighbours is equivalent to the
        function output based on the qubit location in the vector and
        the size of the size of the neighbours vector.
    */
    if (currentQubit == pathGraph[0])
    {
        assert(neighbours.size() == 1 && "Neighbour set shoud be size 1");
    } else if (currentQubit == pathGraph[pathGraph.size()-1]){
        assert(neighbours.size() == 1 && "Neighbour set shoud be size 1");
    } else {
        assert(neighbours.size() == 2 && "Neighbour set shoud be size 2");
    }


    printf("\n");
    // Iterate over path graph cluster p_10
    int NewNumberQubits = 10;
    // Create a vector representing a linear cluster graph
    vector<int> NewLinearCluster = getPathGraph(NewNumberQubits);

    // Iterate over all vertices, return neighbours
    
    // Iterate over the path cluster
    for (int q: NewLinearCluster)
    {
        cout << "Qubit: " << q << "\n";
        vector<int> neighbours = 
            getOpenNeighbourhoodPathGraph(
                NewLinearCluster ,q);
        cout << "Neighbours: ";
        // Get the future qubit using pathGraph and current qubit
        int FutureQubit = getFutureQubitPathGraph(NewLinearCluster ,q);
        printf("Current qubit: %d future qubit: %d\n",q,FutureQubit);
        // Get the past qubit using pathGraph and current qubit
        int pastQubit = getPastQubitPathGraph(NewLinearCluster ,q);
        printf("Current qubit: %d past qubit: %d\n",q,FutureQubit);
        for (int n: neighbours)
        {
            cout << n << ' ';
        }
        printf("\n");
        
    }



    

}









