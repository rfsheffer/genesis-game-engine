//
//  IPlatform.h
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IPLATFORM_H
#define IPLATFORM_H

class IPlatform
{
public:
    virtual void Initialize(void) = 0;
    virtual void Shutdown(void) = 0;
};

#endif // IPLATFORM_H
