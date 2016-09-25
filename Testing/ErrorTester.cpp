#include "gtest/gtest.h"
#include "../errors.h"

TEST(Errors,fatal) {
  EXPECT_DEATH(error_fatal(static_cast<error_message>(1),1),  "Fatal error on line");
}

int main(int argc, char** argv) {
  printf("In main of gtest\n");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
