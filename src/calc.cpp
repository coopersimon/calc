#include <tree.hpp>
#include <parse.tab.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <list>
#include <string>
#include <sstream>

int inputToLexer(char*, int*, int);
int parseMaths(result&, data_format);
//std::string outputString(std::list<ftype>&, data_format);

namespace intext
{
      static int offset;
      std::string data;
};


int main(int argc, char* argv[])
{
      // run until ctrl-D
      bool active_input_mode = true;

      // options
      data_format default_type = FP_DEC;

      // parse arguments
      for (int i = 1; i < argc; i++)
      {
            // options
            if (argv[i][0] == '-')
            {
                  std::string iter(argv[i]);
                  for (auto c : iter)
                  {
                        if (c == 'h')
                        {
                              default_type = HEX;
                        }
                        else if (c == 'o')
                        {
                              default_type = OCT;
                        }
                        else if (c == 'b')
                        {
                              default_type = BIN;
                        }
                        else if (c == 'i')
                        {
                              default_type = INT_DEC;
                        }
                  }
            }

            // code
            else
            {
                  intext::offset = 0;
                  active_input_mode = false;
                  intext::data = std::string(argv[i]);
                  result output;
                  parseMaths(output, default_type);
                  std::cout << output.str();
            }
      }

      // decode input at runtime
      while (active_input_mode)
      {
            intext::offset = 0;
            std::getline(std::cin, intext::data);
            if (intext::data == "exit" || intext::data == "quit" || intext::data == "q")
            {
                  break;
            }
            else
            {
                  result output;
                  parseMaths(output, default_type);
                  std::cout << output.str();
            }
      }

      return 0;
}

int parseMaths(result& output, data_format default_type)
{
      root_node calc_ast(default_type);
      //data_format output_type = default_type;

      yyparse(&calc_ast);

      // try
      /*if (output_type == FP_DEC)
      {
            calc_ast.interpretFloats(output);
      }
      else
      {
            calc_ast.interpretInts(output);
      }*/

      calc_ast.interpret(output);

      // catch

      return 0;
}

int inputToLexer(char* buffer, int* num_bytes_read, int max_bytes_to_read)
{
      int bytes_remaining = intext::data.length() - intext::offset;
      int num_bytes_to_read = (max_bytes_to_read > bytes_remaining) ?
            bytes_remaining : max_bytes_to_read;

      for (int i = 0; i < num_bytes_to_read; i++)
      {
            buffer[i] = intext::data.at(intext::offset + i);
      }

      *num_bytes_read = num_bytes_to_read;
      intext::offset += num_bytes_to_read;
      return 0;
}
