// Scene.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "scene.h"

namespace Scene
{
    
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
    
}