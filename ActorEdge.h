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
    /** the source actor of this edge
     */
    ActorNode* source;
    
    /** the destination actor of this edge
     */
    ActorNode* dest;
    
    /** the movie that connects the source actor and the destination actor
     */
    Movie* movie;
    
    
    /** the weight of the edge
     */
    int weight;
    
    /** constructor
     */
    ActorEdge(ActorNode* s, ActorNode* d, Movie* m) : source(s), dest(d), movie(m){
        weight = 1 + (2015 - movie->year);
    };
};



#endif /* ActorEdge_h */



