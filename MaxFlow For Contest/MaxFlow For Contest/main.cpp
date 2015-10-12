//
//  main.cpp
//  MaxFlow For Contest
//
//  Created by Alexander Malyshev on 09.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#define nullptr NULL
#define INT_MAX 1000000001
#include <cstddef>

typedef unsigned long long VertexType;
typedef long long VertexWeight;

#include <forward_list>
#include <set>
#define USED_VERTEX (INT_MAX - 1)

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


#include <vector>
#include <queue>
#include <assert.h>

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
    virtual const bool edgeExists(const VertexType from, const VertexType to) {
        return getEdge(from, to) != nullptr;
    }
    
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
    auto edge = std::shared_ptr<Edge<EdgeInfo>>(new Edge<EdgeInfo>(from, to, *info));
    incomingEdgesToVertex[to].push_front(edge);
    outcomingEdgesFromVertex[from].push_front(edge);
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
    return std::shared_ptr<Edge<EdgeInfo>>(new Edge<EdgeInfo>(0, 0, std::shared_ptr<EdgeInfo>(new EdgeInfo(0, 0))));
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


typedef long FlowType;
typedef unsigned long CapacityType;

class NetworkEdgeInfo {
    
public:
    NetworkEdgeInfo(CapacityType capacity): _flow(0), _capacity(capacity) {};
    NetworkEdgeInfo(FlowType flow, CapacityType capacity): _flow(flow), _capacity(capacity){};
    virtual FlowType flow() { return _flow; }
    virtual CapacityType capacity() { return _capacity; }
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
};


#include <functional>

#define NOT_VISITED INT_MAX


class NetworkGraph: public ArcGraph<NetworkEdgeInfo> {
    
public:
    NetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): ArcGraph<NetworkEdgeInfo>(numberOfVertexes), source(source), sink(sink) {};
    virtual const void performCompletionBlockOnNextEdges(const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
        return performCompletionBlockOnEdgesWithDirection(1, vertex, completionBlock);
    }
    virtual const void performCompletionBlockOnPrevEdges(const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
        return performCompletionBlockOnEdgesWithDirection(0, vertex, completionBlock);
    }
    virtual CapacityType getCapacity(std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        return edge->info()->capacity();
    }
    virtual FlowType getFlow(std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        return edge->info()->flow();
    }
    virtual void print(const VertexType start) {
        BFS(start, [this](std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
            std::cout<<edge->from()<<"->"<<edge->to()<<" ("<<getFlow(edge)<<"/"<<getCapacity(edge) <<")"<<std::endl;
        });
    }
    const VertexType source;
    const VertexType sink;
private:
    virtual const void performCompletionBlockOnEdgesWithDirection(const bool isFrontDirection, const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock);
};

const void NetworkGraph:: performCompletionBlockOnEdgesWithDirection(const bool isFrontDirection, const VertexType vertex, const std::function<void(const std::shared_ptr<Edge<NetworkEdgeInfo>> edge)> completionBlock) {
    auto edges = isFrontDirection ? getNextEdges(vertex) : getPrevEdges(vertex);
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (getCapacity(*it) > 0) {
            completionBlock(*it);
        }
    }
}


#define NOT_VISITED INT_MAX

class ResidualNetworkGraph: public NetworkGraph {
    
public:
    ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): NetworkGraph(numberOfVertexes, source, sink) {};
    
    CapacityType getCapacity(std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
        return edge->info()->capacity() - edge->info()->flow();
    }
    
    void addFlow(std::shared_ptr<Edge<NetworkEdgeInfo>> edge, const FlowType flow) {
        auto oldFlow = edge->info()->flow();
        auto to = edge->to();
        auto from = edge->from();
//        assert(getEdge(from, to) != nullptr);
        edge->info()->setFlow(oldFlow + flow);
        auto reversedEdge = getEdge(to, from);
        if (!reversedEdge) {
            auto info = std::shared_ptr<NetworkEdgeInfo>(new NetworkEdgeInfo(0, edge->info()->flow()));
            addEdge(to, from, info);
        } else {
            reversedEdge->info()->setCapacity(reversedEdge->info()->capacity() + flow);
        }
    }
    
    virtual void print(const VertexType start) {
        BFS(start, [this](std::shared_ptr<Edge<NetworkEdgeInfo>> edge) {
            std::cout<<edge->from()<<"->"<<edge->to()<<" ("<<getCapacity(edge) <<")"<<std::endl;
        });
    }
    
private:
    
};




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

