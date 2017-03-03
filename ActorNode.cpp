//
//  ActorNode.cpp
//  SixDegrees
//
//  Created by Xie kesong on 2/27/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include "ActorNode.h"

bool ActorNode::operator ==(const ActorNode& actor) const{
    return  name == actor.name;
}
