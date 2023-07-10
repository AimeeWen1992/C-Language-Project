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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, record = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            record = 1;
        }
    }

    if (!record)
    {
        printf("*** No records found ***\n\n");
    }

    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do   
    {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');

        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        default:
            break;
        }

    } while (selection);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int index = 0;

    index = findPatientIndexByPatientNum(0, patient, max);

    if (index > -1)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int userInput, index;

    printf("Enter the patient number: ");
    userInput = inputIntPositive();
    index = findPatientIndexByPatientNum(userInput, patient, max);
    putchar('\n');

    if (index > -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int userInput, index;
    struct Patient emptyStruct = { 0 };

    printf("Enter the patient number: ");
    userInput = inputIntPositive();
    index = findPatientIndexByPatientNum(userInput, patient, max);
    putchar('\n');

    if (index > -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");

        if (inputCharOption("yn") == 'y')
        {
            printf("Patient record has been removed!\n\n");
            patient[index] = emptyStruct;
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;

    sort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }

    printf("\n");
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j;
    struct Date date = { 0 };

    inputCalender(&date);

    putchar('\n');

   sort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) 
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    if (data->appointments[i].date.year == date.year &&
                        data->appointments[i].date.month == date.month &&
                        data->appointments[i].date.day == date.day) 
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    printf("\n");
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppointment,
                    struct Patient* patient, int maxPatient)
{
    struct Date date = { 0 };
    struct Time time = { 0 };
    int patientNumber, index;
    int validTimeSlot, validHourAndInterval;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    index = findPatientIndexByPatientNum(patientNumber, patient, maxPatient);

    if (index > -1) 
    {
        do
        {
            validTimeSlot = 1;

            inputCalender(&date);

            do
            {
                validHourAndInterval = 1;

                inputTimes(&time);  

                if (timeSlotAvailable(date, time, appointments, maxAppointment))
                {

                    if ((time.hour < OPEN_HOUR || time.hour > CLOSE_HOUR) ||
                        (time.hour == CLOSE_HOUR && time.min > 0) ||
                        (time.min % MINUTE_INTERVAL != 0))
                    {
                        printf("ERROR: Time must be between %02d:00 and"
                               " %02d:00 in %02d minute intervals.\n\n"
                               , OPEN_HOUR, CLOSE_HOUR, MINUTE_INTERVAL);

                        validHourAndInterval = 0;
                    }
                }
                else
                {
                    validTimeSlot = 0;
                    putchar('\n');
                    printf("ERROR: Appointment timeslot is not available!\n\n");
                }

            } while (!validHourAndInterval);

        } while (!validTimeSlot);

        index = nextSlotAvailable(appointments, maxAppointment);
        appointments[index].date = date;
        appointments[index].time = time;
        appointments[index].patientNumber = patientNumber;
        putchar('\n');
        printf("*** Appointment scheduled! ***\n\n");
    }
    else
    {
        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppointment,
                       struct Patient* patient, int maxPatient)
{
    struct Date date = { 0 };
    struct Appointment emptyStruct = { 0 };
    int index, patientNumber, appointIndex;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, patient, maxPatient);

    if (index > -1)
    {
        inputCalender(&date);

        appointIndex = validAppointment(patientNumber, date, appointments, maxAppointment);

        if (appointIndex > -1) 
        {
            putchar('\n');
            displayPatientData(&patient[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') 
            {
                putchar('\n');
                printf("Appointment record has been removed!\n\n");
                appointments[appointIndex] = emptyStruct;
            }
            else
            {
                printf("Operation aborted.\n\n");
            }
        }
        else
        {
            printf("ERROR: No appointment for this date!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int userInput, index;

    printf("Search by patient number: ");
    userInput = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(userInput, patient, max);

    if (index > -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }

    putchar('\n');
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[PHONE_LEN + 1] = { '\0' };
    int i, valid, record = 0;

    printf("Search by phone number: ");

    
    do
    {
        valid = 1;
        inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);

        if (!checkCstringAlldigits(phoneNumber, PHONE_LEN))
        {
            valid = 0;
            printf("ERROR: Input only digits for searching: ");
        }

    } while (!valid);


    putchar('\n');
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            record++;
        }
    }

    if (!record)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }

    putchar('\n');
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maxNumber, i;

    maxNumber = patient[0].patientNumber;

    for (i = 1; i < max; i++)
    {
        if (patient[i].patientNumber > maxNumber)
        {
            maxNumber = patient[i].patientNumber;
        }
    }

    return maxNumber + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i, index = -1;

    for (i = 0; i < max && index == -1; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            index = i;
        }
    }

    return index;
}

// Checks to see whether a time slot is available
int timeSlotAvailable(struct Date date, struct Time time, 
                      struct Appointment* appointments, int maxAppointment)
{
    int i, slotAvailable = 1;

