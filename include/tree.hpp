// tree.hpp - defines the ast for calc

#ifndef TREE_HPP
#define TREE_HPP

#include <cstdlib>
#include <list>

typedef long long itype;
typedef double    ftype;

class expression
{
public:
      virtual ~expression() {};
      virtual itype interpretInt() = 0;
      virtual ftype interpretFloat() = 0;
};

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

      void interpretInts(std::list<ftype> &outputs);
      void interpretFloats(std::list<ftype> &outputs);
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
