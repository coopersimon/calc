#include <tree.hpp>
#include <parse.tab.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <list>
#include <string>
#include <sstream>

enum data_format
{
      DEC,
      HEX,
      OCT,
      BIN
};

int inputToLexer(char*, int*, int);
int parseMaths(std::list<ftype>&);
std::string outputString(std::list<ftype>&, data_format);

namespace intext
{
      static int offset;
      std::string data;
};


int main(int argc, char* argv[])
{
      // output numbers
      std::list<ftype> output;
      // run until ctrl-D
      bool active_input_mode = true;

      // options
      data_format output_type = DEC;

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
                              output_type = HEX;
                        }
                        else if (c == 'o')
                        {
                              output_type = OCT;
                        }
                        else if (c == 'b')
                        {
                              output_type = BIN;
                        }
                  }
            }

            // code
            else
            {
                  intext::offset = 0;
                  active_input_mode = false;
                  intext::data = std::string(argv[i]);
                  parseMaths(output);
                  std::cout << outputString(output, output_type);
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
                  parseMaths(output);
                  std::cout << outputString(output, output_type);
            }
      }

      return 0;
}

int parseMaths(std::list<ftype>& output)
{
      expression_list* calc_ast;
      bool use_float = false;

      yyparse(&calc_ast, &use_float);

      if (use_float)
      {
            // try{} catch{}
            calc_ast->interpretFloats(output);
      }
      else
      {
            // try{} catch{}
            calc_ast->interpretInts(output);
      }

      if (calc_ast != NULL)
      {
            delete calc_ast;
      }

      return 0;
}

std::string outputString(std::list<ftype>& output, data_format output_type)
{
      std::stringstream s;
      int output_size = output.size();

      s << "\t= ";

      for (auto o : output)
      {
            switch (output_type)
            {
            case DEC:
                  s << o;
                  break;
            case HEX:
            {
                  unsigned fill_width = 2;
                  if (itype(o) >= 0xFFFFFFFF)
                        fill_width = 16;
                  else if (itype(o) >= 0xFFFF)
                        fill_width = 8;
                  else if (itype(o) >= 0xFF)
                        fill_width = 4;
                  s << std::setfill('0') << std::setw(fill_width) << std::hex << itype(o);
                  break;
            }
            case OCT:
                  s << std::setfill('0') << std::setw(22) << std::oct << itype(o);
                  break;
            case BIN:
            {
                  if (itype(o) >= 0xFFFFFFFF)
                        s << std::bitset<64>(itype(o));
                  else if (itype(o) >= 0xFFFFFF)
                        s << std::bitset<48>(itype(o));
                  else if (itype(o) >= 0xFFFF)
                        s << std::bitset<32>(itype(o));
                  else if (itype(o) >= 0xFF)
                        s << std::bitset<16>(itype(o));
                  else if (itype(o) >= 0xF)
                        s << std::bitset<8>(itype(o));
                  else
                        s << std::bitset<4>(itype(o));
                  break;
            }
            default:
                  break;
            }

            output_size--;
            if (output_size)
            {
                  s << ", ";
            }
            else
            {
                  s << "\n";
            }
      }

      output.clear();

      return s.str();
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
