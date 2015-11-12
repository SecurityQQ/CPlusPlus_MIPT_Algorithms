//
//  ResidualNetworkGraph.hpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef ResidualNetworkGraph_hpp
#define ResidualNetworkGraph_hpp

#include <forward_list>
#include <vector>
#include <queue>
#include "Graph.h"
#include "FlowKeeper.h"

class ResidualNetworkGraph: public Graph {
    
public:
    //TODO: using::
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
    
    virtual const VertexType getSource() { return source; }
    virtual const VertexType getSink() { return sink; }
    
private:
    
    VertexType source;
    VertexType sink;
    
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
    std::shared_ptr<FlowKeeper> flowKeeper;
    
};


ResidualNetworkGraph:: ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): Graph(numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    flowKeeper = std::make_shared<FlowKeeper>(numberOfVertexes);
    _vertexCount = numberOfVertexes;
    this->source = source;
    this->sink = sink;
}

void ResidualNetworkGraph:: addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity) {
    if ((flowKeeper->capacity(from, to) == 0 && flowKeeper->capacity(to, from) == 0)) {
        Graph::addEdge(from, to);
        Graph::addEdge(to, from);
    }
    flowKeeper->addCapacity(capacity, from, to);
    flowKeeper->pushFlow(flow, from, to);
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


#endif /* ResidualNetworkGraph_hpp */
