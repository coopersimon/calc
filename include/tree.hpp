// tree.hpp - defines the ast for calc

#ifndef TREE_HPP
#define TREE_HPP

#include <cstdlib>
#include <list>
#include <result.hpp>

// data independent of type
/*class number
{
      union data
      {
            itype i;
            ftype f;
      };

      bool type;

public:
      number(itype d) :
            data.i(d), type(


}*/

// all expressions derive from this class
class expression
{
public:
      virtual ~expression() {};
      virtual itype interpretInt() = 0;
      virtual ftype interpretFloat() = 0;
};

// list that chains expressions together
class expression_list
{
      expression* expr;
      expression_list* next;

public:
      expression_list(expression* e, expression_list* n) :
            expr(e), next(n) {}

      ~expression_list()
      {
            if (next != NULL)
            {
                  delete next;
            }
            if (expr != NULL)
            {
                  delete expr;
            }
      }

      void interpretInts(result &outputs, data_format output_type);
      void interpretFloats(result &outputs);
};

// wrapper class for the ast
class root_node
{
      expression_list* ast;
      data_format default_type;

public:
      root_node(data_format o) :
            ast(NULL), default_type(o) {}

      ~root_node()
      {
            if (ast != NULL)
            {
                  delete ast;
            }
      }

      void setList(expression_list* t_in)
      {
            ast = t_in;
      }

      void interpret(result &outputs);
};

class add_expression : public expression
{
      expression* left;
      expression* right;

public:
      add_expression(expression* l, expression* r) :
            left(l), right(r) {}

      ~add_expression()
      {
            if (left != NULL)
            {
                  delete left;
            }
            if (right != NULL)
            {
                  delete right;
            }
      }

      itype interpretInt();
      ftype interpretFloat();
};

class sub_expression : public expression
{
      expression* left;
      expression* right;

public:
      sub_expression(expression* l, expression* r) :
            left(l), right(r) {}

      ~sub_expression()
      {
            if (left != NULL)
            {
                  delete left;
            }
            if (right != NULL)
            {
                  delete right;
            }
      }

      itype interpretInt();
      ftype interpretFloat();
};

class mul_expression : public expression
{
      expression* left;
      expression* right;

public:
      mul_expression(expression* l, expression* r) :
            left(l), right(r) {}

      ~mul_expression()
      {
            if (left != NULL)
            {
                  delete left;
            }
            if (right != NULL)
            {
                  delete right;
            }
      }

      itype interpretInt();
      ftype interpretFloat();
};

class div_expression : public expression
{
      expression* left;
      expression* right;

public:
      div_expression(expression* l, expression* r) :
            left(l), right(r) {}

      ~div_expression()
      {
            if (left != NULL)
            {
                  delete left;
            }
            if (right != NULL)
            {
                  delete right;
            }
      }

      itype interpretInt();
      ftype interpretFloat();
};

class exp_expression : public expression
{
      expression* base;
      expression* exponent;

public:
      exp_expression(expression* b, expression* e) :
            base(b), exponent(e) {}

      ~exp_expression()
      {
            if (base != NULL)
            {
                  delete base;
            }
            if (exponent != NULL)
            {
                  delete exponent;
            }
      }

      itype interpretInt();
      ftype interpretFloat();
};

class int_leaf : public expression
{
      itype value;

public:
      int_leaf(itype v) :
            value(v) {}

      itype interpretInt();
      ftype interpretFloat();
};

class float_leaf : public expression
{
      ftype value;

public:
      float_leaf(ftype v) :
            value(v) {}

      itype interpretInt();
      ftype interpretFloat();
};

class ans_leaf : public expression
{
public:
      itype interpretInt();
      ftype interpretFloat();
};

#endif
