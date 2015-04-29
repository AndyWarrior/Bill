#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include "GameT.h"

#include "Imageloader.h"
int level = 0;
double width, height;
GameT game;
char color;
int moveT;
bool handMove = false;
bool jumpMove = false;
int moveJ = 0;
double lx = -1.2;
double ly = -2;
double rx = 1.2;
double ry = -2;
double bj = -2;
static GLuint texName[7];
#include <iostream>
using namespace std;


//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}



void initRendering()
{GLuint i=0;
    GLfloat ambientLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {1.9f, 1.9f, 1.9f, 1.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(7, texName); //Make room for our texture
    Image* image;

    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\red.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\blur.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\green.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\menu2.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\inst.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\final.bmp");loadTexture(image,i++);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\white.bmp");loadTexture(image,i++);

    delete image;
}

void init(void)
{
    glClearColor (0.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    game.initRendering();
    width = 640;
    height= 480;
    PlaySound(TEXT("C:\\Users\\Andres\\Documents\\Programas\\Bill\\DigitalStream.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void mainMenu(){
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(0, 0, 3.0f);
    switch (level) {
            case 0: glBindTexture(GL_TEXTURE_2D, texName[3]);
                      break;
            case 4: glBindTexture(GL_TEXTURE_2D, texName[4]);
                      break;
            case 5: glBindTexture(GL_TEXTURE_2D, texName[5]);
                      break;
        }

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.85f, -1.4f, 0);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.85f, -1.4f, 0);

        glTexCoord2f(1.0f, 1.0f);//si se cambia a 2, aparecen dos imágenes al mismo tiempo en la pantalla
        glVertex3f(1.85f, 1.4f, 0);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.85f, 1.4f, 0);
    glEnd();

    glPopMatrix();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(level == 0 || level == 4 || level == 5){
        mainMenu();
    } else {

        //Bill's body
        glPushMatrix();
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        GLUquadricObj *qobj;

        switch (game.getColor()) {
            case 'r': glBindTexture(GL_TEXTURE_2D, texName[0]);
                      break;
            case 'b': glBindTexture(GL_TEXTURE_2D, texName[1]);
                      break;
            case 'g': glBindTexture(GL_TEXTURE_2D, texName[2]);
                      break;
        }

        //body
        glPushMatrix();
        qobj = gluNewQuadric();
        glTranslatef(0.0f, bj, 0);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluSphere(qobj, 1.2, 25, 20);
        glPopMatrix();

        //left hand
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[6]);
        qobj = gluNewQuadric();
        glTranslated(lx, ly, 0);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluSphere(qobj, 0.35, 25, 20);
        glPopMatrix();

        //right hand
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[6]);
        qobj = gluNewQuadric();
        glTranslatef(rx, ry, 0);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluSphere(qobj, 0.35, 25, 20);
        //glutSolidSphere(1.0,10,10);
        glPopMatrix();

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);

        glPopMatrix();

        game.draw();
    }
    glutSwapBuffers();
}

void startGame(int l){
    level = l;
    game = GameT(level);
    color = game.getColor();
    glutPostRedisplay();
}

void timer(int v){
    if(handMove){
        if(moveT < 5){
            moveT++;
        } else {
            moveT = 0;
            lx = -1.2;
            ly = -2;
            rx = 1.2;
            ry = -2;
            handMove = false;
        }
    }
    if(jumpMove){
        if(moveJ < 2){
            moveJ++;
        } else {
            moveJ = 0;
            bj = -2;
            jumpMove = false;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 1);

}

void timer2 (int v)
{
    if(level == 1 || level == 2 || level == 3){
        if(game.updateTimer()){
            startGame(level);
            //level = 0;
            //inGame = false;
        }
    }
    glutTimerFunc(1000, timer2, 1);

}

void reshape (int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    gluPerspective(69.0, (float)w / (float)h, 1.0, 18.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    //alejamos la camara
    /*Frustum top part is smaller to have the center higher */
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);


}



void clic(int button, int state, int x, int y)
{
    if(level == 0){
        y -= (height/2);
        cout << x << ", " << (y+(height/2)) << " " << (height*.15) << endl;
        if(y >= height/160 && y <= height/9 - height/480 ){ //level two
            cout << "hola" << endl;
            startGame(2);
        } else if(y >= -1*(((height/2)*.10)+height/8) && y <= -1*(((height/2)*.10)+7)){ //level one
            cout << "toop" << (((height/2)*.10)+10) << endl;
            startGame(1);
        }else if(y <= (((height/2)*.10)+height/4) && y >= (((height/2)*.10)+height/8 + height/48)){ //level three
            cout << "gaaah" << endl;
            startGame(3);
        }else if(x >= (width - (width*.20)) && (y+(height/2)) <=  (height*.15)){
            cout << "instructions" << endl;
            level = 4;
        }
    } else if(level == 4 || level == 5){
        cout << x << ", " << y << endl;
        if(x <= width*.20 && y >=  (height -(height*.15))){
            cout << "instructions" << endl;
            level = 0;
        }
    }
}

void key_Stroke(unsigned char key, int xs, int ys)
{
    switch(key){
        case '1':
            startGame(1);
            break;
        case '2':
            startGame(2);
            break;
        case '3':
            startGame(3);
            break;
        case 'l':
            lx = -3;
            ly = 0;
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            handMove = true;
            break;

        case 's':
            lx = -3;
            ly = 2;
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            handMove = true;
            break;

        case 'c':
            lx = -1;
            ly = 2;
            rx = 1;
            ry = 2;
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            handMove = true;
            break;

        case 'o':
            rx = 3;
            ry = 2;
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            handMove = true;
            break;

        case 'r':
            rx = 3;
            ry = 0;
            if(game.checkHit(key)){
                cout << "HIIIT" << endl;
            }
            handMove = true;
            break;

        case 'j':
        /* Only way the player can change color is by jumping */
            bj = -1.5;
            jumpMove = true;
            game.changeColor();
            color = game.getColor();
            break;

        case 'q':
        case 'Q':
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    initRendering();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(clic);
    glutTimerFunc(300, timer, 1);
    glutTimerFunc(1000, timer2, 1);

    glutKeyboardFunc(key_Stroke);
    glutMainLoop();
    return 0;
}
