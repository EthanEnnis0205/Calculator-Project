#include "Resource.h"


// Global variable for rounding
const int SIGNIGICANTDIGITS = 5;
// noOfEqs[] is used to keep track of the total number of sub equations [*,/,%,+,-]
int noOfEqs[] = {0,0,0,0,0};

// Flags used to dictate how to formate trace
const bool includeTCHARmanipulation = true;



// Helper Functions for TCHAR manipulation //

// numOfChars() takes a TCHAR and iterates through to find the number of characters before null character
inline int numOfChars(TCHAR* l) {


	// size stores the number of characters in the list before terminating character
	int size = 0;
	

	// While the value at size is not the terminating character
	while (l[size] != '\0') {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE char exists in TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
		// increment the size
		size++;
	}

	if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN size of TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
	// increment the size again to account for indexing and return the size
	return size++;
}

// resize() takes a TCHAR and a optional size and resizes the TCHAR to either the provided limit or to the smallest TCHAR containing all the characters (optimizes memory usage)
inline TCHAR* resize(TCHAR* old, int limit) {


	// n will store the new list of characters (size will be set later)
	TCHAR* n;
	// size will store the number of characters in old if needed, and s is an indexing variable
	int size, s = 0;


	if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF a limit is provided...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
	// If a specific size is provided...
	if (limit != NULL) {
		// Set the size of n to 1 + the provided size to account for terminating character
		n = new TCHAR[limit + 1];

		// While the current value is not the terminating character and the index is less than the limit
		while (old[s] != '\0' && s < limit) {
			if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE within limit and char is valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

			if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF char is '$'...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
			// If the character at s is '$', essentially ignore it
			if (old[s] == '$') {
				while (old[s + 1] != '\0' && s + 1 < limit) {
					if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE within new limit and char is valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

					n[s] = old[s + 1];
					s++;
				}
				if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK since '$' is skipped...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
				// Set terminating character at the last index
				n[s - 1] = '\0';				
				break;
			}
			// If the character is not '$'
			else {
				if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE char is still valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

				// Set n[s] to old[s]
				n[s] = old[s];
				// increment index
				s++;
			}
			// Set terminating character at the last index
			n[s] = '\0';
		}
		// Return n and delete memory for temporary list
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN the resized TCHAR...(TCHAR: %ls)\r\n"), traceNo, n); wcscat_s(traceList, currTrace); traceNo++; } }
		return n;
		delete[] n;
	}
	// If a specific size is not provided...
	else {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE limit not provided...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		size = numOfChars(old);
		// Set the size of n to the number of characters in old +1 to account for terminating character
		n = new TCHAR[size + 1];

		// While s is smaller than the size of old
		while (s < size) {
			if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE char is in range...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

			if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF char is '$'...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
			// If the character is '$', ignore it
			if (old[s] == '$') {
				while (s + 1 < size) {
					if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE char is in new range...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

					n[s] = old[s + 1];
					s++;
				}
				if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK since '$' is skipped...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
				// Set terminating character at the last index
				n[size - 1] = '\0';
				break;
			}
			// If the character is not '$'
			else {
				if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE char is still valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

				// Set n[s] to old[s]
				n[s] = old[s];
				// increment index
				s++;
			}
			// Set terminating character at the last index
			n[size] = '\0';
		}
		// Return n and delete memory for temporary list
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN resized TCHAR...(TCHAR: %ls)\r\n"), traceNo, n); wcscat_s(traceList, currTrace); traceNo++; } }
		return n;
		delete[] n;
	}
}

// shave() takes a TCHAR, a starting index, and a ending index and returns a TCHAR containing all values inbetween (bounds included)
inline TCHAR* shave(TCHAR* old, int s, int f) {
	

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	// size stores the number of characters in old, and i is an indexing variable starting at the starting index
	int size = numOfChars(old), i = s;
	// n stores the shaved list (size is the difference between the ending and starting indexes +2 for terminating character and extra character since bounds are inclusive)
	TCHAR* n = new TCHAR[(f - s) + 2];


	// While the temporary variable is less than the ending index
	while (i <= f) {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE index is less than final index...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

		// Set n[i - s] to the value at old[temp] (i - s starts at 0 and increments)
		n[i - s] = old[i];
		// increment index
		i++;
	}
	// Set terminating character at the last index
	n[i - s] = '\0';
	if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN shaved TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
	// Return n and delete memory for temporary list
	return n;
	delete[] n;
}

// reverse() takes a TCHAR and reverses the order of the characters
inline TCHAR* reverse(TCHAR* old) {


	// size stores the number of characters in the old list, and i is an indexing variable
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	int size = numOfChars(old), i = 0;
	// n stores the reversed list (same size as old list +1 from terminating character)
	TCHAR* n = new TCHAR[size + 1];


	// While the current index is less than the number of items in the old list
	while (i < size) {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE index is less than size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

		// Set n[i] to the value at old[size - i - 1] (size - 1 accounts for the last item in old and - i decrements it, reversing the list)
		n[i] = old[size - 1 - i];
		// increment index
		i++;
	}
	// Set terminating character at last index
	n[size] = '\0';
	if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN reversed TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
	// Return n and delete memory for temporary list
	return n;
	delete[] n;
}

// combine() takes two TCHARS and concatenates them together
inline TCHAR* combine(TCHAR* f, TCHAR* s) {


	// fsize stores the number of characters in the first list (likewise with ssize for second list), i and j are indexing variables
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	int fsize = numOfChars(f), ssize = numOfChars(s), i = 0;
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	// n stores the concatonated list (size is the amount of characters in both lists +1 for terminating character)
	TCHAR* n = new TCHAR[fsize + ssize + 1];


	// While the current index is less than the amount of characters in the first list
	while (i < fsize) {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE index less than first TCHAR size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

		// Set the n[i] value to f[i]
		n[i] = f[i];
		// increment index
		i++;
	}

	// While the current index is less then the sum of the sizes of both lists
	while (i < fsize + ssize) {
		if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE index less than second TCHAR size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }

		// Set the n[i] value to the s[i - fsize] value (i - fsize starts from 0 and works up to ssize)
		n[i] = s[i - fsize];
		// increment index
		i++;
	}
	// Set terminating character at last index
	n[fsize + ssize] = '\0';

	if (includeTCHARmanipulation) { if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN combined TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } }
	// Return n and delete memory for temporary list
	return n;
	delete[] n;
}




