#include "graphCalculatorParser.h"

graph stringToGraph(const std::string phrase,const graphCalculator& G1);
bool firstLetterIsExclamationMark(const std::string& phrase);
std::string removeExclamationMark(const std::string& phrase);

graphCalculatorParser::graphCalculatorParser(const std::string line,const graphCalculator memory) : line(line), memory(memory) {}


graph graphCalculatorParser::calculatPhrase
(std::string phrase1 , std::string phrase2, const std::string action)
{
    graph g1 = stringToGraph(phrase1, memory);
    graph g2 = stringToGraph(phrase2, memory);

    if(action.c_str() == "+")
    {
        return (g1 + g2);
    }
    else if(action.c_str() == "*")
    {
        return (g1 * g2);
    }
    else if(action.c_str() == "^")
    {
        return (g1 ^ g2);
    }
    else if(action.c_str() == "-")
    {
        return (g1 - g2);
    }
    else
    {
        throw InvalidGraphLiteral();
    }
}

graph graphCalculatorParser::calculatMultiPhrase(const std::string phrase)
{
    
}



graph stringToGraph(std::string phrase, const graphCalculator& G1)
{
    if (phrase.find('{') == std::string::npos) 
    {
        bool exclamation_mark_on = false;
        if (firstLetterIsExclamationMark(phrase))
        {
            exclamation_mark_on = true;
            phrase = removeExclamationMark(phrase);
        }
        if(!isLegalGraphName(phrase))
        {
            throw IllegalGraphName();
        }
        std::string new_phrase = removeSpeces(phrase);
        if (exclamation_mark_on)
        {
            return (!(G1.get(new_phrase)));  
        }
        return G1.get(new_phrase);
    }
    else 
    {
        graph new_graph(phrase);
        return new_graph;
    }
}

bool firstLetterIsExclamationMark(const std::string& phrase)
{
    for (auto letter : phrase)
    {
        if (letter == ' ')
        {
            continue;
        }
        if (letter == '!')
        {
            return true;
        }
        break;
    }
    return false;
}

std::string removeExclamationMark(const std::string& phrase)
{
    std::string res;
    bool allready_removed = false;
    for (auto letter : phrase)
    {
        if (letter == ' ')
        {
            res += ' ';
            continue;
        }
        if (letter == '!')
        {
            if(!allready_removed)
            {
                allready_removed = true;
                continue;
            }
            res += letter ;
        }
        else
        {
            res += letter;
        }
    } 
    return res;
}