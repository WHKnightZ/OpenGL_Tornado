#include <math.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 600
#define INTERVAL 15
#define MAX 20

int POS_X, POS_Y;

GLfloat BG_Color[] = {0.2f, 0.6f, 0.6f, 1.0f};
GLfloat Light_Pos[] = {0.0f, 20.0f, 80.0f, 0.0f};
GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

float Angle = 0.0f;
float Rotate = 10.0f;
double Height = -1.2;

void Init_Game() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, Height, Height + 2.0, 1, 50);
    glTranslatef(0.0f, -5.0f, -7.0f);
    glRotatef(Rotate, 1.0f, 0.0f, 0.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(BG_Color[0], BG_Color[1], BG_Color[2], BG_Color[3]);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Dif);
    glLightfv(GL_LIGHT0, GL_POSITION, Light_Pos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0f);
    glEnable(GL_LIGHTING);
}

float r2 = 0.6f, h2 = 0.0f, a2 = 0.0f; //0.6f
float a4 = 10.0f;

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int i, j, k;
    float a = a2, h = h2, r = r2;
    float a3 = a4;
    float h3 = 0.004f;
    for (i = 0; i < 1000; i++) {
        glLoadIdentity();
        glRotatef(a - Angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(r, h, 0.0f);
        glutSolidSphere(0.05, 10, 10);
        a += a3;
        h += h3;
        r *= 1.0017f;
        a3 *= 0.9999994f;
        h3 /= 1.001f;
    }
    glLoadIdentity();
    glutSwapBuffers();
}

void Timer(int value) {
//    r2 /= 1.0017f;
//    h2 *= 1.0005f;
//    a4 *= 1.0002f;
    Angle += 1.2f;
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, Timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tornado");
    Init_Game();
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
