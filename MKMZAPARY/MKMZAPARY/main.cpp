//
//  main.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "LayeredNetworkGraph.h"
//#include "LayeredNetworkGraph.h"
//#include <array>
//#include "Graph.h"
int main(int argc, const char * argv[]) {
    int n, m;
    std::cin>>n >>m;
    auto residual = std::make_shared<ResidualNetworkGraph>(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        residual->addEdge(from, to, 0, capacity);
//        if (from == 0 && to == 1) {
//            residual->pushFlow(1, edge);
//        }
    }
//    residual->pushFlow(1, 0, 2);
//    residual->pushFlow(1, 1, 3);
    std::cout<<"Residual:"<<std::endl;
    residual->print(0);
//    std::cout<<"Layered:"<<std::endl;
//    auto layered = std::make_shared<LayeredNetworkGraph>(residual);
//    layered->print(0);
    return 0;
}
