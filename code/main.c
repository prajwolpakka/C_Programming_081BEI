#include <stdio.h>
#include <string.h>
#include <stdlib.h> //data conversion
#include <conio.h> //for getch() function


// constants
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_EVENT_NAME_LEN 100
#define MAX_EVENT_DESCRIPTION_LEN 200
#define MAX_EVENT_LOCATION_LEN 100
#define MAX_DATE_LEN 20
#define MAX_TIME_LEN 20
#define MAX_EVENTS 100
#define MAX_REGISTRATIONS 500

// Structures

typedef struct {
    int id;
    char name[MAX_EVENT_NAME_LEN];
    char description[MAX_EVENT_DESCRIPTION_LEN];
    char location[MAX_EVENT_LOCATION_LEN];
    char time[MAX_TIME_LEN];
    int maxParticipants;
    int currentParticipants;
} Event;

// this is for each Registered Event 
typedef struct {
    int id;
    char username[MAX_USERNAME_LEN];
    int eventId;
} Registration;

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int isAdmin; // 1 for admin, 0 for normal user
    int isOrganizer; // 1 for organizer, 0 for participant
} User;

// function declearation
int login(char *username, int *isAdmin, int *isOrganizer);
void displayAdminMenu();
void displayOrganizerMenu();
void displayParticipantMenu();
void clearScreen(); // if you want to clear the screen just call it
void pauseScreen(); // if you want to hold the screen just call it

int main(){
    char username[MAX_USERNAME_LEN];
    int isOrganizer = 0;
    int isAdmin = 0;
    int choice;
    int loggedIn = 0;

    clearScreen();
    printf("===== WELCOME TO EVENT MANAGEMENT SYSTEM =====\n\n");
    
    ////////////////////////////////////////////////
    /// implement login here 
    // loggedIn = login(username, &isAdmin, &isOrganizer); 

    /*
    -set default username and password for admin
    -sign in and sign up options for organizer and participant

    */
    ////////////////////////////////////////////////

    // for testing
    loggedIn = 1;

    while(!loggedIn){
        printf("Login failed. Try again...\n");
        // loggedIn = login(username, &isAdmin, &isOrganizer);
    }

    clearScreen();
    printf("Welcome %s\n", username);
    pauseScreen();

    /// main loop
    while(1){
        clearScreen();
        if(isAdmin){

            ////////////////////////////////
            /// implement Admin Section here
            ////////////////////////////////

            displayAdminMenu();
        } else if(isOrganizer){
            ////////////////////////////////
            /// implement Organizer Section here
            ////////////////////////////////


            displayOrganizerMenu();
        } else{

            ////////////////////////////////
            /// implement Participant Section here
            ////////////////////////////////

            displayParticipantMenu();
            //// instructions
            /*
            participant menu consists
            1. show all events
              - load events from the file  and show
            2. show available events
              - load events from the file and show only those events which are not full
            3. register for an event
              - ask for event id and register it  if it is vacent
            4. show my regestered events
                - load registrations from the file and show only those events which are registered by the user
            5. cancel registration
                - ask for event id and cancel the registration
            6. back to main menu
            */
        }
    }

    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    printf("\nPress any key to continue...");
    getch();
}