#include <add.hpp>
#include <gtest/gtest.h>

TEST(add, test_add_adddsTwoNumbers)
{
    int expected = 1 + 2;
    int actual = add(1, 2);

    ASSERT_EQ(expected, actual);
}