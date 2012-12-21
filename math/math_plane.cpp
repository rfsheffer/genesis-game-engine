//
//  math_plane.cpp
//  A plane class
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

namespace MathLib
{
    //-----------------------------------------------------------------------------
    // Purpose: This is used to simplify box to plane tests
    //-----------------------------------------------------------------------------
    void CPlane::ComputeSignbitsForPlane(void)
    {        
        // For fast box on planeside test
        m_iBits = 0;
        
        for (int i = 0; i < 3; ++i)
        {
            if (m_vecN[i] < 0)
                m_iBits |= (1 << i);
        }
    }
    
    void CPlane::ComputePlaneType(void)
    {
        float flX, flY, flZ;
        
        // NOTE: should these have an epsilon around 1.0?
        if ( m_vecN[0] == 1.0f || m_vecN[0] == -1.0f )
        {
            m_iType = PLANE_X;
            return;
        }
        else if ( m_vecN[1] == 1.0f || m_vecN[1] == -1.0f )
        {
            m_iType = PLANE_Y;
            return;
        }
        else if ( m_vecN[2] == 1.0f || m_vecN[2] == -1.0f )
        {
            m_iType = PLANE_Z;
            return;
        }
        
        flX = fabsf( m_vecN[0] );
        flY = fabsf( m_vecN[1] );
        flZ = fabsf( m_vecN[2] );
        
        if (flX >= flY && flX >= flZ)
        {
            m_iType = PLANE_ANYX;
            return;
        }
        else if (flY >= flX && flY >= flZ)
        {
            m_iType = PLANE_ANYY;
            return;
        }
        else
        {
            m_iType = PLANE_ANYZ;
            return;
        }
    }
    
