/*!
 * \file
 */

#ifndef SQUARE_EQUATION_PREDICATES_H
#define SQUARE_EQUATION_PREDICATES_H

#include <cmath>
#include <cstdlib>

template<class T>
struct DefaultEqualityPredicate {
  bool operator ()(const T& first, const T& second) {
    return first == second;
  }
};

const double EPS = 1e-5;

template<>
struct DefaultEqualityPredicate<double> {
  bool operator ()(const double& first, const double& second) {
    return std::abs(first - second) < EPS;
  }
};

bool operator==(const std::vector<double>& v1, const std::vector<double>& v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (size_t i = 0; i < v1.size(); ++i) {
    if (std::abs(v1[i] - v2[i]) >= EPS) {
      return false;
    }
  }
  return true;
}

#endif //SQUARE_EQUATION_PREDICATES_H
