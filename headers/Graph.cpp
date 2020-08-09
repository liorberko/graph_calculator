#include "graph.h"

graph* create()
{
    graph* object;
    try
    {
        object = new graph;
    }
    catch(const std::exception& err)
    {
        std::cout << err.what() << '\n';
    }
    return object;
}

void destroy(graph* target)
{
    if (target == NULL)
    {
        return;
    }
    delete(target);
}

graph* addVertex(graph* target, const char* name)
{
    if (target == nullptr)
    {
        std::cout << "Error: null pointer";
        return target;
    }
    try
    {
        (*target).addVertic(name);
    }
    catch(const std::exception& err)
    {
        std::cout << err.what() << '\n';
    }
    return target;
}

graph* addEdge(graph* target, const char* name1, const char* name2)
{
    if (target == nullptr)
    {
        std::cout << "Error: null pointer";
        return target;
    }
    try
    {
        if ((!(*target).containVertix(name1)) || (!(*target).containVertix(name2)))
        {
            throw VertixNotExict();
        }
        if (name1 == name2)
        {
            throw SelfArc();
        }
        (*target).addEdgeWithLegalName(name1, name2);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return target;
}

void disp(const graph* target)
{
    std::cout << (*target);
}

graph* graphUnion(const graph* graph_in1, const graph* graph_in2, graph* graph_out)
{
    if ((graph_in1 == nullptr) || (graph_in2 == nullptr) || (graph_out == nullptr))
    {
        std::cout << "Error: null pointer";
        return graph_out;
    }
    try
    {
        (*graph_out) = ((*graph_in1).graphUnion(*graph_in2));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph_out;
}

graph* graphIntersection(const graph* graph_in1, const graph* graph_in2, graph* graph_out)
{
    if ((graph_in1 == nullptr) || (graph_in2 == nullptr) || (graph_out == nullptr))
    {
        std::cout << "Error: null pointer";
        return graph_out;
    }
    try
    {
        (*graph_out) = ((*graph_in1).graphIntersection(*graph_in2));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph_out;
}


graph* graphDifference(const graph* graph_in1, const graph* graph_in2, graph* graph_out)
{
    if ((graph_in1 == nullptr) || (graph_in2 == nullptr) || (graph_out == nullptr))
    {
        std::cout << "Error: null pointer";
        return graph_out;
    }
    try
    {
        (*graph_out) = ((*graph_in1).graphDifference(*graph_in2));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph_out;
}

graph* graphProduct(const graph* graph_in1, const graph* graph_in2, graph* graph_out)
{
    if ((graph_in1 == nullptr) || (graph_in2 == nullptr) || (graph_out == nullptr))
    {
        std::cout << "Error: null pointer";
        return graph_out;
    }
    try
    {
        (*graph_out) = ((*graph_in1).graphProduct(*graph_in2));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph_out;
}
graph* graphComplement(const graph* graph_in, graph* graph_out)
{
    if ((graph_in == nullptr) || (graph_out == nullptr))
    {
        std::cout << "Error: null pointer";
        return graph_out;
    }
    try
    {
        (*graph_out) = ((*graph_in).graphComplement());
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return graph_out;
}