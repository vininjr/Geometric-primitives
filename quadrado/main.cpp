#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <GL/glu.h>
#include <bits/stdc++.h>
#include <iostream>

using namespace glm;
using namespace std;

float scalex = 0.0,scaley = 0.0;

class Quadrado
{
public:
    vec3 a, b, c, d;

    Quadrado(vec3 a, vec3 b, vec3 c, vec3 d);

};

Quadrado::Quadrado(vec3 a, vec3 b, vec3 c, vec3 d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

void drawQuadrado(void)
{
    glPushMatrix();
    mat4 Rz = mat4(1.0);
    mat4 rf = mat4(1.0);

    //rotacao eixo X
    //Rz[1] = vec4(0.0, cos(scalex), -sin(scalex), 0.0);
    //Rz[2] = vec4( 0.0, sin(scalex), cos(scalex), 0.0);

    //rotacao eixo Y
    //Rz[0] = vec4(cos(scalex), 0.0, sin(scalex), 0.0);
    //Rz[2] = vec4( -sin(scalex),0.0, cos(scalex), 0.0);

    //rotacao eixo Z
    //Rz[0] = vec4(cos(scalex), -sin(scalex), 0.0, 0.0);
    //Rz[1] = vec4(sin(scalex), cos(scalex), 0.0, 0.0);

    //TRANSLACAO
    //Rz[0] = vec4(1.0,0.0,0.0,scalex);
    //Rz[1] = vec4(0.0,1.0,0.0,scaley);

    //Escala
    //Rz[0] = vec4(scalex,0.0,0.0,0.0);
    //Rz[1] = vec4(0.0,scaley,0.0,0.0);

    //Cisalhamento
    //Rz[0] = vec4(1.0,cos(scalex)/sin(scalex),0.0,0.0); //x
    //Rz[1] = vec4(cos(scalex)/sin(scalex),1.0,0.0,0.0); //y

    //Reflexao
    //rf[0] = vec4(-1.0,0.0,0.0,0.0);
    //rf[1] = vec4(0.0,-1.0,0.0,0.0);

    //if((int)scalex % 2 == 0) glMultMatrixf((GLfloat*) &rf);

    //glMultTransposeMatrixf((GLfloat*) &Rz);

    Quadrado *q = new Quadrado(vec3(-5.0, 7.5, 0.0),vec3(-5.0, -5.0, 0.0),vec3(7.5, -5.0, 0.0),vec3(7.5, 7.5, 0.0));

    glBegin(GL_LINE_LOOP);
        glColor3b(0.0,0.0,0.0);
        glVertex2f(q->a.x, q->a.y);
        glVertex2f(q->b.x, q->b.y);
        glVertex2f(q->c.x, q->c.y);
        glVertex2f(q->d.x, q->d.y);
    glEnd();
    glPopMatrix();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuadrado();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void special_keys(int button, int x, int y)
{
    switch (button)
    {
    case GLUT_KEY_RIGHT:
        scalex += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        scalex -= 1.0f;
        if(scalex < 0.0) scalex = 0.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        scaley += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        scaley -= 1.0f;
        if (scaley < 0.0) scaley = 0.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quadrado");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special_keys);
    glutMainLoop();
    return 0;
}

