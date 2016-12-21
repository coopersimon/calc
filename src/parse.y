%define parse.error verbose
%parse-param {expression_list** calc_ast} {bool* use_float}
%{
#include <tree.hpp>
#include <iostream>

int yylex();
void yyerror(expression_list**, bool*, const char*);
%}

%union
{
      itype i;
      ftype fp;

      expression_list* list;
      expression* expr;
}

%token _ANS
%token _INT _FLOAT
%token _ADD _SUB _MUL _DIV _EXP
%token _LBRAC _RBRAC
%token _SEMI

%type <i> _INT
%type <fp> _FLOAT
%type <list> expr_list
%type <expr> expression add_exp mul_exp exp_exp neg_exp prim_exp

%start root

%%

root        : expr_list { *calc_ast = $1; }

expr_list   : expr_list _SEMI expression { $$ = new expression_list($3, $1); }
            | expression { $$ = new expression_list($1, NULL); }
            ;

expression  : add_exp { $$ = $1; }
            ;

add_exp     : mul_exp { $$ = $1; }
            | add_exp _ADD mul_exp { $$ = new add_expression($1, $3); }
            | add_exp _SUB mul_exp { $$ = new sub_expression($1, $3); }
            ;

mul_exp     : exp_exp { $$ = $1; }
            | mul_exp _MUL exp_exp { $$ = new mul_expression($1, $3); }
            | mul_exp _DIV exp_exp { *use_float = true;
                                    $$ = new div_expression($1, $3); }
            ;

exp_exp     : neg_exp { $$ = $1; }
            | exp_exp _EXP neg_exp { $$ = new exp_expression($1, $3); }
            ;

neg_exp     : prim_exp { $$ = $1; }
            | _SUB prim_exp { expression* zero = new int_leaf(0); 
                              $$ = new sub_expression(zero, $2); }
            ;

prim_exp    : _INT { $$ = new int_leaf($1); }
            | _FLOAT { *use_float = true;
                        $$ = new float_leaf($1); }
            | _ANS { $$ = new ans_leaf(); }
            | _LBRAC expression _RBRAC { $$ = $2; }
            ;

%%

void yyerror(expression_list** n, bool* b, const char* e)
{
      std::cerr << e << std::endl;
      return;
}
