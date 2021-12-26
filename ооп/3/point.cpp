#include<iostream>
#include<vector>
#include<cmath>
#include<string.h>


#include "point.h"

double scalar_mult(point a_end, point top_begin, point b_end){
    return (top_begin.x - a_end.x)*(top_begin.x - b_end.x) + (top_begin.y - a_end.y)*(top_begin.y - b_end.y);
}

double segment_length(point a, point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
