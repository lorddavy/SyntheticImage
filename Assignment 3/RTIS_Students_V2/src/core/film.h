#ifndef FILM_H
#define FILM_H

#include "vector3d.h"
#include "bitmap.h"

#include <iostream>


/**
 * @brief The Film class
 */
class Film
{
public:
    // Constructor(s)
    Film(size_t width_, size_t height_);
    Film() = delete;

    // Destructor
    ~Film();

    // Getters
    size_t getWidth() const;
    size_t getHeight() const;
    Vector3D getPixelValue(size_t w, size_t h) const;

    // Setters
    void setPixelValue(size_t w, size_t h, Vector3D &value);

    // Other functions
    int save();
    void clearData();

private:
    // Image size
    size_t width;
    size_t height;

    // Pointer to image data
    Vector3D **data;
};

#endif // FILM_H
