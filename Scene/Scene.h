#pragma once

#include "stdafx.h"

//#ifndef SCENEH
//#define SCENEH

#ifdef SCENE_EXPORTS
#define SCENE_API __declspec(dllexport)
#else
#define SCENE_API //__declspec(dllimport)
#endif




namespace Scene
{
    /*
    extern SCENE_API int LoadMyShape( )
    {
        std::cout << "@@@" << std::endl;
        return 0;
    }
    */
    class SCENE_API MyScene
    {
    private:
        struct ColorRGB
        {
            BYTE R;
            BYTE G;
            BYTE B;
        };

    public:
        std::vector< Geometr::MyShape > m_shapes;
        int m_height;
        int m_width;
        ColorRGB m_scene[500][500];
        
        MyScene()
        {
            m_height = 500;
            m_width = 500;
            for(int idx_y=0; idx_y<m_height; idx_y++)
            {
                for(int idx_x=0; idx_x<m_width; idx_x++)
                {
                    m_scene[idx_x][idx_y].R = 0;
                    m_scene[idx_x][idx_y].G = 0;
                    m_scene[idx_x][idx_y].B = 0;
                }
            }
        };
        MyScene(int height, int width)
        {
            m_height = height;
            m_width = width;
        };
        //Geometr::MyShape * m_shapes;
        

        int LoadMyShape( LPCWSTR name_dll )
        {
            
            HINSTANCE h;

            //h = LoadLibrary( L"f:\\1\\geometr\\Figs\\fig_triangle2.dll" );
            h = LoadLibrary( name_dll );
            if ( !h )
            {
                printf( "������ - �� ���� ����� Geometr.dll\n" );
                DWORD dw = GetLastError(); 
                return 1;
            }

            typedef Geometr::MyShape (*INIT_FIG)();
            INIT_FIG figure;
            figure = (INIT_FIG)GetProcAddress((HMODULE)h, "Init");

            if (!figure)
            {
                printf( "������ - �� ���� ����� figure\n" );
                DWORD dw = GetLastError(); 
                return 1;
            }
            
            Geometr::MyShape *pb;
            
            std::string type_str = typeid( figure() ).name();
            if( type_str ==  "class Geometr::Triangle" )
            {
                pb = new Geometr::Triangle;
            }
            else if(type_str ==  "class Geometr::Rectangle")
            {
                pb = new Geometr::Rectangle;
            }
            else if(type_str ==  "class Geometr::Square")
            {
                pb = new Geometr::Square;
            }
            else if(type_str ==  "class Geometr::Polygon")
            {
                pb = new Geometr::Polygon;
            }

            *pb = figure();
            pb->ToString();

            m_shapes.push_back( *pb );
            
            delete pb;
            FreeLibrary( h );
            
            return 0;
        };
        void CalcScene()
        {
            for(int idx_y=0; idx_y<500; idx_y++)
            {
                for(int idx_x=0; idx_x<500; idx_x++)
                {
                    for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
                    {
                        if( it->IsDotPoligon(idx_x, idx_y) )
                        {
                            m_scene[idx_x][idx_y].R = (m_scene[idx_x][idx_y].R + it->m_color_brush.R)/2;
                            m_scene[idx_x][idx_y].G = (m_scene[idx_x][idx_y].R + it->m_color_brush.G)/2;
                            m_scene[idx_x][idx_y].B = (m_scene[idx_x][idx_y].R + it->m_color_brush.B)/2;
                        }
                        if( it->IsDotLine(idx_x, idx_y) )
                        {
                            m_scene[idx_x][idx_y].R = (m_scene[idx_x][idx_y].R + it->m_color_lines.R)/2;
                            m_scene[idx_x][idx_y].G = (m_scene[idx_x][idx_y].R + it->m_color_lines.G)/2;
                            m_scene[idx_x][idx_y].B = (m_scene[idx_x][idx_y].R + it->m_color_lines.B)/2;
                        }
                    }
                }
            }
        }
        ~MyScene(){};
    };
}
//#endif