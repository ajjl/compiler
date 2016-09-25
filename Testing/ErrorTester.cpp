#include "gtest/gtest.h"
#include "../errors.h"

TEST(Errors,fatal) {
  std::cout << "hello test" << std::endl;
  EXPECT_DEATH(error_fatal(static_cast<error_message>(0),1),  "Cannot open input file.");
  EXPECT_DEATH(error_fatal(static_cast<error_message>(1),1),  "String pool overflow.");
  EXPECT_DEATH(error_fatal(static_cast<error_message>(2),1),  "Symbol table overflow");
  EXPECT_DEATH(error_fatal(static_cast<error_message>(3),1),  "Value too large.");
  EXPECT_DEATH(error_fatal(static_cast<error_message>(4),1),  "Unclosed string.");
  EXPECT_DEATH(error_fatal(static_cast<error_message>(5),1),  "Identifier or string too long.");
}

#if 0
TEST(Errors, warnings) {
  EXPECT_DEATH(error_warn(static_cast<error_message>(0),1),  "Cannot open input file.");
  EXPECT_DEATH(error_warn(static_cast<error_message>(1),1),  "String pool overflow.");
  EXPECT_DEATH(error_warn(static_cast<error_message>(2),1),  "Symbol table overflow");
  EXPECT_DEATH(error_warn(static_cast<error_message>(3),1),  "Value too large.");
  EXPECT_DEATH(error_warn(static_cast<error_message>(4),1),  "Unclosed string.");
  EXPECT_DEATH(error_warn(static_cast<error_message>(5),1),  "Identifier or string too long.");
}
#endif

int main(int argc, char** argv) {
  printf("In main of gtest\n");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
