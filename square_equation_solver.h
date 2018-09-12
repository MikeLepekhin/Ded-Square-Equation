/*!
 * \file
 * \briefly This file contains the general function providing calculations - solveSquareEquation
 */

#ifndef SQUARE_EQUATION_SQUARE_EQUATION_SOLVER_H
#define SQUARE_EQUATION_SQUARE_EQUATION_SOLVER_H

#include "linear_equation_solver.h"
#include "exceptions.h"
#include "predicates.h"
#include "constants.h"

#include <iostream>
#include <exception>
#include <limits>
#include <vector>
#include <cmath>
#include <cstdlib>


/*!
 * \briefly This class is used for convenient storage of solutions returned by solveSquareEquation answer
 * \tparam Field is type of the answer.
 * \tparam EqualityPredicate is the functor indicating whether two instances of class Field are equal or not.
 *
 */
template <class Field, class EqualityPredicate = DefaultEqualityPredicate<Field>>
class SquareEquationAnswer {
 private:
  size_t answer_cnt_{0};
  Field* answer_1_{nullptr};
  Field* answer_2_{nullptr};

  void setAnswer(Field*& answer, const Field& new_value) {
    if (answer != nullptr) {
      delete answer;
    }
    answer = new Field(new_value);
  }

  void clearAnswer(Field* answer) {
    if (answer != nullptr) {
      delete answer;
      answer = nullptr;
    }
  }

 public:
  SquareEquationAnswer() {}

  SquareEquationAnswer(const LinearEquationAnswer<Field>& leanswer):
      answer_cnt_(leanswer.size()) {
    if (leanswer.size() > 0) {
      answer_1_ = new Field(leanswer.getAnswer());
    }
  }

  SquareEquationAnswer(const SquareEquationAnswer& another):
      answer_cnt_(another.answer_cnt_) {
    if (another.answer_1_ != nullptr) {
      answer_1_ = new Field(*another.answer_1_);
    }
    if (another.answer_2_ != nullptr) {
      answer_2_ = new Field(*another.answer_2_);
    }
  }

  SquareEquationAnswer(SquareEquationAnswer&& another):
      answer_cnt_(another.answer_cnt_),
      answer_1_(another.answer_1_),
      answer_2_(another.answer_2_) {
    another.answer_cnt_ = 0;
    another.answer_1_ = nullptr;
    another.answer_2_ = nullptr;
  }

  bool operator==(const SquareEquationAnswer& another) const {
    if (answer_cnt_ != another.answer_cnt_) {
      return false;
    }
    return (answer_1_ == nullptr || EqualityPredicate()(*answer_1_, *another.answer_1_)) &&
           (answer_2_ == nullptr || EqualityPredicate()(*answer_2_, *another.answer_2_));
  }

  SquareEquationAnswer& operator=(const SquareEquationAnswer& another) {
    if (this != &another) {
      clearAnswer(answer_1_);
      clearAnswer(answer_2_);

      answer_cnt_ = another.answer_cnt_;
      if (another.answer_1 != nullptr) {
        answer_1_ = new Field(*another.answer_1_);
      }
      if (another.answer_2 != nullptr) {
        answer_2_ = new Field(*another.answer_2_);
      }
    }
    return *this;
  }

  SquareEquationAnswer& operator=(SquareEquationAnswer&& another) {
    if (this != &another) {
      clearAnswer(answer_1_);
      clearAnswer(answer_2_);

      answer_cnt_ = another.answer_cnt_;
      answer_1_ = another.answer_1_;
      another.answer_1_ = nullptr;
      answer_2_ = another.answer_2_;
      another.answer_2_ = nullptr;
    }
    return *this;
  }

  void addAnswer(const Field& value) {
    if (answer_cnt_ >= MAX_SQUARE_ROOT_CNT) {
      throw AnswerOverflowException("It already contains >= 2 solutions");
    }
    if (answer_cnt_ == 0) {
      setAnswer(answer_1_, value);
    } else {
      setAnswer(answer_2_, value);
      if (*answer_1_ > *answer_2_) {
        std::swap(*answer_1_, *answer_2_);
      }
    }
    ++answer_cnt_;
  }

  Field getAnswer(size_t answer_id = 0) const {
    if (answer_id >= answer_cnt_) {
      throw IncorrectArgumentException("It is more than count of solutions");
    }

    switch (answer_id) {
      case 0: return *answer_1_;
      case 1: return *answer_2_;
      default: throw IncorrectArgumentException("Possible values: 0 and 1");
    }
  }

  Field operator[](size_t answer_id) const {
    return getAnswer(answer_id);
  }

  size_t size() const {
    return answer_cnt_;
  }

  bool empty() const {
    return answer_cnt_ == 0;
  }

  operator std::vector<Field>() const {
    std::vector<Field> result;

    for (size_t answer_id = 0; answer_id < answer_cnt_; ++answer_id) {
      result.push_back(getAnswer(answer_id));
    }
    return result;
  }

  static SquareEquationAnswer EmptySet() {
    return SquareEquationAnswer();
  }

  static SquareEquationAnswer InfiniteSet() {
    SquareEquationAnswer result;

    result.answer_cnt_ = INFINITE_ROOT_CNT;
    result.setAnswer(result.answer_1_, 0);
    return result;
  }

  ~SquareEquationAnswer() {
    if (answer_1_ != nullptr) {
      delete answer_1_;
    }
    if (answer_2_ != nullptr) {
      delete answer_2_;
    }
  }
};

template<class Field>
std::ostream& operator<<(std::ostream& os, const SquareEquationAnswer<Field>& answer) {
  if (answer.size() > MAX_SQUARE_ROOT_CNT) {
    std::cout << "the number of solutions is infinite\n";
    return os;
  }
  os << "The number of solutions: " << answer.size() << "\n";
  if (!answer.empty()) {
    os << "Solutions: ";
  }
  for (size_t answer_id = 0; answer_id < answer.size(); ++answer_id) {
    os << answer[answer_id] << ' ';
  }
  os << '\n';
  return os;
}

/*!
 * \fn
 * \brief This is the general function of the project containing the implementation of square equations solving.
 * \details You have opportunity to put your own equality predicate to use for custom field
 */

template <class Field = double, class EqualityPredicate = DefaultEqualityPredicate<Field>>
SquareEquationAnswer<Field> solveSquareEquation(const Field& coeff_a = 0, const Field& coeff_b = 0, const Field& coeff_c = 0) {
  if (!std::isfinite(coeff_a) || !std::isfinite(coeff_b) || !std::isfinite(coeff_c)) {
    throw IncorrectArgumentException("some of the arguments are infinite");
  }

  if (EqualityPredicate()(coeff_a, 0.0)) {
    return solveLinearEquation<Field, EqualityPredicate>(coeff_b, coeff_c);
  }

  SquareEquationAnswer<Field> result;
  Field D = coeff_b * coeff_b - 4.0 * coeff_a * coeff_c;

  if (EqualityPredicate()(D, 0.0)) {
    result.addAnswer(-coeff_b / (2.0 * coeff_a));
  } else if (D > 0.0) {
    Field D_sqrt = sqrt(D);
    result.addAnswer((-coeff_b + D_sqrt) / (2.0 * coeff_a));
    result.addAnswer((-coeff_b - D_sqrt) / (2.0 * coeff_a));
  }
  std::cout << result << '\n';
  return result;
}

#endif //SQUARE_EQUATION_SQUARE_EQUATION_SOLVER_H
