#include <sstream>

/**
 * Compresses string orig by replacing successively repeated characters by their count.
 */
char * compress(char *orig, int len)
{
	char *compStr = new char[len];
	int j = 0;
	int charCount = 1;
	char curChar = *orig;
	for(int i = 1;i < len; i++)
	{
		if(j >= len - 1)
		{
			return orig;
		}
		if(*(orig + i) == curChar)
		{
			charCount++;
		}
		else
		{
			*(compStr + j) = curChar;
			std::ostringstream oss;
			oss << charCount;
			int k = 1;
			std::string charCountStr = oss.str();
			for(std::string::iterator it = charCountStr.begin(); it != charCountStr.end(); ++it)
			{
				*(compStr + j + (k++)) = *it;
			}
			j = j + k;
			curChar = *(orig + i);
			charCount = 1;
		}
	}
	// we cannot capture change in last character since string is terminated before it
	// does, so we need extra computation here to deal with it
	if(j < len - 1)
	{
		*(compStr + j) = curChar;
		std::ostringstream oss;
		oss << charCount;
		int k = 1;
		std::string charCountStr = oss.str();
		for(std::string::iterator it = charCountStr.begin(); it != charCountStr.end(); ++it)
		{
			if((j + k) >= len - 1)
			{
				// always check if the new string length is shorter than the original
				// otherwise we'll have to just return the original
				return orig;
			}
			*(compStr + j + (k++)) = *it;
		}
		j = j + k;
	}
	else
	{
		return orig;
	}
	return compStr;
}
