#include <iostream>
#include "Graph.h"

int main()
{
    Edge* edge = new Edge();
    vector<Edge> edges;
    
    int numberOfNodes = 0;
    edges.reserve(1000000);
    numberOfNodes = edge->LoadData(numberOfNodes,edges);

    Graph* graph = new Graph(edges, numberOfNodes);
    vector<int> BigComp;
    vector<int> BigCompHelp;

    graph->FindBigComponent(numberOfNodes, BigComp, BigCompHelp);
    int citatel = (int)graph->MoovDoTabulce(BigComp) - 1;

    printf("ID\tCentralita\tCentralita Result\n");
    for (int elem : BigComp) {
        vector<int> dist;
        dist = graph->BFS(elem, numberOfNodes);
        graph->Centralita(dist, elem, numberOfNodes, citatel);
    }
    return 0;
}