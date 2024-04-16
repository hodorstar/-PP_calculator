/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса ModelCalculationResult
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATION_RESULT_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATION_RESULT_H_

#include <string>
#include <vector>

#include "model_calculator.h"
#include "model_validation_input.h"

namespace s21 {
/*!
 * @brief  Класс ModelCalculationResult необходим для проверки поступившего
 * математического выражения и вычисления значения. Представляет собой часть
 * модуля модели в в паттерне MVC.
 */
class ModelCalculationResult {
 public:
  using vectors_xy = std::pair<std::vector<double>, std::vector<double>>;

  ModelCalculationResult();
  ~ModelCalculationResult();

  /*!
    Вычисляет значение математического выражения с проверкой на наличие ошибок
    записи \return Значение выражения
   */
  double Result();

  /*!
  Вычисляет значения для простроения графика и проверяет математическое
  выражение наналичие ошибок записи
  \param x_max_value Максимальное значение х
  \param step Параметр на который изменяется х
  \return Два массива со значениями x и y
  */
  vectors_xy GraphResult(double x_max_value, double step);

  void SetString(std::string input);
  void SetX(double x);
  int GetError() noexcept { return error_; };

 private:
  ModelValidationInput *validation_input_;
  ModelCalculator *calculation_input_;
  double x_value_;
  int error_;
};
};  // namespace s21

#endif  //  CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATION_RESULT_H_