/*!
 * @file model_calculator.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса ModelCalculator
 */

#include "model_calculator.h"

#include <iostream>
namespace s21 {

double ModelCalculator::Calculator() {
  ReversePolishNotation();
  double result = Calculate();
  return result;
}

std::pair<std::vector<double>, std::vector<double>> ModelCalculator::Graph(
    double x_max_value, double step) {
  vectors_xy result;
  ReversePolishNotation();
  std::stack<Lexeme> tmp_stack = stack_;
  for (double x = -x_max_value; x < x_max_value; x += step) {
    result.first.push_back(x);
    x_value_ = x;
    double y = Calculate();
    result.second.push_back(y);
    stack_ = tmp_stack;
  }
  return result;
}

double ModelCalculator::Calculate() {
  while (!stack_.empty()) {
    if (stack_.top().symbol == 'x') {
      number_.push(x_value_);
    } else if (stack_.top().priority == 0) {
      number_.push(stack_.top().value);
    } else {
      operator_.push(stack_.top().symbol);
      if (IsBinaryOperator(operator_.top())) {
        CounterBinaryOperator();
      } else {
        CounterUnaryOperator();
      }
    }
    stack_.pop();
  }

  double result = number_.top();
  return result;
}

void ModelCalculator::CounterBinaryOperator() {
  double b = number_.top();
  number_.pop();
  double a = number_.top();
  number_.pop();
  if (operator_.top() == '+') {
    number_.push(a + b);
  } else if (operator_.top() == '-') {
    number_.push(a - b);
  } else if (operator_.top() == '/') {
    number_.push(a / b);
  } else if (operator_.top() == '*') {
    number_.push(a * b);
  } else if (operator_.top() == '^') {
    number_.push(std::pow(a, b));
  } else if (operator_.top() == 'm') {
    number_.push(std::fmod(a, b));
  }
}

void ModelCalculator::CounterUnaryOperator() {
  double a = number_.top();
  number_.pop();
  if (operator_.top() == 'C') {
    number_.push(std::acos(a));
  } else if (operator_.top() == 'S') {
    number_.push(std::asin(a));
  } else if (operator_.top() == 'T') {
    number_.push(std::atan(a));
  } else if (operator_.top() == 'c') {
    number_.push(std::cos(a));
  } else if (operator_.top() == 's') {
    number_.push(std::sin(a));
  } else if (operator_.top() == 't') {
    number_.push(std::tan(a));
  } else if (operator_.top() == 'L') {
    number_.push(std::log(a));
  } else if (operator_.top() == 'l') {
    number_.push(std::log10(a));
  } else if (operator_.top() == 'Q') {
    number_.push(std::sqrt(a));
  } else if (operator_.top() == 'p') {
    number_.push(a);
  } else if (operator_.top() == 'u') {
    number_.push(-a);
  }
}

void ModelCalculator::ReversePolishNotation() {
  std::stack<char> support;
  for (size_t i = 0; i < str_.length(); i++) {
    if (IsNumber(str_[i])) {
      PushNumber(GetNumber(&i));
    } else if (str_[i] == 'x') {
      PushSymbol(str_[i]);
    } else if (str_[i] == ')') {
      while (support.top() != '(') {
        PushSymbol(support.top());
        support.pop();
      }
      support.pop();
    } else if (str_[i] == '(') {
      support.push(str_[i]);
    } else if (IsFunction(str_[i]) || IsOperator(str_[i]) || str_[i] == '(') {
      while (!support.empty() &&
             GetPriority(str_[i]) <= GetPriority(support.top()) &&
             str_[i] != 'p' && str_[i] != 'u' && support.top() != '(' &&
             (str_[i] != '^' || support.top() != '^')) {
        PushSymbol(support.top());
        support.pop();
      }
      support.push(str_[i]);
    }
  }

  while (!support.empty()) {
    PushSymbol(support.top());
    support.pop();
  }
  InverseStack();
}

void ModelCalculator::PushNumber(double value) {
  Lexeme temp;
  temp.value = value;
  temp.symbol = '\0';
  temp.priority = 0;
  stack_.push(temp);
}

void ModelCalculator::PushSymbol(char symbol) {
  Lexeme temp;
  temp.value = 0;
  temp.symbol = symbol;
  temp.priority = GetPriority(symbol);
  stack_.push(temp);
}

int ModelCalculator::GetPriority(char symbol) {
  int status = 0;
  if (symbol == '(' || symbol == ')') {
    status = -1;
  } else if (symbol == 'x') {
    status = 0;
  } else if (symbol == '+' || symbol == '-') {
    status = 1;
  } else if (symbol == '/' || symbol == '*') {
    status = 2;
  } else if (symbol == 'p' || symbol == 'u') {
    status = 3;
  } else if (symbol == '^') {
    status = 3;
  } else if (IsFunction(symbol)) {
    status = 5;
  }
  return status;
}

double ModelCalculator::GetNumber(size_t *pos) {
  size_t end = *pos;
  std::string tmp;
  bool exp = false;
  while (end < str_.size() && (IsNumber(str_[end]) || IsExp(str_[end], exp))) {
    if (str_[end] == 'e') exp = true;
    if (str_[end] == '+' || str_[end] == '-') exp = false;
    tmp += str_[end];
    end++;
  }
  double result = std::stod(tmp);
  *pos = end - 1;
  return result;
}

bool ModelCalculator::IsBinaryOperator(char symbol) {
  return comparison_[0].find(symbol) != std::string_view::npos;
}

bool ModelCalculator::IsFunction(char symbol) {
  return comparison_[1].find(symbol) != std::string_view::npos;
}

bool ModelCalculator::IsOperator(char symbol) {
  return comparison_[2].find(symbol) != std::string_view::npos;
}

void ModelCalculator::InverseStack() {
  std::stack<Lexeme> tmp;
  while (!stack_.empty()) {
    tmp.push(stack_.top());
    stack_.pop();
  }
  stack_ = tmp;
}

void ModelCalculator::SetString(std::string str) { str_ = str; }

void ModelCalculator::SetX(double x_val) { x_value_ = x_val; }

bool IsNumber(char symbol) {
  return std::isdigit(symbol) || symbol == '.' || symbol == 'e' ||
         symbol == 'E';
}

bool IsExp(char symbol, bool exp) {
  if (exp && (symbol == '+' || symbol == '-' || IsNumber(symbol))) {
    return true;
  } else {
    return false;
  }
}
}  // namespace s21