    for (i = 0; i < maxAppointment && slotAvailable; i++)
    {
        // Checking if time slot is available
        if (date.year == appointments[i].date.year && date.month == appointments[i].date.month &&
            date.day == appointments[i].date.day && time.hour == appointments[i].time.hour &&
            time.min == appointments[i].time.min)
        {
            slotAvailable = 0;
        }
    }

    return slotAvailable;
}

// Checks to see which is the next slot that is available and return the index
int nextSlotAvailable(struct Appointment* appointments, int maxAppointment)
{
    int i = 0, available = 0;

    while (available == 0 && i < maxAppointment) 
    {
        if (appointments[i].patientNumber < 1)
        {
            available = 1;
        }

        i++;
    }
    return i;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date, 
                     struct Appointment* appointments, int maxAppointment)
{
    int i, index = -1;

    for (i = 0; i < maxAppointment && index == -1; i++)
    {
        if ((appointments[i].patientNumber == patientNumber) &&
            (appointments[i].date.day == date.day) &&
            (appointments[i].date.month == date.month) &&
            (appointments[i].date.year == date.year))
        {
            index = i;
        }
    }

    return index;
}

// Sorting the appointment schedule by order
void sort(struct Appointment appointments[], int max)
{

    int i, j;
    struct Appointment appiontsTemp = { 0 };

    for (i = 0; i < max; i++)
    {
        appointments[i].time.min = (appointments[i].date.year * 12 * 30 * 24 * 60) +
                                   (appointments[i].date.month * 30 * 24 * 60) +
                                   (appointments[i].date.day * 24 * 60) +
                                   (appointments[i].time.hour * 60) +
                                   (appointments[i].time.min);
    }

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appointments[j].time.min > appointments[j + 1].time.min)
            {
                appiontsTemp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = appiontsTemp;
            }
        }
    }

    for (i = 0; i < max; i++)
    {
        appointments[i].time.min = (appointments[i].time.min) -
                                   (appointments[i].date.year * 12 * 30 * 24 * 60) -
                                   (appointments[i].date.month * 30 * 24 * 60) -
                                   (appointments[i].date.day * 24 * 60) -
                                   (appointments[i].time.hour * 60);
    }
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
           "------------------\n");

    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection, valid;
    char userInputPhone[1000 + 1] = { 0 };

    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");

    selection = inputIntRange(1, 4);

    switch (selection)
    {
    case 1:
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        break;
    case 2:
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        break;
    case 3:
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        break;
    default:
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        break;
    }

    if (selection < 4)
    {
        putchar('\n');
        printf("Contact: %s\n", phone->description);
        printf("Number : ");

        do
        {
            valid = 1;
            scanf("%1000[^\n]", userInputPhone);
            clearInputBuffer();

            if (!checkCstringAlldigits(userInputPhone, PHONE_LEN) ||
                strlen(userInputPhone) != PHONE_LEN)
            {
                valid = 0;
                printf("Invalid %d-digit number! Number: ",PHONE_LEN);
            }
            else
            {
                strcpy(phone->number, userInputPhone);
            }

        } while (!valid);
    }
    else
    {
        *phone->number = '\0';
    }

    putchar('\n');
}

// Get uesr input year-month-day
void inputCalender(struct Date* date)
{
    int lastDay;

    printf("Year        : ");
    date->year = inputIntPositive();

    printf("Month (1-12): ");
    date->month = inputIntRange(1, 12);

    switch (date->month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        lastDay = 30;
        break;
    case 2:
        if ((date->year % 4 == 0 && date->year % 100 != 0) || date->year % 400 == 0)
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
        break;
    default:
        lastDay = 31;
        break;
    }

    printf("Day (1-%d)  : ", lastDay);

    date->day = inputIntRange(1, lastDay);
}

// Get user input hour-min 
void inputTimes(struct Time* time)
{
    printf("Hour (0-23)  : ");
    time->hour = inputIntRange(0, 23);

    printf("Minute (0-59): ");
    time->min = inputIntRange(0, 59);
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = fopen(datafile, "r");
    int i = 0;

    if (fp != NULL)
    {
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n",
                           &patients[i].patientNumber, patients[i].name,
                           patients[i].phone.description, patients[i].phone.number) != EOF    
                           && i < max)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        puts("ERROR: Failed to access file!");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = fopen(datafile, "r");
    int i = 0;

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
               &appoints[i].patientNumber, &appoints[i].date.year, 
               &appoints[i].date.month, &appoints[i].date.day, 
               &appoints[i].time.hour, &appoints[i].time.min) != EOF
               && i < max)
        {
            i++;
        }

        fclose(fp);
        fp = NULL;
    }
    else
    {
        puts("ERROR: Failed to access file!");
    }

    return i;
}