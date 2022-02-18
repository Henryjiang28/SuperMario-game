#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"


class StudentWorld;

class Actor : public GraphObject{               // all actors are alive
public:
    Actor(StudentWorld* world_ptr, int imageID, int startX, int startY, int dir, int depth)
    :GraphObject(imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, dir, depth), m_world(world_ptr), alive(true){}

    StudentWorld* getWorld(){return m_world;}
    virtual void doSomething() = 0;                     // all actors has doSomething
     bool isAlive(){return alive;}
     virtual bool blockMovement() = 0;
     virtual bool canBeDamaged(){return false;}
      virtual void bonk(){return;}

private:
    StudentWorld* m_world;
    bool alive;
};



class Peach : public Actor{
    public:
        Peach(StudentWorld* world_ptr, int lx, int ly): // ptr to the student world is needed to access functions
            Actor(world_ptr, IID_PEACH, lx, ly, 0, 0),
            health(1), shootPower(false),jumpPower(false),starPower(false),invincible(false){}

    //bool block(){return false;}
    virtual void doSomething();
    virtual bool blockMovement(){return false;}
    virtual void bonk(){return;}

    private:
        int health;
        bool shootPower,jumpPower,starPower,invincible;

};

// _____________________________________________________
// immobilized: pipe and Block
class Immobilized : public Actor{
    public:
     Immobilized(StudentWorld* world_ptr, int imageID, int lx, int ly):
     Actor(world_ptr, imageID, lx, ly, 0, 2){}

     virtual bool blockMovement(){return true;}
     virtual bool canBeDamaged(){return false;}

     private:


};

class Block : public Immobilized{
    public:
        Block(StudentWorld* world_ptr, int lx, int ly)
        :Immobilized(world_ptr, IID_BLOCK, lx, ly)
        {}

    virtual void doSomething(){return;};
    virtual bool blockMovement(){return true;}
    virtual void bonk(); // To Do !!!!!
    void releaseGoodie();
    bool hasGoodie(){return m_hasGoodie;}

    private:
     bool m_hasGoodie;

};

class Pipe : public Immobilized{
    public:
        Pipe(StudentWorld* world_ptr, int lx, int ly)
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
        interactItems(StudentWorld* world_ptr, int imageID, int lx, int ly, int dir, int depth) :
		Actor(world_ptr, imageID, lx, ly, dir, depth){};

    virtual bool blockMovement(){return false;}

};

// ________________________________________________________

class Flag : public interactItems{
    public:
        Flag(StudentWorld* world_ptr, int lx, int ly)
        :interactItems(world_ptr, IID_FLAG, lx, ly, 0, 1){}

        virtual void doSomething(){return;}  // TO DO!!!
        virtual void bonk(){return;}
        virtual bool canBeDamaged(){return false;}

    private:

};


class Mario : public interactItems{
    public:
        Mario(StudentWorld* world_ptr, int lx, int ly)
        :interactItems(world_ptr, IID_MARIO, lx, ly, 0, 1){}

        virtual void doSomething(){return;}  // TO DO!!!
        virtual void bonk(){return;}
        virtual bool canBeDamaged(){return false;}

    private:

};



class Goodie : public interactItems{
    public:
        Goodie(StudentWorld* world_ptr, int imageID, int lx, int ly)
        :interactItems(world_ptr, imageID, lx, ly, 0, 1){}
};



class Flower : public Goodie{
    public:
        Flower(StudentWorld* world_ptr, int lx, int ly)
        :Goodie(world_ptr, IID_FLOWER, lx, ly){}

        virtual void doSomething(){return;}  // TO DO!!!
        virtual void bonk(){return;}
        virtual bool canBeDamaged(){return false;}

    private:

};

class Mushroom : public Goodie{
    public:
        Mushroom(StudentWorld* world_ptr, int lx, int ly)
        :Goodie(world_ptr, IID_MUSHROOM, lx, ly){}

        virtual void doSomething(){return;}  // TO DO!!!
        virtual void bonk(){return;}
        virtual bool canBeDamaged(){return false;}

    private:

};

class Star : public Goodie{
    public:
        Star(StudentWorld* world_ptr, int lx, int ly)
        :Goodie(world_ptr, IID_STAR, lx, ly){}

        virtual void doSomething(){return;}  // TO DO!!!
        virtual void bonk(){return;}
        virtual bool canBeDamaged(){return false;}

    private:

};








// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
