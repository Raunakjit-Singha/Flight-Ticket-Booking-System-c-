#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

struct Flight
{
    char user[20];
    char pass[20];
    int ticketNo;
};

struct BoardingPass
{
    char passengerName[50];
    int seatNumber;
    long ph[15];
    int flightNo[20];
    char departureGate[10];
    char destination[50];
};

struct UserAccount
{
    char username[20];
    char password[20];
};

void createAccount()
{
    struct UserAccount newUser;
    printf("Enter the username: ");
    scanf("%s", newUser.username);

    printf("Enter a password: ");
    scanf("%s", newUser.password);

    FILE *accountsFile = fopen("accounts.txt", "a");
    if (accountsFile != NULL)
    {
        fprintf(accountsFile, "%s %s\n", newUser.username, newUser.password);
        fclose(accountsFile);
        printf("Account created successfully!\n");
    }
    else
    {
        printf("Error creating account. Please try again later.\n");
    }
}

int loginCheck()
{
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    FILE *accountsFile = fopen("accounts.txt", "r");
    if (accountsFile != NULL)
    {
        char storedUsername[20];
        char storedPassword[20];
        int found = 0;

        while (fscanf(accountsFile, "%s %s", storedUsername, storedPassword) != EOF)
        {
            if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0)
            {
                found = 1;
                break;
            }
        }

        fclose(accountsFile);

        if (found)
        {
            printf("Login successful!\n");
            return 1;
        }
        else
        {
            printf("Invalid username or password. Please try again.\n");
            return 0;
        }
    }
    else
    {
        printf("Error accessing accounts database. Please try again later.\n");
        return 0;
    }
}

void display_LoginMenu()
{
    printf("\n");
    printf("\n<<<<<<<<<--Flight Ticket Booking System-->>>>>>>>>\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Exit\n");
}
void displayMenu()
{
    printf("\n");
    printf("1. Display available flights\n");
    printf("2. Book a Flight\n");
    printf("3. Cancel Flight\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    
}

void displayFlight()
{
    printf("\n\tAirline Name\t\tFlight Number\tDate\t\tDestination\tPrice\n");
    printf("\n\t16063.  Indigo\t\t6E-6063E\t3 Dec,2023\tCCU-MAA\t\t7845\n");
    printf("\t26407.  Air India\tET-6407W\t7 Dec,2023\tBLR-DEL\t\t6800\n");
    printf("\t33239.  Emirates\tADS-3239F\t11 Dec,2023\tDEL-MUM\t\t11780\n");
    printf("\t46087.  Fly Dubai\tFLD-6087E\t13 Dec,2023\tDEL-DBU\t\t9790\n");
    printf("\t54844.  Spicejet\tSPJ-484U\t15 Dec,2023\tSHL=NJ\t\t3500\n\n");
}

int bookingflight()
{
    struct BoardingPass b;
    int flightNo;
    printf("Passenger Name( First Name ): ");
    scanf("%s", &b.passengerName);

    printf("Phone Number: ");
    scanf("%d", &b.ph);

    printf("enter the flight number: ");
    scanf("%d", &flightNo);

    srand(time(0));

    int seatrd = (rand() % 10) + 1;
    int seatrda = (rand() % 10) + 1;

    int randomAsciiA = rand() % 26 + 'A';
    char alpha = (char)randomAsciiA;

    printf("\nYOUR TICKET HAS BEEN BOOKED\n\n");
    printf("--------------------<BOARDING PASS>---------------------------\n");
    printf("\tBoarding Passenge Name\tSeat Number\tDeparture Gate\n ");
    printf("\t%s", b.passengerName);
    printf("\t\t%d%c", seatrd, alpha);
    printf("\t\t%d\n", seatrda);

    FILE *ptra = fopen("flhistory.txt", "a");
    if (ptra == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    fprintf(ptra, "Flight No: %d\n", flightNo);
    fprintf(ptra, "passenger name:%s\n", b.passengerName);

    fclose(ptra);
    return 0;
}

void cancelFlight()
{
    printf("Flight Cancellation\n");
    printf("Enter the flight number to cancel the ticket: ");
    int flightNumberToCancel;
    scanf("%d", &flightNumberToCancel);

    FILE *history = fopen("flhistory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (history == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    int flightNo;
    int canceled = 0;

    while (fgets(line, sizeof(line), history))
    {
        if (sscanf(line, "Flight No: %d", &flightNo) == 1 && flightNo == flightNumberToCancel)
        {
            printf("------------------Ticket canceled:--------------------\n%s-", line);
            printf("<<<<<Ticket for Flight No: %d has been canceled.\n>>>>>>", flightNo);
            printf("NAME OF THE PASSENGER WILL NOT BE DELETED FORM HISTORY\n\n");
            canceled = 1;
        }
        else
        {
            fputs(line, temp);
        }
    }

    fclose(history);
    fclose(temp);

    remove("flhistory.txt");
    rename("temp.txt", "flhistory.txt");

    if (!canceled)
    {
        printf("No tickets found for Flight No: %d\n", flightNumberToCancel);
    }
}
int main()
{
    struct Flight a;
    struct BoardingPass myBoardingPass;
    a.user[20];
    a.pass[20];
    char user[10], pass[10];
    int choice, choice2, f = 0;
    do
    {

        display_LoginMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            if (loginCheck())
            {
                f = 1;
                if (f == 1)
                {
                    do
                    {
                        displayMenu();
                        scanf("%d", &choice2);
                        switch (choice2)
                        {
                        case 1:
                            displayFlight();
                            break;
                        case 2:
                            bookingflight();
                            break;
                        case 3:
                            cancelFlight();
                            break;
                        case 4:
                            printf("Exiting...\n");
                            break;
                        default:
                            break;
                        }
                    } while (choice2 != 4);
                }
            }
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            break;
        }
    } while (choice != 3);

    return 0;
}