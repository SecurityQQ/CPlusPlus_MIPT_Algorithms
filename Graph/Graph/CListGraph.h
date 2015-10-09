//
//  CListGraph.h
//  Graph
//
//  Created by Александр Малышев on 06.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __Graph__CListGraph__
#define __Graph__CListGraph__

#include <stdio.h>
#include <forward_list>
#include <unordered_set>
#include "IGraph.h"


template <class EdgeInfo = DefaultVertexWeightType>
class CListGraph: public IGraph<EdgeInfo> {
    
public:
    
    
    typedef typename IGraph<EdgeInfo>::VertexCollection VertexCollection;
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::VertexCollectionUnit VertexCollectionUnit;
    
    CListGraph();
    ~CListGraph();
    
    
    void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    void removeEdge(VertexType from, VertexType to);
    VertexType vertexCount() const;
    VertexCollection getNextVertexes(VertexType vertex) const;
    VertexCollection getPrevVertexes(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;

    void convertToGraph(IGraph<EdgeInfo> &newGraph) const;

    
private:
    typedef std::forward_list<VertexCollectionUnit> VertexBufUnit;
    
    std::unordered_set<VertexType> _vertexes;
    std::vector<VertexBufUnit> buf;
    VertexType _vertexCount;
    

};

template <class EdgeInfo>
CListGraph<EdgeInfo>:: CListGraph() {
    
}

template <class EdgeInfo>
CListGraph<EdgeInfo>:: ~CListGraph() {
    
}

template <class EdgeInfo>
void CListGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    if (from >= buf.size() || to >= buf.size()) {
        VertexType newSize = std::max(from, to) + 1;
        VertexType oldBufSize = buf.size();
        buf.insert(buf.end(), newSize - oldBufSize, VertexBufUnit());
    }
    _vertexes.insert(to);
    _vertexes.insert(from);
    buf[from].push_front(VertexCollectionUnit(to, weight));
}

template <class EdgeInfo>
void CListGraph<EdgeInfo>:: removeEdge(VertexType from, VertexType to) {
#warning implement this
//
//    for (auto it = buf[from].begin; it != buf[from].end; ++it) {
//        if (it->vertex == to) {
//            buf[from].erase(*it);
//            break;
//        }
//    }
}

template <class EdgeInfo>
typename CListGraph<EdgeInfo>::VertexCollection CListGraph<EdgeInfo>:: getNextVertexes(VertexType vertex) const {
    return VertexCollection(buf[vertex].begin(), buf[vertex].end());
}

template <class EdgeInfo>
typename CListGraph<EdgeInfo>::VertexCollection CListGraph<EdgeInfo>:: getPrevVertexes(VertexType vertex) const {
    VertexCollection prevVertexes;
    
    for (auto i = _vertexes.begin(); i != _vertexes.end(); ++i) {
        if (*i != vertex) {
            for (auto j = buf[*i].begin(); j != buf[*i].end(); ++j) {
                if (j->vertex == vertex) {
                    prevVertexes.push_back(VertexCollectionUnit(*i, j->info));
                }
            }
        }
    }
    
    return prevVertexes;
}

template <class EdgeInfo>
typename CListGraph<EdgeInfo>::VertexType CListGraph<EdgeInfo>:: vertexCount() const {
    return _vertexes.size();
}

template <class EdgeInfo>
void CListGraph<EdgeInfo>:: convertToGraph(IGraph<EdgeInfo> &newGraph) const{
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (auto j = buf[i].begin(); j != buf[i].end(); ++j) {
            newGraph.addEdge(i, j->vertex, j->info);
        }
    }
}

template <class EdgeInfo>
std::vector<typename CListGraph<EdgeInfo>::VertexType> CListGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

#endif /* defined(__Graph__CListGraph__) */