    //-----------------------------------------------------------------------------
    // Used to create a "best-fit" plane from a number of points
    //-----------------------------------------------------------------------------
    void CPlane::ComputeBestFitPlane(const Vector3 v[], unsigned int n)
    {
        if(n <= 0)
        {
            ASSERTION(n > 0, "ComputeBestFitPlane called with ZERO points!");
            return;
        }
        
        // Zero out sum
        m_vecN = Vector3Origin;
        m_flD = 0;
        
        Vector3 dirAvg = Vector3Origin;
        
        // Start with the previous vertex as the last one.
        // This avoids an if-statement in the loop
        
        const Vector3 *p = &v[n-1];
        
        // Iterate through the verticies
        for(int i = 0; i < n; ++i)
        {
            // Current vertex
            const Vector3 *c = &v[i];
            
            // Add in edge vector products appropriately
            m_vecN.x += (p->z + c->z) * (p->y - c->y);
            m_vecN.y += (p->x + c->x) * (p->z - c->z);
            m_vecN.z += (p->y + c->y) * (p->x - c->x);
            
            // Add all the points together to we can average them
            // at the end.
            dirAvg += *c;
            
            // Next vertex, please :)
            p = c;
        }
        
        // Make sure it's a unit vector
        Vector3Normalize(m_vecN);
        
        // "best-fit" distance computed as the average of the d values for
        // each point.
        m_flD = DotProduct(dirAvg, m_vecN) * (1/n);
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: This is a clone of BaseWindingForPlane()
    // Input  : *pOutVerts - an array of preallocated verts to build the polygon in
    //			normal - the plane normal
    //			dist - the plane constant
    // Output : int - vert count (always 4)
    //-----------------------------------------------------------------------------
    int PolyFromPlane(Vector3 *pOutVerts, const Vector3 &normal, float dist, float fHalfScale )
    {
        int		i, x;
        vec_t	max, v;
        Vector3	org, vright, vup;
        
        // find the major axis
        
        max = -16384; //MAX_COORD_INTEGER
        x = -1;
        for (i = 0; i < 3; ++i)
        {
            v = fabs(normal[i]);
            if (v > max)
            {
                x = i;
                max = v;
            }
        }
        
        if(x == -1)
            return 0;
        
        // Build a unit vector along something other than the major axis
        vup = Vector3Origin;
        
        switch(x)
        {
            case 0:
            case 1:
                vup[2] = 1;
                break;
            case 2:
                vup[0] = 1;
                break;
        }
        
        // Remove the component of this vector along the normal
        v = DotProduct(vup, normal);
        
        Vector3MulAdd(vup, normal, -v, vup);
        
        // Make it a unit (perpendicular)
        Vector3Normalize (vup);
        
        // Center of the poly is at normal * dist
        Vector3Scale(normal, dist, org);
        
        // Calculate the third orthonormal basis vector for our plane space (this one and vup are in the plane)
        CrossProduct (vup, normal, vright);
        
        // Make the plane's basis vectors big (these are the half-sides of the polygon we're making)
        Vector3Scale(vup, fHalfScale, vup);
        Vector3Scale(vright, fHalfScale, vright);
        
        // Move diagonally away from org to create the corner verts
        Vector3Subtract (org, vright, pOutVerts[0]);	// left
        Vector3Add(pOutVerts[0], vup, pOutVerts[0]);	// up
        
        Vector3Add(org, vright, pOutVerts[1]);		// right
        Vector3Add(pOutVerts[1], vup, pOutVerts[1]);	// up
        
        Vector3Add(org, vright, pOutVerts[2]);		// right
        Vector3Subtract(pOutVerts[2], vup, pOutVerts[2]);	// down
        
        Vector3Subtract(org, vright, pOutVerts[3]);		// left
        Vector3Subtract(pOutVerts[3], vup, pOutVerts[3]);	// down
        
        // The four corners form a planar quadrilateral normal to "normal"
        return 4;
    }
    
    //-----------------------------------------------------------------------------
    // Clips a line segment such that only the portion in the positive half-space
    // of the plane remains.  If the segment is entirely clipped, the vectors
    // are set to vec3_invalid (all components are FLT_MAX).
    //
    // flBias is added to the dot product with the normal.  A positive bias
    // results in a more inclusive positive half-space, while a negative bias
    // results in a more exclusive positive half-space.
    //-----------------------------------------------------------------------------
    void ClipLineSegmentToPlane(const Vector3 &vNormal, const Vector3 &vPlanePoint, Vector3 *p1, Vector3 *p2, float flBias)
    {
        float flDot1, flDot2;
        Vector3 temp;
        
        Vector3Subtract(*p1, vPlanePoint, temp);
        flDot1 = DotProduct(temp, vNormal) + flBias;
        
        Vector3Subtract(*p2, vPlanePoint, temp);
        flDot2 = DotProduct(temp, vNormal) + flBias;
        
        // Nothing to clip? Alright then :)
        if(flDot1 >= 0 && flDot2 >= 0)
        {
            return;
        }
        
        if(flDot1 >= 0)
        {
            Vector3 vRay;
            Vector3Subtract(*p2, *p1, vRay);
            
            // *p2 = *p1 + vRay * flDot1 / ( flDot1 - flDot2 );
            Vector3Multiply(vRay, flDot1 / ( flDot1 - flDot2 ), vRay);
            Vector3Add(*p1, vRay, *p2);
        }
        else if ( flDot2 >= 0 )
        {
            Vector3 vRay;
            Vector3Subtract(*p1, *p2, vRay);
            
            // *p1 = *p2 + vRay * flDot2 / ( flDot2 - flDot1 );
            Vector3Multiply(vRay, flDot2 / ( flDot2 - flDot1 ), vRay);
            Vector3Add(*p2, vRay, *p1);
        }
        else
        {
            p1->Invalidate();
            p2->Invalidate();
            ASSERTION(0, "Bad ClipLineSegmentToPlane!");
        }
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Used to determine if an AABB is on the normal direction side of a plane.
    // Input  : vecMin, vecMax - The bounds of the AABB
    //			plane - The plane to check against
    // Output : int - 1, 2, or 1 + 2
    //-----------------------------------------------------------------------------
    int BoxOnPlaneSide(const Vector3 &vecMin, const Vector3 &vecMax, const CPlane &plane)
    {
        float	dist1, dist2;
        int		sides;
        
        // fast axial cases
        if(plane.m_iType < 3)
        {
            if(plane.m_flD <= vecMin[plane.m_iType])
                return 1;
            if(plane.m_flD >= vecMax[plane.m_iType])
                return 2;
            return 3;
        }
        
        // general case
        switch (plane.m_iBits)
        {
            case 0:
                dist1 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMax[2];
                dist2 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMin[2];
                break;
            case 1:
                dist1 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMax[2];
                dist2 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMin[2];
                break;
            case 2:
                dist1 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMax[2];
                dist2 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMin[2];
                break;
            case 3:
                dist1 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMax[2];
                dist2 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMin[2];
                break;
            case 4:
                dist1 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMin[2];
                dist2 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMax[2];
                break;
            case 5:
                dist1 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMin[2];
                dist2 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMax[2];
                break;
            case 6:
                dist1 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMin[2];
                dist2 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMax[2];
                break;
            case 7:
                dist1 = plane.m_vecN[0]*vecMin[0] + plane.m_vecN[1]*vecMin[1] + plane.m_vecN[2]*vecMin[2];
                dist2 = plane.m_vecN[0]*vecMax[0] + plane.m_vecN[1]*vecMax[1] + plane.m_vecN[2]*vecMax[2];
                break;
            default:
                dist1 = dist2 = 0;		// shut up compiler
                ASSERTION(0, "Invalid Sign Bits for Box on Plane Test! Sign bits not calculated?");
                break;
        }
        
        sides = 0;
        if (dist1 >= plane.m_flD)
            sides = 1;
        if (dist2 < plane.m_flD)
            sides |= 2;
        
        ASSERTION(sides != 0, "Could not determine which side the AABB is to the plane?!");
        
        return sides;
    }
}