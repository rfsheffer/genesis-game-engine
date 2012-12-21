//
//  math_frustum.cpp
//  Stuff related to a cameras view frustum.
//
//  Created by Ryan Sheffer on 2012-11-11.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

namespace MathLib
{
    //-----------------------------------------------------------------------------
    // Purpose: Generates a Perspective Frustum with these parameters
    //-----------------------------------------------------------------------------
    void CFrustum::GeneratePerspectiveFrustum(const Vector3 &origin,
                                              const Vector3 &forward,
                                              const Vector3 &right,
                                              const Vector3 &up,
                                              float flZNear,
                                              float flZFar,
                                              float flFovX,
                                              float flFovY)
    {
        float flIntercept = DotProduct(origin, forward);
        
        Vector3 negForward = forward;
        negForward.Negate();
        
        // Setup the near and far planes
        m_planes[FRUSTUM_FARZ].Init(negForward, -flZFar - flIntercept);
        m_planes[FRUSTUM_NEARZ].Init(forward, flZNear - flIntercept);
        
        flFovX *= 0.5f;
        flFovY *= 0.5f;
        
        float flTanX = tan(DEG2RAD(flFovX));
        float flTanY = tan(DEG2RAD(flFovY));
        
        Vector3 normalPos, normalNeg;
        
        normalPos.MulAdd(right, forward, flTanX);
        normalNeg.MulAdd(normalPos, right, -2.0f);
        
        Vector3Normalize(normalPos);
        Vector3Normalize(normalNeg);
        
        m_planes[FRUSTUM_LEFT].Init(normalPos, DotProduct(normalPos, origin));
        m_planes[FRUSTUM_RIGHT].Init(normalNeg, DotProduct(normalNeg, origin));
        
        normalPos.MulAdd(up, forward, flTanY);
        normalNeg.MulAdd(normalPos, up, -2.0f);
        
        Vector3Normalize(normalPos);
        Vector3Normalize(normalNeg);
        
        m_planes[FRUSTUM_BOTTOM].Init(normalPos, DotProduct(normalPos, origin));
        m_planes[FRUSTUM_TOP].Init(normalNeg, DotProduct(normalNeg, origin));
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Generates a Orthogonal Frustum with these parameters
    //-----------------------------------------------------------------------------
    void CFrustum::GenerateOrthogonalFrustum(const Vector3 &origin,
                                             const Vector3 &forward,
                                             const Vector3 &right,
                                             const Vector3 &up,
                                             float flLeft,
                                             float flRight,
                                             float flBottom,
                                             float flTop,
                                             float flZNear,
                                             float flZFar)
    {
        // NEAR AND FAR
        float flIntercept = DotProduct(origin, forward);
        
        Vector3 negForward = forward;
        negForward.Negate();
        
        m_planes[FRUSTUM_NEARZ].Init(forward, flZNear + flIntercept);
        m_planes[FRUSTUM_FARZ].Init(negForward, -flZFar - flIntercept);
        
        // RIGHT AND LEFT
        flIntercept = DotProduct(origin, right);
        
        Vector3 negRight = right;
        negRight.Negate();
        
        m_planes[FRUSTUM_RIGHT].Init(negRight, -flRight - flIntercept);
        m_planes[FRUSTUM_LEFT].Init(right, flLeft + flIntercept);
        
        // UP AND DOWN
        flIntercept = DotProduct(origin, up);
        
        Vector3 negUp = up;
        negUp.Negate();
        
        m_planes[FRUSTUM_BOTTOM].Init(up, flBottom + flIntercept);
        m_planes[FRUSTUM_TOP].Init(negUp, -flTop - flIntercept);
    }
}