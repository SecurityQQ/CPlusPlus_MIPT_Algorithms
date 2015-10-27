//
//  MKMMaxFlowManager.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include "MKMMaxFlowManager.hpp"
#include "LayeredNetworkGraph.hpp"

const VertexType MKMMaxFlowManager:: getMaxFlow() {
    while (true) {
        auto layeredGraph = LayeredNetworkGraph(residualNetwork);
        
#ifdef DEBUG
        std::cout<<"layered graph created"<<std::endl;
        residualNetwork->print(residualNetwork->getSource());
#endif
        
        if (!(layeredGraph.sinkReachable())) {
            break;
        }
        
        layeredGraph.getBlockingFlow();
#ifdef DEBUG
        std::cout<<"Blocking path added"<<std::endl;
        residualNetwork->print(residualNetwork->getSource());
#endif
    }
    FlowType maxFlow = 0;
    auto sourceAdjEdges = residualNetwork->getNextVertexes(residualNetwork->getSource());
    for (auto it = sourceAdjEdges.begin(); it != sourceAdjEdges.end(); ++it) {
        maxFlow += residualNetwork->flow(residualNetwork->getSource(), *it);
    }
    return maxFlow;
}