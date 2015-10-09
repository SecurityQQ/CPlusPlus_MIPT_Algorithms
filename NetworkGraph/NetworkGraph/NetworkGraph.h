//
//  NetworkGraph.h
//  NetworkGraph
//
//  Created by Alexander Malyshev on 30.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef NetworkGraph_h
#define NetworkGraph_h
#include "CMatrixGraph.h"

typedef unsigned long long CapacityType;
typedef unsigned long long FlowType;

struct NetworkEdgeInfo {
    CapacityType capacity;
    FlowType flow;
    unsigned long long potential;
};

class NetworkGraph: public CMatrixGraph<NetworkEdgeInfo> {
public:
    VertexType source;
    VertexType sink;
    
    NetworkGraph(VertexType source, VertexType sink): source(source), sink(sink) {};
};



#endif /* NetworkGraph_h */
