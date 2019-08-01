#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
#include <iostream>

using namespace glm;
using namespace std;

float scalex = 0.0,scaley = 0.0;

class Triangulo
{
public:
    vec3 a, b, c;

    Triangulo(vec3 a, vec3 b, vec3 c);

};

Triangulo::Triangulo(vec3 a, vec3 b, vec3 c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void drawTriangulo(void)
{
    glPushMatrix();
    mat4 rf = mat4(1.0);
    mat4 Rz = mat4(1.0);

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
    glMultMatrixf((GLfloat*)&Rz);
    //glTranslatef(scalex,scaley,1);
    //glRotatef(scalex,1.0f,1.0f,0.0f);
    Triangulo *t = new Triangulo(vec3(5.0, 5.0, 0.0),vec3(5.0, -5.0, 0.0),vec3(-5.0, 5.0, 0.0));

    glBegin(GL_LINE_LOOP);
        glColor3b(0.0,0.0,0.0);
        glVertex2f(t->a.x, t->a.y);
        glVertex2f(t->b.x, t->b.y);
        glVertex2f(t->c.x, t->c.y);
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
    drawTriangulo();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Triangulo");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special_keys);
    glutMainLoop();
    return 0;
}
