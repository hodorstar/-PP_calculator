/*!
 * @file model_calculation_result.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса ModelCalculationResult
 */

#include "model_calculation_result.h"
using vectors_xy = std::pair<std::vector<double>, std::vector<double>>;

namespace s21 {
ModelCalculationResult::ModelCalculationResult()
    : validation_input_(new ModelValidationInput()),
      calculation_input_(new ModelCalculator()),
      x_value_(0),
      error_(0) {}

ModelCalculationResult::~ModelCalculationResult() {
  if (validation_input_) delete validation_input_;
  if (calculation_input_) delete calculation_input_;
}

double ModelCalculationResult::Result() {
  double result = 0.0;
  if (validation_input_->ValidateInput()) {
    calculation_input_->SetString(validation_input_->GetCorrectString());
    calculation_input_->SetX(x_value_);
    result = calculation_input_->Calculator();
    if (std::isnan(result) || std::isinf(result)) error_ = 2;
  } else {
    error_ = 1;
  }
  return result;
}

std::pair<std::vector<double>, std::vector<double>>
ModelCalculationResult::GraphResult(double x_max_value, double step) {
  vectors_xy result;
  if (validation_input_->ValidateInput()) {
    calculation_input_->SetString(validation_input_->GetCorrectString());
    calculation_input_->SetX(0);
    result = calculation_input_->Graph(x_max_value, step);
  } else {
    error_ = 1;
  }
  return result;
}

void ModelCalculationResult::SetString(std::string input) {
  validation_input_->SetString(input);
  error_ = 0;
}

void ModelCalculationResult::SetX(double x) {
  x_value_ = x;
  error_ = 0;
}

};  // namespace s21