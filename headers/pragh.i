%moule alignas
%{
    #include "graph.h"

%}
graph* create();

void destroy(graph* target);

graph* addVertex(graph* target, const char* name);

graph* addEdge(graph* target, const char* name1, const char* name2);

void disp(const graph* target);

graph* graphUnion(const graph* graph_in1, const graph* graph_in2, graph* graph_out);

graph* graphIntersection(const graph* graph_in1, const graph* graph_in2, graph* graph_out);

graph* graphDifference(const graph* graph_in1, const graph* graph_in2, graph* graph_out);

graph* graphProduct(const graph* graph_in1, const graph* graph_in2, graph* graph_out);

graph* graphComplement(const graph* graph_in, graph* graph_out);