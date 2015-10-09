//
//  NetworkFlowManager.h
//  NetworkGraph
//
//  Created by Alexander Malyshev on 29.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef NetworkAlgorithmManager_h
#define NetworkAlgorithmManager_h

#include <stdio.h>
#include "MPMNetworkGraph.h"
#include "CMatrixGraph.h"

#define NOT_VISITED INT_MAX
#define VISITED (INT_MAX - 1)
template <class EdgeInfo>
using Edge = typename IGraph<EdgeInfo>:: Edge;
using VertexType = IGraph<>::VertexType;

class NetworkAlgorithmManager {
public:

    NetworkAlgorithmManager(MPMNetworkGraph &network): network(network) {
        distance = std::vector<VertexType>(network.vertexMax() + 1, NOT_VISITED);
        potential = std::vector<VertexType>(network.vertexMax() + 1);
        incPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
        outPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    };
    
//    void findBlockingFlowInLayeredNetwork(MPMNetworkGraph &network);
    MPMNetworkGraph network;
    MPMNetworkGraph residualNetwork;
    
    MPMNetworkGraph getLayeredGraph(MPMNetworkGraph &network, VertexType source, VertexType sink);
    FlowType maxFlowWithMPMBlocking(const VertexType source, const VertexType sink);
private:
    
    FlowType maxFlow;
    
    std::vector<VertexType> distance;
    std::vector<VertexType> potential;
    std::vector<VertexType> incPotential;
    std::vector<VertexType> outPotential;
    
    void updatePotentials(MPMNetworkGraph &layeredNetwork, std::queue<VertexType> &updatingQueue);
    void findBlockingFlowInLayeredNetwork(MPMNetworkGraph &layeredNetwork, MPMNetworkGraph &originalNetwork, const VertexType source, const VertexType sink);
    
};
FlowType NetworkAlgorithmManager::maxFlowWithMPMBlocking(const VertexType source, const VertexType sink) {
    potential = std::vector<VertexType>(network.vertexMax() + 1);
    
    while (true) {
        auto layeredNetwork = getLayeredGraph(network, source, sink);
        
        if (distance[sink] == NOT_VISITED) {
            return maxFlow;
        }
        findBlockingFlowInLayeredNetwork(layeredNetwork, network, source, sink);
    }
    
    return maxFlow;
}
void NetworkAlgorithmManager:: updatePotentials(MPMNetworkGraph &layeredNetwork, std::queue<VertexType> &updatingQueue) {
    while (!updatingQueue.empty()) {
        auto currentVertex = updatingQueue.front();
        updatingQueue.pop();
        if (!(potential[currentVertex] == VISITED)) {
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            assert(potential[currentVertex] >= 0);
            if (potential[currentVertex] == 0) {
                potential[currentVertex] = VISITED;
                auto nextEdges = layeredNetwork.getNextEdges(currentVertex);
                auto prevEdges = layeredNetwork.getPrevEdges(currentVertex);
                for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                    layeredNetwork.removeEdge(it->from, it->to);
                    updatingQueue.push(it->to);
                }
                for (auto it = prevEdges.begin(); it != prevEdges.end(); ++it) {
                    layeredNetwork.removeEdge(it->from, it->to);
                    updatingQueue.push(it->from);
                }
            }
        }
    }
}

void NetworkAlgorithmManager:: findBlockingFlowInLayeredNetwork(MPMNetworkGraph &layeredNetwork, MPMNetworkGraph &residualNetwork, const VertexType source, const VertexType sink) {
    while (true) {
        auto minPotentialVertexIt = std::min_element(potential.begin(), potential.end());
        auto minPotential = potential[*minPotentialVertexIt];
        if (minPotential == VISITED) {
            return;
        }
        
        std::vector<VertexType> extraFlow(layeredNetwork.vertexMax() + 1, 0);
        std::queue<VertexType> vertexQueue;
        std::queue<VertexType> updatingQueue;
        vertexQueue.push(*minPotentialVertexIt);
        extraFlow[*minPotentialVertexIt] = potential[*minPotentialVertexIt];
        
        //forward pushing
        auto pushFlow = [&vertexQueue, &extraFlow, &minPotentialVertexIt, &layeredNetwork, &residualNetwork, &updatingQueue, &source, &sink, this](bool isFrontPushing) {
            std::vector<char> used(layeredNetwork.vertexMax() + 1, 0);
            while (!vertexQueue.empty()) {
                auto currentVertex = vertexQueue.front();
                vertexQueue.pop();
                if (!used[currentVertex]) {
                    used[currentVertex] = 1;
                    std::vector<MPMNetworkEdge> nextEdges;
                    if (isFrontPushing) {
                        nextEdges = layeredNetwork.getNextEdges(currentVertex);
                    } else {
                        nextEdges = layeredNetwork.getPrevEdges(currentVertex);
                    }
                    updatingQueue.push(currentVertex);
                    for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                        auto augmentingCapacity = it->info.capacity;
                        if (augmentingCapacity <= extraFlow[it->from]) {
                            residualNetwork.removeEdge(it->from, it->to);
                            layeredNetwork.removeEdge(it->from, it->to);
                            extraFlow[it->to] += augmentingCapacity;
                            extraFlow[it->from] -= augmentingCapacity;
                            outPotential[it->from] -= augmentingCapacity;
                            incPotential[it->to] -= augmentingCapacity;
                        } else {
                            auto newInfo = it->info.infoWithNewCapacity(it->info.capacity - extraFlow[it->from]);
                            residualNetwork.changeEdge(it->from, it->to, newInfo);
                            layeredNetwork.changeEdge(it->from, it->to, newInfo);
                            extraFlow[it->to] += extraFlow[it->from];
                            extraFlow[it->from] = 0;
                            outPotential[it->from] -= extraFlow[it->from];
                            incPotential[it->to] -= extraFlow[it->from];
                            break;
                        }
                        vertexQueue.push(it->to);
                    }
                }
            }
        };
        
        pushFlow(1);
        extraFlow[*minPotentialVertexIt] = minPotential;
        pushFlow(0);
        
        updatePotentials(layeredNetwork, updatingQueue);
    }
}

MPMNetworkGraph NetworkAlgorithmManager:: getLayeredGraph(MPMNetworkGraph &graph, VertexType source, VertexType sink) {
    distance = std::vector<VertexType>(network.vertexMax() + 1, NOT_VISITED);
    incPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    outPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    MPMNetworkGraph layeredGraph;
    
    std::vector<VertexType> used(graph.vertexMax());
    std::queue<VertexType>  vertexQueue;
    
    incPotential[source] = NOT_VISITED;
    outPotential[sink] = NOT_VISITED;
    
    vertexQueue.push(source);
    distance[source] = 0;
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = graph.getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                if (distance[it->to] == NOT_VISITED) {
                    distance[it->to] = distance[currentVertex] + 1;
                }
                
                if (distance[it->to] == distance[currentVertex] + 1) {
                    if (it->info.capacity != it->info.flow) {
                        layeredGraph.addEdge(it->from, it->to, it->info);
                    }
                    incPotential[it->to] += it->info.capacity;
                    outPotential[it->from] += it->info.capacity;
                }
                vertexQueue.push(it->to);
            }
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            
#ifdef DEBUG
            std::cout<<"Potential for "<<currentVertex <<" is "<<potential[currentVertex] <<std::endl;
#endif
        }
    }
    
    return layeredGraph;
}






#endif /* NetworkFlowManager_hpp */
