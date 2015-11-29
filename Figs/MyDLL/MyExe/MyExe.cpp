// MyExe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int)
{
    HINSTANCE h;
    h = LoadLibrary( L"MyDLL.dll" );
    if ( !h )
    {
        DWORD dw = GetLastError(); 
        return 1;
    }
   /* typedef Geometr::Triangle (*INIT_FIG)();
    INIT_FIG figure;
    figure = (INIT_FIG)GetProcAddress((HMODULE)h, "Init");*/

    double (*figure)(double, double);
    ( FARPROC & )figure = GetProcAddress( h, "Add" );
    //figure = (Geometr::Triangle (*)()) GetProcAddress( h, "Add" );

    /* void (Class::*figure)(int = 0);
    (FARPROC &)figure = GetProcAddress(h, "SetA");*/
            
    if (!figure)
    {
        printf( "Ошибка - не могу найти figure\n" );
        DWORD dw = GetLastError(); 
        return 1;
    }
    return 0;
}

