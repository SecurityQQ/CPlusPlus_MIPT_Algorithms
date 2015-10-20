//
//  main.cpp
//  Graphs-Govnokod
//
//  Created by Alexander Malyshev on 18.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "ResidualNetworkGraph.h"

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin>>n >>m;
    auto residual = std::shared_ptr<ResidualNetworkGraph>(new ResidualNetworkGraph(n));
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        auto edge = std::make_shared<NetworkEdge>(from, to, i, NetworkEdgeInfo(0, capacity));
        residual->addEdge(edge);
        if (from == 0 && to == 1) {
            residual->pushFlow(1, edge);
        }
    }
    
    residual->print(0);
    
    return 0;
}
