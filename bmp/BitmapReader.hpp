//
//  BitmapReader.hpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#ifndef BitmapReader_hpp
#define BitmapReader_hpp

#include <iostream>
#include <fstream>

#include "Bitmap.hpp"

class BitmapReader {
    
    void parseColor1(Bitmap & bmp, unsigned char colors, int8_t bitsToStore);
    
    Color readColor();
    Color readColor32();
    
    std::ifstream file;
    void openFile(const std::string & filename);
    
    void readFileHeader(Bitmap & bmp);
    void readInfoHeader(Bitmap & bmp);
    void readColorPallet(Bitmap & bmp);
    void readBitmap(Bitmap & bmp);
    
public:
    
    Bitmap readFile(const std::string & filename);
    
};

#endif /* BitmapReader_hpp */
