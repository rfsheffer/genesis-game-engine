//
//  CBasicRender.h
//  A basic rendering pipeline
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef BASIC_RENDER_H
#define BASIC_RENDER_H

/**
 * Basic render pipeline
 */
class CBasicRender : public render::IRenderPipeline
{
public:
    void    Setup(render::CContext *pContext);
    void    SetupProjection(render::CContext *pContext);
    void    SetupModelView(render::CContext *pContext);
    void    Draw(render::CContext *pContext);
    
    Angle   m_camAng;
    Vector3 m_camPos;
};

#endif // BASIC_RENDER_H
