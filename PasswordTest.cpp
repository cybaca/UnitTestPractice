/**
 * Unit Tests for Password class
**/

#include <gtest/gtest.h>
#include "Password.h"

class PasswordTest : public ::testing::Test
{
    protected:
    PasswordTest(){} //constructor runs before each test
    virtual ~PasswordTest(){} //destructor cleans up after tests
    virtual void SetUp(){} //sets up before each test (after constructor)
    virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PasswordTest, smoke_test)
{
    ASSERT_TRUE( 1 == 1 );
}

TEST(PasswordTest, four_leading_char_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("ZZZZjklasdj");
    ASSERT_EQ(4,actual);
}

TEST(PasswordTest, one_leading_char_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("Zjklasdj");
    ASSERT_EQ(1,actual);
}

TEST(PasswordTest, single_letter_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("Z");
    ASSERT_EQ(1,actual);
}

TEST(PasswordTest, empty_letter_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("");
    ASSERT_EQ(0,actual);
}

TEST(PasswordTest, all_spaces_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("   ");
    ASSERT_EQ(3,actual);
}

TEST(PasswordTest, mixed_case_single_upper)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("Z");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_single_lower)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("z");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_2char_upper_first)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("Zz");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_2char_lower_first)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("zZ");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_empty_string)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_3_spaces)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("  ");
    ASSERT_EQ(false, actual);
}


/*
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <limits.h>
TEST(PasswordTest, very_long_password)
{
    char *m = (char *)malloc(INT_MAX+2);
    memset(m, 0, INT_MAX + 2);
    memcpy(m, "a", INT_MAX);
    Password my_password;
    int actual = my_password.count_leading_characters(m);
    ASSERT_EQ(INT_MAX, actual);
}
*/
