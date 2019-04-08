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
void  getChar(); 
void  getNonBlank(); 
int  lex();
/* Character classes */ 
#define LETTER 0 
#define DIGIT 1 
#define UNKNOWN 99
/* Token codes */ 
#define INT_LIT 10 
#define IDENT 11 
#define ASSIGN_OP 20 
#define ADD_OP 21 
int main(void) {
	printf("Hello World\n");
	return 0;
}