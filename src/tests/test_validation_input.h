#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_VALIDATION_INPUT_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_VALIDATION_INPUT_H_

#include <gtest/gtest.h>

#include "../model/model_validation_input.h"

class TestModelValidationInput : public ::testing::Test {
 public:
  TestModelValidationInput()
      : validation_input_(new s21::ModelValidationInput()) {
    // initialization code here
  }

  ~TestModelValidationInput() {
    if (validation_input_) delete validation_input_;
  }

  void SetUp() {}

  void TearDown() {}

  bool SetString(std::string str);

  std::vector<std::string> ubnormal_input{
      "()",
      "2+2ban",
      ")2+2",
      "*2+2",
      "/2+2",
      "^2+2",
      "mod2+2",
      "2+2+",
      "2+2-",
      "ban2+2",
      "2+2(",
      "2+2*",
      "2+2/",
      "2+2^",
      "(2+2))",
      "1+(*1)",
      "1+(/1)",
      "1+(^1)",
      "1+(mod1)",
      "1+*1",
      "3//3",
      "3*^3",
      "3**3",
      "3^^3",
      "sinsin1",
      "cosatan1",
      "mod",
      " log",
      "3modmod4",
      "1-/+2",
      "3+mod2",
      "1.22.4+5",
      "1.1.1-6",
      "1+)1+3(* (-3+5)",
      "*",
      "-",
      "sin",
      "/",
      "(.)*(.)",
      "sincos",
      "tan(cos)",
      "",
      "10e-e",
      "1e10e",
      "(1+2))-(",
      "11111111111111111111111111+111111111111111111111111111+"
      "1111111111111111111111111111+11111111111111111111111111+"
      "1111111111111111111+111111111111111111+1111111111111111111111+"
      "1111111111111111111+11111111111111111111+111111111111111111+"
      "111111111111111111+111111111111111111+1111111111111111"

  };

  std::vector<std::string> normal_input{
      "1+(+1)",   "1+(-1)",     "sin(1)",
      "cos(1)",   "tan(1)",     "atan(1)",
      "acos(1)",  "asin(1)",    "2    + 5    - 3",
      "1*+2",     "3/-3",       "3+++3",
      "3---3",    "(1+3)(2-1)", "(1+3)2 +4",
      "5+2(7-3)", "xx",         "x(3-x)",
      "(4*2)x",   "xsin1",      "(2.+1)*(.2-0.2)",
      "1.2+3.5",  "2cos2",      "1e-4"};

  // put in any custom data members that you need
 private:
  s21::ModelValidationInput *validation_input_;
};

#endif  // CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_VALIDATION_INPUT_H_