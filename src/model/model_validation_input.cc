/*!
 * @file model_validation_input.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса ModelValidationInput
 */

#include "model_validation_input.h"

#include "model_calculator.h"
namespace s21 {

ModelValidationInput::ModelValidationInput() : input_string_("0") {
  flags_.point = false;
  flags_.bracket = 0;
  flags_.exp = false;
  functions_ = {{"mod", {3, 'm'}},  {"sin", {3, 's'}},  {"cos", {3, 'c'}},
                {"tan", {3, 't'}},  {"asin", {4, 'S'}}, {"acos", {4, 'C'}},
                {"atan", {4, 'T'}}, {"sqrt", {4, 'Q'}}, {"ln", {2, 'L'}},
                {"log", {3, 'l'}}};
  right_str_ = {"*/^",      "asctlm",           "asctl",
                ")*/^m",    "-+pu/*SCTQsctlLm", "(-+*/^SCTQsctmlLpu",
                "x)",       "x(asctl+- ",       "SCTQsctlLm",
                "asctlm/^*"};
}

bool ModelValidationInput::ValidateInput() {
  bool status = true;
  auto len = input_string_.size();
  if (len > 255 || len < 1) {
    status = false;
  }

  for (decltype(len) i = 0; status && i < len; ++i) {
    if (IsNumber(input_string_[i])) {
      status = CheckNumber(&i);
    } else if (input_string_[i] == ' ') {
      continue;
    } else if (input_string_[i] == 'x') {
      CheckX(i);
    } else if (input_string_[i] == '(') {
      status = CheckLeftBracket(i);
    } else if (input_string_[i] == ')') {
      status = CheckRightBracket(i);
    } else if (input_string_[i] == '+' || input_string_[i] == '-') {
      status = CheckUnarOperator(i, input_string_[i]);
    } else if (right_str_[0].find(input_string_[i]) != right_str_[0].npos) {
      status = CheckBinaryOperator(i);
    } else if (right_str_[1].find(input_string_[i]) != right_str_[1].npos) {
      status = CheckLongOperetor(&i);
    } else {
      status = false;
    }
  }
  if (flags_.bracket) status = false;
  return status;
}

bool ModelValidationInput::CheckNumber(size_t* pos) {
  size_t end = *pos;
  while (
      end < input_string_.size() &&
      (IsNumber(input_string_[end]) || IsExp(input_string_[end], flags_.exp))) {
    if (input_string_[end] == '.') {
      if (flags_.point || flags_.exp ||
          (!IsNumber(input_string_[end - 1]) &&
           !IsNumber(input_string_[end + 1]))) {
        return false;
      } else {
        flags_.point = true;
      }
    }
    if (input_string_[end] == 'e' || input_string_[end] == 'E') {
      if (flags_.exp) {
        return false;
      }
      flags_.exp = true;
    }
    end++;
  }
  std::string number_string = input_string_.substr(*pos, end - *pos);
  correct_ += number_string;
  if (right_str_[2].find(input_string_[end]) != right_str_[2].npos &&
      end != input_string_.size())
    correct_ += "*";
  flags_.point = false;
  flags_.exp = false;
  *pos = end - 1;
  return true;
}

void ModelValidationInput::CheckX(size_t pos) {
  if (IsNumber(input_string_[pos - 1]) || input_string_[pos - 1] == 'x') {
    correct_ += "*x";
  } else if ((IsNumber(input_string_[pos + 1]) ||
              right_str_[2].find(input_string_[pos + 1]) !=
                  right_str_[2].npos) &&
             pos + 1 != input_string_.size()) {
    correct_ += "x*";
  } else {
    correct_ += input_string_[pos];
  }
}

bool ModelValidationInput::CheckLeftBracket(const size_t pos) {
  if (pos == input_string_.size() - 1 ||
      right_str_[3].find(input_string_[pos + 1]) != right_str_[3].npos) {
    return false;
  }
  flags_.bracket++;
  if (IsNumber(input_string_[pos - 1]) || input_string_[pos - 1] == 'x') {
    correct_ += "*(";
  } else {
    correct_ += "(";
  }
  return true;
}

bool ModelValidationInput::CheckRightBracket(const size_t pos) {
  if (pos == 0 ||
      right_str_[4].find(correct_[correct_.size() - 1]) != right_str_[4].npos ||
      !flags_.bracket) {
    return false;
  }
  flags_.bracket--;
  if ((IsNumber(input_string_[pos + 1]) || input_string_[pos + 1] == 'x' ||
       input_string_[pos + 1] == '(' ||
       right_str_[1].find(input_string_[pos + 1]) != right_str_[1].npos) &&
      pos + 1 != input_string_.size()) {
    correct_ += ")*";
  } else {
    correct_ += ")";
  }
  return true;
}

bool ModelValidationInput::CheckUnarOperator(const size_t pos,
                                             const char symbol) {
  if (pos == input_string_.size() - 1) return false;
  if (pos == 0 || right_str_[5].find(correct_.back()) != right_str_[5].npos) {
    if (symbol == '+') {
      correct_ += "p";
    } else if (symbol == '-') {
      correct_ += "u";
    }
  } else {
    if (symbol == '+') {
      correct_ += "+";
    } else if (symbol == '-') {
      correct_ += "-";
    }
  }
  return true;
}

bool ModelValidationInput::CheckBinaryOperator(const size_t pos) {
  correct_ += input_string_[pos];
  if (CheckPositionBinaryOperator(pos)) {
    return true;
  }
  return false;
}

bool ModelValidationInput::CheckPositionBinaryOperator(const size_t pos) {
  if (pos > 0 && pos < input_string_.size() - 1 &&
      (IsNumber(correct_[correct_.size() - 2]) ||
       right_str_[6].find(correct_[correct_.size() - 2]) !=
           right_str_[6].npos) &&
      (IsNumber(input_string_[pos + 1]) ||
       right_str_[7].find(input_string_[pos + 1]) != right_str_[7].npos)) {
    return true;
  }
  return false;
}

bool ModelValidationInput::CheckLongOperetor(size_t* pos) {
  bool status = false;
  for (auto& item : functions_) {
    if (*pos + item.second.first < input_string_.size()) {
      std::string str(&input_string_[*pos],
                      &input_string_[*pos] + item.second.first);

      if (str == item.first) {
        correct_ += item.second.second;
        status = CheckFunction(*pos, item.second.first);
        *pos += item.second.first - 1;
      }
    }
  }
  return status;
}

bool ModelValidationInput::CheckFunction(const size_t pos, const size_t shift) {
  bool status = true;
  size_t end = pos + shift;
  if (correct_.back() == 'm') {
    status = (end < input_string_.size() &&
              CheckPositionBinaryOperator(end - 1) && pos > 0);
  } else {
    if (end >= input_string_.size() ||
        (right_str_[8].find(correct_[correct_.size() - 2]) !=
             right_str_[8].npos &&
         correct_.size() > 1) ||
        right_str_[9].find(input_string_[end]) != right_str_[9].npos)
      status = false;
  }
  return status;
}

void ModelValidationInput::SetString(std::string str) {
  input_string_ = str;
  correct_.clear();
  flags_.point = false;
  flags_.bracket = 0;
  flags_.exp = false;
}

}  // namespace s21