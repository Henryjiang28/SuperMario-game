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
                    case Level::peach:
                        cout << "Location " << x << " " << y << " is where Peach starts" << endl;
                        m_peach = new Peach(this, x, y);
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


 int StudentWorld::move()
{

     m_peach->doSomething();

    for (auto iter = m_actors.begin(); iter != m_actors.end(); iter++) {
        if((*iter)->isAlive()){
            (*iter)->doSomething();
        }

        if( m_peach->isAlive() == false ){
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }

    }
     return GWSTATUS_CONTINUE_GAME;

//     // This code is here merely to allow the game to build, run, and terminate after you hit enter.
//     // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

}

void StudentWorld::cleanUp()
{

    delete m_peach;
    m_peach = nullptr;
    for(Actor* actor : m_actors){
        delete actor;
    }
    m_actors.clear(); // reset size to 0;
}

StudentWorld::~StudentWorld() {
	cleanUp();
}


bool StudentWorld::overlap(int x, int y) {

	for (Actor* actor: m_actors){

        if( (x < actor->getX() + (SPRITE_WIDTH - 1)  && x > actor->getX() - (SPRITE_WIDTH-1) ) &&
            ((y > actor->getY()- (SPRITE_HEIGHT-1) && y < actor->getY() + (SPRITE_HEIGHT-1) )) ) {
                return true;
            }
    }
	return false;
}


