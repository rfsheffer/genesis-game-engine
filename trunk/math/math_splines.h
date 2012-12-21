//
//  math_splines.h
//  A number of functions used for smoothly lerping between a number of points.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_SPLINES_H
#define MATH_SPLINES_H

namespace MathLib
{
    void Catmull_Rom_Spline(const Vector3 &p1,
                            const Vector3 &p2,
                            const Vector3 &p3,
                            const Vector3 &p4,
                            float t,
                            Vector3 &output);
    
    void Catmull_Rom_Spline_Tangent(const Vector3 &p1,
                                    const Vector3 &p2,
                                    const Vector3 &p3,
                                    const Vector3 &p4,
                                    float t,
                                    Vector3 &output);
    
    void Catmull_Rom_Spline_Integral(const Vector3 &p1,
                                     const Vector3 &p2,
                                     const Vector3 &p3,
                                     const Vector3 &p4,
                                     float t,
                                     Vector3 &output);
    
    void Catmull_Rom_Spline_Integral(const Vector3 &p1,
                                     const Vector3 &p2,
                                     const Vector3 &p3,
                                     const Vector3 &p4,
                                     Vector3 &output);
    
    void Catmull_Rom_Spline_Normalize(const Vector3 &p1,
                                      const Vector3 &p2,
                                      const Vector3 &p3,
                                      const Vector3 &p4,
                                      float t,
                                      Vector3 &output);
    
    void Catmull_Rom_Spline_Integral_Normalize(const Vector3 &p1,
                                               const Vector3 &p2,
                                               const Vector3 &p3,
                                               const Vector3 &p4,
                                               float t,
                                               Vector3 &output);
    
    void Catmull_Rom_Spline_NormalizeX(const Vector3 &p1,
                                       const Vector3 &p2,
                                       const Vector3 &p3,
                                       const Vector3 &p4,
                                       float t,
                                       Vector3 &output);
    
    void Hermite_Spline(const Vector3 &p1,
                        const Vector3 &p2,
                        const Vector3 &d1,
                        const Vector3 &d2,
                        float t,
                        Vector3 &output);
    
    float Hermite_Spline(float p1,
                         float p2,
                         float d1,
                         float d2,
                         float t);
    
    void Hermite_SplineBasis(float t, float basis[4]);
    
    void Hermite_Spline(const Vector3 &p0,
                        const Vector3 &p1,
                        const Vector3 &p2,
                        float t,
                        Vector3 &output);
    
    float Hermite_Spline(float p0, float p1, float p2,	float t);
}


#endif // MATH_SPLINES_H
