//
//  main.cpp
//  Govnokod-New-Era
//
//  Created by Alexander Malyshev on 20.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <queue>
#include <memory.h>


//std::vector<int> distance;
//
//int buildLevelGraph(int source, int sink) {
//    std::queue<int> queue;
//    memset(&distance, 0, sizeof(distance));
//    queue.push(source);
//    distance[source] = 1;
//    while (!queue.empty()) {
//        int currentVertex = queue.front();
//        queue.pop();
//        auto nextVertexes = getNextVertexes(currentVertex);
//        for (auto it = nextVertexes.begin(); it != nextVertexes.end(); ++it) {
//    }
//}
//
//int dinic(int source, int sink) {
//    int flow = 0;
//    while (buildLevelGraph(source, sink)) {
//        flow += constructBlockingFlow(source, sink);
//    }
//}



int main() {
    unsigned long long a = 0;
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
            for (int k = 0; k < 500; ++k) {
                ++a;
            }
        }
    }
    return 0;
}