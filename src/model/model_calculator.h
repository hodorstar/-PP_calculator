/*!
 * @file
 * @author hodorsta
 * @brief Заголовочный файл с описанием класса ModelCalculator
 */

#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATOR_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATOR_H_

#include <cmath>
#include <cstring>
#include <stack>
#include <string>
#include <string_view>
#include <vector>

namespace s21 {
/*!
 * @brief  Класс ModelCalculator необходим для перевода поступившего
 * математического выражения в постфиксную запись и вычисления значенияю
 * Представляет собой часть модуля модели в в паттерне MVC.
 */
class ModelCalculator {
 public:
  using vectors_xy = std::pair<std::vector<double>, std::vector<double>>;
  /*!
  Структура Lexeme хранит в себе значения отдельной лексемы маьематического
  выражения.
  */
  struct Lexeme {
    double value;  ///< Значение числа
    int priority;  ///< Значение приоретета
    char symbol;  ///< Значение типа оператора или функции
  };

  ModelCalculator() : str_("0"), x_value_(0) {
    comparison_ = {"+-*/m^", "CSTQcstLlm", "+-*/^pu"};
  };
  // ~ModelCalculator(){} = ;

  /*!
  Вычисляет значения для простроения графика
  \return Значение выражения
  */
  double Calculator();

  /*!
  Вычисляет значения для простроения графика
  \param x_max_value Максимальное значение х
  \param step Параметр на который изменяется х
  \return Два массива со значениями x и y
  */
  vectors_xy Graph(double x_max_value, double step);

  void SetString(std::string str);
  void SetX(double x_val);

 private:
  std::string str_;
  double x_value_;
  std::vector<std::string_view> comparison_;
  std::stack<Lexeme> stack_;
  std::stack<double> number_;
  std::stack<char> operator_;

  double Calculate();
  void CounterBinaryOperator();
  void CounterUnaryOperator();

  void ReversePolishNotation();
  void PushNumber(double value);
  void PushSymbol(char symbol);
  double GetNumber(size_t *pos);
  int GetPriority(char symbol);
  bool IsFunction(char symbol);
  bool IsOperator(char symbol);
  bool IsBinaryOperator(char symbol);
  void InverseStack();
};
bool IsExp(char symbol, bool exp);
bool IsNumber(char symbol);
};  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CALCULATOR_H_