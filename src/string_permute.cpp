//
//  string_permute.cpp
//  Cpluspluspractice
//
//  Created by Venkat Pedapati on 22/04/13.
//  Copyright (c) 2013 Venkat Pedapati. All rights reserved.
//

#include "string_permute.h"

bool isPermutation(char *a, char *b)
{
    int len_a = 0;
    int len_b = 0;
    int present[256];
    for(int i = 0; i < 256; i++)
    {
        present[i] = 0;
    }
        
    char *temp = b;
    while(*temp != NULL)
    {
        present[*temp]++;
        len_b++;
        temp++;
    }
    temp = a;
    while(*temp != NULL)
    {
        if(--present[*temp] < 0)
        {
            return false;
        }
        len_a++;
        temp++;
    }
    return len_a == len_b;
}