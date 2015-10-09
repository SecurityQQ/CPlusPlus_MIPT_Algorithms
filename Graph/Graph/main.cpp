//
//  main.cpp
//  Graph
//
//  Created by Александр Малышев on 04.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "IGraph.h"
#include "CMatrixGraph.h"
#include "CListGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"
#include <unordered_map>
#include <unordered_set>
#include <map>

int main(int argc, const char * argv[]) {
//    CSetGraph<> graph;
//    
//    graph.addEdge(1, 0);
//    graph.addEdge(0, 1);
//    graph.addEdge(1, 2);
//    graph.addEdge(2, 1);
//    graph.addEdge(3, 1);
//    graph.addEdge(1, 3);
//    graph.addEdge(4, 5);
//    graph.addEdge(5, 4);
//    
//    
//    IGraph<>::VertexCollection col = graph.getPrevVertexes(1);
//    
//    for (int i = 0 ; i < col.size(); ++i ) {
//        std::cout<< col[i].vertex <<std::endl;
//    }
//    
//    std::cout<<graph.vertexCount();
//
    
    CMatrixGraph<float> a;
    a.addEdge(0, 1, 1);
    a.addEdge(1, 0, 2);
    a.getNextVertexes(1);
    
    
    return 0;
}
