#include "graphCalculatorParser.h"
#include <algorithm>
#define DONE '%'


graph stringToGraph(const std::string phrase,const graphCalculator& G1);
bool firstLetterIsExclamationMark(const std::string& phrase);
std::string removeExclamationMark(const std::string& phrase);
int countActions(const std::string phrase);
std::string removeEnter(const std::string& phrase);
char get_first_letter(const std::string& phrase);
bool isLoadFanction(const std::string& phrase, std::string& filename );
char findeAndRemoveLasstAction(std::string& phrase);
bool conteine_only_exclamation_mark_phrase(const std::string phrase);

graphCalculator graphCalculatorParser::memory;


graphCalculatorParser::graphCalculatorParser(std::string line, std::ostream* out) : line(line), out(out) { }

bool graphCalculatorParser::applyLine() 
{
    line = removeEnter(line);
    if (std::count(line.begin(), line.end(), '=') == 1)
    {
        std::string graph_name, phrase;
        bool equals_apear = false;
        for (auto letter : line)
        {
            if(equals_apear)
            {
                phrase += letter;
                continue;
            }
            if (letter == '=')
            {
                equals_apear = true;
                continue;
            }
            graph_name += letter;
        }
        if (!isLegalGraphName(graph_name))
        {
            throw IllegalGraphName();
        }
        graph_name = removeEnter(graph_name);
        graph temp = calculatComplexPhrase(phrase);
        memory.addGraph(temp, graph_name);
        return true;
    }
    else if (std::count(line.begin(), line.end(), '(') == 0)
    {
        if(!isLegalSpaceUse(line))
        {
            throw WrongSpaceUse();
        }
        line = removeSpeces(line);
        if(line == "who")
        {
            memory.who(*out);
            return true;
        }
        else if (line == "reset")
        {
            memory.reset();
            return true;
        }
        else if (line == "quit")
        {
            return false;
        }
        else
        {
            throw SintaxError();
        }
    }
    else
    {
        std::string comened, phrase, leftover;
        int bracker_counter = 0;
        bool first_bracket_apear = false, bracket_closed = false;
        for (auto letter : line)
        {
            if (bracket_closed)
            {
                leftover += letter;
                continue;
            }
            if (letter == ')')
            {
                bracker_counter--;
                if (bracker_counter < 0)
                {
                    throw IllegalBracketUse();
                }
                if (bracker_counter == 0)
                {
                    bracket_closed = true;
                    continue;
                }
            }
            if (letter == '(')
            {
                bracker_counter++;
                if (!first_bracket_apear)
                {
                    first_bracket_apear = true;
                    continue;
                }
            }
            if(first_bracket_apear)
            {
                phrase += letter;
                continue;
            }
            comened += letter;
        }
        if (!is_blanck_phrase(leftover))
        {
            throw SintaxError();
        }
        if (!isLegalSpaceUse(comened))
        {
            throw WrongSpaceUse();
        }
        comened = removeSpeces(comened);
        if (comened == "print")
        {
            graph temp = calculatComplexPhrase(phrase);
            *out << temp;
            return true; 
        }
        else if (comened == "delete")
        {
            if(!isLegalSpaceUse(phrase))
            {
                throw WrongSpaceUse();
            }
            phrase = removeSpeces(phrase);
            if (!memory.contain(phrase))
            {
                throw GraphDoesNotExist();
            }
            memory.remove(phrase);
            return true;
        }
        else if (comened == "save")
        {
            std::string filename, graph_name;
            bool come_apear = false;
            for (auto letter : phrase)
            {
                if (come_apear)
                {
                    filename += letter;
                    continue;
                }
                if (letter == ',')
                {
                    come_apear = true;
                    continue;
                }
                graph_name += letter;
            }
            if (!isLegalSpaceUse(graph_name))
            {
                throw WrongSpaceUse();
            }
            graph_name = removeSpeces(graph_name);
            save((memory.get(graph_name)), filename);
            return true;
        }
        else
        {
            throw SintaxError();
        }
    }
    throw SintaxError();
}

