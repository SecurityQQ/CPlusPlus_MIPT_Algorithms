//
//  main.cpp
//  TopologicalSortForContest
//
//  Created by Александр Малышев on 09.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//


#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
typedef unsigned int ull;


#define NO_VERTEX 0

class IGraph {
    
public:
    
    typedef unsigned int VertexType;
    typedef int VertexWeight;
    typedef VertexType VertexCollectionUnit;
    typedef std::vector<VertexCollectionUnit> VertexCollection;
    
    virtual ~IGraph() {}
    
    virtual void addEdge(VertexType from, VertexType to, VertexWeight weight = 1) = 0;
    virtual VertexType vertexCount() const = 0;
    
    virtual void convertToGraph(IGraph &newGraph) const = 0; //how to re-create IGraph ???
};


#include <unordered_map>
#include <unordered_set>

class CSetGraph: public IGraph {
    
public:
    
    CSetGraph();
    ~CSetGraph();
    
    
    void addEdge(VertexType from, VertexType to, VertexWeight weight = 1);
    VertexType vertexCount() const;
    std::unordered_set<VertexType>& getNextVertexes(VertexType vertex);
    
    void convertToGraph(IGraph &newGraph) const;
    
private:
    typedef std::unordered_set<VertexType> VertexBufUnit;
    std::vector<VertexBufUnit> buf;
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
}

VertexType CSetGraph::vertexCount() const {
    return buf.size();
}

std::unordered_set<VertexType>& CSetGraph::getNextVertexes(VertexType vertex) {
    return buf[vertex];
}

void CSetGraph:: convertToGraph(IGraph &newGraph) const {
    for (VertexType i = 0; i < buf.size(); ++i) {
        for (auto j = buf[i].begin(); j != buf[i].end(); ++j) {
            newGraph.addEdge(i, *j);
        }
    }
}

void DFS(CSetGraph& graph, std::vector<ull> &topSorted, ull u, std::vector<char> &visited) {
    visited[u] = 1;
    auto nextVertexes = graph.getNextVertexes(u);
    for (auto i = nextVertexes.begin(); i != nextVertexes.end(); ++i) {
        if (!visited[*i]) {
            DFS(graph, topSorted, *i, visited);
        }
    }
    topSorted.push_back(u);
}

std::vector<ull> topologicalSort(CSetGraph& g) {
    std::vector<ull> topSorted;
    
    ull tempVert = g.vertexCount();
    for (ull i = 0; i < tempVert; ++i) {
        g.addEdge(tempVert, i);
    }
    std::vector<char> visited(g.vertexCount(), 0);
    
    DFS(g, topSorted, tempVert, visited);
    
    topSorted.pop_back();
    std::reverse(topSorted.begin(), topSorted.end());
    return topSorted;
}


int main(int argc, const char * argv[]) {
    CSetGraph g;
    ull vertexes, edges;
    ull from, to;
    ull n, foo;
    std::cin>>vertexes >> edges;
    for (ull i = 0; i < edges; ++i) {
        std::cin>> from >> to;
        g.addEdge(from, to);
    }
    std::vector<ull> sorted = topologicalSort(g);
    
    std::cin>>n;
    for (ull i = 0; i < n; ++i) {
        std::cin>>foo;
        for (ull i = 0; i < g.vertexCount(); ++i) {
            if (sorted[i] == foo) {
                std::cout<<i << " ";
            }
        }
    }
    //    for (auto i = sorted.begin(); i != sorted.end(); ++i) {
    //        std::cout << *i << std::endl;
    //    }
    
    return 0;
}
