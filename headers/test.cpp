#include "Graph.h"
#include "GraphCalculator.h"
#include <algorithm>
#include "graphCalculatorParser.h"

int main ()
{
    std::string g1 = "{a , b,   c| <a,b> , < b,   a> }";
    

   // std::string g1 = "g2+{a , b,   c| <a,b> , < b,   a> }";
    std::string g2 = "{a1 ,1c , 2v |  <  2v  ,1c>}";
   // std::cout << g1 << std::endl;
    graph G1(g1);
    graph G2(g2);
    // G1 = G1+ G2;
    // std::cout << G1 << std::endl ;
    graphCalculator berko;
    berko.addGraph(G1 , "G1");
    berko.addGraph(G2, "G2");
    
    // berko.print("G1");
    // berko.who();
    // berko.remove("G1");
    // berko.who();
    // berko.reset();
    // berko.print("G1");

    graph G3 = G2*G1 +G2;
    std::cout << G3 << std::endl << std::endl;
    berko.addGraph(G3, "G3");

    graphCalculatorParser memory1 ("a = G2*G1 +G2",berko);
    graph tal = memory1.calculatMultiPhrase("G2*G1 +G2");
    std::cout << tal;

    return 0 ; 
}