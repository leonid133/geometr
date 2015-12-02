#pragma once

#include "stdafx.h"

#ifdef MY_SCENE_EXPORTS
#define MY_SCENE_API __declspec(dllexport)
#else
#define MY_SCENE_API  //__declspec(dllimport)
#endif


namespace Scene
{
    class MY_SCENE_API MyScene
    {
        struct ColorRGB
        {
            BYTE R;
            BYTE G;
            BYTE B;
        };
        
        std::map<std::string, std::string> m_shap_map;

        wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
        {
            wchar_t* wString=new wchar_t[4096];
            MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
            return wString;
        }
        
        void MyScene::ClearScene()
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
            m_shap_map.clear();
        }

        bool OutLoadedSort()
        {
            // ¬ыходной текстовый файл out_loaded_sort.txt, включающий список имен и координат вершин, отсортированный по возрастанию.

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
            // ¬ыходной текстовый файл out_loaded_sort.txt, включающий список имен и координат вершин, отсортированный по возрастанию.

            std::string logfile = "out_intersected.txt";
            std::ofstream log_filestream( logfile, std::ios_base::trunc );
            if(!log_filestream.is_open())
            {
                return false;
            }
            std::cout.rdbuf(log_filestream.rdbuf());
            std::cout << m_shap_map.size();

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


        void MyScene::CalcScene()
        {
            std::string first_name;
            std::string first_coord;
            for(int idx_y=0; idx_y < m_height; idx_y++)
            {
                for(int idx_x=0; idx_x < m_width; idx_x++)
                {
                    int label=0;

                    for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
                    {
                        if( it->PointInPoligon(idx_x, idx_y) )
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

                    }
                }
            }
            for( auto it = m_shapes.begin(); it < m_shapes.end(); ++it )
            {
                std::vector<Geometr::MyShape::CoordXY> y( it->GetLineCoord( m_width, m_height ) );
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
            }
        }

        int m_height; //ToDo перенести в приват и сделать Get метод
        int m_width;

    public:

        MyScene()
        {
            m_height = 500;
            m_width = 500;
            m_scene = new ColorRGB * [m_width+1];
            for (int idx = 0; idx < (m_width+1); idx++) 
            {
                m_scene[idx] = new ColorRGB [m_height+1];
            }
            ClearScene();
        }

        std::vector< Geometr::MyShape > m_shapes;

        int Height() { return m_height; }

        int Width()  { return m_width;  }

        ColorRGB **m_scene;
        
        MyScene::MyScene( const int &width, const int &height )
        {
            m_width = width;
            m_height = height;

            m_scene = new ColorRGB * [m_width+1];
            for (int idx = 0; idx < (m_width+1); idx++) 
            {
                m_scene[idx] = new ColorRGB [m_height+1];
            }
            ClearScene();
        }
        

        bool LoadMyShape( std::string patch_name_dll )
        {
            HINSTANCE h;
            LPCSTR name_dll;
            name_dll = patch_name_dll.c_str();
            h = LoadLibraryA( name_dll );
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

        void Refresh()
        {
            ClearScene();
            CalcScene();
            OutLoadedSort();
            OutIntersected();
        }
        ~MyScene()
        {
            for ( int idx = 0; idx < (m_width+1); idx++ ) 
            {
                delete [] m_scene[idx];
            }
            delete [] m_scene;
        };
    };
}
