//
//  CMatrixGraph.h
//  Graph
//
//  Created by Александр Малышев on 04.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Graph_CMatrixGraph_h
#define Graph_CMatrixGraph_h

#define NO_VERTEX NULL

#include "IGraph.h"
#include <unordered_set>



template <class EdgeInfo = DefaultVertexWeightType>
class CMatrixGraph: public IGraph<EdgeInfo> {
    
public:
    
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::Edge Edge;
    typedef typename IGraph<EdgeInfo>::EdgesCollection EdgesCollection;
    
    CMatrixGraph();
    ~CMatrixGraph();
    
    
    virtual void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    virtual void removeEdge(VertexType from, VertexType to);
    virtual void changeEdge(VertexType from, VertexType to, EdgeInfo info);
    virtual EdgeInfo getEdgeInfo(VertexType from, VertexType to);
    
    VertexType vertexCount() const;
    VertexType vertexMax() const;
    EdgesCollection getNextEdges(VertexType vertex) const;
    EdgesCollection getPrevEdges(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
    void convertToGraph(IGraph<EdgeInfo> &newGraph) const;
    
private:
    VertexType _maxVertex;
    std::vector<std::vector<EdgeInfo *>> buf;
    std::unordered_set<VertexType> _vertexes;
};


template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: CMatrixGraph() {
    _maxVertex = 0;
}

template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: ~CMatrixGraph() {
    
}
template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    
    if ( from >= buf.size() || to >= buf.size() ) {
        VertexType newSize = std::max(from, to) + 1;
        VertexType oldBufSize = buf.size();
        for (auto it = buf.begin(); it != buf.end(); ++it) {
            it->insert(it->end(), newSize - oldBufSize, NO_VERTEX);
        }
        buf.insert(buf.end(), newSize - oldBufSize, std::vector<EdgeInfo *>(newSize, NO_VERTEX));
    }
    
    buf[from][to] = new EdgeInfo(weight);
    _maxVertex = std::max(_maxVertex, std::max(from, to));
    _vertexes.insert(to);
    _vertexes.insert(from);
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: removeEdge(VertexType from, VertexType to) {
    delete buf[from][to];
    buf[from][to] = NO_VERTEX;
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: changeEdge(VertexType from, VertexType to, EdgeInfo info) {
    removeEdge(from, to);
    addEdge(from, to, info);
}

template <class EdgeInfo>
EdgeInfo CMatrixGraph<EdgeInfo>:: getEdgeInfo(VertexType from, VertexType to) {
    return *(buf[from][to]);
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>:: VertexType CMatrixGraph<EdgeInfo>::vertexCount() const {
    return _vertexes.size();
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::VertexType CMatrixGraph<EdgeInfo>::vertexMax() const {
    return _maxVertex;
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::EdgesCollection CMatrixGraph<EdgeInfo>:: getNextEdges(VertexType vertex) const{
    EdgesCollection nextVertexes;
    
    for (VertexType i = 0; i < buf[vertex].size(); ++i) {
        if (buf[vertex][i] != NO_VERTEX && i != vertex) {
            nextVertexes.push_back(Edge(vertex, i, *(buf[vertex][i])));
        }
    }
    
    return nextVertexes;
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::EdgesCollection CMatrixGraph<EdgeInfo>:: getPrevEdges(VertexType vertex) const {
    EdgesCollection prevVertexes;
    
    
    for (auto i = _vertexes.begin(); i != _vertexes.end(); ++i) {
        if (buf[*i][vertex] != NO_VERTEX && *i != vertex) {
            prevVertexes.push_back(Edge(vertex, *i, *(buf[*i][vertex])));
        }
    }
    
    return prevVertexes;
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>::convertToGraph(IGraph<EdgeInfo> &newGraph) const {
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (VertexType j = 0; j < buf[i].size(); ++j) {
            if (buf[i][j] != NO_VERTEX) {
                newGraph.addEdge(i, j, *(buf[i][j]));
            }
        }
    }
}

template <class EdgeInfo>
std::vector<typename CMatrixGraph<EdgeInfo>:: VertexType> CMatrixGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

#endif

