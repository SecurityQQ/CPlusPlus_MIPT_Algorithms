//
//  NetworkGraph.h
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef NetworkGraph_h
#define NetworkGraph_h


#include <forward_list>
#include <vector>
#include <queue>
#include <assert.h>
#include "FlowKeeper.h"

class NetworkGraph {
    
public:
    
    typedef std::forward_list<VertexType> VertexesCollection;
    
    NetworkGraph(const VertexType numberOfVertexes);
    virtual ~NetworkGraph() {}
    
    virtual void addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity);
    virtual void removeEdge(const VertexType from, const VertexType to);
    virtual void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
    
    virtual const VertexType vertexCount() const;
    virtual const VertexesCollection getNextVertexes(const VertexType vertex) const;
    virtual const VertexesCollection getPrevVertexes(const VertexType vertex) const;
    
    virtual void BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock);
    virtual void print(const VertexType start);
    
protected:
    
    NetworkGraph() {}
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
    std::shared_ptr<FlowKeeper> flowKeeper;
};

NetworkGraph:: NetworkGraph(const VertexType numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    flowKeeper = std::make_shared<FlowKeeper>(numberOfVertexes);
    _vertexCount = numberOfVertexes;
}

void NetworkGraph:: addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity) {
    flowKeeper->addCapacity(capacity, from, to);
    flowKeeper->pushFlow(flow, from, to);
    incomingVertexes[to].push_front(from);
    outcomingVertexes[from].push_front(to);
}

void NetworkGraph:: removeEdge(const VertexType from, const VertexType to) {
    assert((from < incomingVertexes.size()) && (to < outcomingVertexes.size()));
    incomingVertexes[to].remove_if([&from](const VertexType vertex) {
        return from == vertex;
    });
    outcomingVertexes[from].remove_if([&to](const VertexType vertex) {
        return to == vertex;
    });
}

void NetworkGraph:: pushFlow(FlowType flow, const VertexType from, const VertexType to) {
    flowKeeper->pushFlow(flow, from, to);
}

const VertexType NetworkGraph:: vertexCount() const {
    return _vertexCount;
}

const typename NetworkGraph::VertexesCollection NetworkGraph:: getNextVertexes(const VertexType vertex) const {
    return outcomingVertexes[vertex];
}

const typename NetworkGraph::VertexesCollection NetworkGraph:: getPrevVertexes(const VertexType vertex) const {
    return incomingVertexes[vertex];
}

void NetworkGraph:: BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(vertexCount());
    vertexQueue.push(start);
    
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = getNextVertexes(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                vertexQueue.push(*it);
                completionBlock(currentVertex, *it);
            }
        }
    }
}

void NetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<flowKeeper->flow(from, to)<<"/"<<flowKeeper->capacity(from, to) <<")"<<std::endl;
    });
}

#endif /* NetworkGraph_h */
