#include "tools.h"
#define MAXFILE 11000
#define MAXFILEREAD "10999"
#define MAXWORD 20
#define MAXWORDREAD "19"

void getInput( char inFileName[], char outFileName[], char searchWord[], char replaceWord[] );
void searchAndReplace( cstream outFile, cstream inFile, cstring file, char search[], char replace[] );

int main (void)
{
    char inFileName[MAXWORD];       // Stores input file name
    char outFileName[MAXWORD];      // Stores output file name
    char searchWord[MAXWORD];       // Word to be searched for
    char replaceWord[MAXWORD];      // Replacement word

    char fileArray[MAXFILE];        // Stores contents of entire file

    banner();
    getInput( inFileName, outFileName, searchWord, replaceWord ); // User input

     // Echo user inputs
    printf("\n Input File: %s\n", inFileName);
    printf("Output File: %s\n", outFileName);
    printf("Search for: %s\n", searchWord);
    printf("Replace with: %s\n", replaceWord);

    cstream inFile = fopen( inFileName, "r");
        if (!inFile) fatal ("Cannot open %s for input.", inFileName);

    cstream outFile = fopen( outFileName, "w");
        if (!outFile) fatal ("Cannot open %s for output.", outFileName);

    fgets( fileArray, "%" MAXFILEREAD "s", inFile );
    //printf("%s", fileArray);


    searchAndReplace( outFile, inFile, fileArray, searchWord, replaceWord ); // Perform search & replace function

    fclose( inFile );
    fclose( outFile );
    bye();
    return 0;
}

//===============================================================================================

void getInput( char inFileName[], char outFileName[], char searchWord[], char replaceWord[] )
{
    printf("Search and Replace Program\n");
    printf("-------------------------------\n");

    printf("\nPlease enter the input file name\n");
    scanf("%" MAXWORDREAD "[^\n]", inFileName);

    printf("\nPlease enter the output file name\n");
    scanf(" %" MAXWORDREAD "[^\n]", outFileName);

    printf("\nPlease enter the word you'd like to replace\n");
    scanf(" %" MAXWORDREAD "[^\n]", searchWord);

    printf("\nPlease enter replacement word\n");
    scanf(" %" MAXWORDREAD "[^\n]", replaceWord);
}

//===============================================================================================

void searchAndReplace( cstream outFile, cstream inFile, cstring file, char search[], char replace[] )
{
    cstring cursor = file;              // Set cursor to beginning
    int wordLength = strlen( search );  // Length of word to be searched for
    printf("\nSearching file...\n");
    int read;
    int charsRead = 0;
    bool found = false;

    while ((read = fgetc( inFile )) != EOF){
        //printf("1");
        if (read == search[0]){
            //printf("2");
            cursor = file[charsRead];       // Set cursor to last char read
            if (strncmp(search, wordLength, cursor)==0){    // Compare letters equal to length of word
                printf("Word found: %s\n", search);
                fprintf(outFile, "%s", replace);            // Print replacement word
                //read = read + strlen(replace);    // Set read to next char to be read?
                //found = false;
            }
        }
        else{
            fprintf(outFile, "%c", read);
            ++charsRead;
        }
    }

    printf("\nSearch complete.\n");
}
