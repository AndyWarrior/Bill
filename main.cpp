#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include "GameT.h"

int level = 0;
double width, height;
GameT game;
char color;
#include <iostream>
using namespace std;

void init(void)
{
    glClearColor (0.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void mainMenu(){
    glColor3ub(255,135,100);
    glPointSize(40.0f);
    glBegin(GL_POINTS);
        glColor3ub(35, 100, 245);
        glVertex3d(0,0,0);

        glVertex3d(0, .75, 0);
        glColor3ub(245, 100, 35);

        glColor3ub(10, 200, 35);
        glVertex3d(0, -0.75, 0);

    glEnd();
}
void display(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(level == 0){
        mainMenu();
    } else {
        glColor3ub(255,135,100);
        glPointSize(10.0f);
        glBegin(GL_POINTS);
            if(color == 'b'){
                glColor3ub(35, 100, 245);
            } else if(color == 'r'){
                glColor3ub(245, 100, 35);
            } else {
                glColor3ub(10, 200, 35);
            }
            glVertex3d(0,0,0);
            //left corner
            glVertex3d(-1, .5, 2);
            //right corner
            glColor3ub(255,0,0);
            glVertex3d(1, .5, 0);
            //left
            glColor3ub(0,255,0);
            glVertex3d(-1,-0.25, 0);
            //right
            glColor3ub(0,0,255);
            glVertex3d(1,-0.25, 0);
            //center
            glColor3ub(0,135,0);
            glVertex3d(0, 0.5, 0);
        glEnd();

        //Bill's body
        glPushMatrix();
        glTranslated(0,-2,0);
        glColor3ub(110,10,255);
         glScalef(4,4,4);
        glutSolidSphere(.45,16,16);
        glPopMatrix();

        glColor3ub(255,135,100);
        glPointSize(20.0f);
        game.draw();
    }
    glutSwapBuffers();
}

void timer (int v)
{
    glutPostRedisplay();
    glutTimerFunc(100, timer, 1);

}

void reshape (int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();


    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    //alejamos la camara
    /*Frustum top part is smaller to have the center higher */
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);


}

void startGame(int l){
    level = l;
    game = GameT(level);
    color = game.getColor();
    glutPostRedisplay();
}

void clic(int button, int state, int x, int y)
{
    y -= (height/2);
    cout << x << ", " << y << endl;
    if(y >= -20 && y <= 20 ){ //level two
        cout << "hola" << endl;
        startGame(2);
    } else if(y >= -1*(((height/2)*.10)+50) && y <= -1*(((height/2)*.10)+10)){ //level one
        cout << "toop" << endl;
        startGame(1);
    }else if(y <= (((height/2)*.10)+50) && y >= (((height/2)*.10)+10)){ //level three
        cout << "gaaah" << endl;
        startGame(3);
    }
}

void key_Stroke(unsigned char key, int xs, int ys)
{
    switch(key){
        case 'l':
        case 's':
        case 'c':
        case 'o':
        case 'r':
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            break;

        case 'j':
        /* Only way the player can change color is by jumping */
            game.changeColor();
            color = game.getColor();
            break;

        case 'q':
        case 'Q':
        case 27:
            exit(0);
            break;
    }

}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (600, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(clic);
    glutTimerFunc(300, timer, 1);

    glutKeyboardFunc(key_Stroke);
    glutMainLoop();
    return 0;
}
