#pragma once

#include <windows.h>
#include <tchar.h>
#include <string.h>

// ID menu for GUI components
#define IDC_0BTN (100)
#define IDC_1BTN (101)
#define IDC_2BTN (102)
#define IDC_3BTN (103)
#define IDC_4BTN (104)
#define IDC_5BTN (105)
#define IDC_6BTN (106)
#define IDC_7BTN (107)
#define IDC_8BTN (108)
#define IDC_9BTN (109)
#define IDC_CBTN (110)
#define IDC_CEBTN (111)
#define IDC_PBTN (112)
#define IDC_SBTN (113)
#define IDC_MBTN (114)
#define IDC_DBTN (115)
#define IDC_PcBTN (116)
#define IDC_DcBTN (117)
#define IDC_EBTN (118)
#define IDC_TFBTN (119)
#define IDC_TOBTN (120)
#define IDC_CTBTN (121)
#define IDC_TCBTN (122)
#define IDC_IOTB (123)
#define IDC_TrTB (124)
#define IDC_ITFB (125)
#define IDC_ITOB (126)

// Global Variables
#define MAXINPUTLENGTH (20)
//#define TRACEBUFFER (16384) //Bytes
//#define TRACEBUFFER (32768)
#define TRACEBUFFER (65536)

// Declaring global variables for both CalcLogic.cpp and Calc.cpp
extern TCHAR input[MAXINPUTLENGTH + 1];
extern TCHAR traceList[TRACEBUFFER + 1];
extern TCHAR currTrace[TRACEBUFFER + 1];
extern int traceNo;
extern int inputLength;
extern TCHAR* solve(TCHAR*);
extern bool extendedTrace;
extern bool TRACEON;