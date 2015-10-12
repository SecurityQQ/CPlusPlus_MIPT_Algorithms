//
//  GraphManager.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 12.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef GraphManager_h
#define GraphManager_h
#include "ResidualNetworkGraph.h"
#include "LayeredNetwork.h"
#include <set>

class GraphManager {
public:
    static GraphManager& sharedInstance() {
        static auto instance = GraphManager();
        return instance;
    }
    
    FlowType maxFlowWithMPMAlgorithm(std::shared_ptr<ResidualNetworkGraph> graph);
private:
    GraphManager() {}
};

FlowType GraphManager:: maxFlowWithMPMAlgorithm(std::shared_ptr<ResidualNetworkGraph> residualNetwork) {
        while (true) {
            auto layeredGraph = std::shared_ptr<LayeredNetwork>(new LayeredNetwork(residualNetwork));
    
    #ifdef DEBUG
            std::cout<<"layered graph created"<<std::endl;
            residualNetwork->print(residualNetwork->source);
//            layeredGraph->BFS(0, [](const std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
//                std::cout<<edge->from() <<"->"<<edge->to() <<"("<<edge->info()->flow()<<"/"<<edge->info()->capacity()<<")"<<std::endl;
//            });
    #endif
    
            if (!(layeredGraph->sinkReachable())) {
                break;
            }
    
            layeredGraph->getBlockingFlow();
    #ifdef DEBUG
            std::cout<<"Blocking path added"<<std::endl;
            residualNetwork->print(residualNetwork->source);
//            residualNetwork->BFS(0, [](const std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
//                std::cout<<edge->from() <<"->"<<edge->to() <<"("<<edge->info()->flow()<<"/"<<edge->info()->capacity()<<")"<<std::endl;
//            });
    
    #endif
        }
        FlowType maxFlow = 0;
        auto sourceAdjEdges = residualNetwork->getNextEdges(residualNetwork->source);
        for (auto it = sourceAdjEdges.begin(); it != sourceAdjEdges.end(); ++it) {
            maxFlow += (*it)->info()->flow();
        }
        return maxFlow;
}

#endif /* GraphManager_h */
