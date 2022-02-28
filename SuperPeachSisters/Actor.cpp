#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>

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
    }

    if(time_to_recharge_before_next_fire > 0){
        time_to_recharge_before_next_fire--;
    }


    if(!getWorld()->blockingObjectAt(getX(),getY())){
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
            case KEY_PRESS_SPACE:
                if(hasShootPower()){
                    if(time_to_recharge_before_next_fire <= 0){
                        getWorld()->playSound(SOUND_PLAYER_FIRE);
                        if(getDirection() == 0){
                            getWorld()->createPeachFireBall(getX()+4, getY(), 0);
                            time_to_recharge_before_next_fire = 8;
                        }if(getDirection() == 180){
                            getWorld()->createPeachFireBall(getX()-4, getY(), 180);
                            time_to_recharge_before_next_fire = 8;
                        }
                    }
                }
            break;

            default:
            break;
            }
    }
    return;

}// end of peach dosomething

void Peach::bonk(){
    if(hasStarPower() || isTempInvincible()){
        return;
    }
    m_hitPoints--;
    tempInvincibleTime = 10;
    if(hasShootPower()){
        m_shootPower = false;
    }
    if(hasJumpPower()){
        m_jumpPower = false;
    }
    if(m_hitPoints >= 1){
        getWorld()->playSound(SOUND_PLAYER_HURT);
    }
    if(m_hitPoints <= 0){
        setDie();
    }

}

void DynamicItems::dofireBallThing(){
     if(!getWorld()->blockingObjectAt(getX(),getY()-2)){
            moveTo(getX(), getY()-2);
        }

    if(getDirection() == 0){
        if(getWorld()->blockingObjectAt(getX()+2, getY())){
            setDie();
            return;
        }else{
            moveTo(getX()+2, getY());
        }
    }else if(getDirection() == 180){
        if(getWorld()->blockingObjectAt(getX()-2, getY())){
            setDie();
            return;
        }else{
            moveTo(getX()-2, getY());
        }
    }
}

void DynamicItems::doSomething(){

    if(getWorld()->damageOverlapEnemy(this)){   // good now, don't change
        setDie();
        return;
    }
    dofireBallThing();

}

void Piranha_Fireball::doSomething(){
    if(getWorld()->overlapPeach(this)){
        getWorld()->bonkPeach(this);
        setDie();
        return;
    }
    dofireBallThing();
}

// goodie implementation:
void Goodie::GoodieMove(){

    if(!getWorld()->blockingObjectAt(getX(),getY()-2)){
        moveTo(getX(),getY()-2);
    }  // call movedown function maybe

    if(getDirection() == 0){
        if(getWorld()->blockingObjectAt(getX()+2, getY())){
            setDirection(180);
            return;
        }else{
            moveTo(getX()+2, getY());
        }
    }

    if(getDirection() == 180){
        if(getWorld()->blockingObjectAt(getX()-2, getY())){
            setDirection(0);
            return;
        }else{
            moveTo(getX()-2, getY());
        }
    }
}


void Mushroom::doSomething(){
    if(getWorld()->overlapPeach(this)){
        getWorld()->increaseScore(75);
        getWorld()->turnOnPeachJumpPower();
        getWorld()->setPeachHitPoints(2);
        setDie();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    GoodieMove();
}

void Flower::doSomething(){
    if(getWorld()->overlapPeach(this)){
        getWorld()->increaseScore(50);
        getWorld()->turnOnPeachShootPower();
        getWorld()->setPeachHitPoints(2);
        setDie();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    GoodieMove();
}

void Star::doSomething(){
    if(getWorld()->overlapPeach(this)){
        getWorld()->increaseScore(100);
        getWorld()->turnOnPeachStarPower();
        setDie();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    GoodieMove();
}



void Block::bonk(){

    if(!hasGoodie()){
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    if(hasGoodie()){
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        releaseGoodie();
    }
}  // todo!!!, implement block bonk


void Block::releaseGoodie(){
    if(m_hasFlower){
            getWorld()->createFlower(getX(),getY()+8);
            m_hasFlower = false;
        }
        if(m_hasMushroom){
            getWorld()->createMushroom(getX(),getY()+8);
            m_hasMushroom = false;
        }
        if(m_hasStar){
            getWorld()->createStar(getX(),getY()+8);
            m_hasStar = false;
        }
}


// Flag Start
void Flag::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getWorld()->overlapPeach(this)){
        getWorld()->increaseScore(1000);
        setDie();
        getWorld()->setCurLevelFinished();
    }
}

// Mario start

void Mario::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getWorld()->overlapPeach(this)){
        getWorld()->increaseScore(1000);
        setDie();
        getWorld()->setSavedMario();
    }
}


// goomba start
void Enemy::doSomething(){
    if(!isAlive()){
        return;
    }
    if(getWorld()->overlapPeach(this)){
        getWorld()->bonkPeach(this);
        return;
    }

// goomba will move without dropping
    if(getDirection() == 0 && getWorld()->blockingObjectAt(getX()+1,getY())){
            setDirection(180);
    }
    if(getDirection() == 180 && getWorld()->blockingObjectAt(getX()-1,getY())){
            setDirection(0);
    }

    if(getDirection() == 0 && !getWorld()->blockingObjectAt(getX()+SPRITE_WIDTH,getY()-1) ){
            setDirection(180);
    }
    if(getDirection() == 180 && !getWorld()->blockingObjectAt(getX()-SPRITE_WIDTH,getY()-1)){
        setDirection(0);
    }


// step 5 in dosomthing
    if(getDirection() == 0){
        if (getWorld()->blockingObjectAt(getX()+1,getY()) ){
           return;
        }else{
            moveTo(getX()+1, getY());
        }
    }else if(getDirection() == 180){
        if (getWorld()->blockingObjectAt(getX()-1,getY()) ){
           return;
        }else{
            moveTo(getX()-1, getY());
        }

    }

}

void Piranha::doSomething(){
    if(!isAlive()){
        return;
    }
    increaseAnimationNumber();

    if(getWorld()->overlapPeach(this)){
        getWorld()->bonkPeach(this);
    }

    if(!getWorld()->isSameLevelWithPeach(this)){
        return;
    }
    if(getWorld()->isSameLevelWithPeach(this)){
        setDirection(getWorld()->getDirToPeach(this));
    }
    if(m_fireDelay > 0){
        m_fireDelay--;
        return;
    }else{
        if(getWorld()->withinAttackingDis(this)){
            getWorld()->createPiranhaFireBall(getX(), getY(), getDirection());
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            m_fireDelay = 40;
        }
    }

}
 // may be moved to enemy bonk virtual function !! todo later
void Enemy::bonk(){
    if(getWorld()->overlapPeach(this)){
            if(getWorld()->PeachHasStarPower()){
                getWorld()->playSound(SOUND_PLAYER_KICK);
                getWorld()->increaseScore(100);
                setDie();
            }
        }
        return;
}

// koopa start // different bonk with enemy
void Koopa::bonk(){
        if(getWorld()->overlapPeach(this)){
            if(getWorld()->PeachHasStarPower()){
                getWorld()->playSound(SOUND_PLAYER_KICK);
                getWorld()->increaseScore(100);
                setDie();
                getWorld()->createShell(getX(),getY(),getDirection());
            }
        }
        return;
}

void Enemy::getDamaged(){
    getWorld()->increaseScore(100);
    setDie();
}


void Koopa::getDamaged(){
    getWorld()->increaseScore(100);
    setDie();
    getWorld()->createShell(getX(),getY(),getDirection());
}





















