//
//  Movie.h
//  SixDegrees
//
//  Created by Xie kesong on 2/27/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#ifndef Movie_h
#define Movie_h

#include <iostream>
#include <unordered_set>

using namespace std;

struct Movie{
    
    /** the title of the movie
     */
    string title;
    
    /** the year of the movie
     */
    int year;
    
    
    /** contains a list of actor names in the this movie
     */
    unordered_set<string> act_in;
    
    /** constructor
     */
    Movie(string t, int y): title(t), year(y){}

    /** convert a given title and year of a movie into a string representation
     *  to be used as the key for a given movie
     */
    static string getMapKeyFromTitleAndYear(string title, int year){
        return title + to_string(year);
    }
};

#endif /* Movie_ph*/
