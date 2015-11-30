// Geometr.h
#pragma once

#include "stdafx.h"

#ifdef GEOMETR_EXPORTS
#define GEOMETR_API __declspec(dllexport) 
#else
#define GEOMETR_API //__declspec(dllimport) 
#endif


namespace Geometr
{
    class GEOMETR_API MyShape
    {
    protected:
        struct CoordXY
        {
            int X;
            int Y;
        };

    
        bool pt_in_polygon(const CoordXY &test, const std::vector<CoordXY> &polygon)
        {
            if (polygon.size()<3) return false;

            auto end=polygon.end();

            CoordXY last_pt=polygon.back();

            last_pt.X-=test.X;
            last_pt.Y-=test.Y;

            double sum=0.0;

            for(
                auto iter=polygon.begin();
                iter!=end;
            ++iter
                )
            {
                auto cur_pt=*iter;
                cur_pt.X-=test.X;
                cur_pt.Y-=test.Y;

                double del= last_pt.X*cur_pt.Y-cur_pt.X*last_pt.Y;
                double xy= cur_pt.X*last_pt.X+cur_pt.Y*last_pt.Y;

                sum+=
                    (
                    atan((last_pt.X*last_pt.X+last_pt.Y*last_pt.Y - xy)/del)+
                    atan((cur_pt.X*cur_pt.X+cur_pt.Y*cur_pt.Y- xy )/del)
                    );
                last_pt=cur_pt;
            }
            return fabs(sum)>1;
        }

        bool isLine(int x, int y, int x1, int y1, int x2, int y2)
        {
            if(x<x1 || x>x2 || y<y1 || y>y2)
                return false;
            double line_ = ((double)y1 - (double)y2)*(double)x + ((double)x2 - (double)x1)*(double)y+ ((double)x1 * (double)y2 - (double)x2 * (double)y1);
            if(line_ < 10.0 && line_>-10.0 )
                return true;
            return false;
        };

        struct ColorRGB
        {
            BYTE R;
            BYTE G;
            BYTE B;
        };

public:
        
        CoordXY * pV;
        ColorRGB m_color_lines;
        ColorRGB m_color_brush;

        enum ShapeLine
        {
            solid,
            dotted_line,
            dotted_bar
        };

        ShapeLine m_shape_line;
        
        std::string m_shape_name;
        
