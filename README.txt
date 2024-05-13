### README ###
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c


Author: 
	Ethan Ennis
Project: 
	C++ Calculator Project with limited libraries (<windows.h>, <tchar.h>, <string.h>)
Project Description: 
	Simple Calculator that can multiply, divide, add, subtract, and do percentage addition all while following the order of operations.
	Along with this, there is functionality to trace the logic behind the calculations to measure comparisions and decision making behind the scenes


NOTES ABOUT PROJECT:
	-	I ran this code using Microsoft Visual Studio 2022 on a Windows 11 System
	-	All of the code dealing with the calculator interface is located in "Calc.cpp"
	-	All of the code dealing with the behind the scenes logic is located in "CalcLogic.cpp"
	-	Libraries, Global variables, API Menu IDs, and constants are located in "Resource.h"
	-	I've attached "Sources.txt" with links to several of the sources I used when writing this code (many parts of my API were retreived from Microsoft and I adapted it to my code to the best of my ability)
	-	Regarding the API, I was not able to find anything about a tab 'interactable' for the Calculator and Trace tabs with these libraries only, so to compensate I used 2 different windows for each screen (when a screen is switched, the previous screen is minimized and the targeted screen is maximized)
	-	I commented my code thourouly to explain my thought process to the best of my ability


NOTES ABOUT LOGIC:
	-	The code will solve equations in the following order: % * / + -
	-	As far as limitations, I've accounted for rounding, negative values, and decimal values while also verifying valid strings, accounting for domain errors (db0), and overflow
	-	If an inputed equation is not valid it will NOT compute aka nothing on the display screen will change (see FORMAT)
	-	If any other error is encountered during computation, the solving functions will return an empty TCHAR and either "Db0Err" or "OErr" will display to screen
	-	To increase flexability, I've added some constant values that can change how the code runs slightly (Ex. MAXINPUTLENGTH can be changed if you want a larger string, SIGNIFICANTDIGITS can be used to alter rounding, etc.)
	-	For the Trace, I've added an "extendedTrace" bool that can switch between a detailed trace of the code and a basic one-word description of what is happening at that point
		I recommend keeping 'extendedTrace == false' since there is a limited buffer size for the number of chars in the trace, but for smaller cases switching it to true should be fine, and this will allow you to trace my code more in depth
		If you try to solve an equation and the calculator freezes and crashes, it's more than likely a memory issue with the buffer size so try increasing TRACEBUFFER (found in "Resource.h") and reruning (I appologize for any inconvinience that this causes)
	-	The maximum value for any number you type into my calculator is 2147483647 and a minimum value of -2147483648, since this bounds are the most extreme values an int can store.


FORMAT:
	1) The only operation the string can start with is '-'
	2) Operations can not have any other operations preceeding it except for '-' (negative numbers) (Ex. 5+-1 is valid, 5-+1 is not)
	3) Operations can not have any other operations following it except for '%' (Ex. 1+100%/2 is valid, 1+100/%2 is not)
	4) Percentage Addition must be formatted as [ number + number % ]. Any other format will not work
	5) The only operation the string can end with is '%'
	6) '.' must have a number either before or after it


GENERAL TEST CASES:
5+1			-> 6
5+-1		-> 4
-5+-1		-> -6
5-1			-> 4
5--1		-> 6
-5--1		-> -4
5/1			-> 5
0/-5		-> 0
5/0			-> Db0Err
5*1			-> 5
-5*1		-> -5
5*-1		-> -5
-5*-1		-> 5
5+100%		-> 10
5+1000%		-> 55


COMPLEX TEST CASES:
1+2+3+4+5			-> 15
1+2+3+4-5			-> 5
1+2+3-4/5			-> 5.2
1+2-3/4*5			-> 2.85
1*2/3-4+5			-> -8.33334
1*2/3+-4+5			-> 1.66666
1*2/3+-4+5+100%		-> 6.66666
1+100%+100%			-> 4
1+50%+100%			-> 3
1/2/1/4				-> 0.125
2147483646+1		-> 2147483647 (any larger of a value will crash calc)

