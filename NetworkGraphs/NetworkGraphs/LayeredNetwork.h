//
//  LayeredNetwork.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 12.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef LayeredNetwork_h
#define LayeredNetwork_h
#include "NetworkGraph.h"

class LayeredNetwork: public NetworkGraph {
public:
    LayeredNetwork(std::shared_ptr<ResidualNetworkGraph>  residualNetwork): NetworkGraph(residualNetwork->vertexCapacity(), residualNetwork->source, residualNetwork->sink) {
        _sinkReachable = false;
        _residualNetwork = residualNetwork;
        createLayeredNetwork();
    }
    
    void getBlockingFlow();

    bool sinkReachable() { return _sinkReachable; }
private:
    bool _sinkReachable;
    void updatePotentials(std::set<VertexType> &vertexesToDelete);
    void createLayeredNetwork();
    std::shared_ptr<ResidualNetworkGraph> _residualNetwork;
    std::vector<VertexType> distance;
    std::vector<VertexType> incPotential;
    std::vector<VertexType> outPotential;
    std::vector<CapacityType> potential;
    std::vector<FlowType> extraFlow;
};

void LayeredNetwork:: createLayeredNetwork() {
    distance = std::vector<VertexType>(_residualNetwork->vertexCount(), NOT_VISITED);
    incPotential = std::vector<VertexType>(_residualNetwork->vertexCount(), 0);
    outPotential = std::vector<VertexType>(_residualNetwork->vertexCount(), 0);
    potential = std::vector<CapacityType>(_residualNetwork->vertexCount(), NOT_VISITED);
    extraFlow = std::vector<FlowType>(_residualNetwork->vertexCount(), 0);
    std::vector<VertexType> used(_residualNetwork->vertexCount());
    std::queue<VertexType>  vertexQueue;
    
    incPotential[source] = NOT_VISITED;
    outPotential[sink] = NOT_VISITED;
    
    vertexQueue.push(source);
    distance[source] = 0;
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = _residualNetwork->getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                if ((*it)->info()->residualCapacity() > 0) {
                    if (distance[(*it)->to()] == NOT_VISITED) {
                        distance[(*it)->to()] = distance[currentVertex] + 1;
                    }
                    if (distance[(*it)->to()] == distance[currentVertex] + 1) {
                        addEdge(*it);
                        incPotential[(*it)->to()] += (*it)->info()->residualCapacity();
                        outPotential[(*it)->from()] += (*it)->info()->residualCapacity();
                        
                    }
                    vertexQueue.push((*it)->to());
                }
            }
            
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            
#ifdef DEBUG
            std::cout<<"Potential for "<<currentVertex <<" is "<<potential[currentVertex] <<std::endl;
#endif
        }
    }
    _sinkReachable = (distance[sink] != NOT_VISITED);
}

void LayeredNetwork:: getBlockingFlow() {
    while (potential[source] != USED_VERTEX && potential[sink] != USED_VERTEX) {
        std::set<VertexType> vertexesToDelete;
        std::queue<VertexType> pushingQueue;
        std::vector<char> used(vertexCapacity(), 0);
        auto getIndexOfMinElement = [](const std::vector<CapacityType>& v) -> unsigned long long {
            CapacityType min = v[0];
            unsigned long long minIndex = 0;
            for (unsigned long long i = 1; i < v.size(); ++i) {
                if (min > v[i]) {
                    min = v[i];
                    minIndex = i;
                }
            }
            return minIndex;
        };
        
        VertexType vertexWithMinPotential = getIndexOfMinElement(potential);
        extraFlow[vertexWithMinPotential] = potential[vertexWithMinPotential];
        pushingQueue.push(vertexWithMinPotential);
        
        //forward:
        while (!pushingQueue.empty()) {
            auto currentVertex = pushingQueue.front();
            pushingQueue.pop();
            if (!used[currentVertex]) {
                used[currentVertex] = 1;
                auto nextEdges = getNextEdges(currentVertex);
                for (auto edge: nextEdges) {
                    auto residualCapacity = edge->info()->residualCapacity();
                    auto to = edge->to();
                    FlowType pushingFlow;
                    if (residualCapacity <= extraFlow[currentVertex]) {
                        pushingFlow = residualCapacity;
                    } else {
                        pushingFlow = extraFlow[currentVertex];
                    }
                    _residualNetwork->addFlow(edge, pushingFlow);
                    outPotential[currentVertex] -= pushingFlow;
                    incPotential[to] -= pushingFlow;
                    extraFlow[to] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(to);
#ifdef DEBUG
                    std::cout<<"from "<<edge->from() << "to "<<edge->to()<<" pushed: "<<pushingFlow<<std::endl;
#endif
                    if (extraFlow[currentVertex] == 0) {
                        break;
                    }
                }
                vertexesToDelete.insert(currentVertex);
            }
        }
        
        //backward:
        extraFlow[vertexWithMinPotential] = potential[vertexWithMinPotential];
        pushingQueue.push(vertexWithMinPotential);
        used = std::vector<char>(vertexCapacity(), 0);
        
        while (!pushingQueue.empty()) {
            auto currentVertex = pushingQueue.front();
            pushingQueue.pop();
            if (!used[currentVertex]) {
                used[currentVertex] = 1;
                auto nextEdges = getPrevEdges(currentVertex);
                for (auto edge: nextEdges) {
                    auto residualCapacity = edge->info()->residualCapacity();
                    auto oldFlow = edge->info()->flow();
                    auto from = edge->from();
                    FlowType pushingFlow;
                    if (residualCapacity <= extraFlow[currentVertex]) {
                        pushingFlow = residualCapacity;
                    } else {
                        pushingFlow = extraFlow[currentVertex];
                    }
                    _residualNetwork->addFlow(edge, pushingFlow);
                    incPotential[currentVertex] -= pushingFlow;
                    outPotential[from] -= pushingFlow;
                    potential[currentVertex] -= pushingFlow;
                    extraFlow[from] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(from);
#ifdef DEBUG
                    std::cout<<"(backward) from "<<edge->from() << "to "<<edge->to()<<" pushed: "<<pushingFlow<<std::endl;
#endif
                    if (extraFlow[currentVertex] == 0) {
                        break;
                    }
                }
                vertexesToDelete.insert(currentVertex);
            }
        }
        updatePotentials(vertexesToDelete);
    }
}

void LayeredNetwork:: updatePotentials(std::set<VertexType> &vertexesToDelete) {
    while (!vertexesToDelete.empty()) {
        auto currentVertex = *vertexesToDelete.begin();
        vertexesToDelete.erase(currentVertex);
        potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
        if (potential[currentVertex] <= 0) {
            potential[currentVertex] = USED_VERTEX;
            auto nextEdges = getNextEdges(currentVertex);
            auto prevEdges = getPrevEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                removeEdge(*it);
                auto to = (*it)->to();
                vertexesToDelete.insert(to);
                incPotential[to] -= (*it)->info()->residualCapacity();
            }
            for (auto it = prevEdges.begin(); it != prevEdges.end(); ++it) {
                removeEdge(*it);
                auto from = (*it)->from();
                vertexesToDelete.insert(from);
                outPotential[from] -= (*it)->info()->residualCapacity();
            }
        }
    }

}

#endif /* LayeredNetwork_h */
