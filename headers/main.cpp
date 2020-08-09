#include "graphCalculatorParser.h"
#include <fstream>

int main (int argc, char* argv[])
{
    bool is_file_mode = true;
    std::ostream* out;
    std::istream * input;
    switch (argc)
    {
        case 1:
        {
            is_file_mode = false;
            input = &std::cin;
            out = &std::cout;
            break;
        }
        case 3:
        {
            std::ifstream in_file(argv[1]);
            if (!in_file)
            {
                std::cerr << "Error: Can not open file";
                return 1;
            }
            std::ofstream out_file(argv[3]);
            if (!out_file)
            {
                std::cerr << "Error: Can not open file";
                return 1;
            }
            input = &in_file;
            out = &out_file;
            break;
        }
        default:
        {
            std::cerr << "Error: Syntax error";
            return 1;
            break;
        }    
    }
    std::string line;
    if (!is_file_mode)
    {
        *out << "Gcalc> ";
    } 
    while (std::getline(*input, line))
    {
        try
        {
            graphCalculatorParser calculator(line,out);
            if (!calculator.applyLine())
            {
                break;
            }
            if (!is_file_mode)
            {
                *out << "Gcalc> ";
            } 
        }
        catch(const std::exception& err)
        {
            *out << err.what() << std::endl;
            if (!is_file_mode)
            {
                *out << "Gcalc> ";
            } 
        }  
    }

    return 0 ; 
}