//
//  main.cpp
//  bmp
//
//  Created by Filip Peterek on 29/01/2018.
//  Copyright © 2018 Filip Peterek. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>

#include "BitmapReader.hpp"
#include "BitmapWriter.hpp"

Bitmap readBitmap(const std::string & bitmapName) {
    
    BitmapReader reader;
    return reader.readFile(bitmapName);
    
}

void writeBitmap(const Bitmap & bitmap, const std::string & outputName) {
    
    BitmapWriter writer;
    writer.writeBmpToFile(bitmap, outputName);
    
}

std::string getInput(std::string text) {
    
    std::string input;
    
    std::cout << text;
    std::cin >> input;
    
    return input;
    
}

std::string getFileName() {
    return getInput("Soubor: ");
}

std::string getMaskName() {
    return getInput("Maska: ");
}

std::string getOutputName() {
    return getInput("Výstup: ");
}

std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> getSquareDimensions() {
    
    std::string strX = getInput("X: ");
    std::string strY = getInput("Y: ");
    std::string strWidth = getInput("Šířka: ");
    std::string strHeight = getInput("Výška: ");
    
    uint32_t x, y, height, width;
    
    try {
        
        x = std::stoi(strX);
        y = std::stoi(strY);
        width = std::stoi(strWidth);
        height = std::stoi(strHeight);
        
    } catch (const std::runtime_error & e) {
        
        std::cout << "Invalidní input. " << std::endl;
        getSquareDimensions();
        
    }
    
    return std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>(x, y, width, height);
    
}

void mask() {

    std::string filename = getFileName();
    std::string maskName = getMaskName();
    std::string output = getOutputName();

    
    Bitmap file = readBitmap(filename);
    Bitmap maskBmp = readBitmap(maskName);
    
    writeBitmap(file.applyMask(maskBmp), output);
    
}

void flipHorizontally() {
    
    std::string filename = getFileName();
    std::string output = getOutputName();
    
    Bitmap file = readBitmap(filename);
    
    writeBitmap(file.flipHorizontally(), output);
    
}

void flipVertically() {
    
    std::string filename = getFileName();
    std::string output = getOutputName();
    
    Bitmap file = readBitmap(filename);
    
    writeBitmap(file.flipVertically(), output);
    
}

void flipRight() {
    
    std::string filename = getFileName();
    std::string output = getOutputName();
    
    Bitmap file = readBitmap(filename);
    
    writeBitmap(file.flipRight(), output);
    
    
}

void flipLeft() {
    
    std::string filename = getFileName();
    std::string output = getOutputName();
    
    Bitmap file = readBitmap(filename);
    
    writeBitmap(file.flipLeft(), output);
    
    
}

void crop() {
    
    std::string filename = getFileName();
    std::string output = getOutputName();
    
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> square = getSquareDimensions();
    
    Bitmap file = readBitmap(filename);
    
    const Bitmap cropped = file.crop(std::get<0>(square), std::get<1>(square), std::get<2>(square), std::get<3>(square));
    
    writeBitmap(cropped, output);
    
}

int main(int argc, const char * argv[]) {
    
    std::unordered_map<char, std::function<void(void)>> functions = {
        { '0', mask             },
        { '1', flipHorizontally },
        { '2', flipVertically   },
        { '3', flipRight        },
        { '4', flipLeft         },
        { '5', crop             }
    };
    
    while (1) {
    
        std::cout << "[0] Maska [1] Přetočit horizontálně [2] Přetočit vertikálně "
                  << "[3] Otočit doprava [4] Otočit doleva [5] Ořezat [6] Konec" << std::endl;
        std::cout << ">>> ";
        std::string input;
        std::cin >> input;
        
        if (input[0] == '6') {
            break;
        }
        
        if (functions.count(input[0])) {
            functions[input[0]]();
        }
        
    }
    
}
