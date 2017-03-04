//
//  Movie.cpp
//  SixDegrees
//
//  Created by Xie kesong on 2/27/17.
//  Copyright © 2017 ___KesongXie___. All rights reserved.
//

#include "Movie.h"


/** convert a given title and year of a movie into a string representation
 *  to be used as the key for a given movie
 */
string Movie::getMapKeyFromTitleAndYear(string title, int year){
    return title + to_string(year);
}
