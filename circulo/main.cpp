#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
#include <iostream>

using namespace glm;
using namespace std;

class Circle
{
public:
    float PI = 3.1415926f;
    float raio;
    int n_points;
    vector<vec2> arestas;
    Circle(float raio, int npoints);

};

Circle::Circle(float raio, int n)
{
    this->n_points = n;
    this->raio = raio;

    for (int i=0; i < n; i++)
    {
        float theta = 2.0f * this->PI * float(i) / float(n);
        vec2 v = vec2(cos(theta)*raio,sin(theta)*raio);
        arestas.push_back(v);
    }

}

void drawCircle(void)
{
    Circle *c = new Circle(20.0,40);
    glBegin(GL_LINE_LOOP);

    for (int i=0; i < c->arestas.size() ; i++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(c->arestas[i].x,c->arestas[i].y);
    }

    glEnd();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-40.0, 40.0, -40.0, 40.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Circulo");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
