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
    string title;
    int year;
    
    Movie(string t, int y): title(t), year(y){}
    
    unordered_set<string> act_in;
    
    bool operator ==(const Movie &m) const{
        return title == m.title && year == m.year;
    }
    
    static string getMapKeyFromTitleAndYear(string title, int year){
        return title + to_string(year);
    }
};



namespace std
{
    template <>
    struct hash<Movie>
    {
        size_t operator()(const Movie& movie) const
        {
            return hash<std::string>{}(movie.title + to_string(movie.year));
        }
    };
}


#endif /* Movie_ph*/
