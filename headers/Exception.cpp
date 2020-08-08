#include "Exception.h"

/*********************************/
/*         GraphException        */
/*********************************/
GraphException::GraphException() :
graph_error("Error: "), exception_name("Unknown Error") { }

GraphException::GraphException(const std::string error) :
graph_error("Error: "), exception_name(error) { }

/*********************************/
/*        InvalidGraphLiteral        */
/*********************************/
InvalidGraphLiteral::InvalidGraphLiteral() :
GraphException("Invalid graph literal"), message(graph_error += exception_name) { }

const char* InvalidGraphLiteral::what() const noexcept
{
    return message.c_str();
}


/*********************************/
/*        IllegalVerticName        */
/*********************************/
IllegalVerticName::IllegalVerticName() :
GraphException("Illegal verticName"), message(graph_error += exception_name) { }

const char* IllegalVerticName::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        IllegalEdgeName        */
/*********************************/
IllegalEdgeName::IllegalEdgeName() :
GraphException("Illegal edgeName"), message(graph_error += exception_name) { }

const char* IllegalEdgeName::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        SelfArc        */
/*********************************/
SelfArc::SelfArc() :
GraphException("Self arc"), message(graph_error += exception_name) { }

const char* SelfArc::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        ParallelEdges        */
/*********************************/
ParallelEdges::ParallelEdges() :
GraphException("Parallel edges"), message(graph_error += exception_name) { }

const char* ParallelEdges::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        ExtraComma        */
/*********************************/
ExtraComma::ExtraComma() :
GraphException("Extra comma"), message(graph_error += exception_name) { }

const char* ExtraComma::what() const noexcept
{
    return message.c_str();
}


/*********************************/
/*        GraphDoesNotExist        */
/*********************************/
GraphDoesNotExist::GraphDoesNotExist() :
GraphException("Graph does not exist"), message(graph_error += exception_name) { }

const char* GraphDoesNotExist::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        IllegalGraphName        */
/*********************************/
IllegalGraphName::IllegalGraphName() :
GraphException("Illegal graph name"), message(graph_error += exception_name) { }

const char* IllegalGraphName::what() const noexcept
{
    return message.c_str();
}


/*********************************/
/*        SintaxError        */
/*********************************/
SintaxError::SintaxError() :
GraphException("Sintax error"), message(graph_error += exception_name) { }

const char* SintaxError::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        WrongSpaceUse        */
/*********************************/
WrongSpaceUse::WrongSpaceUse() :
GraphException("Wrong space use"), message(graph_error += exception_name) { }

const char* WrongSpaceUse::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        IllegalBracketUse        */
/*********************************/
IllegalBracketUse::IllegalBracketUse() :
GraphException("Illegal bracket use"), message(graph_error += exception_name) { }

const char* IllegalBracketUse::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        VertixNotExict        */
/*********************************/
VertixNotExict::VertixNotExict() :
GraphException("Vertix dose not exict"), message(graph_error += exception_name) { }

const char* VertixNotExict::what() const noexcept
{
    return message.c_str();
}





