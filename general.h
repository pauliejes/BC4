#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include "symTable.h"

#ifndef _GENERAL_H_
#define _GENERAL_H_
/* Global declarations */
/* Variables */
extern char lexeme [100];
extern char nextChar;
extern int lexLen;
extern Symbol_table symbolTable;

/* Character classes */
extern int charClass;
#define LETTER 0
#define DIGIT 1
#define COMMENT 98
#define OPERATOR 99
#define NEWLINE_CLASS 100
#define WHITESPACE 101

/* Token codes */
extern int token;
extern int nextToken;

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define POW_OP 26
#define LEFT_PAREN 27
#define RIGHT_PAREN 28
#define QUIT 29
#define DUMP 30
#define EQL_OP 31
#define NOTEQL_OP 32
#define LESS_OP 33
#define GREAT_OP 34
#define LESSEQL_OP 35
#define GREATEQL_OP 36
#define COMMENT_ID 37
#define NEWLINE 38
#define IF 39
#define THEN 40
#define ELSE 41
#define FI 42
#define WHILE 43
#define DO 44
#define DONE 45
#define PRINT 46



#endif