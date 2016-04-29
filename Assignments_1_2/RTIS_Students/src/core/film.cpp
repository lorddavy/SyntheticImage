#include "film.h"

/**
 * @brief Film::Film
 */

Film::Film(size_t width_, size_t height_)
{
    // Initialize the width and height of the image
    width  = width_;
    height = height_;

    // Allocate memory for the image matrix
    data = new Vector3D*[height];
    for( size_t i=0; i<height; i++)
    {
        data[i] = new Vector3D[width];
    }

    // Set all values to zero
    clearData();
}

Film::~Film()
{
    // Resease the dynamically-allocated memory for the image data
    for( size_t i=0; i<height; i++)
    {
        delete [] data[i];
    }
    delete [] data;
}

size_t Film::getWidth() const
{
    return width;
}

size_t Film::getHeight() const
{
    return height;
}

Vector3D Film::getPixelValue(size_t w, size_t h) const
{
    return data[h][w];
}

void Film::setPixelValue(size_t w, size_t h, Vector3D &value)
{
    data[h][w] = value;
}

void Film::clearData()
{
    Vector3D zero;

    for(size_t h=0; h<height; h++)
    {
        for(size_t w=0; w<width; w++)
        {
            setPixelValue(w, h, zero);
        }
    }
}

int Film::save()
{
    return BitMap::save(data, width, height);
}
