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
int signUP(int isOrgzr);
int signIN(char *username, int *isAdmin, int *isOrganizer, int request); // request 0 for admin , 1 for organizer and 2 for participant
void displayLoginMenu(int opt);
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
void registerForEvent(char *username);
int getNextRegistrationId();
void saveRegistrationToFile(Registration registration);
int showRegisteredEvents(char *username);
void cancelRegistration(char *username);
void updateRegistrationFile(Registration *registrations, int registrationCount);
int safeInput(const char *format, void *input);
void clearInputBuffer();
int isValidTime(const char *time);
int isValidDate(const char *date);
void clearScreen(); // if you want to clear the screen just call it
void pauseScreen(); // if you want to hold the screen just call it

int main(){
    char username[MAX_USERNAME_LEN];
    // char username[MAX_USERNAME_LEN] = "mandip";
    int isOrganizer = 0;
    // int isOrganizer = 1;
    int isAdmin = 0;
    int choice;
    int loggedIn = 0;

    clearScreen();
    printf("===== WELCOME TO EVENT MANAGEMENT SYSTEM =====\n\n");
    
    ////////////////////////////////////////////////
    /// implement login here 
    loggedIn = login(username, &isAdmin, &isOrganizer); 

    /*
    -set default username and password for admin
    -sign in and sign up options for organizer and participant

    */
    ////////////////////////////////////////////////

    // for testing
    // loggedIn = 1;

    while(!loggedIn){
        printf("\nRe-Login...\n");
        loggedIn = login(username, &isAdmin, &isOrganizer);
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
                safeInput("%d", &admChoice);

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
                        // back home
                        printf("Logging Out..\n");
                        // pauseScreen();
                        goto logOut;
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
                safeInput("%d", &orgChoice);

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
                        // back home
                        printf("Logging Out..\n");
                        // pauseScreen();
                        goto logOut;
                    default:
                        printf("Invalid choice. Try again...\n");
                        pauseScreen();
                }

            }

        } else{
            ////////////////////////////////
            /// implement Participant Section here
            ////////////////////////////////
            int partChoice;
            while(1){
                clearScreen();
                displayParticipantMenu();
                printf("Enter your choice: ");
                safeInput("%d", &partChoice);

                switch(partChoice){
                    case 1:
                        // show Available events
                        showEvents(0,username,0);
                        break;
                    case 2:
                        // Register for event
                        registerForEvent(username);
                        break;
                    case 3:
                        // Show Registered Event
                        showRegisteredEvents(username);
                        pauseScreen();
                        break;
                    case 4:
                        // cancel my registration
                        cancelRegistration(username);
                        break;
                    case 5:
                        // back home
                        printf("Logging Out..\n");
                        // pauseScreen();
                        goto logOut;
                    default:
                        printf("Invalid choice. Try again...\n");
                        pauseScreen();
                }

            }
        }
    mainMenu:;
        continue;

    logOut:
        break;
    }

    main();

    // return 0;
}

int login(char *username, int *isAdmin, int *isOrganizer){
    *isAdmin = 0;
    *isOrganizer = 0;
    int status = 0;
    char password[MAX_PASSWORD_LEN];
    // int loginStatus = 0;
    FILE *userFile;
    User user;

    userFile = fopen(".\\files\\users.dat", "rb");
    if (userFile == NULL) {
        userFile = fopen(".\\files\\users.dat", "wb");
        if (userFile == NULL) {
            printf("Error opening users file!\n");
            return 0;
        }
        
        // default admin login credentials
        strcpy(user.username, "mandip");
        strcpy(user.password, "chhetri");
        user.isAdmin = 1;
        user.isOrganizer = 0;
        fwrite(&user, sizeof(User), 1, userFile);
        fclose(userFile);
        
        printf("Default users created:\n");
        printf("1. Admin (Organizer): username - mandip, password - chhetri\n");
        pauseScreen();
    }else{
        fclose(userFile);
    }


    
    displayLoginMenu(0);
    // this is for debugging
    // printf("this is login %d %d",*isAdmin,*isOrganizer);
    int opt;
    printf("Enter your choice: ");
    safeInput("%d", &opt);

    if(opt == 1){
        // admin
        *isAdmin = 1;
        status = signIN(username, isAdmin, isOrganizer,0);

        if(!status){
            *isAdmin = 0;
        }
        return status;

    }else if(opt == 2){
        // organizer
        *isOrganizer = 1;
        *isAdmin = 0;
        while(1){
            displayLoginMenu(1);

            int choice;
            printf("Enter your choice: ");
            safeInput("%d", &choice);

            if(choice == 3){
                return 0;
            }else if(choice == 1){
                status =  signIN(username, isAdmin, isOrganizer,1);
                return status;
            }else if(choice == 2){
                status =  signUP(1);
                if(!status){
                    printf("Sign Up Faild. Try again.\n");
                    pauseScreen();
                }
                return 0;
            }else{
                // return 0; //////////////////////////add here ////////////
                printf("Invalid Choice.\n");
            }
         }

    }else if(opt == 3){
        // participant
        *isOrganizer = 0;
        *isAdmin = 0;
        while(1){
            displayLoginMenu(1);

            int choice;
            printf("Enter your choice: ");
            safeInput("%d", &choice);

            if(choice == 3){
                return 0;
            }else if(choice == 1){
                status = signIN(username, isAdmin, isOrganizer,2);
                return status;
            }else if(choice == 2){
                status =  signUP(0);
                if(!status){
                    printf("Sign Up Faild. Try again.\n");
                    pauseScreen();
                }
                return 0;
            }else{
                printf("Invalid Choice.\n");
            }
        }
    }else if(opt == 4){
        exit(0);
    }else{
        printf("Invalid Choice..");
        return 0;
    }
}



