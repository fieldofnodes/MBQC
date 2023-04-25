#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <boost/container/vector.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>




using namespace boost;





/*
  Return true if i == j, else false
*/
bool testTwoValueEquate (int i, int j) {
  return (i==j);
}


/*
  Get minimum value inside a vector
*/
int getMin(const boost::container::vector<int>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Cannot get max of empty vector");
    }

    int min_val = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] < min_val) {
            min_val = vec[i];
        }
    }

    return min_val;
}


/*
  Get maximum value inside a vector
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
