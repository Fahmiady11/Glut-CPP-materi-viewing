#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Math.h>

float pos[3];
GLdouble viewdir[]= {-1.0, 0.0, 0.0};
double alpha = 3.1415;

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(pos[0], pos[1], pos[2], pos[0]+viewdir[0], pos[1]+viewdir[1],
                  pos[2]+viewdir[2], 0.0, 1.0, 0.0);

    glutSolidSphere (1.0, 40, 16);
    glTranslated(0,0,3);
    glutSolidTeapot(1);
    glTranslated(0,0,-6);
    glutSolidTorus(0.3, 0.7, 12, 12);

    glFlush ();
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    //glOrtho(-5,5,-5,5,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void mykey(unsigned char key, int x, int y){
    /*if (key=='n') {
        viewdir[0] = viewdir[0] * cos(-0.03) + viewdir[2] * sin(-0.03);
        viewdir[2] = -viewdir[0] * sin(-0.03) + viewdir[2] * cos(-0.03);
    }
    else if (key=='v') {
        viewdir[0] = viewdir[0] * cos(0.03) + viewdir[2] * sin(0.03);
        viewdir[2] = -viewdir[0] * sin(0.03) + viewdir[2] * cos(0.03);
    }*/
    if (key=='n'){
        alpha +=0.01;
        viewdir[0] = cos(alpha);
        viewdir[2] = sin(alpha);
    }
    else if (key == 'v'){
        alpha -=0.01;
        viewdir[0] = cos(alpha);
        viewdir[2] = sin(alpha);
    }
    else if (key=='g') {
        pos[0] += 0.2 * viewdir[0];
        pos[1] += 0.2 * viewdir[1];
        pos[2] += 0.2 * viewdir[2];
    }
    else if (key=='b') {
        pos[0] -= 0.2 * viewdir[0];
        pos[1] -= 0.2 * viewdir[1];
        pos[2] -= 0.2 * viewdir[2];
    }
    glutPostRedisplay();
}

void init(void){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };

    GLfloat diffuse_light[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat light_position[] = { 3.0, 1.0, 3.0, 0.0 };
    GLfloat specular_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat ambient_light[] = { 1.0, 0.0, 0.0, 1.0 };

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

    pos[0] = 5.0;
    pos[1] = 0.0;
    pos[2] = 0.0;
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Viewing");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);
    glutMainLoop();
    return 0;
}
