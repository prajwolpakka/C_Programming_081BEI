#include <stdio.h>
#include "mindmap_generator.h"
#include <windows.h>

void create_mindmap(char *username) {
    
    char topic[200];
    printf("\nEnter topic for mind map: ");
    scanf(" %199[^\n]", topic);
   
    printf("\nGenerating Mind Map for '%s'...\n", topic);
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" mindmap", topic);
    system(cmd);

}
