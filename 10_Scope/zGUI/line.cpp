#include "line.h"
#include "osil.h"
#include<stdio.h>


void draw(int* y, int N)
{
    float x, dx = 1.0/N;
    glPushMatrix(); /* GL_MODELVIEW is default */
    glScalef(0.01,0.0001, 1.0);
    glTranslatef(0,0,0.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for(int t = 0; t < N; t++){
        glVertex2f(t, y[t]);
    }
    glEnd();
    glPopMatrix();
};
void redraw(void)
{
    osil w;
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    draw(w.y,200);
    glutSwapBuffers();
};
void idle(void){
    glutPostRedisplay();
};
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
};