//////////////////////////////////////////////

// Main Solving Functions //

// simplify() takes a double representing the solved value and a significant digit value and rounds the value
// This function accounts for the inaccuracy of doubles
inline int* simplify(double num, int sigfig) {


	// tnum temporarily stores the current double value
	double tnum = num;
	// nnum is an int array of size 2 where nnum[0] stores the whole-number part of tnum and nnum[1] stores the rounded decimal portion of tnum
	// Stores a decimal as 2 integers
	int* nnum = new int[2];
	// Default values for nnum[0] and nnum[1] (nnum[1] is set to one by default to account for any leading 0s in the decimal place)
	nnum[0] = 0;
	nnum[1] = 1;
	// digit temporarily stores the current digit in the current decimal place (dplace), and i is an incremental value for significant digits
	int digit, dplace = 10, i = 0;


	// While tnum has a weight larger than 1
	while (tnum >= 1.0) {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE number has a weight larger than 1...(tnum: %f)\r\n"), traceNo, tnum); wcscat_s(traceList, currTrace); traceNo++; }

		// Grab the integer at the current dplace
		digit = (int)tnum % dplace;
		// Add that number to the nnum[0]
		nnum[0] += digit;
		// subtract the digit from the temporary number since it is now stored in nnum[0]
		tnum -= digit * 1.0;
		// Move up a decimal place by nultiplying dplace by 10
		dplace *= 10;
	}

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF tnum is close to 1... (tnum: %f)\r\n"), traceNo, tnum); wcscat_s(traceList, currTrace); traceNo++; }
	// If the temporary number is close enough to 1, then round
	if (tnum >= 0.9999) {
		nnum[0] += 1;
	}
	// If the temporary number is close enough to 0, then do nothing (round down essentially)
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF tnum is close to 0... (tnum: %f)\r\n"), traceNo, tnum), wcscat_s(traceList, currTrace), traceNo++)),
		tnum <= 0.0001) {}
	// If the remaining value is in between, then start adding the value to nnum[1]
	else {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE tnum has specific value...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }

		// While in range of the specified significant digits
		while (i < sigfig) {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE digits are significant...(i: %d)\r\n"), traceNo, i); wcscat_s(traceList, currTrace); traceNo++; }

			// Multiply the temporary number by 10 to shift decimal place right
			tnum *= 10;
			// Grab the digit in front of the decimal place
			digit = (int)tnum;
			// Subtract that digit from the temporary number since it is now stored in digit
			tnum -= digit * 1.0;

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF tnum is close to 1... (tnum: %f)\r\n"), traceNo, tnum); wcscat_s(traceList, currTrace); traceNo++; }
			// If the temporary number is now close enough to 1...
			if (tnum >= 0.9999) {
				// Increment the digit, multiply nnum[1] by 10 (so value carries over) and add the new digit to nnum[1]
				digit++;
				nnum[1] *= 10;
				nnum[1] += digit;
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK since done rounding...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Break loop since there is no longer any reason to stay in
				break;
			}
			// If the temporary number is now close enough to 0...
			else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF tnum is close to 0... (tnum: %f)\r\n"), traceNo, tnum), wcscat_s(traceList, currTrace), traceNo++)),
				tnum <= 0.0001) {
				// multiply nnum[1] by 10 (so value carries over) and add the digit to nnum[1]
				nnum[1] *= 10;
				nnum[1] += digit;
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK since done rounding...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Break loop since there is no longer any reason to stay in
				break;
			}
			// If the remaining number is still in between, then run through the loop again
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE tnum still has specific value...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }

				// multiply nnum[1] by 10 (so value carries over) and add the digit to nnum[1]
				nnum[1] *= 10;
				nnum[1] += digit;
				// increment counter
				i++;
			}
		}
	}
	
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN integer list...(int: %d, dec: %d)\r\n"), traceNo, nnum[0], nnum[1]); wcscat_s(traceList, currTrace); traceNo++; }
	// Return the integer list
	return nnum;
}

