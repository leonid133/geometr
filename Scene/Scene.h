#pragma once

#include "stdafx.h"

#ifndef SCENEH
#define SCENEH

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
        //int LoadMyShape( LPCWSTR namedll )
        int LoadMyShape( )
        {
            
            HINSTANCE h;
            //h = LoadLibrary( namedll );
            h = LoadLibrary( L"Fig_Triangle.dll" );
            if ( !h )
            {
                printf( "Ошибка - не могу найти Geometr.dll\n" );
                return 1;
            }
            Geometr::MyShape *pVar;
            (FARPROC &)pVar = GetProcAddress( h, "fig" );
            //*pVar = 123;

            FreeLibrary( h );
            
            return 0;
        };
        ~MyScene(){};
    };
}
#endif