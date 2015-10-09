//
//  MPMNetworkGraph.h
//  NetworkGraph
//
//  Created by Alexander Malyshev on 30.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef MPMNetworkGraph_h
#define MPMNetworkGraph_h
#include "CMatrixGraph.h"
#include <assert.h>

typedef unsigned long long CapacityType;
typedef unsigned long long FlowType;
typedef unsigned long long PotentialType;

struct MPMNetworkEdgeInfo {
    CapacityType capacity;
    FlowType flow;
    PotentialType potential;
    
    MPMNetworkEdgeInfo(CapacityType capacity): capacity(capacity), flow(0), potential(INFINITY) {};
    MPMNetworkEdgeInfo(CapacityType capacity, FlowType flow): capacity(capacity), flow(flow), potential(INFINITY) {};
    MPMNetworkEdgeInfo(CapacityType capacity, FlowType flow, PotentialType potential): capacity(capacity), flow(flow), potential(potential) {};
    
    MPMNetworkEdgeInfo augmentingInfo() const {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(capacity - flow, flow, potential);
    }
    
    MPMNetworkEdgeInfo infoWithNewFlow(FlowType newFlow) {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(capacity, newFlow, potential);
    }
    
    MPMNetworkEdgeInfo infoWithNewCapacity(CapacityType newCapacity) {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(newCapacity, flow, potential);
    }
    
    FlowType augmentingCapacity() {
        assert(capacity >= flow);
        return capacity - flow;
    }
    
    bool isSuitable() const {
        return flow - capacity;
    }
};

typedef IGraph<MPMNetworkEdgeInfo>::Edge MPMNetworkEdge;

class MPMNetworkGraph: public CMatrixGraph<MPMNetworkEdgeInfo> {
    
public:
//    MPMNetworkGraph residualNetworkWithSource(VertexType source);
};


//MPMNetworkGraph MPMNetworkGraph::residualNetworkWithSource(VertexType source) {
//    MPMNetworkGraph residualNetwork;
//    auto addEdgeToResidualNetwork = [&residualNetwork](const MPMNetworkEdge edge) {
//        if (edge.info.isSuitable()) {
//            residualNetwork.addEdge(edge.from, edge.to, edge.info.augmentingInfo());
//        }
//    };
//    
//    BFS(source, addEdgeToResidualNetwork);
//    
//    return residualNetwork;
//}

#endif /* MPMNetworkGraph_h */
