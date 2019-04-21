/*
  Calculator.cpp - A simple arithmetic interpreter.
  Name: R. Shore
  Class: CSC-4510
  The program demonstrates two main components of
  an interpreter/compiler.
  1) A lexical analyzer to scan the input for
     LETTERs, DIGITs, or OPERATORs
     An IDENT consist of a LETTER followed by
     a LETTER or DIGIT (max 99 characters)
     AN INT_LIT consists of a sequence of DIGITs
     (max 99 digits).
     An OPERATOR =, +, -, *, /, (, )
     lexeme[] holds the item read from source
     nextToken holds the type
  2) A recursive descent parser
     The Grammar - EBNF description
     <expr> → <term> {(+ | -) <term>}
     <term> → <factor> {(* | /) <factor>}
     <factor> → id | int_constant | ( <expr>  )
     NOTE: the recusive descent starts at <expr>
 */

#include<iostream>
#include<stdio.h>
#include"general.h"
#include"lex.h"
#include"topDownParser.h"
#include"symTable.h"



using namespace std;


/******************************************************/
/* main driver */
int main(void) {
  do {
    getChar();
    lex();
    stmt();
  } while (nextToken != EOF);
}

/* stmts
   Parses strings in the language generated by the rule:
   <stmts> -> <stmt> <stmts>
           |  <stmt>
 */
int stmts()
{
  int return_val = 0;

  getChar();
  lex();
  while (nextToken != DONE && nextToken != FI && nextToken != EOF) {
    cout << "nextToken: " << nextToken << endl;
    return_val = stmt();
    if (nextToken == NEWLINE)
    {
      getChar();
      lex();
      //cout << "after lex 2\n";
      //cout << "nextToken: " << nextToken << endl;
    }
  }

  return return_val;
}


/* stmt
   Parses strings in the language generated by the rule:
   <stmt> -> <var> = <expr>
          | if <cond> then <stmts> fi
          | if <cond> then <stmts> else <stmts> fi 
          | while <cond> do <stmts> done
          | print <var>
          | #comment
          | dump | quit
 */
int stmt()
{

   int return_val = 0;
   //Quit
   if(nextToken == QUIT) {
      exit(11);
   } else if(nextToken == DUMP) { //Dump
      symbolTable.dump_table();
   } else if(nextToken == PRINT) { //Print
      print();
   } else if(nextToken == IDENT) { //for assignment statements
   	  return_val = identifier();
   } else if (nextToken == COMMENT_ID) { //for comments
      //do nothing
   } else if (nextToken == IF) { //for if statements
      return_val = ifstmt();
   } else if (nextToken == WHILE) {
      return_val = whileLoop(); 
   } else if (nextToken == NEWLINE) {
      error("Statement should not be empty");
      exit(0);
   } else { //plain expressions
      error("This grammar does not allow plain expressions, please define a variable name");
   }

   return return_val;
}

void print(){
	lex();
	//return_val = factor();
	Symbol_ptr var_ptr = symbolTable.insert(lexeme);
	cout << var_ptr->getId() << " = ";
	cout << var_ptr->getval() << endl;
}

int identifier() {

	int return_val;

	//get the next token
	Symbol_ptr var_to_assign = symbolTable.insert(lexeme);
	return_val = factor();
	while (nextToken == ASSIGN_OP) {
		lex();
		return_val = expr();
		var_to_assign->putval(return_val);
	}

	return return_val;
}

int ifstmt() {

	int return_val;

	lex();
	int cond_result = cond();
	if(cond_result) {
		cout << "true\n";
		cout << "nextToken = " << nextToken << endl;
		if(nextToken == THEN) {
			cout << "then\n";
			lex();
			cout << "lexeme = " << lexeme << endl;
			return_val = stmts();
			cout << "return_val = " << return_val <<endl;
		} else {
      cout << "ERROR: IF without THEN\n";
    }
	} else {
		cout << "condition is false\n";
    //condition is false, skip over the statement
    int num_ifs = 1;
    while (num_ifs > 0) {
      lex();
      //this is to get out of loop we get stuck in if we try
      //to use lex() to get past a newline character. Should
      //change lex() to fix this ideally
      if (nextToken == NEWLINE)
      {
        getChar();
        lex();
      }
      if (nextToken == FI)
      {
        num_ifs--;
      }
      if (nextToken == IF) 
      {
        num_ifs++;
      }
    }
	}

  cout << "exiting ifstmt\n";
	return return_val;
}

