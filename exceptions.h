/*!
 * \file
 */

#ifndef SQUARE_EQUATION_EXCEPTIONS_H
#define SQUARE_EQUATION_EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

struct SquareSolverException : public std::exception {
  std::string message;

  SquareSolverException(const std::string& message):
    message(message) {}
};

struct IncorrectArgumentException : public SquareSolverException {
  IncorrectArgumentException(const std::string& message):
    SquareSolverException(message) {}
};

struct AnswerOverflowException : public SquareSolverException {
  AnswerOverflowException(const std::string& message):
    SquareSolverException(message) {}
};

std::ostream& operator<<(std::ostream& os, const SquareSolverException& iaexception) {
  os << "!!! IncorrectArgument: " << iaexception.message << '\n';
  return os;
}


#endif //SQUARE_EQUATION_EXCEPTIONS_H
