#include "tools.hpp"

void getInput( string *in, string *out, string *srch, string *rpl);
void searchAndReplace(istream& inFile, ostream& outFile, string searchWord, string replaceWord );

int main()
{
    string inFileName;
    string outFileName;
    string searchWord;
    string replaceWord;
    string s;

    banner();
    getInput(&inFileName, &outFileName, &searchWord, &replaceWord);

    cout << "Input File: " << inFileName << endl;
    cout << "Output File: " << outFileName << endl;
    cout << "Search Word: " << searchWord << endl;
    cout << "Replace Word: " << replaceWord << endl;

    ifstream inFile( inFileName.c_str() );
        if (!inFile) fatal("Cannot open %s for input.", inFileName.c_str() );
    ofstream outFile( outFileName.c_str() );
        if (!outFile) fatal("Cannot open %s for output.", outFileName.c_str() );

    searchAndReplace( inFile, outFile, searchWord, replaceWord );

    inFile.close();
    outFile.close();
    bye();
    return 0;
}

//--------------------------------------------------------------------------
void getInput( string *in, string *out, string *srch, string *rpl){

    cout << "Enter the name of the input file.\n";
    getline(cin, *in);

    cout << "Enter the name of the output file.\n";
    getline(cin, *out);

    cout << "Enter the word to search for.\n";
    getline(cin, *srch);

    cout << "Enter the word to replace it with.\n";
    getline(cin, *rpl);
}

//-----------------------------------------------------------------------------
void searchAndReplace( istream& inFile, ostream& outFile, string searchWord, string replaceWord ){

    string line;
    size_t wordlen = replaceWord.length();
    int cursor = 0;
    getline(inFile, line, '\0');

    for(;;){
        size_t pos = line.find(replaceWord, cursor);
        if (pos == string::npos) {
            cout << "No more words found." << endl;
            break;
        }

        char* head = &line[cursor];
        char* repl = &line[pos];

        outFile << head << repl;

        cursor = pos + wordlen;
    }
}
