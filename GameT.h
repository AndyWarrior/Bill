#ifndef GAMET_H_INCLUDED
#define GAMET_H_INCLUDED
#include "Target.h"
#include "Player.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
class GameT
{
    public:
        GameT();
        GameT(int l);
        void draw();
        bool checkHit(char pos);
        void changeLevel(int l);
        void changeColor();
        char getColor();
        void initRendering();
         bool updateTimer();
         void Score();

    private:
        Target targets[5] =  {Target(1), Target(1), Target(1), Target(1), Target(1)};
        Target rubbish[3] =  {Target(1, true), Target(1, true), Target(1, true)};
        int level;
        int timer;
        int score;
        double wWidth;
        double wHeight;
        Player player;
        GLubyte numbers[10] = { '0', '1', '2', '3','4', '5', '6', '7', '8', '9'};
        GLint arr[5] = {0,0,0,0,0};

};

GameT::GameT(){
/* Game usually starts on level 1. */
    level = 1;
    timer = 10;
    score = 0;
    player = Player();
}

GameT::GameT(int l){
    level = l;
    timer = 10;
    score = 0;
    player = Player();
    changeLevel(l);
    wWidth = 640;
    wHeight = 480;
}

void GameT::draw(){
/* Moves all the targets in the game.*/
    Score();
   // if(level == 1 || level == 2){
        for(int i = 0; i < 2; i++){
            targets[i].moveL1();
        }
  //  } else
     if(level == 3){
      /*  for(int i = 0; i < 2; i++){
            targets[i].moveL3();
        }*/
        for(int i = 0; i < 2; i++){
            rubbish[i].moveL3();
        }
    }

}

bool GameT::checkHit(char pos){
/* Checks all the targets in the game to see if the user hit any of them, in case it did it returns true, otherwise it
* returns false. Still missing: color. */
    for(int i = 0; i < 2; i++){
        if(targets[i].hit(pos, player.getColor())){
            score += 50;
            cout << score << endl;
            return true;
        }
    }
    return false;
}

void GameT::changeLevel(int l){
    level = l;
    player.setLevel(l);
    for(int i = 0; i < 5; i++){
        targets[i].setLevel(l);
    }
}

char GameT::getColor(){
    return player.getColor();
}

void GameT::changeColor(){
    player.changeColor();
}

void GameT::initRendering(){
    for(int i = 0; i < 3; i++){
           targets[i].initRendering();
    }
}

bool GameT::updateTimer(){
    timer--;
    if (timer <= 0){
        return true;
    } else {
        int aux = timer, i=0;
        while(aux > 0){
            arr[i] = aux % 10;
            aux = aux/10;
            i++;
        }
        if(arr[2] >= 6){
            timer = 0;
            arr[2] = 0;
            arr[3] += 1;
            if(arr[3] > 9){
                arr[3] = 0;
                arr[4] += 1;
            }
        }
        return false;
    }
}

void GameT::Score(){
    double xRaster = -3.5;
    glColor3ub(255,255,255);
    //left score
    glRasterPos2d(xRaster, 3);
    int aux = score ;
    do{
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, numbers[(aux % 10)]);
        aux = aux/10;
        xRaster -= .15;
        glRasterPos2d(xRaster, 3);
    }while(aux > 0);
    int one = arr[0];
    int two = arr[1];
     glRasterPos2i(3.5,3);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, numbers[two]); //D
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, numbers[one]); //C

}
#endif // GAMET_H_INCLUDED
