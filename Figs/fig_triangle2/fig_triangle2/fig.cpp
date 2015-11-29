#include "stdafx.h"
#include "fig.h"
#include <stdexcept>

namespace Fig
{
    
Geometr::Triangle Fig::Init()
{
    Geometr::Triangle triangle_;
    std::vector<std::pair<int, int> > coord_pairs;
    std::pair<int, int> v1, v2, v3;
    v1.first = 1;
    v1.second =1;
    coord_pairs.push_back( v1 );
    v2.first = 10;
    v2.second =10;
    coord_pairs.push_back( v2 );
    v3.first = 20;
    v3.second =13;
    coord_pairs.push_back( v3 );

    triangle_.SetCoord( coord_pairs );
    triangle_.SetName("fig_triangle2");
    return triangle_;
}

}