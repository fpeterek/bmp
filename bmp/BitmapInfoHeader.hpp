//
//  BitmapInfoHeader.hpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#ifndef BitmapInfoHeader_hpp
#define BitmapInfoHeader_hpp

#include <cstdint>

struct BitmapInfoHeader {
  
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    
    uint16_t biPlanes;
    uint16_t biBitCount;
    
    uint32_t biCompression;
    uint32_t biSizeImage;
    
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    
    uint32_t biClrUsed;
    uint32_t biClrImportant;
    
};

#endif /* BitmapInfoHeader_hpp */
