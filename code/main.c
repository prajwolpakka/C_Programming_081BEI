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
    char organizerName[MAX_USERNAME_LEN];
    int id;
    char name[MAX_EVENT_NAME_LEN];
    char description[MAX_EVENT_DESCRIPTION_LEN];
    char location[MAX_EVENT_LOCATION_LEN];
    char time[MAX_TIME_LEN];
    char date[MAX_DATE_LEN];
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
void showEvents(int showAll, char *username,int isOrganizer);
void createEvent(char *username);
void deleteEvent(char *organizerUsername, int isOrganizer);
int getNextEventId();
void saveEventToFile(Event event);
// void loadEventsFromFile(Event *events, int *eventCount, int status); // status = 0 for user, 1 for organizer and 2 for admin
void loadEventsFromFile(Event *events, int *eventCount); // without status
void loadRegistrationsFromFile(Registration *registrations, int *registrationCount);
int isEventRegistered(int eventId, char *username);
void updateEventFile(Event *events, int eventCount);
void updateRegistrationFile(Registration *registrations, int registrationCount);
void clearScreen(); // if you want to clear the screen just call it
void pauseScreen(); // if you want to hold the screen just call it

int main(){
    // char username[MAX_USERNAME_LEN];
    char username[MAX_USERNAME_LEN] = "mandip";
    // int isOrganizer = 0;
    int isOrganizer = 1;
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

            int admChoice;
            while(1){
                clearScreen();
                displayAdminMenu();
                printf("Enter your choice: ");
                scanf("%d", &admChoice);

                switch(admChoice){
                    case 1:
                        showEvents(1,username,0);
                        break;
                    case 2:
                        createEvent(username);
                        break;
                    case 3:
                        deleteEvent(username,0);
                        break;
                    case 4:
                        printf("Returning to main menu...\n");
                        pauseScreen();
                        goto mainMenu;
                    default:
                        printf("Invalid choice. Try again...\n");
                        pauseScreen();
                }

            }


        } else if(isOrganizer){
            ////////////////////////////////
            /// implement Organizer Section here
            ///////////////////////////////
            int orgChoice;
            while(1){
                clearScreen();
                displayOrganizerMenu();
                printf("Enter your choice: ");
                scanf("%d", &orgChoice);

                switch(orgChoice){
                    case 1:
                        // show all events
                        showEvents(1,username,0);
                        break;
                    case 2:
                        // show my events
                        showEvents(1,username,1);
                        break;
                    case 3:
                        // create my event
                        createEvent(username);
                        break;
                    case 4:
                        // delete my event
                        deleteEvent(username,1);
                        break;
                    case 5:
                        // back to main menu
                        printf("Returning to main menu...\n");
                        pauseScreen();
                        goto mainMenu;
                    default:
                        printf("Invalid choice. Try again...\n");
                        pauseScreen();
                }

            }

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
    mainMenu:;
    }

    return 0;
}

void displayOrganizerMenu(){
    printf("===== ORGANIZER MENU =====\n");
    printf("1. Show All Events\n");
    printf("2. Show My Events\n");
    printf("3. Create My Event\n");
    printf("4. Delete My Event\n");
    printf("5. Back to Main Menu\n");

}

void displayAdminMenu(){
    printf("===== ADMIN MENU =====\n");
    printf("1. Show All Events\n");
    printf("2. Create Event\n");
    printf("3. Delete Event\n");
    printf("4. Back to Main Menu\n");

}


void showEvents(int showAll, char *username,int isOrganizer){
    Event events[MAX_EVENTS];
    Registration registrations[MAX_REGISTRATIONS];
    int eventCount = 0, registrationCount = 0;
    int i, j;
    int hasRegistrations = 0;
    
    // Load events and registrations
    // if (showAll) {
    //     loadEventsFromFile(events, &eventCount, 2);
    // } else {
    //     loadEventsFromFile(events, &eventCount, 1);
    // }


    loadEventsFromFile(events, &eventCount);

    /// here, load regisration is for user if they want to print available events
    loadRegistrationsFromFile(registrations, &registrationCount);

    clearScreen();

    if(isOrganizer){
        printf("===== YOUR EVENTS (%s)=====\n\n",username);
        int newCount = 0;

        for(i = 0; i < eventCount; i++){
            if(strcmp(events[i].organizerName,username) == 0){
                newCount++;
            }
        }
        if(newCount == 0){
            printf("No events available.\n");
            pauseScreen();
            return;
            
        }else{
            printf("ID\tName\t\tLocation\t\tDate\t\tTime\tRegistered/Max\n");
            printf("------------------------------------------------------------------\n");
            for(i = 0; i < eventCount; i++){
                if(strcmp(events[i].organizerName,username) == 0){
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                events[i].id, events[i].name, events[i].location, 
                events[i].date, events[i].time, 
                events[i].currentParticipants, events[i].maxParticipants);
                }
            }
        
        }
        printf("\n");
        pauseScreen();
        return;
    }

    if (showAll) {
        printf("===== ALL EVENTS =====\n\n");
    } else {
        printf("===== AVAILABLE EVENTS =====\n\n");
    }
    
    if (eventCount == 0) {
        printf("No events available.\n");
    } else {
        if(showAll){
            printf("Organizer\tID\t\tName\t\tLocation\t\tDate\t\tTime\tRegistered/Max\n");
        } else{
            printf("ID\tName\t\tLocation\t\tDate\t\tTime\tRegistered/Max\n");
        }
        printf("------------------------------------------------------------------\n");
        
        for (i = 0; i < eventCount; i++) {
            // If not showing all events, check if user has registered for this event
            if (!showAll) {
                int registered = isEventRegistered(events[i].id, username);
                
                // If user has registered, mark it
                if (registered) {
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d (Registered)\n", 
                           events[i].id, events[i].name, events[i].location, 
                           events[i].date, events[i].time, 
                           events[i].currentParticipants, events[i].maxParticipants);
                    hasRegistrations = 1;
                } else {
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                           events[i].id, events[i].name, events[i].location, 
                           events[i].date, events[i].time, 
                           events[i].currentParticipants, events[i].maxParticipants);
                }
            } else {
                printf("%-15s\t%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                       events[i].organizerName,events[i].id, events[i].name, events[i].location, 
                       events[i].date, events[i].time, 
                       events[i].currentParticipants, events[i].maxParticipants);
            }
        }
    }
    
    printf("\n");
    pauseScreen();
}

