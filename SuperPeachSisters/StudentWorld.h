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

  void createFlower(double x, double y);
  void createStar(double x, double y);
  void createMushroom(double x, double y);
  void createShell(double x, double y, int dir);
  void createPeachFireBall(double x, double y, int dir);
  void createPiranhaFireBall(double x, double y, int dir);
  void setCurLevelFinished(){m_finishCurLevel = true;}
  void setSavedMario(){m_savedMario = true;}
  bool overlapPeach(Actor* me);
  void bonkPeach(Actor* me);
  bool overlapDamageableItems(Actor* me);  // not including peach
  void damageItemAt(double x, double y);
  Peach* getPeach(){return m_peach;}
  bool damageOverlapEnemy(Actor* me);
  bool isSameLevelWithPeach(Actor* me);
  int getDirToPeach(Actor* me);
  bool withinAttackingDis(Actor* me);


private:
  Peach* m_peach;
  std::vector<Actor*> m_actors;

  bool m_finishCurLevel;
  bool m_savedMario;

};

#endif // STUDENTWORLD_H_
