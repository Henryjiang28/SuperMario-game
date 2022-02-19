#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Level.h"
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_peach = nullptr;
}

int StudentWorld::init()
{

    m_finishCurLevel = false;

    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    oss << setw(2) << to_string(getLevel());
 string level_file = "level" + oss.str() + ".txt";
 Level::LoadResult result = lev.loadLevel(level_file);

 if (result == Level::load_fail_file_not_found)
    cerr << "Could not find "<<level_file<< " data file" << endl;
 else if (result == Level::load_fail_bad_format)
    cerr << level_file << " is improperly formatted" << endl;
 else if (result == Level::load_success)
    {
    cerr << "Successfully loaded level" << endl;
    for(int x = 0; x<32; x++){
            for(int y = 0; y<32; y++){
                    Level::GridEntry ge;
                ge = lev.getContentsOf(x, y);
                switch (ge)
                {
                    case Level::empty:
                        cout << "Location " << x << " " << y << " is empty" << endl;
                        break;
                    case Level::koopa:
                        cout << "Location " << x << " " << y << " starts with a koopa" << endl;
                        break;
                    case Level::goomba:
                        cout << "Location " << x << " " << y << " starts with a goomba" << endl;
                        break;
                    case Level::piranha:
                        cout << "Location " << x << " " << y << " starts with a goomba" << endl;
                        break;
                    case Level::peach:
                        cout << "Location " << x << " " << y << " is where Peach starts" << endl;
                        m_peach = new Peach(this, x, y);
                        m_actors.push_back(m_peach);
                        break;
                    case Level::mario:
                        cout << "Location " << x << " " << y << " is where Peach starts" << endl;
                        break;
                    case Level::flag:
                        cout << "Location " << x << " " << y << " is where a flag is" << endl;
                        m_actors.push_back(new Flag(this, x , y));
                        break;
                    case Level::block:
                        cout << "Location " << x << " " << y << " holds a regular block" << endl;
                        m_actors.push_back(new Block(this, x, y));
                        break;
                    case Level::star_goodie_block:
                        cout << "Location " << x << " " << y << " has a star goodie block" << endl;
                        m_actors.push_back(new Block(this, x, y, false, true, false));
                        break;
                    case Level::flower_goodie_block:
                        cout << "Location " << x << " " << y << " has a star goodie block" << endl;
                        m_actors.push_back(new Block(this, x, y, false, false, true));
                        break;
                    case Level::mushroom_goodie_block:
                        cout << "Location " << x << " " << y << " has a star goodie block" << endl;
                        m_actors.push_back(new Block(this, x, y, true, false, false));
                        break;
                    case Level::pipe:
                        cout << "Location " << x << " " << y << " is where a pipe is" << endl;
                        m_actors.push_back(new Pipe(this,x,y));
            // etc…
                }

            }
        }

    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::createFlower(double x, double y){
    m_actors.push_back(new Flower(this, x/SPRITE_WIDTH, y/SPRITE_HEIGHT));
    // todo
}
void StudentWorld::createStar(double x, double y){
    m_actors.push_back(new Star(this, x/SPRITE_WIDTH, y/SPRITE_HEIGHT));
    // todo
}
void StudentWorld::createMushroom(double x, double y){
    m_actors.push_back(new Mushroom(this, x/SPRITE_WIDTH, y/SPRITE_HEIGHT));
    // todo
}


 int StudentWorld::move()
{
    for(auto it = m_actors.begin(); it != m_actors.end(); it++){          // auto autoConverts type
        if((*it)->isAlive() == true){
            (*it)->doSomething();
        }

        if( m_peach->isAlive() == false ){
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }

        if (m_finishCurLevel) {             // set to true when peach reaches overlap with flag
				playSound(SOUND_FINISHED_LEVEL);
				return GWSTATUS_FINISHED_LEVEL;
			}
        if(m_savedMario) {
                playSound(SOUND_GAME_OVER);
                return GWSTATUS_PLAYER_WON;
        }

    }

    for(auto it = m_actors.begin(); it != m_actors.end(); it++){
            if ( (*it) ->isAlive() == false) {

                delete *it;                 // remove object
                m_actors.erase(it);             // erase that slot and reallocate pointer
                it = m_actors.begin();        // put it back to the beginning
            }

	    }
        // Lives: 2 Level: 5 Points: 500 StarPower! JumpPower!
    ostringstream oss;

    oss << "Lives: ";
	oss << getLives() << " ";

    oss.fill('0');
    oss << "Level: ";
    oss << setw(2) << getLevel() << " ";

    oss.fill('0');
    oss << "Points: ";
    oss << setw(6) << getScore() << " ";

    if(m_peach->hasStarPower())
        oss << "StarPower! ";
    if(m_peach->hasJumpPower())
        oss<<"JumpPower! ";
    if(m_peach->hasShootPower())
        oss<<"ShootPower! ";
    if(m_peach->isTempInvincible())
        oss<<"Invincible! ";

    setGameStatText(oss.str());

// TODO
     return GWSTATUS_CONTINUE_GAME;

//     // This code is here merely to allow the game to build, run, and terminate after you hit enter.
//     // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

} // end of move() function

void StudentWorld::cleanUp()
{

    for(Actor* actor : m_actors){
        delete actor;
    }
    m_peach = nullptr;
    m_actors.clear(); // reset size to 0;
}

StudentWorld::~StudentWorld() {
	cleanUp();
}


bool StudentWorld::blockingObjectAt(double x, double y) {

	for (Actor* actor: m_actors){
        if(actor->isAlive() && actor->blockMovement()){
            if (x < actor->getX() + (SPRITE_WIDTH)  && x > actor->getX() - (SPRITE_WIDTH) )
                if((y > actor->getY() - (SPRITE_HEIGHT) && y < actor->getY() + (SPRITE_HEIGHT)) )
                    return true;
        }

    }
	return false;
}

bool StudentWorld::overlap(Actor* a, Actor* b){
    if ((a->getX() + SPRITE_WIDTH > b->getX() && a->getX() - SPRITE_WIDTH < b->getX())){
        if(a->getY() + SPRITE_HEIGHT > b->getY() && a->getY() - SPRITE_HEIGHT < b->getY()){
            return true;
        }
    }
    return false;
}

void StudentWorld::bonkObjectAt(double x, double y){
    for (Actor* actor: m_actors){
        if (x < actor->getX() + (SPRITE_WIDTH)  && x > actor->getX() - (SPRITE_WIDTH) ){
            if((y > actor->getY() - (SPRITE_HEIGHT) && y < actor->getY() + (SPRITE_HEIGHT)) ){
                actor->bonk();
            }
        }

    }
    return;
}

bool StudentWorld::noBlockingObjectAt(double x, double y){
    for (Actor* actor: m_actors){
        if(actor->isAlive() && !actor->blockMovement()){
            if (x < actor->getX() + (SPRITE_WIDTH)  && x > actor->getX() - (SPRITE_WIDTH) )
                if((y > actor->getY() - (SPRITE_HEIGHT) && y < actor->getY() + (SPRITE_HEIGHT)) )
                    return true;
        }
    }
	return false;
}


bool StudentWorld::overlapPeach(Actor* me) {
	for (Actor* a : m_actors)
		if (a!= me && a->isAlive() && a->isPeach() && overlap(a, me)){
            if (a->isAlive() && overlap(a, me)){
                return true;
            }

        }
	return false;
}






