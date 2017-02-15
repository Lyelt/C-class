#include "tools.hpp"
#define MAX 50
#define OUTFILE "sorted.txt"

void mySort (int lottery[], int length);
void print (ostream& out, int lottery[], int length);

//------------------------------------------------------------------------------
int main( void )
{
    banner();
    int winningNumbers[MAX];
    int length = MAX;

    ofstream sortFile( OUTFILE );
        if (!sortFile) fatal ("Could not open %s for output.", OUTFILE);

    srand((unsigned) time(NULL));
    for (int k=0; k<MAX; ++k){
        winningNumbers[k] = rand() % 1000; // Random number 0-999
    }

    mySort(winningNumbers, length); // Sort function
    print(sortFile, winningNumbers, length);

    sortFile.close();
    bye();
    return 0;
}

//------------------------------------------------------------------------------
//-Selection sort function------------------------------------------------------
//------------------------------------------------------------------------------
void mySort (int lottery[], int length){
    int minLoc;     // Current minimum value in array

    for (int k=0; k<length; ++k){
        minLoc = k; // Assume min is first element

        for (int j=k+1; j<length+1; ++j){
            if (lottery[j] < lottery[minLoc]){ // Compare to the next element
                minLoc = j; // If it is smaller, set minimum to next element
            }
        }
        swap (lottery[k], lottery[minLoc]); // Swap the two
    }
    cout << "Array Sorted" << endl;
}

//------------------------------------------------------------------------------
void print (ostream& out, int lottery[], int length){
    cout << "Printing..." << endl;

    for (int k=0; k<length; ++k){
    // Print the sorted array with leading zeros
        cout << setfill('0') << setw(3) << lottery[k] << endl;
        out << setfill('0') << setw(3) << lottery[k] << endl;
    }
}
