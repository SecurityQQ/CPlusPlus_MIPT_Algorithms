//
//  ResidualNetworkGraph.h
//  Graphs-Govnokod
//
//  Created by Alexander Malyshev on 18.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef ResidualNetworkGraph_h
#define ResidualNetworkGraph_h

#include <forward_list>
#include <vector>
#include <queue>
#include <assert.h>

#define USED_VERTEX (INT_MAX - 1)

typedef long FlowType;
typedef long CapacityType;
typedef unsigned long long VertexType;
typedef long long VertexWeight;

class NetworkEdgeInfo {
    
public:
    NetworkEdgeInfo(CapacityType capacity): _flow(0), _capacity(capacity) {};
    NetworkEdgeInfo(FlowType flow, CapacityType capacity): _flow(flow), _capacity(capacity){};
    virtual FlowType flow() { return _flow; }
    virtual CapacityType capacity() { return _capacity; }
    virtual CapacityType residualCapacity() { return _capacity - _flow; }
    virtual void setFlow(FlowType flow) {
        assert(flow <= capacity());
        _flow = flow;
    }
    virtual void setCapacity(CapacityType capacity) {
        assert(flow() <= capacity);
        _capacity = capacity;
    }
protected:
    FlowType _flow;
    CapacityType _capacity;
};

class NetworkEdge {
public:
    VertexType from;
    VertexType to;
    VertexType id;
    NetworkEdgeInfo info;
    bool isReveresed;
    NetworkEdge(const VertexType from, const VertexType to, const VertexType id, const NetworkEdgeInfo info): from(from), to(to), id(id), info(info) { isReveresed = false; };
    
    void setFlow(FlowType flow) {
        info.setFlow(flow);
    }
    
    std::weak_ptr<NetworkEdge> reversedEdge;
};

class ResidualNetworkGraph {
    
public:
    
    typedef std::forward_list<std::shared_ptr<NetworkEdge>> EdgesCollection;
    
    ResidualNetworkGraph(const VertexType numberOfVertexes);
    virtual ~ResidualNetworkGraph() {}
    
    virtual void addEdge(const VertexType from, const VertexType to, const VertexType id, const VertexType flow, const VertexType capacity);
    virtual void removeEdge(const VertexType from, const VertexType to, const VertexType id);
    virtual void pushFlow(FlowType flow, std::shared_ptr<NetworkEdge> edge);
    
    virtual const VertexType vertexCount() const;
    virtual const VertexType vertexCapacity() const;
    virtual const EdgesCollection getNextEdges(const VertexType vertex) const;
    virtual const EdgesCollection getPrevEdges(const VertexType vertex) const;
    
    virtual void BFS(const VertexType start, const std::function<void(const std::shared_ptr<NetworkEdge> edge)> completionBlock);
    virtual void print(const VertexType start);
    
protected:
    
    ResidualNetworkGraph() {}
    std::vector<EdgesCollection> incomingEdgesToVertex;
    std::vector<EdgesCollection> outcomingEdgesFromVertex;
    VertexType _vertexCount;
};

ResidualNetworkGraph:: ResidualNetworkGraph(const VertexType numberOfVertexes) {
    incomingEdgesToVertex = std::move(std::vector<EdgesCollection>(numberOfVertexes));
    outcomingEdgesFromVertex = std::move(std::vector<EdgesCollection>(numberOfVertexes));
    _vertexCount = numberOfVertexes;
}

void ResidualNetworkGraph:: addEdge(const VertexType from, const VertexType to, const VertexType id, const VertexType flow, const VertexType capacity) {
    auto edge = std::make_shared<NetworkEdge>(from, to, id, NetworkEdgeInfo(flow, capacity));
    auto reversedEdge = std::make_shared<NetworkEdge>(edge->to, edge->from, edge->id, NetworkEdgeInfo(flow, capacity));
    reversedEdge->isReveresed = true;
    edge->reversedEdge = reversedEdge;
    reversedEdge->reversedEdge = edge;
    assert((edge->from < incomingEdgesToVertex.size()) && (edge->to < outcomingEdgesFromVertex.size()));
    incomingEdgesToVertex[edge->to].push_front(edge);
    incomingEdgesToVertex[reversedEdge->to].push_front(reversedEdge);
    outcomingEdgesFromVertex[edge->from].push_front(edge);
    outcomingEdgesFromVertex[reversedEdge->from].push_front(reversedEdge);
}

void ResidualNetworkGraph:: removeEdge(const VertexType from, const VertexType to, const VertexType id) {
    assert((from < incomingEdgesToVertex.size()) && (to < outcomingEdgesFromVertex.size()));
    incomingEdgesToVertex[to].remove_if([&id](std::shared_ptr<NetworkEdge> edge) {
        return edge->id == id;
    });
    outcomingEdgesFromVertex[from].remove_if([&id](std::shared_ptr<NetworkEdge> edge) {
        return edge->id == id;
    });
}

void ResidualNetworkGraph:: pushFlow(FlowType flow, std::shared_ptr<NetworkEdge> edge) {
    auto reversedEdge = std::shared_ptr<NetworkEdge>(edge->reversedEdge);
    assert(reversedEdge != nullptr);
    edge->setFlow(edge->info.flow() + flow);
    reversedEdge->setFlow(-edge->info.flow());
}

const VertexType ResidualNetworkGraph:: vertexCount() const {
    return _vertexCount;
}

const VertexType ResidualNetworkGraph:: vertexCapacity() const {
    return _vertexCount;
}

const typename ResidualNetworkGraph::EdgesCollection ResidualNetworkGraph:: getNextEdges(const VertexType vertex) const {
    return outcomingEdgesFromVertex[vertex];
}

const typename ResidualNetworkGraph::EdgesCollection ResidualNetworkGraph:: getPrevEdges(const VertexType vertex) const {
    return incomingEdgesToVertex[vertex];
}

void ResidualNetworkGraph:: BFS(const VertexType start, const std::function<void (const std::shared_ptr<NetworkEdge>)> completionBlock) {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(vertexCount());
    vertexQueue.push(start);
    
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                vertexQueue.push((*it)->to);
                completionBlock(*it);
            }
        }
    }
}

void ResidualNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](std::shared_ptr<NetworkEdge> edge) {
        std::cout<<edge->from<<"->"<<edge->to<<" ("<<edge->info.flow()<<"/"<<edge->info.capacity() <<")"<<std::endl;
    });
}

#endif /* ResidualNetworkGraph_h */
