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
        
    public:
        MyScene(){};

        int LoadMyShape( )
        {
            
            HINSTANCE h;

            h = LoadLibrary( L"f:\\1\\geometr\\Figs\\fig_triangle2.dll" );
            if ( !h )
            {
                printf( "Ошибка - не могу найти Geometr.dll\n" );
                DWORD dw = GetLastError(); 
                return 1;
            }

            typedef Geometr::MyShape (*INIT_FIG)();
            INIT_FIG figure;
            figure = (INIT_FIG)GetProcAddress((HMODULE)h, "Init");

            if (!figure)
            {
                printf( "Ошибка - не могу найти figure\n" );
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

            delete pb;
            FreeLibrary( h );
            
            return 0;
        };
        ~MyScene(){};
    };
}
//#endif