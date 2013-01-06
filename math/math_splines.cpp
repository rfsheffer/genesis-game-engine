//
//  math_splines.cpp
//  A number of functions used for smoothly lerping between a number of points.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

// NOTE: These splines are based off Valve Softwares implementation of them.

namespace MathLib
{
    //-----------------------------------------------------------------------------
    // Purpose:
    // Input  :
    //-----------------------------------------------------------------------------
    void Catmull_Rom_Spline(const Vector3 &p1,
                            const Vector3 &p2,
                            const Vector3 &p3,
                            const Vector3 &p4,
                            float t,
                            Vector3 &output)
    {
        float tSqr = t * t * 0.5f;
        float tSqrSqr = t * tSqr;
        t *= 0.5f;
        
        ASSERTION( &output != &p1, "" );
        ASSERTION( &output != &p2, "" );
        ASSERTION( &output != &p3, "" );
        ASSERTION( &output != &p4, "" );
        
        output.Init();
        
        Vector3 a, b, c, d;
        
        // matrix row 1
        Vector3Scale( p1, -tSqrSqr, a );		// 0.5 t^3 * [ (-1*p1) + ( 3*p2) + (-3*p3) + p4 ]
        Vector3Scale( p2, tSqrSqr*3, b );
        Vector3Scale( p3, tSqrSqr*-3, c );
        Vector3Scale( p4, tSqrSqr, d );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
        Vector3Add( c, output, output );
        Vector3Add( d, output, output );
        
        // matrix row 2
        Vector3Scale( p1, tSqr*2,  a );		// 0.5 t^2 * [ ( 2*p1) + (-5*p2) + ( 4*p3) - p4 ]
        Vector3Scale( p2, tSqr*-5, b );
        Vector3Scale( p3, tSqr*4,  c );
        Vector3Scale( p4, -tSqr,    d );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
        Vector3Add( c, output, output );
        Vector3Add( d, output, output );
        
        // matrix row 3
        Vector3Scale( p1, -t, a );			// 0.5 t * [ (-1*p1) + p3 ]
        Vector3Scale( p3, t,  b );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
        
        // matrix row 4
        Vector3Add( p2, output, output );	// p2
    }
    
    void Catmull_Rom_Spline_Tangent(const Vector3 &p1,
                                    const Vector3 &p2,
                                    const Vector3 &p3,
                                    const Vector3 &p4,
                                    float t,
                                    Vector3 &output )
    {
        float tOne = 3 * t * t * 0.5f;
        float tTwo = 2 * t * 0.5f;
        float tThree = 0.5;
        
        ASSERTION( &output != &p1, "" );
        ASSERTION( &output != &p2, "" );
        ASSERTION( &output != &p3, "" );
        ASSERTION( &output != &p4, "" );
        
        output.Init();
        
        Vector3 a, b, c, d;
        
        // matrix row 1
        Vector3Scale( p1, -tOne, a );		// 0.5 t^3 * [ (-1*p1) + ( 3*p2) + (-3*p3) + p4 ]
        Vector3Scale( p2, tOne*3, b );
        Vector3Scale( p3, tOne*-3, c );
        Vector3Scale( p4, tOne, d );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
        Vector3Add( c, output, output );
        Vector3Add( d, output, output );
        
        // matrix row 2
        Vector3Scale( p1, tTwo*2,  a );		// 0.5 t^2 * [ ( 2*p1) + (-5*p2) + ( 4*p3) - p4 ]
        Vector3Scale( p2, tTwo*-5, b );
        Vector3Scale( p3, tTwo*4,  c );
        Vector3Scale( p4, -tTwo,    d );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
        Vector3Add( c, output, output );
        Vector3Add( d, output, output );
        
        // matrix row 3
        Vector3Scale( p1, -tThree, a );			// 0.5 t * [ (-1*p1) + p3 ]
        Vector3Scale( p3, tThree,  b );
        
        Vector3Add( a, output, output );
        Vector3Add( b, output, output );
    }
    
