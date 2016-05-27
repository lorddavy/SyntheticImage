#include "bitmap.h"

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <algorithm>
#include <string>

BitMap::BitMap()
{

}

int BitMap::read(Vector3D** &dataOut, size_t &widthOut, size_t &heightOut, std::string &fileName)
{
    std::ifstream inputFile;
    inputFile.open(fileName.c_str(), std::ios::binary | std::ios::in);

    if(inputFile.is_open())
    {
        std::cout << "Reading BMP file \"" << fileName << "\"" << std::endl;

        // start off with four pointers
        unsigned char *dataBuffer[2] = {nullptr, nullptr};     // Header buffers
        unsigned char *pixels = nullptr;                       // Pixels
        bmp24_file_header* bmpFileHeader = nullptr;            // Header
        bmp24_info_header* bmpInfoHeader   = nullptr;          // Info

        // Allocate byte memory that will hold the two headers
        dataBuffer[0] = new unsigned char[14];
        dataBuffer[1] = new unsigned char[40];

        // Get the values with the data buffers
        inputFile.read((char*)dataBuffer[0], 14);
        inputFile.read((char*)dataBuffer[1], 40);

        // Construct the values from the buffers
        bmpFileHeader = (bmp24_file_header*) dataBuffer[0];
        bmpInfoHeader   = (bmp24_info_header*) dataBuffer[1];

        // Check if the file is an actual BMP file
        if(bmpFileHeader->magic1 != (unsigned char)0x4D42)
        {
            std::cout << "File \"" << fileName << "\" isn't a bitmap file\n";
            return 2;
        }

        // Allocate pixel memory
        pixels = new unsigned char[bmpInfoHeader->size_image];

        // Go to where image data starts, then read in image data
        std::cout << "Jumping " << 54 << " bits on the file" << std::endl;
        inputFile.seekg(54);
        std::cout << "Reading " << bmpInfoHeader->size_image << " bytes of pixels" << std::endl;
        inputFile.read((char *)pixels, bmpInfoHeader->size_image);

        // Allocate memory for the image matrix
        heightOut = (size_t)bmpInfoHeader->height;
        widthOut  = (size_t)bmpInfoHeader->width;
        dataOut = new Vector3D*[heightOut];
        for( size_t i=0; i<heightOut; i++)
        {
            dataOut[i] = new Vector3D[widthOut];
        }

        //int channels = bmpFileHeader->size;
        int extra_bytes = (4 - (bmpInfoHeader->width * 3) % 4) % 4;
        //void* padd = (void*)malloc(extra_bytes);

        // Store the result in the input Buffer
        for( size_t i=0; i<heightOut; i++)
        {
            for(size_t j=0; j<widthOut; j++)
            {
                Vector3D pixelValue;
                //if(bmpFileHeader->size == 3)
                //{
                    size_t index = i*(widthOut*3+extra_bytes) + j*3;
                    int r, g, b;

                    //b = (int)pixels[index];
                    b = (int)pixels[index];
                    g = (int)pixels[index+1];
                    r = (int)pixels[index+2];

                    pixelValue = Vector3D(r, g, b)/255.0;
                //}
                //else
                //{
                //    size_t index = i*(widthOut+extra_bytes) + j;
                //    pixelValue = Vector3D((int)pixels[index])/255.0;
                //}
                dataOut[heightOut-1-i][j] = pixelValue;
            }
        }

        // Delete the two buffers.
        delete[] dataBuffer[0];
        delete[] dataBuffer[1];
        delete[] pixels;

        // return success
        return 0;
    }
    else
    {
        // Problem opening file
        std::cout << "Problem at BitMap::read() : Could not open file \""
                  << fileName << "\"" << std::endl;

        return 1;
    }
}

int BitMap::save(Vector3D** &data, const size_t &width, const size_t &height)
{
    // Create file header
    bmp24_file_header fileHeader;

    // Create info header
    bmp24_info_header infoHeader(width, height);

    std::ofstream outputFile;
    outputFile.open("./output.bmp", std::ios::binary | std::ios::out);

    if(outputFile.is_open())
    {
        // Write the file header
        outputFile.write(fileHeader.toCharBlock(), 14);

        // Write the info header
        outputFile.write(infoHeader.toCharBlock(), 40);

        int extra_bytes = (4 - (infoHeader.width * 3) % 4) % 4;
        void* padd = (void*)malloc(extra_bytes);

        // Store the image in the BMP format (bottom-up, i.e.,
        //  first row stores is the lowermost one)
        for(size_t row = height; row > 0; row--)
        {
            for(size_t col = 0; col < width; col++)
            {
                // Get the pixel value
                Vector3D p = data[row-1][col];
                uint8_t red   = (uint8_t)(std::min(p.x, 1.0) * 255);
                uint8_t green = (uint8_t)(std::min(p.y, 1.0) * 255);
                uint8_t blue  = (uint8_t)(std::min(p.z, 1.0) * 255);

                // Write the pixel value
                outputFile.write(reinterpret_cast<const char *>(&blue),  1); // blue
                outputFile.write(reinterpret_cast<const char *>(&green), 1); // green
                outputFile.write(reinterpret_cast<const char *>(&red),   1); // red

            }
            // Padd the rest of the row;
            outputFile.write(reinterpret_cast<const char *>(padd), extra_bytes);
        }

        outputFile.close();
        return 0;
    }
    else
    {
        // Problem opening file
        std::cout << "Problem at BitMap::save() : Could not open file \""
                  << "example.bmp" << "\"" << std::endl;
        return 1;
    }
}
