//
//  main.cpp
//  MaxFlow For Contest
//
//  Created by Alexander Malyshev on 09.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <forward_list>
#include <assert.h>
#include <queue>

#define nullptr NULL
#define INT_MAX 1000*1000*1000

#ifndef NetworkEdgeInfoWithID_h
#define NetworkEdgeInfoWithID_h

typedef unsigned long long VertexType;
typedef long long VertexWeight;
typedef long FlowType;
typedef unsigned long CapacityType;
typedef unsigned long IDType;



typedef unsigned int DefaultEdgeInfo;


template <class EdgeInfo = DefaultEdgeInfo>
class Edge {
    
public:
    Edge(const VertexType from, const VertexType to, const EdgeInfo info): _from(from), _to(to), _info(std::shared_ptr<EdgeInfo>(new EdgeInfo(info))) {};
    Edge(const VertexType from, const VertexType to, std::shared_ptr<EdgeInfo> info): _from(from), _to(to), _info(info) {};
    
    VertexType from() { return _from; }
    VertexType to() { return _to; }
    std::shared_ptr<EdgeInfo> info() { return _info; }
    
private:
    VertexType _from;
    VertexType _to;
    std::shared_ptr<EdgeInfo> _info;
};


class NetworkEdgeInfoWithID {
    
public:
    NetworkEdgeInfoWithID(CapacityType capacity, IDType id): _flow(0), _capacity(capacity), _id(id) {};
    NetworkEdgeInfoWithID(FlowType flow, CapacityType capacity, IDType id): _flow(flow), _capacity(capacity), _id(id) {};
    virtual FlowType flow() { return _flow; }
    virtual CapacityType capacity() { return _capacity; }
    virtual IDType id() { return _id; }
    virtual CapacityType residualCapacity() { return _capacity - _flow; }
    virtual void setFlow(FlowType flow) {
        assert(flow <= capacity());
        _flow = flow;
    }
    virtual void setCapacity(CapacityType capacity) {
        assert(flow() <= capacity);
        _capacity = capacity;
    }
protected:
    FlowType _flow;
    CapacityType _capacity;
    IDType _id;
};





#endif /* NetworkEdgeInfoWithID_h */

//
//  ArcGraph.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 04.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef ArcGraph_h
#define ArcGraph_h


template <class EdgeInfo>
class ArcGraph {
    
public:
    
    typedef std::forward_list<std::shared_ptr<Edge<EdgeInfo>>> EdgesCollection;
    
    ArcGraph(const VertexType numberOfVertexes);
    virtual ~ArcGraph() {}
    
    virtual void addEdge(const VertexType from, const VertexType to, const std::shared_ptr<EdgeInfo> info = nullptr);
    virtual void addEdge(const std::shared_ptr<Edge<EdgeInfo>> edge);
    virtual void removeEdge(const VertexType from, const VertexType to);
    virtual void removeEdge(const std::shared_ptr<Edge<EdgeInfo>> edge);
    virtual void changeEdge(const VertexType from, const VertexType to, std::shared_ptr<EdgeInfo> info = nullptr);
    virtual std::shared_ptr<Edge<EdgeInfo>> getEdge(const VertexType from, const VertexType to) const;
    
    virtual const VertexType vertexCount() const;
    virtual const VertexType vertexCapacity() const;
    virtual const EdgesCollection getNextEdges(const VertexType vertex) const;
    virtual const EdgesCollection getPrevEdges(const VertexType vertex) const;
    virtual std::shared_ptr<const std::vector<const VertexType>> getAllVertexes() const;
    
    virtual void BFS(const VertexType start, const std::function<void(const std::shared_ptr<Edge<EdgeInfo>> edge)>);
    
    
protected:
    
    ArcGraph() {}
    std::vector<std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>> incomingEdgesToVertex;
    std::vector<std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>> outcomingEdgesFromVertex;
    VertexType _vertexCount;
};

