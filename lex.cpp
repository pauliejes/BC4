#include<iostream>
#include"general.h"
#include"lex.h"

using namespace std;


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char *ch)
{

  if(strcmp(ch, "(") == 0){
			addChar();
			nextToken = LEFT_PAREN;
  }
  else if(strcmp(ch, ")") == 0){
			addChar();
			nextToken = RIGHT_PAREN;
  }
  else if(strcmp(ch, "+") == 0){
			addChar();
			nextToken = ADD_OP;
  }
  else if(strcmp(ch, "-") == 0){
			addChar();
			nextToken = SUB_OP;
  }
  else if(strcmp(ch, "*") == 0){
			addChar();
			nextToken = MULT_OP;
  }
  else if(strcmp(ch, "/") == 0){
			addChar();
			nextToken = DIV_OP;
  }
  else if(strcmp(ch, "%") == 0){
			addChar();
			nextToken = MOD_OP;
  }
  else if(strcmp(ch, "^") == 0){
			addChar();
			nextToken = POW_OP;
  }
  else if(strcmp(ch, "=") == 0){
			addChar();
			nextToken = ASSIGN_OP;
  }
  else if(strcmp(ch, "==") == 0){
			addChar();
			nextToken = EQL_OP;
  }
  else if(strcmp(ch, "!=") == 0){
			addChar();
			nextToken = NOTEQL_OP;
  }
  else if(strcmp(ch, "<") == 0){
			addChar();
			nextToken = LESS_OP;
  }      
  else if(strcmp(ch, ">") == 0){
			addChar();
			nextToken = GREAT_OP;
  }  
  else if(strcmp(ch, "<=") == 0){
			addChar();
			nextToken = LESSEQL_OP;
  }      
  else if(strcmp(ch, ">=") == 0){
			addChar();
			nextToken = GREATEQL_OP;
  }  
  else if(strcmp(ch, "#") == 0){
			addChar();
			nextToken = COMMENT_ID;
  }       
  else if(strcmp(ch, "=") == 0){
			addChar();
			nextToken = ASSIGN_OP;
  }
  else{
			addChar();
			nextToken = EOF;
  }
  return nextToken;
}

int reservedWordLookup(char * lexeme) {
  if (strcmp(lexeme,"quit") == 0) {
	  return QUIT;
   }
   else if (strcmp(lexeme,"dump") == 0) {
	  return DUMP;
   }
   else if (strcmp(lexeme,"if") == 0) {
	  return IF;
   }
   else if (strcmp(lexeme,"then") == 0) {
	  return THEN;
   }
   else if (strcmp(lexeme,"else") == 0) {
	  return ELSE;
   }
   else if (strcmp(lexeme,"fi") == 0) {
	  return FI;
   }
   else if (strcmp(lexeme,"while") == 0) {
	  return WHILE;
   }
   else if (strcmp(lexeme,"do") == 0) {
	  return DO;
   }
   else if (strcmp(lexeme,"done") == 0) {
	  return DONE;
   }
   else if (strcmp(lexeme,"print") == 0) {
	  return PRINT;
   }
   else {
	  return IDENT;
   }
}


/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
   if (lexLen <= 98) {
	  lexeme[lexLen++] = nextChar;
	  lexeme[lexLen] = '\0';
   } else {
	  printf("Error - lexeme is too long \n");
     exit(0);
   }
}
/*****************************************************/
/* getChar - a function to get the next character of
   input and determine its character class
   Two globals are set
   nextChar - the next character scanned from the input.
   charClass - the category of the character - LETTER, DiGIT, OPERATOR
*/
void getChar()
{
   if(buffer_index < buffer.length()) {
	  nextChar = buffer[buffer_index++];
   } else {
	  //If at end of buffer, grab another character and move the 
	  //buffer index forward

     if(cin.peek() == -1) { //check if next char will be the EOF
        nextChar = EOF;
     } else {
   	  cin.get(nextChar);
   	  buffer += nextChar;
   	  buffer_index++;
     }
   }
   //insert next char into buffer here?
   if (nextChar != EOF) {
	  if (isalpha(nextChar))
		 charClass = LETTER;
	  else if (isdigit(nextChar))
		 charClass = DIGIT;
	  else if (nextChar == '#')
		 charClass = COMMENT;
	  else if (nextChar == '\n')
		 charClass = NEWLINE_CLASS;
	  else if (isspace(nextChar)) {
		 charClass = WHITESPACE;
	  }
	  else
		 charClass = OPERATOR;
   } else {
	  charClass = EOF;
   }
}
/*****************************************************/
/* getNonBlank - remove white space characters.
   call getChar until it returns a non-whitespace
   character.
   nextChar will be set to the next non-whitespace char.
*/
void getNonBlank()
{
    while (isspace(nextChar) && nextChar != '\n') {
	   getChar();
    }
}



/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex()
{
   lexLen = 0;
   getNonBlank();
   switch (charClass) {
	  /* Parse identifiers - once you find the first
		 letter, read and add char by char to lexeme. */

	  case LETTER:
				   addChar();
				   getChar();
				   /* After first char, you may use either char or digits */
				   while (charClass == LETTER || charClass == DIGIT) {
                 addChar();
					  getChar();
				   }
				   
				   nextToken = reservedWordLookup(lexeme);

				   break;

	  /* Parse integer literals - once you find the first
		 digit, read and add digits to lexeme. */
	  case DIGIT:
				   addChar();
				   getChar();
				   while (charClass == DIGIT) {
					  addChar();
					  getChar();
				   }
				   nextToken = INT_LIT;
				   break;

	  /* Parentheses and operators */
	  case OPERATOR:
				   /* Call lookup to identify the type of operator */
				   while(charClass == OPERATOR){
					  addChar();
					  getChar();
				   }
				   lookup(lexeme);
				   break;

	  case COMMENT:
				   addChar();
				   getChar();
				   /* After first char, you may use either char or digits */
				   while (charClass != NEWLINE_CLASS) {
					  addChar();
					  getChar();
				   }
				 
				   nextToken = COMMENT_ID;

				   break;

	  /* Newline characters */
	  case NEWLINE_CLASS:
				   addChar();
				   getChar();
				   nextToken = NEWLINE;
				   break;


	  /* EOF */
	  case EOF:
				   nextToken = EOF;
				   lexeme[0] = 'E';
				   lexeme[1] = 'O';
				   lexeme[2] = 'F';
				   lexeme[3] = '\0';
				   break;

   } /* End of switch */


   return nextToken;
}
