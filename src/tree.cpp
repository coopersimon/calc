#include <cmath>
#include <tree.hpp>

namespace ans
{
      itype i;
      ftype f;
};

void expression_list::interpretInts(std::list<ftype> &outputs)
{
      if (next != NULL)
      {
            next->interpretInts(outputs);
      }

      ans::i = expr->interpretInt();
      ans::f = ans::i;
      outputs.push_back(ans::f);

      return;
}

void expression_list::interpretFloats(std::list<ftype> &outputs)
{
      if (next != NULL)
      {
            next->interpretFloats(outputs);
      }

      ans::f = expr->interpretFloat();
      outputs.push_back(ans::f);
      
      return;
}

itype add_expression::interpretInt()
{
      itype l_val = left->interpretInt();
      itype r_val = right->interpretInt();
      return l_val + r_val;
}

ftype add_expression::interpretFloat()
{
      ftype l_val = left->interpretFloat();
      ftype r_val = right->interpretFloat();
      return l_val + r_val;
}

itype sub_expression::interpretInt()
{
      itype l_val = left->interpretInt();
      itype r_val = right->interpretInt();
      return l_val - r_val;
}

ftype sub_expression::interpretFloat()
{
      ftype l_val = left->interpretFloat();
      ftype r_val = right->interpretFloat();
      return l_val - r_val;
}

itype mul_expression::interpretInt()
{
      itype l_val = left->interpretInt();
      itype r_val = right->interpretInt();
      return l_val * r_val;
}

ftype mul_expression::interpretFloat()
{
      ftype l_val = left->interpretFloat();
      ftype r_val = right->interpretFloat();
      return l_val * r_val;
}

itype div_expression::interpretInt()
{
      itype r_val = right->interpretInt();
      if (r_val == 0)
      {
            // throw exception
      }
      itype l_val = left->interpretInt();
      return l_val / r_val;
}

ftype div_expression::interpretFloat()
{
      ftype r_val = right->interpretFloat();
      if (r_val == 0)
      {
            // throw exception
      }
      ftype l_val = left->interpretFloat();
      return l_val / r_val;
}

itype exp_expression::interpretInt()
{
      itype e_val = exponent->interpretInt();
      if (e_val == 0)
            return 1;

      itype b_val = base->interpretInt();
      return (itype)pow(b_val, e_val);
}

ftype exp_expression::interpretFloat()
{
      ftype e_val = exponent->interpretFloat();
      if (e_val == 0)
            return 1.0;

      ftype b_val = base->interpretFloat();
      return pow(b_val, e_val);
}

itype int_leaf::interpretInt()
{
      return value;
}

ftype int_leaf::interpretFloat()
{
      return value;
}

itype float_leaf::interpretInt()
{
      // throw exception
      return 0;
}

ftype float_leaf::interpretFloat()
{
      return value;
}

itype ans_leaf::interpretInt()
{
      return ans::i;
      return 0;
}

ftype ans_leaf::interpretFloat()
{
      return ans::f;
      return 0;
}
