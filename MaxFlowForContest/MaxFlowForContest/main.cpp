//
//  main.cpp
//  MaxFlowForContest
//
//  Created by Alexander Malyshev on 02.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <stdio.h>


#ifndef NetworkAlgorithmManager_h
#define NetworkAlgorithmManager_h


#ifndef MPMNetworkGraph_h
#define MPMNetworkGraph_h
#ifndef Graph_CMatrixGraph_h
#define Graph_CMatrixGraph_h

#define NO_VERTEX NULL

#ifndef Graph_IGraph_h
#define Graph_IGraph_h

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <functional>

typedef long long DefaultVertexWeightType;

template <class EdgeInfo = DefaultVertexWeightType>
class IGraph {
    
public:
    
    typedef unsigned long long VertexType;
    typedef long long VertexWeight;
    struct Edge {
        VertexType from;
        VertexType to;
        EdgeInfo info;
        Edge(VertexType from, VertexType to, EdgeInfo info): from(from), to(to), info(info) {}
    };
    
    typedef std::vector<Edge> EdgesCollection;
    
    virtual ~IGraph() {}
    
    virtual void addEdge(VertexType from, VertexType to, EdgeInfo info = 1) = 0;
    virtual void removeEdge(VertexType from, VertexType to) = 0;
    virtual void changeEdge(VertexType from, VertexType to, EdgeInfo info) = 0;
    virtual EdgeInfo getEdgeInfo(VertexType from, VertexType to) = 0;
    
    
    virtual VertexType vertexCount() const = 0;
    virtual EdgesCollection getNextEdges(VertexType vertex) const = 0;
    virtual EdgesCollection getPrevEdges(VertexType vertex) const = 0;
    virtual std::vector<VertexType> getAllVertexes() const = 0;
    
    virtual void BFS(const VertexType start, const std::function<void(const Edge edge)> completionBlock) const;
    
    
    virtual void convertToGraph(IGraph &newGraph) const = 0;
};


template <class EdgeInfo>
void IGraph<EdgeInfo>:: BFS(const VertexType start, const std::function<void(const Edge edge)> completionBlock) const {
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
                vertexQueue.push(it->to);
                completionBlock(*it);
            }
        }
    }
}




#endif

#include <unordered_set>



template <class EdgeInfo = DefaultVertexWeightType>
class CMatrixGraph: public IGraph<EdgeInfo> {
    
public:
    
    typedef typename IGraph<EdgeInfo>::VertexType VertexType;
    typedef typename IGraph<EdgeInfo>::Edge Edge;
    typedef typename IGraph<EdgeInfo>::EdgesCollection EdgesCollection;
    
    CMatrixGraph();
    ~CMatrixGraph();
    
    
    virtual void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    virtual void removeEdge(VertexType from, VertexType to);
    virtual void changeEdge(VertexType from, VertexType to, EdgeInfo info);
    virtual EdgeInfo getEdgeInfo(VertexType from, VertexType to);
    
    VertexType vertexCount() const;
    VertexType vertexMax() const;
    EdgesCollection getNextEdges(VertexType vertex) const;
    EdgesCollection getPrevEdges(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
    void convertToGraph(IGraph<EdgeInfo> &newGraph) const;
    
private:
    VertexType _maxVertex;
    std::vector<std::vector<EdgeInfo *>> buf;
    std::unordered_set<VertexType> _vertexes;
};


template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: CMatrixGraph() {
    _maxVertex = 0;
}

template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: ~CMatrixGraph() {
    
}
template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    
    if ( from >= buf.size() || to >= buf.size() ) {
        VertexType newSize = std::max(from, to) + 1;
        VertexType oldBufSize = buf.size();
        for (auto it = buf.begin(); it != buf.end(); ++it) {
            it->insert(it->end(), newSize - oldBufSize, NO_VERTEX);
        }
        buf.insert(buf.end(), newSize - oldBufSize, std::vector<EdgeInfo *>(newSize, NO_VERTEX));
    }
    
