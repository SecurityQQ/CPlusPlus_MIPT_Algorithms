//
//  GraphSearchManager.h
//  NetworkGraph
//
//  Created by Alexander Malyshev on 29.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef GraphSearchManager_h
#define GraphSearchManager_h

#include <stdio.h>
#include "IGraph.h"


using VertexType = IGraph<>::VertexType;

template <class EdgeInfo>
using Edge = typename IGraph<EdgeInfo>:: Edge;

class GraphAlgorithmManager {
public:
    
    static GraphAlgorithmManager& defaultManager() {
        static GraphAlgorithmManager instance;
        return instance;
    }
    
//    template <class EdgeInfo>
//    virtual void BFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const VertexType vertex)> completionBlock) const;
//    template <class EdgeInfo>
//    virtual void DFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const VertexType vertex)> completionBlock) const;

    

//    template <class EdgeInfo>
//    virtual void DFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const Edge<EdgeInfo> edge)> completionBlock) const;
    
    template <class EdgeInfo>
    void BFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const Edge<EdgeInfo> edge)> completionBlock) const;
    
    ~GraphAlgorithmManager() {};
    
    
private:
    GraphAlgorithmManager() { };
};

//
//template <class EdgeInfo>
//void GraphAlgorithmManager:: BFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const VertexType vertex)> completionBlock) const {
//    std::queue<VertexType> vertexQueue;
//    std::set<VertexType> used;
//    vertexQueue.push(start);
//    
//    while (!vertexQueue.empty()) {
//        VertexType currentVertex = vertexQueue.front();
//        vertexQueue.pop();
//        if (used.find(currentVertex) == used.end()) { //current vertex is not used
//            used.insert(currentVertex);
//            auto nextEdges = graph.getNextEdges(currentVertex);
//            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
//                vertexQueue.push(it->vertex);
//            }
//            completionBlock(currentVertex);
//        }
//    }
//}
//
//template <class EdgeInfo>
//void GraphAlgorithmManager:: DFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const VertexType vertex)> completionBlock) const {
//    std::stack<VertexType> vertexStack;
//    std::set<VertexType> used;
//    vertexStack.push(start);
//    
//    while (!vertexStack.empty()) {
//        VertexType currentVertex = vertexStack.top();
//        vertexStack.pop();
//        if (used.find(currentVertex) == used.end()) { //current vertex is not used
//            used.insert(currentVertex);
//            auto nextEdges = graph.getNextEdges(currentVertex);
//            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
//                vertexStack.push(it->to);
//            }
//            vertexStack.push(currentVertex);
//            completionBlock(currentVertex);
//        }
//    }
//}

template <class EdgeInfo>
void GraphAlgorithmManager:: BFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const Edge<EdgeInfo> edge)> completionBlock) const {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(graph.vertexMax());
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
//
//template <class EdgeInfo>
//void GraphAlgorithmManager:: DFS(IGraph<EdgeInfo>& graph, const VertexType start, const std::function<void(const Edge<EdgeInfo> edge)> completionBlock) const {
//    std::stack<VertexType> vertexStack;
//    std::set<VertexType> used;
//    vertexStack.push(start);
//    
//    while (!vertexStack.empty()) {
//        VertexType currentVertex = vertexStack.top();
//        vertexStack.pop();
//        if (used.find(currentVertex) == used.end()) { //current vertex is not used
//            used.insert(currentVertex);
//            auto nextEdges = graph.getNextEdges(currentVertex);
//            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
//                vertexStack.push(it->to);
//                if (used.find(it->to) != used.end()) {
//                    completionBlock(*it);
//                }
//            }
//            vertexStack.push(currentVertex);
//        }
//    }
//}

#endif /* GraphSearchManager_h */
