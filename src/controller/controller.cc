/*!
 * @file model_calculation_result.cc
 * @author hodorsta
 * @brief Содержит реализацию функций класса ModelCalculationResult
 */

#include "controller.h"

namespace s21 {
double Controller::Calculation(QString input_expression, double x_value) {
  std::string input = input_expression.toStdString();
  calc_->SetString(input);
  calc_->SetX(x_value);
  double result = calc_->Result();
  err_ = calc_->GetError();
  return result;
}

std::pair<std::vector<double>, std::vector<double>> Controller::CalcGraph(
    QString input_expression, double x_max_value, double step) {
  std::string input = input_expression.toStdString();
  calc_->SetString(input);
  calc_->SetX(0);
  std::pair<std::vector<double>, std::vector<double>> result =
      calc_->GraphResult(x_max_value, step);
  err_ = calc_->GetError();
  return result;
}

};  // namespace s21