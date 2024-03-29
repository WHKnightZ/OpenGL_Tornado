#include <math.h>
#include <GL/glut.h>

#define WIDTH 400
#define HEIGHT 400
#define INTERVAL 15
#define RADIAN 57.29578f

int POS_X, POS_Y;

GLfloat BGColor[] = {0.420f, 0.604f, 0.922f, 1.0f};
GLfloat Light_Pos[] = {0.0f, -20.0f, 80.0f, 0.0f};
GLfloat Light_Dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Ambient[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat Diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat Specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

float Angle = 0.0f, x, y;

void Init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, 0.5, -0.5, 1, 200);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.2f, 0.6f, 0.6f, 1.0f);
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

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int i, j, k;
    float f = 3.0f, g, h;
    for (i = 0; i < 30; i++) {
        g = i * 0.3f - 3.0f;
        k = 60 - i * 1.2f;
        h = 360.0f / k;
        for (j = 0; j < k; j++) {
            glLoadIdentity();
            gluLookAt(x, -5.0, y, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            glRotatef(j * h, 0.0f, 1.0f, 0.0f);
            glTranslatef(f, g, 0.0f);
            glutSolidSphere(0.05, 10, 10);
        }
        f *= 0.93f;
    }
    glutSwapBuffers();
}

void Timer(int value) {
    x = 10 * sin(Angle / RADIAN);
    y = 10 * cos(Angle / RADIAN);
    Angle -= 1.0f;
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
    Init();
    glutTimerFunc(0, Timer, 0);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
