#include "GraphFactory.h"

bool emptyGrapg(const std::string& text);
bool isLegalVerticName(const std::string& name);
bool isLegalEdgeName(std::string& name);
std::pair<std::string,std::string> getEdgeFromFile(const std::string& filename);
std::string getVertexFromFile(const std::string filename);
std::string fixFilename(const std::string& filename);

graph::graph(const std::set<std::string> vertices, const std::set<std::pair<std::string, std::string>> edges) :
vertices(vertices), edges(edges) { }

graph::graph(const graph& target) :
vertices(target.vertices), edges(target.edges) {}

graph::graph(const std::string& info)
{
    if (emptyGrapg(info))
    {
        return;
    }
    bool is_a_vertic = true, is_first = true, edge_exists = false, secondery_comma = false;
    int line_counter =0, clos_counter =0, angel_bracket_count = 0;
    std::string vertic;
    std::string edge;

    for(auto letter : info)
    {
        if (is_first)
        {   
            if (std::isblank(letter)) continue;
            if (letter != '{')
            {
                throw InvalidGraphLiteral();
            }
            is_first = false;
            continue;
        }
        if (letter == '|')
        {
            line_counter++;
            if (line_counter > 1)
            {
                throw InvalidGraphLiteral();
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
            if (clos_counter > 1) {throw InvalidGraphLiteral();}

        }
        else 
        {
            if(letter == '<')
            {
                angel_bracket_count++;
            }
            if(letter == '>')
            {
                angel_bracket_count--;
            }
            if ((letter == ',') && (angel_bracket_count == 0))
            {
                secondery_comma = true;
            }
            if (((letter == ',') && (angel_bracket_count == 0) ) || ((letter == '}') && ((++clos_counter) < 2) && (edge_exists)))
            {
                if (secondery_comma && ((removeSpeces(edge)).size() == 0))
                {
                    throw ExtraComma();
                }
                addEdge(edge);
                edge.clear();
                continue;
            }
            if(letter != ' ')
            {
                edge_exists = true;
            }
            edge.push_back(letter);
            if (clos_counter > 1) {throw InvalidGraphLiteral();}
        }
    }
}


bool isLegalVerticName(const std::string& name)
{
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
            if (space_after_letter)
            {
                return false;
            }
        }
        if (letter == '[')
        {
            parenthesis_count++;
            continue;
        }
        if (letter == ']')
        {
            if (parenthesis_count < 1)
            {
                return false;
            }
            parenthesis_count--;
            continue;
        }
        if (letter == ';')
        {
            if (parenthesis_count < 1)
            {
                return false;
            }
            continue;
        }
        if (!(((letter >= 'a') && (letter <= 'z')) || ((letter >= 'A') && (letter <= 'Z')) || (letter == ' ') || ((letter >='0') && (letter <='9'))))
        {
           return false;
        }
    }
    if (parenthesis_count == 0)
    {
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
    std::string new_name = removeSpeces(name);
    vertices.insert(new_name);
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
            if ((!isLegalVerticName(first_ver)) || (vertices.find(removeSpeces(first_ver)) == vertices.end()))
            {
                throw IllegalEdgeName();
            }
            continue;
        }
        if (letter == '>')
        {
            if ((!isLegalVerticName(seconed_ver)) || (vertices.find(removeSpeces(seconed_ver)) == vertices.end()))
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
    first_ver = removeSpeces(first_ver);
    seconed_ver = removeSpeces(seconed_ver);
    if (first_ver == seconed_ver)
    {
        throw SelfArc();
    }
    std::pair<std::string, std::string> new_egde (first_ver, seconed_ver);
    if (edges.count(new_egde))
    {
        throw ParallelEdges();
    }
    edges.insert(new_egde);
}

