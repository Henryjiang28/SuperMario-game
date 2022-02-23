#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"


class StudentWorld;

class Actor : public GraphObject{               // all actors are alive
public:
    Actor(StudentWorld* world_ptr, int imageID, double startX, double startY, int dir, int depth)
    :GraphObject(imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, dir, depth), m_world(world_ptr), alive(true){}

    StudentWorld* getWorld(){return m_world;}
    virtual void doSomething() = 0;                     // all actors has doSomething
     bool isAlive(){return alive;}
     virtual bool blockMovement() = 0;
     virtual bool canBeDamaged(){return false;}
      virtual void bonk(){return;}
      virtual bool hasGoodie(){return false;}
      virtual bool isPeach(){return false;}
      virtual void setDie() { alive = false;}
      virtual void getDamaged(){};
      virtual bool isEnemy(){return false;}
    

private:
    StudentWorld* m_world;
    bool alive;
};



class Peach : public Actor{
    public:
        Peach(StudentWorld* world_ptr, double lx, double ly): // ptr to the student world is needed to access functions
            Actor(world_ptr, IID_PEACH, lx, ly, 0, 0),
            m_hitPoints(1), m_shootPower(false),m_jumpPower(false),m_starPower(false),remaining_jump_distance(0),starPowerTime(0)
            ,m_tempInvincible(false),tempInvincibleTime(0){}
            // change shoot power to false!!!! , teseting only


    virtual void doSomething();
    virtual void getDamaged(){ bonk(); }   // same with getting bonked.
    virtual bool blockMovement(){return false;}
    virtual void bonk();
    bool hasStarPower(){return m_starPower;}
    bool hasJumpPower(){return m_jumpPower;}
    bool hasShootPower(){return m_shootPower;}
    bool isTempInvincible(){return m_tempInvincible;}
    bool canShoot(){return m_canShoot;}
    void turnOnShootPower(){m_shootPower = true;};
    void turnOnJumpPower(){m_jumpPower = true;}
    void setHitPoints(int num){m_hitPoints = num;}
    void turnOnStarPower(){m_starPower = true; starPowerTime = 150;}

    virtual bool isPeach(){return true;}
    virtual bool canBeDamaged(){return true;}

    private:
        int m_hitPoints;
        bool m_shootPower, m_jumpPower,m_starPower, m_tempInvincible, m_canShoot;
        int remaining_jump_distance;
        int starPowerTime;
        int tempInvincibleTime;
        int time_to_recharge_before_next_fire;

};

// _____________________________________________________
// immobilized: pipe and Block
class Immobilized : public Actor{
    public:
     Immobilized(StudentWorld* world_ptr, int imageID, double lx, double ly):
     Actor(world_ptr, imageID, lx, ly, 0, 2){}

     virtual bool blockMovement(){return true;}
     virtual bool canBeDamaged(){return false;}

     private:


};

class Block : public Immobilized{
    public:
        Block(StudentWorld* world_ptr, double lx, double ly, bool Mushroom = false, bool Star = false, bool Flower = false)
        :Immobilized(world_ptr, IID_BLOCK, lx, ly), m_hasMushroom(Mushroom),m_hasStar(Star),m_hasFlower(Flower)
        {}

    virtual void doSomething(){return;};
    virtual bool blockMovement(){return true;}
    virtual void bonk(); // To Do !!!!!
    bool hasGoodie(){return m_hasFlower || m_hasMushroom || m_hasStar;}


    private:
     bool m_hasMushroom;
     bool m_hasStar;
     bool m_hasFlower;
     void releaseGoodie();
};

class Pipe : public Immobilized{
    public:
        Pipe(StudentWorld* world_ptr, double lx, double ly)
        :Immobilized(world_ptr, IID_PIPE, lx, ly)
        {}

    virtual void doSomething(){return;}
    virtual void bonk(){return;}
    virtual bool blockMovement(){return true;}

};






// ______________________________________________________
//  interactItems class.
//

class interactItems : public Actor{
    public:
        interactItems(StudentWorld* world_ptr, int imageID, double lx, double ly, int dir, int depth) :
		Actor(world_ptr, imageID, lx, ly, dir, depth){};

    virtual bool blockMovement(){return false;}
    virtual bool canBeDamaged(){return false;}

};

// ________________________________________________________

