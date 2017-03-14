//
//  DisjointSet.cpp
//  SixDegrees
//
//  Created by Xie kesong on 3/12/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include "DisjointSet.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "Movie.h"
#include "util.h"



/** find actor connection using BFS
 */
void DisjointSet::actorConnectionUnionFind(string in_filename, string test_pair_filename, string output_filename){
    Timer timer;
    timer.begin_timer();
    
    loadFromFileActorConnectionUnionFind(in_filename);
    searchActorConnectionsUnionFind(test_pair_filename, output_filename);
    
    long long timeCost = timer.end_timer();
    cout << "Run time: " << timeCost << "s" << endl;

}


/** Load the graph from a tab-delimited file of actor->movie relationships.
 *  @param in_filename :  input filename
 */
void DisjointSet::loadFromFileActorConnectionUnionFind(string in_filename) {
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
        
        
        
        if(actors.find(actor_name) == actors.end()){
            ActorNodeDJS* actor = new ActorNodeDJS(actor_name);
            //add the actor
            actors[actor_name] = actor;
        }
        
        int movie_year = stoi(record[2]);
        pair<string, string> entryPair(actor_name, movie_title);
        if(yearGroup.find(movie_year) == yearGroup.end()){
            //year not found
            vector<pair<string, string>> groups;
            groups.push_back(entryPair);
            yearGroup[movie_year] = groups;
        }else{
            //year found
            yearGroup[movie_year].push_back(entryPair);
        }
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
    }
    infile.close();
}


int DisjointSet::searchActorConnectionsUnionFind(string test_pair_filename, string output_filename){
    ifstream readPairFile(test_pair_filename);
    ofstream outputFile(output_filename);
    
    if(!outputFile.is_open()){
        cerr << "Can't write to file: " << output_filename << endl;
        return -1;
    }
    
    
    if(readPairFile.is_open()){
        bool have_header = false;
        
        // keep reading lines until the end of file is reached
        outputFile << "Actor1\tActor2\tYear" << endl;
        
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
            bool found = false;
            int foundYear = 9999;
            for(auto& i: yearGroup){
                for(auto& j: i.second){
                    string movieKey = Movie::getMapKeyFromTitleAndYear(j.second, i.first); //j.second, movie title
                    if(movies.find(movieKey) == movies.end()){
                        //movie not found
                        movies[movieKey] = actors[j.first];
                    }else{
                        ActorNodeDJS* movieSentinelNode = movies[movieKey]->getSentinelNode().first;
                        ActorNodeDJS* actorSentinelNode = actors[j.first]->getSentinelNode().first;
                        if(movieSentinelNode->upTreeSize >= actorSentinelNode->upTreeSize){
                            //this might be the new sentinel
                            actorSentinelNode->up = movieSentinelNode;
                            actorSentinelNode->isSentinelNode = false;
                            movieSentinelNode->isSentinelNode = true;
                            movieSentinelNode->upTreeSize += 1;
                        }else{
                            movieSentinelNode->up = actorSentinelNode;
                            movieSentinelNode->isSentinelNode = false;
                            actorSentinelNode->isSentinelNode = true;
                            actorSentinelNode->upTreeSize += 1;
                        }
                    }
                }
                if(find(actors[first_actor], actors[second_actor])){
                    found = true;
                    foundYear =  i.first;
                    break;
                }
            }
            
            
            cout << "pair: " << first_actor << " -- " << second_actor << " done!" <<endl;
            outputFile << first_actor << '\t' << second_actor << '\t';
            if(found){
                outputFile << foundYear << endl;
            }else{
                outputFile << 9999 << endl;
            }
            
            //reset
            for(auto& actor: actors){
                actor.second->reset();
            }
        }
        cout << "Done!" << endl;
    }else{
        cerr << "Can't open and read from file: " << test_pair_filename << endl;
    }
    return 0;
}



bool DisjointSet::find(ActorNodeDJS* first, ActorNodeDJS* second){
    //path conpression
    return first->getSentinelNode().first == second->getSentinelNode().first;
}

