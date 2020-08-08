#ifndef GRAPH_CALCULATOR_PARSER
#define GRAPH_CALCULATOR_PARSER
#include "GraphCalculator.h"



class graphCalculatorParser
{
private:
    std::string line ;
    std::ostream* out;

    static graphCalculator memory;
public:
    graphCalculatorParser(std::string line, std::ostream* out);
    ~graphCalculatorParser() = default;

    bool applyLine();
    graph astimetThreePhrases
    (const std::string& phrase1, const std::string& phrase2,const std::string& phrase3, char action1, char action2) const;
    graph calculatComplexPhrase(std::string phrase) const;
    std::string fechNexPhrase(std::string& phrase, char& action) const;
    graph calculatMultiPhrase(std::string phrase) const;
    graph calculatPhrase(graph g1, std::string phrase2, char& action) const;
    std::string getFirstWord() const ;
    static void save(const graph& g1, std::string filename);

    static graph load(const std::string& filename);
};





#endif