void createEvent(char *organizerUsername){
    Event event;

    clearScreen();
    printf("===== CREATE NEW EVENT =====\n");
    
    strcpy(event.organizerName, organizerUsername);
    event.id = getNextEventId();

    // Input event details
    printf("Event Name: ");
    getchar(); // Clear input buffer
    fgets(event.name, MAX_EVENT_NAME_LEN, stdin);
    event.name[strcspn(event.name, "\n")] = '\0'; // Remove newline
    
    printf("Event Description: ");
    fgets(event.description, MAX_EVENT_DESCRIPTION_LEN, stdin);
    event.description[strcspn(event.description, "\n")] = '\0';
    
    printf("Location: ");
    fgets(event.location, MAX_EVENT_LOCATION_LEN, stdin);
    event.location[strcspn(event.location, "\n")] = '\0';
    
    printf("Date (DD/MM/YYYY): ");
    scanf("%s", event.date);
    
    printf("Time (HH:MM): ");
    scanf("%s", event.time);
    
    printf("Maximum Participants: ");
    scanf("%d", &event.maxParticipants);
    
    event.currentParticipants = 0;
    
    // Save event to file
    saveEventToFile(event);
    
    printf("\nEvent created successfully with ID: %d\n", event.id);
    pauseScreen();
}

int getNextEventId(){
    Event event;
    int maxId = 0;

    FILE *eventFile;

    eventFile = fopen(".\\files\\events.dat", "rb");
    if(eventFile == NULL){
        return 1;
    }

    while(fread(&event, sizeof(Event), 1, eventFile)){
        if(event.id > maxId){
            maxId = event.id;
        }
    }

    fclose(eventFile);
    return maxId + 1;
}

void saveEventToFile(Event event){
    FILE *eventFile;

    eventFile = fopen(".\\files\\events.dat", "ab");
    if(eventFile == NULL){
        printf("Error saving event to file\n");
        return;
    }

    fwrite(&event, sizeof(Event), 1, eventFile);
    fclose(eventFile);
}

void loadEventsFromFile(Event *events, int *eventCount){
    FILE *eventFile;
    Event event;

    eventFile = fopen(".\\files\\events.dat", "rb");
    if(eventFile == NULL){
        *eventCount = 0;
        return;
    }

    *eventCount = 0;
    while(fread(&event, sizeof(Event), 1, eventFile)){
        events[*eventCount] = event;
        (*eventCount)++;
    }

    fclose(eventFile);
}

void loadRegistrationsFromFile(Registration registrations[], int *registrationCount) {
    FILE *regFile;
    Registration registration;
    
    *registrationCount = 0;
    
    regFile = fopen(".\\files\\registrations.dat", "rb");

    if (regFile == NULL) {
        return;
    }
    
    while (fread(&registration, sizeof(Registration), 1, regFile) && *registrationCount < MAX_REGISTRATIONS) {
        registrations[*registrationCount] = registration;
        (*registrationCount)++;
    }
    
    fclose(regFile);
}