//WHILE <condition> DO <stmts> DONE
int whileLoop() {
  cout << "whileLoop\n";
  int return_val = 0;
  //subtract characters from while
  int start_index = buffer_index - 6;

  lex();
  //store the location in the buffer where the while loop starts
  if (cond())
  {
    cout << "condition true\n";
    //lex();
    if (nextToken == DO)
    {
      return_val = stmts();

      //return to top
      cout << "done\n";
      buffer_index = start_index;
      cout << "returning to top of while\n";
    }
  } else {
    cout << "condition is false\n";
    //condition is false, skip over the statement
    int num_whiles = 1;
    while (num_whiles > 0) {
      cout << num_whiles << endl;
      lex();
      //this is to get out of loop we get stuck in if we try
      //to use lex() to get past a newline character. Should
      //change lex() to fix this ideally
      if (nextToken == NEWLINE)
      {
        getChar();
        lex();
      }
      if (nextToken == DONE)
      {
        num_whiles--;
      }
      if (nextToken == WHILE) 
      {
        num_whiles++;
      }
    }
  }

  cout << "EXITING WHILE LOOP FUNCTION\n";
  return return_val;
}

/* cond
   Parses strings in the language generated by the rule:
   <cond> -> <expr> <rel_op> <expr>}
*/
int cond()
{
   cout << "Enter condition. lexeme: " << lexeme << endl;
   bool return_val;


   //evaluate the first expression and hold value
   int val_1 = expr();
   //cout << "val_1 = " << val_1 << endl;
   int val_2;

   if(nextToken == EQL_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 == val_2);

   } else if(nextToken == NOTEQL_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 != val_2);

   } else if(nextToken == LESS_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 < val_2);

   } else if(nextToken == GREAT_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 > val_2);

   } else if(nextToken == LESSEQL_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 <= val_2);

   } else if(nextToken == GREATEQL_OP) {
      lex();
      val_2 = expr();
      //cout << "val_2 = " << val_2 << endl;
      return_val = (val_1 >= val_2);
   }  else if(nextToken == FI) {
      cout << "if return_val = " << return_val << endl;
      return return_val;

   } else {
      cout << "You didn't close the block! Current if return_val = " << return_val << endl;
      return return_val;
   }


   /* Parse the first expr */
   // int first_cond = expr();
   // op = rel_op();

   /* As long as the next token is a rel_op, get
      the next token and parse the next term */
   // while (nextToken == op) {
   //    lex();
   //    return_val += term();
   // }

   // cout << "if return_val = " << return_val << endl;

   // return return_val;

} /* End of function cond */


/* expr
   Parses strings in the language generated by the rule:
   <expr> -> <term> {(+ | -) <term>}
 */
int expr()
{
   int return_val;


   /* Parse the first term */
   return_val = term();

   /*while (nextToken == ASSIGN_OP) {
      lex();
      term();
   }*/
   /* As long as the next token is + or -, get
      the next token and parse the next term */
   while (nextToken == ADD_OP ) {
      lex();
      return_val += term();
      //cout << "ADD_OP" << endl;
   }

   while (nextToken == SUB_OP) {
      lex();
      return_val -= term();
   }
  
   return return_val;

} /* End of function expr */


/* term
 *  Parses strings in the language generated by the rule:
 *  <term> -> <factor> {(* | /) <factor>)
 *  <term> | <factor>
 *  <term> | - <factor>
 */
int term()
{
   int return_val;
  /* Parse the first factor */
   if (nextToken == SUB_OP) {
      //negative
      lex();
      return_val = factor() * -1;
   } else {
      return_val = factor();
   }
   /* As long as the next token is * or /, get the
      next token and parse the next factor */
   while (nextToken == MULT_OP){
      lex();
      return_val *= factor();
   } 
   while ( nextToken == DIV_OP) {
      lex();
      return_val /= factor();
   } 
   while (nextToken == MOD_OP) {
      lex();
      return_val = return_val % factor();
   }
   while (nextToken == POW_OP) {
      lex();
      return_val = pow(return_val,factor());
   }


   return return_val;

} /* End of function term */

/* factor
 * Parses strings in the language generated by the rule:
 *
 *   <factor> -> id | int_constant | ( <expr  )
 *
 */
int factor()
{
   int return_val = 0;
   /* Determine which RHS */
   if (nextToken == IDENT) {
      //look up the ident in the symbol table
      return_val = symbolTable.insert(lexeme)->getval();
      lex();
   } else if (nextToken == INT_LIT){
      /* Get the next token d*/
      return_val = atoi(lexeme);
      lex();

   /* If the RHS is ( <expr> ), call lex to pass over the left
      parenthesis, call expr and check for the right parenthesis */
   } else if (nextToken == LEFT_PAREN) {
         lex();
         return_val = expr();
         if (nextToken == RIGHT_PAREN)
            lex();
         else
            error("Right without left paren");
   } else {
   /* It was not an id, an integer literal, or a left
       parenthesis */
       error("expected an id, integer, or a left paren");
   } /* End of else */

   return return_val;
}/* End of function factor */

void error(const char *message)
{
   printf("Error: %s\n",message);
}
