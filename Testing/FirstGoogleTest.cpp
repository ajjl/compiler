#include "gtest/gtest.h"

/*
 * Try out gtest with a simple example
 * more info at: 
 * https://github.com/google/googletest/blob/master/googletest/docs/Samples.md
 * https://github.com/google/googletest
 */



int Return_Two_Dummy() {
  return 2;
}

template<typename TInputType>
bool Return_Is_Equal(TInputType A, TInputType B) {
  return A == B;
}

TEST(Return_Two_Test, DidItWork) {
  EXPECT_EQ(2, Return_Two_Dummy());
  EXPECT_EQ(2, Return_Two_Dummy());
}

TEST(ReturnEqualTest, didItWork) {
  EXPECT_TRUE(Return_Is_Equal(1,1));
  EXPECT_FALSE(Return_Is_Equal(2,1));
}


int main(int argc, char** argv) {
  printf("In main of gtest\n");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
