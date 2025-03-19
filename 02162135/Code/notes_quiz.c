#include <stdio.h>
#include "notes_quiz.h"
#include "utils.h"
#include <windows.h>
#include "banner.h"

void generate_content() {
    
    char topic[100];
    char content_type[20];
    
    clearScreen();
    printBanner();
    
    setColor(14); // Yellow
    printf("\n    ╔═════════════ Generate Content ════════════╗\n");
    printf("    ║                                           ║\n");
    printf("    ║  Enter a topic to learn about:            ║\n");
    printf("    ╚═══════════════════════════════════════════╝\n");
    setColor(7); // White
    
    printf("\n    Topic: ");
    scanf(" %99[^\n]", topic);
    
    clearScreen();
    printBanner();
    
    setColor(14); // Yellow
    printf("\n    ╔════════════ Select Content Type ══════════╗\n");
    printf("    ║                                           ║\n");
    printf("    ║  1. Study Notes                           ║\n");
    printf("    ║  2. Quiz                                  ║\n");
    printf("    ║                                           ║\n");
    printf("    ╚═══════════════════════════════════════════╝\n");
    setColor(7); // White
    
    printf("\n    Choice (1-2): ");
    int choice;
    if(scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while(getchar() != '\n');
        setColor(12); // Red
        printf("\n    Invalid choice! Returning to main menu.\n");
        setColor(7);
        Sleep(1500);
        return;
    }
    
    strcpy(content_type, choice == 1 ? "notes" : "quiz");
    
    setColor(11); // Cyan
    printf("\n    Generating %s for '%s'...\n", 
           choice == 1 ? "study notes" : "quiz", 
           topic);
    setColor(7);
    
    // Call Python script
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" %s", topic, content_type);
    
    system(cmd);

}