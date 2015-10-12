//
//  NetworkGraph.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 06.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef NetworkGraph_h
#define NetworkGraph_h
#include "assert.h"
#include "ArcGraph.h"
#include "NetworkEdgeInfo.h"
#include <functional>

#define NOT_VISITED INT_MAX


class NetworkGraph: public ArcGraph<NetworkEdgeInfo> {
    
public:
    NetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): ArcGraph<NetworkEdgeInfo>(numberOfVertexes), source(source), sink(sink) {};
    virtual const void performCompletionBlockOnNextEdges(const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
        return performCompletionBlockOnEdgesWithDirection(1, vertex, completionBlock);
    }
    virtual const void performCompletionBlockOnPrevEdges(const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
        return performCompletionBlockOnEdgesWithDirection(0, vertex, completionBlock);
    }
    virtual CapacityType getCapacity(std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        return edge->info()->capacity();
    }
    virtual FlowType getFlow(std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        return edge->info()->flow();
    }
    virtual void print(const VertexType start) {
        BFS(start, [this](std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        std::cout<<edge->from()<<"->"<<edge->to()<<" ("<<getFlow(edge)<<"/"<<getCapacity(edge) <<")"<<std::endl;
        });
    }
    const VertexType source;
    const VertexType sink;
private:
    virtual const void performCompletionBlockOnEdgesWithDirection(const bool isFrontDirection, const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock);
};

const void NetworkGraph:: performCompletionBlockOnEdgesWithDirection(const bool isFrontDirection, const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
    auto edges = isFrontDirection ? getNextEdges(vertex) : getPrevEdges(vertex);
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (getCapacity(*it) > 0) {
            completionBlock(*it);
        }
    }
}

#endif /* NetworkGraph_h */