template <class EdgeInfo>
ArcGraph<EdgeInfo>:: ArcGraph(const VertexType numberOfVertexes) {
    
    incomingEdgesToVertex = std::move(std::vector<std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>>(numberOfVertexes, std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>()));
    outcomingEdgesFromVertex = std::move(std::vector<std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>>(numberOfVertexes, std::forward_list<std::shared_ptr<Edge<EdgeInfo>>>()));
    _vertexCount = numberOfVertexes;
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>:: addEdge(const VertexType from, const VertexType to, const std::shared_ptr<EdgeInfo> info) {
    assert((from < incomingEdgesToVertex.size()) && (to < outcomingEdgesFromVertex.size()));
    incomingEdgesToVertex[to].push_front(std::shared_ptr<Edge<EdgeInfo>>(new Edge<EdgeInfo>(from, to, *info)));
    outcomingEdgesFromVertex[from].push_front(std::shared_ptr<Edge<EdgeInfo>>(new Edge<EdgeInfo>(from, to, *info)));
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>::addEdge(const std::shared_ptr<Edge<EdgeInfo>> edge) {
    auto from = edge->from();
    auto to = edge->to();
    assert((from < incomingEdgesToVertex.size()) && (to < outcomingEdgesFromVertex.size()));
    incomingEdgesToVertex[to].push_front(edge);
    outcomingEdgesFromVertex[from].push_front(edge);
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>:: removeEdge(const VertexType from, const VertexType to) {
    assert((from < incomingEdgesToVertex.size()) && (to < outcomingEdgesFromVertex.size()));
    incomingEdgesToVertex[to].remove_if([&from](std::shared_ptr<Edge<EdgeInfo>> edge) {
        return edge->from() == from;
    });
    outcomingEdgesFromVertex[from].remove_if([&to](std::shared_ptr<Edge<EdgeInfo>> edge) {
        return edge->to() == to;
    });
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>:: removeEdge(const std::shared_ptr<Edge<EdgeInfo>> edge) {
    incomingEdgesToVertex[edge->to()].remove(edge);
    outcomingEdgesFromVertex[edge->from()].remove(edge);
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>:: changeEdge(const VertexType from, const VertexType to, std::shared_ptr<EdgeInfo> info) {
    assert(false);
}


template <class EdgeInfo>
std::shared_ptr<Edge<EdgeInfo>> ArcGraph<EdgeInfo>:: getEdge(const VertexType from, const VertexType to) const {
    for (auto it = incomingEdgesToVertex[to].begin(); it != incomingEdgesToVertex[to].end(); ++it) {
        if ((*it)->from() == from) {
            return *it;
        }
    }
//    return nullptr;
    return std::shared_ptr<Edge<EdgeInfo>>(new Edge<EdgeInfo>(0, 0, std::shared_ptr<EdgeInfo>(new EdgeInfo(0, 0, 0))));
}

template <class EdgeInfo>
const VertexType ArcGraph<EdgeInfo>:: vertexCount() const {
    return _vertexCount;
}

template <class EdgeInfo>
const VertexType ArcGraph<EdgeInfo>:: vertexCapacity() const {
    return _vertexCount;
}

template <class EdgeInfo>
const typename ArcGraph<EdgeInfo>::EdgesCollection ArcGraph<EdgeInfo>:: getNextEdges(const VertexType vertex) const {
    return outcomingEdgesFromVertex[vertex];
}

template <class EdgeInfo>
const typename ArcGraph<EdgeInfo>::EdgesCollection ArcGraph<EdgeInfo>:: getPrevEdges(const VertexType vertex) const {
    return incomingEdgesToVertex[vertex];
}

template <class EdgeInfo>
std::shared_ptr<const std::vector<const VertexType>> ArcGraph<EdgeInfo>:: getAllVertexes() const {
    assert(false);
    return std::shared_ptr<const std::vector<const VertexType>>();
}

template <class EdgeInfo>
void ArcGraph<EdgeInfo>:: BFS(const VertexType start, const std::function<void(const std::shared_ptr<Edge<EdgeInfo>> edge)> completionBlock) {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(vertexCount());
    vertexQueue.push(start);
    
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                vertexQueue.push((*it)->to());
                completionBlock(*it);
            }
        }
    }
}


#endif /* ArcGraph_h */


#define NOT_VISITED INT_MAX


class NetworkGraph: public ArcGraph<NetworkEdgeInfoWithID> {
    
public:
    NetworkGraph(const VertexType numberOfVertexes): ArcGraph<NetworkEdgeInfoWithID>(numberOfVertexes) {};
    virtual CapacityType getCapacity(std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
        return edge->info()->capacity();
    }
private:
    
};

//
//  ResidualNetworkGraph.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 07.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef ResidualNetworkGraph_h
#define ResidualNetworkGraph_h

#define NOT_VISITED INT_MAX


class ResidualNetworkGraph: public NetworkGraph {
    
public:
    ResidualNetworkGraph(const VertexType numberOfVertexes): NetworkGraph(numberOfVertexes) {};
    CapacityType getCapacity(std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
        return edge->info()->capacity() - edge->info()->flow();
    }
    void addFlow(std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge, const FlowType flow) {
//        auto oldFlow = edge->info()->flow();
//        auto to = edge->to();
//        auto from = edge->from();
////        assert(getEdge(from, to) != nullptr);
//        edge->info()->setFlow(oldFlow + flow);
//        auto reversedEdge = getEdge(to, from);
//        if (reversedEdge == nullptr) {
//            auto info = std::shared_ptr<NetworkEdgeInfoWithID>(new NetworkEdgeInfoWithID(0, edge->info()->flow(), edge->info()->id()));
//            addEdge(to, from, info);
//        } else {
//            reversedEdge->info()->setCapacity(reversedEdge->info()->capacity() + flow);
//        }
        // TODO: implement this
        //remade capacities
    }
    
private:
    
};

#endif /* ResidualNetworkGraph_h */

#include <set>

#define USED_VERTEX (INT_MAX - 1)

class LayeredNetworkManager {
public:
    static LayeredNetworkManager& sharedInstance();
    std::shared_ptr<ResidualNetworkGraph> getLayeredGraph(std::shared_ptr<NetworkGraph> network, const VertexType source,
                                                          const VertexType sink);
    FlowType maxFlowWithMPMAlgorithm(std::shared_ptr<NetworkGraph> graph, const VertexType source, const VertexType sink);
    void getBlockingFlow(std::shared_ptr<ResidualNetworkGraph> network, const VertexType source, const VertexType sink);
private:
    void updatePotentials(std::shared_ptr<ResidualNetworkGraph> layeredNetwork, std::set<VertexType> &vertexesToDelete, const VertexType source, const VertexType sink);
    LayeredNetworkManager() {}
    std::vector<VertexType> distance;
    std::vector<VertexType> incPotential;
    std::vector<VertexType> outPotential;
    std::vector<CapacityType> potential;
    std::vector<FlowType> extraFlow;
};

LayeredNetworkManager& LayeredNetworkManager:: sharedInstance() {
    static LayeredNetworkManager instance;
    return instance;
}


FlowType LayeredNetworkManager:: maxFlowWithMPMAlgorithm(std::shared_ptr<NetworkGraph> graph, const VertexType source, const VertexType sink) {
    auto residualNetwork = std::shared_ptr<NetworkGraph>(new NetworkGraph(graph->vertexCount()));
    while (true) {
        auto layeredGraph = getLayeredGraph(graph, source, sink);
#ifdef DEBUG
        std::cout<<"layered graph created"<<std::endl;
        layeredGraph->BFS(0, [](const std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
            std::cout<<edge->from() <<"->"<<edge->to() <<"("<<edge->info()->flow()<<"/"<<edge->info()->capacity()<<")"<<std::endl;
        });
#endif
        
        if (distance[sink] == NOT_VISITED) {
            break;
        }
        
        getBlockingFlow(layeredGraph, source, sink);
#ifdef DEBUG
        std::cout<<"Blocking path added"<<std::endl;
        graph->BFS(0, [](const std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
            std::cout<<edge->from() <<"->"<<edge->to() <<"("<<edge->info()->flow()<<"/"<<edge->info()->capacity()<<")"<<std::endl;
        });
        
#endif
    }
    FlowType maxFlow = 0;
    auto sourceAdjEdges = graph->getNextEdges(source);
    for (auto it = sourceAdjEdges.begin(); it != sourceAdjEdges.end(); ++it) {
        maxFlow += (*it)->info()->flow();
    }
    return maxFlow;
}

std::shared_ptr<ResidualNetworkGraph> LayeredNetworkManager:: getLayeredGraph(std::shared_ptr<NetworkGraph> network, const VertexType source, const VertexType sink) {
    distance = std::vector<VertexType>(network->vertexCount(), NOT_VISITED);
    incPotential = std::vector<VertexType>(network->vertexCount(), 0);
    outPotential = std::vector<VertexType>(network->vertexCount(), 0);
    potential = std::vector<CapacityType>(network->vertexCount(), NOT_VISITED);
    extraFlow = std::vector<FlowType>(network->vertexCount(), 0);
    auto layeredGraph = std::shared_ptr<ResidualNetworkGraph>(new ResidualNetworkGraph(network->vertexCount()));
    std::vector<VertexType> used(network->vertexCount());
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
            auto nextEdges = network->getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                if ((*it)->info()->residualCapacity() > 0) {
                    if (distance[(*it)->to()] == NOT_VISITED) {
                        distance[(*it)->to()] = distance[currentVertex] + 1;
                    }
                    if (distance[(*it)->to()] == distance[currentVertex] + 1) {
                        layeredGraph->addEdge(*it);
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
    
    return layeredGraph;
}

void LayeredNetworkManager:: getBlockingFlow(std::shared_ptr<ResidualNetworkGraph> layeredNetwork, const VertexType source, const VertexType sink) {
    while (potential[source] != USED_VERTEX && potential[sink] != USED_VERTEX) {
        std::set<VertexType> vertexesToDelete;
        std::queue<VertexType> pushingQueue;
        std::vector<char> used(layeredNetwork->vertexCount(), 0);
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
                auto nextEdges = layeredNetwork->getNextEdges(currentVertex);
                for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                    auto edge = *it;
                    auto residualCapacity = edge->info()->residualCapacity();
                    auto oldFlow = edge->info()->flow();
                    auto to = edge->to();
                    FlowType pushingFlow;
                    if (residualCapacity <= extraFlow[currentVertex]) {
                        pushingFlow = residualCapacity;
                    } else {
                        pushingFlow = extraFlow[currentVertex];
                    }
                    edge->info()->setFlow(oldFlow + pushingFlow);
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
        used = std::vector<char>(layeredNetwork->vertexCount(), 0);
        
        while (!pushingQueue.empty()) {
            auto currentVertex = pushingQueue.front();
            pushingQueue.pop();
            if (!used[currentVertex]) {
                used[currentVertex] = 1;
                auto nextEdges = layeredNetwork->getPrevEdges(currentVertex);
                for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                    auto edge = *it;
                    auto residualCapacity = edge->info()->residualCapacity();
                    auto oldFlow = edge->info()->flow();
                    auto from = edge->from();
                    FlowType pushingFlow;
                    if (residualCapacity <= extraFlow[currentVertex]) {
                        pushingFlow = residualCapacity;
                    } else {
                        pushingFlow = extraFlow[currentVertex];
                    }
                    edge->info()->setFlow(oldFlow + pushingFlow);
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
        
        updatePotentials(layeredNetwork, vertexesToDelete, source, sink);
    }
}

void LayeredNetworkManager:: updatePotentials(std::shared_ptr<ResidualNetworkGraph> layeredNetwork, std::set<VertexType> &vertexesToDelete, const VertexType source, const VertexType sink) {
    while (!vertexesToDelete.empty()) {
        auto currentVertex = *vertexesToDelete.begin();
        vertexesToDelete.erase(currentVertex);
        potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
        if (potential[currentVertex] <= 0) {
            potential[currentVertex] = USED_VERTEX;
            auto nextEdges = layeredNetwork->getNextEdges(currentVertex);
            auto prevEdges = layeredNetwork->getPrevEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                layeredNetwork->removeEdge(*it);
                auto to = (*it)->to();
                vertexesToDelete.insert(to);
                incPotential[to] -= (*it)->info()->residualCapacity();
            }
            for (auto it = prevEdges.begin(); it != prevEdges.end(); ++it) {
                layeredNetwork->removeEdge(*it);
                auto from = (*it)->from();
                vertexesToDelete.insert(from);
                outPotential[from] -= (*it)->info()->residualCapacity();
            }
        }
    }
    
}


#undef DEBUG

int main(int argc, const char * argv[]) {
    
    int n, m;
    std::cin>>n >>m;
    std::shared_ptr<ResidualNetworkGraph> network(new ResidualNetworkGraph(n));
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from >> to >> capacity;
        network->addEdge(from - 1, to - 1, std::shared_ptr<NetworkEdgeInfoWithID>(new NetworkEdgeInfoWithID(0, capacity, i)));
    }
    std::vector<FlowType> flows(m, 0);
    //    auto printGraph = [](const std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
    //        std::cout<<edge->from() <<"->"<<edge->to() <<"("<<edge->info()->flow()<<"/"<<edge->info()->capacity()<<")"<<std::endl;
    //    };
    //
    //    network->BFS(0, printGraph);
    
    //    auto layered = LayeredNetworkManager::sharedInstance().getLayeredGraph(network, 0, n - 1);
    //    layered->BFS(0, printGraph);
    //    auto maxFlow = LayeredNetworkManager::sharedInstance().getBlockingFlow(network, 0, n - 1);
    
    std::cout<<LayeredNetworkManager::sharedInstance().maxFlowWithMPMAlgorithm(network, 0, n - 1) <<std::endl;
    network->BFS(0, [&flows, &network](const std::shared_ptr<Edge<NetworkEdgeInfoWithID>> edge) {
        flows[edge->info()->id()] = edge->info()->flow();
    });
    
    for (auto it = flows.begin(); it != flows.end(); ++it) {
        std::cout<<*it<<std::endl;
    }
    
    
    return 0;
}