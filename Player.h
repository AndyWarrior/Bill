#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
using namespace std;
class Player{
    public:
        Player();
        void changeColor();
        char getColor();
        void setLevel(int l);
        void drawPlayer();

    private:
        char colors[3] = {'b', 'r', 'g'};
        int color;
        int level;
};
Player::Player(){
    color = 0;
    level = 1;
}

void Player::changeColor(){
/* Changes to the next color in level 1 checks if we are on the limit, 1, if so return it, same on level 2, with limit
* 2, and level 3, with limit 3. */
    cout << level << " " << color;
    if(level == color || (level == 3) && color == 2){
        color = 0;
    } else {
        color += 1;
    }
}

char Player::getColor(){
    return colors[color];
}

void Player::setLevel(int l){
    level = l;
}

void Player::drawPlayer(){
    glutSolidSphere(1,2,5);
}
#endif // PLAYER_H_INCLUDED
