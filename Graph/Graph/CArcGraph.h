//
//  CArcGraph.h
//  Graph
//
//  Created by Александр Малышев on 09.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Graph_CArcGraph_h
#define Graph_CArcGraph_h

#include "IGraph.h"
#include <map>
#include <unordered_set>

template <class EdgeInfo = DefaultVertexWeightType>
class CArcGraph : public IGraph<EdgeInfo> {
    
public:
    
    typedef typename IGraph<EdgeInfo>::VertexCollection VertexCollection;
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::VertexCollectionUnit VertexCollectionUnit;
    
    CArcGraph();
    ~CArcGraph();
    
    
    void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    VertexType vertexCount() const;
    VertexCollection getNextVertexes(VertexType vertex) const;
    VertexCollection getPrevVertexes(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
    void convertToGraph(IGraph<EdgeInfo> &newGraph) const;
    
private:
    
    std::multimap<VertexType, VertexCollectionUnit> buf;
    std::unordered_set<VertexType> _vertexes;
    
};

template <class EdgeInfo>

CArcGraph<EdgeInfo>::CArcGraph() {
    
}

template <class EdgeInfo>
CArcGraph<EdgeInfo>::~CArcGraph() {
    
}

template <class EdgeInfo>
void CArcGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    auto unit = std::make_pair(from, VertexCollectionUnit(to, weight));
    buf.insert(unit);
    _vertexes.insert(from);
    _vertexes.insert(to);
}

template <class EdgeInfo>
typename CArcGraph<EdgeInfo>::VertexType CArcGraph<EdgeInfo>::vertexCount() const {
    return _vertexes.size();
}

template <class EdgeInfo>
typename CArcGraph<EdgeInfo>::VertexCollection CArcGraph<EdgeInfo>::getNextVertexes(VertexType vertex) const {
    VertexCollection nextVertexes;
    for (auto i = buf.find(vertex); i != buf.end(); ++i) {
        nextVertexes.push_back(i->second);
    }
    return nextVertexes;
}

template <class EdgeInfo>
typename CArcGraph<EdgeInfo>::VertexCollection CArcGraph<EdgeInfo>::getPrevVertexes(VertexType vertex) const {
    VertexCollection prevVertexes;
    for (auto i = buf.begin(); i != buf.end(); ++i) {
        if (i->second.vertex == vertex) {
            prevVertexes.push_back(VertexCollectionUnit(i->first, i->second.weight));
        }
    }
    return prevVertexes;
}

template <class EdgeInfo>
void CArcGraph<EdgeInfo>::convertToGraph(IGraph<EdgeInfo> &newGraph) const {
    for (auto i = buf.begin(); i != buf.end(); ++i) {
        newGraph.addEdge(i->first, i->second.vertex, i->second.weight);
    }
}

template <class EdgeInfo>
std::vector<typename CArcGraph<EdgeInfo>::VertexType> CArcGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

#endif
