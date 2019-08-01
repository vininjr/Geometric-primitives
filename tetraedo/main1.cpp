#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <math.h>

using namespace glm;
using namespace std;

int angleZ = 0,angleX = 0;

class Face
{
public:
    vec3 v1,v2,v3;
    Face(vec3 v1,vec3 v2,vec3 v3);

};

class Tetraedo
{
public:
    Face *f[4];
    Tetraedo(vec3 v0,vec3 v1,vec3 v2);
};

Face::Face(vec3 v1,vec3 v2,vec3 v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

Tetraedo::Tetraedo(vec3 v0, vec3 v1, vec3 v2)
{

    float l = fabs(v0[0] - v1[0]);
    float h = (l *sqrt(3.0))/4.0;
    float a = (l *sqrt(6.0))/3.0;

    vec3 v3 = vec3(0.0f, h + a, 0.0f);
////v0 , v1 , v2
    this->f[0] = new Face(v0,v1,v2);
////v0 , v2 , v3 .
    this->f[1] = new Face(v0,v2,v3);
////v0 , v1 , v3;
    this->f[2] = new Face(v0,v1,v3);
//// v3,v2,v1;
    this->f[3] = new Face(v3,v2,v1);
}

void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5.0,5.0,-5.0,5.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei width, GLsizei height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void spkeyboard(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        angleZ += 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        angleZ -= 1;
        if(angleZ<1) angleZ=1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        angleX += 1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        angleX -= 1;
        if(angleX<1) angleX=1;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


void tetaedro ()
{
    vec3 v0 = vec3(0.0, -0.25,  0.5 );
    vec3 v1 = vec3( 0.5, -0.25, -0.25 );
    vec3 v2 = vec3(-0.5, -0.25, -0.25 );

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    mat4 Rz = mat4(1.0);

    //rotacao eixo X
    Rz[1] = vec4(0.0, cos(angleX), -sin(angleX), 0.0);
    Rz[2] = vec4( 0.0, sin(angleX), cos(angleX), 0.0);

    //Rz[0] = vec4(cos(angleX), -sin(angleX), 0.0, 0.0);
    //Rz[1] = vec4(sin(angleX), cos(angleX), 0.0, 0.0);

    Tetraedo *t = new Tetraedo(v0,v1,v2);

    //glRotatef(angleX,1.0f,0.0f,0.0f);
    //glRotatef(angleZ,0.0f,0.0f,1.0f);
    glMultMatrixf((GLfloat*)&Rz);

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 4; i++)
    {
        glColor3f(1.0,1.0,1.0);
        glVertex3f(t->f[i]->v1.x,t->f[i]->v1.y,t->f[i]->v1.z);
        glVertex3f(t->f[i]->v2.x,t->f[i]->v2.y,t->f[i]->v2.z);
        glVertex3f(t->f[i]->v3.x,t->f[i]->v3.y,t->f[i]->v3.z);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

int main(int argc,char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TETRAEDRO");
    myinit();
    glutDisplayFunc(tetaedro);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spkeyboard);
    glutMainLoop();
    return 0;
}
