//
//  Launcher.cpp
//  Launcher Main
//
//  Created by Ryan Sheffer on 2014-02-08.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "Launcher.h"
#include "CPlatform.h"
#include <strsafe.h>
#include "IEngine.h"
#include "memory\memory_interface.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;                                      // current window
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Threaded Engine
DWORD WINAPI EngineThread( LPVOID lpParam );
HANDLE engineMutex = 0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//------------------------------------------------------------------------------
/** This is the pointer to the WIN specific platform interface */
static CPlatform g_platform;
IPlatform *GetPlatform(void)
{
    return &g_platform;
}

/** The platform is registered early on so all systems can access it */
REGISTER_STATIC_INTERFACE(g_platform,
                          PLATFORM_INTERFACE_NAME,
                          PLATFORM_INTERFACE_VERSION);

//------------------------------------------------------------------------------
/**
 * Win Main
 */
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    // Before ANYTHING, we need to initialize all the stuff needed by the engine

    // Initialize Memory Pool ( Creates all general pools for system allocations )
    GetMemoryPool()->Initialize();

    // Initialize the platform wrapper
    g_platform.Initialize();
    g_platform.LogPlatformCaps();
    // Done Initializing Engine Stuff

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAUNCHER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAUNCHER));

    Logging::Msg("Created Windows");

    // Create the engine thread mutex
    engineMutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

    // Create the engine thread
    DWORD  engineThreadID = 0;
    HANDLE engineThread = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            EngineThread,           // thread function name
            NULL,                   // argument to thread function 
            0,                      // use default creation flags 
            &engineThreadID);       // returns the thread identifier

    ASSERTION(engineThread != NULL, "Unable to create engine thread!");
    if(engineThread == NULL)
    {
        Logging::Warning("Unable to create engine thread!");
        ExitProcess(3);
    }

    Logging::Msg("Finished Launching Engine Thread");

	// windows message loop:
    DWORD code = 0;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

        if(GetExitCodeThread(engineThread, &code))
        {
            if(code != STILL_ACTIVE)
            {
                if(code == 1)
                {
                    Logging::Warning("Engine exited under strange circumstances");
                }

                break;
            }
        }
	}

    CloseHandle(engineThread);
    CloseHandle(engineMutex);

	return (int)code; // msg.wParam;
}

//------------------------------------------------------------------------------
/** Engine States */
enum engine_state_e
{
    ENGINE_STATE_INACTIVE,
    ENGINE_STATE_ACTIVE,
    ENGINE_STATE_CLOSING,
};

/** The State the engine is currently in.
 * NOTE: Only change this state if you have an engine mutex lock */
engine_state_e engineState = ENGINE_STATE_INACTIVE;

//------------------------------------------------------------------------------
/**
 * Engine Thread
 */
DWORD WINAPI EngineThread( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    // This is nessesary for our file structure. We are not using apples APP
    // package and resource folders because it isn't modder friendly. ~RFS
    //chdir(GetPlatform()->GetAbsoluteApplicationPath());
    Logging::Msg("Setting Application Path to %s\n", GetPlatform()->GetAbsoluteApplicationPath());
    
    DLLHANDLE dllHandle = GetPlatform()->LoadDLL("engine.dll");
    if(dllHandle == NULL)
    {
        ASSERTION(dllHandle, "Unable to load Engine DLL!");
        return 1;
    }
    
    IEngine *pEngine = static_cast<IEngine *>
            (GetInterfaceRegistration()->GetInterface(ENGINE_INTERFACE_NAME,
                                                      ENGINE_INTERFACE_VERSION));
    
    if(pEngine == NULL)
    {
        ASSERTION(pEngine, "Engine DLL loaded, but unable to create an interface to it!");
        return 1;
    }
    
    pEngine->Initialize();

    bool shouldExit = false;
    while(shouldExit == false)
    {
        DWORD dwWaitResult;
        dwWaitResult = WaitForSingleObject(engineMutex, INFINITE);
        if(dwWaitResult == WAIT_OBJECT_0)
        {
            if(engineState == ENGINE_STATE_CLOSING || pEngine->FinishedExecution())
            {
                shouldExit = true;
                break;
            }
            else
            {
                engineState = ENGINE_STATE_ACTIVE;
            
                //CPerfTimer engine_timer("Engine Run Time", true);
                pEngine->Run();
                //engine_timer.PrintTimer();
            }

            ReleaseMutex(engineMutex);
        }
    }

    pEngine->Shutdown();
    
    // Now release the interface pointer
    GetInterfaceRegistration()->ReleaseInterfacePointer(ENGINE_INTERFACE_NAME, pEngine);
    
    // Release any un-released interfaces (they will be reported)
    GetInterfaceRegistration()->ReleaseAllInterfacePointers();
    
    GetPlatform()->UnloadDLL(dllHandle);
    
    engineState = ENGINE_STATE_INACTIVE;
    
    ReleaseMutex(engineMutex);

    return 0;
}

//------------------------------------------------------------------------------
/**
 * Registers the window class.
 */
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAUNCHER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAUNCHER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//------------------------------------------------------------------------------
/**
 * Saves instance handle and creates main window
 * In this function, we save the instance handle in a global variable and
 * create and display the main program window.
 */
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//------------------------------------------------------------------------------
/**
 * Processes messages for the main window.
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 * @return result
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
        {
		    DWORD dwWaitResult;
            dwWaitResult = WaitForSingleObject(engineMutex, INFINITE);
            if(dwWaitResult == WAIT_OBJECT_0)
            {
                engineState = ENGINE_STATE_CLOSING;
                ReleaseMutex(engineMutex);
            }
        }
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//------------------------------------------------------------------------------
/**
 * Message handler for about box.
 */
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
