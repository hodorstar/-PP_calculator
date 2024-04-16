#ifndef CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_CALCULATION_H_
#define CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_CALCULATION_H_

#include <gtest/gtest.h>

#include <map>

#include "../model/model_calculation_result.h"

class TestModelCalculationResult : public ::testing::Test {
 public:
  TestModelCalculationResult() : formula_(new s21::ModelCalculationResult()) {
    // initialization code here
  }

  ~TestModelCalculationResult() {
    if (formula_) delete formula_;
  }

  void SetUp() {}

  void TearDown() {}

  double SetStringAndX(std::string input, double x);
  std::pair<std::vector<double>, std::vector<double>> SetStringGraph(
      std::string input);
  int GetErrorForTest();

  std::map<std::string, double> request_function = {
      {"sin1+1", 1.84147098481},
      {"cos(1) + 2", 2.54030230586},
      {"tan(1+2)", -0.14254654307},
      {"cos(sin(0))", 1.000000},
      {"2 * -cos0", -2.000000},
      {"sin-5", 0.95892427466},

      {"(8+(-2))-1mod2", 5.000000},
      {"15*atan-101+35", 11.58656509689638},
      {"-sin(cos(tan(sqrt(6mod2*(-2-4)))))", -0.8414709848},
      {"-sin(cos(tan(sqrt(-2+4))))", -0.84076958709},
      {"-sin(cos(tan(2)))", 0.54495923728},
      {"sin(cos(tan(2)))", -0.54495923728},
      {"sqrt(4)", 2.0},
      {"sqrt4", 2.0},
      {"sqrt(-2+6)", 2.0},
      {"cos.2", 0.98006657784},
      {"tan(log(3)) + 3 / 8", 0.89195732177},
      {"ln(10)", 2.30258509299},
      {"acos1", 0.000000},
      {"asin0", 0.000000},
      {"5mod3", 2},
      {"+10--log(100)", 12},
      {"-atan(52)*-9.5", 14.7398953},
      {"-(-(-((sin(cos(48)^(2)))/(tan(2)^(2)))+3*-6))", -18.0834475},
      {"-cos2", 0.41614683654}};

  std::map<std::string, double> request_number = {
      {"1*+2", 2.000000},
      {"3/-3", -1.000000},
      {"3--3", 6.000000},
      {"3-(-3)", 6.000000},
      {"3+++3", 6.000000},
      {"3---3", 0.000000},
      {"(1+3)(2-1)", 4.000000},
      {"(1+3)2 +4", 12.000000},
      {"5+2(7-3)", 13.000000},
      {"1*-2", -2.000000},
      {"-2^2", 4.000000},
      {"10.*.2", 2.000000},
      {"(2+1)+2.(1+1)", 7.000000},
      {"2/1+2+3+4*5*6^7-12+((1000+500*2)*201)", 6000715.000000},
      {"2^2^3", 256.0},
      {"2^(2^3)", 256.0},
      {"(2+1)+2.(1+1)", 7},
      {"(1+5)^(2)(1+1)", 72},
      {"1e+11", 100000000000},
      {"45e+3", 45000},
      {"1e", 1},

      {"2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)", 6000000.000000}};

  std::map<std::string, double> x_val = {
      {"2+x", 4.000000}, {"xx", 4.000000}, {"x(3+5)", 16.000000}};

  std::map<std::string, int> error = {
      {"1+(*1)", 1}, {"1/0", 2}, {"(.)(.)", 1}, {"4/0", 2}};

 private:
  s21::ModelCalculationResult* formula_;
};

#endif  // CPP3_S21_SMARTCALC_V2_0_1_SRC_TESTS_TEST_CALCULATION_H_