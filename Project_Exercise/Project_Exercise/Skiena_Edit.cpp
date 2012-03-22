/*	Steven Skiena
	Compute String Edit Distance
	March 26, 2002
*/
#include "stdafx.h"
#include <string>
#include "stdio.h"
#include <iostream>
using namespace std;

#define TRUE    1
#define FALSE   0

//typedef int bool;


#define MAXLEN          101     /* longest possible string */

#define MATCH           0       /* enumerated type symbol for match */
#define INSERT          1       /* enumerated type symbol for insert */
#define DELETE          2       /* enumerated type symbol for delete */

typedef struct {
        int cost;               /* cost of reaching this cell */
        int parent;             /* parent cell */
} cell;





cell m[MAXLEN][MAXLEN];         /* dynamic programming table */

/******************************************************************/
//Forward declaration

static void print_matrix(char *s, char *t, bool costQ);
static int string_compare(const char *s, const char *t);
static void reconstruct_path(char *s, char *t, int i, int j);


/******************************************************************/

/*	For normal edit distance computation  */

static void goal_cell(char *s, char *t, unsigned int *i, unsigned int *j)
{
	*i = strlen(s) - 1;
	*j = strlen(t) - 1;
}

static int match(char c, char d)
{
	if (c == d) return(0);
	else return(1);
}

static int indel(char c)
{
	return(1);
}

static void row_init(int i)		/* what is m[0][i]? */
{
	m[0][i].cost = i;
	if (i>0)
		m[0][i].parent =  INSERT;
	else
		m[0][i].parent = -1;
}

static void column_init(int i)	/* what is m[i][0]? */
{
        m[i][0].cost = i;
	if (i>0)
		m[i][0].parent = DELETE;
	else
		m[0][i].parent = -1;
}

/**********************************************************************/

static void match_out(char *s, char *t, int i, int j)
{
	if (s[i] == t[j]) printf("M");
	else printf("S");
}

static void insert_out(char *t, int j)
{
	printf("I");
}

static void delete_out(char *s, int i)
{
        printf("D");
}



/**********************************************************************/

int main_1234()
{
	unsigned int i,j;

	string s("amit");
    string t("tima");		/* input strings */

	//s[0] = t[0] = ' ';

	//scanf("%s",&(s[1]));
	//scanf("%s",&(t[1]));

        //s[1] = "AMIT";
        //t[1] = "MIT";

        //s[strlen(s)-1] = '\0';
        //t[strlen(t)-1] = '\0';

	printf("matching cost = %d \n", string_compare(s.c_str(),t.c_str()/*, strlen(s)-1,strlen(t)-1)*/));

	print_matrix((char *)s.c_str(),(char *)t.c_str(),TRUE);
	printf("\n");
	print_matrix((char *)s.c_str(),(char *)t.c_str(),FALSE);

	goal_cell((char *)s.c_str(),(char *)t.c_str(),&i,&j);

	printf("%d %d\n",i,j);

	reconstruct_path((char *)s.c_str(),(char *)t.c_str(),i,j);
	printf("\n");
        return 0;
}





/**********************************************************************/

static int string_compare(const char *s, const char *t)
{
	unsigned int i,j,k;		/* counters */
	int opt[3];		/* cost of the three options */

	for (i=0; i<MAXLEN; i++) {
		row_init(i);
		column_init(i);
	}

	for (i=1; i<strlen(s); i++)
		for (j=1; j<strlen(t); j++) {
			opt[MATCH] = m[i-1][j-1].cost + match(s[i],t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);

			m[i][j].cost = opt[MATCH];
			m[i][j].parent = MATCH;
			for (k=INSERT; k<=DELETE; k++)
				if (opt[k] < m[i][j].cost) {
					m[i][j].cost = opt[k];
					m[i][j].parent = k;
				}
		}

	goal_cell((char *)s,(char *)t,&i,&j);
	return( m[i][j].cost );
} 

static void reconstruct_path(char *s, char *t, int i, int j)
{
/*printf("trace (%d,%d)\n",i,j);*/

	if (m[i][j].parent == -1) return;

	if (m[i][j].parent == MATCH) {
		reconstruct_path(s,t,i-1,j-1);
		match_out(s, t, i, j);
		return;
	}
        if (m[i][j].parent == INSERT) {
                reconstruct_path(s,t,i,j-1);
		insert_out(t,j);
		return;
        }
        if (m[i][j].parent == DELETE) {
                reconstruct_path(s,t,i-1,j);
		delete_out(s,i);
		return;
        }
}

static void print_matrix(char *s, char *t, bool costQ)
{
	int i,j;			/* counters */
	int x,y;			/* string lengths */

	x = strlen(s);
	y = strlen(t);

	printf("   ");
	for (i=0; i<y; i++)
		printf("  %c",t[i]);
	printf("\n");


	for (i=0; i<x; i++) {
		printf("%c: ",s[i]);
		for (j=0; j<y; j++) {
			if (costQ == TRUE)
				printf(" %2d",m[i][j].cost);
			else
				printf(" %2d",m[i][j].parent);

		}
		printf("\n");
	}
}