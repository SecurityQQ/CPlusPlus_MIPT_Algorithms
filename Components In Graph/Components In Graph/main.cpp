//
//  main.cpp
//  Components In Graph
//
//  Created by Александр Малышев on 10.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <vector>
#include "CSetGraph.h"


void DFS(CSetGraph& graph, int vertex, std::vector<char> &visited, int& vertInComp) {
    visited[vertex] = 1;
    
    auto next = graph.getNextVertexes(vertex);
    for (auto i = next.begin(); i != next.end(); ++i) {
        if (!visited[i->vertex]) {
            ++vertInComp;
            DFS(graph, i->vertex, visited, vertInComp);
        }
    }
}


int main(int argc, const char * argv[]) {
    int vertexes, edges, to, from;
    CSetGraph graph;

    std::cin>>vertexes >>edges;
    for (int i = 0; i < edges; ++i) {
        std::cin>>from >> to;
        graph.addEdge(from, to);
        graph.addEdge(to, from);
    }
    
    
    int numOfComps = 0;
    int maxComp = -1;
    

    std::vector<char> visited(graph.vertexCount(), false);
    
    
    for (int i = 0; i < graph.vertexCount(); ++i) {
        int verInComp = 1;
        if (!visited[i]) {
            DFS(graph, i, visited, verInComp);
            ++numOfComps;
        }
        maxComp = std::max(maxComp, verInComp);
    }
    
    std::cout<<numOfComps << " " << maxComp <<std::endl;
    
    return 0;
}
