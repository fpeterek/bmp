//
//  main.cpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include <iostream>
#include <sstream>

#include "BitmapReader.hpp"
#include "BitmapWriter.hpp"

int main(int argc, const char * argv[]) {
    
    BitmapReader reader;
    Bitmap bmp = reader.readFile("lenna.bmp");
    Bitmap mask = reader.readFile("lenna_mask.bmp");
    
    Bitmap postTransformation = bmp.flipRight();
    
    
    BitmapWriter writer;
    writer.writeBmpToFile(postTransformation, "output.bmp");
    
    Bitmap bmp2 = reader.readFile("output.bmp");
    
}
