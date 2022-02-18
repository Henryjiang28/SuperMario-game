#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include <string>
#include <vector>
#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class Peach;

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  ~StudentWorld();
  bool overlap(int x, int y);

private:
  Peach* m_peach;
  std::vector<Actor*> m_actors;

};

#endif // STUDENTWORLD_H_
