/*/////////////////////////////////////////////////////////////////////////
						Assignment 1 - Milestone 1
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

#include "core.h"

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

		if (aNewLine!='\n')
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
	int i, valid, count;
	char userInput = '\0';
	char aNewLine = '\0';

	do {
		valid = 1;
		count = 0;

		scanf("%c%c", &userInput,&aNewLine);

		if (aNewLine == '\n')
		{
			for (i = 0; stringArray[i] != '\0'; i++)
			{
				if (userInput == stringArray[i])
				{
					count++;
				}
			}

			if (count == 0)
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

	int i, valid, countChar, countDigits;
	char array[1000 + 1] = { '\0' };

	do
	{
		valid = 1;
		countChar = countDigits = 0;

		scanf("%1000[^\n]", array);
		
		for (i = 0; array[i] !='\0'; i++)
		{
			countChar++;

			if (array[i] >= '0' && array[i] <= '9')
			{
				countDigits++;
			}
		}

		if (countDigits > 0)
		{
			valid = 0;
			printf("ERROR: Do not input number: ");
		}
		else
		{

			if (countChar > max || countChar < min)
			{
				valid = 0;
				if (max == min)
				{
					printf("ERROR: String length must be exactly %d chars: ", max);
				}
				else if (countChar > max)
				{
					printf("ERROR: String length must be no more than %d chars: ", max);
				}
				else if (countChar < min)
				{
					printf("ERROR: String length must be between %d and %d chars: ", min, max);
				}
			}
			else
			{
				for (i = 0; array[i] != '\0'; i++)
				{
					ptrString[i] = array[i];
				}
			}
		}

		clearInputBuffer();

	} while (!valid);
}

// Display an array of 10-character digits as a formatted phone number
void displayFormattedPhone(const char* ptrString)
{
	const int phoneLength = 10;
	int i, countDigits = 0;

	if (ptrString != NULL)
	{
		for (i = 0; ptrString[i] != '\0'; i++)
		{
			if (ptrString[i] >= '0' && ptrString[i] <= '9')
			{
				countDigits++;
			}
		}
	}

	if (countDigits != phoneLength)
	{
		printf("(___)___-____");
	}
	else
	{
		for (i = 0; i < countDigits; i++)
		{
			switch (i)
			{
			case 0:
				putchar('(');
				break;
			case 3:
				putchar(')');
				break;
			case 6:
				putchar('-');
				break;
			}

			printf("%c", ptrString[i]);
		}
	}
}
