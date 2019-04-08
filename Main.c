#include <stdio.h> 
#include <ctype.h>
/* Global declarations */ /* Variables */ 
int  charClass; 
char  lexeme[100]; 
char  nextChar; 
int  lexLen;
int  token; 
int  nextToken; 
FILE *in_fp, *fopen();
/* Function declarations */ 
void  addChar();
int main(void) {
	printf("Hello World\n");
	return 0;
}