//
//  main.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "ResidualNetworkGraph.h"
#include "LayeredNetworkGraph.h"
#include <array>
#include "NetworkGraph.h"

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin>>n >>m;
    auto residual = std::shared_ptr<ResidualNetworkGraph>(new ResidualNetworkGraph(n));
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        residual->addEdge(from, to, 0, capacity);
//        if (from == 0 && to == 1) {
//            residual->pushFlow(1, edge);
//        }
    }
    
    residual->print(0);
    return 0;
}
