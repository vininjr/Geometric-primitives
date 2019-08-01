#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<vector>

using namespace std;

vector<float> points;
int angleZ = 0,angleX = 0;

GLfloat v0[] = {0.0, -1.0, +2.0 };
GLfloat v1[] = {+1.73205081, -1.0, -1.0 };
GLfloat v2[] = {-1.73205081, -1.0, -1.0 };

void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0f, 1.0f);
    //gluOrtho2D(-1.0,11.0,-1.0,11.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void spkeyboard(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        angleZ += 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        angleZ -= 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        angleX += 5;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        angleX -= 5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void tetaedro ()
{
    static const GLfloat P1[3] = { 0.0, -1.0, +2.0 };
    static const GLfloat P2[3] = { +1.73205081, -1.0, -1.0 };
    static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat P4[3] = { 0.0, +2.0, 0.0 };
    static const GLfloat * const coords[4][3] =
    {
        { P1, P2, P3 }, { P1, P3, P4 }, { P1, P4, P2 }, { P2, P4, P3 }
    };
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    //glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);

    for (int i = 0; i < 4; ++i)
    {
        glLoadName(i);
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; ++j)
        {
            glColor3f(0.0,0.0,0.0);
            glVertex3f(coords[i][j][0], coords[i][j][1],
                       coords[i][j][2]);
        }
        glEnd();
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
    tetaedro();
    glFlush();
}

void reshape1(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc,char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("TETRAEDRO");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape1);
    glutSpecialFunc(spkeyboard);
    glutMainLoop();

    return 0;
}
