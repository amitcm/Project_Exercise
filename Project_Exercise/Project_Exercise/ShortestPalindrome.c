/*Computes the shortest palindrome:
 *A Topcoder problem.
 vamsik@engr Apr 19,2008.
 */
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
static char buf[256];
static int len;
unsigned int **LCS = NULL;
char *palindrome= NULL;
char *palindrome_rev = NULL;
unsigned int GetMax3(unsigned int a,unsigned int b,unsigned int c){
	b = (a < b) ? b: a;
	return (b<c)?c:b;
}
/*Builds the LCS between the forward and backwards and finds
a index 'p' which will give minimum # of operations to transform
forward string to backward string.*/
void FindLCSReverse(char *str,unsigned int len){
	int i,j;
	int current_min,max_lcs;
	int imax,jmax,palindex,palindex_r;
	unsigned int operations;
	char path=0;
	for(i=0;i<len;i++){
		LCS[i][0] = 0;
	}
	for(j=0;j<len;j++){
		LCS[0][j] = 0;
	}
	for(i=1;i<len;i++){
		for(j=1;j<len;j++){
			/*use len-j to access other string*/
			if(buf[i] == buf[len-j]){
				LCS[i][j] = LCS[i-1][j-1]+1;
			}else{
				LCS[i][j] = (LCS[i-1][j]>LCS[i][j-1])?LCS[i-1][j]:LCS[i][j-1];
			}
		}
	}
	/*Compute the p which gives minimum inserts to transform 
	 *forward string to backward
	 */
	max_lcs=0;
	imax=len-1;jmax=0;
	for(i=len-1;i>=1;i--){
		if(LCS[i][len-i-1] > max_lcs){
			max_lcs = LCS[i][len-i-1];
			imax = i;
			jmax = len-i-1;
		}
		if(i>0 && LCS[i-1][len-i-1] >= max_lcs){
			max_lcs = LCS[i-1][len-i-1];
			imax = i-1;
			jmax = len-i-1;
		}
	}
	/*Now find the actual string*/
	i=imax;
	j=jmax; 

	palindex_r=0;
	while(i!=0 || j!=0){
		if(i>0 && j>0){
			if(buf[i] == buf[len-j]){
				palindrome_rev[palindex_r++] = buf[i];
				i--; j--;
				continue;
			}
			current_min = (LCS[i-1][j] > LCS[i][j-1])?LCS[i-1][j]:LCS[i][j-1];
			if(current_min == LCS[i-1][j]){
				if(current_min == LCS[i][j-1] && buf[i] < buf[len-j]){
					palindrome_rev[palindex_r++] = buf[len-j];
					j--;
				}else{
					palindrome_rev[palindex_r++] = buf[i];
					i--;
				}
			}else if(current_min == LCS[i][j-1]){
				if(current_min == LCS[i-1][j] && buf[len-j] < buf[i]){
					palindrome_rev[palindex_r++] = buf[i];
					i--;
				}else{
					palindrome_rev[palindex_r++] = buf[len-j];
					j--;
				}
			}
		}else if(j==0){
			palindrome_rev[palindex_r++] = buf[i];
			i--;
		}else if(i==0){
			palindrome_rev[palindex_r++] = buf[len-j];
			j--;
		}
		/*path=1 (left) path=2 (down) path=3 (diag)*/
	}

	for(i=0;i<palindex_r;i++){
		palindrome[palindex_r-1-i] = palindrome_rev[i];
	}
	palindrome_rev[palindex_r] = '\0';
	palindrome[palindex_r] = '\0';

	/*printf("imax = %u jmax = %u len=%u \n",imax,jmax,len);*/
	if(imax+jmax==len-1){
		printf("%s%s\n",palindrome,palindrome_rev);
	}else{
		printf("%s%c%s\n",palindrome,buf[imax+1],palindrome_rev);
	}
}

int main(){
	unsigned int i;
	buf[0]='C';
	scanf("%255s",&buf[1]);
	len  = strlen(buf);
	LCS = (unsigned int**)malloc(sizeof(unsigned int*)*(len+1));
	palindrome = (char *)malloc(sizeof(char)*2*len);
	palindrome_rev = (char *)malloc(sizeof(char)*2*len);
	assert(LCS && palindrome && palindrome_rev);
	for(i=0;i<len;i++){
		LCS[i] = NULL;
		LCS[i] = (unsigned int *)malloc(sizeof(unsigned int)*(len+1));
		assert(LCS[i]);
	}
	FindLCSReverse(buf,len);
}
