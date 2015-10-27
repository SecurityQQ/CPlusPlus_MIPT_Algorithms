//
//  ResidualNetworkGraph.hpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef ResidualNetworkGraph_hpp
#define ResidualNetworkGraph_hpp

#include <forward_list>
#include <vector>
#include <queue>
#include "Graph.h"
#include "FlowKeeper.h"

class ResidualNetworkGraph: public Graph {
    
public:
    
    typedef std::forward_list<VertexType> VertexesCollection;
    
    ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink);
    
    virtual void addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity);
    virtual void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
    
    virtual void performCompletionBlockOnNextVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    virtual void performCompletionBlockOnPrevVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    
    virtual void print(const VertexType start);
    
    virtual const FlowType flow(const VertexType from, const VertexType to) { return flowKeeper->flow(from, to); }
    virtual const CapacityType capacity(const VertexType from, const VertexType to) { return flowKeeper->capacity(from, to); }
    virtual const CapacityType residualCapacity(const VertexType from, const VertexType to) { return flowKeeper->residualCapacity(from, to); }
    
    virtual const VertexType getSource() { return source; }
    virtual const VertexType getSink() { return sink; }
    
protected:
    
    VertexType source;
    VertexType sink;
    
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
    std::shared_ptr<FlowKeeper> flowKeeper;
    
};



#endif /* ResidualNetworkGraph_hpp */
