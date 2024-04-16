#include "test.h"

TEST_F(TestModelCalculationResult, Formulas) {
  for (auto& item : request_function) {
    double result = std::fabs(SetStringAndX(item.first, 0));
    double fabs_result = std::fabs(result - std::fabs(item.second));
    EXPECT_LT(fabs_result, 10e-7);
    if (fabs_result > 10e-7)
      std::cout << item.first << " != " << result << " = " << item.second
                << "\n";
  }
}

TEST_F(TestModelCalculationResult, NumericFormulas) {
  for (auto& item : request_number) {
    double result = std::fabs(SetStringAndX(item.first, 0));
    double fabs_result = std::fabs(result - std::fabs(item.second));
    EXPECT_LT(fabs_result, 10e-7);
    if (fabs_result > 10e-7)
      std::cout << item.first << " != " << result << " = " << item.second
                << "\n";
  }
}

TEST_F(TestModelCalculationResult, XValue) {
  for (auto& item : x_val) {
    double result = std::fabs(SetStringAndX(item.first, 2));
    double fabs_result = std::fabs(result - std::fabs(item.second));
    EXPECT_LT(fabs_result, 10e-7);
    if (fabs_result > 10e-7)
      std::cout << item.first << " != " << item.second << "\n";
  }
}

TEST_F(TestModelCalculationResult, Error) {
  for (auto& item : error) {
    SetStringAndX(item.first, 0);
    int result = GetErrorForTest();
    EXPECT_EQ(result, item.second);
    if (GetErrorForTest() != item.second)
      std::cout << item.first << " = " << item.second << "\n";
  }
}

TEST_F(TestModelCalculationResult, Graph) {
  std::pair<std::vector<double>, std::vector<double>> vector_xy =
      SetStringGraph("x");
  double expect = -10;
  for (size_t i = 0; i < vector_xy.first.size(); i++, expect += 1) {
    EXPECT_EQ(vector_xy.first[i], expect);
    EXPECT_EQ(vector_xy.second[i], expect);
  }
}

TEST_F(TestModelCalculationResult, GraphError) {
  SetStringGraph("x(5))");
  int result = GetErrorForTest();
  EXPECT_EQ(result, 1);
}

double TestModelCalculationResult::SetStringAndX(std::string input, double x) {
  formula_->SetString(input);
  formula_->SetX(x);
  return formula_->Result();
}

std::pair<std::vector<double>, std::vector<double>>
TestModelCalculationResult::SetStringGraph(std::string input) {
  formula_->SetString(input);
  formula_->SetX(0);
  return formula_->GraphResult(10, 1);
}

int TestModelCalculationResult::GetErrorForTest() {
  return formula_->GetError();
}