#include "gtest/gtest.h"


GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners =  testing::UnitTest::GetInstance()->listeners();

    return RUN_ALL_TESTS();
}

