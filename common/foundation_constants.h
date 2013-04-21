//
//  foundation_constants.h
//  This is a header which should be included with each system dll. It contains
//  a number of system wide maximums which should be followed.
//
//  Created by Ryan Sheffer on 2013-03-29.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef launcher_foundation_constants_h
#define launcher_foundation_constants_h

/**
 * The Foundation namespace.
 * If anything is changed here, all libraries will need to be recompiled.
 */
namespace Foundation
{
    /**
     * The Engine Version. This is a number sent with the handshake between
     * systems local or networked to ensure compatibility.
     */
    const unsigned int      ENGINE_VERSION                  = 1;
    
    /** The maximum number of entities which are allowed to be networked. */
    const unsigned int      MAX_SHARED_BASE_ENTITIES        = 512;
    
    /** The maximum number of windows which can be created. */
    const unsigned int      MAX_PLATFORM_WINDOWS            = 4;
    
    /** Lowest supported resolution width */
    const unsigned int      LOWEST_SCREEN_WIDTH             = 800;
    
    /** Lowest supported resolution height */
    const unsigned int      LOWEST_SCREEN_HEIGHT            = 600;
    
    /** IPhone 1-3 resolution */
    const unsigned int      IPHONE_SCREEEN_WIDTH            = 320;
    const unsigned int      IPHONE_SCREEEN_HEIGHT           = 480;
    
    /** IPhone 4+ resolution */
    const unsigned int      IPHONE_4_SCREEN_WIDTH           = 640;
    const unsigned int      IPHONE_4_SCREEN_HEIGHT          = 960;
}

#endif
