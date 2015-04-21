#ifndef GAMET_H_INCLUDED
#define GAMET_H_INCLUDED
#include "Target.h"
#include "Player.h"
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
        bool updateTimer();

    private:
        Target targets[10] =  {Target(1), Target(1), Target(1), Target(1), Target(1)};
        Target rubbish[10] =  {Target(1, true), Target(1, true), Target(1, true)};
        int level;
        int timer;
        int score;
        Player player;

};

GameT::GameT(){
/* Game usually starts on level 1. */
    level = 1;
    timer = 60;
    score = 0;
    player = Player();
}

GameT::GameT(int l){
    level = l;
    timer = 60;
    score = 0;
    player = Player();
    changeLevel(l);
}

void GameT::draw(){
/* Moves all the targets in the game.*/
    player.drawPlayer();
    if(level == 1 || level == 2){
        for(int i = 0; i < 2; i++){
            targets[i].moveL1();
        }
    } else if(level == 3){
        for(int i = 0; i < 2; i++){
            targets[i].moveL3();
        }
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

bool GameT::updateTimer(){
    timer--;
    if (timer <= 0)
        return true;
    else
        return false;
}
#endif // GAMET_H_INCLUDED
