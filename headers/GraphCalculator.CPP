#include "GraphCalculator.h"

// std::string removeSpeces(const std::string text);
// bool isSaveKey(const std::string name);

void graphCalculator::addGraph(const graph target, const std::string name)
{
    if (!isLegalGraphName(name))
    {
        throw IllegalGraphName();
    }
    std::string new_name = removeSpeces(name);
    graphs[new_name] = target;
}

// bool graphCalculator::isLegalGrafName( const std::string name)
// {
//     if (isSaveKey(name))
//     {
//         return false;
//     }
//     bool first_letter_apper = false;
//     bool space_after_letter = false;
//     for (auto key : name)
//     {
//         if ((key == ' ') && (first_letter_apper))
//         {
//             space_after_letter = true;
//             continue;
//         }
//         if (key != ' ')  
//         {
//             if (!std::isalnum(key))
//             {
//                 return false;
//             }
//             if (!first_letter_apper)
//             {
//                 if (!std::isalpha(key))
//                 {
//                     return false;
//                 }
//                 first_letter_apper = true;
//             }
//             if (space_after_letter)
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

void graphCalculator::print(const std::string name, std::ostream& out) const
{
    if (graphs.count(name) == 0)
    {
        throw GraphDoesNotExist();
    }
    graph temp = graphs.at(name);
    out <<  temp ;
}

void graphCalculator::who(std::ostream& out) const
{
    bool is_first = true;
    for (auto element : graphs)
    {
        if (!(is_first))
        {
            out << std::endl ; 
        }
        out << element.first ; 
        is_first = false;
    }
    out << std::endl;
}

void graphCalculator::remove(const std::string name)
{
    graphs.erase(name);
}  

void graphCalculator::reset()
{
    graphs.clear();
}

bool graphCalculator::contain(const std::string& name) const
{
    if (graphs.count(name))
    {
        return true;
    }
    return false;
}

graph& graphCalculator::get(const std::string& name)
{
    if (!(contain(name)))
    {
        throw GraphDoesNotExist();
    }
    return graphs[name];
}

graph graphCalculator::get(const std::string& name) const
{
    if (!(contain(name)))
    {
        throw GraphDoesNotExist();
    }
    graph new_graph = graphs.at(name);
    return new_graph;
}

// bool isSaveKey(const std::string name)
// {
//     if ((name == "print") || (name == "delete")  || (name == "who")
//     || (name == "reset") || (name == "quit") || (name == "save") || (name == "load"))
//     {
//         return true;
//     }
//     return false;
// }

// std::string removeSpeces(const std::string text)
// {
//     std::string res;
//     for (auto letter : text)
//     {
//         if (letter != ' ')
//         {
//             res += letter;
//         }
//     }
//     return res;
// }