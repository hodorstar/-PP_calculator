/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса ModelValidationInput
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_VALIDATION_INPUT_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_VALIDATION_INPUT_H_

#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "model_calculator.h"

namespace s21 {
/*!
 * @brief  Класс ModelValidationInput необходим для для проверки поступившего
 * математического выражения на наличие ошибок записию Представляет собой часть
 * модуля модели в в паттерне MVC.
 */
class ModelValidationInput {
 public:
  using map_of_functions = std::map<std::string, std::pair<size_t, char>>;
  /*!
 Структура Flags указывает на наличие в математическом выражении или в его
 части определенных объектов
 */
  struct Flags {
    bool point;  ///< Указывает на наличие точки
    int bracket;  ///< Указывает на наличии открывающей скобки
    bool exp;  ///< Указывает на наличие экспоненциальной формы записи числа
  };

  ModelValidationInput();
  ~ModelValidationInput(){};

  /*!
  Проверяет математическое выражение наналичие ошибок записи
  */
  bool ValidateInput();

  std::string GetCorrectString() noexcept { return correct_; }
  void SetString(std::string input);

 private:
  Flags flags_;
  std::string input_string_;
  std::string correct_;
  map_of_functions functions_;
  std::vector<std::string_view> right_str_;

  bool CheckNumber(size_t* pos);
  void CheckX(const size_t pos);

  bool CheckLeftBracket(const size_t pos);
  bool CheckRightBracket(const size_t pos);
  bool CheckUnarOperator(const size_t pos, const char symbol);
  bool CheckBinaryOperator(const size_t pos);
  bool CheckPositionBinaryOperator(const size_t pos);
  bool CheckLongOperetor(size_t* pos);
  bool CheckFunction(const size_t pos, const size_t shift);
};

};  // namespace s21

#endif  //  CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_VALIDATION_INPUT_H_