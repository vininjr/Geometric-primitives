#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
#include <iostream>

using namespace glm;
using namespace std;

float scaley = 0.0, scalex = 0.0;

class Esfera
{
public:
    float PI = 3.1415926f;
    float raio;
    int lats,longs;
    vector<vec3> arestas;
    Esfera(float raio, int lats, int longs);

};

Esfera::Esfera(float r, int lats, int longs)
{
    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = (2.0f*M_PI * float(i-1))/ float(lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
        double lat1 = (2.0f*M_PI * float(i))/ float(lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for(j = 0; j <= longs; j++)
        {
            double lng = (2.0f*M_PI * float(j))/ float(longs);
            double x = cos(lng);
            double y = sin(lng);
            vec3 v1 = vec3(x * zr0, y * zr0, z0);
            vec3 v2 = vec3(x * zr1, y * zr1, z1);
            this->arestas.push_back(v1);
            this->arestas.push_back(v2);
        }
    }

}

void drawEsfera(void)
{
    Esfera *c = new Esfera(20.0,50,50);
    glRotatef(scalex,1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i < c->arestas.size() ; i++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(c->arestas[i].x,c->arestas[i].y,c->arestas[i].z);
    }

    glEnd();
}

void special_keys(int button, int x, int y)
{
    switch (button)
    {
    case GLUT_KEY_UP:
        scalex += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        scalex -= 1.0f;
        if(scalex < 0.0) scalex = 0.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        scaley += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        scaley -= 1.0f;
        if (scaley < 0.0) scaley = 0.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawEsfera();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Esfera");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special_keys);
    glutMainLoop();
    return 0;
}
