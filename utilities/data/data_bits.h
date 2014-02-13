//
//  data_bits.h
//  Classes for helping traversal of and setting of individual bits.
//
//  Created by Ryan Sheffer on 11/17/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_BITS_H
#define DATA_BITS_H

#ifdef _WIN
#pragma once
#endif

namespace data
{
    //--------------------------------------------------------------------------
    /** 
     * A class designed for helping with traversal of a number of bytes
     * bit by bit.
     */
    class BitGetter
    {
    public:
        /** The position of the current byte */
        const byte      *pPos;
        
        /** The number of bits left to traverse before incrementing the byte */
        unsigned int    bitsLeft;
        
        /** Constructor */
        BitGetter(const byte *pStartingByte)
        {
            pPos = pStartingByte;
            bitsLeft = 8;
        }
        
        /** Gets the next bits state, and increments the byte pointer if needed. */
        bool GetNextBitState(void)
        {
            --bitsLeft;
            bool bitState = ((*pPos) >> bitsLeft) & 0x01;
            
            if(bitsLeft == 0)
            {
                ++pPos;
                bitsLeft = 8;
            }
            
            return bitState;
        }
    };
    
    //--------------------------------------------------------------------------
    /**
     * A class designed for helping with the setting of individual bits one at
     * a time, from right to left.
     */
    class BitSetter
    {
    public:
        /** The position of the current byte */
        byte            *pPos;
        
        /** The number of bits left to traverse before incrementing the byte */
        unsigned int    bitsLeft;
        
        /** Constructor */
        BitSetter(byte *pStartingByte)
        {
            pPos = pStartingByte;
            bitsLeft = 8;
        }
        
        /** Sets the next bit in line */
        void SetNextBitState(bool state)
        {
            --bitsLeft;
            (*pPos) = (*pPos) | (byte(state?1:0) << bitsLeft);
            
            if(bitsLeft == 0)
            {
                ++pPos;
                bitsLeft = 8;
            }
        }
    };
}

#endif // DATA_BITS_H
