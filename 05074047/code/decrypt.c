#include <stdio.h>
#define KEY 5 // XOR decryption key

int main()
{
    char fname[50], ch;
    FILE *fps, *fpt;
    
    //Taking filename as input
    printf("Enter Filename: ");
    scanf("%s", fname);

    // Opening the encrypted file in read mode
    fps = fopen(fname, "r");
    if (fps == NULL)
        return 0;

    // Opening or creating a temporary file in write mode
    fpt = fopen("temp.txt", "w");
    if (fpt == NULL)
        return 0;

    ch = fgetc(fps);
    // Reading each character, applying XOR with the key, and writing to a temporary file
    while (ch != EOF)
    {
        ch = ch ^ KEY;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }

    // Closing both files after decryption
    fclose(fps);
    fclose(fpt);

    // Reopening files to overwrite the original file with decrypted data
    fps = fopen(fname, "w");
    if (fps == NULL)
        return 0;

    fpt = fopen("temp.txt", "r");
    if (fpt == NULL)
        return 0;

    ch = fgetc(fpt);
    // Copying decrypted content from the temporary file back to the original file
    while (ch != EOF)
    {
        fputc(ch, fps);
        ch = fgetc(fpt);
    }

    // Closing files after copying
    fclose(fps);
    fclose(fpt);

    printf("\n %s decrypted successfully.", fname);
    return 0;
}
