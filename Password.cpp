#include "Password.h"
#include <string>

using std::string;

/*
  The function receives a string counts how many times the same character 
  occurs at the beginning of the string, before any other characters (or the
  end of the string). The function is case-sensitive so 'Z' is different than
  'z' and any ASCII characters are allowed.
*/
int Password::count_leading_characters(string phrase){
    int repetition = 1;
    int index = 0;

    while( index < phrase.length()-1 && phrase[index] == phrase[index+1] ){
        repetition++;
        index++;
    }
    return repetition;
}

bool Password::has_mixed_case(string phrase)
{
    if (phrase.empty())
        return false;

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
