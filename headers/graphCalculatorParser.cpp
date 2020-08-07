#include "graphCalculatorParser.h"
#include <algorithm>
#define DONE '%'


graph stringToGraph(const std::string phrase,const graphCalculator& G1);
bool firstLetterIsExclamationMark(const std::string& phrase);
std::string removeExclamationMark(const std::string& phrase);
int countActions(const std::string phrase);
bool is_blanck_phrase(const std::string phrase);
std::string removeEnter(const std::string& phrase);
char get_first_letter(const std::string& phrase);
bool isLoadFanction(const std::string& phrase, std::string& filename );


graphCalculatorParser::graphCalculatorParser(const std::string line,const graphCalculator memory) : line(line), memory(memory) {}


graph graphCalculatorParser::calculatPhrase
(graph g1, std::string phrase2, char& action)
{
    graph g2 = stringToGraph(phrase2, memory);

    if(action == '+')
    {
        return (g1 + g2);
    }
    else if(action == '*')
    {
        return (g1 * g2);
    }
    else if(action == '^')
    {
        return (g1 ^ g2);
    }
    else if(action == '-')
    {
        return (g1 - g2);
    }
    else
    {
        throw InvalidGraphLiteral();
    }
}

std::string graphCalculatorParser::fechNexPhrase(std::string input, char& action)
{
    std::string phrase, leftover;
    bool  record_action = false, record_leftover = false;
    for (auto letter : input)
    {
        if (record_leftover)
        {
            leftover += letter;
            continue;
        }
        if ((letter == '+') || (letter == '-') || (letter == '*') || (letter == '^'))
        {
            record_leftover = true;
            action = letter;
            continue;
        }
        phrase += letter;
    }
    if (leftover.size() == 0)
    {
        action = DONE;
    }
    input = leftover;
    return phrase;
}

graph graphCalculatorParser::calculatMultiPhrase(std::string phrase)
{
    char action;
    phrase = removeEnter(phrase);
    if (phrase.size() == 0)
    {
        throw SintaxError();
    }
    graph res = stringToGraph(fechNexPhrase(phrase, action), memory);
    while (action != DONE)
    {
        std::string phrase2 = fechNexPhrase(phrase, action);
        res = calculatPhrase(res,phrase2,action);
    }
    return res;
}

// graph graphCalculatorParser::calculatMultiPhrase(graph g1, std::string phrase, char lest_action)
// {
//     if(is_blanck_phrase(phrase)) 
//     {
//         throw SintaxError();
//     }
//     std::string new_phrase = removeEnter(phrase);
//     if ((std::count(new_phrase.begin(), new_phrase.end(), '(') == 0) && (countActions(new_phrase) == 1))
//     {
//         return stringToGraph(new_phrase, memory);
//     }
//     std::string phrase1, phrase2;
//     char action = '@';
//     bool record_to_phrase2 = false, record_action = false;
//     char first_letter = get_first_letter(new_phrase);
//     if (first_letter == '(')
//     {
//         int bracket_count = 0;
//         for (auto letter : new_phrase)
//         {
//             if (isblank(letter) && (!isspace(letter)))
//             {
//                 continue;
//             }
//             if(record_action)
//             {
//                 if (letter == ' ')
//                 {
//                     continue;
//                 }
//                 if (!((letter == '+') || (letter == '-') || (letter == '*') || (letter == '^')))
//                 {
//                     throw SintaxError();
//                 }
//                 action = letter;
//                 record_to_phrase2 = true;
//                 record_action = false;
//                 continue;
//             }
//             if (record_to_phrase2)
//             {
//                 phrase2 += letter;
//                 continue;
//             }
//             if (letter == '(')
//             {
//                 if(bracket_count == 0)
//                 {
//                     bracket_count++;
//                     continue;
//                 }
//                 bracket_count++;
//             }
//             if (letter == ')')
//             {
//                 bracket_count--;
//                 if (bracket_count == 0)
//                 {
//                     record_action = true;
//                     continue;
//                 }
//             }
//             phrase1 += letter;
//         }
//     }
//     else
//     {
//         for (auto letter : new_phrase)
//         {
//             if (isblank(letter) && (!isspace(letter)))
//             {
//                 continue;
//             }
//             if (record_to_phrase2)
//             {
//                 phrase2 += letter;
//                 continue;
//             }
//             if ((letter == '+') || (letter == '-') || (letter == '*') || (letter == '^'))
//             {
//                 action = letter;
//                 record_to_phrase2 = true;
//                 continue;
//             }
//             phrase1 += letter;
//         }
//     }
//     if (lest_action == '+')
//     {
//         return (calculatMultiPhrase(g1 +(calculatMultiPhrase(graph(),phrase1,'+')), phrase2, action));
//     }

