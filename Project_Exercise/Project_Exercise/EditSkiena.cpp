#include "stdafx.h"
#include<stdio.h>
#include<string>
using namespace std;
#define MAXLEN 11
#define MATCH 0 /* symbol for match */
#define INSERT 1 /* symbol for insert */
#define DELETE 2 /* symbol for delete */

typedef struct 
{
	int cost; /* cost of reaching this cell */
	int parent; /* parent cell */
} cell;

cell m[MAXLEN][MAXLEN]; /* dynamic programming table */

static void printMatrix(int i, int j)
{
	for(int l = 0; l < i; l++)
		{
			for(int p = 0; p < j; p++)
			{
				printf("%d\t", m[l][p].cost);
			}
			printf("\n");
		}
}

void printMatrixP(int i, int j)
{
	for(int l = 0; l < i; l++)
		{
			for(int p = 0; p < j; p++)
			{
				printf("%d\t", m[l][p].parent);
			}
			printf("\n");
		}
}

void column_init(int i)
{
	m[i][0].cost = i;
	if (i>0)
		m[i][0].parent=DELETE;
	else
		m[0][i].parent = -1;
}


int match(char c, char d)
{
	if (c == d) return(0);
	else return(1);
}

int indel(char c)
{
	return(1);
}

void row_init(int i)
{
	m[0][i].cost = i;
	if (i>0)
		m[0][i].parent=INSERT;
	else
		m[0][i].parent = -1;
}


//Nothing but bakwas. gives the index of the cell where we'll get the result
void goal_cell(char *s, char *t, int *i, int *j)
{
*i = strlen(s) - 1;
*j = strlen(t) - 1;
}



int string_compare(char *s, char *t)
{
	int i,j,k; /* counters */
	int opt[3]; /* cost of the three options */
	for (i=0; i<MAXLEN; i++) {
		row_init(i);
		column_init(i);
	}
	printMatrix(i, i);
	for (i=1; i<strlen(s); i++){
		for (j=1; j<strlen(t); j++) {
			opt[MATCH] = m[i-1][j-1].cost + match(s[i],t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);
			m[i][j].cost = opt[0];
			m[i][j].parent = 0;
			for (k=1; k<3; k++)
				if (opt[k] < m[i][j].cost) {
					m[i][j].cost = opt[k];
					m[i][j].parent = k;
				}
		}
	}
	printMatrix(i, j);
	goal_cell(s,t,&i,&j);
	return( m[i][j].cost );
}

int main_Skiena()
{
	char* s = " mykma";
	char* t = " amkym";
	printf("%d",string_compare(s, t));
	return 0;
}