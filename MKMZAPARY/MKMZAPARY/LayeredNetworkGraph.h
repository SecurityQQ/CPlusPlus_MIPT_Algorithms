//
//  LayeredNetworkGraph.h
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef LayeredNetworkGraph_h
#define LayeredNetworkGraph_h
#include "ResidualNetworkGraph.h"

class LayeredNetworkGraph: public ResidualNetworkGraph {
public:
    LayeredNetworkGraph(const VertexType numberOfVertexes) = delete;
};


#endif /* LayeredNetworkGraph_h */
