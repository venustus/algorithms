/*
 * string_normalize.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: venkat
 */


char * normalize(char *str, int len)
{
	int *finalPos = new int[len];
	int factor = 1;
	finalPos[0] = 0;
	for(int i = 1; i < len; i++)
	{
		if(*(str + i) != ' ')
		{
			finalPos[i] = finalPos[i-1] + 1;
		}
		else {
			finalPos[i] = 2 * (factor++) + i;
		}
	}
	for(int i = len - 1; i >= 0; i--)
	{
		if(*(str + i) == ' ')
		{
			*(str + finalPos[i]) = '0';
			*(str + finalPos[i] - 1) = '2';
			*(str + finalPos[i] - 2) = '%';
		}
		else
		{
			*(str + finalPos[i]) = *(str + i);
		}
	}
	return str;
}




