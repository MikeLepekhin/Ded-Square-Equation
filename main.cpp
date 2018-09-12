/*!
 * \file
 * \brief This is the code of program using function solveSquareEquation for calculations.
 * \details The program has options --help and --verbose.
 *
 * \author Mikhail Lepekhin
 * \version 1.0
 */

#include "square_equation_solver.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <getopt.h>

void help() {
  std::cout << "# usage:\n";
  std::cout << "# [[A] B]C, where A, B and C are coefficients of square equation\n";
}


/*!
 * \fn
 * \brief This function is called when user hasn't entered any argument.
 * \details The program has options --help and --verbose.
 *
 * \author Mikhail Lepekhin
 * \version 1.0
 */

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

void parseOptions(int argc, char** argv) {
  const char* const short_opts = "v:h";
  const option long_opts[] = {
    {"verbose", no_argument, nullptr, 'v'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, no_argument, nullptr, 0}
  };

  int opt = 0;
  while (opt != -1) {
    const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

    switch (opt) {
      case 'h':
        help();
        exit(0);
      case -1:
        return;
      case '?':
      default:
        std::cerr << "!!! unknown option " << opt << "\n";
        return;
    }
  }
}

int main(int argc, char *argv[]) {
  parseOptions(argc, argv);
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