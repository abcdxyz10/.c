%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[ \t]+          ;   // ignore whitespace
\n              { return 0; }
.               { return yytext[0]; }

%%

int yywrap(void) { return 1; }



%{
#include <stdio.h>
#include <stdlib.h>
int flag = 0;
void yyerror(const char *s);
int yylex(void);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

ArithmeticExpression:
        E   { printf("Result = %d\n", $1); return 0; }
;

E:
        E '+' E   { $$ = $1 + $3; }
    |   E '-' E   { $$ = $1 - $3; }
    |   E '*' E   { $$ = $1 * $3; }
    |   E '/' E   { $$ = $1 / $3; }
    |   E '%' E   { $$ = $1 % $3; }
    |   '(' E ')' { $$ = $2; }
    |   NUMBER    { $$ = $1; }
;

%%

int main(void) {
    printf("Enter any arithmetic expression (+, -, *, /, %% and parentheses):\n");
    yyparse();
    if (flag == 0)
        printf("Entered arithmetic expression is Valid\n");
    return 0;
}

void yyerror(const char *s) {
    (void)s;
    printf("Entered arithmetic expression is Invalid\n");
    flag = 1;
}
