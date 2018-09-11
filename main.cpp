#include "square_equation_solver.h"

#include <iostream>
#include <vector>
#include <cstdlib>

void help() {
  std::cout << "# Square Equation Solver 1.0\n";
  std::cout << "# usage:\n";
  std::cout << "# [A] [B] [C], where A, B and \n";
}

void hello() {
  std::cout << "# Square Equation Solver 1.0\n";
  std::cout << "# Hello! This is the most efficient solver for square equations\n";
  std::cout << "# If you want to figure out how to use it, use --help option\n";
}

std::vector<double> parseCoeffs(int argc, char* argv[]) {
  std::vector<double> result;

  for (size_t arg_id = 1; arg_id < argc; ++arg_id) {
    result.push_back(atof(argv[arg_id]));
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    hello();
    return 0;
  }

  std::vector<double> coeffs = parseCoeffs(argc, argv);

  try {
    SquareEquationAnswer<double> answer;
    switch (coeffs.size()) {
      case 3:
        answer = solveSquareEquation<double>(coeffs[0], coeffs[1], coeffs[2]);
        break;
      case 2:
        answer = solveLinearEquation<double>(coeffs[0], coeffs[1]);
        break;
      case 1:
        answer = solveLinearEquation<double>(coeffs[0]);
        break;
      case 0:
        answer = solveLinearEquation<double>();
        break;
      default:
        std::cerr << "!!! Incorrect number of coefficients\n";
        return 1;
    }
    std::cout << answer;
  } catch (SquareSolverException& func_exception) {
    std::cerr << func_exception;
  }
  return 0;
}