int signUP(int isOrgzr){
    FILE *userFile;
    User user;
    userFile = fopen(".\\files\\users.dat", "ab");
    if (userFile == NULL) {
        printf("Error opening user file!\n");
        return 0;
    }
    clearScreen();
    if(isOrgzr){
        printf("===== ORGANIZER SIGN UP =====\n");
    }else{
        printf("===== PARTICIPANT SIGN UP =====\n");
    }
    printf("Username: ");
    safeInput("%s", user.username);
    printf("Password: ");
    safeInput("%s", user.password);
    user.isAdmin = 0;
    user.isOrganizer = isOrgzr;
    
    fwrite(&user, sizeof(User), 1, userFile);
    fclose(userFile);
    
    printf("Account created successfully!\n");
    pauseScreen();
    return 1;
}



int signIN(char *username, int *isAdmin, int *isOrganizer, int request){ // request 0 for admin , 1 for organizer and 2 for participant
    char password[MAX_PASSWORD_LEN];
    int loginStatus = 0;
    FILE *userFile;
    User user;

    clearScreen(); // clear the screen
    if(request == 0){
        printf("===== LOGIN AS A ADMIN=====\n");
        *isAdmin = 1;
    }else if(request == 1){
        printf("===== LOGIN AS A ORGANIZER=====\n");
        *isOrganizer = 1;
    }else if(request == 2){
        printf("===== LOGIN AS A PARTICIPANT=====\n");
    }else{
        printf("===== LOGIN =====\n");
    }

    printf("Username: ");
    safeInput("%s", username);
    printf("Password: ");
    
    // Password masking
    int i = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == 13) { // Enter key
            password[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
    
    // Check credentials
    userFile = fopen(".\\files\\users.dat", "rb");
    if (userFile == NULL) {
        printf("Error opening user file!\n");
        pauseScreen();
        return 0;
    }
    
    while (fread(&user, sizeof(User), 1, userFile)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            // this is done for debugging
            // printf("Login successful!\n\n");
            // printf("%d %d %d\n",request,user.isAdmin,user.isOrganizer);
            // pauseScreen();

            if(request == 0 && user.isAdmin && !user.isOrganizer){
                loginStatus = 1;
            }else if(request == 1 && user.isOrganizer && !user.isAdmin){
                loginStatus = 1;
            }else if(request == 2 && !user.isAdmin && !user.isOrganizer){
                loginStatus = 1;
            }else{
                loginStatus = 0;
            }
            if(loginStatus){
                *isOrganizer = user.isOrganizer;
                *isAdmin = user.isAdmin;
                break;
            }
        }
    }

    fclose(userFile);
    
    if (!loginStatus) {
        clearScreen();
        printf("Invalid username or password. Please try again.\n");
        pauseScreen();
    }
    
    return loginStatus;

}
////////////////////////////////UI
void displayLoginMenu(int opt){
    clearScreen();
    if (opt == 0){
        printf("===== LOGIN MENU =====\n");
        printf("1. Admin\n");
        printf("2. Organizer\n");
        printf("3. Participant\n");
        printf("4. Exit\n");
    }else{
        printf("===== LOGIN MENU =====\n");
        printf("1. Sign In\n");
        printf("2. Sign Up\n");
        printf("3. Exit\n");
    }
}
void displayOrganizerMenu(){
    printf("===== ORGANIZER MENU =====\n");
    printf("1. Show All Events\n");
    printf("2. Show My Events\n");
    printf("3. Create My Event\n");
    printf("4. Delete My Event\n");
    // printf("5. Back to Main Menu\n");
    printf("5. Logout\n");
}

