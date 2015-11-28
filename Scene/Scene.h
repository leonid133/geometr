#pragma once

#include "stdafx.h"

#ifdef SCENE_EXPORTS
#define SCENE_API __declspec(dllexport)
#else
#define SCENE_API __declspec(dllimport)
#endif

namespace Scene
{
    class SCENE_API MyScene
    {
    private:
        
    public:
        //MyScene(){};
        int LoadMyShape( LPCWSTR namedll )
        {
            HINSTANCE h;
            h = LoadLibrary( namedll );
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
        //~MyScene(){};
    };
}