void deleteEvent(char *organizerUsername,int isOrganizer){

    Event events[MAX_EVENTS];
    Registration registrations[MAX_REGISTRATIONS];

    int eventCount = 0, registrationCount = 0;
    int i, j, eventId, found = 0;

    loadEventsFromFile(events, &eventCount);
    loadRegistrationsFromFile(registrations, &registrationCount);

    clearScreen();

    if(!isOrganizer){
        printf("===== DELETE EVENT =====\n");

        // show all event first
        if(eventCount == 0){
            printf("No events available.\n");
            pauseScreen();
            return;
        }

        printf("Available events: \n");
        printf("ID\tName\t\tLocation\t\tDate\t\tTime\tRegistered/Max\n");
        printf("------------------------------------------------------------------\n");
        for(i = 0; i < eventCount; i++){
            printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                events[i].id, events[i].name, events[i].location, 
                events[i].date, events[i].time, 
                events[i].currentParticipants, events[i].maxParticipants);
        }

        printf("\nEnter event ID to delete(0 for cancel): ");
        scanf("%d", &eventId);

        if(eventId == 0){
            printf("Delete operation cancelled.\n");
            pauseScreen();
            return;
        }

        //we have to find event and delete it
        for (i = 0; i < eventCount; i++) {
            if (events[i].id == eventId) {
                // Remove event by shifting array
                for (j = i; j < eventCount - 1; j++) {
                    events[j] = events[j + 1];
                }
                eventCount--;
                
                // Update event file
                updateEventFile(events, eventCount);
                
                // Delete all registrations for this event
                int newRegistrationCount = 0;
                for (j = 0; j < registrationCount; j++) {
                    if (registrations[j].eventId != eventId) {
                        registrations[newRegistrationCount++] = registrations[j];
                    }
                }
                
                // Update registration file if any registrations removed
                if (newRegistrationCount != registrationCount) {
                    updateRegistrationFile(registrations, newRegistrationCount);
                }
                
                printf("Event deleted successfully\n");
                found = 1;
                break;
            }
        }
    }else{
        // printf("===== CHOOSE YOUR EVENT (%s) =====\n", organizerUsername);
        // showEvents(1,organizerUsername,1);
        printf("===== YOUR EVENTS (%s)=====\n\n",organizerUsername);
        int newCount = 0;

        for(i = 0; i < eventCount; i++){
            if(strcmp(events[i].organizerName,organizerUsername) == 0){
                newCount++;
            }
        }
        if(newCount == 0){
            printf("No events available.\n");
            pauseScreen();
            return;
            
        }else{
            printf("ID\tName\t\tLocation\t\tDate\t\tTime\tRegistered/Max\n");
            printf("------------------------------------------------------------------\n");
            for(i = 0; i < eventCount; i++){
                if(strcmp(events[i].organizerName,organizerUsername) == 0){
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                events[i].id, events[i].name, events[i].location, 
                events[i].date, events[i].time, 
                events[i].currentParticipants, events[i].maxParticipants);
                }
            }
        
        }
        /////

        printf("\nEnter event ID to delete(0 for cancel): ");
        scanf("%d", &eventId);

        if(eventId == 0){
            printf("Delete operation cancelled.\n");
            pauseScreen();
            return;
        }

        //we have to find event and delete it
        for (i = 0; i < eventCount; i++) {
            if (events[i].id == eventId && (strcmp(events[i].organizerName,organizerUsername) == 0)) {
                // Remove event by shifting array
                for (j = i; j < eventCount - 1; j++) {
                    events[j] = events[j + 1];
                }
                eventCount--;
                
                // Update event file
                updateEventFile(events, eventCount);
                
                // Delete all registrations for this event
                int newRegistrationCount = 0;
                for (j = 0; j < registrationCount; j++) {
                    if (registrations[j].eventId != eventId) {
                        registrations[newRegistrationCount++] = registrations[j];
                    }
                }
                
                // Update registration file if any registrations removed
                if (newRegistrationCount != registrationCount) {
                    updateRegistrationFile(registrations, newRegistrationCount);
                }
                
                printf("Event deleted successfully\n");
                found = 1;
                break;
            }
        }

    }

    if (!found) {
        printf("Event %d not found.\n",eventId);
    }

    pauseScreen();
    
}

void updateEventFile(Event events[], int eventCount){
    FILE *eventFile;
    int i;

    /// rewrriting event file 

    eventFile = fopen(".\\files\\events.dat", "wb");
    if(eventFile == NULL){
        printf("Error updating event file.\n");
        return;
    }

    for(i = 0; i < eventCount; i++){
        fwrite(&events[i], sizeof(Event), 1, eventFile);
    }

    fclose(eventFile);
}

void updateRegistrationFile(Registration registrations[], int registrationCount) {
    FILE *regFile;
    int i;

    // also rewritting registration file

    regFile = fopen(".\\files\\registrations.dat", "wb");
    if (regFile == NULL) {
        printf("Error opening registrations file for writing!\n");
        return;
    }
    
    for (i = 0; i < registrationCount; i++) {
        fwrite(&registrations[i], sizeof(Registration), 1, regFile);
    }
    
    fclose(regFile);
}

int isEventRegistered(int eventId, char *username) {
    Registration registration;
    FILE *regFile;
    
    regFile = fopen(".\\files\\registrations.dat", "rb");
    if (regFile == NULL) {
        return 0; // No registrations file
    }
    
    while (fread(&registration, sizeof(Registration), 1, regFile)) {
        if (registration.eventId == eventId && strcmp(registration.username, username) == 0) {
            fclose(regFile);
            return 1; // Found registration
        }
    }
    
    fclose(regFile);
    return 0; // No registration found
}




void displayParticipantMenu(){
    printf("===== PARTICIPANT MENU =====\n");
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