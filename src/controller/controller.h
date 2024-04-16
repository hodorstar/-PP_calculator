/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса Controller
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include <QString>

#include "../model/model_calculation_result.h"

namespace s21 {
/*!
 * @brief  Класс Controller представляет собой модуль контроллера в паттерне
 * MVC. Осуществляет модификацию модели.
 */
class Controller {
 public:
  using vectors_xy = std::pair<std::vector<double>, std::vector<double>>;

  Controller(ModelCalculationResult *model) : calc_(model), err_(0){};
  ~Controller(){};

  double Calculation(QString input_expression, double x_value);

  vectors_xy CalcGraph(QString input_expression, double x_max_value,
                       double step);

  int GetErr() noexcept { return err_; };

 private:
  ModelCalculationResult *calc_;
  int err_;
};

};  // namespace s21

#endif  //   CPP3_S21_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_