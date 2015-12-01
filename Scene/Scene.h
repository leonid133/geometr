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
    private:
        struct ColorRGB
        {
            BYTE R;
            BYTE G;
            BYTE B;
        };
        void ClearScene()
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
        std::map<std::string, std::string> m_shap_map;
    public:
        std::vector< Geometr::MyShape > m_shapes;
        int m_height; //ToDo ��������� � ������ � ������� Get �����
        int m_width;
        ColorRGB m_scene[2000][2000]; //ToDo ���������� �� **
        
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

        bool LoadMyShape( LPCWSTR name_dll )
        {
            HINSTANCE h;

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
                        
            m_shapes.push_back( *pb );
            
            delete pb;
            FreeLibrary( h );
            
            return true;
        };

        void CalcScene() //ToDo �������������� 
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
                                //��� � ���� �������
                                std::stringstream ss;
                                ss << first_name << " <-> " << it->m_shape_name;
                                std::stringstream ss2;
                                ss2 << first_coord << " <-> "<< it->ToString(false, false).str();
                                m_shap_map.insert(make_pair(ss.str(), ss2.str()));
                                //m_shap_map.insert(make_pair(ss.str(), 1));
                            }
                            label++;
                            first_name = it->m_shape_name;
                            first_coord = it->ToString(false, false).str();
                            m_scene[idx_x][idx_y].R = (m_scene[idx_x][idx_y].R + it->m_color_brush.R)/2;
                            m_scene[idx_x][idx_y].G = (m_scene[idx_x][idx_y].R + it->m_color_brush.G)/2;
                            m_scene[idx_x][idx_y].B = (m_scene[idx_x][idx_y].R + it->m_color_brush.B)/2;
                            if( it->IsDotLine(idx_x, idx_y) )
                            {
                                Geometr::MyShape::ColorRGB line_color = it->GetColorLine();
                                m_scene[idx_x][idx_y].R = line_color.R;
                                m_scene[idx_x][idx_y].G = line_color.G;
                                m_scene[idx_x][idx_y].B = line_color.B;
                                
                            }
                        }
                    }
                }
            }
        }
        bool OutLoadedSort()
        {
            // �������� ��������� ���� out_loaded_sort.txt, ���������� ������ ���� � ��������� ������, ��������������� �� �����������.

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
    // �������� ��������� ���� out_loaded_sort.txt, ���������� ������ ���� � ��������� ������, ��������������� �� �����������.

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