graph graphCalculatorParser::calculatComplexPhrase(std::string phrase) const
{
    if ((std::count(phrase.begin(), phrase.end(), '(') == 0) || 
    ((std::count(phrase.begin(), phrase.end(), '(') == 1) &&  (phrase.find("load") != std::string::npos)))
    {
        return calculatMultiPhrase(phrase);
    }
    int bracket_counter = 0;
    bool bracket_closed = false, first_bracket_met = false, record_action2 = false;
    std::string phrash1, phrase2, bracket_phrase;
    char action1, action2;
    for (auto letter : phrase)
    {
        if(record_action2)
        {
            if ( letter == ' ')
            {
                continue;
            }
            action2 = letter;
            record_action2 = false;
            continue;
        }
        if (bracket_closed)
        {
            phrase2 += letter;
            continue;
        }
        if (letter == ')')
        {
            bracket_counter--;
            if (bracket_counter < 0)
            {
                throw IllegalBracketUse();
            }
            if ((bracket_counter == 0) && first_bracket_met)
            {
                record_action2 = true;
                bracket_closed = true;

                continue; 
            }
        }
        if (letter == '(')
        {
            bracket_counter++;
            if (!first_bracket_met && (phrash1.find("load") != std::string::npos))
            {
                phrash1 += letter;
                continue;
            }
            if (!first_bracket_met)
            {
                first_bracket_met = true;
                continue;
            }
        }
        if (first_bracket_met)
        {
            bracket_phrase += letter;
            continue;
        }
        phrash1 += letter;
    }
    if (is_blanck_phrase(phrase2))
    {
        if (!conteine_only_exclamation_mark_phrase(phrash1))
        {
            action1 =  findeAndRemoveLasstAction(phrash1);
            int exclamation_mark_counter = 0;
            while ((action1 == '+') || (action1 == '-') || (action1 == '*') || (action1 == '^') || (action1 == '!'))
            {
                if (!(exclamation_mark_counter%2))
                {
                    if(action1 == '+')
                    {
                        return (stringToGraph(phrash1, memory) + calculatComplexPhrase(bracket_phrase));
                    }
                    else if(action1 == '*')
                    {
                        return (stringToGraph(phrash1, memory) * calculatComplexPhrase(bracket_phrase));
                    }
                    else if(action1 == '^')
                    {
                        return (stringToGraph(phrash1, memory) ^ calculatComplexPhrase(bracket_phrase));
                    }
                    else if(action1 == '-')
                    {
                        return (stringToGraph(phrash1, memory) - calculatComplexPhrase(bracket_phrase));
                    }
                    else if (action1 == '!')
                    {
                        exclamation_mark_counter++;
                        action1 =  findeAndRemoveLasstAction(phrash1);
                    }
                }
                else 
                {
                    if(action1 == '+')
                    {
                        return (stringToGraph(phrash1, memory) + !(calculatComplexPhrase(bracket_phrase)));
                    }
                    else if(action1 == '*')
                    {
                        return (stringToGraph(phrash1, memory) * !(calculatComplexPhrase(bracket_phrase)));
                    }
                    else if(action1 == '^')
                    {
                        return (stringToGraph(phrash1, memory) ^ !(calculatComplexPhrase(bracket_phrase)));
                    }
                    else if(action1 == '-')
                    {
                        return (stringToGraph(phrash1, memory) - !(calculatComplexPhrase(bracket_phrase)));
                    }
                    else if (action1 == '!')
                    {
                        exclamation_mark_counter++;
                        action1 =  findeAndRemoveLasstAction(phrash1);
                    }
                }
            }
            throw IllegalBracketUse();
        }
        else if (is_blanck_phrase(phrash1))
        {
            return (calculatComplexPhrase(bracket_phrase));
        }
        else
        {
            int exclamation_mark_counter = 0;
            while (!(is_blanck_phrase(phrash1)))
            {
                action1 =  findeAndRemoveLasstAction(phrash1);
                exclamation_mark_counter++;
            }
            if(exclamation_mark_counter%2)
            {
                return (calculatComplexPhrase(bracket_phrase));
            }
            else
            {
                return (!(calculatComplexPhrase(bracket_phrase)));
            }
        }
    }
    else if (is_blanck_phrase(phrash1))
    {
        if(action2 == '+')
        {
            return (calculatComplexPhrase(bracket_phrase) + calculatComplexPhrase(phrase2));
        }
        else if(action2 == '*')
        {
            return (calculatComplexPhrase(bracket_phrase) * calculatComplexPhrase(phrase2));
        }
        else if(action2 == '^')
        {
            return (calculatComplexPhrase(bracket_phrase) ^ calculatComplexPhrase(phrase2));
        }
        else if(action2 == '-')
        {
            return (calculatComplexPhrase(bracket_phrase) - calculatComplexPhrase(phrase2));
        }
        else
        {
            throw IllegalBracketUse();
        }
    }
    else if (!conteine_only_exclamation_mark_phrase(phrash1))
    {
        action1 =  findeAndRemoveLasstAction(phrash1);
        return (astimetThreePhrases(phrash1, bracket_phrase, phrase2, action1, action2));
    }
    else
    {
        int exclamation_mark_counter = 0;
        while (!(is_blanck_phrase(phrash1)))
        {
            action1 =  findeAndRemoveLasstAction(phrash1);
            exclamation_mark_counter++;
        }
        if(exclamation_mark_counter%2)
        {
            if(action2 == '+')
            {
                return (calculatComplexPhrase(bracket_phrase) + calculatComplexPhrase(phrase2));
            }
            else if(action2 == '*')
            {
                return (calculatComplexPhrase(bracket_phrase) * calculatComplexPhrase(phrase2));
            }
            else if(action2 == '^')
            {
                return (calculatComplexPhrase(bracket_phrase) ^ calculatComplexPhrase(phrase2));
            }
            else if(action2 == '-')
            {
                return (calculatComplexPhrase(bracket_phrase) - calculatComplexPhrase(phrase2));
            }
            else
            {
                throw IllegalBracketUse();
            }
        }
        else
        {
            if(action2 == '+')
            {
                return (!(calculatComplexPhrase(bracket_phrase)) + calculatComplexPhrase(phrase2));
            }
            else if(action2 == '*')
            {
                return (!(calculatComplexPhrase(bracket_phrase)) * calculatComplexPhrase(phrase2));
            }
            else if(action2 == '^')
            {
                return (!(calculatComplexPhrase(bracket_phrase)) ^ calculatComplexPhrase(phrase2));
            }
            else if(action2 == '-')
            {
                return (!(calculatComplexPhrase(bracket_phrase)) - calculatComplexPhrase(phrase2));
            }
            else
            {
                throw IllegalBracketUse();
            }
        }
    }
 
}


