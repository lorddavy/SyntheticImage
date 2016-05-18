#include "camera.h"

Camera::Camera(const Matrix4x4 &cameraToWorld_, const Film &film_)
    : cameraToWorld(cameraToWorld_), film(film_)
{
    aspect = (double) (film.getWidth()) / (double) (film.getHeight());
}

