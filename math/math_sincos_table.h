//
//  math_sincos_table.h
//  genesis
//
//  Created by Ryan Sheffer on 2012-11-12.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_SIN_COS_TABLE
#define MATH_SIN_COS_TABLE

namespace MathLib
{
    void InitSinCosTable(void);
    float TableCos(float theta);
    float TableSin(float theta);
}

#endif // MATH_SIN_COS_TABLE
