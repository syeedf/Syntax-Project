#include <stdio.h> 
#include <ctype.h>
/* Global declarations */ /* Variables */
int  charClass;
char  lexeme[100];
char  nextChar;
int  lexLen;
int  token;
int  nextToken;
FILE *in_fp;
int read;
/* Function declarations */
void  addChar();
void  getChar();
void  getNonBlank();
void getLine();
int  lex();
void expr();
void error();
/* Character classes */
#define LETTER 0 
#define DIGIT 1 
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10 
#define IDENT 11 
#define ASSIGN_OP 20 
#define ADD_OP 21 
#define SUB_OP 22 
#define MULT_OP 23 
#define DIV_OP 24 
#define LEFT_PAREN 25 
#define RIGHT_PAREN 26
/* main driver */
int main() {
	/* Open the input data file and process its contents */
	if ((in_fp = fopen("infile.txt", "r")) == NULL)
		printf("ERROR - cannot open front.in \n");
	else {
		getChar();
		do
		{
			lex();
			expr();
		}
		while (nextToken != EOF || nextToken == '\n');
	}
	return 0;
}
/* lookup - a function to lookup operators and  parentheses and return the token */
int  lookup(char  ch) {
	switch (ch) {
	case  '(':
		addChar();
		nextToken = LEFT_PAREN;
		break;
	case  ')':
		addChar();
		nextToken = RIGHT_PAREN;
		break;
	case  '+':
		addChar();
		nextToken = ADD_OP;
		break;
	case  '-':
		addChar();
		nextToken = SUB_OP;
		break;
	case  '*':
		addChar();
		nextToken = MULT_OP;
		break;
	case  '/':
		addChar();
		nextToken = DIV_OP;
		break;
	default:
		addChar();
		nextToken = EOF;
		break;
	}
	return  nextToken;
}
/* addChar - a function to add nextChar to lexeme */
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else    printf("Error - lexeme is too long \n");
}
/*void getLine()

{

	while (read = fgetc("infile.txt") != EOF)

	{

		getChar(line);

	}

}
*/
void getChar() {
	if ((nextChar = getc(in_fp)) != EOF) {
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else  charClass = UNKNOWN;
	}
	else     charClass = EOF;
}
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
	case  LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = IDENT;
		break;
	case  DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
		break;
	case  UNKNOWN:
		lookup(nextChar);
		getChar();
		break;
	case  EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	}
	printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	return  nextToken;
}
void factor() {
	if (nextToken == IDENT || nextToken == INT_LIT) {
		printf("Enter <factor>\n");
		lex();
	}
	else if (nextToken == '\n')
	{
		printf("Exit <factor>\n");
	}
	else {
		if (nextToken == LEFT_PAREN) {
			lex();
			expr();
			if (nextToken == RIGHT_PAREN)
				lex();
			else {
				error();
			}
		}
		else {
			printf("Its this error.");
			error();
		}
	}
	printf("Exit <factor>\n");
}
void error() {
	printf("There is an error.\n");
}
void  term() {
	printf("Enter <term>\n");
	factor();
	while (nextToken == MULT_OP || nextToken == DIV_OP) {
		lex();
		factor();
	}  printf("Exit <term>\n");
}
void  expr() {
	printf("Enter <expr>\n");
	term();
	while (nextToken == ADD_OP || nextToken == SUB_OP) {
		lex();
		term();
	}  printf("Exit <expr>\n");
}  /* End of function expr */