#include "square_equation_solver.h"
#include "linear_equation_solver.h"

#include <iostream>

void help() {
  std::cout << "# Square Equation Solver 1.0\n";
  std::cout << "# usage:\n";
  std::cout << "# [A] [B] [C], where A, B and \n";

}

int main() {
    double coeff_a, coeff_b, coeff_c;
    std::cin >> coeff_a >> coeff_b >> coeff_c;

    auto answer = SquareEquationSolver<double>::solve(coeff_a, coeff_b, coeff_c);

    std::cout << answer;
    /*SquareEquationSolver<double> my_solver;
    std::cout << my_solver.solve(coeff_a, coeff_b, coeff_c);*/
    return 0;
}