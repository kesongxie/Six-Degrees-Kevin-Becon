/*
 * ActorGraph.h
 * Author: Kesong Xie
 * Date:   Feb 27, 2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "ActorNode.h"

using namespace std;

class ActorGraph {
protected:
    /** The connections between two actors and edges representation in the graph
     * the key is the name representation for the actor/actress
     */
    unordered_map<string, ActorNode*> vertices;
    
    /** The movie that in the graph
     *  The key is the movie object
     *  The value is an unordered_set of a actor's name
     */
    unordered_map<string, Movie*> movies;
    
    
public:
    
    ActorGraph(void);

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(string in_filename, bool use_weighted_edges);
    
    
    /** add the actor to the graph
     */
    void addActor(string actor_name, string movie_title, int movie_year);
    
    
    /** build the graph
     */

    int buildGraph(int argc, char** argv);
    
    
    /** output the shortest path
     */
    void shorestPath(string from_actor, string to_actor, ofstream &outfile);
    
    
    
  
};


#endif // ACTORGRAPH_H
