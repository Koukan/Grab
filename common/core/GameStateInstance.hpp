#ifndef		_GAMESTATEINSTANCE_
#define 	_GAMESTATEINSTANCE_

#include "GameState.hpp"

class GameStateKeeper
{
  public:
    virtual ~GameStateKeeper(){}
    virtual GameState	*newInstance() = 0;
};

template <class T>
class GameStateInstance : public GameStateKeeper
{
  public:
   virtual GameState	*newInstance()
   {
     return new T;
   }
};

#endif		/* _GAMESTATEINSTANCE_ */
