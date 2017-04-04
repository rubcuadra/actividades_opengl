//
//  main.c
//  curvas
//
//  Created by Ruben Cuadra on 3/23/17.
//  Copyright © 2017 Ruben Cuadra. All rights reserved.
//

#include <stdlib.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#elif _WIN32 || __linux__
    #include <GL/glut.h>
#endif

//1)En los formatos de imágenes binarios ¿cuáles son las 2 secciones de formato internas y qué incluye cada una? (6 pts: 3c/u)
//El Header incluye el formato, las medidas(alto/ancho), tipo de archivo, compresion, etc
//Datos de Imagen: Incluye los colores y los valores de los pixeles

//2)Indica el aspect ratio de las siguientes resoluciones: , , 720x480 (3 pts: 1c/u)
// 1024x768   4:3
// 1920x1080 16:9
// 720x480  1.5:1

//3)Escribe como son las matrices de transformación homogénea de la translación y rotación con respecto a Z. (7 pts: 3.5c/u)
//Traslacion z lugares sobre eje z
//1 0 0 0
//0 1 0 0
//0 0 1 z
//0 0 0 1

//Rotacion z grados sonre eje z
// cos(z) -sin(z) 0 0
// sin(z)  cos(z) 0 0
// 0        0     1 0
// 0        0     0 1

//4) menciona ¿qué son: COP, DOP y el punto de fuga? (6 pts: 2c/u)
//Punto de fuga es el punto que se usa para montar una perspectiva, se ve en dibujo tecnico, en lugar de hacer lineas horizontales se harian lineas que salen desde ese punto hasta donde acaba la linea, con eso simulamos la perspectiva
//COP Centro de Proyeccion, El origen de la camara
//DOP Direccion de Proyeccion, hacia donde ve

//5)Explica qué hace la cinemática, la cinemática directa y la cinemática inversa. (9 pts: 3c/u)
//  Cinematica es el calculo de trayectorias sin considerar fuerzas externas mas que las iniciales, de modo que con un punto de inicio y una fuerza inicio podemos generar un punto final;
//Cinematica directa encuentra la configuración final con base en los grados de libertad y si configuracion inicial.
//Cinematica Inversa encuentra la configuración de cada grado de libertad dada la configuración final.


//6)De un brazo normal humano, menciona cada uno de los tipos de grados de libertad que se tienen en las articulaciones giratorias tanto en el hombro, en el codo y en la muñeca. (6 pts: 1c/u)
//Torsion
//Rotacion
//Revolucion

//El hombro posee rotacion y revolucion
//Codo Rotacion
//Muñeca posee Torsion,Rotacion y Revolucion

//7)Teniendo la cámara en el origen apuntando hacia el eje ­Z y si el plano de proyección está en ­5, ¿dónde se proyectan los puntos? (utilizar las ecuaciones básicas de proyección en perspectiva) para:
//         a) (5, 3, ­10), b) (­2, ­3, ­9). (6 pts: 3c/u)
//      (2.5,1.5,5) y ( 2/(9/5), 3/(9/5), 5  )

//8)Menciona las diferencias entre las curvas de Bezier y las curvas NURBS (3 pts)
//Bezier nos genera polinomios de grado n-1 donde n es el numero de puntos de control, puntos inicio/fin del polígono de control coincide con los vectores tangentes del los primeos y ultimos respectivamente
//Generan 2 funciones polinomiales, usan coordenadas homogeneas plasmadas en 3D, el grado maximo del polinomio es n donde n es el numero de puntos de control en direccion, lo que mas influye son knots en lugar de puntos de control

//9)Explica las diferencias entre la representación explícita, implícita o paramétricas de las ecuaciones. (6 pts)


//Explicita son las funciones que estan igualadas entre variables, de modo que se genera dependencia, cuando uno le da valor a una variable se genera la siguiente, con esto podemos despejar para obtener funcion en base a una variable

//Implicita son las funciones igualada a 0  de modo que limita el espacio dividiendo puntos que pertenecen o no a las curvas

//Parametrica suelen ser varias ecuaciones que definen cada eje, requieren de un parametro en 2D y de 2 para 3D, se suele limitar el parametro (entre 0 y 1 por ej)

//10) ¿Qué son y menciona las diferencias entre AR, VR, MR y AV? (8 pts)
    //AR es Realidad aumentada e implica agregarle cosas digitales a la realidad, agregarle a lo cotidiano elementos digitales , se sobreponen estimulos a la realidad
    //VR es realidad virtual es un mundo inmersivo el cual todo es digital, requiere ponerte headsets y te lleva a un lugar diferente de la realidad, suele requerir de todos los sentidos para genera una inmersion total, genera mundos digitales
    //MR es realidad mixta y como su nombre lo indica es una fusion de ambas partes, implica combinar mundos reales y mundos virtuales para que coexistan
    //AV es Augmented Virtuality es llevar objetos de la vida real a mundos virtualizados


