//
//  main.cpp
//  Dijkstra Algo
//
//  Created by Александр Малышев on 15.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CMatrixGraph.h"
#include <array>
#include <queue>
#include <algorithm>

typedef unsigned long long ull;

struct VertexWithPriority {
    ull vertex;
    ull priority;
    VertexWithPriority(ull vertex, ull priority) : vertex(vertex), priority(priority) {}
};

struct compVertexesWithPriority {
    bool operator() (const VertexWithPriority i, const VertexWithPriority j) const{
        return i.priority > j.priority;
    }
};

ull findMinRoad(CMatrixGraph<ull> &graph, ull from, ull to) {
    char checked[graph.vertexMax() + 1];
    std::vector<ull> ans(graph.vertexMax() + 1, ULLONG_MAX);
    for (ull i = 0; i <= graph.vertexMax(); ++i) {
        checked[i] = 0;
    }
    ans[from] = 0;
    

    std::priority_queue<VertexWithPriority, std::vector<VertexWithPriority>, compVertexesWithPriority> queue;
    queue.push(VertexWithPriority(from, ans[from]));

    
    while (!queue.empty()) {
        ull i = queue.top().vertex;
        queue.pop();
        
        if (!checked[i]) {
            checked[i] = 1;
            CMatrixGraph<ull>:: VertexCollection next = graph.getNextVertexes(i);
            for (auto j = next.begin(); j != next.end(); ++j) {
                if (ans[j->vertex] > ans[i] + j->info) {
                    ans[j->vertex] =  ans[i] + j->info;
                    if (ans[to] > ans[j->vertex]) {
                        queue.push(VertexWithPriority(j->vertex, ans[j->vertex]));
                    }
                }
            }
        }
    }
    
    return ans[to];
}

void debug() {
    CMatrixGraph<ull> graph;
    ull vertNum = 11;
    ull from, to, weight;
    for (ull i = 0; i < vertNum; ++i) {
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }
    std::cout<<findMinRoad(graph, 0, 7);
}

int main(int argc, const char * argv[]) {
    ull edges, vertexes;
    CMatrixGraph<ull> graph;
    std::cin>>vertexes >>edges;
    for (ull i = 0; i < edges; ++i) {
        ull from, to, weight;
        std::cin>>from >> to >> weight;
        graph.addEdge(from, to, weight);
        graph.addEdge(to, from, weight);
    }
    ull cityFrom, cityTo;
    std::cin>>cityFrom >> cityTo;
    std::cout<<findMinRoad(graph, cityFrom, cityTo) <<std::endl;
    
    return 0;
}
