//
//  IGraph.h
//  Graph
//
//  Created by Александр Малышев on 04.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Graph_IGraph_h
#define Graph_IGraph_h

#include <vector>
#include <queue>
#include <stack>
#include <set>

typedef long long DefaultVertexWeightType;

template <class EdgeInfo = DefaultVertexWeightType>
class IGraph {
    
public:

    typedef unsigned long long VertexType;
    typedef long long VertexWeight;
    struct Edge {
        VertexType from;
        VertexType to;
        EdgeInfo info;
        Edge(VertexType from, VertexType to, EdgeInfo info): from(from), to(to), info(info) {}
    };
    
    typedef std::vector<Edge> EdgesCollection;
    
    virtual ~IGraph() {}
    
    virtual void addEdge(VertexType from, VertexType to, EdgeInfo info = 1) = 0;
    virtual void removeEdge(VertexType from, VertexType to) = 0;
    virtual void changeEdge(VertexType from, VertexType to, EdgeInfo info) = 0;
    virtual EdgeInfo getEdgeInfo(VertexType from, VertexType to) = 0;
    
    
    virtual VertexType vertexCount() const = 0;
    virtual EdgesCollection getNextEdges(VertexType vertex) const = 0;
    virtual EdgesCollection getPrevEdges(VertexType vertex) const = 0;
    virtual std::vector<VertexType> getAllVertexes() const = 0;
    
    virtual void BFS(const VertexType start, const std::function<void(const Edge edge)> completionBlock) const;
    
    
    virtual void convertToGraph(IGraph &newGraph) const = 0;
};


template <class EdgeInfo>
void IGraph<EdgeInfo>:: BFS(const VertexType start, const std::function<void(const Edge edge)> completionBlock) const {
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
                vertexQueue.push(it->to);
                completionBlock(*it);
            }
        }
    }
}




#endif
