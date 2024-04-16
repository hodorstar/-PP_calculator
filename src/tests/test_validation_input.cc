#include "test.h"

bool TestModelValidationInput::SetString(std::string str) {
  validation_input_->SetString(str);
  bool res = validation_input_->ValidateInput();
  return res;
}

TEST_F(TestModelValidationInput, UbnormalInput) {
  for (auto& item : ubnormal_input) {
    bool res = SetString(item);
    EXPECT_FALSE(res);
    if (res) std::cout << item << "\n";
  }
}

TEST_F(TestModelValidationInput, NormalInput) {
  for (auto& item : normal_input) {
    bool res = SetString(item);
    EXPECT_TRUE(res);
    if (!res) std::cout << item << "\n";
  }
}