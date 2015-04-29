#ifndef TARGET_H
#define TARGET_H

#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <iostream>

#include "Imageloader.h"
using namespace std;
/*
* A target can only be in one of the 5 positions
* 1 = l = left
* 2 = s = left corner
* 3 = c = center
* 4 = o = right corner
* 5 = r = right
*/

class Target
{
    public:
        Target();
        Target(int l);
        Target(int l, bool ru);
        void drawTarget();
        void reset();
        void moveL1();
        void moveL3();
        void checkPos();
        bool hit(char po, char playerColor);
        void setPosition();
        void setColor();
        void setLevel(int l);
        void loadTexture(Image* image,int k);
        void initRendering();

    private:
        char position;
        int wdh;
        int hgt;
        double zI;
        double z;
        char color;
        int level;
        bool rubbish;
        char colors[4] = {'b', 'r', 'g'};
        static GLuint texName[3];

};

GLuint Target::texName[3] = {0};
Target:: Target(){
/*when you create a new target it randomly decides
* its position and color. According to the position they are in the width and the height values
* will be adapted and stored in wdh and hgt (they become the draw's x and y, respectively. The position is chosen by a random
* number between 1 and 5. Using a random the value for the color is defined. The default values for the width and height
* are the default values for the window. The starting value for z is a random number between -30 and -50. Once the
* position is defined and the values for wdh, hgt and z, we must call the draw method. */
    level = 1;
    rubbish = false;
    setColor();
    //color
    wdh = 1;
    hgt = 1;
    setPosition();
    drawTarget();
}

Target:: Target(int l){
/*when you create a new target it randomly decides
* its position and color. According to the position they are in the width and the height values
* will be adapted and stored in wdh and hgt (they become the draw's x and y, respectively. The position is chosen by a random
* number between 1 and 5. Using a random the value for the color is defined. The default values for the width and height
* are the default values for the window. The starting value for z is a random number. Once the
* position is defined and the values for wdh, hgt and z, we must call the draw method. */
     level = l;
    setColor();
    //color
    rubbish = false;
    wdh = 1;
    hgt = 1;
    setPosition();
    drawTarget();
}

Target:: Target(int l, bool ru){
/*Constructor for rubbish. */
     level = l;
    setColor();
    //color
    rubbish = ru;
    wdh = 1;
    hgt = 1;
    setPosition();
    drawTarget();
}

void Target::drawTarget(){
/* function that draws the target, right now it only draws a point in representation. */

        glPushMatrix();
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

        GLUquadricObj *qobj;
        //glBindTexture(GL_TEXTURE_2D, texName[1]);
         if(color == 'b'){
            glBindTexture(GL_TEXTURE_2D, texName[1]);
        } else if(color == 'r'){
            glBindTexture(GL_TEXTURE_2D, texName[0]);
        } else if(color == 'g'){
            glBindTexture(GL_TEXTURE_2D, texName[2]);
        } else {
            glBindTexture(GL_TEXTURE_2D, texName[0]);
        }

        //glPushMatrix();
        qobj = gluNewQuadric();
        glTranslated(0,0,z);
        glTranslated(wdh,hgt,zI);
         //glScalef(.45,.45,.01);
        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluSphere(qobj, 0.25, 25, 20);
        //glutSolidSphere(1.0,10,10);
        glPopMatrix();
       // glPopMatrix();


}

void Target::reset(){
/* This function reset the position of the target to a new one. According to the values of width
* and height, it makes the proper adjustments. It also gives it a new color depending on the current level. */

    wdh = 1;
    //color
    hgt = 1;
    setColor();
    setPosition();
}

void Target::checkPos(){
/* Checks the position of the target, if its past the camera it's values must be reseted. */
    if(z > 10){
        reset();
    }
}

void Target::moveL1(){
/* Moves the object forward, draws it and then checks if it needs to be reseted.*/
    z+=.5;
    drawTarget();
    checkPos();

}

void Target::moveL3(){
/* Moves the object forward faster, draws it and then checks if it needs to be reseted.*/
    z+=.5;

    drawTarget();
    checkPos();

}

bool Target::hit(char po, char playerColor){
/* Checks if the user hit the target, it does if they are in the same position and if the target is at least
* on a positive z. Check if they are the same color is still missing.*/
    if(po == position && playerColor == color){
        if(z >= 2 ){
            reset();
            return true;
        }
    }
    return false;
}

 void Target::setPosition(){
/* Generates a new starting z position for the target, as well as a new position */

     zI = (rand() % 5 + 5 ) * -1;
     z = zI;
     int po;
    po = rand() % 5 + 1;
    if(po == 1){
        position = 'l';
        wdh = -1;
        hgt = -0.25;
    } else if(po == 2){
        position = 's';
        wdh = -1;
    } else if(po == 3){
        position = 'c';
        wdh = 0;
    } else if(po == 4){
        position = 'o';
    } else {
        position = 'r';
        hgt = -0.25;
    }
 }

void Target::setColor(){
/* According to the current level, it assigns a color. */
    int rndC;
    if(rubbish){
        color = 'p'; //rubbish
    } else {
        if(level == 1){
             rndC = rand() % 2 ;
             color = colors[rndC];
        } else {
            rndC = rand() % 3;
             color = colors[rndC];
        }
    }
}

void Target::setLevel(int l){
/* Changes the current level. */
    level = l;
    setColor();
}

//Makes the image into a texture, and returns the id of the texture
void Target::loadTexture(Image* image,int k)
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

void Target::initRendering()
{
    GLuint i=0;
    //glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(3, texName); //Make room for our texture
    Image* image;


    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\target_red.bmp");loadTexture(image,0);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\target_blue.bmp");loadTexture(image,1);
    image = loadBMP("C:\\Users\\Andres\\Documents\\Programas\\Bill\\images\\target_green.bmp");loadTexture(image,2);


    delete image;
}

#endif // TARGET_H


#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    cout << filename << endl;
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find fileeee");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}
