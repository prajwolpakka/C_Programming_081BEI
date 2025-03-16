#include <stdio.h>
#include "youtube_summarizer.h"
#include <windows.h>



void summarize_youtube_video(char *username) {
    
    char url[200];
    printf("\nEnter YouTube video URL: ");
    scanf(" %199[^\n]", url);
   
    printf("\nGenerating Summary for Youtube Video'%s'...\n", url);
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "python api_handler.py \"%s\" youtube_summary", url);
    system(cmd);
}
