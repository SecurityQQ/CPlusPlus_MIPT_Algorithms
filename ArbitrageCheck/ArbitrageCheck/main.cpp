//
//  main.cpp
//  ArbitrageCheck
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

bool findArbitrageStartsWith(ull start, CMatrixGraph<float> &graph, std::vector<ull>& uncheckedVertexes) {
    std::vector<float> dist(graph.vertexMax() + 1, INF);
    dist[start] = 1;
    
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
                    if (dist[j->vertex] < dist[i] * j->info) {
                        dist[j->vertex] = dist[i] * j->info;
                        distChanged = true;
                        nextLevel.push(j->vertex);
                    }
                } else { //need to prevent  INF - 1, INF - 2 etc. cases
                    
                    dist[j->vertex] = dist[i] * j->info;
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
    
    uncheckedVertexes.erase(uncheckedVertexes.begin(), uncheckedVertexes.end());
    uncheckedVertexes.shrink_to_fit();
    for (ull i = 0; i < graph.vertexMax() + 1; ++i) {
        if (dist[i] == INF) {
            uncheckedVertexes.push_back(dist[i]);
        }
    }
    
    if (distChanged == true) {
        
    }
    
    return distChanged;
}

bool isArbitrageIn(CMatrixGraph<float> graph) {
    auto uncheckedVertexes = graph.getAllVertexes();
    
    while (uncheckedVertexes.size() > 0) {
        if (findArbitrageStartsWith(uncheckedVertexes[0], graph, uncheckedVertexes)) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ull currenciesNum;
    CMatrixGraph<float> graph;
    std::cin>>currenciesNum;
    for (ull i = 0; i < currenciesNum; ++i) {
        for (ull j = 0; j < currenciesNum; ++j) {
            float coef;
            if (i != j) {
                std::cin>>coef;
                if (coef != -1) {
                    graph.addEdge(i, j, coef);
                }
            }
        }
    }
    if (isArbitrageIn(graph)) {
        std::cout<<"Ok\n";
    } else {
        std::cout<<"No\n";
    }
    
    return 0;
}