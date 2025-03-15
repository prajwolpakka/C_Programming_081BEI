#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

// Structure for Bus details
struct Bus{
    char num[10];
    char pick[20];
    char drop[20];
    int seat;
    int time1;
};

// Structure for Passenger details
struct Passenger{
    char name[20];
    int seatNumber;
};

// Function declarations
void login();
void view_buses();
void admin_menu();
void add_bus();
void remove_bus();
void view_passengers();
void client_menu();
void book_ticket();
void cancel_ticket();
void update_seat_count(char *bus_num, int change);
void exit_program();

int main(){
    login();
    return  0;
}

// Login Function
void login(){
    system("cls");
    char user[20], pass[20];
    printf("Enter username: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", pass);
    
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
        admin_menu();
    } else {
        client_menu();
    }
}

// View Available Buses
void view_buses(){
    system("cls");
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        printf("No buses available!\n");
        exit_program();
    }
    
    struct Bus bus;
    printf("Bus Number\tPickup\tDrop\tSeats\tTime\n");
    printf("------------------------------------------------\n");
    while (fscanf(fp, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        printf("%s\t%s\t%s\t%d\t%d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }
    fclose(fp);
}

// Admin Menu
void admin_menu(){
    struct Bus bus;
    int choice,con1;
    system("cls");
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        printf("\t\tNo buses available!\n\n");
        printf("Enter 1 to add bus : ");
        scanf("%d",&con1);
        if(con1==1)
            add_bus();
        else
            exit_program();
        
    }
    else{
    system("cls");
    rewind(fp);
    printf("Bus Number\tPickup\tDrop\tSeats\tTime\n");
    printf("------------------------------------------------\n");
    while (fscanf(fp, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        printf("%s\t%s\t%s\t%d\t%d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }
    
    
        printf("\n1. Add Bus\n2. Remove Bus\n3. View Passengers\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: add_bus(); break;
            case 2: remove_bus(); break;
            case 3: view_passengers(); break;
            default: exit_program();
        }
    }
    fclose(fp);
}


// Add Bus
void add_bus(){
    system("cls");
    FILE *fp = fopen("bus.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        printf("Press any key to return to dashboard !!");
        getch();
        admin_menu();
    }
    
    struct Bus bus;
    printf("Enter bus number: ");
    scanf("%s", bus.num);
    printf("Enter pickup location: ");
    scanf("%s", bus.pick);
    printf("Enter drop location: ");
    scanf("%s", bus.drop);
    printf("Enter no of seats: ");
    scanf("%d", &bus.seat);
    printf("Enter bus departure time: ");
    scanf("%d", &bus.time1);
    
    fprintf(fp, "%s %s %s %d %d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    fclose(fp);
    printf("Bus added successfully!\n");
    printf("Press any key to return to dashboard !!");
    getch();
    admin_menu();
}

// Remove Bus
void remove_bus() {
    system("cls");
    
    char bus_num[10];
    struct Bus bus;
    int found = 0;

    FILE *fp = fopen("bus.txt", "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *temp = fopen("temp.txt", "w+");
    if (temp == NULL) {
        perror("Error creating temporary file");
        fclose(fp);
        return;
    }

    printf("Enter bus number: ");
    scanf("%s", bus_num);
    
    while (fscanf(fp, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        if (strcmp(bus.num, bus_num) == 0) {
            found = 1;  
            continue;
        }
        fprintf(temp, "%s %s %s %d %d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        if (remove("bus.txt") != 0) {
            perror("Error deleting original file");
        } else if (rename("temp.txt", "buses.txt") != 0) {
            perror("Error renaming temporary file");
        } else {
            printf("Bus removed successfully!\n");
        }
    } else {
        printf("Bus not found!\n");
        remove("temp.txt"); 
    }
}


// View Passengers
void view_passengers(){
    system("cls");
    char bus_num[10];
    struct Passenger p;
    printf("Enter bus number to view passengers: ");
    scanf("%s", bus_num);
    
    char filename[20];
    sprintf(filename, "bus_%s.txt", bus_num);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No passengers found!\n");
        printf("Enter any key to return to dashboard !!");
        getch();
        admin_menu();
    }
    
    else{
    printf("Passenger Name\tSeat Number\n");
    printf("-------------------------------\n");
    while (fscanf(fp, "%s %d", p.name, &p.seatNumber) != EOF) {
        printf("%s\t%d\n", p.name, p.seatNumber);
    }
    fclose(fp);
    printf("Enter any key to return to dashboard !!");
    getch();
    admin_menu();
}
}

// Client Menu
void client_menu(){
    system("cls");
    int choice;
    struct Bus bus;
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        printf("No buses available!\n");
        exit_program();
    }
    
    
    printf("Bus Number\tPickup\tDrop\tSeats\tTime\n");
    printf("------------------------------------------------\n");
    while (fscanf(fp, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        printf("%s\t%s\t%s\t%d\t%d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }
    fclose(fp);
    
   
        printf("\n1. Book Ticket\n2. Cancel Ticket\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: book_ticket(); break;
            case 2: cancel_ticket(); break;
            default: exit_program();
        }
}

// Book Ticket
void book_ticket() {
    system("cls");
    struct Bus bus;
    char bus_num[10];
    char filename[20];
    int found = 0;
    struct Passenger temp;
    struct Passenger p;
    int seatTaken;
    printf("Enter bus number to book a ticket: ");
    scanf("%s", bus_num);

    FILE *fp1 = fopen("bus.txt", "r+");
    if (fp1 == NULL) {
        printf("Error opening bus file.\n");
        return;
    }

    // Search for bus
    while (fscanf(fp1, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        if (strcmp(bus.num, bus_num) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp1);

    if (found == 1) {
        update_seat_count(bus_num, -1);
        sprintf(filename, "bus_%s.txt", bus_num);
        
        FILE *fp = fopen(filename, "a+"); // Open file in append+read mode
        if (fp == NULL) {
            printf("Error opening booking file.\n");
            return;
        }

        
        do {
            seatTaken = 0;
            printf("Enter passenger name: ");
            scanf("%s", p.name);
            printf("Enter seat number: ");
            scanf("%d", &p.seatNumber);

            // Check if seat number is already booked
            
            rewind(fp); // Move pointer to the start of file
            while (fscanf(fp, "%s %d", temp.name, &temp.seatNumber) != EOF) {
                if (temp.seatNumber == p.seatNumber) {
                    printf("Seat number %d is already booked! Choose another seat.\n", p.seatNumber);
                    seatTaken = 1;
                    break;
                }
            }
        } while (seatTaken);

        // Write passenger details to file
        fprintf(fp, "%s %d\n", p.name, p.seatNumber);
        fclose(fp);

        printf("Ticket booked successfully!\n");
    } else {
        printf("Bus not found.\n");
    }

    printf("Enter any key to go to the dashboard!!");
    getch();
    client_menu();
}

// Cancel Ticket
void cancel_ticket(){
    system("cls");
    char bus_num[10], passenger_name[20];
    printf("Enter bus number: ");
    scanf("%s", bus_num);
    printf("Enter passenger name: ");
    scanf("%s", passenger_name);
    
    char filename[20];
    sprintf(filename, "bus_%s.txt", bus_num);
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    struct Passenger p;
    int found = 0;
    while (fscanf(fp, "%s %d", p.name, &p.seatNumber) != EOF) {
        if (strcmp(p.name, passenger_name) == 0) {
            found = 1;
        } else {
            fprintf(temp, "%s %d\n", p.name, p.seatNumber);
        }
    }
    fclose(fp);
    fclose(temp);
    
    remove(filename);
    rename("temp.txt", filename);
    
    if (found) {
        update_seat_count(bus_num, 1);
        printf("Ticket canceled successfully!\n");
        printf("Enter any key to go to dashboard !!");
        getch();
        client_menu();
    } else {
        printf("Passenger not found!\n");
        printf("Enter any key to go to dashboard !!");
        getch();
        client_menu();
    }
}

// Update Seat Count
void update_seat_count(char *bus_num, int change){
    system("cls");
    struct Bus bus;
    FILE *fp = fopen("bus.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    
    while (fscanf(fp, "%s %s %s %d %d", bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        if (strcmp(bus.num, bus_num) == 0) {
            bus.seat += change;
        }
        fprintf(temp, "%s %s %s %d %d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }
    fclose(fp);
    fclose(temp);
    
    remove("bus.txt");
    rename("temp.txt", "bus.txt");
}

void exit_program(){
    system("cls");
    printf("Enter any key to exit !!");
    getch();
    system("cls");
    printf("Exiting the system...\n");
}