// Geometr.h

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
    class MyShape
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

        MyShape()
        {
            m_shape_name = "uniq_name";
        };

    public:        
        
        

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
        };

        virtual void SetCoord() = 0;

        virtual ~MyShape();
    };

    class Triangle: public MyShape
    {
    private:

    public:
        Triangle()
        {
            m_count_vertex = 3;
            pV = new CoordXY[m_count_vertex];
        };
        ~Triangle()
        {
            delete[] pV;
        };
    };

    class Rectangle: public MyShape
    {
    private:

    public:
        Rectangle()
        {
            m_count_vertex = 4;
            pV = new CoordXY[m_count_vertex];
        };
        ~Rectangle()
        {
            delete[] pV;
        };
    };

    class Square: public MyShape
    {
    private:
        
    public:
        Square()
        {
            m_count_vertex = 4;
            pV = new CoordXY[m_count_vertex];
        };
        ~Square()
        {
            delete[] pV;
        };
    };
        
    class Polygon: public MyShape
    {
    private:
        
        
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