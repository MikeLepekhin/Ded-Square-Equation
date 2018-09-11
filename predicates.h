//
// Created by mike on 08.09.18.
//

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

const double EPS = 1e-6;

template<>
struct DefaultEqualityPredicate<double> {
  bool operator ()(const double& first, const double& second) {
    return std::abs(first - second) < EPS;
  }
};

#endif //SQUARE_EQUATION_PREDICATES_H
