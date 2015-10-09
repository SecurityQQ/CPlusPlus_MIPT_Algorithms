//
//  main.cpp
//  Bellman Ford Algo
//
//  Created by Александр Малышев on 16.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CMatrixGraph.h"
#include <array>
#include <queue>
#include <algorithm>

#define INF LLONG_MAX

typedef unsigned long long ull;
typedef long long ll;

bool findNegativeCycles(CMatrixGraph<ll> &graph, ull start) {
    std::vector<ll> dist(graph.vertexMax() + 1, INF);
    dist[start] = 0;
    
    std::queue<ull> curLevel;
    curLevel.push(start);
    
    bool distChanged = true;
    ull iter = 0;
    
    while (iter < dist.size()) {
        ++iter;
        
        
        distChanged = false;
        std::queue<ull> nextLevel;
        while (!curLevel.empty()) {

            ull i = curLevel.front();
            curLevel.pop();
            
            auto next = graph.getNextVertexes(i);
            
            for (auto j = next.begin(); j != next.end(); ++j) {
                if (dist[j->vertex] != INF) {
                    if (dist[j->vertex] > dist[i] + j->info) {
                        dist[j->vertex] = dist[i] + j->info;
                        distChanged = true;
                        nextLevel.push(j->vertex);
                    }
                } else { //need to prevent  INF - 1, INF - 2 etc. cases
                    
                    dist[j->vertex] = dist[i] + j->info;
                    distChanged = true;
                    nextLevel.push(j->vertex);
                    
                }
            }
        }
        if (!distChanged) {
            break;
        }
        curLevel = nextLevel;
    }
    
    
    return distChanged;
}

int main(int argc, const char * argv[]) {
    ull edges, vertexes;
    CMatrixGraph<long long> graph;
    std::cin>>vertexes >>edges;
    for (ull i = 0; i < edges; ++i) {
        ull from, to;
        long long weight;
        std::cin>>from >> to >> weight;
        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }
    std::cout<<findNegativeCycles(graph, 0);
    
    return 0;
}