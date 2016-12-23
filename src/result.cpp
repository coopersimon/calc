#include <result.hpp>
#include <iomanip>
#include <bitset>

std::string result::str()
{
      std::stringstream s;

      if (start != NULL)
      {
            s << "\t= ";
            start->str(s);
      }

      s << "\n";

      return s.str();
}

void result::appendInt(itype in, data_format output_type)
{
      single_result* new_result = new int_result(in, output_type);

      if (start == NULL)
      {
            start = new_result;
      }
      else
      {
            end->append(new_result);
      }

      end = new_result;

      return;
}

void result::appendFloat(ftype in)
{
      single_result* new_result = new float_result(in);

      if (start == NULL)
      {
            start = new_result;
      }
      else
      {
            end->append(new_result);
      }

      end = new_result;

      return;
}


void int_result::str(std::stringstream& stream)
{
      switch(output_type)
      {
      case INT_DEC:
            stream << data;
            break;
      case HEX:
      {
            unsigned fill_width = 2;
            if (data > 0xFFFFFFFF)
                  fill_width = 16;
            else if (data > 0xFFFF)
                  fill_width = 8;
            else if (data > 0xFF)
                  fill_width = 4;
            stream << std::setfill('0') << std::setw(fill_width) << std::hex << data;
            break;
      }
      case OCT:
            stream << std::setfill('0') << std::setw(22) << std::oct << data;
            break;
      case BIN:
      {
            if (data > 0xFFFFFFFF)
                  stream << std::bitset<64>(data);
            else if (data > 0xFFFFFF)
                  stream << std::bitset<48>(data);
            else if (data > 0xFFFF)
                  stream << std::bitset<32>(data);
            else if (data > 0xFF)
                  stream << std::bitset<16>(data);
            else if (data > 0xF)
                  stream << std::bitset<8>(data);
            else
                  stream << std::bitset<4>(data);
            break;
      }
      default:
            break;
      }

      if (next != NULL)
      {
            stream << ", ";
            next->str(stream);
      }

      return;
}

void int_result::append(single_result* in)
{
      next = in;

      return;
}


void float_result::str(std::stringstream& stream)
{
      stream << data;

      if (next != NULL)
      {
            stream << ", ";
            next->str(stream);
      }

      return;
}

void float_result::append(single_result* in)
{
      next = in;

      return;
}
