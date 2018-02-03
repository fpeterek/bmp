//
//  BitmapWriter.cpp
//  bmp
//
//  Created by Filip Peterek on 30/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include "BitmapWriter.hpp"


void BitmapWriter::openFile(const std::string & filename) {
    
    stream.open(filename, std::ios::binary);
    
    if (not stream) {
        throw std::runtime_error("Error opening file " + filename);
    }
    
}

void BitmapWriter::writeFileHeader(const Bitmap & bmp) {
    
    stream << "BM";
    
    char buffer[4];
    buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
    
    uint32_t total_size = bmp.infoHeader.biWidth * bmp.infoHeader.biHeight * 3 + 54;
    buffer[0] = total_size & 255;
    buffer[1] = ((total_size & (255 << 8)) >> 8);
    buffer[2] = ((total_size & (255 << 16)) >> 16);
    buffer[3] = ((total_size & (255 << 24)) >> 24);
    stream.write(buffer, 4);
    
    buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
    stream.write(buffer, 2);
    
    buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
    stream.write(buffer, 2);
    
    buffer[0] = 54;
    buffer[1] = buffer[2] = buffer[3] = 0;
    stream.write(buffer, 4);
    
}

void BitmapWriter::writeInfoHeader(const Bitmap & bmp) {
    
    char buffer[4];
    buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
    
    
    buffer[0] = 40;
    stream.write(buffer, 4);
    
    buffer[0] = bmp.infoHeader.biWidth & 255;
    buffer[1] = ((bmp.infoHeader.biWidth & (255 << 8)) >> 8);
    buffer[2] = ((bmp.infoHeader.biWidth & (255 << 16)) >> 16);
    buffer[3] = ((bmp.infoHeader.biWidth & (255 << 24)) >> 24);
    stream.write(buffer, 4);
    
    buffer[0] = bmp.infoHeader.biHeight & 255;
    buffer[1] = ((bmp.infoHeader.biHeight & (255 << 8)) >> 8);
    buffer[2] = ((bmp.infoHeader.biHeight & (255 << 16)) >> 16);
    buffer[3] = ((bmp.infoHeader.biHeight & (255 << 24)) >> 24);
    stream.write(buffer, 4);
    
    buffer[0] = 1;
    buffer[1] = 0;
    stream.write(buffer, 2);
    
    buffer[0] = 24;
    buffer[2] = 0;
    buffer[3] = 0;
    stream.write(buffer, 2);
    
    buffer[0] = bmp.infoHeader.biCompression & 255;
    stream.write(buffer, 4);
    
    
    uint32_t size = bmp.infoHeader.biWidth * bmp.infoHeader.biHeight * 3;
    buffer[0] = size & 255;
    buffer[1] = ((size & (255 << 8)) >> 8);
    buffer[2] = ((size & (255 << 16)) >> 16);
    buffer[3] = ((size & (255 << 24)) >> 24);
    stream.write(buffer, 4);
    
    buffer[0] = buffer[1] = buffer[2] = buffer[3] = 0;
    
    stream.write(buffer, 4);
    stream.write(buffer, 4);
    stream.write(buffer, 4);
    stream.write(buffer, 4);
    
}

void BitmapWriter::writeBitmap(const Bitmap & bmp) {
    
    for (int64_t i = bmp.pixels.size() - 1; i >= 0; --i) {
        
        const std::vector<Pixel> & row = bmp.pixels[i];
        
        for (auto & pixel : row) {
            
            char b[1];
            b[0] = pixel.b;
            
            char g[1];
            g[0] = pixel.g;
            
            char r[1];
            r[0] = pixel.r;
            
            // char o[1];
            // o[0] = pixel.o;
            
            stream.write(b, 1);
            stream.write(g, 1);
            stream.write(r, 1);
            
        }
        
        /* Right padding with zeroes */
        
        const uint64_t bytes = (bmp.infoHeader.biWidth * 3);
        char c[4];
        c[0] = c[1] = c[2] = c[3] = 0;
        bytes % 4 and stream.write(c, 4 - (bytes % 4));
        
    }
    
}

void BitmapWriter::writeBmpToFile(const Bitmap & bmp, const std::string & filename) {
    
    openFile(filename);
    writeFileHeader(bmp);
    writeInfoHeader(bmp);
    
    writeBitmap(bmp);
    
    stream.close();
    
}
