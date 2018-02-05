//
//  Bitmap.hpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#ifndef Bitmap_hpp
#define Bitmap_hpp

#include <vector>
#include <string>

#include "BitmapFileHeader.hpp"
#include "BitmapInfoHeader.hpp"
#include "Color.hpp"
#include "Pixel.hpp"

struct Bitmap {
    
    uint8_t bitsPerPixel;
    
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    
    std::vector<Color> colorPallet;
    
    std::vector<std::vector<Pixel>> pixels;
    
    Bitmap applyMask(const Bitmap & mask) const;
    
    Bitmap flipHorizontally() const;
    Bitmap flipVertically() const;
    Bitmap flipLeft() const;
    Bitmap flipRight() const;
    
    Bitmap crop(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;
    
};

#endif /* Bitmap_hpp */
