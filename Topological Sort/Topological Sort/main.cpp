//
//  main.cpp
//  Topological Sort
//
//  Created by Александр Малышев on 09.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CMatrixGraph.h"
#include <stack>
typedef unsigned long long ull;

void DFS(CMatrixGraph graph, std::vector<ull> &topSorted, ull u, std::vector<char> &visited) {
    visited[u] = 1;
    VertexCollection nextVertexes = graph.getNextVertexes(u);
    for (ull i = 0; i < nextVertexes.size(); ++i) {
        if (!visited[nextVertexes[i].first]) {
            DFS(graph, topSorted, nextVertexes[i].first, visited);
        }
    }
    topSorted.push_back(u);
}

std::vector<ull> topologicalSort(CMatrixGraph graph) {
    CMatrixGraph g = graph;
    std::vector<ull> topSorted;

    
    std::vector<ull> vertexes = graph.getAllVertexes();
    
    ull tempVert = vertexes.size();
    for (ull i = 0; i < tempVert; ++i) {
        g.addEdge(tempVert, vertexes[i]);
    }
    std::vector<char> visited(g.vertexCount(), 0);
    
    DFS(g, topSorted, tempVert, visited);
    
    topSorted.pop_back();
    std::reverse(topSorted.begin(), topSorted.end());
    return topSorted;
}


int main(int argc, const char * argv[]) {
    CMatrixGraph g;
    ull vertexes, edges;
    ull from, to;
    ull n, foo;
    std::cin>>vertexes >> edges;
    for (ull i = 0; i < edges; ++i) {
        std::cin>> from >> to;
        g.addEdge(from, to);
    }
    std::vector<ull> sorted = topologicalSort(g);
    
    std::cin>>n;
    for (ull i = 0; i < n; ++i) {
        std::cin>>foo;
        for (ull i = 0; i < g.vertexCount(); ++i) {
            if (sorted[i] == foo) {
                std::cout<<i << " ";
            }
        }
    }

//    for (auto i = sorted.begin(); i != sorted.end(); ++i) {
//        std::cout << *i << std::endl;
//    }
    
    return 0;
}
