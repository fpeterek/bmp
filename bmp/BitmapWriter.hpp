//
//  BitmapWriter.hpp
//  bmp
//
//  Created by Filip Peterek on 30/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#ifndef BitmapWriter_hpp
#define BitmapWriter_hpp

#include <iostream>
#include <fstream>

#include "Bitmap.hpp"

class BitmapWriter {
    
    std::ofstream stream;
    
    void openFile(const std::string & filename);
    
    void writeFileHeader(const Bitmap & bmp);
    void writeInfoHeader(const Bitmap & bmp);
    void writeBitmap(const Bitmap & bmp);

    
public:
    
    void writeBmpToFile(const Bitmap & bmp, const std::string & filename);
    
};

#endif /* BitmapWriter_hpp */
