#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

struct Bus {
    int num;
    char pick[20];
    char drop[20];
    int seat;
    int time1;
};

struct Passenger {
    char name[20];
    int seatNumber;
};

void login();
void view_buses();
void admin_menu();
void add_bus();
void remove_bus();
void view_passengers();
void client_menu();
void book_ticket();
void cancel_ticket();
void update_seat_count(int bus_num, int change);
void exit_program();
void display_buses(FILE *fp);
int is_bus_number_unique(int bus_num);
void display_available_seats(int bus_num);
int is_seat_available(int bus_num, int seatNumber);
int get_integer_input(const char *prompt);

int main() {
    login();
    return 0;
}

void login() {
    system("cls");
    char user[20], pass[20];
    printf("Enter username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0';
    printf("Enter password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
        admin_menu();
    } else {
        client_menu();
    }
}

void display_buses(FILE *fp) {
    struct Bus bus;
    printf("Bus Number\tPickup\t\tDrop\t\tSeats\tTime\n");
    printf("------------------------------------------------------------\n");
    while (fscanf(fp, "%d %s %s %d %d", &bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        printf("%-10d\t%-10s\t%-10s\t%-5d\t%-5d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    }
}

void view_buses() {
    system("cls");
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        printf("No buses available!\n");
        exit_program();
    }
    display_buses(fp);
    fclose(fp);
}

void admin_menu() {
    int choice;
    system("cls");
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        printf("\t\tNo buses available!\n\n");
        printf("Enter 1 to add bus: ");
        scanf("%d", &choice);
        if (choice == 1)
            add_bus();
        else
            exit_program();
    } else {
        display_buses(fp);
        fclose(fp);
        printf("\n1. Add Bus\n2. Remove Bus\n3. View Passengers\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_bus(); break;
            case 2: remove_bus(); break;
            case 3: view_passengers(); break;
            default: exit_program();
        }
    }
}

int is_bus_number_unique(int bus_num) {
    FILE *fp = fopen("bus.txt", "r");
    if (!fp) {
        return 1;
    }
    struct Bus bus;
    while (fscanf(fp, "%d %s %s %d %d", &bus.num, bus.pick, bus.drop, &bus.seat, &bus.time1) != EOF) {
        if (bus.num == bus_num) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void add_bus() {
    system("cls");
    struct Bus bus;
    bus.num = get_integer_input("Enter bus number: ");
    if (!is_bus_number_unique(bus.num)) {
        printf("Error: Bus number %d already exists!\n", bus.num);
        printf("Press any key to return to dashboard !!");
        getch();
        admin_menu();
        return;
    }
    printf("Enter pickup location: ");
    scanf("%s", bus.pick);
    printf("Enter drop location: ");
    scanf("%s", bus.drop);
    bus.seat = get_integer_input("Enter no of seats: ");
    bus.time1 = get_integer_input("Enter bus departure time: ");
    FILE *fp = fopen("bus.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
        printf("Press any key to return to dashboard !!");
        getch();
        admin_menu();
    }
    fprintf(fp, "%d %s %s %d %d\n", bus.num, bus.pick, bus.drop, bus.seat, bus.time1);
    fclose(fp);
    printf("Bus added successfully!\n");
    printf("Press any key to return to dashboard !!");
    getch();
    admin_menu();
}

int get_integer_input(const char *prompt) {
    char input[20];
    int value;
    while (1) {
        printf("%s", prompt);
        scanf("%s", input);
        int valid = 1, i;
        for(i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            value = atoi(input);
            break;
        } else {
            printf("Invalid input! Please enter an integer.\n");
        }
    }
    return value;
}

void exit_program() {
    system("cls");
    printf("Enter any key to exit !!");
    getch();
    system("cls");
    printf("Exiting the system...\n");
}