// solve() takes a TCHAR, a starting index, a symbol index, and a finish ended and properly solves the sub-equation marked by the indexes
// Grabs each sub-equation, solves it, and concatenates the list back together
inline TCHAR* calculate(TCHAR* Eq, int start, int symbol, int finish) {


	// fn will store the first number in the sub-equation (size is the difference between the symbol and start indexes +1 for terminating character)
	TCHAR* fn = new TCHAR[symbol - start + 1];
	// sn will store the second number in the sub-equation (size is the difference between the finish and finishing indexes +1 for terminating character)
	TCHAR* sn = new TCHAR[finish - symbol + 1];
	// val will store the resulting value from the sub-equation (size is set to the max input length)
	TCHAR* val = new TCHAR[MAXINPUTLENGTH];
	// part will store part of the whole equation (used when recombining the new value with the old equation) (size is set to the max input length)
	TCHAR* part = new TCHAR[MAXINPUTLENGTH];
	// curr and i are indexing variables, and osize will store the size of the original equation
	// digit will store the digit of resulting number when appending it to val and dplace keeps track of decimal place
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfChars()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfChars() for size...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	int curr = start, i = 0, osize = numOfChars(Eq), digit;
	// n will store the whole number and decimal part of the resulting number after solving
	int* n = new int[2];
	// fnum, snum, and nnum will be used to store the first, second, and new numbers as doubles
	double fnum, snum, nnum = 0;
	// negative flag will be raised if value is negative
	bool negative = FALSE;
	TCHAR* err = new TCHAR[1];
	err[0] = '\0';


	// While temp is not equal to the symbol index
	while (curr != symbol) {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE temp is not equal to sym...(curr: %i, sym: %i)\r\n"), traceNo, curr, symbol); wcscat_s(traceList, currTrace); traceNo++; }

		// Set fn[i] to Eq[curr]
		fn[i] = Eq[curr];
		// increment both indexing variables
		curr++;
		i++;
	}
	// Set terminating character at last index of fn
	fn[symbol - start] = '\0';
	// Convert the tchar to double using built-in function
	fnum = _tcstod(fn, nullptr);
	// Delete memory of fn
	delete[] fn;

	// Reset i to 0
	i = 0;
	// increment curr (since it it currently equal to symbol)
	curr++;

	// While temp is not equal to the finish index + 1
	while (curr != finish + 1) {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE curr is not equal to finish + 1...(curr: %i, sym: %i)\r\n"), traceNo, curr, finish + 1); wcscat_s(traceList, currTrace); traceNo++; }

		// Set sn[i] = Eq[curr]
		sn[i] = Eq[curr];
		// increment both indexing variables
		curr++;
		i++;
	}
	// Set terminating character at last index of sn
	sn[finish - symbol] = '\0';
	// Convert the tchar to double
	snum = _tcstod(sn, nullptr);
	// Delete memory of sn
	delete[] sn;
	
	if (extendedTrace) { swprintf_s(currTrace, _T("Fnum: %f, Snum: %f\r\n"), fnum, snum); wcscat_s(traceList, currTrace); }

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF symbol is '*'... (Symbol: %c)\r\n"), traceNo, Eq[symbol]); wcscat_s(traceList, currTrace); traceNo++; }
	// Computation of value
	// If the symbol is multipication:
	if (Eq[symbol] == '*') {
		nnum = fnum * snum;
	}
	// If the symbol is division:
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. IF symbol is '/'... (Symbol: %c)\r\n"), traceNo, Eq[symbol]), wcscat_s(traceList, currTrace), traceNo++)),
		Eq[symbol] == '/') {

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF second number is NOT 0.0... (snum: %f)\r\n"), traceNo, snum); wcscat_s(traceList, currTrace); traceNo++; }
		// Error checking to prevent division by 0 (0 is default error value)
		if (snum != 0.0) {
			nnum = fnum / snum;
		}
		// If the second number is 0, then throw Db0Err
		else {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE dividing by 0 is not allowed...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Set the output to "Db0Err" and set the inputLength to 6 (since Db0Err is 6 chars long)
			input[0] = '\0';
			wcscat_s(input, _T("Db0Err"));
			inputLength = 6;
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN Db0Err... (snum: %f)\r\n"), traceNo, snum); wcscat_s(traceList, currTrace); traceNo++; }
			// Return err since dividing by 0 is not allowed
			return err;
			delete[] val;
			delete[] part;
		}
	}
	// If the symbol is percentage:
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. IF symbol is '%%'... (Symbol: %c)\r\n"), traceNo, Eq[symbol]), wcscat_s(traceList, currTrace), traceNo++)),
		Eq[symbol] == '%') {
		nnum = (fnum * (snum / 100)) + fnum;
	}
	// If the symbol is addition:
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. IF symbol is '+'... (Symbol: %c)\r\n"), traceNo, Eq[symbol]), wcscat_s(traceList, currTrace), traceNo++)),
		Eq[symbol] == '+') {
		nnum = fnum + snum;
	}
	// If the symbol is subtraction:
	else {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE symbol is '-'... (Symbol: %c)\r\n"), traceNo, Eq[symbol]); wcscat_s(traceList, currTrace); traceNo++; }
		nnum = fnum - snum;
	}

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF resulting value is 0.0... (nnum: %f)\r\n"), traceNo, nnum); wcscat_s(traceList, currTrace); traceNo++; }
	// If the resulting value is 0...
	if (nnum == 0.0) {
		// Set the values for val
		val[0] = '0';
		val[1] = '\0';
	}
	// If the resulting value is NOT 0...
	else {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE resulting value is NOT 0.0...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF resulting value is < 0.0... (nnum: %f)\r\n"), traceNo, nnum); wcscat_s(traceList, currTrace); traceNo++; }
		// If the resulting value is below 0...
		if (nnum < 0.0) {
			// Set the negative flag to true
			negative = TRUE;
			// Flip the sign of the new number to make it positive
			nnum -= (2 * nnum);
		}
		// Retreive the list returned by simplify()
		n = simplify(nnum, SIGNIGICANTDIGITS);
		if (extendedTrace) { swprintf_s(currTrace, _T("int: %d, dec: %d\r\n"), n[0], n[1]); wcscat_s(traceList, currTrace); }

		// Set the indexing variable to 0
		i = 0;

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF decimal portion of answer is 1 (meaning integer)... (dec: %d)\r\n"), traceNo, n[1]); wcscat_s(traceList, currTrace); traceNo++; }
		// Building the val list (builds it backwards)
		// if the decimal portion of the number has value (1 is default value) 
		if (n[1] != 1) {
			// Loops until the default value is left (1)
			while (TRUE) {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE decimal still has value...(dec: %i)\r\n"), traceNo, n[1]); wcscat_s(traceList, currTrace); traceNo++; }

				// Grab the digit in the first
				digit = (int)n[1] % 10;
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF digit - remaining portion of decimal eq 0 (no more value)... (digit: %d, dec: %d)\r\n"), traceNo, digit, n[1]); wcscat_s(traceList, currTrace); traceNo++; }
				// If the difference between the digit and the remaining number in n[1] is 0, then it has to be the default value, so break the loop
				if (digit - n[1] == 0) {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK the loop...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					break;
				}

				// Shift the value right
				n[1] = (int)n[1] / 10;

				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current amount of chars in val doesn't exceed MAXINPUTLENGTH...(curr: %i, MAX: %i)\r\n"), traceNo, inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); traceNo++; }
				// If the current number of characters exceeds the MAX
				if (inputLength < MAXINPUTLENGTH) {
					// Set val[i] to that value (+48 is ascii) and increment length
					val[i] = (int)digit + 48;
					if (extendedTrace) { swprintf_s(currTrace, _T("val[%d]: %c\r\n"), i, val[i]); wcscat_s(traceList, currTrace); }
					inputLength++;
					if (extendedTrace) { swprintf_s(currTrace, _T("digit: %c\r\n"), digit + 48); wcscat_s(traceList, currTrace); }
					if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }
					if (extendedTrace) { swprintf_s(currTrace, _T("inputLength: %d, MAX: %d\r\n"), inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); }
				}
				// If MAXINPUTLENGTH is exceeded
				else {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE MAXINPUTLENGTH is exceeded\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Set the output to "0Err" and set the inputLength to 4 (since Db0Err is 4 chars long)
					input[0] = '\0';
					wcscat_s(input, _T("OErr"));
					inputLength = 4;
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN OErr\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Return err since Overflow is not allowed
					return err;
					delete[] val;
					delete[] part;
					delete[] err;
				}
				// increment the index
				i++;
			}

			// Append a decimal point to the front of the list and increment the index
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current amount of chars in val doesn't exceed MAXINPUTLENGTH...(curr: %i, MAX: %i)\r\n"), traceNo, inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); traceNo++; }
			// If the current number of characters exceeds the MAX
			if (inputLength < MAXINPUTLENGTH) {
				// Set val[i] to '.' (+48 is ascii) and increment length
				val[i] = '.';
				inputLength++;
				if (extendedTrace) { swprintf_s(currTrace, _T("digit: %c\r\n"), digit + 48); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("inputLength: %d, MAX: %d\r\n"), inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); }
			}
			// If MAXINPUTLENGTH is exceeded
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE MAXINPUTLENGTH is exceeded\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Set the output to "0Err" and set the inputLength to 4 (since Db0Err is 4 chars long)
				input[0] = '\0';
				wcscat_s(input, _T("OErr"));
				inputLength = 4;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN OErr\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Return err since Overflow is not allowed
				return err;
				delete[] val;
				delete[] part;
				delete[] err;
			}
			i++;
		}

		// While there is value in n[0]
		while (n[0] != 0) {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE integer part of number has value...(int: %i)\r\n"), traceNo, n[1]); wcscat_s(traceList, currTrace); traceNo++; }

			// Grab the digit in the first
			digit = (int)n[0] % 10;
			// Shift the value right
			n[0] = (int)n[0] / 10;

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current amount of chars in val doesn't exceed MAXINPUTLENGTH...(curr: %i, MAX: %i)\r\n"), traceNo, inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); traceNo++; }
			// If the current number of characters exceeds the MAX
			if (inputLength < MAXINPUTLENGTH) {
				// Set val[i] to that value (+48 is ascii) and increment length
				val[i] = (int)digit + 48;
				//if (extendedTrace) { swprintf_s(currTrace, _T("val[%d]: %c\r\n"), i, val[i]); wcscat_s(traceList, currTrace); }
				inputLength++;
				if (extendedTrace) { swprintf_s(currTrace, _T("digit: %c\r\n"), digit + 48); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("inputLength: %d, MAX: %d\r\n"), inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); }
			}
			// If MAXINPUTLENGTH is exceeded
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE MAXINPUTLENGTH is exceeded\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Set the output to "0Err" and set the inputLength to 4 (since Db0Err is 4 chars long)
				input[0] = '\0';
				wcscat_s(input, _T("OErr"));
				inputLength = 4;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN OErr\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Return err since Overflow is not allowed
				return err;
				delete[] val;
				delete[] part;
				delete[] err;
			}
			// increment the index
			i++;
		}

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF new number was negative...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// If the number is supposed to be negative
		if (negative) {
			// Set val[i] to a negative symbol and increment the index
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current amount of chars in val doesn't exceed MAXINPUTLENGTH...(curr: %i, MAX: %i)\r\n"), traceNo, inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); traceNo++; }
			// If the current number of characters exceeds the MAX
			if (inputLength < MAXINPUTLENGTH) {
				// Set val[i] to '-' (+48 is ascii) and increment length
				val[i] = '-';
				inputLength++;
				if (extendedTrace) { swprintf_s(currTrace, _T("digit: %c\r\n"), digit + 48); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }
				if (extendedTrace) { swprintf_s(currTrace, _T("inputLength: %d, MAX: %d\r\n"), inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); }
			}
			// If MAXINPUTLENGTH is exceeded
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE MAXINPUTLENGTH is exceeded\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Set the output to "0Err" and set the inputLength to 4 (since Db0Err is 4 chars long)
				input[0] = '\0';
				wcscat_s(input, _T("OErr"));
				inputLength = 4;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN OErr\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Return err since Overflow is not allowed
				return err;
				delete[] val;
				delete[] part;
				delete[] err;
			}
			i++;
		}
		// Set the last value in val as the terminating character
		val[i] = '\0';
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. reverse()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL reverse() reverse the TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Reverse the string using reverse()
		val = reverse(val);
	}

	// Check and see if the total size will overflow buffer
	inputLength = inputLength + start + (osize - 1 - finish);
	//if (extendedTrace) { swprintf_s(currTrace, _T("inputLength: %d, MAX: %d\r\n"), inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); }

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current amount of chars in val doesn't exceed MAXINPUTLENGTH...(curr: %i, MAX: %i)\r\n"), traceNo, inputLength, MAXINPUTLENGTH); wcscat_s(traceList, currTrace); traceNo++; }
	// If the total length of the new string exceeds the MAX
	if (inputLength >= MAXINPUTLENGTH) {
		input[0] = '\0';
		wcscat_s(input, _T("OErr"));
		inputLength = 4;
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN OErr\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Return err since Overflow is not allowed
		return err;
		delete[] val;
		delete[] part;
		delete[] err;
	}

	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF subeq was nested...(s: %d, f: %d, o: %d)\r\n"), traceNo, start, finish, osize - 1); wcscat_s(traceList, currTrace); traceNo++; }
	// Recombining the equations
	// If the sub-equation was in the middle of the original equation
	if (start != 0 && finish != osize - 1) {

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. shave()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL shave() to remove part of TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// part uses shave() to grab the last part of the original equation
		part = shave(Eq, finish + 1, osize - 1);
		if (extendedTrace) { swprintf_s(currTrace, _T("part: %ls\r\n"), part); wcscat_s(traceList, currTrace); }

		// Set Eq[start] to the terminating character (essentially storing the first part of the original equation)
		Eq[start] = '\0';

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. combine()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL combine() to combine two TCHARS...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// combine all of the parts together and store in val
		val = combine(Eq, val);
		if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. combine()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL combine() to combine two TCHARS...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// combine all of the parts together and store in val
		val = combine(val, part);
		if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }

	}
	// If the sub-equation was at the start of the original equation
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF subeq was at the start...(s: %d, f: %d, o: %d)\r\n"), traceNo, start, finish, osize - 1), wcscat_s(traceList, currTrace), traceNo++)),
		start == 0 && finish != osize - 1) {
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. shave()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL shave() to remove part of TCHAR...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// part uses shave() to grab the last part of the original equation
		part = shave(Eq, finish + 1, osize - 1);
		if (extendedTrace) { swprintf_s(currTrace, _T("part: %ls\r\n"), part); wcscat_s(traceList, currTrace); }

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. combine()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL combine() to combine two TCHARS...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Combine val and part and store the resulting equation in val
		val = combine(val, part);
		if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }

	}
	// If the sub-equation was at the end of the original equation
	else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF subeq was at the end...(s: %d, f: %d, o: %d)\r\n"), traceNo, start, finish, osize - 1), wcscat_s(traceList, currTrace), traceNo++)),
		start != 0 && finish == osize - 1) {
		
		// Set Eq[start] to the terminating character (essentially storing the first part of the original equation)
		Eq[start] = '\0';
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. combine()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL combine() to combine two TCHARS...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Combine Eq and val and store the resulting equation in val
		val = combine(Eq, val);
		if (extendedTrace) { swprintf_s(currTrace, _T("val: %ls\r\n"), val); wcscat_s(traceList, currTrace); }

	}
	// If the sub-equation was the original equation, do nothing
	else {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE subeq was eq, so don't reformat...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	}

	// Return the new equation
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN new Eq...(val: %ls)\r\n"), traceNo, val); wcscat_s(traceList, currTrace); traceNo++; }
	// Return the new equation
	return val;
	delete[] val;
	delete[] part;
	delete[] err;
}

