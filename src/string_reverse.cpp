//
//  string_revers.cpp
//  Cpluspluspractice
//
//  Created by Venkat Pedapati on 22/04/13.
//  Copyright (c) 2013 Venkat Pedapati. All rights reserved.
//

#include "string_reverse.h"

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Returns a string which is exact reverse of str.
 */
char * reverse(char * str)
{
    char *begin = str;
    char *temp = str;
    while(*temp != NULL)
    {
        temp++;
    }
    temp--;
    while(temp > begin)
    {
        swap(temp, begin);
        temp--;
        begin++;
    }
    return str;
}
