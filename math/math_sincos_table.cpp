//
//  math_sincos_table.cpp
//  genesis
//
//  Created by Ryan Sheffer on 2012-11-12.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "math_sincos_table.h"

namespace MathLib
{
#define SIN_TABLE_SIZE	256
#define FTOIBIAS		12582912.f
    
    // The table itself. Initialized by InitSinCosTable
    static float SinCosTable[SIN_TABLE_SIZE];
    
    // Initialize the SIN / COS table
    // Should be called at load time when needed.
    void InitSinCosTable(void)
    {
        for( int i = 0; i < SIN_TABLE_SIZE; i++ )
        {
            SinCosTable[i] = sin(i * 2.0 * M_PI / SIN_TABLE_SIZE);
        }
    }
    
    float TableCos(float theta)
    {
        union
        {
            int i;
            float f;
        } ftmp;
        
        // ideally, the following should compile down to: theta * constant + constant, changing any of these constants from defines sometimes fubars this.
        ftmp.f = theta * ( float )( SIN_TABLE_SIZE / ( 2.0f * M_PI ) ) + ( FTOIBIAS + ( SIN_TABLE_SIZE / 4 ) );
        return SinCosTable[ ftmp.i & ( SIN_TABLE_SIZE - 1 ) ];
    }
    
    float TableSin(float theta)
    {
        union
        {
            int i;
            float f;
        } ftmp;
        
        // ideally, the following should compile down to: theta * constant + constant
        ftmp.f = theta * ( float )( SIN_TABLE_SIZE / ( 2.0f * M_PI ) ) + FTOIBIAS;
        return SinCosTable[ ftmp.i & ( SIN_TABLE_SIZE - 1 ) ];
    }
}