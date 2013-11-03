#include "palindrome.h"

bool isPalindrome(std::string s)
{
    int end = s.size() - 1;
    int begin = 0;
    while(true)
    {
        while(begin < s.size() && s.at(begin) == ' ') begin++;
        while(0 <= end && s.at(end) == ' ') end--;

        if(begin >= end) return true;
        if(s.at(begin++) != s.at(end--))
        {
            return false;
        }
    }
}