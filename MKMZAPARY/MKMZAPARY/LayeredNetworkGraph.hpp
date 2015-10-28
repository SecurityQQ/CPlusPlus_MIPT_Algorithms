//
//  LayeredNetworkGraph.hpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef LayeredNetworkGraph_hpp
#define LayeredNetworkGraph_hpp

#include <numeric>
#include <set>
#include <queue>
#include <iostream>
#include "ResidualNetworkGraph.hpp"


class LayeredNetworkGraph: public Graph {
    
public:
    LayeredNetworkGraph(const VertexType numberOfVertexes) = delete;
    LayeredNetworkGraph(ResidualNetworkGraph *residualNetwork): Graph(residualNetwork->vertexCount()), residualNetwork(residualNetwork), source(residualNetwork->getSource()), sink(residualNetwork->getSink()) {
        init();
    }
    
    void getBlockingFlow();
    bool sinkReachable();
    
    void print(const VertexType start);
private:
    const VertexType NOT_REACHED = std::numeric_limits<VertexType>::max();
    const CapacityType MAX_POTENTIAL = std::numeric_limits<CapacityType>::max();
    
    void pushFront(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void pushBackward(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void pushWithDirection(bool isFront, const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void updatePotentials(std::set<VertexType> &vertexesToUpdate);
    
    
    VertexType source;
    VertexType sink;
    void init();
    ResidualNetworkGraph *residualNetwork;
    std::vector<VertexType> distance;
    std::vector<CapacityType> incPotential;
    std::vector<CapacityType> outPotential;
    std::vector<CapacityType> potential;
    std::vector<FlowType> extraFlow;
};



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
        auto flowToPush = potential[vertexWithMinPotential];
        pushFront(flowToPush, vertexWithMinPotential, vertexesToDelete);
        pushBackward(flowToPush, vertexWithMinPotential, vertexesToDelete);
        updatePotentials(vertexesToDelete);
    }
}

void LayeredNetworkGraph:: pushFront(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(1, flow, vertexWithMinPotential, vertexesToUpdate);
}

void LayeredNetworkGraph:: pushBackward(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(0, flow, vertexWithMinPotential,vertexesToUpdate);
}

void LayeredNetworkGraph:: pushWithDirection(bool isFront, const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {

    std::queue<VertexType> pushingQueue;
    std::vector<char> used(vertexCount(), 0);
    extraFlow[vertexWithMinPotential] = flow;
    pushingQueue.push(vertexWithMinPotential);

    while (!pushingQueue.empty()) {
        auto currentVertex = pushingQueue.front();
        pushingQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextVertexes = (isFront ? getNextVertexes(currentVertex) : getPrevVertexes(currentVertex));
            for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
#ifdef DEBUG
                std::cout<<"FROM: "<<currentVertex <<" TO: "<<*it <<std::endl;
#endif
                VertexType to, from;
                if (isFront) {
                    from = currentVertex;
                    to = *it;
                    if (!(distance[*it] == (distance[currentVertex] + 1))) {
                        continue;
                    }
                } else {
                    from = *it;
                    to = currentVertex;
                    if (!(distance[*it] + 1 == (distance[currentVertex]))) {
                        continue;
                    }
                }
                
                FlowType pushingFlow;
                auto residualCapacity = residualNetwork->residualCapacity(from, to);
                if (residualCapacity <= 0) {
                    continue;
                }
                if (residualCapacity <= extraFlow[currentVertex]) {
                    pushingFlow = residualCapacity;
                } else {
                    pushingFlow = extraFlow[currentVertex];
                }
                
                residualNetwork->pushFlow(pushingFlow, from, to);
                if (isFront) {
                    outPotential[currentVertex] -= pushingFlow;
                    incPotential[to] -= pushingFlow;
                    extraFlow[to] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(to);
                } else {
                    incPotential[currentVertex] -= pushingFlow;
                    outPotential[from] -= pushingFlow;
                    extraFlow[from] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(from);
                }
#ifdef DEBUG
#warning ПЛОХО ПУШИТ
                std::cout<<"Pushed "<<pushingFlow <<" from " << currentVertex <<"to "<<*it<<std::endl;
#endif

                if (extraFlow[currentVertex] == 0) {
                    break;
                }
            }
            vertexesToUpdate.insert(currentVertex);
        }
    }
}

void LayeredNetworkGraph:: updatePotentials(std::set<VertexType> &vertexesToUpdate) {
    while (!vertexesToUpdate.empty()) {
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
                outPotential[*it] -= residualNetwork->residualCapacity(*it, currentVertex);
            }
        }
    }
}

void LayeredNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<residualNetwork->flow(from, to)<<"/"<<residualNetwork->capacity(from, to) <<")"<<std::endl;
    });
}
#endif /* LayeredNetworkGraph_hpp */
