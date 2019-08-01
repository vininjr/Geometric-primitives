#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

class Pentagono
{
public:
    vec3 a, b, c, d, e;

    Pentagono(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e);

};

Pentagono::Pentagono(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
}

void drawPentagono(void)
{
    glPushMatrix();
    Pentagono *p = new Pentagono(vec3(-2.5,3.75,0.0),vec3(-2.5,-2.5,0.0),vec3(3.75,-2.5,0.0),vec3(3.75,3.75,0.0),vec3(0.7,6.5,0.0));
    glBegin(GL_LINE_LOOP);
        glVertex2f(p->a.x,p->a.y);
        glVertex2f(p->b.x,p->b.y);
        glVertex2f(p->c.x,p->c.y);
        glVertex2f(p->d.x,p->d.y);
        glVertex2f(p->e.x,p->e.y);
    glEnd();
}

void init(void)
{
    glShadeModel (GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPentagono();
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Pentagono");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
