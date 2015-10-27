//
//  Graph.h
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 26.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <forward_list>
#include <vector>
#include <queue>
#include <assert.h>
#include "Constants.h"

class Graph {
public:
    typedef std::forward_list<VertexType> VertexesCollection;
    
    Graph(const VertexType numberOfVertexes);
    virtual ~Graph() {}
    
    virtual void addEdge(const VertexType from, const VertexType to);
    virtual void removeEdge(const VertexType from, const VertexType to);
    
    virtual const VertexType vertexCount() const;
    virtual const VertexesCollection getNextVertexes(const VertexType vertex) const;
    virtual const VertexesCollection getPrevVertexes(const VertexType vertex) const;
    
    virtual void BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock);
    
private:
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
};

Graph:: Graph(const VertexType numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    _vertexCount = numberOfVertexes;
}

void Graph:: addEdge(const VertexType from, const VertexType to) {
    incomingVertexes[to].push_front(from);
    outcomingVertexes[from].push_front(to);
}

void Graph:: removeEdge(const VertexType from, const VertexType to) {
    assert((from < incomingVertexes.size()) && (to < outcomingVertexes.size()));
    incomingVertexes[to].remove_if([&from](const VertexType vertex) {
        return from == vertex;
    });
    outcomingVertexes[from].remove_if([&to](const VertexType vertex) {
        return to == vertex;
    });
}

const VertexType Graph:: vertexCount() const {
    return _vertexCount;
}

const typename Graph::VertexesCollection Graph:: getNextVertexes(const VertexType vertex) const {
    return outcomingVertexes[vertex];
}

const typename Graph::VertexesCollection Graph:: getPrevVertexes(const VertexType vertex) const {
    return incomingVertexes[vertex];
}

void Graph:: BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock) {
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

#endif /* Graph_h */
