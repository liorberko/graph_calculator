#ifndef AUXILARIES_H
#define AUXILARIES_H
#include <string>
#include <iostream>
#include <ostream>
#include "Exception.h"




bool isSaveKey(const std::string name);


std::string removeSpeces(const std::string text);

bool isLegalGraphName( const std::string name);

bool isLegalSpaceUse(const std::string& phrase);

bool is_blanck_phrase(const std::string phrase);


#endif
