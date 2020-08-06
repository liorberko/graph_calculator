#include "Graph.h"


int main ()
{
    std::string g1 = "{nuihiu, aiub, ciubi,  who  | <nuihiu,  aiub> , <ciubi,aiub> }";
   // std::cout << g1 << std::endl;
    graph g2(g1);

    std::cout << g2 << std::endl ;

    


    return 0 ; 
}