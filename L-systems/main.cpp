#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

int W=1000;
int H=1000;
int n=0;
float d = 1.0;
float delta = 90 * 3.14/180;
vec2 p0 = vec2(0.0, 0.0);
vec2 v = vec2(0.0, d);
bool done = false;


void display(void);
void init(void);
void keyboard (unsigned char key, int x, int y);
void reshape(int w, int h);
void drawLine(vec2 p, vec2 q);
void L(string s, int n);

int main (int argc, char** argv) {
  int win;

  glutInit(&argc,argv);

  glutInitWindowSize(W,H);
  glutInitWindowPosition(100,100);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  win = glutCreateWindow("plant");
  glutSetWindow(win);
  glutKeyboardFunc(keyboard);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}


void keyboard (unsigned char key, int x, int y){
  switch(key){
      case '.':
        n++;
        p0 = vec2(0.0, 0.0);
        d /= 2;
        v = vec2(0.0, d);
        done = false;
        glutPostRedisplay();
        break;
      case ',':
        if (n > 0)
        {
          n--;
          d *= 2;
        }
        p0 = vec2(0.0, 0.0);
        v = vec2(0.0, d);
        done = false;
        glutPostRedisplay();
        break;
      case 'q':
        exit(0);
        break;
      default:
        break;
  }
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
   glShadeModel (GL_FLAT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    string axiom ("-F");

    glLineWidth(5);

    if (!done)
    {
        L(axiom, n);
        glFlush();
        done = true;
    }

}

void L(string s, int n)
{
    //cout << s << '\n' << "n = " << n << '\n' << s.size() << "\n\n";

    for (int i=0; i<s.size(); i++)
    {
        if (s[i] == 'F')
        {
            if (n > 0)
            {
                L("F-F+F+FF-F-F+F", n-1);
            }
            else
            {
                drawLine(p0, vec2(p0.x+v.x, p0.y+v.y));
                p0 = vec2(p0.x+v.x, p0.y+v.y);
            }
        }
        else if (s[i] == 'f')
        {
            p0 = vec2(p0.x+v.x, p0.y+v.y);
        }
        else if (s[i] == '+')
        {
            v = vec2(v.x * cos(delta)- v.y * sin(delta), v.x * sin(delta) + v.y * cos(delta));
        }
        else if (s[i] == '-')
        {
            v = vec2(v.x * cos(-delta)- v.y * sin(-delta), v.x * sin(-delta) + v.y * cos(-delta));
        }
    }

}

void drawLine(vec2 p, vec2 q)
{
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(p.x, p.y);
        glVertex2f(q.x, q.y);
        //printf("%.2f , %.2f-> %.2f , %.2f\n", p.x, p.y, q.x, q.y);
    glEnd();

}




