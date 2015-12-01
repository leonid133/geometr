#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#ifdef SCENE_EXPORTS
#define SCENE_API __declspec(dllexport)
#else
#define SCENE_API //__declspec(dllimport)
#endif

namespace Scene
{
    class SCENE_API MyScene
    {
        struct ColorRGB
        {
            BYTE R;
            BYTE G;
            BYTE B;
        };
        void ClearScene();
        std::map<std::string, std::string> m_shap_map;

        wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
        {
            wchar_t* wString=new wchar_t[4096];
            MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
            return wString;
        }

    public:
        std::vector< Geometr::MyShape > m_shapes;
        int m_height; //ToDo перенести в приват и сделать Get метод
        int m_width;
        ColorRGB m_scene[2000][2000]; //ToDo переделать на **
        
        MyScene()
        {
            m_height = 500;
            m_width = 500;
            ClearScene();
        };
        MyScene( int width, int height )
        {
            m_height = height;
            m_width = width;
            ClearScene();
        };

        bool LoadMyShape( std::string patch_name_dll )
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
        };

        void CalcScene() //ToDo распараллелить 
        {
            ClearScene();
            
            std::string first_name;
            std::string first_coord;
            for(int idx_y=0; idx_y < m_height; idx_y++)
            {
                for(int idx_x=0; idx_x < m_width; idx_x++)
                {
                    int label=0;
                    
                    for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
                    {
                        if( it->IsDotPoligon(idx_x, idx_y) )
                        {
                            if(label>0)
                            {
                                label = 0;
                                //вот и пара нашлась
                                std::stringstream ss;
                                ss << first_name << " <-> " << it->m_shape_name;
                                std::stringstream ss2;
                                ss2 << first_coord << " <-> "<< it->ToString(false, false).str();
                                m_shap_map.insert(make_pair(ss.str(), ss2.str()));
                            }
                            label++;
                            first_name = it->m_shape_name;
                            first_coord = it->ToString(false, false).str();
                            m_scene[idx_x][idx_y].R = (m_scene[idx_x][idx_y].R + it->m_color_brush.R)/2;
                            m_scene[idx_x][idx_y].G = (m_scene[idx_x][idx_y].R + it->m_color_brush.G)/2;
                            m_scene[idx_x][idx_y].B = (m_scene[idx_x][idx_y].R + it->m_color_brush.B)/2;
                            
                        }
                        /*if( it->IsDotLine(idx_x, idx_y) )
                        {
                        Geometr::MyShape::ColorRGB line_color = it->GetColorLine();
                        m_scene[idx_x][idx_y].R = line_color.R;
                        m_scene[idx_x][idx_y].G = line_color.G;
                        m_scene[idx_x][idx_y].B = line_color.B;
                        }*/
                    }
                }
            }
            for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
            {
                    std::vector<Geometr::MyShape::CoordXY> y( it->F( m_width, m_height ) );
                    for (auto it_y = y.begin(); it_y < y.end(); ++it_y)
                    {
                        if( ( 0 < it_y->Y && it_y->Y < m_height ) && ( 0 < it_y->X && it_y->X < m_width ) )
                        {
                            Geometr::MyShape::ColorRGB line_color = it->GetColorLine();
                            m_scene[it_y->X][it_y->Y].R = line_color.R;
                            m_scene[it_y->X][it_y->Y].G = line_color.G;
                            m_scene[it_y->X][it_y->Y].B = line_color.B;
                        }
                    }
                    /*for( int idx = 1; idx < it->m_count_vertex; ++idx )
                    {
                        double x = idx_x;
                        double x1 = it->pV[idx-1].X;
                        double y1 = it->pV[idx-1].Y;
                        double x2 = it->pV[idx].X;
                        double y2 =  it->pV[idx].Y;
                        double y = -x*(y1-y2)/(x2-x1) - (x1*y2 - x2*y1)/(x2-x1);
                        if( ( x1 < x && x < x2 ) || (x2 < x && x < x1 ) || ( y1 < y && y < y2 ) || (y2 < y && y < y1 ) )
                        {
                            if( 0 < y && y < m_height )
                            {
                                Geometr::MyShape::ColorRGB line_color = it->GetColorLine();
                                m_scene[idx_x][(int)y].R = line_color.R;
                                m_scene[idx_x][(int)y].G = line_color.G;
                                m_scene[idx_x][(int)y].B = line_color.B;
                            }
                        }
                        
                    }*/
            }
        }
        

        bool OutLoadedSort()
        {
            // Выходной текстовый файл out_loaded_sort.txt, включающий список имен и координат вершин, отсортированный по возрастанию.

            std::string logfile = "out_loaded_sort.txt";
            std::ofstream log_filestream( logfile, std::ios_base::trunc );
            if(!log_filestream.is_open())
            {
                return false;
            }
            std::cout.rdbuf(log_filestream.rdbuf());
            for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
            {
                std::cout << it->m_shape_name << std::endl;
                std::cout << it->ToString(false,true).str() << std::endl;
            }
            log_filestream.close();
            return true;
        }
        bool OutIntersected()
        {
            // Выходной текстовый файл out_loaded_sort.txt, включающий список имен и координат вершин, отсортированный по возрастанию.

            std::string logfile = "out_intersected.txt";
            std::ofstream log_filestream( logfile, std::ios_base::trunc );
            if(!log_filestream.is_open())
            {
                return false;
            }
            std::cout.rdbuf(log_filestream.rdbuf());
            std::cout << m_shap_map.size();


            m_shap_map.begin();
            m_shap_map.end();
            m_shap_map.find("aaa");
            std::map< std::string, std::string >::const_iterator it;
            it = m_shap_map.begin();
            while(it !=  m_shap_map.end())
            {
                std::cout << it->first << std::endl;
                std::cout << it->second << std::endl;
                ++it;
            }

            log_filestream.close();
            return true;
        }
        ~MyScene(){};
    };
}
