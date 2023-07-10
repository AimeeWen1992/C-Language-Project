/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Rong-Yuan, Wen
Student ID#: 114556228
Email      : rwen1@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Wait for user to input the "enter" key to continue
void suspend(void);

// Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* ptrString);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get a valid integer from the user and return it
int inputInt(void);

// Guarantee a positive integer value is entered and returned
int inputIntPositive(void);

// Guarantee an integer value is entered within the range (inclusive) and returned
int inputIntRange(int lowerBound, int upperBound);

// Get a single character value from the user
char inputCharOption(const char stringArray[]);

/* Guarantee¡¦s a C string value is entered containing the number of characters within the range
specified by the 2nd and 3rd arguments(and return via the 1st argument pointer)*/
void inputCString(char* ptrString, int min, int max);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Valid string if is all digits then retrun 1, otherwise return 0
int checkCstringAlldigits(const char* ptrString, int length);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
