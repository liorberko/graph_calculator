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

    graph& get(const std::string& name);
    graph get(const std::string& name) const;
    bool contain(const std::string& name) const;
    void addGraph(const graph target, const std::string name);
    void print(const std::string name, std::ostream& out = std::cout) const; 
    void who(std::ostream& out = std::cout) const;
    void remove(const std::string name);  
    void reset();
};




#endif