        MyShape( )
        {
            m_shape_name = "_name_undefined_";
            ColorRGB color_def;
            color_def.B = color_def.G = color_def.R = 0;
            m_color_lines = color_def;
            m_color_brush = color_def;
            ShapeLine shap_def;
            shap_def = solid;
            m_shape_line = shap_def;
        };
        MyShape( const MyShape& right )
        {
            m_shape_name = right.m_shape_name;
            m_shape_line = right.m_shape_line;
            m_count_vertex = right.m_count_vertex;
            m_color_lines = right.m_color_lines;
            m_color_brush = right.m_color_brush;
           
            pV = new CoordXY[m_count_vertex]; 
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = right.pV[idx].X;
                pV[idx].Y = right.pV[idx].Y;
            }
        }
        MyShape& operator=(const MyShape& right) 
        {
            if (this == &right) {
                return *this;
            }
            m_shape_name = right.m_shape_name;
            m_shape_line = right.m_shape_line;
            m_count_vertex = right.m_count_vertex;
            m_color_lines = right.m_color_lines;
            m_color_brush = right.m_color_brush;
            if( pV )
                delete[] pV;
            pV = new CoordXY[m_count_vertex]; 
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = right.pV[idx].X;
                pV[idx].Y = right.pV[idx].Y;
            }
            return *this;
        }

        virtual void SetName( const std::string &name  ){m_shape_name=name;};
        virtual void V_count() {};
        
        virtual std::string ToString()
        {
            std::string coord_str;
            coord_str = "/nКоординаты вершин фигуры/n";
            for(int it_v =0 ; it_v < m_count_vertex; ++it_v)
            {
                coord_str +="/n";
                coord_str +="V[";
                coord_str +=it_v;
                coord_str +="]; X:";
                coord_str += pV[it_v].X;
                coord_str +="; Y:";
                coord_str += pV[it_v].Y;
                coord_str +=";/n";
            }
            return coord_str;
        };

        virtual bool SetCoord( std::vector<std::pair<int, int> > coord_x_y  )
        {
            if( coord_x_y.size() != m_count_vertex)
                return false;

            std::sort( coord_x_y.begin(), coord_x_y.end() );
            int idx_coord = 0;
            for( auto it = coord_x_y.begin(); it < coord_x_y.end(); ++it )
            {
                pV[idx_coord].X = it->first;
                pV[idx_coord++].Y = it->second;
            }

            return true;
        };

        virtual bool SetLinesColor( BYTE R, BYTE G, BYTE B)
        {
            if (R<0||R>255||G<0||G>255||B<0||B>255)
            {
                return false;
            }
            m_color_lines.R = R;
            m_color_lines.G = G;
            m_color_lines.B = B;
            return true;
        }

        virtual bool SetBrushColor( BYTE R, BYTE G, BYTE B)
        {
            if (R<0||R>255||G<0||G>255||B<0||B>255)
            {
                return false;
            }
            m_color_brush.R = R;
            m_color_brush.G = G;
            m_color_brush.B = B;
            return true;
        }

        int m_count_vertex;
        
        virtual bool IsDotLine(int x, int y)
        {
            for( int idx = 1; idx < m_count_vertex; ++idx )
            {
                if( isLine( x, y, pV[idx-1].X, pV[idx-1].Y, pV[idx].X, pV[idx].Y ) )
                    return true;
            }
            if( isLine( x, y, pV[0].X, pV[0].Y, pV[m_count_vertex-1].X, pV[m_count_vertex-1].Y ) )
                return true;
            return false;
        };

        virtual bool IsDotPoligon(int x, int y)
        {
            CoordXY test_p;
            test_p.X = x;
            test_p.Y = y;
            std::vector< CoordXY > polygon;
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                polygon.push_back( pV[idx] );
            }
            return pt_in_polygon( test_p, polygon );
        }

        virtual ~MyShape(){};
    };

    class GEOMETR_API Triangle: public MyShape
    {
    private:
        virtual void V_count(){m_count_vertex = 3;};

    public:
        Triangle()
        {
            V_count();
            pV = new CoordXY[m_count_vertex];
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = 0;
                pV[idx].Y = 0;
            }
        };
        ~Triangle()
        {
            if( pV )
                delete[] pV;
        };
    };

    class GEOMETR_API Rectangle: public MyShape
    {
    private:
         virtual void V_count(){m_count_vertex = 4;};
    public:
        Rectangle()
        {
            V_count();
            pV = new CoordXY[m_count_vertex];
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = 0;
                pV[idx].Y = 0;
            }
        };
        ~Rectangle()
        {
            if( pV )
                delete[] pV;
        };
    };

    class GEOMETR_API Square: public MyShape
    {
    private:
        virtual void V_count(){m_count_vertex = 4;};
    public:
        Square()
        {
            V_count();
            pV = new CoordXY[m_count_vertex];
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = 0;
                pV[idx].Y = 0;
            }
        };
        ~Square()
        {
            if( pV )
                delete[] pV;
        };
    };
        
    class GEOMETR_API Polygon: public MyShape
    {
    private:
        virtual void V_count(){};
        
    public:
        Polygon(){};
        Polygon(int n)
        {
            m_count_vertex = n;
            pV = new CoordXY[m_count_vertex];
            for( int idx = 0; idx < m_count_vertex; ++idx )
            {
                pV[idx].X = 0;
                pV[idx].Y = 0;
            }
        };

        ~Polygon()
        {
            if( pV )
                delete[] pV;
        };
    };
}