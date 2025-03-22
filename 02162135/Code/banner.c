#include <stdio.h>
#include "config.h"
#include "banner.h"
#include <windows.h>
#include "colors.h"

void printBanner() {
    setColor(10); // Bright Green
    printf("\n");
    printf("    +==========================================+\n");
    printf("    |              StudyBuddyyy 📚            |\n");
    printf("    |        Your Personal Study Companion    |\n");
    printf("    +==========================================+\n\n");
    setColor(7); // White
}