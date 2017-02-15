#include "tools.hpp"
#include "pgm.hpp"


int main(){

    banner();
    string outFileName, inFileName;

    cout << "Enter a .pgm input file name:\n";
    cin >> inFileName;
    cout << "Enter the output file name:\n";
    cin >> outFileName;

    // Pgm object with input filename as parameter
    Pgm pic = new Pgm(inFileName);

    ofstream outFile(outFileName);
        if (!outFile) fatal ("Could not open %s for output", outFileName);
    outFile.close();

    //---Open in binary mode
    outFile.open(outFileName, ios_base::out | ios_base::binary);
    pic.extract(outFile);

    //inFile.close();
    //outFile.close();
    bye();
    return 0;
}

