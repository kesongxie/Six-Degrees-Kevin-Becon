//
//  DisjointSet.h
//  SixDegrees
//
//  Created by Xie kesong on 3/12/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef DisjointSet_h
#define DisjointSet_h

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include "ActorNodeDJS.h"

class DisjointSet{
    
    
private:
    /** actor node, the key is the actor name, the value is the pointer to the actor node
     */
    unordered_map<string, ActorNodeDJS*> actors;
    
    
    /** the key is movie encoding string, the value is pointer to the sentinel node of
     *  a uptree
     */
    unordered_map<string, ActorNodeDJS*> movies;
    
    
    /** group the cast entry by year.
     *  the key is the year of the movie
     *  the pair contains the pair which its first entry is the actor name, and the
     *  second entry is the title of the movie
     */
    map<int, vector<pair<string, string>>> yearGroup;

    
    /** read from the movie cast file and instantiate necessary member properties
     *  @param in_filename : input filename
     */
    void loadFromFileActorConnectionUnionFind(string in_filename);

    /** search actor connection using union find/disjoint set
     *  @param test_pair_filename : filename for test pair file
     *  @param output_filename : filename for the output file
     */
    int searchActorConnectionsUnionFind(string test_pair_filename, string output_filename);
    
    /** see whether two actor node connected or not
     *  @param first : first actor
     *  @param second : second actor
     */
    bool find(ActorNodeDJS* first, ActorNodeDJS* second);
    
public:
    /** find the connection using union find
     *  @param in_filename : input filename
     *  @param test_pair_filename : test pair filename
     *  @param output_filename : output filename
     */
    void actorConnectionUnionFind(string in_filename, string test_pair_filename, string output_filename);

    
};

#endif /* DisjointSet_h */