// findSubEq() takes a TCHAR as a full string of equations and a sym that represents the targeted symbol and a num representing the total number of syms in string
inline TCHAR* findSubEq(TCHAR* Eq, char sym, int num) {


	// start, fin, and m are all indexing variables
	int start = 0, fin = 0, m = 0;


	// While characters and an equation still exist
	while (Eq[m] != '\0' && num > 0) {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE char is valid and the target exists...(Eq[m]: %c, num: %d)\r\n"), traceNo, Eq[m], num); wcscat_s(traceList, currTrace); traceNo++; }

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr char DOESNT match target... (Value: %c; target: %c)\r\n"), traceNo, Eq[m], sym); wcscat_s(traceList, currTrace); traceNo++; }
		// If a current character does not equal the target
		if (Eq[m] != sym) {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char is non-target sym... (Value: %c; target: %c)\r\n"), traceNo, Eq[m], sym); wcscat_s(traceList, currTrace); traceNo++; }
			// If the current character is a symbol thats not '.'
			if ((Eq[m] < '0' || Eq[m] > '9') && Eq[m] != '.') {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr is '-' and m = 0 or m > 0 and previous char was sym... (Eq[m]: %c; m: %c, Eq[m - 1]: %d)\r\n"), traceNo, Eq[m], m, Eq[m-1]); wcscat_s(traceList, currTrace); traceNo++; }
				// If the current character is '-', then set the start to that value (for negative numbers)
				if (Eq[m] == '-' && (m == 0 || (m > 0 && (Eq[m - 1] < '0' || Eq[m - 1] > '9')))) {
					// Set the start to m
					start = m;
				}
				else {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE curr is non '-' sym so set start to m + 1...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Set the start to m + 1
					start = m + 1;
				}
			}
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE on to next character...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Increment and continue
			m++;
			continue;
		}
		// If the current character is equal to the target
		else {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE curr char matches target...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF target symbol is '-' and the curr char is first char... (Value: %c; Index: %o)\r\n"), traceNo, Eq[m], m); wcscat_s(traceList, currTrace); traceNo++; }
			// If the target is '-' and its the first character in the string
			if (sym == '-' && m == 0) {

				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE on to next character...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Ignore it since negative numbers don't count for '-'
				m++;
				continue;
			}
			// Set last index to m
			fin = m;
			while (Eq[fin + 1] != '*' && Eq[fin + 1] != '/' && Eq[fin + 1] != '+' && Eq[fin + 1] != '%') {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE next sym has not been reached... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				
				// Increment last index
				fin++;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr char is last char... (Value: %c; Index: %o)\r\n"), traceNo, Eq[fin], fin + 1); wcscat_s(traceList, currTrace); traceNo++; }
				// If the next character in the string is terminating
				if (Eq[fin + 1] == '\0') {

					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK the loop... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Break since there is no more string
					break;
				}

				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF target symbol is '-' and the curr char is first char... (Value: %c; Index: %o)\r\n"), traceNo, Eq[m], m); wcscat_s(traceList, currTrace); traceNo++; }
				// If the current character is '-' and it isn't a negative number
				if (Eq[fin] == '-' && fin - 1 != m) {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK the loop...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Decrement and break since the end of the second number has been found
					fin--;
					break;
				}
			}
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. calculate()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL calculate() to calculate subeq...(start: %d, sym: %d, fin: %d)\r\n"), traceNo, start, m, fin); wcscat_s(traceList, currTrace); traceNo++; }
			// Set the inputLength to 0 and Calculate the subequation and decrement the total number of targets in the string
			inputLength = 0;
			Eq = calculate(Eq, start, m, fin);

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF empty TCHAR was returned... (Value: %ls)\r\n"), traceNo, Eq); wcscat_s(traceList, currTrace); traceNo++; }
			// If an empty TCHAR was returned
			if (Eq[0] == '\0') {
				// Set all symbol numbers to 0 and return the empty TCHAR
				noOfEqs[0] = 0;
				noOfEqs[1] = 0;
				noOfEqs[2] = 0;
				noOfEqs[3] = 0;
				noOfEqs[4] = 0;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN new Eq...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				return Eq;
				delete[] Eq;
			}

			// Decrement the total number of symbols
			num--;

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF start is not beginning of the string... (Index: %d)\r\n"), traceNo, start); wcscat_s(traceList, currTrace); traceNo++; }
			// If the start was not 0, then set the new start to a character before the previous start
			if (start != 0) {
				m = start - 1;
			}
			// If the previous start was at the beginning, keep it there
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE set the new start to beginning of string... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				m = 0;
			}
		}
	}

	// Resize the Equation
	//Eq = resize(Eq, NULL);
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN new Eq...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	// Returned the new equation with no more targets
	return Eq;
	delete[] Eq;
}

