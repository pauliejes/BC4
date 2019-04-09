#include<iostream>
#include<stdio.h>
#include<ctype.h>

#ifndef _TOP_DOWN_PARSER_H_
#define _TOP_DOWN_PARSER_H_
/* Function declarations */
void stmt_list();
int stmt();
int stmts();
int cond();
int opt_else();
int expr();
void print();
int comment();
int term();
int factor();
void error(const char *);

#endif