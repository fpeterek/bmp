//
//  BitmapFileHeader.hpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#ifndef BitmapFileHeader_hpp
#define BitmapFileHeader_hpp

#include <cstdint>

struct BitmapFileHeader {
    
    int8_t bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
    
    BitmapFileHeader & operator=(const BitmapFileHeader & orig);
    
};

#endif /* BitmapFileHeader_hpp */