// findSubEqp() is a specific case of findSubEq() when sym is %
inline TCHAR* findSubEqp(TCHAR* Eq, int num) {
	

	// start, fin, and m are all indexing variables
	int start = 0, p = 0, a = 0, ta = -1;


	// While characters and an equation still exist
	while (Eq[p] != '\0' && num > 0) {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE char is valid and the target exists...(Eq[p]: %c, num: %i)\r\n"), traceNo, Eq[p], num); wcscat_s(traceList, currTrace); traceNo++; }

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr char DOESNT match target... (Value: %c; target: %%)\r\n"), traceNo, Eq[p]); wcscat_s(traceList, currTrace); traceNo++; }
		// If a current character does not equal %
		if (Eq[p] != '%') {

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char is number... (Value: %c)\r\n"), traceNo, Eq[p]); wcscat_s(traceList, currTrace); traceNo++; }
			// If the character is not a symbol
			if ((Eq[p] >= '0' && Eq[p] <= '9') || Eq[p] == '.') {
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE to next char...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Increment the current index and continue
				p++;
				continue;
			}

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char is non-target sym other than '-' or '+'... (Value: %c)\r\n"), traceNo, Eq[p]); wcscat_s(traceList, currTrace); traceNo++; }
			// If the character is a symbol that is not '+' (different case for '+')
			if ((Eq[p] < '0' || Eq[p] > '9') && Eq[p] != '+') {
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE to next char...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Set the start of the equation to the next character and increment and continue
				start = p + 1;
				p++;
				continue;
			}

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char is '+'... (Value: %c; target: +)\r\n"), traceNo, Eq[p]); wcscat_s(traceList, currTrace); traceNo++; }
			// If the character is '+'
			if (Eq[p] == '+') {
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF a is 0...(a: %d)\r\n"), traceNo, a); wcscat_s(traceList, currTrace); traceNo++; }
				// If there is no add symbol yet, set that to the current addition sym
				if (a == 0) {
					// Set the current add to p
					a = p;
				}
				else {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE another a exists, so set ta to a and a to p...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					// Set the temp add to add and the current add to p
					ta = a;
					a = p;
				}

				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE to next char...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				// Set a to the location of '+' and increment and continue
				p++;
				continue;
			}
		}
		// If the symbol is the target
		else {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE curr char matches target...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Set the add symbol to a percent and the percent symbol to a '$' (used as empty char)
			Eq[a] = '%';
			Eq[p] = '$';
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF start is less than ta... (start: %d, ta: %d)\r\n"), traceNo, start, ta); wcscat_s(traceList, currTrace); traceNo++; }
			// If the current start index is less than the temp add index (meaning the temp add is the most recent sym)
			if (start < ta) {
				// Set the new start to the temp add + 1
				start = ta + 1;
			}

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. calculate()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL calculate() to calculate subeq...(start: %d, sym: %d, fin: %d)\r\n"), traceNo, start, a, p-1); wcscat_s(traceList, currTrace); traceNo++; }
			// Set inputLength to 0 and Calculate the equaiton using the indexes
			inputLength = 0;
			Eq = calculate(Eq, start, a, p - 1);

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF empty TCHAR was returned... (Value: %ls)\r\n"), traceNo, Eq); wcscat_s(traceList, currTrace); traceNo++; }
			// If the returned equation is empty, then there was an error, so return
			if (Eq[0] == '\0') {
				// Set all symbol numbers to 0 and return the empty TCHAR
				noOfEqs[0] = 0;
				noOfEqs[1] = 0;
				noOfEqs[2] = 0;
				noOfEqs[3] = 0;
				noOfEqs[4] = 0;
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN new Eq...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				return Eq;
				delete[] Eq;
			}

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. resize()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL resize() to remove $...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Resize the equation to remove '$'
			Eq = resize(Eq, NULL);

			// Decrement the total number of '%'
			num--;

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF start is not beginning of the string... (Index: %d)\r\n"), traceNo, start); wcscat_s(traceList, currTrace); traceNo++; }
			// If the start was not at the beginning of the string, then set the new start to right before the previous start
			if (start > 0) {
				p = start - 1;
			}
			// else set the new start to the beginning of the string
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE set the new start to beginning of string... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				p = 0;
			}
			// Reset all of the values
			start = 0;
			a = 0;
			ta = -1;
		}
	}
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. resize()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL resize() to remove $...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	// Resize again to remove any '$' char and return the new Eq
	Eq = resize(Eq, NULL);
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN new Eq...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	return Eq;
	delete[] Eq;
}

