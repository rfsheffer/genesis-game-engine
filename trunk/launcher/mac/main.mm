//
//  main.m
//  Main entry point for the MAC implementation of the Genesis Project
//
//  Created by Ryan Sheffer on 2012-10-07.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "ScriptParse.h"
#include "CExtensions.h"

int main(int argc, char *argv[])
{
    static char szFileLine[2048];
    printf( "working directory: %s\n", getcwd(szFileLine, sizeof(szFileLine)) );
    
    CExtensions     *pExtensions = new CExtensions();
    pExtensions->CreateAllExtensions();
    
    // Only read in 8 places
    //float f = 407.92948291f;
    //printf("%1.8f\n", f);
    
    /*ScriptParse::CScriptLexer newLex;
    
    newLex.Analyze("8*5+10-2/2+8*9-3+20-2/5*2");
    
    ScriptParse::CScriptParse newParse;
    
    newParse.Parse(newLex.GetTokens(), newLex.GetNumTokens());
    
    //newParse.PrintOutput();
    
    ScriptParse::CPostfixEvaluate newEval;
    
    float output = newEval.Evaluate(newParse.GetOutput(), newParse.GetNumOutput());
    
    printf("%f\n", output);*/
    
    pExtensions->DestroyAllExtensions();
    delete pExtensions;
    
    return 1;
    //return NSApplicationMain(argc, (const char **)argv);
}
