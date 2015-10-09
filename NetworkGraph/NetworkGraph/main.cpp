//
//  main.cpp
//  NetworkGraph
//
//  Created by Alexander Malyshev on 25.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "NetworkGraph.h"
#include "CMatrixGraph.h"
#include "CMatrixOrientedGraph.h"
#include "MPMNetworkGraph.h"
#include "NetworkAlgorithmManager.h"

#include <functional>

#define DEBUG

template <class EdgeInfo>
using Edge = typename IGraph<EdgeInfo>:: Edge;

template <class EdgeInfo>
void BFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const Edge<EdgeInfo> edge)> completionBlock) {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(100000);
    vertexQueue.push(start);
    
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = graph.getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                vertexQueue.push(it->to);
                completionBlock(*it);
            }
        }
    }
    
}

int main(int argc, const char * argv[]) {
    MPMNetworkGraph g;
    int n = 0;
    std::cin>>n;
    for (int i = 0; i < n; ++i) {
        int to, from, capacity;
        std::cin>> from;
        std::cin>> to;
        std::cin>> capacity;
        MPMNetworkEdgeInfo edgeInfo = MPMNetworkEdgeInfo(capacity);
        g.addEdge(from, to, edgeInfo);
    }
    
    NetworkAlgorithmManager manager = NetworkAlgorithmManager(g);
    
    auto printEdge = [](MPMNetworkEdge edge) {
        std::cout<<edge.from <<"->"<<edge.to<<" ("<<edge.info.flow<<"/"<<edge.info.capacity<<")"<<std::endl;
    };
    
    BFS(g, 0, printEdge);

    std::cout<<"-------"<<std::endl;
    
    auto maxFlow = manager.maxFlowWithMPMBlocking(0, n - 1);
    
    std::cout<<maxFlow<<std::endl;
    
    return 0;
}




