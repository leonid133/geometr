#include "stdafx.h"
#include "fig.h"
#include <stdexcept>
#include <vector>

namespace Fig
{
  /*  
Geometr::Triangle Fig::Init()
{
    Geometr::Triangle triangle_;
    std::vector<std::pair<int, int> > coord_pairs;
    std::pair<int, int> v1, v2, v3;
    v1.first = 90;
    v1.second =30;
    coord_pairs.push_back( v1 );
    v2.first = 100;
    v2.second =160;
    coord_pairs.push_back( v2 );
    v3.first = 35;
    v3.second =145;
    coord_pairs.push_back( v3 );
    //0xEE82EE violet
    //0xFFFF7F50 coral
    //0xFFB22222 firebrick
    triangle_.SetLinesColor(0x7F, 0x7F, 0x50);
    triangle_.SetBrushColor(0xEE, 0x82, 0xEE);
    triangle_.SetCoord( coord_pairs );
    triangle_.SetName("fig_triangle.dll");
    return triangle_;
}
*/
    Geometr::Rectangle Fig::Init()
    {
        Geometr::Rectangle rectangle_;
        std::vector<std::pair<int, int> > coord_pairs;
        std::pair<int, int> v1, v2, v3;
        v1.first = 90;
        v1.second =30;
        coord_pairs.push_back( v1 );
        v2.first = 100;
        v2.second =160;
        coord_pairs.push_back( v2 );
        v3.first = 35;
        v3.second =145;
        coord_pairs.push_back( v3 );
        //0xEE82EE violet
        //0xFFFF7F50 coral
        //0xFFB22222 firebrick
        rectangle_.SetLinesColor(0x5F, 0x3F, 0x20);
        rectangle_.SetBrushColor(0x1E, 0x72, 0x4E);
        rectangle_.SetCoord( coord_pairs );
        rectangle_.SetName("fig_rectangle.dll");
        return rectangle_;
    }
}