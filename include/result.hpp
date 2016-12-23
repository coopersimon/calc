// class that contains and deals with the outputs

#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>
#include <sstream>

// output data types
typedef long long itype;
typedef double    ftype;

// format of string output
enum data_format
{
      FP_DEC,
      INT_DEC,
      HEX,
      OCT,
      BIN
};

// abstract class for single result
class single_result
{
public:
      virtual ~single_result() {}
      virtual void str(std::stringstream& stream) = 0;
      virtual void append(single_result* in) = 0;
};

// list wrapper class for results
class result
{
      single_result* start;
      single_result* end;

public:
      result() :
            start(NULL), end(NULL) {}

      ~result()
      {
            if (start != NULL)
            {
                  delete start;
            }
      }

      std::string str();

      void appendInt(itype in, data_format output_type);
      void appendFloat(ftype in);
};

class int_result : public single_result
{
      single_result* next;
      itype data;
      data_format output_type;

public:
      int_result(itype d, data_format o) :
            next(NULL), data(d), output_type(o) {};

      ~int_result()
      {
            if (next != NULL)
            {
                  delete next;
            }
      }

      void str(std::stringstream& stream) override;
      void append(single_result* in) override;
};

class float_result : public single_result
{
      single_result* next;
      ftype data;

public:
      float_result(ftype d) :
            next(NULL), data(d) {};

      ~float_result()
      {
            if (next != NULL)
            {
                  delete next;
            }
      }

      void str(std::stringstream& stream) override;
      void append(single_result* in) override;
};

#endif
