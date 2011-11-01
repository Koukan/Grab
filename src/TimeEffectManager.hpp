#pragma once

#include <list>
#include <map>
#include <string>

class TimeEffectGroup
{
  public:
   TimeEffectGroup();
   double		getTimeEffect();
   void			setTimeEffect(double timeEffect = 1);

  private:
   double		_timeEffect;
};

class TimeEffectManager
{
  public:
    TimeEffectManager();
    ~TimeEffectManager();
    double		getTimeEffect(std::string const &name = "default");
    TimeEffectGroup	*getTimeEffectGroup(std::string const &name = "default");
    void		setTimeEffect(std::string const &name = "default",
		    		      double timeEffect = 1);

  private:
    std::map<std::string, TimeEffectGroup*>	_timeEffectMap;
};
