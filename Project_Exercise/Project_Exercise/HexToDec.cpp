#include "stdafx.h"
#include <stdio.h>
#include <string>

unsigned int HexToDecimal(char * in)
{
	unsigned int res = 1, i = 0;
	char ch = *(in + 9);
	int len = strlen(in);
	while(len > 2)
	{
		int temp = ch;
		if(temp > 0x39)
		{
			temp = temp - 97 + 10;
		}
		else
			temp -= 0x30;
		res += (0x00000001 << (4*i)) * temp;
		i++;
		len--;
		ch = *(in + 9 - i);
	}
	res -= 1;
	printf("%ud\n",res);
	return res;
}

int main()
{
	char *in = "0x00000005";
	HexToDecimal(in);
	char *in1 = "0xf0000000";
	HexToDecimal(in1);
	char *in2 = "0x000000a5";
	HexToDecimal(in2);
	char *in3 = "0x000001c5";
	HexToDecimal(in3);
	char *in4 = "0x00000050";
	HexToDecimal(in4);
	return 0;
}