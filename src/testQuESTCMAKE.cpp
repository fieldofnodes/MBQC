#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/container/vector.hpp>

int main() {
    std::vector<int> numbers; // Create a vector to store the numbers

    // Populate the vector with numbers from 1 to 10
    for (int i = 1; i <= 10; i++) {
        numbers.push_back(i);
    }

    // Square each element in the vector
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int num) {
        return num * num;
    });

    // Print the squared numbers
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;



     boost::container::vector<int> myVector;

    // Add elements to the vector
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    // Print the elements of the vector
    for (const auto& element : myVector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
