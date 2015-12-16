//
//  main.cpp
//  MaxFlow For Contest
//
//  Created by Alexander Malyshev on 28.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
typedef unsigned long long VertexType;
typedef long FlowType;
typedef long CapacityType;
#include <limits.h>
#include <set>
#include <queue>
#include <forward_list>
#include <vector>
#include <assert.h>

class Graph {
public:
    typedef std::forward_list<VertexType> VertexesCollection;
    
    Graph(const VertexType numberOfVertexes);
    virtual ~Graph() {}
    
    virtual void addEdge(const VertexType from, const VertexType to);
    virtual void removeEdge(const VertexType from, const VertexType to);
    
    virtual const VertexType vertexCount() const;
    virtual const VertexesCollection getNextVertexes(const VertexType vertex) const;
    virtual const VertexesCollection getPrevVertexes(const VertexType vertex) const;
    
    virtual void BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock);
    
private:
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
};

Graph:: Graph(const VertexType numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    _vertexCount = numberOfVertexes;
}

void Graph:: addEdge(const VertexType from, const VertexType to) {
    incomingVertexes[to].push_front(from);
    outcomingVertexes[from].push_front(to);
}

void Graph:: removeEdge(const VertexType from, const VertexType to) {
    assert((from < incomingVertexes.size()) && (to < outcomingVertexes.size()));
    incomingVertexes[to].remove_if([&from](const VertexType vertex) {
        return from == vertex;
    });
    outcomingVertexes[from].remove_if([&to](const VertexType vertex) {
        return to == vertex;
    });
}

const VertexType Graph:: vertexCount() const {
    return _vertexCount;
}

const typename Graph::VertexesCollection Graph:: getNextVertexes(const VertexType vertex) const {
    return outcomingVertexes[vertex];
}

const typename Graph::VertexesCollection Graph:: getPrevVertexes(const VertexType vertex) const {
    return incomingVertexes[vertex];
}

void Graph:: BFS(const VertexType start, const std::function<void(const VertexType from, const VertexType to)> completionBlock) {
    std::queue<VertexType> vertexQueue;
    std::vector<VertexType> used(vertexCount());
    vertexQueue.push(start);
    
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextEdges = getNextVertexes(currentVertex);
            for (auto it = nextEdges.begin(); it != nextEdges.end(); ++it) {
                vertexQueue.push(*it);
                completionBlock(currentVertex, *it);
            }
        }
    }
}


class FlowKeeper {
    
public:
    
    FlowKeeper(const VertexType numberOfVertexes);
    const FlowType flow(const VertexType from, const VertexType to) const;
    const CapacityType capacity(const VertexType from, const VertexType to) const;
    const CapacityType residualCapacity(const VertexType from, const VertexType to) const;
    void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
    void addFlow(const FlowType flow, const VertexType from, const VertexType to)
    void addCapacity(const CapacityType capacity, const VertexType from, const VertexType to);
private:
    std::vector<std::vector<FlowType>> _flow;
    std::vector<std::vector<CapacityType>> _capacity;
};

FlowKeeper:: FlowKeeper(const VertexType numberOfVertexes) {
    _flow = std::move(std::vector<std::vector<FlowType>>(numberOfVertexes, std::vector<FlowType>(numberOfVertexes)));
    _capacity = std::move(std::vector<std::vector<CapacityType>>(numberOfVertexes, std::vector<CapacityType>(numberOfVertexes)));
}

void FlowKeeper:: pushFlow(const FlowType flow, const VertexType from, const VertexType to) {
//    assert(_flow[from][to] + flow <= _capacity[from][to]);
    _flow[from][to] += flow;
    _flow[to][from] -= flow;
}

void FlowKeeper:: addFlow(const FlowType flow, const VertexType from, const VertexType to) {
    _flow[from][to] += flow;
}

void FlowKeeper:: addCapacity(const CapacityType capacity, const VertexType from, const VertexType to) {
    _capacity[from][to] += capacity;
}


const FlowType FlowKeeper:: flow(const VertexType from, const VertexType to) const {
    return _flow[from][to];
}

const CapacityType FlowKeeper:: capacity(const VertexType from, const VertexType to) const {
    return _capacity[from][to];
}

const CapacityType FlowKeeper:: residualCapacity(const VertexType from, const VertexType to) const {
    return _capacity[from][to] - _flow[from][to];
}

