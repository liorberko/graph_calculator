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
#include <fstream>
#include <algorithm>


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

    static void save(const graph& g1, std::string filename);
    static graph load(std::string filename);

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

    graph graphUnion(const graph& graph_in) const;
    graph graphIntersection(const graph& graph_in) const;
    graph graphDifference(const graph& graph_in) const;
    graph graphProduct(const graph& graph_in) const;
    graph graphComplement() const;
    };




#endif