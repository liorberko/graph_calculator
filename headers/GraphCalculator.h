#ifndef GRAPHCALCULATOR
#define GRAPHCALCULATOR
#include "Graph.h"
#include <map> 

class graphCalculator
{
private:
    std::map<std::string, graph> graphs;
public:
    graphCalculator() = default;
    ~graphCalculator() = default;

    void addGraph(const graph& target, const std::string name);
    void print(std::string name, std::ostream out) const; 
    void who() const;
    void remove(graph target);  
    void reset();
};




#endif