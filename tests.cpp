/*!
 * \file
 * \brief This file contains tests for the function squareEquationSolver
 * \details Class Tester can be used as a handler for every boolean test function.
 * It reports whether program works correctly on the test or not and catches exceptions
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "square_equation_solver.h"

class Tester {
 private:
  void test(bool (*foo)(), size_t test_id = 1, const std::string& title = "") {
    std::cout << "Test #" << test_id << ": '" << title << "'\n";
    try {
      bool passed = foo();

      std::cout << "Status: ";
      if (passed) {
        std::cout << "passed\n";
      } else {
        std::cout << "failed\n";
      }
    } catch (std::exception&) {
      std::cerr << "!!! exception was caught\n";
      std::cout << "Status: failed\n";
    }
    std::cout << '\n';
  }

  std::vector<std::pair<bool(*)(), std::string>> functions_;

 public:
  template <typename P, typename... Args>
  Tester(const P& function, const Args&... rest):
      Tester(rest...) {
    functions_.push_back(function);
  }

  Tester() {}

  void start() {
    std::reverse(functions_.begin(), functions_.end());
    for (size_t function_id = 0; function_id < functions_.size(); ++function_id) {
      test(functions_[function_id].first, function_id + 1, functions_[function_id].second);
    }
  }
};

bool noArguments() {
  return solveSquareEquation<double>() == SquareEquationAnswer<double>::InfiniteSet();
}

bool trivialCase() {
  return solveSquareEquation<double>(0, 0, 0) == SquareEquationAnswer<double>::InfiniteSet();
}

bool noSolutions() {
  return solveSquareEquation<double>(0, 0, 15.8) == SquareEquationAnswer<double>::EmptySet();
}

bool simpleLinear() {
  return std::vector<double>(solveSquareEquation<double>(0, 16, 3.5)) == std::vector<double>{-0.21875};
}

bool simpleSquare() {
  return std::vector<double>(solveSquareEquation<double>(0.00001, 0, 0)) == std::vector<double>{0};
}

bool badSquare() {
  return solveSquareEquation<double>(1, -4, 10) == SquareEquationAnswer<double>::EmptySet();
}

bool squareOneRoot() {
  return std::vector<double>(solveSquareEquation<double>(1.5, 6, 6)) == std::vector<double>{-2};
}

bool squareTwoRoots() {
  return std::vector<double>(solveSquareEquation<double>(1, 1, -1)) == std::vector<double>{-1.61803, 0.618034};
}

int main() {
  Tester tester(
    std::make_pair(noArguments, "no arguments"),
    std::make_pair(trivialCase, "infinite number of solutions"),
    std::make_pair(noSolutions, "empty set of solutions"),
    std::make_pair(simpleLinear, "16x + 3.5 = 0"),
    std::make_pair(simpleSquare, "0.00001x^2 = 0"),
    std::make_pair(badSquare, "x^2 - 4x + 10 = 0"),
    std::make_pair(squareOneRoot, ""),
    std::make_pair(squareTwoRoots, "")
  );

  tester.start();
  return 0;
}