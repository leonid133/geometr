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
    triangle_.m_shape_line = triangle_.ShapeLine::dotted_bar;
    triangle_.SetLinesColor(0x7F, 0x7F, 0x50);
    triangle_.SetBrushColor(0xEE, 0x82, 0xEE);
    triangle_.SetCoord( coord_pairs );
    return triangle_;
}
*/
    /*
    Geometr::Rectangle Fig::Init()
    {
        Geometr::Rectangle rectangle_;
        std::vector<std::pair<int, int> > coord_pairs;
        std::pair<int, int> v1, v2, v3;
        v1.first = 250;
        v1.second =100;
        coord_pairs.push_back( v1 );
        v2.first = 10;
        v2.second =330;
        coord_pairs.push_back( v2 );
        v3.first = 250;
        v3.second = 385;
        coord_pairs.push_back( v3 );
        //0xEE82EE violet
        //0xFFFF7F50 coral
        //0xFFB22222 firebrick
        rectangle_.m_shape_line = rectangle_.ShapeLine::solid;
        rectangle_.SetLinesColor(0x4F, 0x1F, 0x40);
        rectangle_.SetBrushColor(0xBE, 0x42, 0xEE);
        rectangle_.SetCoord( coord_pairs );
        return rectangle_;
    }*/
    /*
    Geometr::Square Fig::Init()
    {
        Geometr::Square square_;
        std::vector<std::pair<int, int> > coord_pairs;
        std::pair<int, int> v1, v2, v3;
        v1.first = 50;
        v1.second =70;
        coord_pairs.push_back( v1 );
        v2.first = 200;
        v2.second =190;
        coord_pairs.push_back( v2 );
        
        //0xEE82EE violet
        //0xFF7F50 coral
        //0xB22222 firebrick
        square_.m_shape_line = square_.ShapeLine::dotted_line;
        square_.SetLinesColor(0xFF, 0xFF, 0xFF);
        square_.SetBrushColor(0x7E, 0x92, 0x2E);
        square_.SetCoord( coord_pairs );
        return square_;
    }
    */
    Geometr::Polygon Fig::Init()
    {
        Geometr::Polygon polygon_(6);
        std::vector<std::pair<int, int> > coord_pairs;
        std::pair<int, int> v1, v2, v3, v4, v5, v6;
        v1.first = 125;
        v1.second =300;
        coord_pairs.push_back( v1 );
        v2.first = 200;
        v2.second =375;
        coord_pairs.push_back( v2 );
        v3.first = 300;
        v3.second =375;
        coord_pairs.push_back( v3 );
        v4.first = 375;
        v4.second =300;
        coord_pairs.push_back( v4 );
        v5.first = 375;
        v5.second =200;
        coord_pairs.push_back( v5 );
        v6.first = 300;
        v6.second =125;
        coord_pairs.push_back( v6 );

        //0xEE82EE violet
        //0xFF7F50 coral
        //0xB22222 firebrick
        polygon_.m_shape_line = polygon_.ShapeLine::dotted_bar;
        polygon_.SetLinesColor(0xFF, 0xFF, 0xFF);
        polygon_.SetBrushColor(0x8E, 0x22, 0x1E);
        polygon_.SetCoord( coord_pairs );
        return polygon_;
    }
}