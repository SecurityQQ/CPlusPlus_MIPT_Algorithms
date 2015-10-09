//
//  CMatrixOrientedGraph.h
//  NetworkGraph
//
//  Created by Alexander Malyshev on 29.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef CMatrixOrientedGraph_h
#define CMatrixOrientedGraph_h
#include "CMatrixGraph.h"


template <class EdgeInfo>
class CMatrixOrientedGraph: public CMatrixGraph<EdgeInfo> {

public:
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::Edge Edge;
    typedef typename IGraph<EdgeInfo>::EdgesCollection EdgesCollection;
    
    virtual void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    virtual void removeEdge(VertexType from, VertexType to);
    virtual void changeEdge(VertexType from, VertexType to, EdgeInfo info);
};

template <class EdgeInfo>
void CMatrixOrientedGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo info) {
    CMatrixGraph<EdgeInfo>::addEdge(from, to, info);
    CMatrixGraph<EdgeInfo>::addEdge(to, from, info);
}

template <class EdgeInfo>
void CMatrixOrientedGraph<EdgeInfo>:: removeEdge(VertexType from, VertexType to) {
    CMatrixGraph<EdgeInfo>::removeEdge(from, to);
    CMatrixGraph<EdgeInfo>::removeEdge(to, from);
}

template <class EdgeInfo>
void CMatrixOrientedGraph<EdgeInfo>:: changeEdge(VertexType from, VertexType to, EdgeInfo info) {
    CMatrixGraph<EdgeInfo>::changeEdge(from, to, info);
    CMatrixGraph<EdgeInfo>::changeEdge(to, from, info);
}

#endif /* CMatrixOrientedGraph_h */