GLfloat ctlpoints[4][4][3];
//GLfloat ctlpoints2[4][4][3];
int showPoints = 1;
GLfloat angle_x = 0.0;
GLfloat angle_y = 0.0;
GLfloat zoom_z = 1;
float offset = 0.0;

GLUnurbsObj *theNurb;
//GLUnurbsObj *theOtherNurb;

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (GLdouble)w/(GLdouble)h, 3.0, 8.0);
    glMatrixMode(GL_MODELVIEW);
}

void
menu(int value)
{
    switch (value) {
        case 0:
            zoom_z += 0.1;
            break;
        case 1:
            zoom_z -= 0.1;
            break;
        case 2:
            offset += 0.1;
            break;
        case 3:
            offset -= 0.1;
            break;
    }
    glutPostRedisplay();
}

int down = 0, lastx, lasty;

/* ARGSUSED1 */
void
motion(int x, int y)
{
    if (down)
    {
        angle_x = lastx - x;
        angle_y = lasty - y;
        //glRotatef(lastx - x, 0, 1, 0);
        //lastx = x;
        glutPostRedisplay();
    }
}

/* ARGSUSED3 */
void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lastx = x;
            down = 1;
        }
        else
        {
            down = 0;
        }
    }
}

GLfloat ctrlpoints[4][4][3] =
{
    {
        {-1.5, -1.5, 0},
        {-0.5, -1.5, 0},
        {0.5, -1.5, 0},
        {1.5, -1.5, 0}},
    {
        {-1, -1, 1.0},
        {-1, -1, 2.0},
        {1, -1, 2.0},
        {1, -1, 1.0}},
    {
        {-1, 1, 1.0},
        {-1, 1, 2.0},
        {1, 1, 2.0},
        {1, 1, 1.0}},
    {
        {-1.5, 1.5, 0.0},
        {-0.5, 1.5, 0},
        {0.5, 1.5, 0},
        {1.5, 1.5, 0.0}}
};

GLfloat ctrlCarne[4][4][3] =
{
    {
        {-1.5, -1.5, 0.0},
        {-0.5, -1.5, 0.0},
        {0.5, -1.5, 0.0},
        {1.5, -1.5, 0.0}},
    {
        {-1.5, -2, 0.0},
        {-0.5, -2, 2.0},
        {0.5, -2, 2.0},
        {1.5, -2, 0.0}},
    {
        {-1.5, 2, 0.0},
        {-0.5, 2, 2.0},
        {0.5, 2,    2.0},
        {1.5, 2,  0.0}},
    {
        {-1.5, 1.5, 0.0},
        {-0.5, 1.5, 0.0},
        {0.5, 1.5, 0.0},
        {1.5, 1.5, 0.0}}
};

GLfloat color_pan[4] = {0.768,0.596,0.121,1.0};
GLfloat color_carne[4] = {1,0.325,0.258,1.0};

void initlights(void)
{
    GLfloat ambient[] =
    {0.2, 0.2, 0.2, 1.0};
    GLfloat position[] =
    {3.0, 3.0, 5.0, 1.0};
    GLfloat mat_diffuse[] =
    {0.6, 0.6, 0.6, 1.0};
    GLfloat mat_specular[] =
    {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] =
    {50.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef(angle_x, 0, 1, 0);
        glRotatef(angle_y, 1, 0, 0);
        glScalef(zoom_z, zoom_z, zoom_z);
    
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, color_pan ); //Color del material
    
        //Panes
        glPushMatrix();
            glTranslatef(0, 0, 0.25 + offset);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(0, 0, 0.25 + offset);
            glRotatef(90,0, 0, 1);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(0, 0, -0.25 -offset);
            glScalef(-1, -1, -1);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(0, 0, -0.25 -offset);
            glRotatef(90,0, 0, 1);
            glScalef(-1, -1, -1);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();
    
        //Carne
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlCarne[0][0][0]);
        glMaterialfv(GL_FRONT, GL_AMBIENT, color_carne ); //Color del material
        glPushMatrix();
            glScalef(1, 0.8, 0.5);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();
    
        glPushMatrix();
            //glTranslatef(0, 0, 0.25);
            glScalef(-1, -0.8, -0.5);
            glEvalMesh2(GL_FILL, 0, 25, 0, 25);
        glPopMatrix();

    
    glPopMatrix();
    
    glFlush();
}

void
myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glMapGrid2f(25, 0.0, 1.0, 25, 0.0, 1.0);
    initlights();       /* for lighted version only */
}

void
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
                4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
                4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Zoom In", 1);
    glutAddMenuEntry("Zoom Out", 0);
    glutAddMenuEntry("Separar", 2);
    glutAddMenuEntry("Unir", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
