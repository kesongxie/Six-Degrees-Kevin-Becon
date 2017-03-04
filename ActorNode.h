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
    /** the name of the actor/actress
     */
    string name;
    
    /** the adjacent edges for connected actors with this current actor
     */
    vector<ActorEdge*> adj;
    
    /** constructor
     */
    ActorNode(string n) : name(n){}
};




#endif /* ActorNode_h */
