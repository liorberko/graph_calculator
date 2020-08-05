#include "Exception.h"

/*********************************/
/*         GraphException        */
/*********************************/
GraphException::GraphException() :
graph_error("Error: "), exception_name("Unknown Error") { }

GraphException::GraphException(const std::string error) :
graph_error("Error: "), exception_name(error) { }

/*********************************/
/*        IllegalArgument        */
/*********************************/
IllegalArgument::IllegalArgument() :
GraphException("IllegalArgument"), message(graph_error += exception_name) { }

const char* IllegalArgument::what() const noexcept
{
    return message.c_str();
}


/*********************************/
/*        IllegalVerticName        */
/*********************************/
IllegalVerticName::IllegalVerticName() :
GraphException("IllegalVerticName"), message(graph_error += exception_name) { }

const char* IllegalVerticName::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        IllegalEdgeName        */
/*********************************/
IllegalEdgeName::IllegalEdgeName() :
GraphException("IllegalEdgeName"), message(graph_error += exception_name) { }

const char* IllegalEdgeName::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        SelfArc        */
/*********************************/
SelfArc::SelfArc() :
GraphException("SelfArc"), message(graph_error += exception_name) { }

const char* SelfArc::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        ParallelEdges        */
/*********************************/
ParallelEdges::ParallelEdges() :
GraphException("ParallelEdges"), message(graph_error += exception_name) { }

const char* ParallelEdges::what() const noexcept
{
    return message.c_str();
}

/*********************************/
/*        ExtraComma        */
/*********************************/
ExtraComma::ExtraComma() :
GraphException("ExtraComma"), message(graph_error += exception_name) { }

const char* ExtraComma::what() const noexcept
{
    return message.c_str();
}