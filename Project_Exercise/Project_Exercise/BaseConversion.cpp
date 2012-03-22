#include "stdafx.h"
#include "BaseConversion.h"

int toDecimal(int n, int b)
{
	int result = 0;
	int multiplier = 1;

	while(n > 0)
	{
		result += n % 10 * multiplier;
		multiplier *= b;
		n /= 10;
	}

	return result;
}

// For base 2 < b < 10
int fromDecimal(int n, int b)
{
	int result = 0;
	int multiplier = 1;
	while(n > 0)
	{
		result += n % b * multiplier;
		multiplier *= 10;
		n /= b;
	}
	return result;
}

// For base b > 10
string fromDecimal2(int n, int b)
{
   string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   string result = "";
   while(n > 0)
   {
      result = chars[n % b] + result;
      n /= b;
   }
      
   return result;
}

// Note the zero thing in the base conversion fucks up the case of converting number to string
string numToStr(int n) {
	string str(1, 'a' + n % 26);
	n = n / 26;
	while (n != 0) {
		str = (char)('a' + (n-1) % 26) + str;
		n = (n-1) / 26;
	}
	return str;
}