
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

// Global variables for guest information


int guestStayLengths[6];
int guestnumber[6];
int guestRoomChoices[6];
char guestBoardTypes[6][3];
char guestBookingIDs[6][80];
bool guestNewspapers[6];
int guestCount = 0;

char firstName[50];
char surName[50];
int adults;
int children;
int stayLength;
int roomChoice;
char boardType[3];
char bookingID[80];
bool newspaper;
bool namecheck;
bool roomsAvailable[6] = {true, true, true, true, true, true};
int roomPrices[6] = {100, 100, 85, 75, 75, 50};
int boardPrices[3] = {20, 15, 5};
int nameCheck(const char *s ) {
    int k=0;
    if (strlen(s) >16 || strlen(s) <=0) {
        printf(" The name you etered is ethier too long or too short \n");
        k++;
    }

        for(int i=0;i<strlen(s);i++) {
            if ((s[i] <65 )||(s[i] <97 && s[i]>90)||( s[i]>122)  ) {
               k++;
            }
        }

    if (k>0){ printf(" The name cant have any unusuall characthers\n");}
    else if (k==0){return 1;}
}

int daysInMonth(int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return 28;
        default: return 0;
    }

}

int confirmOrQuit(const char* question) {
    char c;
    printf("%s (Y/N, Q to quit): ", question);
    scanf(" %c", &c);
    c = toupper(c);
    if (c == 'Q') {return -1;}
    if (c == 'N') {return 0;}
     if (c == 'Y') {return 1;}
    else { return 2;}
}


int getBoardPrice(const char* type) {
    if (strcmp(type, "FB") == 0) return boardPrices[0];
    if (strcmp(type, "HB") == 0) return boardPrices[1];
    if (strcmp(type, "BB") == 0) return boardPrices[2];
    return 0;
}

