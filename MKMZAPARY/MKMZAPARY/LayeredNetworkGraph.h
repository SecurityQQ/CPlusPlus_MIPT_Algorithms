//
//  LayeredNetworkGraph.h
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef LayeredNetworkGraph_h
#define LayeredNetworkGraph_h
#include <numeric>
#include <set>
#include <queue>
//#include "ResidualNetworkGraph.hpp"

class LayeredNetworkGraph;

#include <forward_list>
#include <vector>
#include <queue>
#include "Graph.h"
#include "FlowKeeper.h"

class ResidualNetworkGraph: public Graph {
    
public:
    
    typedef std::forward_list<VertexType> VertexesCollection;
    
    ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink);
    
    virtual void addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity);
    virtual void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
    
    virtual void performCompletionBlockOnNextVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    virtual void performCompletionBlockOnPrevVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    
    virtual void print(const VertexType start);
    
    virtual const FlowType flow(const VertexType from, const VertexType to) { return flowKeeper->flow(from, to); }
    virtual const CapacityType capacity(const VertexType from, const VertexType to) { return flowKeeper->capacity(from, to); }
    virtual const CapacityType residualCapacity(const VertexType from, const VertexType to) { return flowKeeper->residualCapacity(from, to); }
    
    virtual const VertexType pushMaxFlow() volatile;
    
    virtual const VertexType getSource() { return source; }
    virtual const VertexType getSink() { return sink; }
    
protected:
    
    VertexType source;
    VertexType sink;
    
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
    std::shared_ptr<FlowKeeper> flowKeeper;
    
};


#include <iostream>

ResidualNetworkGraph:: ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): Graph(numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    flowKeeper = std::make_shared<FlowKeeper>(numberOfVertexes);
    _vertexCount = numberOfVertexes;
    this->source = source;
    this->sink = sink;
}

void ResidualNetworkGraph:: addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity) {
    flowKeeper->addCapacity(capacity, from, to);
    flowKeeper->pushFlow(flow, from, to);
    Graph::addEdge(from, to);
    Graph::addEdge(to, from);
}

void ResidualNetworkGraph:: pushFlow(FlowType flow, const VertexType from, const VertexType to) {
    flowKeeper->pushFlow(flow, from, to);
}


void ResidualNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<flowKeeper->flow(from, to)<<"/"<<flowKeeper->capacity(from, to) <<")"<<std::endl;
    });
}

void ResidualNetworkGraph:: performCompletionBlockOnNextVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    auto nextVertexes = getNextVertexes(vertex);
    for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
        if (flowKeeper->residualCapacity(vertex, *it) > 0) {
            completionBlock(vertex, *it);
        }
    }
}

void ResidualNetworkGraph:: performCompletionBlockOnPrevVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    auto nextVertexes = getPrevVertexes(vertex);
    for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
        if (flowKeeper->residualCapacity(vertex, *it) > 0) {
            completionBlock(vertex, *it);
        }
    }
}

const VertexType ResidualNetworkGraph:: pushMaxFlow() volatile {
    while (true) {
        auto _this = std::make_shared<ResidualNetworkGraph>(this);
        auto layeredGraph = LayeredNetworkGraph(_this);

//    #ifdef DEBUG
//            std::cout<<"layered graph created"<<std::endl;
//            print(source);
//    #endif
    
            if (!(layeredGraph->sinkReachable())) {
                break;
            }
    
            layeredGraph->getBlockingFlow();
//    #ifdef DEBUG
//            std::cout<<"Blocking path added"<<std::endl;
//            print(source);
//    #endif
    }
        
    FlowType maxFlow = 0;
    auto sourceNextVertexes = getNextVertexes(source);
    for (auto it = sourceNextVertexes.begin(); it != sourceNextVertexes.end(); ++it) {
        maxFlow += flow(source, *it);
    }
    return maxFlow;
}



class LayeredNetworkGraph: public Graph {
    
public:
    LayeredNetworkGraph(const VertexType numberOfVertexes) = delete;
    LayeredNetworkGraph(std::shared_ptr<ResidualNetworkGraph> residualNetwork): Graph(residualNetwork->vertexCount()), residualNetwork(residualNetwork), source(residualNetwork->getSource()), sink(residualNetwork->getSink()) {
        init();
    }
    
    void getBlockingFlow();
    bool sinkReachable();
    
    void print(const VertexType start);
private:
    const VertexType NOT_REACHED = std::numeric_limits<VertexType>::max();
    const CapacityType MAX_POTENTIAL = std::numeric_limits<CapacityType>::max();
    
    void pushFront(std::set<VertexType> &vertexesToUpdate);
    void pushBackward(std::set<VertexType> &vertexesToUpdate);
    void pushWithDirection(bool isFront, std::set<VertexType> &vertexesToUpdate);
    void updatePotentials(std::set<VertexType> &vertexesToUpdate);
    
    
    VertexType source;
    VertexType sink;
    void init();
    std::shared_ptr<ResidualNetworkGraph> residualNetwork;
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

#endif /* LayeredNetworkGraph_h */
