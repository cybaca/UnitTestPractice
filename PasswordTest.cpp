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

/*******************************************************************************
 * LEADING
 */
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

TEST(PasswordTest, leading_single_letter_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("Z");
    ASSERT_EQ(1,actual);
}

TEST(PasswordTest, leading_empty_letter_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("");
    ASSERT_EQ(0,actual);
}

TEST(PasswordTest, leading_all_spaces_password)
{
    Password my_password;
    int actual = my_password.count_leading_characters("   ");
    ASSERT_EQ(3,actual);
}

/*******************************************************************************
 * MIXED
 */
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

TEST(PasswordTest, mixed_case_upper_last)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("zzzzzzzzzzzzzzzzzzzZ");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_tilde)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("zzzzzzzzzzzzzzzzzzzZ~");
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

TEST(PasswordTest, mixed_case_newline)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("\n");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_numbers)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("0x718abd");
    ASSERT_EQ(false, actual);
}


TEST(PasswordTest, mixed_case_ul_numbers)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("helloWorld123");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_lower_numbers)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("123hello");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_special)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("Hello-World!!!");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_special_ws)
{
    Password my_password;
    bool actual = my_password.has_mixed_case(" Hello-World!!! ");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, mixed_case_only_special)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("!@#$%^&*()");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, mixed_case_non_ascii)
{
    Password my_password;
    bool actual = my_password.has_mixed_case("àáâäæãåāÇçÐĦĲ");
    ASSERT_EQ(false, actual);
}

#include <climits>
TEST(PasswordTest, mixed_case_long_string)
{
    // string a(INT_MAX, 'a');
    string a(10000, 'a');
    a += "Z";
    Password my_password;
    bool actual = my_password.has_mixed_case(a);
    ASSERT_EQ(true, actual);
}

/*******************************************************************************
 * AUTHENTICATE
 */
TEST(PasswordTest, authenticate_lt_eight)
{
    Password my_password;
    my_password.set("95929");
    bool actual = my_password.authenticate("95929");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, authenticate_leading_gt_three)
{
    Password my_password;
    my_password.set("ggggg95928");
    bool actual = my_password.authenticate("ggggg95929");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, authenticate_no_mixed)
{
    Password my_password;
    my_password.set("abcdefghijk");
    bool actual = my_password.authenticate("abcedfghijk");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, authenticate_default)
{
    Password my_password;
    bool actual = my_password.authenticate("ChicoCA-95929");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, authenticate_not_default)
{
    Password my_password;
    bool actual = my_password.authenticate("chicoCA-95929");
    ASSERT_EQ(false, actual);
}

TEST(PasswordTest, authenticate_set_authenticate)
{
    Password my_password;
    my_password.set("HelloWorld");
    bool actual = my_password.authenticate("HelloWorld");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, authenticate_set_four_leading)
{
    Password my_password;
    my_password.set("HHHHelloWorld");
    bool actual = my_password.authenticate("ChicoCA-95929");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, authenticate_set_five_passwords)
{
    Password my_password;
    my_password.set("HelloWorld");
    my_password.set("HelloWorld1");
    my_password.set("HelloWorld2");
    my_password.set("HelloWorld3");
    my_password.set("HelloWorld4");
    bool actual = my_password.authenticate("HelloWorld4");
    ASSERT_EQ(true, actual);
}

TEST(PasswordTest, authenticate_set_same_password)
{
    Password my_password;
    my_password.set("HelloWorld");
    my_password.set("HelloWorld1");
    my_password.set("HelloWorld2");
    my_password.set("HelloWorld3");
    my_password.set("HelloWorld4");
    my_password.set("HelloWorld1");
    bool actual = my_password.authenticate("HelloWorld4");
    ASSERT_EQ(true, actual);
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
