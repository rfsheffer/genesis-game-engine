//
//  main.m
//  Main entry point for the MAC implementation of the Genesis Project
//
//  Created by Ryan Sheffer on 2012-10-07.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

// Objective-C headers go here
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>

// Carbon, the low level graphics API for MAC
#include <Carbon/Carbon.h>

int main(int argc, char *argv[])
{
    // Start the cocoa application, see CCocoaWrapper for where the engine starts.
    return NSApplicationMain(argc, (const char **)argv);
}
