#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void Peach::doSomething(){

    if(!isAlive()){
        return;
    }
    if(hasStarPower()){
        starPowerTime--;
        if(starPowerTime == 0){
            m_starPower = false;
        }
    }
    if(isTempInvincible()){
        tempInvincibleTime--;
        if(tempInvincibleTime == 0){
            m_tempInvincible = false;
        }
    }

    if(isInRecharge()){
        if(time_to_recharge_before_next_fire > 0){
            time_to_recharge_before_next_fire--;
        }
        if(time_to_recharge_before_next_fire == 0){
            m_canShoot = true;
        }
    }

    if(getWorld()->noBlockingObjectAt(getX(),getY())){
        getWorld()->bonkObjectAt(getX(),getY());
    }


     if(remaining_jump_distance > 0){
        if(getWorld()->blockingObjectAt(getX(), getY()+4)){
            getWorld()->bonkObjectAt(getX(), getY()+4);
            remaining_jump_distance = 0;
        }else{
            moveTo(getX(),getY()+4);
            remaining_jump_distance--;
        }

    }

        if(remaining_jump_distance == 0){
            if(!getWorld()->blockingObjectAt(getX(), getY()) && !getWorld()->blockingObjectAt(getX(), getY()-1) && !getWorld()->blockingObjectAt(getX(), getY()-2) && !getWorld()->blockingObjectAt(getX(), getY()-3) ){
                moveTo(getX(), getY()-4);
            }
        }




    int ch;
	if (getWorld()->getKey(ch))
	{
        switch(ch){
            case KEY_PRESS_LEFT:
                setDirection(180);
                if(getWorld()->blockingObjectAt(getX()-4,getY())){
                    getWorld()->bonkObjectAt(getX()-4, getY());
                }
                 if(!getWorld()->blockingObjectAt(getX()-4,getY())){
                    moveTo(getX()-4,getY());
                }
            break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if(getWorld()->blockingObjectAt(getX()+4,getY())){
                    getWorld()->bonkObjectAt(getX()+4, getY());
                }
                 if(!getWorld()->blockingObjectAt(getX()+4,getY())){
                    moveTo(getX()+4,getY());
                }
            break;
            case KEY_PRESS_UP:
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                 if(getWorld()->blockingObjectAt(getX(),getY()-1)){
                    if(hasJumpPower()){
                        remaining_jump_distance = 12;
                    }else{
                        remaining_jump_distance = 8;
                    }
                 }
            break;

            default:
                break;
            }
    }
    return;

}

void Peach::bonk(){

} // todo

void Block::bonk(){

    if(!hasGoodie()){
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    if(hasGoodie()){
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        releaseGoodie();
    }
}


void Block::releaseGoodie(){
    if(m_hasFlower){
            getWorld()->createFlower(getX(),getY()+8);
            m_hasGoodie = false;
        }
        if(m_hasMushroom){
            getWorld()->createMushroom(getX(),getY()+8);
            m_hasGoodie = false;
        }
        if(m_hasStar){
            getWorld()->createStar(getX(),getY()+8);
            m_hasGoodie = false;
        }
}









