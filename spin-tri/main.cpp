#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <glm/glm.hpp>

using namespace glm;

const float PI = 3.14159265359;

float angle = 0.0;

class Triangle
{
public:
    vec3 a, b, c;

    Triangle(vec3 a, vec3 b, vec3 c);

};

Triangle::Triangle(vec3 a, vec3 b, vec3 c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void drawTriangle(void)
{
    glPushMatrix();
    Triangle *t = new Triangle(vec3(-2.0, 4.0, 0.0), vec3(5.0, 0.0, 0.0), vec3(5.0, 8.666, 0.0));
    mat4 Rz = mat4(1.0);
    //rotacao eixo X
    //Rz[1] = vec4(0.0, cos(angle), -sin(angle), 0.0);
    //Rz[2] = vec4( 0.0, sin(angle), cos(angle), 0.0);

    //rotacao eixo Y
    //Rz[0] = vec4(cos(angle), 0.0, sin(angle), 0.0);
    //Rz[2] = vec4( -sin(angle),0.0, cos(angle), 0.0);

    //rotacao eixo Z
    //Rz[0] = vec4(cos(angle), -sin(angle), 0.0, 0.0);
    //Rz[1] = vec4(sin(angle), cos(angle), 0.0, 0.0);

    //TRANSLACAO
    //Rz[0] = vec4(1.0,0.0,0.0,0.0);
    //Rz[1] = vec4(0.0,1.0,0.0,angle);
    //Rz[2] = vec4(0.0,0.0,1.0,angle);

    glMultMatrixf((GLfloat*) &Rz);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(t->a.x, t->a.y);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(t->b.x, t->b.y);
        glColor3f(0.0, 0.0, 1.0);
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
    drawTriangle();
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

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            angle += 5;
        glutPostRedisplay();
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            angle -= 5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

/*
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Spin Tri");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
