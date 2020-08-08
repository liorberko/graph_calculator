#ifndef GRAFH_H
#define GRAFH_H
#include <iostream>
#include <string> 
#include <set>
#include <utility>
#include <vector>
#include "Exception.h"
#include <cctype>
#include "Auxiliaries.h"

class graph
{
private:
    std::set<std::string> vertices ; 
    std::set<std::pair<std::string, std::string>> edges ; 

public:
    graph() = default;
    graph(const std::set<std::string> vertices, const std::set<std::pair<std::string, std::string>> edges);
    explicit graph(const std::string& info);
    graph(const graph& target);
    ~graph() = default;

    static void save(const graph& g1, std::string& filename);
    static graph load(const std::string filename)
    {
        return graph();
    }

    bool containVertix(std::string name) const;
    void addEdgeWithLegalName(const std::string vertix1,const std::string vertix2);
    graph& operator=(const graph& target);
    graph operator+(const graph& target) const;
    graph operator^(const graph& target) const;
    graph operator-(const graph& target) const;
    graph operator*(const graph& target) const;
    graph operator!() const;

    friend std::ostream& operator<<(std::ostream& out,const graph& g1);
    void addEdge(std::string name);
    void addVertic(std::string name);

};




#endif