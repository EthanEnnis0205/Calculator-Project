// Calc.cpp

#include "Resource.h"

// Constants for buttons dimensions (for formatting)
const int BHEIGHT = 60;
const int BLENGTH = 50;

// Constants for button positions (Y position of top left-most button) (for formatting)
const int BYORGIN = 120;

// Button Spacing (for formatting)
const int BSPACE = 10;

// Constants for window size (for formating)
const int WLENGTH = 400;
const int WHEIGHT = 450;

// Constants for window borders (for formatting)
const int BTMBRDR = WHEIGHT - 25 - BHEIGHT;
const int LFTBRDR = 25;
const int RGHTBRDR = WLENGTH - (2*25) - BLENGTH;
const int TPBRDR = 25;

// Declaration of Global Variables
// input[] will store the current string inputted
TCHAR input[MAXINPUTLENGTH + 1] = _T("");
// traceList[] will store the trace through the entire code
TCHAR traceList[TRACEBUFFER + 1] = _T("");
TCHAR currTrace[TRACEBUFFER + 1] = _T("");
// traceNo stores the current trace step
int traceNo = 1;
// inputLength will prevent any overload in input
int inputLength = 0;
// TRACEON will keep track of whether the trace is on or off
bool TRACEON = false;
// extendedTrace will change the formatting of each trace
/// ONLY USE TRUE FOR TROUBLESHOUTING SMALL EQUATIONS ///
bool extendedTrace = false;



// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND currentWnd;


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex1;
    WNDCLASSEX wcex2;

    // Initialize all aspects for the Calculator Window class
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW;
    wcex1.lpfnWndProc = WndProc;
    wcex1.cbClsExtra = 0;
    wcex1.cbWndExtra = 0;
    wcex1.hInstance = hInstance;
    wcex1.hIcon = LoadIcon(wcex1.hInstance, IDI_APPLICATION);
    wcex1.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex1.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex1.lpszMenuName = NULL;
    wcex1.lpszClassName = _T("CalcApp");
    wcex1.hIconSm = LoadIcon(wcex1.hInstance, IDI_APPLICATION);

    // Initialize all aspects for the Trace Window class
    wcex2.cbSize = sizeof(WNDCLASSEX);
    wcex2.style = CS_HREDRAW | CS_VREDRAW;
    wcex2.lpfnWndProc = WndProc;
    wcex2.cbClsExtra = 0;
    wcex2.cbWndExtra = 0;
    wcex2.hInstance = hInstance;
    wcex2.hIcon = LoadIcon(wcex2.hInstance, IDI_APPLICATION);
    wcex2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex2.lpszMenuName = NULL;
    wcex2.lpszClassName = _T("TraceApp");
    wcex2.hIconSm = LoadIcon(wcex2.hInstance, IDI_APPLICATION);

    // If registering the classes fail...
    if (!RegisterClassEx(&wcex1) || !RegisterClassEx(&wcex2))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application


    /*HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW, // Optional extended window style
        _T("DesktopApp"),       // Name
        szTitle,                // Window Text
        WS_OVERLAPPEDWINDOW,    // styles
        CW_USEDEFAULT,          // x position
        CW_USEDEFAULT,          // y position
        WLENGTH,                // width
        WHEIGHT,                // height
        NULL,                   // parent
        NULL,                   // menu
        hInstance,              // instance
        NULL                    // NULL
    ); */
    
    ////// CREATING WINDOWS //////

    // Instance of the Calculator Window
    HWND CalcWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        _T("CalcApp"),
        _T("VS Merlot Calculator Project: Calculator"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT,
        WLENGTH, 
        WHEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // Instance of the Trace Window
    HWND TraceWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        _T("TraceApp"),
        _T("VS Merlot Calculator Project: Trace"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WLENGTH,
        WHEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // Set the currentWnd to the Calculator Window
    currentWnd = CalcWnd;
    
    
    ////// CREATING TABS //////

    // Instance of the Calculator Tab button on the Trace Window
    HWND CCalcTab = CreateWindowEx(
        0,
        _T("BUTTON"),
        _T("Calculator"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_AUTOCHECKBOX | WS_DISABLED,
        1,
        0,
        63,
        20,               
        CalcWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
        NULL
    );
    SendMessage(CCalcTab, BM_SETCHECK, TRUE, TRUE);

    // Instance of the Trace Tab button on the Trace 
    HWND CTraceTab = CreateWindowEx(
        0,
        _T("BUTTON"),
        _T("Trace Logic"),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        64,
        0,
        63,
        20,
        CalcWnd,
        (HMENU)IDC_CTBTN,
        (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
        NULL 
    );

    // Instance of the Calculator Tab button on the Calculator Window
    HWND TCalcTab = CreateWindowEx(
        0,
        _T("BUTTON"),
        _T("Calculator"), 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD, 
        1,
        0,
        63,
        20,
        TraceWnd,
        (HMENU)IDC_TCBTN,
        (HINSTANCE)GetWindowLongPtr(TraceWnd, GWLP_HINSTANCE),
        NULL
    );

    // Instance of the Trace Tab button on the Calculator Window
    HWND TTraceTab = CreateWindowEx(
        0,
        _T("BUTTON"),
        _T("Trace Logic"), 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_AUTOCHECKBOX | WS_DISABLED, 
        64,
        0,
        63,
        20,
        TraceWnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(TraceWnd, GWLP_HINSTANCE),
        NULL
    );
    SendMessage(TTraceTab, BM_SETCHECK, TRUE, TRUE);


    ////// CREATING FONTS //////

    // Font used for all of the buttons
    HFONT baFont = CreateFont(
        20, 
        0, 
        0, 
        0, 
        FW_DONTCARE, 
        FALSE, 
        FALSE, 
        FALSE, 
        ANSI_CHARSET, 
        OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, 
        DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_SWISS, 
        L"Arial"
    );

    // Font used for all of the tab bars
    HFONT bbFont = CreateFont(
        14,
        0,
        0,
        0,
        FW_DONTCARE,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"Arial"
    );

    // Font used for the input text box
    HFONT bcFont = CreateFont(
        40,
        13,
        0,
        0,
        FW_DONTCARE,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"Arial"
    );

    // Initializing the font for all of the tabs
    SendMessage(CCalcTab, WM_SETFONT, WPARAM(bbFont), TRUE);
    SendMessage(CTraceTab, WM_SETFONT, WPARAM(bbFont), TRUE);
    SendMessage(TCalcTab, WM_SETFONT, WPARAM(bbFont), TRUE);
    SendMessage(TTraceTab, WM_SETFONT, WPARAM(bbFont), TRUE);


    ////// CREATE CALCULATOR BUTTONS //////

        // First Row
        // Instance of 7 button (and set font)
        HWND SevenButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("7"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR,
            BYORGIN,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_7BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(SevenButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 8 button (and set font)
        HWND EightButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("8"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + BLENGTH + BSPACE,
            BYORGIN,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_8BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(EightButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 9 button (and set font)
        HWND NineButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("9"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + (2 * BLENGTH) + (2 * BSPACE),
            BYORGIN,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_9BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(NineButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of C button (and set font)
        HWND CButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("C"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR - BLENGTH - BSPACE,
            BYORGIN,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_CBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(CButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of CE button (and set font)
        HWND CEButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("CE"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR,
            BYORGIN,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_CEBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(CEButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Second Row
        // Instance of 4 button (and set font)
        HWND FourButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("4"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR,
            BYORGIN + BHEIGHT + BSPACE,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_4BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(FourButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 5 button (and set font)
        HWND FiveButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("5"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + BLENGTH + BSPACE,
            BYORGIN + BHEIGHT + BSPACE,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_5BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(FiveButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 6 button (and set font)
        HWND SixButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("6"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + (2 * BLENGTH) + (2 * BSPACE),
            BYORGIN + BHEIGHT + BSPACE,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_6BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(SixButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of + button (and set font)
        HWND PlusButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("+"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR - BLENGTH - BSPACE,
            BYORGIN + BHEIGHT + BSPACE,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_PBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(PlusButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of - button (and set font)
        HWND MinusButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("-"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR,
            BYORGIN + BHEIGHT + BSPACE,
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_SBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(MinusButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Third Row
        // Instance of 1 button (and set font)
        HWND OneButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("1"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR,
            BYORGIN + (2 * BHEIGHT) + (2 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_1BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(OneButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 2 button (and set font)
        HWND TwoButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("2"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + BLENGTH + BSPACE,
            BYORGIN + (2 * BHEIGHT) + (2 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_2BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(TwoButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of 3 button (and set font)
        HWND ThreeButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("3"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + (2 * BLENGTH) + (2 * BSPACE),
            BYORGIN + (2 * BHEIGHT) + (2 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_3BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(ThreeButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of * button (and set font)
        HWND MultButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("*"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR - BLENGTH - BSPACE,
            BYORGIN + (2 * BHEIGHT) + (2 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_MBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(MultButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of / button (and set font)
        HWND DivButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("/"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR,
            BYORGIN + (2 * BHEIGHT) + (2 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_DBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(DivButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Last Row
        // Instance of 0 button (and set font)
        HWND ZeroButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("0"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR,
            BYORGIN + (3 * BHEIGHT) + (3 * BSPACE),
            (2 * BLENGTH) + BSPACE,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_0BTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(ZeroButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of . button (and set font)
        HWND DecButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("."), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            LFTBRDR + (2 * BLENGTH) + (2 * BSPACE),
            BYORGIN + (3 * BHEIGHT) + (3 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_DcBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(DecButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of = button (and set font)
        HWND EqButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("="), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR - BLENGTH - BSPACE,
            BYORGIN + (3 * BHEIGHT) + (3 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_EBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(EqButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of % button (and set font)
        HWND PercButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("%"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
            RGHTBRDR,
            BYORGIN + (3 * BHEIGHT) + (3 * BSPACE),
            BLENGTH,
            BHEIGHT,
            CalcWnd,
            (HMENU)IDC_PcBTN,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(PercButton, WM_SETFONT, WPARAM(baFont), TRUE);

        // Instance of Intro to Trace On button (and set font)
        HWND IntTRACEONButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("Intro Trace On"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_AUTOCHECKBOX | WS_GROUP, 
            RGHTBRDR - 120,
            20,
            80,
            20,
            CalcWnd,
            (HMENU)IDC_ITOB,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(IntTRACEONButton, WM_SETFONT, WPARAM(bbFont), TRUE);

        // Instance of Intro to Trace Off button (and set font)
        HWND IntTraceOffButton = CreateWindowEx(
            0,
            _T("BUTTON"),
            _T("Intro Trace Off"), 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_AUTOCHECKBOX | WS_GROUP | WS_DISABLED, 
            RGHTBRDR - 30,
            20,
            80,
            20,
            CalcWnd,
            (HMENU)IDC_ITFB,
            (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
            NULL
        );
        SendMessage(IntTraceOffButton, WM_SETFONT, WPARAM(bbFont), TRUE);
        SendMessage(IntTraceOffButton, BM_SETCHECK, TRUE, TRUE);


    ////// CREATE OUTPUT TEXT BOXES //////
    // Instance of the Input/Output Textbox on calculator screen
    HWND IOTextBox = CreateWindowEx(
        0,
        _T("EDIT"),
        input,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
        LFTBRDR - 10,
        TPBRDR + 30,
        WLENGTH - (3*LFTBRDR) + 20,
        45,
        CalcWnd,
        (HMENU)IDC_IOTB,
        (HINSTANCE)GetWindowLongPtr(CalcWnd, GWLP_HINSTANCE),
        NULL
    );

    // Instance of the Trace Textbox on the Trace screen
    HWND TraceTextBox = CreateWindowEx(
        0,
        _T("EDIT"),
        traceList,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_READONLY | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_MULTILINE,
        LFTBRDR - 20,
        TPBRDR,
        WLENGTH - (3 * (LFTBRDR - 15)),
        WHEIGHT - (3 * TPBRDR) - 10,
        TraceWnd,
        (HMENU)IDC_TrTB,
        (HINSTANCE)GetWindowLongPtr(TraceWnd, GWLP_HINSTANCE),
        NULL
    );
    SendMessage(IOTextBox, WM_SETFONT, WPARAM(bcFont), TRUE);

    // If either window fail...
    if (!CalcWnd && !TraceWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Something went wrong"),
            NULL);

        return 1;
    }

    // Show the respective window
    if (currentWnd) {
        ShowWindow(currentWnd, nCmdShow);
        UpdateWindow(currentWnd);
    }
    
    // Main message loop:
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HWND IOInst = GetDlgItem(hWnd, IDC_IOTB);
    HWND TrInst = FindWindow(NULL, _T("VS Merlot Calculator Project: Trace"));
    HWND TraceInst = GetDlgItem(TrInst, IDC_TrTB);
    HWND TrOn = GetDlgItem(hWnd, IDC_ITOB);
    HWND TrOff = GetDlgItem(hWnd, IDC_ITFB);
    TCHAR* tempOutput;
    int size;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        // Functionality for 0 button
        case IDC_0BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("0"));
                SetWindowText(IOInst, input);
                inputLength++;
            }

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '0'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '0' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 1 button
        case IDC_1BTN:
            
            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("1"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '1'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '1' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 2 button
        case IDC_2BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("2"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '2'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '2' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 3 button
        case IDC_3BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("3"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '3'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '3' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 4 button
        case IDC_4BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("4"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '4'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '4' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 5 button
        case IDC_5BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("5"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '5'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '5' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 6 button
        case IDC_6BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("6"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '6'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '6' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 7 button
        case IDC_7BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("7"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {      
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '7'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '7' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 8 button
        case IDC_8BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("8"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '8'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '8' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for 9 button
        case IDC_9BTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("9"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '9'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '9' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for C button
        case IDC_CBTN:
            
            input[0] = _T('\0');
            inputLength = 0;
            SetWindowText(IOInst, input);

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. CLEAR ALL\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Clear all input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for CE button
        case IDC_CEBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            size = GetWindowText(IOInst, (LPWSTR)input, MAXINPUTLENGTH);
            if (size != 0) {
                input[size - 1] = '\0';
                inputLength--;
            }
            SetWindowText(IOInst, input);

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. CLEAR LAST\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Delete previous entry from input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for + button
        case IDC_PBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("+"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '+'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '+' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for - button
        case IDC_SBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("-"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '-'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '-' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for * button
        case IDC_MBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("*"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) { 
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '*'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '*' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for / button
        case IDC_DBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("/"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '/'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '/' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for % button
        case IDC_PcBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("%"));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '%%'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '%%' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for . button
        case IDC_DcBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF inputLength is less than MAXINPUTLENGTH...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If inputLength is less than MAXINPUTLENGTH, then add the character to input and increment inputLength
            if (inputLength < MAXINPUTLENGTH) {
                wcscat_s(input, _T("."));
                SetWindowText(IOInst, input);
                inputLength++;
            }
            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. INSERT '.'\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Insert '.' into the current input (Current input: %ls)\r\n"), traceNo, input); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for = button
        case IDC_EBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            tempOutput = new TCHAR[MAXINPUTLENGTH];
            inputLength = 0;
            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // Solve() the current input
            tempOutput = solve(input);
            SetWindowText(IOInst, input);


            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF an empty string was not returned...(tempOutput: %ls)\r\n"), traceNo, tempOutput); wcscat_s(traceList, currTrace); traceNo++; }
            // If the result was not empty
            if (tempOutput[0] != '\0') {
                input[0] = '\0';
                wcscat_s(input, tempOutput);
                SetWindowText(IOInst, input);
            }
            else { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE do nothing...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. DISPLAY ANSWER\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Return the answer to the equation (Current input: %ls)\r\n"), traceNo, tempOutput); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for Calculator to Trace Tab button
        case IDC_CTBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            ShowWindow(currentWnd, SW_HIDE);
            UpdateWindow(currentWnd);
            currentWnd = FindWindow(NULL, _T("VS Merlot Calculator Project: Trace"));
            ShowWindow(currentWnd, SW_SHOW);
            UpdateWindow(currentWnd);

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. SWITCH TAB\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Switch to 'Trace Logic' Tab \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for Trace To Calculator Tab button
        case IDC_TCBTN:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            ShowWindow(currentWnd, SW_HIDE);
            UpdateWindow(currentWnd);
            currentWnd = FindWindow(NULL, _T("VS Merlot Calculator Project: Calculator"));
            ShowWindow(currentWnd, SW_SHOW);
            UpdateWindow(currentWnd);

            if (TRACEON) {
                if (!extendedTrace) { swprintf_s(currTrace, _T("%d. SWITCH TAB\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } else { swprintf_s(currTrace, _T("%d. Switch to 'Calculator' Tab \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
                SetWindowText(TraceInst, traceList);
            }
            return TRUE;

        // Functionality for the Intro to Trace Off Button
        case IDC_ITFB:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            EnableWindow(TrOn, TRUE);
            EnableWindow(TrOff, FALSE);
            SendMessage(TrOn, BM_SETCHECK, FALSE, TRUE);
            TRACEON = FALSE;
            traceList[0] = _T('\0');
            traceNo = 1;
            SetWindowText(TraceInst, traceList);

            return TRUE;

        // Functionality for the Intro to Trace On Button
        case IDC_ITOB:

            if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF current input is an error message...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
            // If the current input is an error message, clear it
            if (input[inputLength - 1] == 'r') {
                input[0] = _T('\0');
                inputLength = 0;
                SetWindowText(IOInst, input);
            }

            EnableWindow(TrOff, TRUE);
            EnableWindow(TrOn, FALSE);
            SendMessage(TrOff, BM_SETCHECK, FALSE, TRUE);
            TRACEON = TRUE;
            traceList[0] = _T('\0');
            traceNo = 1;

            return TRUE;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}