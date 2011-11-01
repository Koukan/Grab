#include "TimeEffectManager.hpp"

TimeEffectGroup::TimeEffectGroup()
	: _timeEffect(1)
{
}

double		TimeEffectGroup::getTimeEffect()
{
  return _timeEffect;
}

void		TimeEffectGroup::setTimeEffect(double timeEffect)
{
  _timeEffect = timeEffect;
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

void		TimeEffectManager::setTimeEffect(std::string const &name,
						 double timeEffect)
{
  this->getTimeEffectGroup(name)->setTimeEffect(timeEffect);
}