class Edge {
public:
    VertexType from;
    VertexType to;
    CapacityType capacity;
    Edge(VertexType from, VertexType to, CapacityType capacity): from(from), to(to), capacity(capacity) {}
};

class ResidualNetworkGraph: public Graph {
    
public:
    
    typedef std::forward_list<VertexType> VertexesCollection;
    
    ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink);
    
    virtual void addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity);
    virtual void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
    
    virtual void performCompletionBlockOnNextVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    virtual void performCompletionBlockOnPrevVertexes(const VertexType vertex, std::function<void(const VertexType from, const VertexType to)> completionBlock);
    
    virtual void print(const VertexType start);
    
    virtual const FlowType flow(const VertexType from, const VertexType to) { return flowKeeper->flow(from, to); }
    virtual const CapacityType capacity(const VertexType from, const VertexType to) { return flowKeeper->capacity(from, to); }
    virtual const CapacityType residualCapacity(const VertexType from, const VertexType to) { return flowKeeper->residualCapacity(from, to); }
    
    virtual const VertexType getSource() { return source; }
    virtual const VertexType getSink() { return sink; }
    
    virtual void printFlowOfEdges(std::vector<Edge> &edges);
    
protected:
    
    VertexType source;
    VertexType sink;
    
    std::vector<VertexesCollection> incomingVertexes;
    std::vector<VertexesCollection> outcomingVertexes;
    VertexType _vertexCount;
    std::shared_ptr<FlowKeeper> flowKeeper;
    
};

void ResidualNetworkGraph:: printFlowOfEdges(std::vector<Edge> &edges) {
    for (auto edge = edges.begin(); edge != edges.end(); ++edge) {
        auto flow = flowKeeper->flow(edge.from, edge.to);
        if (flow > flowKeeper->capacity(edge.from, edge.to)) {
            std::cout<<flowKeeper->capacity(edge.from, edge.to) <<std::endl;
            flowKeeper->addFlow(-flowKeeper->capacity(edge.from, edge.to));
        } else {
            if (flow >= 0) {
                std::cout<< flow <<std::endl;
            } else {
                std::cout<<0 <<std::endl;
            }
            std::cout<<flow<<std::endl;
        }
    }
}

ResidualNetworkGraph:: ResidualNetworkGraph(const VertexType numberOfVertexes, const VertexType source, const VertexType sink): Graph(numberOfVertexes) {
    incomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    outcomingVertexes = std::move(std::vector<VertexesCollection>(numberOfVertexes));
    flowKeeper = std::make_shared<FlowKeeper>(numberOfVertexes);
    _vertexCount = numberOfVertexes;
    this->source = source;
    this->sink = sink;
}