char findeAndRemoveLasstAction(std::string& phrase)
{
    char res;
    reverse(phrase.begin(),phrase.end());
    std::string temp;
    bool recored_the_rest = false;
    for (auto letter : phrase)
    {
        if (recored_the_rest)
        {
            temp += letter;
            continue;
        }
        if (letter == ' ')
        {
            continue;
        }
        res = letter;
        recored_the_rest = true;
    }
    reverse(temp.begin(),temp.end());
    phrase = temp;
    return res;
}

graph graphCalculatorParser::calculatPhrase
(graph g1, std::string phrase2, char& action) const
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

std::string graphCalculatorParser::fechNexPhrase(std::string& input, char& action) const
{
    std::string phrase, leftover;
    bool record_leftover = false;
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

graph graphCalculatorParser::calculatMultiPhrase(std::string phrase) const
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
        char next_action;
        std::string phrase2 = fechNexPhrase(phrase, next_action);
        if (action == DONE)
        {
            continue;
        }
        res = calculatPhrase(res,phrase2,action);
        action = next_action;

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



bool conteine_only_exclamation_mark_phrase(const std::string phrase)
{
    for (auto letter : phrase)
    {
        if ((!isblank(letter)) && (!(letter == '!')))
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
    bool exclamation_mark_on = false;
    if (firstLetterIsExclamationMark(phrase))
    {
        exclamation_mark_on = true;
    }
    phrase = removeExclamationMark(phrase);
    if (phrase.find('{') == std::string::npos) 
    {
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
        if (exclamation_mark_on)
        {
            return (!(new_graph));
        }
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
    int res;
    for (auto letter : phrase)
    {
        if (letter == ' ')
        {
            continue;
        }
        else if (letter == '!')
        {
            res++;
        }
        else 
        {
            break;
        }
        
    }
    return (res%2);
}

std::string removeExclamationMark(const std::string& phrase)
{
    std::string res;
    bool first_letter_apear = false;
    for (auto letter : phrase)
    {
        if (letter == ' ')
        {
            res += ' ';
            continue;
        }
        else if (letter == '!')
        {
            if(first_letter_apear)
            {
                res += letter ;
            }
        }
        else
        {
            first_letter_apear = true;
            res += letter;
        }
    } 
    return res;
}

graph graphCalculatorParser::astimetThreePhrases
(const std::string& phrase1, const std::string& phrase2,const std::string& phrase3, char action1, char action2) const
{
    if (action1 == '+')
    {
        if (action2 == '+')
        {
            return ((calculatComplexPhrase(phrase1) + calculatComplexPhrase(phrase2)) + calculatComplexPhrase(phrase3));
        }
        else if (action2 == '-')
        {
            return ((calculatComplexPhrase(phrase1) + calculatComplexPhrase(phrase2)) - calculatComplexPhrase(phrase3));
        }
        else if (action2 == '*')
        {
            return ((calculatComplexPhrase(phrase1) + calculatComplexPhrase(phrase2)) * calculatComplexPhrase(phrase3));
        }
        else if (action2 == '^')
        {
            return ((calculatComplexPhrase(phrase1) + calculatComplexPhrase(phrase2) )^ calculatComplexPhrase(phrase3));
        }
        else
        {
            throw SintaxError();
        }
    }
    else if (action1 == '-')
    {
        if (action2 == '+')
        {
            return ((calculatComplexPhrase(phrase1) - calculatComplexPhrase(phrase2)) + calculatComplexPhrase(phrase3));
        }
        else if (action2 == '-')
        {
            return ((calculatComplexPhrase(phrase1) - calculatComplexPhrase(phrase2)) - calculatComplexPhrase(phrase3));
        }
        else if (action2 == '*')
        {
            return ((calculatComplexPhrase(phrase1) - calculatComplexPhrase(phrase2)) * calculatComplexPhrase(phrase3));
        }
        else if (action2 == '^')
        {
            return ((calculatComplexPhrase(phrase1) - calculatComplexPhrase(phrase2)) ^ calculatComplexPhrase(phrase3));
        }
        else
        {
            throw SintaxError();
        }
    }
    else if (action1 == '*')
    {
        if (action2 == '+')
        {
            return ((calculatComplexPhrase(phrase1) * calculatComplexPhrase(phrase2)) + calculatComplexPhrase(phrase3));
        }
        else if (action2 == '-')
        {
            return ((calculatComplexPhrase(phrase1) * calculatComplexPhrase(phrase2)) - calculatComplexPhrase(phrase3));
        }
        else if (action2 == '*')
        {
            return ((calculatComplexPhrase(phrase1) * calculatComplexPhrase(phrase2)) * calculatComplexPhrase(phrase3));
        }
        else if (action2 == '^')
        {
            return ((calculatComplexPhrase(phrase1) * calculatComplexPhrase(phrase2)) ^ calculatComplexPhrase(phrase3));
        }
        else
        {
            throw SintaxError();
        }
    }
    else if (action1 == '^')
    {
        if (action2 == '+')
        {
            return ((calculatComplexPhrase(phrase1) ^ calculatComplexPhrase(phrase2)) + calculatComplexPhrase(phrase3));
        }
        else if (action2 == '-')
        {
            return ((calculatComplexPhrase(phrase1) ^ calculatComplexPhrase(phrase2)) - calculatComplexPhrase(phrase3));
        }
        else if (action2 == '*')
        {
            return ((calculatComplexPhrase(phrase1) ^ calculatComplexPhrase(phrase2)) * calculatComplexPhrase(phrase3));
        }
        else if (action2 == '^')
        {
            return ((calculatComplexPhrase(phrase1) ^ calculatComplexPhrase(phrase2)) ^ calculatComplexPhrase(phrase3));
        }
        else
        {
            throw SintaxError();
        }
    }
    else
    {
        throw SintaxError();
    }
    
}