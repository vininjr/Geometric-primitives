#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Camera
{
    public:
        Camera(vec3 p, vec3 o, vec3 u);
        virtual ~Camera();

        vec3 getPos();
        vec3 getOri();
        vec3 getUp();

        void setPos(vec3 p);
        void setOri(vec3 o);
        void setUp(vec3 u);

    protected:

    private:

    vec3 position;
    vec3 orientation;
    vec3 upvector;

};

#endif // CAMERA_H
