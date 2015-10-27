//
//  LayeredNetworkGraph.hpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef LayeredNetworkGraph_hpp
#define LayeredNetworkGraph_hpp

#include <stdio.h>
#include <numeric>
#include <set>
#include <queue>
#include <iostream>
#include "ResidualNetworkGraph.hpp"

class LayeredNetworkGraph: public Graph {
    
public:
    LayeredNetworkGraph(const VertexType numberOfVertexes) = delete;
    LayeredNetworkGraph(ResidualNetworkGraph *residualNetwork): Graph(residualNetwork->vertexCount()), residualNetwork(residualNetwork), source(residualNetwork->getSource()), sink(residualNetwork->getSink()) {
        init();
    }
    
    void getBlockingFlow();
    bool sinkReachable();
    
    void print(const VertexType start);
private:
    const VertexType NOT_REACHED = std::numeric_limits<VertexType>::max();
    const CapacityType MAX_POTENTIAL = std::numeric_limits<CapacityType>::max();
    
    void pushFront(std::set<VertexType> &vertexesToUpdate);
    void pushBackward(std::set<VertexType> &vertexesToUpdate);
    void pushWithDirection(bool isFront, std::set<VertexType> &vertexesToUpdate);
    void updatePotentials(std::set<VertexType> &vertexesToUpdate);
    
    
    VertexType source;
    VertexType sink;
    void init();
    ResidualNetworkGraph *residualNetwork;
    std::vector<VertexType> distance;
    std::vector<CapacityType> incPotential;
    std::vector<CapacityType> outPotential;
    std::vector<CapacityType> potential;
    std::vector<FlowType> extraFlow;
};

#endif /* LayeredNetworkGraph_hpp */
