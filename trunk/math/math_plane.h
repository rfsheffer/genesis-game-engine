//
//  math_plane.h
//  A plane class
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_PLANE_H
#define MATH_PLANE_H

namespace MathLib
{
    
#define PLANE_X     0
#define PLANE_Y     1
#define PLANE_Z     2
#define PLANE_ANYX  3
#define PLANE_ANYY  4
#define PLANE_ANYZ  5
    
    //=========================================================
    // Plane Class
    //=========================================================
    class CPlane
    {
    public:
        
        // No initialization
        inline CPlane()
        {
            m_vecN = Vector3Origin;
            m_flD = 0;
        }
        
        // Create this plane with this normal and distance
        inline CPlane(const Vector3 &normal, float distance)
        {
            m_vecN = normal;
            m_flD = distance;
        }
        
        // Create this plane based on three known points
        CPlane(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
        {
            Vector3 p1_to_p2;
            Vector3 p2_to_p3;
            
            // Create vector to vector for points            
            Vector3Subtract(p2, p1, p1_to_p2);
            Vector3Subtract(p3, p2, p2_to_p3);
            
            // Get the perpendicular vector from this
            CrossProduct(p1_to_p2, p2_to_p3, m_vecN);
            
            // Make sure it's a unit vector
            Vector3Normalize(m_vecN);
            
            // Distance == Dot product of any point and normal
            m_flD = DotProduct(p1, m_vecN);
        }
        
        inline void Init(const Vector3 &normal, float distance)
        {
            m_vecN = normal;
            m_flD = distance;
        }
        
        inline void FlipPlane(void)
        {
            m_vecN.Negate();
            m_flD = -m_flD;
        }
        
        // Used to create a "best-fit" plane from a number of points
        void ComputeBestFitPlane(const Vector3 v[], unsigned int n);
        
        inline float DistanceToPlane(const Vector3 &vec) const
        {
            return DotProduct(vec, m_vecN) - m_flD;
        }
        
        // Snaps a point to a plane
        inline void SnapPointToPlane(const Vector3 &point, Vector3 &out) const
        {
            // Snap Pos == point - normal * distToPoint
            Vector3 temp;
            Vector3Multiply(m_vecN, DistanceToPlane(point), temp);
            Vector3Subtract(point, temp, out);
        }
        
        // Returns which side of the plane a point is on, or if the point is on the plane.
        inline side_t GetPointSide(const Vector3 &vecPoint, float flSideEpsilon = PLANE_POINT_SIDE_EPSILON) const;
        
        // Returns which side of the plane a point is on.
        // Returns SIDE_FRONT if on or in front of the plane.
        inline side_t GetPointSideExact(const Vector3 &vecPoint)
        {
            return (DistanceToPlane(vecPoint) > 0.0f)?SIDE_FRONT:SIDE_BACK;
        }
        
        inline void SetupFastPlaneData(void)
        {
            ComputePlaneType();
            ComputeSignbitsForPlane();
        }
        
        void ComputePlaneType(void);
        void ComputeSignbitsForPlane(void);
        
        // Plane Normal
        Vector3     m_vecN;
        
        // Distance from the origin
        float       m_flD;
        
        // For fast box on planeside test
        int         m_iBits;
        
        // Quick way of telling the direction of the plane
        int         m_iType;
    };
    
    // Returns which side of the plane a point is on, or if the point is on the plane.
    inline side_t CPlane::GetPointSide(const Vector3 &vecPoint, float flSideEpsilon) const
    {
        float flDist;
        
        flDist = DistanceToPlane(vecPoint);
        if(flDist >= flSideEpsilon)
        {
            return SIDE_FRONT;
        }
        else if(flDist <= -flSideEpsilon)
        {
            return SIDE_BACK;
        }
        
        return SIDE_ON;
    }
    
    int PolyFromPlane(Vector3 *pOutVerts, const Vector3 &normal, float dist, float fHalfScale);
    void ClipLineSegmentToPlane(const Vector3 &vNormal, const Vector3 &vPlanePoint, Vector3 *p1, Vector3 *p2, float flBias);
    int BoxOnPlaneSide(const Vector3 &vecMin, const Vector3 &vecMax, const CPlane &plane);
}


#endif // MATH_PLANE_H
