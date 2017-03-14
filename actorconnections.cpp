//
//  actorconnections.cpp
//  SixDegrees
//
//  Created by Xie kesong on 3/11/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include <iostream>
#include "ActorGraph.h"
#include "DisjointSet.h"

using namespace std;

int main(int argc, char** argv){
    
    if(argc < 4 || argc > 5){
        cerr << "Usage: ./actorconnections movie_casts.tsv test_pairs.tsv out_connections_bfs.tsv ufind/bfs" << endl;
        return -1;
    }
    
    //get the cast file name
    string mov_cast_filename = *(++argv);
    if(mov_cast_filename.length() < 1){
        return -1;
    }
    
    //get the test pair filename
    string test_pair_filename = *(++argv);
    
    
    
    //get the output file name
    string output_filename = *(++argv);
    
    
    //optional, specify which method to use ufind/bfs
    
    bool useUFind = true;
    //get the weighted or unweighted option
    
    if(argc >= 5){
        //get the forth paramerer
        string method = *(++argv); //equals to ufind/bfs
        if(method != "ufind" && method != "bfs"){
            cerr << "the option should be 'ufind' (union find) or 'bfs'(breath first search) only" << endl;
            return -1;
        }
        if(method == "bfs"){
            useUFind = false;
        }
    }
    
    //load actors from the cast and build the graph
    if(useUFind){
        cout << "use union find" << endl;
        DisjointSet ds;
        ds.actorConnectionUnionFind(mov_cast_filename, test_pair_filename, output_filename);
    }else{
        cout << "use breath first search" << endl;
        ActorGraph graph;
        graph.actorConnectionBFS(mov_cast_filename, test_pair_filename, output_filename);
    }

    
}
