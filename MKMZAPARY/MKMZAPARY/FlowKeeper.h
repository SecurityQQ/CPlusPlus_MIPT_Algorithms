//
//  FlowKeeper.h
//  MKMZAPARY
//
//  Created by Alexander Malyshev on 23.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef FlowKeeper_h
#define FlowKeeper_h
#include "Constants.h"
class FlowKeeper {
    
public:
    
    FlowKeeper(const VertexType numberOfVertexes);
    const FlowType flow(const VertexType from, const VertexType to) const;
    const CapacityType capacity(const VertexType from, const VertexType to) const;
    const CapacityType residualCapacity(const VertexType from, const VertexType to) const;
    void pushFlow(const FlowType flow, const VertexType from, const VertexType to);
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
    assert(_flow[from][to] + flow <= _capacity[from][to]);
    _flow[from][to] += flow;
    _flow[to][from] -= flow;
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

#endif /* FlowKeeper_h */