void checkin() {
    int day, month, year;

    printf("************* Welcome to Kap Hotel Check-in ***********\n");
    printf("You can quit at any question by pressing 'Q'.\n");

    while (true) {
        int p=0;
        do {
            printf("Enter main guest's first name: ");
            scanf("%s", firstName);
            p= nameCheck(firstName );
        }while(p != 1);

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        int q=0;
       do {
           printf("Enter main guest's surname: ");
           scanf("%s", surName);
            q= nameCheck(surName);
       }while (q != 1);
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter main guest's DOB (DD/MM/YY): ");
        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            printf("Invalid format.\n");
            while (getchar() != '\n');
            continue;
        }
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month)) {
            printf("Invalid date.\n");
            continue;
        }
        if (year>2007) {
            printf("children cant sign up plaese bring and adult.\n");
            continue;

        }
        if (year<1925) {
            printf("You cant be more than 100 years old that is not possible.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;

    }


    while (true) {
        printf("Enter number of adults (16+): ");
        scanf("%d", &adults);
        printf("Enter number of children (15 or under): ");
        scanf("%d", &children);

        if (children > 0 && adults < 1) {
            printf("Children must be accompanied by at least one adult.\n");
            continue;
        }
        if (adults + children > 4) {
            printf("Maximum guests allowed is 4.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter number of days to stay (max 15): ");
        scanf("%d", &stayLength);
        if (stayLength < 1 || stayLength > 15) {
            printf("Invalid stay length.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("Enter board type (HB/FB/BB): ");
        scanf("%s", boardType);
        if (strcmp(boardType, "HB") != 0 &&
            strcmp(boardType, "FB") != 0 &&
            strcmp(boardType, "BB") != 0) {
            printf("Invalid board type.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("\nAvailable rooms:\n");
        for (int i = 0; i < 6; i++)
            printf("Room %d - GDP%d - %s\n", i + 1, roomPrices[i], roomsAvailable[i] ? "Available" : "Occupied");

        printf("Choose room number: ");
        scanf("%d", &roomChoice);

        if (roomChoice < 1 || roomChoice > 6 || !roomsAvailable[roomChoice - 1]) {
            printf("Room unavailable or invalid.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("Do you want a newspaper? (Y/N): ");
        char c;
        scanf(" %c", &c);
        if (toupper(c) == 'Q') return;
        newspaper = (toupper(c) == 'Y');
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    roomsAvailable[roomChoice - 1] = false;
    int r;
    srand(time(NULL));
    r = rand() % 100;
    strcpy(bookingID, surName);
    snprintf(bookingID, sizeof(bookingID), "%s%d", surName, r);

    printf("\nBooking Summary:\n");
    printf("Guest: %s %s\n", firstName, surName);
    printf("Adults: %d, Children: %d\n", adults, children);
    printf("Stay: %d days\n", stayLength);
    printf("Board type: %s (GDP%d per person per day)\n", boardType, getBoardPrice(boardType));
    printf("Room: %d (GDP%d)\n", roomChoice, roomPrices[roomChoice - 1]);
    printf("Newspaper: %d\n", newspaper );
    printf("Booking ID: %s\n", bookingID);
    printf("\n************* Check-in Complete ***********\n");
}

void storeInfo() {

    guestStayLengths[guestCount] = stayLength;
    guestRoomChoices[guestCount] = roomChoice;
    strcpy(guestBoardTypes[guestCount], boardType);
    strcpy(guestBookingIDs[guestCount], bookingID);
    guestNewspapers[guestCount] = newspaper;
    guestnumber[guestCount] = children + adults;
    guestCount++;

    printf("\nGuest stay info has been stored under booking ID: %s\n", bookingID);
}

void findAndPrintByID() {
    char searchID[80];
    printf("\nEnter Booking ID to search: ");
    scanf("%s", searchID);

    for (int i = 0; i < guestCount; i++) {
        if (strcmp(guestBookingIDs[i], searchID) == 0) {

            printf("\n=== Guest Found ===\n");
            printf("Booking ID: %s\n", guestBookingIDs[i]);
            printf("Room: %d\n", guestRoomChoices[i]);
            printf("Stay Length: %d nights\n", guestStayLengths[i]);
            printf("number of guests: %d \n", guestnumber[i]);
            printf("Board Type: %s\n", guestBoardTypes[i]);
            printf("Newspaper: %d\n", guestNewspapers[i]);
            printf("====================\n");
            return;
        }
    }

    printf("\nNo guest found with Booking ID: %s\n", searchID);
}


char bookTable(int guestNum);
void processTableChoice(int *guestNumber);

//GLOBAL VARIABLES FOR THIS MODULE ONLY: these variables have scope throughout the whole dinner table subprogram
//these variables change as the program continues and when users keep booking tables
int endor7 = 0;
int naboo7 = 0;
int tatooine7 = 0;
int endor9 = 0;
int naboo9 = 0;
int tatooine9 = 0;



//subroutine to decide whether the user's table has been booked or not
void processTableChoice(int *guestNumber) {
    char tableChoice;
    //call to the subroutine to list the available tables and book a choice
    tableChoice = bookTable(guestNumber[3]);

    //the table chosen by the user is now unavailable, update tables and communicate to user
    //if the user couldn't choose a table, explain that none were available
    switch (tableChoice) {
        case 'A':
            endor7 = 1;
            printf("Your table has successfully been booked - Endor at 7PM\n");
            break;
        case 'B':
            naboo7 = 1;
            printf("Your table has successfully been booked - Naboo at 7PM\n");
            break;
        case 'C':
            tatooine7 = 1;
            printf("Your table has successfully been booked - Tatooine at 7PM\n");
            break;
        case 'D':
            endor9 = 1;
            printf("Your table has successfully been booked - Endor at 9PM\n");
            break;
        case 'E':
            naboo9 = 1;
            printf("Your table has successfully been booked - Naboo at 9PM\n");
            break;
        case 'F':
            tatooine9 = 1;
            printf("Your table has successfully been booked - Tatooine at 9PM\n");
            break;
        case 'X':
            printf("Sorry, this table is unavailable.\n");
            char option;
            printf("Would you like to choose a different table? (Y/N) : ");
            fflush(stdin);
            scanf("%c", &option);
            if (toupper(option) == 'Y') { //subprogram called again, user can make new choice
                processTableChoice(guestNumber);
            }
            break;
        case 0:
            printf("Sorry, there are no available tables today.\n");
    }
}


//subroutine to display the available dinner table choices and take the user's choice
char bookTable(int guestNum) {

    if (guestNum <= 4) {

        //message to display if no tables are available
        if (endor7 == 1 && endor9 == 1 && naboo7 == 1 && naboo9 == 1 && tatooine7 == 1 && tatooine9 == 1) {
            char choice = 0;
            return choice; //return choice to show that no tables could be booked by the user
        }
        else {
            //allow user to enter their choice of table and confirm their choice
            char choice;
            do {
                //messages to display every table that hasn't been booked yet
                printf("The available tables today are listed as below: \n");
                if (endor7 == 0) {
                    printf("A) Endor at 7pm\n");
                }
                if (naboo7 == 0) {
                    printf("B) Naboo at 7pm\n");
                }
                if (tatooine7 == 0) {
                    printf("C) Tatooine at 7pm\n");
                }
                if (endor9 == 0) {
                    printf("D) Endor at 9pm\n");
                }
                if (naboo9 == 0) {
                    printf("E) Naboo at 9pm\n");
                }
                if (tatooine9 == 0) {
                    printf("F) Tatooine at 9pm\n");
                }

                printf("Enter your choice of table (Enter letter): ");
                fflush(stdin);
                scanf("%c", &choice);
                char confirm;
                printf("Is this correct? (Y/N): ");
                fflush(stdin);
                scanf("%c", &confirm);
                if (toupper(confirm) == 'N') {
                    choice = 'X'; //dummy value given so the do-while loop repeats
                }
                choice = toupper(choice);
                if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E' && choice != 'F' && choice != 'X') {
                    printf("Please enter an option from the given list.\n");
                }
            }while (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E' && choice != 'F');

            //if the user chooses a table that is already booked, choice is given a dummy value
            //this value will be rejected by the process table procedure
            if (endor7 == 1 && choice == 'A') {
                choice = 'X';
            }
            if (naboo7 == 1 && choice == 'B') {
                choice = 'X';
            }
            if (tatooine7 == 1 && choice == 'C') {
                choice = 'X';
            }
            if (endor9 == 1 && choice == 'D') {
                choice = 'X';
            }
            if (naboo9 == 1 && choice == 'E') {
                choice = 'X';
            }
            if (tatooine9 == 1 && choice == 'F') {
                choice = 'X';
            }
            return choice;
        }

    }
    else {
        printf("Sorry, there is not a free table for your party");
    }
}
int main() {
for (int i=0;i<100000;i++) {
    char choice;

    printf("Do you want to Check In (C), Check Out (O), Dinner (D), CHECK info(I), or Quit (Q)? ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice == 'C') {
        checkin();
        storeInfo();

    }
    else if (choice == 'O') {
        printf("Check Out function not added yet.\n");
    }
    else if (choice == 'D') {
           //dummy code to enter values for the global variables, which would be used in this module when integrated
    printf("ENTER TEST DATA\n");
    char guestSystem[6][30];
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            //user to enter a bookingID for room 4
            printf("Booking ID value for room 5: ");
            gets(guestSystem[i]);
        }
    }

    int guestNumber[6];
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            guestNumber[i] = 3;
            printf("%d\n", guestNumber[i]);
        }
    }

    char boardType[6][3];
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            printf("Enter board type for room 5: ");
            gets(boardType[i]);
        }
    }
    //for testing, program outputs all the data that should be passed into this program
    puts(guestSystem[4]); //booking ID for my room
    printf("%d\n", guestNumber[4]); //number of guests in my room
    puts(boardType[4]); //my room's board type

    //MAIN CODE BEGINS HERE
    while (1) {
        printf("************* Dinner table booking ***********\n");

        int flag = 0; //variable to confirm whether the guest exists in the system
        char bookingID[30];

        printf("\n Please enter your Booking ID: ");
        scanf("%s", bookingID);


        for (int i = 0; i < 6; i++) {
            int compareID = strcmp(bookingID, guestSystem[i]);
            if (compareID == 0) {
                flag = 1;

                int compareBoardFB = strcmp(boardType[i], "FB"); //check if board type is FB (value 0)
                int compareBoardHB = strcmp(boardType[i], "HB"); //check if board type is HB (value 0)
                if (compareBoardFB == 0 || compareBoardHB == 0) { //if their board type is FB or HB, proceed

                    //call the procedure to proceed to table booking and processing
                    processTableChoice(guestNumber);

                }
                else {
                    printf("Sorry, you can only book a table if your board is FB or HB\n");
                }

            }
        }
        if (flag == 0) {
            printf("ERROR: Unable to book table as guest does not exist\n");
        }

    }

    return 0;
    }
    else if (choice == 'I') {
        findAndPrintByID();
    }
    else if (choice == 'Q') {
        printf("Goodbye!\n");
    }
    else {
        printf("Invalid option.\n");
    }
}
    return 0;
}