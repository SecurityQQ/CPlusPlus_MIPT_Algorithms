//
//  ResidualNetworkGraph.cpp
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 27.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include "ResidualNetworkGraph.hpp"

#include <iostream>

ResidualNetworkGraph:: ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): Graph(numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    flowKeeper = std::make_shared<FlowKeeper>(numberOfVertexes);
    _vertexCount = numberOfVertexes;
    this->source = source;
    this->sink = sink;
}

void ResidualNetworkGraph:: addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity) {
    flowKeeper->addCapacity(capacity, from, to);
    flowKeeper->pushFlow(flow, from, to);
    Graph::addEdge(from, to);
    Graph::addEdge(to, from);
}

void ResidualNetworkGraph:: pushFlow(FlowType flow, const VertexType from, const VertexType to) {
    flowKeeper->pushFlow(flow, from, to);
}


void ResidualNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<flowKeeper->flow(from, to)<<"/"<<flowKeeper->capacity(from, to) <<")"<<std::endl;
    });
}

void ResidualNetworkGraph:: performCompletionBlockOnNextVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    auto nextVertexes = getNextVertexes(vertex);
    for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
        if (flowKeeper->residualCapacity(vertex, *it) > 0) {
            completionBlock(vertex, *it);
        }
    }
}

void ResidualNetworkGraph:: performCompletionBlockOnPrevVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    auto nextVertexes = getPrevVertexes(vertex);
    for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
        if (flowKeeper->residualCapacity(vertex, *it) > 0) {
            completionBlock(vertex, *it);
        }
    }
}