    // area under the curve [0..t]
    // TODO: This needs to be split up, what a mess!
    /*void Catmull_Rom_Spline_Integral(
                                     const Vector3 &p1,
                                     const Vector3 &p2,
                                     const Vector3 &p3,
                                     const Vector3 &p4,
                                     float t,
                                     Vector3 &output )
    {
        output = p2*t
        -0.25f*(p1 - p3)*t*t
        + (1.0f/6.0f)*(2.0f*p1 - 5.0f*p2 + 4.0f*p3 - p4)*t*t*t
        - 0.125f*(p1 - 3.0f*p2 + 3.0f*p3 - p4)*t*t*t*t;
    }
    
    
    // area under the curve [0..1]
    void Catmull_Rom_Spline_Integral(
                                     const Vector3 &p1,
                                     const Vector3 &p2,
                                     const Vector3 &p3,
                                     const Vector3 &p4,
                                     Vector3 &output )
    {
        output = (-0.25f * p1 + 3.25f * p2 + 3.25f * p3 - 0.25f * p4) * (1.0f / 6.0f);
    }*/
    
    
    void Catmull_Rom_Spline_Normalize(const Vector3 &p1,
                                      const Vector3 &p2,
                                      const Vector3 &p3,
                                      const Vector3 &p4,
                                      float t,
                                      Vector3 &output)
    {
        // Normalize p2->p1 and p3->p4 to be the same length as p2->p3
        float dt = p3.DistTo(p2);
        
        Vector3 p1n, p4n;
        Vector3Subtract( p1, p2, p1n );
        Vector3Subtract( p4, p3, p4n );
        
        Vector3Normalize( p1n );
        Vector3Normalize( p4n );
        
        Vector3MulAdd( p2, p1n, dt, p1n );
        Vector3MulAdd( p3, p4n, dt, p4n );
        
        Catmull_Rom_Spline( p1n, p2, p3, p4n, t, output );
    }
    
    
    /*void Catmull_Rom_Spline_Integral_Normalize(const Vector3 &p1,
                                               const Vector3 &p2,
                                               const Vector3 &p3,
                                               const Vector3 &p4,
                                               float t,
                                               Vector3 &output)
    {
        // Normalize p2->p1 and p3->p4 to be the same length as p2->p3
        float dt = p3.DistTo(p2);
        
        Vector3 p1n, p4n;
        Vector3Subtract( p1, p2, p1n );
        Vector3Subtract( p4, p3, p4n );
        
        Vector3Normalize( p1n );
        Vector3Normalize( p4n );
        
        Vector3MulAdd( p2, p1n, dt, p1n );
        Vector3MulAdd( p3, p4n, dt, p4n );
        
        Catmull_Rom_Spline_Integral( p1n, p2, p3, p4n, t, output );
    }*/
    
    
    /*void Catmull_Rom_Spline_NormalizeX(const Vector3 &p1,
                                       const Vector3 &p2,
                                       const Vector3 &p3,
                                       const Vector3 &p4,
                                       float t,
                                       Vector3 &output)
    {
        Vector3 p1n, p4n;
        Spline_Normalize( p1, p2, p3, p4, p1n, p4n );
        Catmull_Rom_Spline( p1n, p2, p3, p4n, t, output );
    }*/
    
    
    //-----------------------------------------------------------------------------
    // Purpose: basic hermite spline.  t = 0 returns p1, t = 1 returns p2, 
    //			d1 and d2 are used to entry and exit slope of curve
    // Input  : 
    //-----------------------------------------------------------------------------
    void Hermite_Spline(const Vector3 &p1,
                        const Vector3 &p2,
                        const Vector3 &d1,
                        const Vector3 &d2,
                        float t, 
                        Vector3 &output)
    {
        float tSqr = t * t;
        float tCube = t * tSqr;
        
        ASSERTION( &output != &p1, "" );
        ASSERTION( &output != &p2, "" );
        ASSERTION( &output != &d1, "" );
        ASSERTION( &output != &d2, "" );
        
        float b1 = 2.0f*tCube-3.0f*tSqr+1.0f;
        float b2 = 1.0f - b1; // -2*tCube+3*tSqr;
        float b3 = tCube-2*tSqr+t;
        float b4 = tCube-tSqr;
        
        Vector3Scale( p1, b1, output );
        Vector3MulAdd( output, p2, b2, output );
        Vector3MulAdd( output, d1, b3, output );
        Vector3MulAdd( output, d2, b4, output );
    }
    
    float Hermite_Spline(float p1,
                         float p2,
                         float d1,
                         float d2,
                         float t)
    {
        float output;
        float tSqr = t*t;
        float tCube = t*tSqr;
        
        float b1 = 2.0f*tCube-3.0f*tSqr+1.0f;
        float b2 = 1.0f - b1; // -2*tCube+3*tSqr;
        float b3 = tCube-2*tSqr+t;
        float b4 = tCube-tSqr;
        
        output = p1 * b1;
        output += p2 * b2;
        output += d1 * b3;
        output += d2 * b4;
        
        return output;
    }
    
    
    void Hermite_SplineBasis( float t, float basis[4] )
    {
        float tSqr = t*t;
        float tCube = t*tSqr;
        
        basis[0] = 2.0f*tCube-3.0f*tSqr+1.0f;
        basis[1] = 1.0f - basis[0]; // -2*tCube+3*tSqr;
        basis[2] = tCube-2*tSqr+t;
        basis[3] = tCube-tSqr;
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: simple three data point hermite spline.  
    //			t = 0 returns p1, t = 1 returns p2, 
    //			slopes are generated from the p0->p1 and p1->p2 segments
    //			this is reasonable C1 method when there's no "p3" data yet.
    // Input  : 
    //-----------------------------------------------------------------------------
    
    // BUG: the VectorSubtract()'s calls go away if the global optimizer is enabled
#pragma optimize( "g", off )
    
    void Hermite_Spline(const Vector3 &p0,
                        const Vector3 &p1,
                        const Vector3 &p2,
                        float t,
                        Vector3 &output)
    {
        Vector3 e10, e21;
        Vector3Subtract( p1, p0, e10 );
        Vector3Subtract( p2, p1, e21 );
        Hermite_Spline( p1, p2, e10, e21, t, output );
    }
    
#pragma optimize( "", on )
    
    float Hermite_Spline(float p0, float p1, float p2,	float t)
    {
        return Hermite_Spline( p1, p2, p1 - p0, p2 - p1, t );
    }
    
}