class Flag : public interactItems{
    public:
        Flag(StudentWorld* world_ptr, double lx, double ly)
        :interactItems(world_ptr, IID_FLAG, lx, ly, 0, 1){}

        virtual void doSomething();
        virtual void bonk(){return;}

    private:

};


class Mario : public interactItems{
    public:
        Mario(StudentWorld* world_ptr, double lx, double ly)
        :interactItems(world_ptr, IID_MARIO, lx, ly, 0, 1){}

        virtual void doSomething();
        virtual void bonk(){return;}

    private:

};



// ______________________________________________________
//  Goodie class extends interactItems

class Goodie : public interactItems{
    public:
        Goodie(StudentWorld* world_ptr, int imageID, double lx, double ly)
        :interactItems(world_ptr, imageID, lx, ly, 0, 1){}

    virtual void bonk(){return;}

    protected:
        void GoodieMove();
};

// ________________________________________________________



class Flower : public Goodie{
    public:
        Flower(StudentWorld* world_ptr, double lx, double ly)
        :Goodie(world_ptr, IID_FLOWER, lx, ly){}

        virtual void doSomething();



};

class Mushroom : public Goodie{
    public:
        Mushroom(StudentWorld* world_ptr, double lx, double ly)
        :Goodie(world_ptr, IID_MUSHROOM, lx, ly){}

    virtual void doSomething();



};

class Star : public Goodie{
    public:
        Star(StudentWorld* world_ptr, double lx, double ly)
        :Goodie(world_ptr, IID_STAR, lx, ly){}

        virtual void doSomething();


};



// dynamicItems extends interactItems maybe??
class dynamicItems : public interactItems{
    public:
        dynamicItems(StudentWorld* world_ptr, int imageID, double lx, double ly, int dir)
        :interactItems(world_ptr, imageID, lx, ly, dir, 1){}

    virtual void doSomething(){return;}
    virtual void bonk(){return;}

};


class Piranha_Fireball  : public dynamicItems{
    public:
        Piranha_Fireball(StudentWorld* world_ptr, double lx, double ly, int dir)
        :dynamicItems(world_ptr, IID_PIRANHA_FIRE, lx, ly, dir){}
    virtual void doSomething();

};



class Peach_Fireball : public dynamicItems{
    public:
        Peach_Fireball(StudentWorld* world_ptr, double lx, double ly, int dir)
        :dynamicItems(world_ptr, IID_PEACH_FIRE, lx, ly, dir){}

    virtual void doSomething();

};



class Shell : public dynamicItems{
    public:
        Shell(StudentWorld* world_ptr, double lx, double ly, int dir)
        :dynamicItems(world_ptr, IID_SHELL, lx, ly, dir){}
    virtual void doSomething();


};


// _--------  enemy class

class Enemy : public Actor{
    public:
        Enemy(StudentWorld* world_ptr, int imageId, double lx, double ly, int dir)
        :Actor(world_ptr, imageId, lx, ly, dir, 0){}

    virtual bool canBeDamaged(){return true;}
    virtual bool blockMovement(){return false;}
    virtual void getDamaged();      // shared betweem goomba and piranha
    virtual bool isEnemy(){return true;}
    virtual void doSomething();  // will be shared between goomba and koopa
    virtual void bonk();        // shared between goomba and Piranha
};

class Goomba : public Enemy{
    public:
        Goomba(StudentWorld* world_ptr, double lx, double ly, int dir)
        :Enemy(world_ptr, IID_GOOMBA, lx, ly, dir){}
};

class Koopa : public Enemy{
    public:
        Koopa(StudentWorld* world_ptr, double lx, double ly, int dir)
        :Enemy(world_ptr, IID_KOOPA, lx, ly, dir){}
    virtual void bonk();   // override enemy bonk               // creates shell
    virtual void getDamaged(); // override enemy getDamaged()   // creates shell
};

class Piranha : public Enemy{
    public:
        Piranha(StudentWorld* world_ptr, double lx, double ly, int dir)
        :Enemy(world_ptr, IID_PIRANHA, lx, ly, dir), m_fireDelay(0){}
    virtual void doSomething();  // shoots fireball
    // virtual void bonk();
    // virtual void getDamaged();  // maybe combined with goomba

    private:
        int m_fireDelay;

};






// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
