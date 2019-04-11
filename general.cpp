#include "general.h"
#include "symTable.h"
#include <string>
std::string buffer;
int buffer_index;
char lexeme [100];
char nextChar;
int lexLen;
int charClass;
int token;
int nextToken;
Symbol_table symbolTable;