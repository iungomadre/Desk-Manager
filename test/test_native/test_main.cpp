#include <unity.h>
#include <add.hpp>

void test_add_addsTwoNumbers()
{
    int expected = 1 + 2;
    int actual = add(1, 2);

    TEST_ASSERT_EQUAL(actual, expected);
}


int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_add_addsTwoNumbers);
    UNITY_END();
}
