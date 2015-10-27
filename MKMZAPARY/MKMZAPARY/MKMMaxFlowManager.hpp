//
//  MKMMaxFlowManager.hpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef MKMMaxFlowManager_hpp
#define MKMMaxFlowManager_hpp

#include <stdio.h>
#include "ResidualNetworkGraph.hpp"

class MKMMaxFlowManager {
public:
    MKMMaxFlowManager(ResidualNetworkGraph *residualNetwork): residualNetwork(residualNetwork) {};
    const VertexType getMaxFlow();
private:
    ResidualNetworkGraph *residualNetwork;
};

#endif /* MKMMaxFlowManager_hpp */
