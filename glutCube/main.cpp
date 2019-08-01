#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Camera.h"

using namespace glm;

vec3 p1(0.0f, 0.0f, 5.0f);
vec3 p2(0.0f, 0.0f, -5.0f);
vec3 o1(0.0f, 0.0f, -1.0f);
vec3 o2(0.0f, 0.0f, 1.0f);
vec3 u(0.0f, 1.0f, 0.0f);

Camera *cam0 = new Camera(p1, o1, u);
Camera *cam1 = new Camera(p2, o2, u);

int activeCam = 0;

void init(void)
{

    glm::vec4 b;

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_FLAT);

}

void display(void)
{
    //-- Cleaning Screen
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);

    //--------

    //-- Projection and Camera Definitions

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();

    Camera *cam;
    if (activeCam)
    {
        cam = cam1;
        glOrtho(-5.0, 5, -5, 5, 2.0, 20.0);
    }
    else
    {
        cam = cam0;
        gluPerspective(45.0f, 1.0f, 2.0f, 100.0f);
    }

    vec3 orientation = cam->getPos() + cam->getOri();

    gluLookAt (cam->getPos().x, cam->getPos().y, cam->getPos().z,
               orientation.x, orientation.y, orientation.z,
               cam->getUp().x, cam->getUp().y, cam->getUp().z);

    //--------

    //-- Objects Definitions

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutWireCube (1.0);              /*drawing obejct*/

    glFlush();                       /*forces buffers update*/

}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(activeCam)
    {
        glOrtho(-10.0, 10, -10, 10, -1, 20.);
    }
    else
    {
        gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 2.0f, 100.0f);
    }
    glMatrixMode(GL_MODELVIEW);

}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            activeCam = 0;
         glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            activeCam = 1;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

void spkeyboard(int key, int x, int y)
{
    Camera *cam;
    if (activeCam == 0) cam = cam0;
    else cam = cam1;
    vec3 newPos, newOri;
    float angle = -1.0 * 3.14/180;

    switch (key)
    {
        case GLUT_KEY_RIGHT:
            //if (glutGetModifiers()== GLUT_ACTIVE_CTRL)
            {
            newOri.x = (cam->getOri().x * cos(angle)) + (cam->getOri().z * sin(angle));
            newOri.z = (-cam->getOri().x * sin(angle)) + (cam->getOri().z * cos(angle));
            newOri.y = cam->getOri().y;
            cam->setOri(newOri);
            }

            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            //if (glutGetModifiers()== GLUT_ACTIVE_CTRL)
            {
            newOri.x = (cam->getOri().x * cos(-angle)) + (cam->getOri().z * sin(-angle));
            newOri.z = (-cam->getOri().x * sin(-angle)) + (cam->getOri().z * cos(-angle));
            newOri.y = cam->getOri().y;
            cam->setOri(newOri);
            }

            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            newPos.x = cam->getPos().x + 0.2*cam->getOri().x;
            newPos.y = cam->getPos().y + 0.2*cam->getOri().y;
            newPos.z = cam->getPos().z + 0.2*cam->getOri().z;
            cam->setPos(newPos);
            glutPostRedisplay();
            break;

        case GLUT_KEY_DOWN:
            newPos.x = cam->getPos().x - 0.2*cam->getOri().x;
            newPos.y = cam->getPos().y - 0.2*cam->getOri().y;
            newPos.z = cam->getPos().z - 0.2*cam->getOri().z;
            cam->setPos(newPos);
            glutPostRedisplay();
            break;
    }

}

int main(int argc, char** argv)
{
    int mainWindow, infoWindow;

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize (500, 500);

    glutInitWindowPosition (600, 700);

    mainWindow = glutCreateWindow("GLUT CUBE");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(spkeyboard);
    init();

    glutMainLoop();

    return 0;
}
