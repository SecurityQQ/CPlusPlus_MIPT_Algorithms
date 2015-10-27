//
//  LayeredNetworkGraph.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include "LayeredNetworkGraph.hpp"

bool LayeredNetworkGraph:: sinkReachable() {
    return distance[sink] != NOT_REACHED;
}

void LayeredNetworkGraph:: init() {
    distance = std::vector<VertexType>(residualNetwork->vertexCount(), NOT_REACHED);
    incPotential = std::vector<CapacityType>(residualNetwork->vertexCount(), 0);
    outPotential = std::vector<CapacityType>(residualNetwork->vertexCount(), 0);
    potential = std::vector<CapacityType>(residualNetwork->vertexCount(), MAX_POTENTIAL);
    extraFlow = std::vector<FlowType>(residualNetwork->vertexCount(), 0);
    std::vector<VertexType> used(residualNetwork->vertexCount());
    std::queue<VertexType>  vertexQueue;
    
    incPotential[source] = MAX_POTENTIAL;
    outPotential[sink] = MAX_POTENTIAL;
    
    vertexQueue.push(source);
    distance[source] = 0;
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            residualNetwork->performCompletionBlockOnNextVertexes(currentVertex, [this, &vertexQueue](const VertexType from, const VertexType to) {
                if (distance[to] == NOT_REACHED) {
                    distance[to] = distance[from] + 1;
                }
                if (distance[to] == distance[from] + 1) {
                    this->addEdge(from, to);
                    incPotential[to] += residualNetwork->residualCapacity(from, to);
                    outPotential[from] += residualNetwork->residualCapacity(from, to);
                }
                vertexQueue.push(to);
            });
            
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            
#ifdef DEBUG
            std::cout<<"Potential for "<<currentVertex <<" is "<<potential[currentVertex] <<std::endl;
#endif
        }
    }
}

void LayeredNetworkGraph:: getBlockingFlow() {
    while (potential[source] != MAX_POTENTIAL && potential[sink] != MAX_POTENTIAL) {
        std::set<VertexType> vertexesToDelete;
        pushFront(vertexesToDelete);
        pushBackward(vertexesToDelete);
        updatePotentials(vertexesToDelete);
    }
}

void LayeredNetworkGraph:: pushFront(std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(1, vertexesToUpdate);
}

void LayeredNetworkGraph:: pushBackward(std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(0, vertexesToUpdate);
}

void LayeredNetworkGraph:: pushWithDirection(bool isFront, std::set<VertexType> &vertexesToUpdate) {
    
    std::queue<VertexType> pushingQueue;
    std::vector<char> used(vertexCount(), 0);
    
    auto getIndexOfMinElement = [](const std::vector<CapacityType>& v) -> VertexType {
        CapacityType min = v[0];
        VertexType minIndex = 0;
        for (VertexType i = 1; i < v.size(); ++i) {
            if (min > v[i]) {
                min = v[i];
                minIndex = i;
            }
        }
        return minIndex;
    };
    
    VertexType vertexWithMinPotential = getIndexOfMinElement(potential);
    extraFlow[vertexWithMinPotential] = potential[vertexWithMinPotential];
    pushingQueue.push(vertexWithMinPotential);
    
    while (!pushingQueue.empty()) {
        auto currentVertex = pushingQueue.front();
        pushingQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextVertexes = (isFront ? getNextVertexes(currentVertex) : getPrevVertexes(currentVertex));
            for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
                auto to = *it;
                FlowType pushingFlow;
                auto residualCapacity = residualNetwork->residualCapacity(currentVertex, to);
                if (residualCapacity <= extraFlow[currentVertex]) {
                    pushingFlow = residualCapacity;
                } else {
                    pushingFlow = extraFlow[currentVertex];
                }
                residualNetwork->pushFlow(pushingFlow, currentVertex, to);
                outPotential[currentVertex] -= pushingFlow;
                incPotential[to] -= pushingFlow;
                extraFlow[to] += pushingFlow;
                extraFlow[currentVertex] -= pushingFlow;
                pushingQueue.push(to);
                if (extraFlow[currentVertex] == 0) {
                    break;
                }
            }
            vertexesToUpdate.insert(currentVertex);
        }
    }
}

void LayeredNetworkGraph:: updatePotentials(std::set<VertexType> &vertexesToUpdate) {
    auto currentVertex = *vertexesToUpdate.begin();
    vertexesToUpdate.erase(currentVertex);
    potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
    if (potential[currentVertex] <= 0) {
        potential[currentVertex] = MAX_POTENTIAL;
        auto nextVertexes = getNextVertexes(currentVertex);
        auto prevVertexes = getPrevVertexes(currentVertex);
        for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
            removeEdge(currentVertex, *it);
            vertexesToUpdate.insert(*it);
            incPotential[*it] -= residualNetwork->residualCapacity(currentVertex, *it);
        }
        for (auto it = prevVertexes.begin(); it != prevVertexes.end(); ++it) {
            removeEdge(*it, currentVertex);
            vertexesToUpdate.insert(*it);
            incPotential[*it] -= residualNetwork->residualCapacity(*it, currentVertex);
        }
    }
}

void LayeredNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<residualNetwork->flow(from, to)<<"/"<<residualNetwork->capacity(from, to) <<")"<<std::endl;
    });
}
