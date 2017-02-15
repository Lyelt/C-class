#include "tools.hpp"
#define WINNERSFILE "sorted.txt"
#define PRIZEFILE "prizes.txt"
#define MAXPRIZE 10
#define MAXNUMBERS 50

void getInput(istream& pfile, istream& wfile, string prizes[], int nums[]);
int binarySearch(int numArray[], int first, int last, int key);
int awardPrize(int prizesLeft, string prizes[]);

//------------------------------------------------------------------------------
int main() {

    string prizeArray[MAXPRIZE];    // Store the available prizes
    int numArray[MAXNUMBERS];       // Store the winning numbers
    int userID;                     // User-entered ID
    int numOfPrizes = MAXPRIZE-1;   // Used for subscript in prize array

    banner();
    cout << "Hello, welcome to this week's prize giveaway!" << endl;
    cout << "Today just might be your lucky day, so jump right in" << endl;
    cout << "and let's see if you won anything!\n" << endl;

    ifstream prizeFile ( PRIZEFILE );
        if (!prizeFile) fatal ("Could not open %s for input.", PRIZEFILE);
    ifstream winnersFile ( WINNERSFILE );
        if (!winnersFile) fatal ("Could not open %s for input.", WINNERSFILE);

    //-------------------------------------------------------------------------
    getInput(prizeFile, winnersFile, prizeArray, numArray);
    // As long as there are prizes left, continue
    while (numOfPrizes > 0){
        // Prompt user for ID
        cout << "Please enter the last 3 digits of your ID number." << endl;
        cin >> userID;
            // Check for validity
            if (userID < 0 || userID > 999) fatal("Invalid ID entered.");

        // Search for the ID in the array of winners
        if (binarySearch(numArray, 0, MAXNUMBERS, userID) >= 0) {
            cout << "We have a match!" << endl;
            // If found, award a prize, store num of remaining prizes
            numOfPrizes = awardPrize(numOfPrizes, prizeArray);
        }
        else {
            cout << "Sorry, your number is not a winner this week!" << endl;
            cout << "---------------------------------------------------\n"
                << endl;
        }
    }
    //--------------------------------------------------------------------------

    cout << "Thanks for entering our holiday giveaway!" << endl;
    cout << "Be sure to come back next week for exciting prizes!" << endl;
    winnersFile.close();
    prizeFile.close();
    bye();
    return 0;
}

//------------------------------------------------------------------------------
void getInput(istream& pfile, istream& wfile, string prizes[], int nums[]) {

// Read in the prizes and winning numbers
    for (int k=0; k<MAXPRIZE; ++k){
        getline(pfile, prizes[k], '\n');
    }

    for (int k=0; k<MAXNUMBERS; ++k){
        wfile >> nums[k];
    }

}

//------------------------------------------------------------------------------
//-Binary Search Function-------------------------------------------------------
int binarySearch(int numArray[], int first, int last, int key) {
    if (first <= last){
        // Find the mid point
        int mid = (first + last) /2;

        if (key == numArray[mid]) return mid; // Found what we're looking for
        else if (key < numArray[mid])
            // If the key was smaller than what we found...
            // Do a recursive call for first half of the array
            return binarySearch(numArray, first, mid-1, key);
        else
            // Otherwise, recursive call for second half of the array
            return binarySearch(numArray, mid+1, last, key);
    }
    return -1; // Indicate that the key was not found
}

//------------------------------------------------------------------------------
//-Award Prize Function---------------------------------------------------------
int awardPrize(int prizesLeft, string prizes[]){
    int prizeNum = rand() % prizesLeft;     // Select a random prize

    cout << "Congratulations! You won a(n) " << prizes[prizeNum]
            << "!" << endl;
    cout << "---------------------------------------------------\n"
        << endl;

    // Swap selected prize with last unused prize
    swap(prizes[prizeNum], prizes[prizesLeft]);

    // Decrement number of prizes left
    return --prizesLeft;
}
