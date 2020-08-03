#ifndef GRAFH_H
#define GRAFH_H
#include <iostream>
#include <set>
#include <utility>
 

class graph
{
private:
    std::set<std::string> vertices ; 
    std::set<std::pair<std::string, std::string>> edges ; 

    static bool isLegalInfo(const std::string& info);
    static bool isLegalVerticName(const std::string& info);
public:
    graph();
    graph(const std::set<std::string>& vertices, const std::set<std::pair<std::string, std::string>>& edges);
    graph(const std::string& info);
    graph(const graph& target);
    ~graph();

    graph operator+(const graph& target) const;
    graph operator^(const graph& target) const;
    graph operator-(const graph& target) const;
    graph operator*(const graph& target) const;
    graph operator!() const;

    friend std::ostream operator<<(std::ostream out, graph& G1);

    static void save(const graph G1, std::string filename);
    static graph load(std::string filename);
};

graph::graph(/* args */)
{
}

graph::~graph()
{
}


#endif