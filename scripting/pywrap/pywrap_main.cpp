//
//  main.cpp
//  pywrap
//
//  Created by Ryan Sheffer on 2014-07-05.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include <stdio.h>
#include <Python.h>
#include "pywrap_main.h"
#include "pywrap_error.h"

#define PY_RUN(a)   { \
                        int ret = PyRun_SimpleString(a); \
                        if(ret) \
                        { \
                            printf("error running python call (" a ")"); \
                            return PYWRAP_INIT_FAIL; \
                        } \
                    }

namespace pywrap {
    
/*
PyObject *pModuleDict = PyImport_GetModuleDict();
PyObject *key, *value;
Py_ssize_t pos = 0;
while (PyDict_Next(pModuleDict, &pos, &key, &value))
{
// do something interesting with the values...
const char *pszKey = PyString_AsString(key);
if (pszKey == NULL && PyErr_Occurred())
{
return 1;
}
if(strcmp("sys", pszKey) == 0)
printf("%s\n", pszKey);
}*/

//------------------------------------------------------------------------------
/**
 * Initialize Pywrap
 */
int InitializePywrap(const char *pszScriptsRoot)
{
    // Initialize the Python interpreter.
    Py_Initialize();
    
    if(Py_IsInitialized() == 0)
    {
        printf("Could not initialize python!\n");
        return 1;
    }
    
    PY_RUN("import sys");
    PY_RUN("sys.path.append('/Users/ryansmac/Documents/project/pywrap/pywrap')");
    
    // Convert the file name to a Python string.
    PyObject *pName = PyString_FromString("addtest");
    
    // Import the file as a Python module.
    PyObject *pModule = PyImport_Import(pName);
    
    // Create a dictionary for the contents of the module.
    PyObject *pDict = PyModule_GetDict(pModule);
    
    // Get the add method from the dictionary.
    PyObject *pFunc = PyDict_GetItemString(pDict, "add");
    
    // Create a Python tuple to hold the arguments to the method.
    PyObject *pArgs = PyTuple_New(2);
    
    // Convert 2 to a Python integer.
    PyObject *pValue = PyInt_FromLong(2);
    
    // Set the Python int as the first and second arguments to the method.
    PyTuple_SetItem(pArgs, 0, pValue);
    PyTuple_SetItem(pArgs, 1, pValue);
    
    // Call the function with the arguments.
    printf("Calling Python to find the sum of 2 and 2.\n");
    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
    
    // Print a message if calling the method failed.
    if(pResult == NULL)
    {
        printf("Calling the add method failed.\n");
    }
    
    // Convert the result to a long from a Python object.
    long result = PyInt_AsLong(pResult);
    
    // Destroy the Python interpreter.
    Py_Finalize();
    
    // Print the result.
    printf("The result is %ld.\n", result);
    
    return PYWRAP_NO_ERROR;
}
    
}

/** This is a test application for testing the python wrapper. */
int pywrap_test(int argc, const char * argv[])
{
    // Strip out the argument
    
    
    pywrap::InitializePywrap("scripts/");
    return 0;
}