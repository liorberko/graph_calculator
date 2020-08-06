#ifndef GRAFH_H
#define GRAFH_H
#include <iostream>
#include <string> 
#include <set>
#include <utility>
#include <vector>
#include "Exception.h"
#include <cctype>

class graph
{
private:
    std::set<std::string> vertices ; 
    std::set<std::pair<std::string, std::string>> edges ; 

    void addEdge(std::string name);
  //  void addEdge(const std::pair<std::string, std::string> name);
    void addVertic(std::string name);
public:
    graph() = default;
    graph(const std::set<std::string> vertices, const std::set<std::pair<std::string, std::string>> edges);
    explicit graph(const std::string& info);
    graph(const graph& target);
    ~graph() = default;

    graph& operator=(const graph& target);
    graph operator+(const graph& target) const;
    graph operator^(const graph& target) const;
    graph operator-(const graph& target) const;
    graph operator*(const graph& target) const;
    graph operator!() const;

    friend std::ostream& operator<<(std::ostream& out, graph& g1);

    static void save(const graph g1, std::string filename);
    static graph load(std::string filename);
};



#endif