//
//  BitmapReader.cpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include "BitmapReader.hpp"

void BitmapReader::openFile(const std::string & filename) {
    
    file.open(filename, std::ios::binary);
    
    if (not file) {
        throw std::runtime_error("Could not open file " + filename);
    }
    
}

void BitmapReader::readFileHeader(Bitmap & bmp) {
    
    unsigned char buffer[5];
    char * b = (char *)buffer;
    
    uint32_t * bit32 = (uint32_t *)buffer;
    uint16_t * bit16 = (uint16_t *)buffer;
    
    file >> bmp.fileHeader.bfType[0] >> bmp.fileHeader.bfType[1];
    
    file.read(b, 4);
    bmp.fileHeader.bfSize = *bit32;
    
    file.read(b, 2);
    bmp.fileHeader.bfReserved1 = *bit16;
    
    file.read(b, 2);
    bmp.fileHeader.bfReserved2 = *bit16;
    
    file.read(b, 4);
    bmp.fileHeader.bfOffBits = *bit32;
    
}

void BitmapReader::readInfoHeader(Bitmap & bmp) {
    
    unsigned char buffer[5];
    char * b = (char *)buffer;
    
    uint32_t * bit32 = (uint32_t *)buffer;
    uint16_t * bit16 = (uint16_t *)buffer;
    
    file.read(b, 4);
    bmp.infoHeader.biSize = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biWidth = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biHeight = *bit32;
    
    file.read(b, 2);
    bmp.infoHeader.biPlanes = *bit16;
    
    file.read(b, 2);
    bmp.infoHeader.biBitCount = *bit16;
    
    file.read(b, 4);
    bmp.infoHeader.biCompression = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biSizeImage = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biXPelsPerMeter = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biYPelsPerMeter = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biClrUsed = *bit32;
    
    file.read(b, 4);
    bmp.infoHeader.biClrImportant = *bit32;
    
}

void BitmapReader::parseColor1(Bitmap & bmp, unsigned char colors, int8_t bitsToStore) {
    
    for (int8_t i = 7; i >= 0; --i) {
        
        if (bitsToStore) {
            bmp.pixels[0].emplace_back(bmp.colorPallet[(colors  >> i) & 1]);
            --bitsToStore;
        }
    }
    
}

Color BitmapReader::readColor() {
    
    Color color;
    
    char bgr[3];
    
    file.read(bgr, 3);
    
    color.b = bgr[0];
    color.g = bgr[1];
    color.r = bgr[2];

    return color;
    
}

Color BitmapReader::readColor32() {
    
    Color color;
    
    char bgro[4];
    
    file.read(bgro, 4);
    
    color.b = bgro[0];
    color.g = bgro[1];
    color.r = bgro[2];
    color.o = bgro[3];
    
    return color;
    
}

void BitmapReader::readColorPallet(Bitmap & bmp) {
    
    for (int32_t i = 0; i < bmp.infoHeader.biClrUsed; ++i) {
        
        bmp.colorPallet.emplace_back(readColor32());
        
    }
    
}

void BitmapReader::readBitmap(Bitmap & bmp) {
    
    int64_t bitsLeft;
    
    for (int64_t rows = 0; rows < bmp.infoHeader.biHeight; ++rows) {
        
        bmp.pixels.insert(bmp.pixels.begin(), std::vector<Pixel>());
        bitsLeft = bmp.infoHeader.biWidth;
        
        for (int64_t column = 0; column < bmp.infoHeader.biWidth; ++column) {
            
            if (bmp.infoHeader.biBitCount == 1) {
                unsigned char byte[1];
                file.read((char *)byte, 1);
                parseColor1(bmp, *byte, bitsLeft > 8 ? 8 : bitsLeft);
                column += 7;
                bitsLeft -= 8;
            }
            else if (bmp.infoHeader.biBitCount == 8) {
                unsigned char colorIndex[1];
                file.read((char *)colorIndex, 1);
                bmp.pixels[0].emplace_back(bmp.colorPallet[*colorIndex]);
            }
            else {
                bmp.pixels[0].emplace_back(readColor());
            }
            
        }
        /* Right padding with zeroes */
        if (bmp.infoHeader.biBitCount == 1) {
            const uint64_t bytes = bmp.infoHeader.biWidth / 8 + ((bmp.infoHeader.biWidth % 8) > 0);
            char c[4];
            bytes % 4 and file.read(c, 4 - (bytes % 4));
        }
        else if (bmp.infoHeader.biBitCount == 8) {
            char c[4];
            bmp.infoHeader.biWidth % 4 and file.read(c, 4 - (bmp.infoHeader.biWidth % 4));
        }
        else if (bmp.infoHeader.biBitCount == 24) {
            const uint64_t bytes = (bmp.infoHeader.biWidth * 3);
            char c[4];
            bytes % 4 and file.read(c, 4 - (bytes % 4));
        }
        
    }
    
    if (bmp.infoHeader.biHeight != bmp.pixels.size()) {
        throw std::runtime_error("Error reading bitmap.");
    }
    
    if (bmp.infoHeader.biWidth != bmp.pixels.back().size()) {
        throw std::runtime_error("Error reading bitmap.");
    }
    
}

Bitmap BitmapReader::readFile(const std::string & filename) {
    
    Bitmap bmp;
    openFile(filename);
    
    readFileHeader(bmp);
    readInfoHeader(bmp);
    readColorPallet(bmp);
    file.seekg(bmp.fileHeader.bfOffBits);
    
    readBitmap(bmp);
    
    file.close();
    
    return bmp;
    
}











