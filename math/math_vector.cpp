//
//  math_vector.h
//  Vector Classes
//
//  Created by Ryan Sheffer on 2012-11-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

namespace MathLib
{
    // Constants for vector types
    const Vector3 Vector3Origin( 0.0f, 0.0f, 0.0f );
    const Vector3 Vector3Identity( 1.0f, 1.0f, 1.0f );
    const Vector2 Vector2Origin( 0.0f, 0.0f );
    
    //------------------------------------------------------------------------------
    // Purpose: Compute transform axis from object position, target and up direction
    //------------------------------------------------------------------------------
    void LookAtToAxes(const Vector3& pos, const Vector3& target, const Vector3& upDir,
                      Vector3& left, Vector3& up, Vector3& forward)
    {
        // compute the forward vector
        Vector3Subtract(target, pos, forward);
        forward.NormalizeInPlace();
        
        // compute the left vector
        CrossProduct(upDir, forward, left); // cross product
        left.NormalizeInPlace();
        
        // compute the orthonormal up vector
        CrossProduct(forward, left, up);     // cross product
        up.NormalizeInPlace();
    }
}