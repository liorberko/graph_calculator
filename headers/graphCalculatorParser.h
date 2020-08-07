#ifndef GRAPH_CALCULATOR_PARSER
#define GRAPH_CALCULATOR_PARSER
#include "GraphCalculator.h"



class graphCalculatorParser
{
private:
    std::string line ;
    graphCalculator memory ;
public:
    graphCalculatorParser(std::string line, graphCalculator memory);
    ~graphCalculatorParser() = default;

    // graph calculatMultiPhrase(const std::string phrase);
    std::string fechNexPhrase(std::string phrase, char& action);
    graph calculatMultiPhrase(std::string phrase);
    graph calculatPhrase(graph g1, std::string phrase2, char& action);
    std::string getFirstWord() const ;
    static void save(const graph& g1, std::string filename);

    static graph load(const std::string& filename);
};





#endif