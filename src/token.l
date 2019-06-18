%option noyywrap
%{
#include <cstdlib>
#include <tree.hpp>
#include <parse.tab.hpp>

extern int inputToLexer(char* buffer, yy_size_t* num_bytes_read, int max_bytes_to_read);

#undef YY_INPUT
#define YY_INPUT(b,r,s) inputToLexer(b, &r, s)
%}

DIGIT       [0-9]
OCT         [0-7]
HEX         [0-9a-fA-F]
BIN         [0-1]

FLOAT       [0-9]*\.[0-9]+


%%

ans         return _ANS;
a           return _ANS;

{DIGIT}+    { yylval.i = atoll(yytext); return _INT; }
b{BIN}+     { yylval.i = strtoll(yytext + 1, NULL, 2); return _INT; }
o{OCT}+     { yylval.i = strtoll(yytext + 1, NULL, 8); return _INT; }
h{HEX}+     { yylval.i = strtoll(yytext + 1, NULL, 16); return _INT; }
{FLOAT}     { yylval.fp = atof(yytext); return _FLOAT; }

\+          return _ADD;
-           return _SUB;
\*          return _MUL;
\/          return _DIV;
\^          return _EXP;

\(          return _LBRAC;
\)          return _RBRAC;
;           return _SEMI;

[ ]
\t

%%
