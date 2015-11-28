// Geometr.h
#include "stdafx.h"

#ifdef GEOMETR_EXPORTS
#define GEOMETR_API __declspec(dllexport) 
#else
#define GEOMETR_API __declspec(dllimport) 
#endif


namespace MathFuncs
{
    // This class is exported from the MathFuncsDll.dll
    class MyMathFuncs
    {
    public: 
        // Returns a + b
        static GEOMETR_API double Add(double a, double b); 

        // Returns a - b
        static GEOMETR_API double Subtract(double a, double b); 

        // Returns a * b
        static GEOMETR_API double Multiply(double a, double b); 

        // Returns a / b
        // Throws const std::invalid_argument& if b is 0
        static GEOMETR_API double Divide(double a, double b); 
    };
}

namespace Geometr
{
    class GEOMETR_API MyShape
    {
    private:

    protected:
        
        struct CoordXY
        {
            int X;
            int Y;
        };

        int m_count_vertex;
        CoordXY * pV;

        struct ColorRGB
        {
            int R;
            int G;
            int B;
        };

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
        };

    public:

        virtual void SetName( const std::string &name  ){m_shape_name=name;};
        virtual void V_count() = 0;

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
        };
        ~Triangle()
        {
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
        };
        ~Rectangle()
        {
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
        };
        ~Square()
        {
            delete[] pV;
        };
    };
        
    class GEOMETR_API Polygon: public MyShape
    {
    private:
        virtual void V_count(){};
        
    public:
        Polygon(int n)
        {
            m_count_vertex = n;
            pV = new CoordXY[m_count_vertex];
        };

        ~Polygon()
        {
            delete[] pV;
        };
    };
}