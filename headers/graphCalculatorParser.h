#ifndef GRAPH_CALCULATOR_PARSER
#define GRAPH_CALCULATOR_PARSER
#include "GraphCalculator.h"

// /enum class action : char
// {
//     plus = '+', minus = '-', 
// };

class graphCalculatorParser
{
private:
    std::string line ;
    graphCalculator memory ;
public:
    graphCalculatorParser(std::string line, graphCalculator memory);
    ~graphCalculatorParser() = default;

    graph calculatMultiPhrase(const std::string phrase);
    graph calculatPhrase(std::string phrase1, std::string phrase2, const std::string action);
    std::string getFirstWord() const ;
};










// bool isSaveKey(const std::string name)
// {
//     if ((name == "print") || (name == "delete")  || (name == "who") || (name == "reset") || (name == "quit"))
//     {
//         return true;
//     }
//     return false;
// }

#endif