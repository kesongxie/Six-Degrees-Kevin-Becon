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


/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */


class ActorGraph {
protected:
    /** The connections between two actors and edges representation in the graph
     * the key is the name representation for the actor/actress
     * the value is the pointer for the ActorNode object
     */
    unordered_map<string, ActorNode*> vertices;
    
    /** The movie that in the graph
     *  The key is the movie as a string representation
     *  The value is the a pointer for a Movie object
     */
    unordered_map<string, Movie*> movies;
    
    /** number of edges
     */
    long long numberOfEdges = 0;
    
    
public:
    
    /** constructor
     */
    ActorGraph(void){};
    
    /** build the graph
     *  @param argc : the number of command line arguments
     *  @param argv : the command line arguments
     */
    int buildGraph(int argc, char** argv);

    /**  Load the graph from a tab-delimited file of actor->movie relationships.
     *  @param in_filename :  input filename
     *  @param use_weighted_edges : if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *  @return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(string in_filename, bool use_weighted_edges);
    
    
    /** add the actor to the graph
     *  @param actor_name : the name of the actor
     *  @param movie_title : the title of the movie
     *  @param movie_year : the year of the movie
     */
    void addActor(string actor_name, string movie_title, int movie_year);
    
    
    
    /** genearte the shortest path
     *  @param from_actor : the start actor vertex
     *  @param to_actor : the destination actor vertex
     *  @param outfile : the outpunt file for storing the shortest path
     */
    void shorestPath(string from_actor, string to_actor, ofstream &outfile);
    
    
    
    /** genearte the shortest path for weighted edges
     *  @param from_actor : the start actor vertex
     *  @param to_actor : the destination actor vertex
     *  @param outfile : the outpunt file for storing the shortest path
     */
    void shorestPathWeighted(string from_actor, string to_actor, ofstream &outfile);

    
    
};


#endif // ACTORGRAPH_H
