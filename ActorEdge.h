//
//  ActorEdge.h
//  SixDegrees
//
//  Created by Xie kesong on 2/27/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef ActorEdge_h
#define ActorEdge_h

#include <iostream>
#include "Movie.h"


struct ActorNode;

struct ActorEdge{
    ActorNode* source;
    ActorNode* dest;
    Movie* movie;
    ActorEdge(ActorNode* s, ActorNode* d, Movie* m) : source(s), dest(d), movie(m){};
};

#endif /* ActorEdge_h */
