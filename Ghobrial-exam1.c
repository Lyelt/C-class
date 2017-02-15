#include "tools.h"

#define inFileName "exam1.txt"
#define outFileName "output1.txt"
#define MAXFILE 4000
#define MAXFILEREAD "3999"
#define MAXWORDS 100

void searchFile( cstream outFile, char search[], char found[][5], int length );

int main(void)
{
    banner();

    char fileArray[MAXFILE];
    char fourLetters[MAXWORDS][5];
    int fileLength;

    cstream inFile = fopen( inFileName, "r");
        if (!inFile) fatal ("Cannot open %s for input.", inFileName);

    cstream outFile = fopen( outFileName, "w");
        if (!outFile) fatal ("Cannot open %s for output.", outFileName);

    fscanf( inFile, "%" MAXFILEREAD "[^#]#", fileArray );
    fileLength = strlen(fileArray);

    //printf("\n%d", fileLength);

    searchFile( outFile, fileArray, fourLetters, fileLength );

    fclose( inFile );
    fclose( outFile );
    bye();
    return 0;
}


// -----------------------------------------------------------------

void searchFile( cstream outFile, char search[], char found[][5], int length ){

    cstring cursor = search;    // Index of first unprocessed char
    cstring rSpace;             // Right space for walking through the file
    char wordArr[5];            // Array to store each word
    int count = 0;              // Counting variable for "found" array
    int counter = 0;            // Stores position in file
    bool wordFound = false;     // True if 4-letter word found

    printf("Searching file: %s\n", inFileName);

    for(;;){
        rSpace = strchr(cursor, ' '); // Search for next space
        char* word = rSpace+1;

        int k=0;

        for(;;){
            if (!(isalpha(word[counter]))){
                ++counter;
                break;
            }
            else{
                ++k;
                ++counter;
            }
        }

        if (k == 4){
            printf("Word number %d found!\n", count+1);
            for (int m=0; m<4; ++m){
                wordArr[m] = word[counter];
                //printf("%c", word[m]);
                wordFound = true;
            }
        }
        /*else {
            printf("%d\n", k);
        }*/

        if (wordFound){
            for (int m=0; m<5; ++m){
                found[count][m] = wordArr[m];
            }
            ++count;
            wordFound = false;
            //printf("Word added: %s\n", found[count]);
        }

        cursor = rSpace-1;    // Set cursor to end of last word

        if (counter >= length) break;

    }

    printf("Printing output in: %s\n", outFileName);
    for (int k=0; k<count; ++k){
        fprintf(outFile, "%s\n", found[count]);
    }
}
