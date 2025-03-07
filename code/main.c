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
void displayMainMenu();
void displayOrganizerMenu();
void displayParticipantMenu();
void clearScreen(); // if you want to clear the screen just call it
void pauseScreen(); // if you want to hold the screen just call it

int main(){
    printf("Hello World\n");
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