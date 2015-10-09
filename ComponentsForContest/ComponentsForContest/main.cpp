//
//  main.cpp
//  ComponentsForContest
//
//  Created by Александр Малышев on 10.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

class IGraph {
    
public:
    
    typedef unsigned long long VertexType;
    typedef long long VertexWeight;
    struct VertexCollectionUnit {
        VertexType vertex;
        VertexCollectionUnit(VertexType vertex): vertex(vertex) {}
    };
    
    typedef std::vector<VertexCollectionUnit> VertexCollection;
    
    virtual ~IGraph() {}
    
    virtual void addEdge(VertexType from, VertexType to, VertexWeight weight = 1) = 0;
    virtual VertexType vertexCount() const = 0;
    virtual VertexCollection getNextVertexes(VertexType vertex) const = 0;
    virtual std::vector<VertexType> getAllVertexes() const = 0;
    
};

#include <unordered_set>
#include <unordered_map>

class CSetGraph: public IGraph {
    
public:
    
    CSetGraph();
    ~CSetGraph();
    
    
    void addEdge(VertexType from, VertexType to, VertexWeight weight = 1);
    VertexType vertexCount() const;
    VertexCollection getNextVertexes(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
private:
    typedef std::unordered_set<VertexType> VertexBufUnit;
    std::vector<VertexBufUnit> buf;
    std::unordered_set<VertexType> _vertexes;
};

///Crutch:                                            /////    /|
typedef CSetGraph::VertexType VertexType;             /////   /_|
typedef CSetGraph::VertexCollection VertexCollection; /////    |
typedef CSetGraph::VertexWeight VertexWeight;         /////    |

CSetGraph:: CSetGraph() {
}

CSetGraph:: ~CSetGraph() {
    
}

void CSetGraph:: addEdge(VertexType from, VertexType to, VertexWeight weight) {
    if ( from >= buf.size() || to >= buf.size() ) {
        VertexType newSize = std::max(from, to) + 1;
        VertexType oldBufSize = buf.size();
        buf.insert(buf.end(), newSize - oldBufSize, VertexBufUnit());
    }
    buf[from].insert(to);
    _vertexes.insert(to);
    _vertexes.insert(from);
}

VertexType CSetGraph::vertexCount() const {
    return _vertexes.size();
}

VertexCollection CSetGraph::getNextVertexes(VertexType vertex) const {
    VertexCollection nextVertexes;
    
    for (auto i = buf[vertex].begin(); i != buf[vertex].end(); ++i) {
        nextVertexes.push_back(VertexCollectionUnit(*i));
    }
    
    return nextVertexes;
}

std::vector<VertexType> CSetGraph:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}

void DFS(const CSetGraph& graph, int vertex, std::vector<char> &visited, int& vertInComp) {
    visited[vertex] = 1;
    
    auto next = graph.getNextVertexes(vertex);
    for (auto i = next.begin(); i != next.end(); ++i) {
        if (!visited[i->vertex]) {
            ++vertInComp;
            DFS(graph, i->vertex, visited, vertInComp);
        }
    }
}


int main(int argc, const char * argv[]) {
    int vertexes, edges, to, from;
    CSetGraph graph;
    std::cin>>vertexes >>edges;
    for (int i = 0; i < edges; ++i) {
        std::cin>>from >> to;
        graph.addEdge(from, to);
        graph.addEdge(to, from);
    }
    
    
    int numOfComps = 0;
    int maxComp = -1;
    std::vector<char> visited(graph.vertexCount(), 0);
    for (int i = 0; i < graph.vertexCount(); ++i) {
        int verInComp = 1;
        if (!visited[i]) {
            DFS(graph, i, visited, verInComp);
            ++numOfComps;
        }
        maxComp = std::max(maxComp, verInComp);
    }
    
    std::cout<<numOfComps << " " << maxComp <<std::endl;
    
    return 0;
}
