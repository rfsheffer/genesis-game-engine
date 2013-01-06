//
//  math_frustum.h
//  Stuff related to a cameras view frustum.
//
//  Created by Ryan Sheffer on 2012-11-11.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_FRUSTUM_H
#define MATH_FRUSTUM_H

namespace MathLib
{
    // The planes that make up a view frustum
    enum frustum_planes
    {
        FRUSTUM_RIGHT,
        FRUSTUM_LEFT,
        FRUSTUM_TOP,
        FRUSTUM_BOTTOM,
        FRUSTUM_NEARZ,
        FRUSTUM_FARZ,
        
        NUM_FRUSTUM_PLANES
    };
    
    // Frustum Class: Contains the planes of the frustum, and the methods
    // to generate them.
    class CFrustum
    {
    public:
        
        FORCEINLINE
        void GeneratePerspectiveFrustum(const Vector3 &origin,
                                        const Angle &angles,
                                        float flZNear,
                                        float flZFar,
                                        float flfovX,
                                        float flFovY);
        
        void GeneratePerspectiveFrustum(const Vector3 &origin,
                                        const Vector3 &forward,
                                        const Vector3 &right,
                                        const Vector3 &up,
                                        float flZNear,
                                        float flZFar,
                                        float flFovX,
                                        float flFovY);
        
        void GenerateOrthogonalFrustum(const Vector3 &origin,
                                       const Vector3 &forward,
                                       const Vector3 &right,
                                       const Vector3 &up,
                                       float flLeft,
                                       float flRight,
                                       float flBottom,
                                       float flTop,
                                       float flZNear,
                                       float flZFar);
        
    private:
        
        CPlane m_planes[NUM_FRUSTUM_PLANES];
    };
    
    //-----------------------------------------------------------------------------
    // Purpose: Generates a Perspective Frustum with these parameters
    //-----------------------------------------------------------------------------
    FORCEINLINE
    void CFrustum::GeneratePerspectiveFrustum(const Vector3 &origin,
                                              const Angle &angles,
                                              float flZNear,
                                              float flZFar,
                                              float flfovX,
                                              float flFovY)
    {
        Vector3 vecForward, vecRight, vecUp;
        AngleVectors(angles, vecForward, vecRight, vecUp);
        
        GeneratePerspectiveFrustum(origin, vecForward, vecRight, vecUp, flZNear, flZFar, flfovX, flFovY);
    }
}

#endif // MATH_FRUSTUM_H