void displayAdminMenu(){
    printf("===== ADMIN MENU =====\n");
    printf("1. Show All Events\n");
    printf("2. Create Event\n");
    printf("3. Delete Event\n");
    // printf("4. Back to Main Menu\n");
    printf("4. Logout\n");

}

void displayParticipantMenu(){
    printf("===== PARTICIPANT MENU =====\n");
    printf("1. Show Available Events\n");
    printf("2. Register for Event\n");
    printf("3. Show Registered Events\n");
    printf("4. Cancel Registration\n");
    // printf("5. Back to Main Menu\n");
    printf("5. LogOut\n");
}

/////////////UI///////////////
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
            printf("ID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
            printf("------------------------------------------------------------------------------\n");
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
            printf("Organizer\tID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
            printf("----------------");
        } else{
            printf("ID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
        }
        printf("------------------------------------------------------------------------------\n");
        
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
    // getchar(); // Clear input buffer
    // clearInputBuffer();
    fgets(event.name, MAX_EVENT_NAME_LEN, stdin);
    event.name[strcspn(event.name, "\n")] = '\0'; // Remove newline
    
    printf("Event Description: ");
    fgets(event.description, MAX_EVENT_DESCRIPTION_LEN, stdin);
    event.description[strcspn(event.description, "\n")] = '\0';
    
    printf("Location: ");
    fgets(event.location, MAX_EVENT_LOCATION_LEN, stdin);
    event.location[strcspn(event.location, "\n")] = '\0';
    
    do{
        printf("Date (DD/MM/YYYY): ");
        safeInput("%s", event.date);
    } while (!isValidDate(event.date));

    do{
        printf("Time (HH:MM): ");
        safeInput("%s", event.time);
    }while(!isValidTime(event.time));
    
    printf("Maximum Participants: ");
    safeInput("%d", &event.maxParticipants);
    
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
        printf("ID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
        printf("------------------------------------------------------------------------------\n");
        for(i = 0; i < eventCount; i++){
            printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                events[i].id, events[i].name, events[i].location, 
                events[i].date, events[i].time, 
                events[i].currentParticipants, events[i].maxParticipants);
        }

        printf("\nEnter event ID to delete(0 for cancel): ");
        safeInput("%d", &eventId);

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
            printf("ID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
            // printf("------------------------------------------------------------------------------\n");
            printf("------------------------------------------------------------------------------\n");
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
        safeInput("%d", &eventId);

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




int showRegisteredEvents(char *username){
    Event events[MAX_EVENTS];
    Registration registrations[MAX_REGISTRATIONS];
    int eventCount = 0, registrationCount = 0;
    int i, j, registeredEventCount = 0;
    
    // Load events and registrations
    loadEventsFromFile(events, &eventCount);
    loadRegistrationsFromFile(registrations, &registrationCount);
    
    clearScreen();

    // Show registered events
    printf("Your Registered Events:\n");
    printf("ID\tName           \tLocation       \tDate\t\tTime\n");
    printf("--------------------------------------------------\n");
    
    for (i = 0; i < eventCount; i++) {
        for (j = 0; j < registrationCount; j++) {
            if (registrations[j].eventId == events[i].id && 
                strcmp(registrations[j].username, username) == 0) {
                printf("%d\t%-15s\t%-15s\t%s\t%s\n", 
                       events[i].id, events[i].name, events[i].location, 
                       events[i].date, events[i].time);
                registeredEventCount++;
                break;
            }
        }
    }
    
    if (registeredEventCount == 0) {
        printf("You are not registered for any events.\n");
        return 0;
    }
    return 1;
}

void registerForEvent(char *username) {
    Event events[MAX_EVENTS];
    Registration registration, registrations[MAX_REGISTRATIONS];
    int eventCount = 0, registrationCount = 0;
    int eventId, i, found = 0;
    
    // Load events and registrations
    loadEventsFromFile(events, &eventCount);
    loadRegistrationsFromFile(registrations, &registrationCount);
    
    clearScreen();
    printf("===== REGISTER FOR EVENT =====\n\n");

    if (eventCount == 0) {
        printf("No events available for registration.\n");
        pauseScreen();
        return;
    }
    
    printf("Available/Vacant Events:\n");
    printf("ID\tName           \tLocation       \tDate\t\tTime\tRegistered/Max\n");
    printf("------------------------------------------------------------------------------\n");
    
    for (i = 0; i < eventCount; i++) {
       int registered = isEventRegistered(events[i].id, username);
                
                // If user has registered, mark it
                if (registered) {
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d (Registered)\n", 
                           events[i].id, events[i].name, events[i].location, 
                           events[i].date, events[i].time, 
                           events[i].currentParticipants, events[i].maxParticipants);
                } else {
                    printf("%d\t%-15s\t%-15s\t%s\t%s\t%d/%d\n", 
                           events[i].id, events[i].name, events[i].location, 
                           events[i].date, events[i].time, 
                           events[i].currentParticipants, events[i].maxParticipants);
                }
            }
    
    printf("\nEnter Event ID to register (0 to cancel): ");
    safeInput("%d", &eventId);
    
    if (eventId == 0) {
        printf("Registration cancelled.\n");
        pauseScreen();
        return;
    }
    
    // Check if event exists and has space
    for (i = 0; i < eventCount; i++) {
        if (events[i].id == eventId) {
            found = 1;
            
            // already registered or not
            if (isEventRegistered(eventId, username)) {
                printf("You are already registered for this event.\n");
                pauseScreen();
                return;
            }
            
            // event is full or not
            if (events[i].currentParticipants >= events[i].maxParticipants) {
                printf("This event is already full.\n");
                pauseScreen();
                return;
            }
            
            // Register process
            registration.id = getNextRegistrationId();
            strcpy(registration.username, username);
            registration.eventId = eventId;
            
            saveRegistrationToFile(registration);
            
            // Update event participant count
            events[i].currentParticipants++;
            updateEventFile(events, eventCount);
            
            printf("You have successfully registered for %s.\n", events[i].name);
            pauseScreen();
            return;
        }
    }
    
    if (!found) {
        printf("Event with ID %d not found.\n", eventId);
        pauseScreen();
    }
}

void cancelRegistration(char *username) {
    Event events[MAX_EVENTS];
    Registration registrations[MAX_REGISTRATIONS];
    int eventCount = 0, registrationCount = 0;
    int eventId, i, j, found = 0, registeredEventCount = 0,status = 0;
    
    // Load events and registrations
    loadEventsFromFile(events, &eventCount);
    loadRegistrationsFromFile(registrations, &registrationCount);
    
    clearScreen();
    printf("===== CANCEL REGISTRATION =====\n\n");
    
    status = showRegisteredEvents(username);
    
    if(!status){
        pauseScreen();
        return;
    }

    printf("\nEnter Event ID to cancel registration (0 to cancel): ");
    safeInput("%d", &eventId);
    
    if (eventId == 0) {
        printf("Cancellation aborted.\n");
        pauseScreen();
        return;
    }
    
    // Find and remove registration
    for (i = 0; i < registrationCount; i++) {
        if (registrations[i].eventId == eventId && 
            strcmp(registrations[i].username, username) == 0) {
            
            // Remove registration by shifting array
            for (j = i; j < registrationCount - 1; j++) {
                registrations[j] = registrations[j + 1];
            }
            registrationCount--;
            
            // Update registration file
            updateRegistrationFile(registrations, registrationCount);
            
            // Update event participant count
            for (j = 0; j < eventCount; j++) {
                if (events[j].id == eventId) {
                    events[j].currentParticipants--;
                    updateEventFile(events, eventCount);
                    break;
                }
            }
            
            printf("Registration cancelled successfully.\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("You are not registered for event with ID %d.\n", eventId);
    }
    
    pauseScreen();
}

int getNextRegistrationId(){
    Registration registration;
    int maxId = 0;

    FILE *regFile;

    regFile = fopen(".\\files\\registrations.dat", "rb");
    if (regFile == NULL) {
        return 1;
    }

    while (fread(&registration, sizeof(Registration), 1, regFile)) {
        if (registration.id > maxId) {
            maxId = registration.id;
        }
    }

    fclose(regFile);
    return maxId + 1;
}

void saveRegistrationToFile(Registration registration){
    FILE *regFile;

    regFile = fopen(".\\files\\registrations.dat", "ab");
    if (regFile == NULL) {
        printf("Error saving registration to file\n");
        return;
    }

    fwrite(&registration, sizeof(Registration), 1, regFile);
    fclose(regFile);
}

/// Error Handling
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safeInput(const char *format, void *input) {
    int result;
    do {
        // printf("Enter your input: ");  // Ask the same question again
        result = scanf(format, input);
        clearInputBuffer();
        if (result != 1) {
            printf("Invalid input.\n");
            printf("Please enter a valid input : ");
        }
    } while (result != 1);
    
    return result;
}

int isValidDate(const char *date) {
    int dd, mm, yyyy;
    if (sscanf(date, "%d/%d/%d", &dd, &mm, &yyyy) != 3)
        return 0;

    // Check valid range
    if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 1000 || yyyy > 9999)
        return 0;

    return 1;
}

int isValidTime(const char *time) {
    int hh, mm;
    if (sscanf(time, "%d:%d", &hh, &mm) != 2)
        return 0;

    // Check valid range
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59)
        return 0;

    return 1;
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