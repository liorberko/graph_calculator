#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>

class Exception : public std::exception { };
class GraphException : public Exception
{
protected:
    std::string graph_error;
    std::string exception_name;
public:
    GraphException();
    GraphException(const std::string error);
    virtual ~GraphException() = default;
};

class IllegalArgument : public GraphException
{ 
    std::string message;
public:
    IllegalArgument();
    ~IllegalArgument() = default;
    const char* what() const noexcept override;
};


class IllegalVerticName : public GraphException
{ 
    std::string message;
public:
    IllegalVerticName();
    ~IllegalVerticName() = default;
    const char* what() const noexcept override;
};

class IllegalEdgeName : public GraphException
{ 
    std::string message;
public:
    IllegalEdgeName();
    ~IllegalEdgeName() = default;
    const char* what() const noexcept override;
};

class SelfArc : public GraphException
{ 
    std::string message;
public:
    SelfArc();
    ~SelfArc() = default;
    const char* what() const noexcept override;
};

class ParallelEdges : public GraphException
{ 
    std::string message;
public:
    ParallelEdges();
    ~ParallelEdges() = default;
    const char* what() const noexcept override;
};

class ExtraComma : public GraphException
{ 
    std::string message;
public:
    ExtraComma();
    ~ExtraComma() = default;
    const char* what() const noexcept override;
};

#endif