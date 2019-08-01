#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include <math.h>

using namespace glm;
using namespace std;

float scalex = 0.0,scaley = 0.0;

class Face
{
public:
    vec3 v1,v2,v3,v4;
    Face(vec3 v1,vec3 v2,vec3 v3,vec3 v4);

};

class Cubo
{
public:
    Face *f[6];
    Cubo(vec3 v0,vec3 v1,vec3 v2,vec3 v3);
};

Face::Face(vec3 v1,vec3 v2,vec3 v3,vec3 v4)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v4 = v4;
}

Cubo::Cubo(vec3 v1, vec3 v2, vec3 v3, vec3 v4)
{

    float l = fabs(v2[0] - v1[0]);

    vec3 v5,v6,v7,v8;

    v5 = vec3(v1[0],v1[1]+l,v1[2]);
    v6 = vec3(v2[0],v2[1]+l,v2[2]);
    v7 = vec3(v3[0],v3[1]+l,v3[2]);
    v8 = vec3(v4[0],v4[1]+l,v4[2]);

    this->f[0] = new Face(v1,v2,v3,v4);
    this->f[1] = new Face(v1,v5,v6,v2);
    this->f[2] = new Face(v3,v7,v6,v2);
    this->f[3] = new Face(v3,v7,v8,v4);
    this->f[4] = new Face(v4,v8,v5,v1);
    this->f[5] = new Face(v5,v6,v7,v8);

}

void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    //glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0f, 1.0f);
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
        scalex += 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        scalex -= 1;
        if(scalex<0.0) scalex=0.0;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        scaley += 1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        scaley -= 1;
        if(scaley<0.0) scaley=0.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


void tetaedro ()
{
    vec3 v0 = vec3(0.25, 0.25,  -0.25 );
    vec3 v1 = vec3(-0.25, 0.25, -0.25 );
    vec3 v2 = vec3(-0.25, 0.25, 0.25 );
    vec3 v3 = vec3(0.25, 0.25, 0.25 );

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    Cubo *t = new Cubo(v0,v1,v2,v3);
    mat4 Rz = mat4(1.0);
    mat4 Rz1 = mat4(1.0);

    //rotacao eixo X
    //Rz[1] = vec4(0.0, cos(scalex), -sin(scalex), 0.0);
    //Rz[2] = vec4( 0.0, sin(scalex), cos(scalex), 0.0);

    //rotacao eixo Y
    //Rz1[0] = vec4(cos(scaley), 0.0, sin(scaley), 0.0);
    //Rz1[2] = vec4( -sin(scaley),0.0, cos(scaley), 0.0);

    //rotacao eixo Z
    //Rz[0] = vec4(cos(scalex), -sin(scalex), 0.0, 0.0);
    //Rz[1] = vec4(sin(scalex), cos(scalex), 0.0, 0.0);

    //TRANSLACAO
    //Rz[0] = vec4(1.0,0.0,0.0,scalex);
    //Rz[1] = vec4(0.0,1.0,0.0,scaley);

    //Escala
    //Rz1[0] = vec4(scalex,0.0,0.0,0.0);
    //Rz1[1] = vec4(0.0,scaley,0.0,0.0);

    //Cisalhamento
    //Rz[0] = vec4(1.0,cos(scalex)/sin(scalex),0.0,0.0); //x
    //Rz[1] = vec4(cos(scalex)/sin(scalex),1.0,0.0,0.0); //y

    //Reflexao
    //Rz[0] = vec4(-1.0,0.0,0.0,0.0);
    //Rz[1] = vec4(0.0,-1.0,0.0,0.0);
    //if((int)scalex % 2 == 0) glMultMatrixf((GLfloat*) &Rz);

    //glMultTransposeMatrixf((GLfloat*)&Rz);
    //glMultMatrixf((GLfloat*)&Rz);
    //glMultMatrixf((GLfloat*)&Rz1);
    //glScalef(scalex,scaley,0.0f);
    //glTranslatef(0.0,float(1.0/4.0)*scaley,0.0);

    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 6; i++)
    {
        glColor3f(1.0,1.0,1.0);
        glVertex3f(t->f[i]->v1.x,t->f[i]->v1.y,t->f[i]->v1.z);
        glVertex3f(t->f[i]->v2.x,t->f[i]->v2.y,t->f[i]->v2.z);
        glVertex3f(t->f[i]->v3.x,t->f[i]->v3.y,t->f[i]->v3.z);
        glVertex3f(t->f[i]->v4.x,t->f[i]->v4.y,t->f[i]->v4.z);
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
    glutCreateWindow("CUBO");
    myinit();
    glutDisplayFunc(tetaedro);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spkeyboard);
    glutMainLoop();
    return 0;
}
