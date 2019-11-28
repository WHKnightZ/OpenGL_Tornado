#include "../Library/loadpng.h"
#include<time.h>
#include<math.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 600
#define INTERVAL 100
#define MAX 20

int POS_X, POS_Y;

GLfloat BG_Color[] = { 0.2f, 0.6f, 0.6f, 1.0f };
GLfloat Light_Pos[] = { 0.0f, 20.0f, 80.0f, 0.0f };
GLfloat Light_Dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

float Angle=0.0f;

void Init_Game() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.2,0.8,1,50);
    glTranslatef(0.0f,-1.5f,-7.5f);
    glRotatef(21,1,0,0);
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

void Display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int i,j,k;
    float f=3.0f,g,h;
    for (i=0;i<30;i++){
    	g=3.0f-i*0.3f;
    	k=60-i*1.2f;
    	h=360.0f/k;
    	for (j=0;j<k;j++){
    		glLoadIdentity();
    		glRotatef(j*h-Angle,0.0f,1.0f,0.0f);
    		glTranslatef(f,g,0.0f);
    		glutSolidSphere(0.05,10,10);
		}
		f*=0.93f;
	}
	glLoadIdentity();
    glutSwapBuffers();
}

void Timer(int value){
	Angle-=1.0f;
	glutPostRedisplay();
	glutTimerFunc(15,Timer,0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tornado");
    Init_Game();
    glutTimerFunc(0,Timer,0);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
