//
//  CMatrixGraph.h
//  
//
//  Created by Александр Малышев on 16.05.15.
//
//

#ifndef Graph_CMatrixGraph_h
#define Graph_CMatrixGraph_h

#define NO_VERTEX 0

#include <vector>
#include <unordered_set>

template <class EdgeInfo = unsigned long long>
class CMatrixGraph {
    
public:
    
    struct VertexType{
        unsigned long long vertex;
        bool checked;
        VertexType(unsigned long long vertex, bool checked) : vertex(vertex), checked(checked) {}
        VertexType(unsigned long long vertex) : vertex(vertex), checked(0) {}
    };
    
    struct VertexCollectionUnit{
        VertexType vertex;
        EdgeInfo info;
        VertexCollectionUnit(VertexType vertex, EdgeInfo info) : vertex(vertex), info(info) {}
    };
    
    typedef std::vector<VertexCollectionUnit> VertexCollection;
    
    CMatrixGraph();
    ~CMatrixGraph();
    
    
    void addEdge(VertexType from, VertexType to, EdgeInfo info = 1);
    VertexType vertexCount() const;
    VertexCollection getNextVertexes(VertexType vertex) const;
    VertexCollection getPrevVertexes(VertexType vertex) const;
    std::vector<VertexType> getAllVertexes() const;
    
    
private:
    
    std::vector<std::vector<EdgeInfo>> buf;
    std::unordered_set<VertexType> _vertexes;
};


template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: CMatrixGraph() {
    
}

template <class EdgeInfo>
CMatrixGraph<EdgeInfo>:: ~CMatrixGraph() {
    
}
template <class EdgeInfo>
void CMatrixGraph<EdgeInfo>:: addEdge(VertexType from, VertexType to, EdgeInfo weight) {
    
    if ( from.vertex >= buf.size() || to.vertex >= buf.size() ) {
        unsigned long long newSize = std::max(from.vertex, to.vertex) + 1;
        unsigned long long oldBufSize = buf.size();
        for (auto it = buf.begin(); it != buf.end(); ++it) {
            it->insert(it->end(), newSize - oldBufSize, NO_VERTEX);
        }
        buf.insert(buf.end(), newSize - oldBufSize, std::vector<EdgeInfo>(newSize, NO_VERTEX));
    }
    
    buf[from.vertex][to.vertex] = weight;
    
    _vertexes.insert(to);
    _vertexes.insert(from);
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>:: VertexType CMatrixGraph<EdgeInfo>::vertexCount() const {
    return _vertexes.size();
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::VertexCollection CMatrixGraph<EdgeInfo>:: getNextVertexes(VertexType vertex) const{
    VertexCollection nextVertexes;
    
    for (VertexType i = 0; i < buf[vertex].size(); ++i) {
        if (buf[vertex][i] != NO_VERTEX && i != vertex) {
            nextVertexes.push_back(VertexCollectionUnit(i, buf[vertex][i]));
        }
    }
    
    return nextVertexes;
}

template <class EdgeInfo>
typename CMatrixGraph<EdgeInfo>::VertexCollection CMatrixGraph<EdgeInfo>:: getPrevVertexes(VertexType vertex) const {
    VertexCollection prevVertexes;
    
    
    for (auto i = _vertexes.begin(); i != _vertexes.end(); ++i) {
        if (buf[*i][vertex] != NO_VERTEX && *i != vertex) {
            prevVertexes.push_back(VertexCollectionUnit(*i, buf[*i][vertex]));
        }
    }
    
    return prevVertexes;
}


template <class EdgeInfo>
std::vector<typename CMatrixGraph<EdgeInfo>:: VertexType> CMatrixGraph<EdgeInfo>:: getAllVertexes() const {
    std::vector<VertexType> vertexes(_vertexes.begin(), _vertexes.end());
    std::sort(vertexes.begin(), vertexes.end());
    return vertexes;
}


#endif
