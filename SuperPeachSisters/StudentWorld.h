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
  bool blockingObjectAt(double x, double y);
  void bonkObjectAt(double x, double y);
  bool overlap(Actor* a, Actor* b);
  bool noBlockingObjectAt(double x, double y);

  void createFlower(double lx, double ly);
  void createStar(double lx, double ly);
  void createMushroom(double lx, double ly);

private:
  Peach* m_peach;
  std::vector<Actor*> m_actors;

  bool m_finishCurLevel;
  bool m_savedMario;

};

#endif // STUDENTWORLD_H_