    buf[from][to] = new EdgeInfo(weight);
    _maxVertex = std::max(_maxVertex, std::max(from, to));
    _vertexes.insert(to);
    _vertexes.insert(from);
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: removeEdge(VertexType from, VertexType to) {
    delete buf[from][to];
    buf[from][to] = NO_VERTEX;
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: changeEdge(VertexType from, VertexType to, EdgeInfo info) {
    removeEdge(from, to);
    addEdge(from, to, info);
}

template <class EdgeInfo>
EdgeInfo CMatrixGraph<EdgeInfo>:: getEdgeInfo(VertexType from, VertexType to) {
    return *(buf[from][to]);
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>:: VertexType CMatrixGraph<EdgeInfo>::vertexCount() const {
    return _vertexes.size();
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::VertexType CMatrixGraph<EdgeInfo>::vertexMax() const {
    return _maxVertex;
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::EdgesCollection CMatrixGraph<EdgeInfo>:: getNextEdges(VertexType vertex) const{
    EdgesCollection nextVertexes;
    
    for (VertexType i = 0; i < buf[vertex].size(); ++i) {
        if (buf[vertex][i] != NO_VERTEX && i != vertex) {
            nextVertexes.push_back(Edge(vertex, i, *(buf[vertex][i])));
        }
    }
    
    return nextVertexes;
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::EdgesCollection CMatrixGraph<EdgeInfo>:: getPrevEdges(VertexType vertex) const {
    EdgesCollection prevVertexes;
    
    
    for (auto i = _vertexes.begin(); i != _vertexes.end(); ++i) {
        if (buf[*i][vertex] != NO_VERTEX && *i != vertex) {
            prevVertexes.push_back(Edge(vertex, *i, *(buf[*i][vertex])));
        }
    }
    
    return prevVertexes;
}

template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>::convertToGraph(IGraph<EdgeInfo> &newGraph) const {
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (VertexType j = 0; j < buf[i].size(); ++j) {
            if (buf[i][j] != NO_VERTEX) {
                newGraph.addEdge(i, j, *(buf[i][j]));
            }
        }
    }
}

template <class EdgeInfo>
std::vector<typename CMatrixGraph<EdgeInfo>:: VertexType> CMatrixGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

#endif

#include <assert.h>

typedef unsigned long long CapacityType;
typedef unsigned long long FlowType;
typedef unsigned long long PotentialType;

struct MPMNetworkEdgeInfo {
    CapacityType capacity;
    FlowType flow;
    PotentialType potential;
    
    MPMNetworkEdgeInfo(CapacityType capacity): capacity(capacity), flow(0), potential(INFINITY) {};
    MPMNetworkEdgeInfo(CapacityType capacity, FlowType flow): capacity(capacity), flow(flow), potential(INFINITY) {};
    MPMNetworkEdgeInfo(CapacityType capacity, FlowType flow, PotentialType potential): capacity(capacity), flow(flow), potential(potential) {};
    
    MPMNetworkEdgeInfo augmentingInfo() const {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(capacity - flow, flow, potential);
    }
    
    MPMNetworkEdgeInfo infoWithNewFlow(FlowType newFlow) {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(capacity, newFlow, potential);
    }
    
    MPMNetworkEdgeInfo infoWithNewCapacity(CapacityType newCapacity) {
        assert(capacity >= flow);
        return MPMNetworkEdgeInfo(newCapacity, flow, potential);
    }
    
    FlowType augmentingCapacity() {
        assert(capacity >= flow);
        return capacity - flow;
    }
    
    bool isSuitable() const {
        return flow - capacity;
    }
};

typedef IGraph<MPMNetworkEdgeInfo>::Edge MPMNetworkEdge;

class MPMNetworkGraph: public CMatrixGraph<MPMNetworkEdgeInfo> {
    
public:
    //    MPMNetworkGraph residualNetworkWithSource(VertexType source);
};


//MPMNetworkGraph MPMNetworkGraph::residualNetworkWithSource(VertexType source) {
//    MPMNetworkGraph residualNetwork;
//    auto addEdgeToResidualNetwork = [&residualNetwork](const MPMNetworkEdge edge) {
//        if (edge.info.isSuitable()) {
//            residualNetwork.addEdge(edge.from, edge.to, edge.info.augmentingInfo());
//        }
//    };
//
//    BFS(source, addEdgeToResidualNetwork);
//
//    return residualNetwork;
//}

#endif /* MPMNetworkGraph_h */

#define NOT_VISITED INT_MAX
#define VISITED (INT_MAX - 1)
template <class EdgeInfo>
using Edge = typename IGraph<EdgeInfo>:: Edge;
using VertexType = IGraph<>::VertexType;

class NetworkAlgorithmManager {
public:
    
    NetworkAlgorithmManager(MPMNetworkGraph &network): network(network) {
        distance = std::vector<VertexType>(network.vertexMax() + 1, NOT_VISITED);
        potential = std::vector<VertexType>(network.vertexMax() + 1);
        incPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
        outPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    };
    
    //    void findBlockingFlowInLayeredNetwork(MPMNetworkGraph &network);
    MPMNetworkGraph network;
    MPMNetworkGraph residualNetwork;
    
    MPMNetworkGraph getLayeredGraph(MPMNetworkGraph &network, VertexType source, VertexType sink);
    FlowType maxFlowWithMPMBlocking(const VertexType source, const VertexType sink);
private:
    
    FlowType maxFlow;
    
    std::vector<VertexType> distance;
    std::vector<VertexType> potential;
    std::vector<VertexType> incPotential;
    std::vector<VertexType> outPotential;
    
    void updatePotentials(MPMNetworkGraph &layeredNetwork, std::queue<VertexType> &updatingQueue);
    void findBlockingFlowInLayeredNetwork(MPMNetworkGraph &layeredNetwork, MPMNetworkGraph &originalNetwork, const VertexType source, const VertexType sink);
    
};
FlowType NetworkAlgorithmManager::maxFlowWithMPMBlocking(const VertexType source, const VertexType sink) {
    potential = std::vector<VertexType>(network.vertexMax() + 1);
    
    while (true) {
        auto layeredNetwork = getLayeredGraph(network, source, sink);
        
        if (distance[sink] == NOT_VISITED) {
            return maxFlow;
        }
        findBlockingFlowInLayeredNetwork(layeredNetwork, network, source, sink);
    }
    
    return maxFlow;
}
void NetworkAlgorithmManager:: updatePotentials(MPMNetworkGraph &layeredNetwork, std::queue<VertexType> &updatingQueue) {
    while (!updatingQueue.empty()) {
        auto currentVertex = updatingQueue.front();
        updatingQueue.pop();
        if (!(potential[currentVertex] == VISITED)) {
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            assert(potential[currentVertex] >= 0);
            if (potential[currentVertex] == 0) {
                potential[currentVertex] = VISITED;
                auto nextEdges = layeredNetwork.getNextEdges(currentVertex);
                auto prevEdges = layeredNetwork.getPrevEdges(currentVertex);
                for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                    layeredNetwork.removeEdge(it->from, it->to);
                    updatingQueue.push(it->to);
                }
                for (auto it = prevEdges.begin(); it != prevEdges.end(); ++it) {
                    layeredNetwork.removeEdge(it->from, it->to);
                    updatingQueue.push(it->from);
                }
            }
        }
    }
}

void NetworkAlgorithmManager:: findBlockingFlowInLayeredNetwork(MPMNetworkGraph &layeredNetwork, MPMNetworkGraph &residualNetwork, const VertexType source, const VertexType sink) {
    while (true) {
        auto minPotentialVertexIt = std::min_element(potential.begin(), potential.end());
        auto minPotential = potential[*minPotentialVertexIt];
        if (minPotential == VISITED) {
            return;
        }
        
        std::vector<VertexType> extraFlow(layeredNetwork.vertexMax() + 1, 0);
        std::queue<VertexType> vertexQueue;
        std::queue<VertexType> updatingQueue;
        vertexQueue.push(*minPotentialVertexIt);
        extraFlow[*minPotentialVertexIt] = potential[*minPotentialVertexIt];
        
        //forward pushing
        auto pushFlow = [&vertexQueue, &extraFlow, &minPotentialVertexIt, &layeredNetwork, &residualNetwork, &updatingQueue, &source, &sink, this](bool isFrontPushing) {
            std::vector<char> used(layeredNetwork.vertexMax() + 1, 0);
            while (!vertexQueue.empty()) {
                auto currentVertex = vertexQueue.front();
                vertexQueue.pop();
                if (!used[currentVertex]) {
                    used[currentVertex] = 1;
                    std::vector<MPMNetworkEdge> nextEdges;
                    if (isFrontPushing) {
                        nextEdges = layeredNetwork.getNextEdges(currentVertex);
                    } else {
                        nextEdges = layeredNetwork.getPrevEdges(currentVertex);
                    }
                    updatingQueue.push(currentVertex);
                    for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                        auto augmentingCapacity = it->info.capacity;
                        if (augmentingCapacity <= extraFlow[it->from]) {
                            residualNetwork.removeEdge(it->from, it->to);
                            layeredNetwork.removeEdge(it->from, it->to);
                            extraFlow[it->to] += augmentingCapacity;
                            extraFlow[it->from] -= augmentingCapacity;
                            outPotential[it->from] -= augmentingCapacity;
                            incPotential[it->to] -= augmentingCapacity;
                        } else {
                            auto newInfo = it->info.infoWithNewCapacity(it->info.capacity - extraFlow[it->from]);
                            residualNetwork.changeEdge(it->from, it->to, newInfo);
                            layeredNetwork.changeEdge(it->from, it->to, newInfo);
                            extraFlow[it->to] += extraFlow[it->from];
                            extraFlow[it->from] = 0;
                            outPotential[it->from] -= extraFlow[it->from];
                            incPotential[it->to] -= extraFlow[it->from];
                            break;
                        }
                        vertexQueue.push(it->to);
                    }
                }
            }
        };
        
        pushFlow(1);
        extraFlow[*minPotentialVertexIt] = minPotential;
        pushFlow(0);
        
        updatePotentials(layeredNetwork, updatingQueue);
    }
}

MPMNetworkGraph NetworkAlgorithmManager:: getLayeredGraph(MPMNetworkGraph &graph, VertexType source, VertexType sink) {
    distance = std::vector<VertexType>(network.vertexMax() + 1, NOT_VISITED);
    incPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    outPotential = std::vector<VertexType>(network.vertexMax() + 1, 0);
    MPMNetworkGraph layeredGraph;
    
    std::vector<VertexType> used(graph.vertexMax());
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
            auto nextEdges = graph.getNextEdges(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                if (distance[it->to] == NOT_VISITED) {
                    distance[it->to] = distance[currentVertex] + 1;
                }
                
                if (distance[it->to] == distance[currentVertex] + 1) {
                    if (it->info.capacity != it->info.flow) {
                        layeredGraph.addEdge(it->from, it->to, it->info);
                    }
                    incPotential[it->to] += it->info.capacity;
                    outPotential[it->from] += it->info.capacity;
                }
                vertexQueue.push(it->to);
            }
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            
#ifdef DEBUG
            std::cout<<"Potential for "<<currentVertex <<" is "<<potential[currentVertex] <<std::endl;
#endif
        }
    }
    
    return layeredGraph;
}






#endif /* NetworkFlowManager_hpp */

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >>n >>m;
    MPMNetworkGraph graph;
    for (int i = 0; i < n; ++i) {
        int from, to, capacity;
        std::cin>>from>>to>>capacity;
        graph.addEdge(from, to, MPMNetworkEdgeInfo(capacity));
    }
    NetworkAlgorithmManager manager = NetworkAlgorithmManager(graph);
    auto maxFlow = manager.maxFlowWithMPMBlocking(1, n);
    std::cout<<maxFlow<<std::endl;
    return 0;
}
