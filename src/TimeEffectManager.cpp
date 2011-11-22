#include "TimeEffectManager.hpp"

TimeEffectGroup::TimeEffectGroup()
	: _timeEffect(1), _time(0)
{
}

void		TimeEffectGroup::updateTime(double time)
{
  _elapseTime = time * _timeEffect;
  _time += time * _timeEffect;
}

void		TimeEffectGroup::setTimeEffect(double timeEffect)
{
  _timeEffect = timeEffect;
}

double		TimeEffectGroup::getTime() const
{
  return _time;
}

double		TimeEffectGroup::getElapseTime() const
{
	return _elapseTime;
}

double		TimeEffectGroup::getTimeEffect() const
{
  return _timeEffect;
}

TimeEffectManager::TimeEffectManager()
{
}

TimeEffectManager::~TimeEffectManager()
{
  for (std::map<std::string, TimeEffectGroup*>::iterator it = _timeEffectMap.begin();
	it != _timeEffectMap.end(); it++)
    delete it->second;
}

void		TimeEffectManager::updateTime(double time)
{
  for (std::map<std::string, TimeEffectGroup*>::iterator it = _timeEffectMap.begin();
       it != _timeEffectMap.end(); it++)
    it->second->updateTime(time);
}

void		TimeEffectManager::setTimeEffect(std::string const &name,
						 double timeEffect)
{
  this->getTimeEffectGroup(name)->setTimeEffect(timeEffect);
}

double		TimeEffectManager::getTime(std::string const &name)
{
  return this->getTimeEffectGroup(name)->getTime();
}

double		TimeEffectManager::getElapseTime(std::string const &name)
{
	return this->getTimeEffectGroup(name)->getElapseTime();
}

double		TimeEffectManager::getTimeEffect(std::string const &name)
{
  return this->getTimeEffectGroup(name)->getTimeEffect();
}

TimeEffectGroup	*TimeEffectManager::getTimeEffectGroup(std::string const &name)
{
  std::map<std::string, TimeEffectGroup*>::iterator	it = _timeEffectMap.find(name);

  if (it != _timeEffectMap.end())
    return it->second;
  TimeEffectGroup	*group = new TimeEffectGroup;
  _timeEffectMap[name] = group;
  return group;
}