void ResidualNetworkGraph:: addEdge(const VertexType from, const VertexType to, const FlowType flow, const CapacityType capacity) {
    if ((flowKeeper->capacity(from, to) == 0 && flowKeeper->capacity(to, from) == 0)) {
        Graph::addEdge(from, to);
        Graph::addEdge(to, from);
    }
    flowKeeper->addCapacity(capacity, from, to);
    flowKeeper->pushFlow(flow, from, to);
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



class LayeredNetworkGraph: public Graph {
    
public:
    LayeredNetworkGraph(const VertexType numberOfVertexes) = delete;
    LayeredNetworkGraph(ResidualNetworkGraph *residualNetwork): Graph(residualNetwork->vertexCount()), residualNetwork(residualNetwork), source(residualNetwork->getSource()), sink(residualNetwork->getSink()) {
//        NOT_REACHED = std::numeric_limits<VertexType>::max();
        NOT_REACHED = 18446744073709551615;
//        MAX_POTENTIAL = std::numeric_limits<CapacityType>::max();
        MAX_POTENTIAL = 9223372036854775807;
        init();
    }
    
    void getBlockingFlow();
    bool sinkReachable();
    
    void print(const VertexType start);
private:
    VertexType NOT_REACHED;
    CapacityType MAX_POTENTIAL;
    
    void pushFront(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void pushBackward(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void pushWithDirection(bool isFront, const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate);
    void updatePotentials(std::set<VertexType> &vertexesToUpdate);
    
    
    VertexType source;
    VertexType sink;
    void init();
    ResidualNetworkGraph *residualNetwork;
    std::vector<VertexType> distance;
    std::vector<CapacityType> incPotential;
    std::vector<CapacityType> outPotential;
    std::vector<CapacityType> potential;
    std::vector<FlowType> extraFlow;
};



bool LayeredNetworkGraph:: sinkReachable() {
    return distance[sink] != NOT_REACHED;
}

void LayeredNetworkGraph:: init() {
    distance = std::vector<VertexType>(residualNetwork->vertexCount(), NOT_REACHED);
    incPotential = std::vector<CapacityType>(residualNetwork->vertexCount(), 0);
    outPotential = std::vector<CapacityType>(residualNetwork->vertexCount(), 0);
    potential = std::vector<CapacityType>(residualNetwork->vertexCount(), MAX_POTENTIAL);
    extraFlow = std::vector<FlowType>(residualNetwork->vertexCount(), 0);
    std::vector<VertexType> used(residualNetwork->vertexCount());
    std::queue<VertexType>  vertexQueue;
    
    incPotential[source] = MAX_POTENTIAL;
    outPotential[sink] = MAX_POTENTIAL;
    
    vertexQueue.push(source);
    distance[source] = 0;
    while (!vertexQueue.empty()) {
        VertexType currentVertex = vertexQueue.front();
        vertexQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            residualNetwork->performCompletionBlockOnNextVertexes(currentVertex, [this, &vertexQueue](const VertexType from, const VertexType to) {
                if (distance[to] == NOT_REACHED) {
                    distance[to] = distance[from] + 1;
                }
                if (distance[to] == distance[from] + 1) {
                    this->addEdge(from, to);
                    incPotential[to] += residualNetwork->residualCapacity(from, to);
                    outPotential[from] += residualNetwork->residualCapacity(from, to);
                }
                vertexQueue.push(to);
            });
            
            potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
            
#ifdef DEBUG
            std::cout<<"Potential for "<<currentVertex <<" is "<<potential[currentVertex] <<std::endl;
#endif
        }
    }
}

void LayeredNetworkGraph:: getBlockingFlow() {
    while (potential[source] != MAX_POTENTIAL && potential[sink] != MAX_POTENTIAL) {
        std::set<VertexType> vertexesToDelete;
        auto getIndexOfMinElement = [](const std::vector<CapacityType>& v) -> VertexType {
            CapacityType min = v[0];
            VertexType minIndex = 0;
            for (VertexType i = 1; i < v.size(); ++i) {
                if (min > v[i]) {
                    min = v[i];
                    minIndex = i;
                }
            }
            return minIndex;
        };
        
        VertexType vertexWithMinPotential = getIndexOfMinElement(potential);
        auto flowToPush = potential[vertexWithMinPotential];
        pushFront(flowToPush, vertexWithMinPotential, vertexesToDelete);
        pushBackward(flowToPush, vertexWithMinPotential, vertexesToDelete);
        updatePotentials(vertexesToDelete);
    }
}

void LayeredNetworkGraph:: pushFront(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(1, flow, vertexWithMinPotential, vertexesToUpdate);
}

void LayeredNetworkGraph:: pushBackward(const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {
    pushWithDirection(0, flow, vertexWithMinPotential,vertexesToUpdate);
}

void LayeredNetworkGraph:: pushWithDirection(bool isFront, const CapacityType flow, const VertexType vertexWithMinPotential, std::set<VertexType> &vertexesToUpdate) {
    
    std::queue<VertexType> pushingQueue;
    std::vector<char> used(vertexCount(), 0);
    extraFlow[vertexWithMinPotential] = flow;
    pushingQueue.push(vertexWithMinPotential);
    
    while (!pushingQueue.empty()) {
        auto currentVertex = pushingQueue.front();
        pushingQueue.pop();
        if (!used[currentVertex]) {
            used[currentVertex] = 1;
            auto nextVertexes = (isFront ? getNextVertexes(currentVertex) : getPrevVertexes(currentVertex));
            for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
#ifdef DEBUG
                std::cout<<"FROM: "<<currentVertex <<" TO: "<<*it <<std::endl;
#endif
                VertexType to, from;
                if (isFront) {
                    from = currentVertex;
                    to = *it;
                    if (!(distance[*it] == (distance[currentVertex] + 1))) {
                        continue;
                    }
                } else {
                    from = *it;
                    to = currentVertex;
                    if (!(distance[*it] + 1 == (distance[currentVertex]))) {
                        continue;
                    }
                }
                
                FlowType pushingFlow;
                auto residualCapacity = residualNetwork->residualCapacity(from, to);
                if (residualCapacity <= 0) {
                    continue;
                }
                if (residualCapacity <= extraFlow[currentVertex]) {
                    pushingFlow = residualCapacity;
                } else {
                    pushingFlow = extraFlow[currentVertex];
                }
                
                residualNetwork->pushFlow(pushingFlow, from, to);
                if (isFront) {
                    outPotential[currentVertex] -= pushingFlow;
                    incPotential[to] -= pushingFlow;
                    extraFlow[to] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(to);
                } else {
                    incPotential[currentVertex] -= pushingFlow;
                    outPotential[from] -= pushingFlow;
                    extraFlow[from] += pushingFlow;
                    extraFlow[currentVertex] -= pushingFlow;
                    pushingQueue.push(from);
                }
#ifdef DEBUG
                std::cout<<"Pushed "<<pushingFlow <<" from " << currentVertex <<"to "<<*it<<std::endl;
#endif
                
                if (extraFlow[currentVertex] == 0) {
                    break;
                }
            }
            vertexesToUpdate.insert(currentVertex);
        }
    }
}

void LayeredNetworkGraph:: updatePotentials(std::set<VertexType> &vertexesToUpdate) {
    while (!vertexesToUpdate.empty()) {
        auto currentVertex = *vertexesToUpdate.begin();
        vertexesToUpdate.erase(currentVertex);
        potential[currentVertex] = std::min(incPotential[currentVertex], outPotential[currentVertex]);
        if (potential[currentVertex] <= 0) {
            potential[currentVertex] = MAX_POTENTIAL;
            auto nextVertexes = getNextVertexes(currentVertex);
            auto prevVertexes = getPrevVertexes(currentVertex);
            for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
                removeEdge(currentVertex, *it);
                vertexesToUpdate.insert(*it);
                incPotential[*it] -= residualNetwork->residualCapacity(currentVertex, *it);
            }
            for (auto it = prevVertexes.begin(); it != prevVertexes.end(); ++it) {
                removeEdge(*it, currentVertex);
                vertexesToUpdate.insert(*it);
                outPotential[*it] -= residualNetwork->residualCapacity(*it, currentVertex);
            }
        }
    }
}

void LayeredNetworkGraph:: print(const VertexType start) {
    BFS(start, [this](const VertexType from, const VertexType to) {
        std::cout<<from<<"->"<<to<<" ("<<residualNetwork->flow(from, to)<<"/"<<residualNetwork->capacity(from, to) <<")"<<std::endl;
    });
}


class MKMMaxFlowManager {
public:
    MKMMaxFlowManager(ResidualNetworkGraph *residualNetwork): residualNetwork(residualNetwork) {};
    const VertexType getMaxFlow();
private:
    ResidualNetworkGraph *residualNetwork;
};

const VertexType MKMMaxFlowManager:: getMaxFlow() {
    while (true) {
        auto layeredGraph = LayeredNetworkGraph(residualNetwork);
        
#ifdef DEBUG
        std::cout<<"layered graph created"<<std::endl;
        layeredGraph.print(residualNetwork->getSource());
#endif
        
        if (!(layeredGraph.sinkReachable())) {
            break;
        }
        
        layeredGraph.getBlockingFlow();
#ifdef DEBUG
        std::cout<<"Blocking path added"<<std::endl;
        residualNetwork->print(residualNetwork->getSource());
#endif
    }
    FlowType maxFlow = 0;
    auto sourceAdjEdges = residualNetwork->getNextVertexes(residualNetwork->getSource());
    for (auto it = sourceAdjEdges.begin(); it != sourceAdjEdges.end(); ++it) {
        maxFlow += residualNetwork->flow(residualNetwork->getSource(), *it);
    }
    return maxFlow;
}

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int n, m;
    std::vector<Edge> edgesToPrint;
    std::cin>>n >>m;
    
    auto residual = new ResidualNetworkGraph(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        std::cin>>from;
        std::cin>>to;
        std::cin>>capacity;
        residual->addEdge(from - 1, to - 1, 0, capacity);
        edgesToPrint.push_back(Edge(from - 1, to - 1, capacity));
        //        if (from == 0 && to == 1) {
        //            residual->pushFlow(1, edge);
        //        }
    }
//    std::cout<<"Я ЗАКОНЧИЛ ВВОД"<<std::endl;
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
    residual->printFlowOfEdges(edgesToPrint);
    delete residual;
    return 0;
}
