/////////////////////////////////////////////////////////////
// Title  : generalAssertFunctions.hpp                     //
// Author : Jonathan Miller                                //
// Date   : 20230425                                       //
// Aim    : Construct general functions                    //
/////////////////////////////////////////////////////////////









/**
 * @brief Tests if two values are equal.
 *
 * This function compares two values and returns true if they are equal, and false otherwise.
 *
 * @param i The first value to compare.
 * @param j The second value to compare.
 * @return True if i is equal to j, false otherwise.
 */
bool testTwoValueEquate(int i, int j) {
    return (i == j);
}

/**
 * @brief Retrieves the minimum value from a vector.
 *
 * This function returns the minimum value from a vector of integers.
 *
 * @param vec The vector of integers.
 * @return The minimum value in the vector.
 * @throws std::invalid_argument if the vector is empty.
 */
int getMin(const boost::container::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Cannot get min of empty vector");
    }

    int min_val = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min_val) {
            min_val = vec[i];
        }
    }

    return min_val;
}



/**
 * @brief Retrieves the maximum value from a vector.
 *
 * This function returns the maximum value from a vector of integers.
 *
 * @param vec The vector of integers.
 * @return The maximum value in the vector.
 * @throws std::invalid_argument if the vector is empty.
 */
int getMax(const boost::container::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Cannot get max of empty vector");
    }

    int max_val = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max_val) {
            max_val = vec[i];
        }
    }

    return max_val;
}



/**
 * @brief Checks if an integer value is present in a vector.
 *
 * This function checks if a given integer value is present in a vector of integers.
 *
 * @param value The integer value to search for.
 * @param vec The vector of integers.
 * @return True if the value is found in the vector, false otherwise.
 */
bool isIntInVector(int value, const std::vector<int>& vec) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}



/**
 * @brief Asserts the value of the last qubit measurement outcome.
 *
 * This function checks if the value of the last qubit measurement outcome matches the specified assert value. If the values do not match, it throws a runtime error with a descriptive message.
 *
 * @param measuredQubitsOutcomes The vector of measured qubit outcomes.
 * @param assertValue The expected value for the last qubit measurement outcome.
 *
 * @throws std::runtime_error if the last qubit measurement outcome does not match the assert value.
 */
void assertFunc(std::vector<int> measuredQubitsOutcomes,int assertValue) {
    if (measuredQubitsOutcomes.back() != assertValue) {
        throw std::runtime_error("The last qubit must be " + std::to_string(assertValue) + ", it is not.");
    }
}

