//
//  NetworkEdgeInfoWithID.h
//  SmartGraphs
//
//  Created by Alexander Malyshev on 06.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef NetworkEdgeInfo_h
#define NetworkEdgeInfo_h

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





#endif /* NetworkEdgeInfoWithID_h */
