#ifndef		_GAMESTATEINSTANCE_
#define 	_GAMESTATEINSTANCE_

#include "GameState.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ GameStateKeeper
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

CORE_END_NAMESPACE

#endif		/* _GAMESTATEINSTANCE_ */
