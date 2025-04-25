#include "CppUTest/TestHarness.h"

TEST_GROUP(SprintfTest) {};

TEST(SprintfTest, PrintsZero) {
    char output[5];
    sprintf(output, "%d", 0);
    STRCMP_EQUAL("0", output);
}

