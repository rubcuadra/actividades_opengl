//
//  main.h
//  cGraphics
//
//  Created by Ruben Cuadra on 1/26/17 A01019102
//  Copyright © 2017 Ruben Cuadra. All rights reserved.
//
#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32 || __linux__
    #include <GL/glut.h>
#endif
#include <stdlib.h>

#include <stdlib.h>

int numdrawsegs = 20;

GLfloat ctrlpoints[6][3] = {
    { -3.0, -4.0, 0.0}, { 4.0, -3.0, 0.0},
    {4.0, 0.0, 0.0}, {-4.0, 0.0, 0.0},
    {-4.0, 3.0, 0.0}, {3.0, 4.0, 0.0}};
GLfloat ctrlpoints2[7][3] = {
    { 2.0, 1.0, 0.0}, { 2.0, 3.0, 0.0},
    {-4.8, 3.0, 0.0}, {-4.8, -4.0, 0.0},
    {2.0, -4.0, 0.0}, {2.0, 8.0, 0.0}, {3.0, -2.0, 0.0}};

GLfloat ctrlpoints_R[3][3] = { { -1.0, 1.0, 0.0}, { 0.5, 1.0, 0.0}, {0.0,-1.1,0.0} };
GLfloat ctrlpoints_U[6][3] = {{ -1.0, 1.0, 0.0},{ -1, -1.0, 0.0},{ 0.5, -1.0, 0.0}, {0.0,3.5,0.0}, {-0.5,0.25,0.0},{0.25,-0.5,0.0} };
GLfloat ctrlpoints_c[5][3] = {{ 1, 1.5, 0.0},{ -0.3, 1.7, 0.0},{ -0.7,0.75,0.0},{ -0.25,0.0,0.0},{1,0.25,0.0}};
GLfloat ctrlpoints_l[3][3] = {{ -0.25, 0, 0.0},{ 0.5, 0.75, 0.0},{ 0,2.5,0}};
GLfloat ctrlpoints_e[5][3] = {{ -1.55, 0, 0.0},{ 4, 1.25, 0.0},{ -4, 2, 0.0},{ -1, -1.5, 0.0},{ 1,-1.5,0}};

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_MAP1_VERTEX_3);
}

void pintaS()
{
    int i;
    glPushMatrix();
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6, &ctrlpoints[0][0]);
    glTranslatef(-3.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= 50; i++)
        glEvalCoord1f((GLfloat) i/50.0);
    glEnd();
    
    /* The following code displays the control points as dots. */
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 6; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    glPopMatrix();
}

void draw_a()
{
    int i;
    glPushMatrix();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 7, &ctrlpoints2[0][0]);
        glScalef(0.5, 0.5, 0.5);
        glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 28; i++)
                glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
}

void draw_u()
{
    int i;
    glPushMatrix();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6, &ctrlpoints_U[0][0]);
        glBegin(GL_LINE_STRIP);
            for (i = 0; i <= 28; i++)
                glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
}
void draw_n()
{
    glPushMatrix();
        glScalef(-1, -1, -1);
        draw_u();
    glPopMatrix();
}

void draw_l()
{
    glPushMatrix();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints_l[0][0]);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 28; i++)
            glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glScalef(-1, 1, 1);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints_l[0][0]);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 28; i++)
            glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
}
void draw_c()
{
    int i;
    glPushMatrix();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 5, &ctrlpoints_c[0][0]);
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 28; i++)
            glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
}
void draw_d()
{
    glPushMatrix();
    
        glPushMatrix();
            glTranslatef(-0.5, 0, 0);
            glScalef(0.8,1, 1);
            draw_c();
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(0.45, 0.2, 0);
            glScalef(0.75,1, 1);
            draw_l();
        glPopMatrix();
    
    glPopMatrix();
}

void draw_r()
{
    glPushMatrix();
        glPushMatrix();
            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3 , &ctrlpoints_R[0][0]);
            glBegin(GL_LINE_STRIP);
            for (int i = 5; i <= 28; i++)   //Que no salga todo
                glEvalCoord1f((GLfloat) i/28.0);
            glEnd();
        glPopMatrix();
        glPushMatrix();
            glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3 , &ctrlpoints_R[0][0]);
            glRotatef(180,0,1,0);
            glBegin(GL_LINE_STRIP);
            for (int  i = 0; i <= 28; i++)
                glEvalCoord1f((GLfloat) i/28.0);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void draw_e()
{
    int i;
    glPushMatrix();
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 5, &ctrlpoints_e[0][0]);
        glScalef(0.5, 0.5, 0.5);
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 28; i++)
            glEvalCoord1f((GLfloat) i/28.0);
        glEnd();
    glPopMatrix();
}

void draw_b()
{
    glPushMatrix();
        glScalef(-1, 1, 1);
        draw_d();
    glPopMatrix();
    
}
void draw_name()
{
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(-6.5, 3, 0);
        draw_r();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0, 1 , 0);
        glTranslatef(-5.0, 2.5, 0);
        draw_u();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0, 0 , 1);
        glTranslatef(-4.10, 1.8, 0);
        draw_b();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1 , 1);
        glTranslatef(-2.75, 2.75, 0);
        glRotatef(-20, 0, 0, 1);
        draw_e();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1, 0 , 1);
        glTranslatef(-2.1, 2.95, 0);
        draw_n();
    glPopMatrix();
}

void draw_last_name()
{
    glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslatef(-6.75,-1, 0);
        glScalef(1, 1.4, 1);
        draw_c();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0, 0.5 , 0.5);
        glTranslatef(-4.75,-0.55, 0);
        draw_u();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.5, 0.5 , 0.5);
        glTranslatef(-4.0,-0.4, 0);
        glRotatef(10, 0, 0, 1);
        glScalef(0.55, 0.55, 1);
        draw_a();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.7, 0.1 , 0.4);
        glTranslatef(-2.5,-0.8, 0);
        glScalef(0.8, 0.8, 1);
        draw_d();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.4, 0.7 , 0.1);
        glTranslatef(-1.65,0, 0);
        glScalef(0.6, 0.6, 1);
        draw_r();
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.1, 0.4 , 0.7);
        glTranslatef(-0.8,-0.3, 0);
        glRotatef(10, 0, 0, 1);
        glScalef(0.55, 0.55, 1);
        draw_a();
    glPopMatrix();
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glPushMatrix();
        draw_name();
        draw_last_name();
    glPopMatrix();
    
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
                5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-5.0*(GLfloat)w/(GLfloat)h,
                5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* ARGSUSED1 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1500, 1500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutMainLoop();
    return 0;
}
