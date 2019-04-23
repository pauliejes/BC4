# BC4

This directory includes a make file that can be executed by running `make` from the command line, alternatively you can run `make clean` to clear the directory of object files.

After running `make`, the compiled bc program will run interactively as well as using I/O redirection.

Start the program by running bc at the command line within the BC4 directory. In this iteration of BC the user is not allowed to enter an explicit expression without assigning that expression to a variable. Only the following grammar is accepted by this interpreter:

<stmts> → <stmt> <stmts>
        | <stmt>
  
<stmt> → id = <expr>
       | if <cond> then <stmts> <optional_else> 
       | while <cond> do <stmts> done
       | print id
       | #comment
       | dump
       | quit
  
<optional_else> → else <stmts> fi 
                | fi
  
<cond> → <expr> <rel_op> <expr>
  
<rel_op> → == | != | < | <= | > | >= 

<expr> → <term> {(+ | -) <term>} 
  
<term> → <factor> {(* |   / | %) <factor>} 
  
<factor> → id 
         | int_constant 
         | ( <expr> )`

The user can input or redirect a file assigning variables, comparing variables with if - then - fi statements, and even execute while - do - done loops altering variables in new more efficient ways. The ability to add comments using the `#` character has also been added.

This is all nice, but to sweeten the deal we've also added a print function so that you can see the value of any given variable whenever you so please. If you want to see the whole program you've created, simply type `dump` and you'll get all the contents of the symbol table, along with the entire program inside bc thus far.

After trying all those new fun features, enter the `quit` command, and you'll find yourself back in the BC4 directory ready to check out our source code.
