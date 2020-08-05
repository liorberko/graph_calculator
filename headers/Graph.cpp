#include "Graph.h"

bool isLegalVerticName(std::string& name);
bool isLegalEdgeName(std::string& name);

graph::graph(const std::set<std::string> vertices, const std::set<std::pair<std::string, std::string>> edges) :
vertices(vertices), edges(edges) { }

graph::graph(const graph& target) :
vertices(target.vertices), edges(target.edges) {}

graph::graph(const std::string& info)
{
    bool is_a_vertic = true, is_first = true;
    int line_counter =0, clos_counter =0;
    std::string vertic;
    std::string edge;

    for(auto letter : info)
    {
        if (is_first)
        {   
            if (std::isblank(letter)) continue;
            if (letter != '{')
            {
                throw IllegalArgument();
            }
            is_first = false;
            continue;
        }
        if (letter == '|')
        {
            line_counter++;
            if (line_counter > 1)
            {
                throw IllegalArgument();
            } 
            is_a_vertic = false;
            addVertic(vertic);
            continue;
        }
        if (is_a_vertic){
            if ((letter == ',') || ((letter == '}') && ((++clos_counter) < 2))){
                addVertic(vertic);
                vertic.clear();
                continue;
            }
            vertic.push_back(letter);
            if (clos_counter > 1) {throw IllegalArgument();}

        }
        else 
        {
            if ((letter == ',') || ((letter == '}') && ((++clos_counter) < 2))){
                addEdge(edge);
                edge.clear();
                continue;
            }
            edge.push_back(letter);
            if (clos_counter > 1) {throw IllegalArgument();}
        }
    }
}


bool isLegalVerticName(std::string& name)
{
    std::string res;
    bool first_letter_apper = false;
    bool space_after_letter = false;
    int parenthesis_count = 0 ;
    for (auto letter : name)
    {
        if ((letter == ' ') && (first_letter_apper))
        {
            space_after_letter = true;
            continue;
        }
        if (letter != ' ')  
        {
            first_letter_apper = true;
            if (space_after_letter){
                return false;
            }
            continue;
        }
        if (letter == '[')
        {
            parenthesis_count++;
            res.push_back(letter);
            continue;
        }
        if (letter == ']')
        {
            if (parenthesis_count < 1)
            {
                return false;
            }
            parenthesis_count--;
            res.push_back(letter);
            continue;
        }
        if (letter == ';')
        {
            if (parenthesis_count < 1)
            {
                return false;
            }
            res.push_back(letter); 
            continue;
        }
        if (((letter < 'a') && (letter > 'z')) && ((letter < 'A') && (letter > 'Z')))
        {
           return false;
        }
        res.push_back(letter);
    }
    if (res.size() == 0)
    {
        throw IllegalVerticName();
    }
    if (parenthesis_count == 0)
    {
          name = res;
          return true;
    }
    return false;
}


void graph::addVertic(std::string name)
{
    if(!isLegalVerticName(name))
    {
        throw IllegalVerticName();
    }
    vertices.insert(name);
}


void graph::addEdge(std::string name)
{
    bool first_letter_apper = false, comma_apper = false, second_parenthesis_apper = false;
    std::string first_ver, seconed_ver;
    for (auto letter : name)
    {
        if (second_parenthesis_apper)
        {
            if(letter != ' ')
            {
                throw IllegalEdgeName();
            }
            continue;
        }
        if ((letter == ' ') && (!first_letter_apper))
        {
            continue;
        }
        if ((letter != '<') && (!first_letter_apper))
        {
            throw IllegalEdgeName();
        }
        if (letter == '<') {
            if(first_letter_apper)
            {
                throw IllegalEdgeName();
            }
            first_letter_apper = true;
            continue;
        }
        if (letter == ',')
        {
            if(comma_apper)
            {
                throw IllegalEdgeName();
            }
            comma_apper = true;
            if ((!isLegalVerticName(first_ver)) || (vertices.find(first_ver) == vertices.end()))
            {
                throw IllegalEdgeName();
            }
            continue;
        }
        if (letter == '>')
        {
            if ((!isLegalVerticName(seconed_ver)) || (vertices.find(seconed_ver) == vertices.end()))
            {
                throw IllegalEdgeName();
            }
            second_parenthesis_apper = true;
            continue;
        }
        if (first_letter_apper && (!comma_apper))
        {
            first_ver.push_back(letter);
        }
        if (comma_apper)
        {
            seconed_ver.push_back(letter);
        }
    }
    if (first_ver == seconed_ver)
    {
        throw SelfArc();
    }
    std::pair<std::string, std::string> new_egde (first_ver, seconed_ver);
    edges.insert(new_egde);
}

graph& graph::operator=(const graph& target)
{
    edges = target.edges;
    vertices = target.vertices;
}

graph graph::operator+(const graph& target) const
{
    std::set<std::string> res_vertices = vertices;
    res_vertices.insert(target.vertices.begin(), target.vertices.end());
    std::set<std::pair<std::string, std::string>> res_edges = target.edges;
    res_edges.insert(edges.begin(), edges.end());
    graph res_graph(res_vertices, res_edges);
    return res_graph;
}


graph graph::operator^(const graph& target) const
{
    graph res_graph;
    for (auto vertix : target.vertices)
    {
        if (vertices.count(vertix))
        {
            res_graph.vertices.insert(vertix);
        }
    }
    for (auto edge : target.edges)
    {
        if (edges.count(edge))
        {
            res_graph.edges.insert(edge);
        }
    }
    return res_graph;
}

graph graph::operator-(const graph& target) const
{
    graph res_graph = (*this);
    for (auto vertix : res_graph.vertices)
    {
        if (target.vertices.count(vertix))
        {
            res_graph.vertices.erase(vertix);
            for (auto edge : res_graph.edges)
            {
                if ((edge.first == vertix) || (edge.second == vertix))
                {
                    res_graph.edges.erase(edge);
                }
            }
            
        }
    }
    return res_graph;
}

graph graph::operator*(const graph& target) const
{
    graph res_graph;
    for (auto vertix1 : vertices)
    {
        for (auto vertix2 : target.vertices)
        {
            std::string new_vertix = ("[" + vertix1 + ";" + vertix2 + "]" );
            res_graph.vertices.insert(new_vertix);
        }
    }
    for (auto edge1 : edges)
    {
        for (auto edge2 : target.edges)
        {
            std::pair<std::string, std::string> new_edge(("[" + edge1.first + ";" + edge2.first + "]"),
            ("[" + edge1.second + ";" + edge2.second + "]"));
            res_graph.edges.insert(new_edge);
        }
    }
    return res_graph;
}

graph graph::operator!() const
{
    graph temp_graph = (*this);
    for (auto vertix1 : vertices)
    {
        for (auto vertix2 : vertices)
        {
            if(vertix1 != vertix2)
            {
                std::pair<std::string,std::string> temp_pair(vertix1,vertix2);
                temp_graph.edges.insert(temp_pair);
            }
        }
    }
    for (auto edge : edges)
    {
        temp_graph.edges.erase(edge);
    }
    return temp_graph;
}

std::ostream& operator<<(std::ostream& out, graph& g1)
{
    for (auto vertix : g1.vertices)
    {
        out << vertix << std::endl ; 
    }
    out << '$' << std::endl ; 
    for (auto edge : g1.edges)
    {
        out << edge.first << ' ' << edge.second << std::endl ; 
    }
}