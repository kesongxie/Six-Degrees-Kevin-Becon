//
//  ActorNodeDJS.h
//  SixDegrees
//
//  Created by Xie kesong on 3/13/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef ActorNodeDJS_h
#define ActorNodeDJS_h

#include <iostream>
#include <string>


using namespace std;

/** The Node structure that defines an actor or actress.
 */
struct ActorNodeDJS{
    /** the name of the actor/actress
     */
    string name;
    
    /** the up reference in the uptree
     */
    ActorNodeDJS* up;
    
    
    /** when the actor originally not union with other nodes in a uptree,
     *  then the this actor node itself will be a sentinel Node
     */
    bool isSentinelNode;
    
    
    /** size of the up tree, default value is 1, which indicates the actor node
     *  the value of this uptree size will be updated as there are more actor nodes added to
     *  this up tree.
     */
    long long upTreeSize;
    
    
    /** constructor
     */
    ActorNodeDJS(string n) : name(n), up(NULL), isSentinelNode(true), upTreeSize(1){}
    
    /** get the sentinel node pointer
     */
    pair<ActorNodeDJS*, long long>  getSentinelNode(){
        if(isSentinelNode){
            return pair<ActorNodeDJS*, long long>(this, upTreeSize);
        }else{
            ActorNodeDJS* sentinelNode = this;
            while(!sentinelNode->isSentinelNode){
                sentinelNode = sentinelNode->up;
            }
            return pair<ActorNodeDJS*, long long>(sentinelNode, sentinelNode->upTreeSize);
        }
    }

    /** reset actor state
     */
    void reset(){
        up = NULL;
        isSentinelNode = true;
        upTreeSize = 1;
    }
    
    
    
};


#endif /* ActorNodeDJS_h */
