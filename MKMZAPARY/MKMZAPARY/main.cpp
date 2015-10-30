//
//  main.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "LayeredNetworkGraph.hpp"
#include "MKMMaxFlowManager.hpp"
//struct EdgeToShow {
//    VertexType from;
//    VertexType to;
//    FlowType flow;
//    EdgeToShow(VertexType from, VertexType to, FlowType flow)
//};
#undef DEBUG
int main(int argc, const char * argv[]) {
    int n, m;
    std::cin>>n >>m;
    auto residual = new ResidualNetworkGraph(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        residual->addEdge(from - 1, to - 1, 0, capacity);
//        if (from == 0 && to == 1) {
//            residual->pushFlow(1, edge);
//        }
    }
//    std::cout<<"Input finished\n";
//    residual->pushFlow(1, 0, 2);
//    residual->pushFlow(1, 1, 3);
//    std::cout<<"Residual:"<<std::endl;
//    residual->print(0);
//    std::cout<<"Layered:"<<std::endl;
//    auto layered = std::make_shared<LayeredNetworkGraph>(residual);
//    layered->print(0);
    
    auto manager = MKMMaxFlowManager(residual);
    auto maxFlow = manager.getMaxFlow();
    std::cout<<maxFlow<<std::endl;
    delete residual;
    return 0;
}
