//
//  BitmapFileHeader.cpp
//  bmp
//
//  Created by Filip Peterek on 03/02/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include "BitmapFileHeader.hpp"

BitmapFileHeader & BitmapFileHeader::operator=(const BitmapFileHeader & orig) {
    
    bfType[0] = orig.bfType[0];
    bfType[1] = orig.bfType[1];
    
    bfSize = orig.bfSize;
    bfReserved1 = orig.bfReserved1;
    bfReserved2 = orig.bfReserved2;
    bfOffBits = orig.bfOffBits;
    
    return *this;
    
}
