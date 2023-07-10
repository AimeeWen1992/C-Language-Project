/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Rong-Yuan, Wen
Student ID#: 114556228
Email      : rwen1@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"

#define PHONE_LENGTH 10
//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n')
	{
		; // do nothing!
	}
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

// Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* ptrString)
{
	int i, valid;

	valid = 0;
	if (ptrString && strlen(ptrString) == PHONE_LENGTH)
	{
		valid = 1;
		for (i = 0; i < PHONE_LENGTH && valid; i++)
		{
			if (!isdigit(ptrString[i]))
			{
				valid = 0;
			}
		}
	}

	if (valid)
	{
		printf("(%.3s)%.3s-%.4s", ptrString, ptrString + 3, ptrString + 6);
	}
	else
	{
		printf("(___)___-____");
	}
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get a valid integer from the user and return it
int inputInt(void)
{
	int userInput = 0;
	char aNewLine = '\0';
	int valid;

	do
	{
		valid = 1;

		scanf("%d%c", &userInput, &aNewLine);

		if (aNewLine != '\n')
		{
			valid = 0;
			printf("Error! Input a whole number: ");
			clearInputBuffer();
		}

	} while (!valid);

	return userInput;
}

// Guarantee a positive integer value is entered and returned
int inputIntPositive(void)
{
	int userInput = 0;
	int valid;

	do
	{
		valid = 1;
		userInput = inputInt();

		if (userInput < 1)
		{
			valid = 0;
			printf("ERROR! Value must be > 0: ");
		}

	} while (!valid);

	return userInput;
}

// Guarantee an integer value is entered within the range (inclusive) and returned
int inputIntRange(int lowerBound, int upperBound)
{
	int userInput = 0;
	int valid;

	do
	{
		valid = 1;
		userInput = inputInt();

		if (userInput > upperBound || userInput < lowerBound)
		{
			valid = 0;
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
		}

	} while (!valid);

	return userInput;
}

// Get a single character value from the user
char inputCharOption(const char stringArray[])
{
	int valid;
	char userInput = '\0';
	char aNewLine = '\0';

	do {
		valid = 1;

		scanf("%c%c", &userInput, &aNewLine);

		if (aNewLine == '\n')
		{
			if (strchr(stringArray, userInput) == NULL)
			{
				valid = 0;
				printf("ERROR: Character must be one of [%s]: ", stringArray);
			}
		}
		else
		{
			valid = 0;
			printf("ERROR: Must be only one Character: ");
			clearInputBuffer();
		}

	} while (!valid);

	return userInput;
}

/* Guarantee¡¦s a C string value is entered containing the number of characters within the range
specified by the 2nd and 3rd arguments(and return via the 1st argument pointer)*/
void inputCString(char* ptrString, int min, int max)
{

	int valid;
	char array[1000 + 1] = { '\0' };

	do
	{
		valid = 1;

		scanf("%1000[^\n]", array);

		clearInputBuffer();

		if (max == min)
		{
			if (strlen(array) != max)
			{
				valid = 0;
				printf("ERROR: String length must be exactly %d chars: ", max);
			}
		}
		else
		{

			if (strlen(array) < min)
			{
				valid = 0;
				printf("ERROR: String length must be between %d and %d chars: ", min, max);
			}
			else if (strlen(array) > max)
			{
				valid = 0;
				printf("ERROR: String length must be no more than %d chars: ", max);
			}
		}

	} while (!valid);

	strcpy(ptrString, array);
}


