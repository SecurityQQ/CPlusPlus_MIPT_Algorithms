//
//  main.cpp
//  NetworkGraphs
//
//  Created by Alexander Malyshev on 11.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "NetworkGraph.h"
#include "ResidualNetworkGraph.h"
#include "LayeredNetworkManager.h"
#include "GraphManager.h"
#include <cstddef>

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin>>n >>m;
    std::vector<std::shared_ptr<NetworkEdgeInfo>> infoToOutput;
    auto residual = std::shared_ptr<ResidualNetworkGraph>(new ResidualNetworkGraph(n , 0, n - 1));
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        auto info = std::shared_ptr<NetworkEdgeInfo>(new NetworkEdgeInfo(0, capacity));
        auto edge = std::shared_ptr<Edge<NetworkEdgeInfo>>(new Edge<NetworkEdgeInfo>(from - 1, to - 1, info));
        residual->addEdge(edge);
        infoToOutput.push_back(info);
    }

    residual->print(0);
    
    std::cout<<GraphManager::sharedInstance().maxFlowWithMPMAlgorithm(residual); std::cout<<std::endl;
    for (auto it = infoToOutput.begin(); it != infoToOutput.end(); ++it) {
        std::cout<<(*it)->flow()<<std::endl;
    }
    
    return 0;
}
