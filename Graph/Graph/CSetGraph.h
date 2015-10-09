//
//  CSetGraph.h
//  Graph
//
//  Created by Александр Малышев on 06.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Graph_CSetGraph_h
#define Graph_CSetGraph_h

#include "IGraph.h"
#include <unordered_set>
#include <unordered_map>

template <class EdgeInfo = DefaultVertexWeightType>
class CSetGraph: public IGraph<EdgeInfo> {
    
public:
    
    typedef typename IGraph<EdgeInfo>::VertexCollection VertexCollection;
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::VertexCollectionUnit VertexCollectionUnit;
    
    CSetGraph();
    ~CSetGraph();
    
    void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    VertexType vertexCount() const;
    VertexCollection getNextVertexes(VertexType vertex) const;
    VertexCollection getPrevVertexes(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
    void convertToGraph(IGraph<EdgeInfo> &newGraph) const;
    
private:
    typedef std::unordered_map<VertexType, EdgeInfo> VertexBufUnit;
    std::vector<VertexBufUnit> buf;
    std::unordered_set<VertexType> _vertexes;
};



template <class EdgeInfo>
CSetGraph<EdgeInfo>:: CSetGraph() {
    
}

template <class EdgeInfo>
CSetGraph<EdgeInfo>:: ~CSetGraph() {
    
}

template <class EdgeInfo>
void CSetGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    if ( from >= buf.size() || to >= buf.size() ) {
        VertexType newSize = std::max(from, to) + 1;
        VertexType oldBufSize = buf.size();
        buf.insert(buf.end(), newSize - oldBufSize, VertexBufUnit());
    }
    buf[from].insert(std::make_pair(to, weight));
    _vertexes.insert(to);
    _vertexes.insert(from);
}

template <class EdgeInfo>
typename CSetGraph<EdgeInfo>::VertexType CSetGraph<EdgeInfo>:: vertexCount() const {
    return _vertexes.size();
}


template <class EdgeInfo>
typename CSetGraph<EdgeInfo>::VertexCollection CSetGraph<EdgeInfo>::getNextVertexes(VertexType vertex) const {
    VertexCollection nextVertexes;
    
    for (auto i = buf[vertex].begin(); i != buf[vertex].end(); ++i) {
        nextVertexes.push_back(VertexCollectionUnit(i->first, i->second));
    }
    
    return nextVertexes;
}

template <class EdgeInfo>
typename CSetGraph<EdgeInfo>::VertexCollection CSetGraph<EdgeInfo>:: getPrevVertexes(VertexType vertex) const {
    VertexCollection prevVertexes;
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (auto j = buf[i].begin(); j != buf[i].end(); ++j) {
            if (j->first == vertex) {
                prevVertexes.push_back(VertexCollectionUnit(i, j->second));
            }
        }
    }
    return prevVertexes;
}

template <class EdgeInfo>
void CSetGraph<EdgeInfo>:: convertToGraph(IGraph<EdgeInfo> &newGraph) const {
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (auto j = buf[i].begin(); j != buf[i].end(); ++j) {
            newGraph.addEdge(i, j->first, j->second);
        }
    }
}

template <class EdgeInfo>
std::vector<typename CSetGraph<EdgeInfo>::VertexType> CSetGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

#endif
