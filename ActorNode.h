//
//  ActorNode.h
//  SixDegrees
//
//  Created by Xie kesong on 2/27/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef ActorNode_h
#define ActorNode_h

#include <iostream>
#include <string>
#include <vector>
#include "ActorEdge.h"

using namespace std;

/** The Node structure that defines an actor or actress.
 */
struct ActorNode{
    //the name of the actor/actress
    string name;
    
    vector<ActorEdge*> adj;
    
    ActorEdge* nextEdge;
    
    bool visited;
    
    ActorNode(string n) : name(n){
        visited = false;
        nextEdge = NULL;
    }
    
    
    bool operator ==(const ActorNode &other) const;
};

namespace std
{
    template <>
    struct hash<ActorNode>
    {
        size_t operator()(const ActorNode& actor) const
        {
            return hash<std::string>{}(actor.name);
        }
    };
}


#endif /* ActorNode_h */
