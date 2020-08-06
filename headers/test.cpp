#include "Graph.h"


int main ()
{
    std::string g1 = "{nuihiu , aiub,   ciubi| <nuihiu,aiub> , < ciubi,   aiub> }";
    std::string g2 = "{a1 ,1c , 2 v , nuihiu   ,    aiub|  <  nuihiu  ,aiub>}";
   // std::cout << g1 << std::endl;
    graph G1(g1);
    graph G2(g2);
    G1 = G1+ G2;
    std::cout << G1 << std::endl ;

    


    return 0 ; 
}