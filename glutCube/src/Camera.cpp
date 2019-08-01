#include "Camera.h"

Camera::Camera(vec3 p, vec3 o, vec3 u)
{
    this->position = p;
    this->orientation = o;
    this->upvector = u;
}

Camera::~Camera()
{
    //dtor
}

vec3 Camera::getPos()
{
    return this->position;
}

vec3 Camera::getOri()
{
    return this->orientation;
}

vec3 Camera::getUp()
{
    return this->upvector;
}

void Camera::setPos(vec3 p)
{
    this->position = p;
}

void Camera::setOri(vec3 o)
{
    this->orientation = o;
}

void Camera::setUp(vec3 u)
{
    this->upvector = u;
}
