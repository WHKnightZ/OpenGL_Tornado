#include "../Library/loadpng.h"
#include <GL/glut.h>
#include<time.h>
#include<math.h>

#define POSX 420
#define POSY 160
#define WIDTH 400
#define HEIGHT 400
#define INTERVAL 100
#define MAX 20

GLfloat BGColor[] = { 0.420f, 0.604f, 0.922f, 1.0f };
GLfloat Light_Pos[] = { 0.0f, -20.0f, 80.0f, 0.0f };
GLfloat Light_Dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat Specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

typedef struct Image {
    GLubyte* img;
    GLuint w, h;
} Image;

int w=180,h=240;

Image img;
float l,r,b,t,b2,t2;
float angle=0.0f,x,y;

void loadTexture(Image* img, const char* path) {
    loadPngSwap(&img->img, &img->w, &img->h, path);
}

void mapTexture(Image* img) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->img);
}

void initGame() {

}

void initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5,0.5,0.5,-0.5,1,200);
//    glTranslatef(0,4,-10);
//    glRotatef(-30,0,1,0);
    //gluPerspective(35.0,1.0,0.1,200.0);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.2f, 0.6f, 0.6f, 1.0f);
    initGame();
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int i,j,k;
    float f=3.0f,g,h;
    //gluLookAt(x,-5.0,10,0.0,0.0,0.0,0.0,1.0,0.0);
    for (i=0;i<30;i++){
    	g=i*0.3f-3.0f;
    	k=60-i*1.2f;
    	h=360.0f/k;
    	for (j=0;j<k;j++){
    		glLoadIdentity();
    		gluLookAt(x,-5.0,y,0.0,0.0,0.0,0.0,1.0,0.0);
    		//glTranslatef(0,0,-10);
    		//glRotatef(angle,0,0,x);
    		glRotatef(j*h,0.0f,1.0f,0.0f);
    		glTranslatef(f,g,0.0f);
    		glutSolidSphere(0.05,10,10);
		}
		f*=0.93f;
	}
    glutSwapBuffers();
}

void timer(int value){
	x=10*sin(angle*3.14/180);
	y=10*cos(angle*3.14/180);
	angle-=1.0f;
	glutPostRedisplay();
	glutTimerFunc(15,timer,0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
    glutInitWindowPosition(POSX, POSY);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("-----");
    initGL();
    //glutMotionFunc(Motion);
    glutTimerFunc(0,timer,0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
