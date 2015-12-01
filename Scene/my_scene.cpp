// my_cene.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "geometr.h"
#include "my_scene.h"

namespace Scene
{
   

    /*
    void  MyScene::ClearScene()
    {
        for(int idx_y=0; idx_y<m_height; idx_y++)
        {
            for(int idx_x=0; idx_x<m_width; idx_x++)
            {
                m_scene[idx_x][idx_y].R = 0;
                m_scene[idx_x][idx_y].G = 0;
                m_scene[idx_x][idx_y].B = 0;
            }
        }
    }
    */




    //MyScene::MyScene( const int &width, const int &height )
    //{
    //    m_height = height;
    //    m_width = width;
    //    ClearScene();
    //}

    /*
    bool MyScene::LoadMyShape( std::string patch_name_dll )
    {
        HINSTANCE h;
        LPCWSTR name_dll;
        name_dll = (LPCWSTR)convertCharArrayToLPCWSTR( patch_name_dll.c_str() );
        h = LoadLibrary( name_dll );
        if ( !h )
        {
            DWORD dw = GetLastError(); 
            return false;
        }

        typedef Geometr::MyShape (*INIT_FIG)();
        INIT_FIG figure;
        figure = (INIT_FIG)GetProcAddress((HMODULE)h, "Init");

        if (!figure)
        {
            DWORD dw = GetLastError(); 
            return false;
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
        size_t slash_pos = patch_name_dll.rfind( '\\' );
        if(!( ( slash_pos == std::string::npos ) || ( slash_pos == patch_name_dll.length() - 1 ) ))
        {
            pb->m_shape_name = patch_name_dll.substr( slash_pos + 1 );
        }

        m_shapes.push_back( *pb );

        delete pb;
        FreeLibrary( h );

        return true;
    }
    */
}