// numOfSubEqs() finds the total number of equations in the input string
inline bool numOfSubEqs(TCHAR* Eq) {
	
	// Curr is indexing variable
	int curr = 1;
	// padd is flag that remembers if the previous symbol was addition (used to verify %)
	bool padd = false;

	
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF first char in string is NOT valid... (Value: %c)\r\n"), traceNo, Eq[0]); wcscat_s(traceList, currTrace); traceNo++; }
	// If the equation starts with a symbol that is not -, then DON'T compute
	if ((Eq[0] < '0' || Eq[0] > '9') && Eq[0] != '-') {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN Symbol '%c' return false (END)\r\n"), traceNo, Eq[0]); wcscat_s(traceList, currTrace); traceNo++; }
		return false;
	}
	// For any other symbol in the string...
	else {
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, __T("%d. ELSE first char is valid... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// While the curr char is not the terminating char
		while (Eq[curr] != '\0') {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. WHILE valid characters string... \r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }

			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current char in string is symbol... (Value: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
			// If the curr char is a symbol and the next char exists
			if ((Eq[curr] < '0' || Eq[curr] > '9') && Eq[curr + 1] != '\0') {
				
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the next char in string is also symbol... (Sym: %c)\r\n"), traceNo, Eq[curr + 1]); wcscat_s(traceList, currTrace); traceNo++; }
				// If the next char is also a symbol
				if (Eq[curr + 1] < '0' || Eq[curr + 1] > '9') {
					
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char in string is '%%' and next symbol not '%%'... (Sym: %c, nextSym: %c)\r\n"), traceNo, Eq[curr], Eq[curr + 1]); wcscat_s(traceList, currTrace); traceNo++; }
					// If the curr sym is a %, the next sym is NOT %, and the last sym was add
					if (Eq[curr] == '%' && Eq[curr + 1] != '%' && padd) {
						// Increment noOfEqs[2] % and continue
						noOfEqs[2]++;
						curr++;
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
						continue;
					}
					// If the next sym is -, do nothing
					else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF Previous sym not add (END)...\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)),
						Eq[curr + 1] == '-') {
						
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the curr char is '.'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
						// If the current input is a '.'
						if (Eq[curr] == '.') {
							if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
							// Increment and continue
							curr++;
							continue;
						}
						
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr sym in string is '*'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
						// If the curr char is *, increment noOfEqs[0] and set the padd flag to false
						if (Eq[curr] == '*') {
							noOfEqs[0]++;
							padd = false;
						}
						// If the curr char is /, increment noOfEqs[1] and set the padd flag to false
						else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF curr sym in string is '/'... (Sym: %c)\r\n"), traceNo, Eq[curr]), wcscat_s(traceList, currTrace), traceNo++)),
							Eq[curr] == '/') {
							noOfEqs[1]++;
							padd = false;
						}
						// If the curr char is +, increment noOfEqs[3] and set the padd flag to true
						else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF curr sym in string is '+'... (Sym: %c)\r\n"), traceNo, Eq[curr]), wcscat_s(traceList, currTrace), traceNo++)),
							Eq[curr] == '+') {
							noOfEqs[3]++;
							padd = true;
						}
						// If the curr char is -, increment noOfEqs[4] and set the padd flag to false
						else {
							if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE curr sym in string is '-'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
							noOfEqs[4]++;
							padd = false;
						}
						// Increment by 2 to skip '-' and continue
						curr += 2;
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
						continue;
					}
					// If the curr sym is % and the previous sym was not add, return false since thats not allowed
					else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF Previous sym not add (END)...\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)),
						Eq[curr] == '%' && !padd) {
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN since previous has to be add...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
						return false;
					}
					// Any other case, return false since two symbols back to back are not allowed
					else {
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE the second sym is %%...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
						if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN since there shouldn't be %%%%...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
						return false;
					}
				}
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr sym in string is '.'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
				// If the curr char is ., increment noOfEqs[0] and set the padd flag to false
				if (Eq[curr] == '.') {
					curr++;
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CONTINUE...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					continue;
				}
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF curr sym in string is '*'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
				// If the curr char is *, increment noOfEqs[0] and set the padd flag to false
				if (Eq[curr] == '*') {
					noOfEqs[0]++;
					padd = false;
				}
				// If the curr char is /, increment noOfEqs[1] and set the padd flag to false
				else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF curr sym in string is '/'... (Sym: %c)\r\n"), traceNo, Eq[curr]), wcscat_s(traceList, currTrace), traceNo++)),
					Eq[curr] == '/') {
					noOfEqs[1]++;
					padd = false;
				}
				// If the curr char is +, increment noOfEqs[3] and set the padd flag to true
				else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF curr sym in string is '+'... (Sym: %c)\r\n"), traceNo, Eq[curr]), wcscat_s(traceList, currTrace), traceNo++)),
					Eq[curr] == '+') {
					noOfEqs[3]++;
					padd = true;
				}
				// If the curr char is -, increment noOfEqs[4] and set the padd flag to false
				else {
					if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE curr sym in string is '-'... (Sym: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
					noOfEqs[4]++;
					padd = false;
				}
				curr++;
			}
			// If the next char is the terminating char, the curr char is a sym and not '.'
			else if ((!extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF\r\n"), traceNo), wcscat_s(traceList, currTrace), traceNo++)) || (extendedTrace && TRACEON && (swprintf_s(currTrace, _T("%d. ELSEIF the last char in string is symbol... (Value: %c)\r\n"), traceNo, Eq[curr]), wcscat_s(traceList, currTrace), traceNo++)),
				 Eq[curr + 1] == '\0' && (Eq[curr] < '0' || Eq[curr] > '9') && Eq[curr] != '.') {
				 if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF the current char in string is symbol... (Value: %c)\r\n"), traceNo, Eq[curr]); wcscat_s(traceList, currTrace); traceNo++; }
				 // If the curr sym is not %, return false since it shouldn't end with any other symbol
				 if (Eq[curr] != '%') {
					 if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN Last char NOT valid return false (END)...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					 return false;
				 }
				 if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF prev sym not addition...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				 // If the curr sym is % and the previous operation was not add, return false
				 if (!padd) {
					 if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN Invalid format for percent (END)...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
					 return false;
				 }
				 if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. BREAK the loop...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				 // increment the number of % and break
				 noOfEqs[2]++;
				 break;
			}
			// If the curr char is a number or '.'
			else {
				if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE the current char in string is num...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
				curr++;
			}
		}
		// Subtract the number of % from the number of +, since % use a + in the operation
		noOfEqs[3] -= noOfEqs[2];

		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF no sym in string...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// If there is no symbol, do nothing
		if (noOfEqs[0] == 0 && noOfEqs[1] == 0 && noOfEqs[2] == 0 && noOfEqs[3] == 0 && noOfEqs[4] == 0) {
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN false...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			return false;
		}
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN Everything valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Return that the string is valid
		if (extendedTrace) { swprintf_s(currTrace, _T("%%: %d, *: %d, /: %d, +: %d, -: %d\r\n"), noOfEqs[2], noOfEqs[0], noOfEqs[1], noOfEqs[3], noOfEqs[4]); wcscat_s(traceList, currTrace); }
		return true;
	}
}

