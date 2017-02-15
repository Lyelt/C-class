/*
 * p1.c
 *
 *  Created on: Sep 4, 2015
 *      Author: Nicholas Ghobrial
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 80

void banner();
void bye();
void doDance( char arr[], char d, int s );

int main (void) {
	char danceArray[1000];
	char danceType;
	int length, arrayNumber;

    banner();
	printf("\nPlease enter an integer 2-4 followed by a string.\n");
	printf("Enter the # key to finish.\n");

    scanf("%[^#] ", danceArray);            // Read all of the user's input, store it in an array

    /*if (danceArray[0] == '2' || danceArray[0] == '3' || danceArray[0] == '4'){
        danceType = danceArray[0];
        length = strlen(danceArray);
        doDance(danceArray, danceType, length);
    }
    else {
        printf("Error: Enter 2, 3, or 4 as your dance type.\n");
        scanf("%[^#]", danceArray);
    }*/

	bye();
	return 0;
}


void banner (){
	printf("Program 1 - Dancing Words\n");
	printf("Nicholas Ghobrial\n");
}

void doDance(char arr[], char d, int s){
    char afterDance[s];
    printf("\nDance Chosen: %c\n", d);

    for (int n=1; n<s; ++n){
        afterDance[n] = arr[n];
    }

    for (int k=1; k<s; ){
        switch (d){
            case '2': afterDance[k] = toupper(afterDance[k]); k+=2;
            case '3': afterDance[k] = toupper(afterDance[k]); k+=3;
            case '4': afterDance[k] = toupper(afterDance[k]); k+=4;
        }
    }

    for (int j=1; j<s; ++j){
        printf("%c", arr[j]);
    }
        printf("\n");

    for (int m=1; m<s; ++m){
        printf("%c", afterDance[m]);
    }
        printf("\n");

}

void bye (){
    printf("\nProgram Ran Successfully\n");
	printf("Goodbye!");
}
