#pragma once

#include <list>
#include <map>
#include <string>

class TimeEffectGroup
{
  public:
   TimeEffectGroup();

   // setter
   void			updateTime(double time);
   void			setTimeEffect(double timeEffect = 1);

   // getter
   double		getTime() const;
   double		getElapseTime() const;
   double		getTimeEffect() const;

  private:
   double		_timeEffect;
   double		_time;
   double		_elapseTime;
};

class TimeEffectManager
{
  public:
    TimeEffectManager();
    ~TimeEffectManager();

    void		updateTime(double time);

    // setter
    void		setTimeEffect(std::string const &name = "default",
		    		      double timeEffect = 1);

    // getter
    double				getTime(std::string const &name = "default");
    double				getElapseTime(std::string const &name = "default");
    double				getTimeEffect(std::string const &name = "default");
    TimeEffectGroup		*getTimeEffectGroup(std::string const &name = "default");

  private:
    std::map<std::string, TimeEffectGroup*>	_timeEffectMap;
};