// solve() tests the number of equations and calls the correct functions to solve in correct order
inline TCHAR* solve(TCHAR* Eq) {
	
	
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF string is valid...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. numOfSubEqs()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL numOfSubEqs() to verify string...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
	// If the string is valid
	if (numOfSubEqs(Eq)) {
		
		TCHAR* newEq = Eq;
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF '%%' in Eq... (Amount: %d)\r\n"), traceNo, noOfEqs[2]); wcscat_s(traceList, currTrace); traceNo++; }
		// If there exist any % in string
		if (noOfEqs[2] > 0) {
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. findSubEqp()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL findSubEqp() to solve %%...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Solve each instance and set the num to 0
			newEq = findSubEqp(newEq, noOfEqs[2]);
			if (extendedTrace) { swprintf_s(currTrace, _T("newEq: %ls\r\n"), newEq); wcscat_s(traceList, currTrace); }
			noOfEqs[2] = 0;
		}
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF '*' in Eq... (Amount: %d)\r\n"), traceNo, noOfEqs[0]); wcscat_s(traceList, currTrace); traceNo++; }
		// If there exist any * in string
		if (noOfEqs[0] > 0) {
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. findSubEq()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL findSubEq() to solve *...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Solve each instance and set the num to 0
			newEq = findSubEq(newEq, '*', noOfEqs[0]);
			if (extendedTrace) { swprintf_s(currTrace, _T("newEq: %ls\r\n"), newEq); wcscat_s(traceList, currTrace); }
			noOfEqs[0] = 0;
		}
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF '/' in Eq... (Amount: %d)\r\n"), traceNo, noOfEqs[1]); wcscat_s(traceList, currTrace); traceNo++; }
		// If there exist any / in string
		if (noOfEqs[1] > 0) {
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. findSubEq()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL findSubEq() to solve /...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Solve each instance and set the num to 0
			newEq = findSubEq(newEq, '/', noOfEqs[1]);
			if (extendedTrace) { swprintf_s(currTrace, _T("newEq: %ls\r\n"), newEq); wcscat_s(traceList, currTrace); }
			noOfEqs[1] = 0;
		}
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF '+' in Eq... (Amount: %d)\r\n"), traceNo, noOfEqs[3]); wcscat_s(traceList, currTrace); traceNo++; }
		// If there exist any + in string
		if (noOfEqs[3] > 0) {
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. findSubEq()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL findSubEq() to solve +...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Solve each instance and set the num to 0
			newEq = findSubEq(newEq, '+', noOfEqs[3]);
			if (extendedTrace) { swprintf_s(currTrace, _T("newEq: %ls\r\n"), newEq); wcscat_s(traceList, currTrace); }
			noOfEqs[3] = 0;
		}
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. IF '-' in Eq... (Amount: %d)\r\n"), traceNo, noOfEqs[4]); wcscat_s(traceList, currTrace); traceNo++; }
		// If there exist any - in string
		if (noOfEqs[4] > 0) {
			
			if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. findSubEq()\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. CALL findSubEq() to solve -...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
			// Solve each instance and set the num to 0
			newEq = findSubEq(newEq, '-', noOfEqs[4]);
			if (extendedTrace) { swprintf_s(currTrace, _T("newEq: %ls\r\n"), newEq); wcscat_s(traceList, currTrace); }
			noOfEqs[4] = 0;
		}
		// Return the answer to the string
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN final answer... (Ans: %ls)\r\n"), traceNo, newEq); wcscat_s(traceList, currTrace); traceNo++; }
		return newEq;
		delete[] newEq;

	}
	// If the string if NOT valid, return an empty TCHAR
	else {
		
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. ELSE String not valid (DO NOTHING)...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		TCHAR* newEq = new TCHAR[1];
		newEq[0] = '\0';
		if (!extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; } if (extendedTrace && TRACEON) { swprintf_s(currTrace, _T("%d. RETURN nothing...\r\n"), traceNo); wcscat_s(traceList, currTrace); traceNo++; }
		// Return the empty TCHAR
		return newEq;
		delete[] newEq;

	}
}