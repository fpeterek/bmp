//
//  Bitmap.cpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include "Bitmap.hpp"

Bitmap Bitmap::applyMask(const Bitmap & mask) const {
    
    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    if (mask.infoHeader.biWidth != infoHeader.biWidth and
        mask.infoHeader.biHeight != infoHeader.biHeight) {
        
        throw std::runtime_error("Mask dimensions don't match image dimensions.");
        
    }
    
    Color white;
    white.r = white.g = white.b = 255;
    
    for (uint64_t row = 0; row < infoHeader.biHeight; ++row) {
        
        bmp.pixels.emplace_back();
        
        for (uint64_t column = 0; column < infoHeader.biWidth; ++column) {
            
            if (not mask.pixels[row][column].r) {
                bmp.pixels[row].emplace_back(pixels[row][column]);
            } else {
                bmp.pixels[row].emplace_back(white);
            }
        }
        
    }
    
    return bmp;
    
}

Bitmap Bitmap::flipHorizontally() const {
    
    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    for (auto & row : pixels) {
        
        bmp.pixels.emplace_back();
        
        for (int32_t column = infoHeader.biWidth - 1; column >= 0; --column) {
            
            bmp.pixels.back().emplace_back(row[column]);
            
        }
        
    }
    
    return bmp;
    
}

Bitmap Bitmap::flipVertically() const {

    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    for (int32_t row = infoHeader.biHeight - 1; row >= 0; --row) {
        
        bmp.pixels.emplace_back(pixels[row]);
        
    }
    
    return bmp;
    
}

Bitmap Bitmap::flipLeft() const {
    
    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    bmp.infoHeader.biHeight = infoHeader.biWidth;
    bmp.infoHeader.biWidth = infoHeader.biHeight;
    
    for (uint32_t i = 0; i < bmp.infoHeader.biHeight; ++i) {
        bmp.pixels.emplace_back();
    }
    
    for (uint32_t row = 0; row < bmp.infoHeader.biHeight; ++row) {
        
        for (uint32_t column = 0; column < bmp.infoHeader.biWidth; ++column) {
            bmp.pixels[row].emplace_back(pixels[column][row]);
        }
        
    }
    
    return bmp;
    
}

Bitmap Bitmap::flipRight() const {
    
    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    bmp.infoHeader.biHeight = infoHeader.biWidth;
    bmp.infoHeader.biWidth = infoHeader.biHeight;
    
    for (uint32_t i = 0; i < bmp.infoHeader.biHeight; ++i) {
        bmp.pixels.emplace_back();
    }
    
    for (uint32_t row = 0; row < bmp.infoHeader.biHeight; ++row) {
        
        for (int32_t column = bmp.infoHeader.biWidth - 1; column >= 0 ; --column) {
            bmp.pixels[row].emplace_back(pixels[column][row]);
        }
        
    }
    
    return bmp;
    
}

Bitmap Bitmap::crop(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const {
    
    Bitmap bmp;
    bmp.infoHeader = infoHeader;
    bmp.fileHeader = fileHeader;
    
    uint32_t endX = ((x + width)  >= infoHeader.biWidth)  ? (infoHeader.biWidth - 1)  : (x + width);
    uint32_t endY = ((y + height) >= infoHeader.biHeight) ? (infoHeader.biHeight - 1) : (y + height);
    
    bmp.infoHeader.biWidth = (x + width) > infoHeader.biWidth ? infoHeader.biWidth - x : width;
    bmp.infoHeader.biHeight = (y + height) > infoHeader.biHeight ? infoHeader.biHeight - y : height;
    bmp.infoHeader.biSizeImage = bmp.infoHeader.biWidth * bmp.infoHeader.biHeight * 3;
    bmp.fileHeader.bfSize = bmp.infoHeader.biSizeImage + 54;
    
    for (uint32_t row = y; row < endY; ++row) {
        
        bmp.pixels.emplace_back();
        
        for (uint32_t column = x; column < endX; ++column) {
            
            bmp.pixels.back().emplace_back(pixels[row][column]);
            
        }
        
    }
    
    return bmp;
    
}











