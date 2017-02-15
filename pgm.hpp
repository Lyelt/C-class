/* -----------------------------------------------------------------------------
 * pgm.h: Read and Write a .pgm image file.
 * Created on: Oct. 23, 2015
 * Author: Michael Fischer and Alice E. Fischer
 */
#pragma once
#include "tools.hpp"

// pgm structure ---------------------------------------------------------------
typedef char pixel;

class Pgm {
private:
	char fileType[3] = { '\0' }; // two magic bytes as a null-terminated string
	int width = 0;
	int height = 0;
	int maxGrey = 0;
	pixel* image = nullptr;
	pixel* start = 0;
	char extract4();
public:
    Pgm( const char* fileName );
    ~Pgm() { delete image; }

    void printHead( ostream& out ) const {
        out << fileType << "\n" << width << " " << height << "\n"
             << maxGrey << endl;
    }
    void write( const char* fileName );
    void reverse();
    void extract( ostream& out );
};
