//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"

TEST(AddTest, SimpleAddTest){
    EXPECT_EQ(Add(2, 2), 4);
}

