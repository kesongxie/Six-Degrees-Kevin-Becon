//
//  MinCostEdgeWrapper.h
//  SixDegrees
//
//  Created by Xie kesong on 3/8/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef MinCostEdgeWrapper_h
#define MinCostEdgeWrapper_h

#include <iostream>
#include <string>
#include "ActorEdge.h"

using namespace std;

struct MinCostEdgeWrapper{
    //the destination actor name
    string actor_name;
    
    //the currrent minimum cost from source to this actor
    int min_weight;
    
    //the previous edge for arriving this minimum cost
    ActorEdge* prev_edge;
    
    MinCostEdgeWrapper(string n, int w, ActorEdge* e): actor_name(n), min_weight(w), prev_edge(e){};

};

class MinCostEdgeWrapperComp {
public:
    bool operator()(MinCostEdgeWrapper& lhs, MinCostEdgeWrapper& rhs) const {
        return lhs.min_weight > rhs.min_weight;
    }
};




#endif /* MinCostEdgeWrapper_h */
