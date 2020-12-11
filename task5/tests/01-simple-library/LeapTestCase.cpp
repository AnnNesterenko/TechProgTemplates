//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"

#include <Functions.h>

TEST(LeapTest, PositiveTest1){
    EXPECT_TRUE(IsLeap(2000));
}

TEST(LeapTest, NegativeTest1){
    EXPECT_FALSE(IsLeap(1300));
}

TEST(LeapTest, PositiveTest2){
    EXPECT_TRUE(IsLeap(2020));
}

TEST(LeapTest, NegativeTest2){
    EXPECT_FALSE(IsLeap(1999));
}

TEST(LeapTest, InvalidYearTest){
    EXPECT_THROW(IsLeap(-1), std::invalid_argument);
}

TEST(LeapTest, InvalidYearTest0){
    EXPECT_THROW(IsLeap(0), std::invalid_argument);
}




