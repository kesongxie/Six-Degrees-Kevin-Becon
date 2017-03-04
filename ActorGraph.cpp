/*
 * ActorGraph.cpp
 * Author: Kesong Xie
 * Date:   Feb 27, 2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "ActorGraph.h"
#include "ActorEdge.h"


using namespace std;


/** build the graph
 *  @param argc : the number of command line arguments
 *  @param argv : the command line arguments
 */
int ActorGraph::buildGraph(int argc, char** argv){
    
    if(argc < 5){
        cerr << "Usage: ./pathfinder movie_casts.tsv u test_pairs.tsv out_paths_unweighted.tsv" << endl;
        return -1;
    }
    
    //get hhe cats file name
    string mov_cast_filename = *(++argv);
    if(mov_cast_filename.length() < 1){
        return -1;
    }
    
    //get the weighted or unweighted option
    string weightedString = *(++argv);
    if(weightedString != "w" && weightedString != "u"){
        cerr << "the option should be 'w' (weighted) or 'u'(unweighted) only" << endl;
        return -1;
    }
    
    bool weighted = (weightedString == "w");
    
    //get the test pair filename
    string test_pair_filename = *(++argv);
    
    //get the output file name
    string output_filename = *(++argv);
    
    //load actors from the cast and build the graph
    loadFromFile(mov_cast_filename, weighted);
    
    ifstream readPairFile(test_pair_filename);
    ofstream outputFile(output_filename);
    
    if(!outputFile.is_open()){
        cerr << "Can't write to file: " << output_filename << endl;
        return -1;
    }
    
    if(readPairFile.is_open()){
        bool have_header = false;
        
        // keep reading lines until the end of file is reached
        outputFile << "(actor)--[movie#@year]-->(actor)--..." << endl;
        
        while (readPairFile) {
            string s;
            
            // get the next line
            if (!getline( readPairFile, s )) break;
            
            if (!have_header) {
                // skip the header
                have_header = true;
                continue;
            }
            
            istringstream ss( s );
            vector <string> record;
            
            while (ss) {
                string next;
                
                // get the next string before hitting a tab character and put it in 'next'
                if (!getline( ss, next, '\t' )) break;
                
                record.push_back( next );
            }
            
            if (record.size() != 2) {
                // we should have exactly 3 columns
                continue;
            }
            
            string first_actor(record[0]);
            string second_actor(record[1]);
            shorestPath(first_actor, second_actor, outputFile);
        }
        
        
        cout << "Actors nodes: " << vertices.size() << endl;
        cout << "Movies: " << movies.size() << endl;
        cout << "Edges: " << numberOfEdges << endl;

        
        
        
    }else{
        cerr << "Can't open and read from file: " << test_pair_filename << endl;
    }
    
    return 0;
}



/**  Load the graph from a tab-delimited file of actor->movie relationships.
 *  @param in_filename :  input filename
 *  @param use_weighted_edges : if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
 *  @return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(string in_filename, bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
        //add the actor and necessary relationship to the graph
        addActor(actor_name, movie_title, movie_year);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}


/** add the actor to the graph
 *  @param actor_name : the name of the actor
 *  @param movie_title : the title of the movie
 *  @param movie_year : the year of the movie
 */
void ActorGraph::addActor(string actor_name, string movie_title, int movie_year){
    //check whether the given actor with the name existed in the graph or not
    unordered_map<string, ActorNode*>::iterator v_itr = vertices.find(actor_name);
    //check whether this given actor node is already a vertex in the graph or not
    if(v_itr == vertices.end()){
        ActorNode* actor = new ActorNode(actor_name);
        vertices[actor_name] = actor;
    }
    
    //check whether this movie existed or not
    string mov_key = Movie::getMapKeyFromTitleAndYear(movie_title, movie_year);
    
    unordered_map<string, Movie*>::iterator mov_itr = movies.find(mov_key);
    if(mov_itr != movies.end()){
        //The movie exsited already
        //check whether the actor is already in the movie or not to
        //prevent duplicate inserting the same actor with the same movie
        
        Movie* mov = mov_itr->second;
        
        unordered_set<string>& act_in_mov = mov->act_in;
        if(act_in_mov.find(actor_name) == act_in_mov.end()){
            //the actor is not yet being added to the movie, add it
            for(auto act_itr = act_in_mov.begin(); act_itr != act_in_mov.end(); ++act_itr){
                //create an undirected edges between the two actors
                ActorEdge* edgeA = new ActorEdge(vertices[*act_itr], vertices[actor_name], mov);
                vertices[*act_itr]->adj.push_back(edgeA);
                
                ActorEdge* edgeB = new ActorEdge(vertices[actor_name] ,vertices[*act_itr], mov);
                vertices[actor_name]->adj.push_back(edgeB);
                numberOfEdges += 2;
            }
            
            act_in_mov.insert(actor_name);
        }
    }else{
        //The movie is not in the graph yet
        //add the movie
        unordered_set<string> act_in_mov;
        act_in_mov.insert(actor_name);
        Movie* movie = new Movie(movie_title, movie_year);
        movie->act_in = act_in_mov;
        string mov_key = Movie::getMapKeyFromTitleAndYear(movie_title, movie_year);
        movies[mov_key] = movie;
    }
}


/** genearte the shortest path
 *  @param from_actor : the start actor vertex
 *  @param to_actor : the destination actor vertex
 *  @param outfile : the outpunt file for storing the shortest path
 */
void ActorGraph::shorestPath(string from_actor, string to_actor, ofstream &outfile){
    auto itr = vertices.find(from_actor);
    if(itr != vertices.end()){
        unordered_set<string> visited;
        unordered_map<string, ActorEdge*> prevEdges;

        //found the from actor
        queue<ActorNode*> q;
        q.push(itr->second);
        visited.insert(from_actor); //visisted

        bool found = false;
        
        ActorNode* actor = NULL;
        while(!q.empty() && !found){
            actor = q.front();
            q.pop();
            if(actor->name != to_actor){
                for(auto itr = actor->adj.begin(); itr != actor->adj.end(); ++itr){
                    if(visited.find((*itr)->dest->name) == visited.end()){
                        prevEdges[(*itr)->dest->name] = *itr;
                        if((*itr)->dest->name == to_actor){
                            //found it
                            actor = (*itr)->dest;
                            found = true;
                            break;
                        }else{
                            q.push((*itr)->dest);
                            visited.insert((*itr)->dest->name); //visisted
                        }
                    }
                }
            }else{
                found = true;
                break;
            }
        }
        
        vector<ActorEdge*> paths;
        if(found && actor != NULL){
            while(prevEdges[actor->name] != NULL){
                paths.push_back(prevEdges[actor->name]);
                actor = prevEdges[actor->name]->source;
            }
            
            int count = 0;
            for(auto edge_itr = paths.rbegin(); edge_itr != paths.rend(); ++edge_itr){
                outfile << "(" << (*edge_itr)->source->name << ")";
                outfile << "--[" << (*edge_itr)->movie->title << "#@" <<(*edge_itr)->movie->year << "]";
                if(++count == paths.size()){
                    outfile << "-->(" << (*edge_itr)->dest->name << ")";
                }else{
                    outfile << "-->";
                }
            }
            outfile<<endl;
            
        }
    }
}