//       if (lest_action == '*')
//     {
//         return (calculatMultiPhrase(g1 *(calculatMultiPhrase(graph(),phrase1,'+')), phrase2, action));
//     }
//       if (lest_action == '-')
//     {
//         return (calculatMultiPhrase(g1 -(calculatMultiPhrase(graph(),phrase1,'+')), phrase2, action));
//     }
//       if (lest_action == '^')
//     {
//         return (calculatMultiPhrase(g1 ^(calculatMultiPhrase(graph(),phrase1,'+')), phrase2, action));
//     }
//     // if (lest_action == '-')
//     // {
//     //     return ((calculatMultiPhrase(phrase1)) - (calculatMultiPhrase(phrase2)));
//     // }
//     // if (lest_action == '*')
//     // {
//     //     return ((calculatMultiPhrase(phrase1)) * (calculatMultiPhrase(phrase2)));
//     // }
//     // if (lest_action == '^')
//     // {
//     //     return ((calculatMultiPhrase(phrase1)) ^ (calculatMultiPhrase(phrase2)));
//     // }
//     // if (lest_action == '@')
//     // {
//     //     return (calculatMultiPhrase((g1 +(calculatMultiPhrase(graph()))),phrase1,'+'));
//     // }
//     // else 
//     {
//         throw SintaxError();
//     } 
// }


bool is_blanck_phrase(const std::string phrase) 
{
    for (auto letter : phrase)
    {
        if (!isblank(letter))
        {
            return false;
        }
    }
    return true;
}

std::string removeEnter(const std::string& phrase)
{
    std::string res;
    for (auto letter : phrase)
    {
        if (!((isblank(letter) && (!isspace(letter))) || (letter == EOF)))
        {
            res += letter;
        }
    }
    return res;
}

char get_first_letter(const std::string& phrase)
{
    if (is_blanck_phrase(phrase))
    {
        throw SintaxError();
    }
    for (auto letter : phrase)
    {
        if (!isblank(letter))
        {
            return letter;
        }
    }
    return ' ';
}


int countActions(const std::string phrase)
{
    int res = 0 ;
    for (auto letter : phrase)
    {
        if ((letter == '+') || (letter == '-') || (letter == '*') || (letter == '^'))
        {
            res++;
        }
    }
    return res;
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
        std::string filename;
        if(isLoadFanction(phrase, filename))
        {
            return graph::load(filename);
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

bool isLoadFanction(const std::string& phrase, std::string& filename )
{
    if ((std::count(phrase.begin(), phrase.end(), '(') != 1) || (std::count(phrase.begin(), phrase.end(), ')') != 1))
    {
        return false;
    }
    std::string res, commaned;
    bool bracket_apear = false, bracket_close = false;
    for (auto letter : phrase)
    {
        if ((letter != ' ') && bracket_close)
        {
            throw SintaxError();
        }
        if(bracket_apear)
        {
            if (letter == ')')
            {
                bracket_close = true;
                continue;
            }
            res += letter;
            continue;
        }
        if (letter == '(')
        {
            bracket_apear = true;
            continue;
        }
        commaned += letter;
    }
    if (!isLegalSpaceUse(commaned) || !isLegalSpaceUse(res))
    {
        throw WrongSpaceUse();
    }
    res = removeSpeces(res);
    std::string temp = removeSpeces(commaned);
    if (temp == "load")
    {
        filename = res;
        return true;
    }
    return false;
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