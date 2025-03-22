#include <stdio.h>
#include <windows.h>
#include "config.h"
#include "auth.h"
#include "youtube_summarizer.h"
#include "mindmap_generator.h"
#include "notes_quiz.h"
#include "banner.h"
#include "colors.h"
#include "utils.h"

char username[50];

void clearScreen() {
    system("cls");
}



void printAuthMenu() {
    setColor(14); // Yellow
        printf("\n    ╔════════════ Authentication ═════════════╗\n");
        printf("    ║                                         ║\n");
        printf("    ║  1. Login                               ║\n");
        printf("    ║  2. Register                            ║\n");
        printf("    ║  3. Exit                                ║\n");
        printf("    ║                                         ║\n");
        printf("    ╚═════════════════════════════════════════╝\n");
    setColor(7); // White
}
void printMenu(char *username) {
    clearScreen();
    printBanner();
    setColor(11); // Cyan
    printf("    Logged in as: %s\n", username);
    setColor(14); // Yellow
    printf("\n    ╔════════════════ MAIN MENU ═══════════════╗\n");
    printf("    ║                                          ║\n");
    printf("    ║  1. Generate Learning Content            ║\n");
    printf("    ║  2. Summarize YouTube Video              ║\n");
    printf("    ║  3. Create Mind Maps                     ║\n");
    printf("    ║  4. Exit                                 ║\n");
    printf("    ║                                          ║\n");
    printf("    ╚══════════════════════════════════════════╝\n");
    setColor(7); // White
    //printf("\n    Choose an option (1-4): ");
}


int main() {
    system("chcp 65001");
    int logged_in = 0;
    clearScreen();
    printBanner();

    while (!logged_in) {
        setColor(14); // Yellow
        printAuthMenu();
        setColor(7); // White

        printf("\n    Choose an option (1-3): ");
        int choice;
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear input buffer
            setColor(12); // Red
            printf("\n    Invalid input! Please enter a number.\n");
            setColor(7);
            Sleep(1500);
            clearScreen();
            printBanner();
            continue;
        }

        switch(choice) {
            case 1:
                if(login_user(username)) {
                    logged_in = 1;
                    setColor(10); // Green
                    printf("\n    Login successful!\n");
                    setColor(7);
                }
                break;
            case 2:
                if(register_user()) {
                    setColor(10);
                    printf("\n    Please login with your new account.\n");
                    setColor(7);
                }
                break;
            case 3:
                setColor(10);
                printf("\n    Thank you for using Learning Assistant!\n\n");
                setColor(7);
                exit(0);
            default:
                setColor(12);
                printf("\n    Invalid choice! Please select 1-3.\n");
                setColor(7);
        }
        Sleep(500);
        clearScreen();
        printBanner();
    }

    int running = 1;
    while (running) {
        clearScreen();
        printBanner();
        setColor(11); // Cyan
        printf("    Logged in as: %s\n", username);
        setColor(7);
        printMenu(username);

        int choice;
        printf("    Choose an option (1-4): ");
        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            setColor(12);
            printf("\n    Invalid input! Please enter a number.\n");
            setColor(7);
            Sleep(500);
            continue;
        }

        switch (choice) {
            case 1:
                generate_content();
                break;
            case 2:
                summarize_youtube_video(username);
                break;
            case 3:
                create_mindmap(username);
                break;
            case 4:
                setColor(10);
                printf("\n    Thank you for using Learning Assistant!\n");
                printf("    Goodbye %s!\n\n", username);
                setColor(7);
                running = 0;
                break;
            default:
                setColor(12);
                printf("\n    Invalid choice! Please select 1-4.\n");
                setColor(7);
                Sleep(500);
        }

        if (running && choice >= 1 && choice <= 3) {
            printf("\n    Press Enter to continue...");
            while(getchar() != '\n');
            getchar();
        }
    }
    return 0;
}
