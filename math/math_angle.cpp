//
//  math_angle.h
//  Angle Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

namespace MathLib
{    
    void AngleVectors(const Angle &ang, Vector3& left, Vector3& up, Vector3& forward)
    {
        float sx, sy, sz, cx, cy, cz;
        
        // rotation angle about X-axis (pitch)
        sx = sinf(ang.x);
        cx = cosf(ang.x);
        
        // rotation angle about Y-axis (yaw)
        sy = sinf(ang.y);
        cy = cosf(ang.y);
        
        // rotation angle about Z-axis (roll)
        sz = sinf(ang.z);
        cz = cosf(ang.z);
        
        // determine left axis
        left.x = cy*cz;
        left.y = sx*sy*cz + cx*sz;
        left.z = -cx*sy*cz + sx*sz;
        
        // determine up axis
        up.x = -cy*sz;
        up.y = -sx*sy*sz + cx*cz;
        up.z = cx*sy*sz + sx*cz;
        
        // determine forward axis
        forward.x = sy;
        forward.y = -sx*cy;
        forward.z = cx*cy;
    }
    
    //-----------------------------------------------------------------------------
    // Forward direction vector -> Euler angles
    //-----------------------------------------------------------------------------
    
    void VectorAngles(const Vector3 &forward, Angle &angles)
    {
        float	tmp, yaw, pitch;
        
        if (forward[1] == 0 && forward[0] == 0)
        {
            yaw = 0;
            if (forward[2] > 0)
                pitch = 270;
            else
                pitch = 90;
        }
        else
        {
            yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
            if (yaw < 0)
                yaw += 360;
            
            tmp = sqrtf(forward[0]*forward[0] + forward[1]*forward[1]);
            pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
            if (pitch < 0)
                pitch += 360;
        }
        
        angles[PITCH] = pitch;
        angles[YAW] = yaw;
        angles[ROLL] = 0;
    }
    
    //-----------------------------------------------------------------------------
    // Forward direction vector with a reference up vector -> Euler angles
    //-----------------------------------------------------------------------------
    void VectorAngles(const Vector3 &forward, const Vector3 &pseudoup, Angle &angles)
    {
        Vector3 left;
        
        CrossProduct( pseudoup, forward, left );
        Vector3Normalize( left );
        
        float xyDist = sqrtf( forward[0] * forward[0] + forward[1] * forward[1] );
        
        // enough here to get angles?
        if ( xyDist > 0.001f )
        {
            // (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
            angles[YAW] = RAD2DEG( atan2f( forward[1], forward[0] ) );
            
            // The engine does pitch inverted from this, but we always end up negating it in the DLL
            // UNDONE: Fix the engine to make it consistent
            // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
            angles[PITCH] = RAD2DEG( atan2f( -forward[2], xyDist ) );
            
            float up_z = (left[1] * forward[0]) - (left[0] * forward[1]);
            
            // (roll)	z = ATAN( left.z, up.z );
            angles[ROLL] = RAD2DEG( atan2f( left[2], up_z ) );
        }
        else	// forward is mostly Z, gimbal lock-
        {
            // (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
            angles[YAW] = RAD2DEG( atan2f( -left[0], left[1] ) ); //This was originally copied from the "void MatrixAngles( const matrix3x4_t& matrix, float *angles )" code, and it's 180 degrees off, negated the values and it all works now (Dave Kircher)
            
            // The engine does pitch inverted from this, but we always end up negating it in the DLL
            // UNDONE: Fix the engine to make it consistent
            // (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
            angles[PITCH] = RAD2DEG( atan2f( -forward[2], xyDist ) );
            
            // Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
            angles[ROLL] = 0;
        }	
    }
}