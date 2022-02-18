#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void Peach::doSomething(){
    int ch;
	if (getWorld()->getKey(ch))
	{
        switch(ch){
            case KEY_PRESS_LEFT:
                setDirection(180);
                 if(getWorld()->overlap(getX()-4,getY()) == false){
                    moveTo(getX()-4,getY());
                }
            break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                 if(getWorld()->overlap(getX()+4,getY()) == false){
                    moveTo(getX()+4,getY());
                }
            break;
            case KEY_PRESS_UP:
                 if(getWorld()->overlap(getX(),getY()+8) == false){
                    moveTo(getX(),getY()+8);
               }
            break;

            default:
                break;
            }
    }
return;
}

void Block::bonk(){

    if(!hasGoodie()){
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    if(hasGoodie()){
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
    } //TODO


}




