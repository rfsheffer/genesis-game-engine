//
//  asm_math.h
//
//  Created by Ryan Sheffer on 2012-10-08.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATH_ASM_H
#define MATH_ASM_H

#ifdef _LINUX
#error "Unsupported Platform."
#endif

namespace MathLib
{

// Math routines done in optimized assembly math package routines
    
    inline float Sqrt(float num)
    {
#ifdef _WIN
        _asm
        {
            fld DWORD PTR [num]
            fsqrt
            fstp DWORD ptr[num]
        }
        return num;
#elif _MAC
        register double __sqrRoot;
        __asm __volatile__("fsqrt" : "=t" (__sqrRoot) : "0" (num));
        return __sqrRoot;
#endif
    }
    
    inline float Sine(float radians)
    {
#ifdef _WIN
        _asm
        {
            fld DWORD PTR [radians]
            fsin
            fstp DWORD PTR [radians]
        }
        return radians;
#elif _MAC
        register double __sinr;
        __asm __volatile__("fsin" : "=t" (__sinr) : "0" (radians));
        return __sinr;
#endif
    }
    
    inline float Cos(float radians)
    {
#ifdef _WIN
        _asm
        {
            fld DWORD PTR [radians]
            fcos
            fstp DWORD PTR [radians]
        }
        return radians;
#elif _MAC
        register double __cosr;
        __asm __volatile__("fcos" : "=t" (__cosr) : "0" (radians));
        return __cosr;
#endif
    }
    
    // AT&T Syntax
    // - OPCODE src dest, which is backwards from intels version
    // - Register names are prefixed by % ie, if eax is to be used, write %eax
    
    inline float Tan(float radians)
    {
#ifdef _WIN
        _asm
        {
            fld DWORD PTR [radians]
            fsincos
            fdiv
            fstp DWORD PTR [radians]
        }
        return radians;
#elif _MAC
        
       // __asm__("fld %[radians]l" : [radians] "=f" (radians) :);
        
        return 1;
#endif
    }
    
    //-----------------------------------------------------------------------------
    // Purpose: Returns the SIN and COS of theta.
    //-----------------------------------------------------------------------------
    void inline SinCos( float radians, float *sine, float *cosine )
    {
#if defined( WIN )
        _asm
        {
            fld		DWORD PTR [radians]
            fsincos
            
            mov edx, DWORD PTR [cosine]
            mov eax, DWORD PTR [sine]
            
            fstp DWORD PTR [edx]
            fstp DWORD PTR [eax]
        }
#elif defined( _LINUX ) || defined( _MAC )
        register double __cosr, __sinr;
        __asm __volatile__("fsincos" : "=t" (__cosr), "=u" (__sinr) : "0" (radians));
        
        *sine = __sinr;
        *cosine = __cosr;
#endif
    }

    
    
#if defined( WIN )
    
    // WIN ONLY!?
    inline __int64 GetCpuCycle()
    {
        unsigned int LowWord;
        unsigned int HighWord;
        _asm
        {
            _emit 0x0F
            _emit 0x31
            mov HighWord, edx
            mov LowWord, eax
        }
        return ((__int64)(HighWord) << 32) + LowWord;
    }
    
    inline float Cot(float Rad)
    {
        _asm
        {
            fld DWORD PTR [Rad]
            fsincos
            fdivr
            fstp DWORD PTR [Rad]
        }
        return Rad;
    }
    
    inline float Atan(float Rad)
    {
        _asm
        {
            fld dword ptr [Rad]
            fld1
            fpatan
            fstp dword ptr [Rad]
        }
        return Rad;
    }
    
    inline float Asin(float Rad)
    {
        Rad = Sqrt(Rad*Rad/(1-Rad*Rad));
        Rad = Atan(Rad);
        return Rad;
    }
    
    inline float Acos(float Rad)
    {
        Rad = Sqrt((1-Rad*Rad)/(Rad*Rad));
        Rad = Atan(Rad);
        return Rad;
    }
    
    inline float Acot(float Rad)
    {
        Rad = 1/Rad;
        Rad = Atan(Rad);
        return Rad;
    }
    
    inline float Pow(float Base, float Power)
    {
        _asm
        {
            fld DWORD PTR [Power]
            fld DWORD PTR [Base]
            fld1
            fsub
            fyl2xp1
            sub     esp,16                                ; z = x*log2
            fist    DWORD PTR [esp+12]            ; round 
            fld1
            fstp    TBYTE PTR [esp]
            fisub   DWORD PTR [esp+12]            ; z - round 
            mov     eax, [esp+12]
            add     [esp+8],eax
            f2xm1
            fld1
            fadd
            fld     TBYTE PTR [esp]               ; 2^(round )
            fmul                                  ; 2^z = e^x
            add     esp,16
            fstp DWORD PTR [Base]
        }
        return Base;
    }
    
    inline double Log(double N)
    {
        _asm
        {
            fld QWORD ptr[N]
            fld1
            fyl2x
            fldl2t
            fdiv
            fstp QWORD ptr[N]
        }
        return N;
    }
    
    inline double Ln(double N)
    {
        _asm
        {
            fld QWORD ptr[N]
            fld1
            fyl2x
            fldl2e
            fdiv
            fstp QWORD ptr[N]
        }
        return N;
    }
    
    
    inline int Random(int Min, int Max)
    {
        unsigned int LowWord;
        _asm  
        {  
            _emit 0x0F
            _emit 0x31
            mov LowWord, eax  
        }
        return (int)((LowWord & 0xFFFF) / (float)0x10000 * (Max - Min + 1)) + Min;
    }
#endif // _WIN
    
}


#endif // MATH_ASM_H
