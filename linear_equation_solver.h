#ifndef SQUARE_EQUATION_LINEAR_EQUATION_SOLVER_H
#define SQUARE_EQUATION_LINEAR_EQUATION_SOLVER_H

#include "exceptions.h"
#include "predicates.h"
#include "constants.h"

#include <iostream>

template <class Field >
class LinearEquationAnswer {
 private:
  size_t answer_cnt_{0};
  Field* answer_{nullptr};

  void setAnswer(const Field& new_value) {
    if (answer_ != nullptr) {
      delete answer_;
    }
    answer_ = new Field(new_value);
  }

 public:
  LinearEquationAnswer() {}

  LinearEquationAnswer(const LinearEquationAnswer& another):
      answer_cnt_(another.answer_cnt_) {
    if (answer_cnt_) {
      answer_ = new Field(*another.answer_);
    }
  }

  LinearEquationAnswer(LinearEquationAnswer&& another):
      answer_cnt_(another.answer_cnt_),
      answer_(another.answer_) {
    another.answer_ = nullptr;
    another.answer_cnt_ = 0;
  }

  bool operator==(const LinearEquationAnswer& another) const {
    if (answer_cnt_ != another.answer_cnt_) {
      return false;
    }
    return answer_cnt_ == 0 || *answer_ == *another.answer_;
  }

  void addAnswer(const Field& value) {
    if (answer_cnt_ >= 1) {
      throw AnswerOverflowException("It already contains >= 2 solutions");
    }
    setAnswer(value);
    ++answer_cnt_;
  }

  Field getAnswer() const {
    if (answer_cnt_ == 0) {
      throw IncorrectArgumentException("It is more than count of solutions");
    }
    return *answer_;
  }

  size_t size() const {
    return answer_cnt_;
  }

  explicit operator Field() const {
    return getAnswer();
  }

  static LinearEquationAnswer EmptySet() {
    return LinearEquationAnswer();
  }

  static LinearEquationAnswer InfiniteSet() {
    LinearEquationAnswer result;

    result.answer_cnt_ = INFINITE_ROOT_CNT;
    result.setAnswer(0);
    return result;
  }

  LinearEquationAnswer& operator=(const LinearEquationAnswer& another) {
    if (this != &another) {
      if (answer_ != nullptr) {
        delete answer_;
        answer_ = nullptr;
      }
      answer_cnt_ = another.answer_cnt_;
      if (answer_cnt_) {
        answer_ = new Field(*another.answer_);
      }
    }
    return *this;
  }

  LinearEquationAnswer& operator=(LinearEquationAnswer&& another) {
    if (this != &another) {
      if (answer_ != nullptr) {
        delete answer_;
        answer_ = nullptr;
      }
      answer_cnt_ = another.answer_cnt_;
      answer_ = another.answer_;
      another.answer_= nullptr;
    }
    return *this;
  }

  ~LinearEquationAnswer() {
    if (answer_ != nullptr) {
      delete answer_;
    }
  }
};

template<class Field>
std::ostream& operator<<(std::ostream& os, const LinearEquationAnswer<Field>& answer) {
  if (answer.size() == INFINITE_ROOT_CNT) {
    std::cout << "the number of solutions is infinite\n";
    return os;
  }

  if (!answer.empty()) {
    os << "Solution: " << answer.getAnswer() << '\n';
  } else {
    os << "No solutions\n";
  }
  return os;
}

template <class Field = double, class EqualityPredicate = DefaultEqualityPredicate<Field>>
LinearEquationAnswer<Field> solveLinearEquation(const Field& coeff_a = 0, const Field& coeff_b = 0) {
  if (EqualityPredicate()(coeff_a, 0)) {
    if (!EqualityPredicate()(coeff_b, 0)) {
      return LinearEquationAnswer<Field>::EmptySet();
    }
    return LinearEquationAnswer<Field>::InfiniteSet();
  }

  LinearEquationAnswer<Field> result;
  result.addAnswer(-coeff_b / coeff_a);
  return result;
}

#endif //SQUARE_EQUATION_LINEAR_EQUATION_SOLVER_H
