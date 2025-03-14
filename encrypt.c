#include <stdio.h>
#define KEY 5 // XOR encryption key
int main()
{
    char fname[50], ch;
    FILE *fps, *fpt;
    // asking the user for file
    printf("Enter Filename: ");
    scanf("%s", fname);
    // opening the original file in read mode
    fps = fopen(fname, "r");
    if (fps == NULL)
        return 0;
    // opening or creating temporary file in write mode
    fpt = fopen("temp.txt", "w");
    if (fpt == NULL)
        return 0;
    ch = fgetc(fps);
    // reading each character,implementing XOR with a key and writing to temporary file
    while (ch != EOF)
    {
        ch = ch ^ KEY;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }
    // closing both files after encryption
    fclose(fps);
    fclose(fpt);
    // Reopening the files to overwrite the original file with encrypted data
    fps = fopen(fname, "w");
    if (fps == NULL)
        return 0;
    fpt = fopen("temp.txt", "r");
    if (fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    // Copying encrypted content from temporary file back to original file
    while (ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }
    // closing file after copying
    fclose(fps);
    fclose(fpt);
    printf("\nFile %s Encrypted Successfully!", fname);
    return 0;
}
// program written to encrypt file using XOR key
