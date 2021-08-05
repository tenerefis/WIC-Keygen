#include "framework.h"
#include "resource.h"

#include "stdafx.h"
#include "main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szBtnGenerate[MAX_LOADSTRING];
WCHAR szBtnQuit[MAX_LOADSTRING];

HWND hWnd;
HWND hWndTextbox;
HWND hWndGenerate;
HWND hWndQuit;

HFONT hFont;
LOGFONT lf;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KEYVALIDATORGUI, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_BTNGENERATE, szBtnGenerate, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_BTNQUIT, szBtnQuit, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYVALIDATORGUI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KEYVALIDATORGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 350, 120, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // center the window
   int xPos = (GetSystemMetrics(SM_CXSCREEN) - 350) / 2;
   int yPos = (GetSystemMetrics(SM_CYSCREEN) - 120) / 2;
   SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

   // create form objects
   hWndTextbox = CreateWindowW(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
	   10,
	   20,
	   220,
	   20,
	   hWnd,
	   (HMENU)ID_TEXTBOX,
	   (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
	   NULL);

   hWndGenerate = CreateWindowW(L"BUTTON", szBtnGenerate, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	   240,     // x position 
	   20,      // y position 
	   80,      // Button width
	   20,      // Button height
	   hWnd,    // Parent window
	   (HMENU) IDM_GENERATE,  // No menu.
	   (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
	   NULL);   // Pointer not needed.

   hWndQuit = CreateWindowW(L"BUTTON", szBtnQuit, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	   240,
	   45,
	   80,
	   20,
	   hWnd,
	   (HMENU) IDM_EXIT,
	   (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
	   NULL);

   // setup font object
   GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
   hFont = CreateFont(lf.lfHeight, lf.lfWidth,
	   lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
	   lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
	   lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
	   lf.lfPitchAndFamily, lf.lfFaceName);

   // set the font for the three controls
   SendMessage(hWndTextbox, WM_SETFONT, (WPARAM)hFont, TRUE);
   SendMessage(hWndGenerate, WM_SETFONT, (WPARAM)hFont, TRUE);
   SendMessage(hWndQuit, WM_SETFONT, (WPARAM)hFont, TRUE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	// cdkey buffer
	char key[26] = "------------------------";

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the button clicks:
            switch (wmId)
            {
            case IDM_GENERATE:
				
				// put the generated key into the textbox
				GenerateRandomKey(key);
				SetWindowTextA(hWndTextbox, key);
				
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}