graph& graph::operator=(const graph& target)
{
    edges = target.edges;
    vertices = target.vertices;
    return (*this);
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

std::ostream& operator<<(std::ostream& out,const graph& g1)
{
    for (auto vertix : g1.vertices)
    {
        out << vertix << std::endl ; 
    }
    out << '$'; 
    for (auto edge : g1.edges)
    {
        out << std::endl << edge.first << ' ' << edge.second; 
    }
    out<<std::endl;
    return out;
}

bool emptyGrapg(const std::string& text)
{
    for (auto letter : text)
    {
        if ((letter != ' ') && (letter != '{') && (letter != '}') && (letter != '|') )
        {
            return false;
        }
    }
    return true;
}

bool graph::containVertix(std::string name) const
{
    if (vertices.count(name) == 0)
    {
        return false;
    }
    return true;
}

void graph::addEdgeWithLegalName(const std::string vertix1, const std::string vertix2)
{
    std::pair<std::string, std::string> edge = { vertix1, vertix2 };
    edges.insert(edge); 
}


graph graph::graphUnion(const graph& graph_in) const
{
    return (*this + graph_in);
}

graph graph::graphIntersection(const graph& graph_in) const
{
    return (*this ^ graph_in);
}

graph graph::graphDifference(const graph& graph_in) const
{
    return (*this - graph_in);
}

graph graph::graphProduct(const graph& graph_in) const
{
    return (*this * graph_in);
}

graph graph::graphComplement() const
{
    return (!(*this));
}


void graph::save(const graph& g1,std::string filename)
{
    filename = fixFilename(filename);
    std::ofstream outfile(filename, std::ios_base::binary);
    if (!outfile)
    {
        throw CanNotOpenFile();
    }
    unsigned num_of_veteces = g1.vertices.size();
    unsigned num_of_edges = g1.vertices.size();
    outfile.write(reinterpret_cast<char*>(&num_of_veteces), sizeof(int));
    outfile.write(reinterpret_cast<char*>(&num_of_edges), sizeof(int));
    for (auto vertex : g1.vertices)
    {
        unsigned vertex_strlen = vertex.size();
        outfile.write(reinterpret_cast<char*>(&vertex_strlen), sizeof(vertex_strlen));
        outfile.write(vertex.c_str(), vertex_strlen);
    }
    for (auto edge : g1.edges)
    {
        unsigned left_size = edge.first.size();
        outfile.write(reinterpret_cast<char*>(&left_size), sizeof(left_size));
        outfile.write(edge.first.c_str(), left_size);
        unsigned right_size = edge.second.size();
        outfile.write(reinterpret_cast<char*>(&right_size), sizeof(right_size));
        outfile.write(edge.second.c_str(), right_size);
    }

}

graph graph::load(std::string filename)
{
    filename = fixFilename(filename);
    std::ifstream infile(filename, std::ios_base::binary);
    if(!infile)
    {
        throw CanNotOpenFile();
    }
    unsigned num_of_veteces;
    infile.read(reinterpret_cast<char*>(&num_of_veteces), sizeof(num_of_veteces));
    unsigned num_of_edges;
    infile.read(reinterpret_cast<char*>(&num_of_edges), sizeof(num_of_edges));
    graph res;
    for (int i = 0; i<num_of_veteces; i++)
    {
        std::string new_vertex = getVertexFromFile(filename);
        if (!isLegalVerticName(new_vertex))
        {
            std::cout << new_vertex << std:: endl;
            throw IllegalVerticNameInFile();
        }
        if (res.vertices.count(new_vertex))
        {
            throw TwoVertexSherAName();
        }
        res.vertices.insert(new_vertex);
    }
    for (int i=0; i < num_of_edges; i++)
    {
        std::pair<std::string,std::string> new_edge = getEdgeFromFile(filename);
        if (res.vertices.count(new_edge.first) == 0)
        {
            throw IllegalEdgeName();
        }
        if (res.vertices.count(new_edge.second) == 0)
        {
            throw IllegalEdgeName();
        }
        if (res.edges.count(new_edge))
        {
            throw TwoEdgesWithSameName();
        }
        res.edges.insert(new_edge);
    }
    return res;
}

std::string getVertexFromFile(const std::string filename)
{
    std::ifstream infile(filename, std::ios_base::binary);
    if(!infile)
    {
        throw CanNotOpenFile();
    }
    unsigned size_of_vertex;
    infile.read(reinterpret_cast<char*>(&size_of_vertex), sizeof(size_of_vertex));
    if (infile.fail())
    {
        throw CanNotOpenFile();
    }
    char* vertex = new char [size_of_vertex +1];
    infile.read(vertex, size_of_vertex);
    if (infile.fail())
    {
        delete[] (vertex);
        throw CanNotOpenFile();
    }
    vertex[size_of_vertex] = '\0';
    std::string new_vertex = vertex;
    delete[] (vertex);
    return new_vertex;

}

std::pair<std::string,std::string> getEdgeFromFile(const std::string& filename)
{
    std::string vertex1 = getVertexFromFile(filename);
    std::string vertex2 = getVertexFromFile(filename);
    if (vertex1 == vertex2)
    {
        throw IllegalEdgeName();
    }
    std::pair<std::string,std::string> res = {vertex1,vertex2};
    return res;

}

std::string fixFilename(const std::string& filename)
{
    std::string res,temp;
    bool first_letter_apear;
    for (auto letter : filename)
    {
        if(letter != ' ')
        {
            first_letter_apear = true;
            temp += letter;
        }
        else
        {
            if (first_letter_apear)
            {
                temp += ' ';
            }
        } 
    }
    reverse(temp.begin(),temp.end());
    for (auto letter : temp)
    {
        if(letter != ' ')
        {
            first_letter_apear = true;
            res += letter;
        }
        else
        {
            if (first_letter_apear)
            {
                res += ' ';
            }
        } 
    }
    reverse(res.begin(),res.end());
    return res;
}