//
//  main.m
//  Main entry point for the MAC implementation of the Genesis Project
//
//  Created by Ryan Sheffer on 2012-10-07.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "file_tga.h"

int main(int argc, char *argv[])
{
    static char szFileLine[2048];
    printf( "working directory: %s\n", getcwd(szFileLine, sizeof(szFileLine)) );
    
    //FileTypes::CTGAFile tgaFile;
    //tgaFile.LoadTGA("genesis.app/Contents/Resources/test.tga");
    
    return NSApplicationMain(argc, (const char **)argv);
}
