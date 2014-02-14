//
//  debug.cpp
//
//  Created by Ryan Sheffer on 2012-10-08.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "debug.h"

#ifdef _MAC

// We need some core API stuff here...
#include <CoreFoundation/CoreFoundation.h>
//#include <CoreServices/CoreServices.h>

int MessageBox(void *hWnd, char* lpText, char* lpCaption, unsigned int uType)
{
    //convert the strings from char* to CFStringRef
    CFStringRef header_ref      = CFStringCreateWithCString( NULL,
                                                            lpCaption,
                                                            kCFStringEncodingASCII );
    
    CFStringRef message_ref  = CFStringCreateWithCString( NULL,
                                                         lpText,
                                                         kCFStringEncodingASCII );
    
    CFOptionFlags result;  //result code from the message box
    
    //launch the message box
    CFUserNotificationDisplayAlert(0,               // no timeout
                                   kCFUserNotificationPlainAlertLevel,
                                   NULL,            //message_type flags
                                   NULL,            //not used
                                   NULL,            //localization of strings
                                   header_ref,      //header text
                                   message_ref,     //message text
                                   CFSTR("Abort"),  //default "ok" text in button
                                   CFSTR("Retry"),  //alternate button title
                                   CFSTR("Ignore"), //other button title, null--> no other button
                                   &result);        //response flags
    
    //Clean up the strings
    CFRelease( header_ref );
    CFRelease( message_ref );
    
    //Convert the result
    if( result == kCFUserNotificationDefaultResponse )
        return IDABORT;
    else if( result == kCFUserNotificationAlternateResponse )
        return IDCANCEL;
    else if( result == kCFUserNotificationOtherResponse )
        return IDIGNORE;
    
    return IDCANCEL;
}

#elif defined(_WIN)

int MessageBoxWIN(void *hWnd, char* lpText, char* lpCaption, unsigned int uType)
{
    return MessageBox((HWND)hWnd, lpText, lpCaption, uType);
}

#endif