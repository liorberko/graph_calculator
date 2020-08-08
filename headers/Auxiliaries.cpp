
#include "Auxiliaries.h"



bool isSaveKey(const std::string name)
{
    if ((name == "print") || (name == "delete")  || (name == "who")
    || (name == "reset") || (name == "quit") || (name == "save") || (name == "load"))
    {
        return true;
    }
    return false;
}

std::string removeSpeces(const std::string text)
{
    std::string res;
    for (auto letter : text)
    {
        if (letter != ' ')
        {
            res += letter;
        }
    }
    return res;
}


bool isLegalGraphName(const std::string name)
{
    if (isSaveKey(name))
    {
        return false;
    }
    if (name.size() == 0)
    {
        return false;
    }
    bool first_letter_apper = false;
    bool space_after_letter = false;
    for (auto key : name)
    {
        if ((key == ' ') && (first_letter_apper))
        {
            space_after_letter = true;
            continue;
        }
        if (key != ' ')  
        {
            if (!std::isalnum(key))
            {
                return false;
            }
            if (!first_letter_apper)
            {
                if (!std::isalpha(key))
                {
                    return false;
                }
                first_letter_apper = true;
            }
            if (space_after_letter)
            {
                return false;
            }
        }
    }
    return true;
}


bool isLegalSpaceUse(const std::string& phrase)
{
    bool first_letter_apper = false;
    bool space_after_letter = false;
    for (auto key : phrase)
    {
        if ((key == ' ') && (first_letter_apper))
        {
            space_after_letter = true;
            continue;
        }
        if (key != ' ')  
        {
            first_letter_apper = true;
            if (space_after_letter)
            {
                return false;
            }
        }
    }
    return true;
}


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