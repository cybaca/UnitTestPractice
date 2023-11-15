#include "Password.h"
#include <string>

using std::string;

/**
 * constructor sets the default password to "ChicoCA-95929"
 */
Password::Password()
{
    set("ChicoCA-95929");
}

/**
 * receives a password and sets the latest in pass_history to it if and
 * only if it meets all criteria:
 * 1. The password is at least 8 letters long
 * 2. It has no more than 3 of the same leading characters
 * 3. It has mixed case (at least one upper case and at least one lower
 * case)
 * 4. It was not a previous password in the history
 */
void
Password::set(string s)
{
    if (s.length() < 8)
        return;

    if (count_leading_characters(s) > 3)
        return;

    if (!has_mixed_case(s))
        return;

    for (const auto &p : pass_history)
        if (p.compare(s) == 0)
            return;

    pass_history.push_back(s);
}

/**
 * receives a string and authenticates it against the latest password in
 * the pass_history, returning true for an exact match or false when it does
 * not match or if a password has not been set.
 */
bool
Password::authenticate(string s)
{
    if (pass_history.empty())
        return false;

    return pass_history.back().compare(s) == 0;
}



/**
 * The function receives a string counts how many times the same character 
 * occurs at the beginning of the string, before any other characters (or the
 * end of the string). The function is case-sensitive so 'Z' is different than
 * 'z' and any ASCII characters are allowed.
 */
int
Password::count_leading_characters(string phrase)
{
    int repetition = 1;
    int index = 0;

    while( index < phrase.length()-1 && phrase[index] == phrase[index+1] ){
        repetition++;
        index++;
    }
    return repetition;
}

bool
Password::has_mixed_case(string phrase)
{
    bool has_lower = false;
    bool has_upper = false;
    for (int i = 0; i < phrase.length(); ++i) {
        if (phrase[i] >= 0x61 && phrase[i] <= 0x7a)
            has_lower = true;
        if (phrase[i] >= 0x41 && phrase[i] <= 0x5a)
            has_upper = true;
    }

    return has_lower && has_upper;
}

bool
Password::_has_mixed_case(string phrase)
{
    bool hasLower = false;
    bool hasUpper = false;

    for (char c: phrase) {
        if (c >= 'a' && c <= 'z') hasLower = true;
        if (c >= 'A' && c <= 'Z') hasUpper = true;
    }

    return hasLower && hasUpper;
}
