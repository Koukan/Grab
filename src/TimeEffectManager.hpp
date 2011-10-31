#pragma once

#include <list>
#include <map>
#include <string>

class TimeEffectGroup
{
  public:
   TimeEffectGroup();
   double		getTimeEffect();
   void			setTimeEffect(double timeEffect);
   void			removeTimeEffect();

  private:
   void			update(double timeEffect);
   double		_timeEffect;
   std::list<double>	_timeEffectList;
};

class TimeEffectManager
{
  public:
    TimeEffectManager();
    ~TimeEffectManager();
    TimeEffectGroup	*getTimeEffect(std::string const &name);
    void		setTimeEffect(std::string const &name, double timeEffect);
    void		removeTimeEffect(std::string const &name);

  private:
    std::map<std::string, TimeEffectGroup*>	_timeEffectMap;
};
