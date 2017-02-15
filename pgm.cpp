/* Read and Write a .pgm photo file.
 * pgm.cpp
 *
 *  Created on: Feb 7, 2011
 *  Author: Michael Fischer
 */
#include "tools.hpp"
#include "pgm.hpp"

// -----------------------------------------------------------------------------
// Realize a pgm data structure from a file
// -----------------------------------------------------------------------------
Pgm::Pgm( const char* fileName ) {

    //	int width, height, maxgrey;
	streampos filePos;
	char discard;				   // For reading a newline from the image file.
	long pgmsz;
	int n;

    ifstream pgmFile( fileName );
	if ( !pgmFile )
		fatal("Can't open photo '%s'", fileName);

    pgmFile.get( fileType, 3 );
    cout << fileType << endl;
    if (fileType[0] != 'P' || fileType[1] != '5')
		fatal("'%s' not a raw-format pgm file", fileName);

    pgmFile >> width >> height >> maxGrey;
    if (!pgmFile.good()) fatal("Corrupted pgm header '%s'", fileName);

	while  (pgmFile.get() != '\n');						// Skip to newline.
    filePos = pgmFile.tellg();
    if (filePos<0) fatal("Can't get file pointer after reading header");
	pgmFile.close();

	// Read pixels -------------------------------------------------------------
	pgmFile.open(fileName, ios_base::in | ios_base::binary); // open file in binary mode

    pgmFile.seekg(filePos);
	if (!pgmFile.good()) fatal("Can't restore file pointer");

	pgmsz = height * width;
	image = new pixel [pgmsz];

    pgmFile.read( image, pgmsz );
	if (!pgmFile.good()) say("Incomplete pgm file '%s'", fileName);

	// Check for eof -----------------------------------------------------------
    pgmFile.get();
	if (!pgmFile.eof()) fatal("File '%s' contains unread data",fileName);
	pgmFile.close();
}

// -----------------------------------------------------------------------------
// Write a pgm file
// -----------------------------------------------------------------------------
void Pgm::write(const char* fileName) {
	int n;
    char ch;

	// prevent accidental overwriting of output file
	ifstream testFile( fileName );
	if (testFile) {
		testFile.close();
		cout <<"File " <<filename
             <<" exists. Do you want to overwrite it? [y/N]: ";
        cin >> ch;
		if (tolower(ch) != 'y') fatal("Aborted");
	}

	// Okay to continue
    ofstream pgmFile( fileName );
    if (!pgmFile) fatal("Can't open photo file '%s' for writing", fileName);
    printHead( pgmFile );
    pgmFile.close();

	/* write pixels */
	long pgmsz = height * width;
    pgmFile.open( fileName, ios_base::out | ios_base::app | ios_base::binary );
    pgmFile.write(image, pgmsz);
    if (!pgmFile.good()) fatal("Error writing pgm file '%s'", fileName);
	pgmFile.close();
}

// -----------------------------------------------------------------------------
// Pixel bit-order reversal
// -----------------------------------------------------------------------------
void Pgm::reverse() {
	long photoSize = height * width;
	pixel* p = image;		  // Use to scan image, one pixel at a time.
	pixel* pend = image + photoSize;   // Mark end of image, for looping.

	while (p<pend) {
		pixel c = *p;
		pixel r = 0;
		// Pull bit off right end of pixel and push onto left end of result.
		for (int k=0; k<8; k++) {
			r = (r << 1) | (c & 1);
			c >>= 1;				// Shift pixel right to access the next bit.
		}
		*p++ = r;      // Replace original pixel with reversed one in the image.
	}
}

//------------------------------------------------------------------------------
void Pgm::extract( ostream& out ){
    long photoSize;
    long len;
    photoSize = width*height;

    pgmFile.open(fileName, ios_base::in | ios_base::binary);
    pgmFile.read(/*something*/, 16);
    if (!len <= (photoSize-16)/4) fatal("No embedded message.");
    //set pixel* to 17th pixel

    for(int k=0; k<len; ++k){
        /*something*/.extract4();
        /*write to file*/
    }
    cout << "Extraction complete." << endl;
    pgmFile.close();
}

//------------------------------------------------------------------------------
char Pgm::extract4(){
    char result = '\0';

    for (int k=0; k<4; ++k){
        result << 2;
        start & mask;
        mask | result;
        ++start;
    }

    return result;
}
