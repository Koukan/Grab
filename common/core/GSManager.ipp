template <class T>
void		GSManager::loadState(T &state)
{
  instanceMap::iterator		it = _keeper.find(state.name);

  if (it != _keeper.end())
    delete it->second;
  _keeper[state.name] = new GameStateInstance<T>;
}

template <class T>
void		GSManager::loadState(const std::string &name)
{
  instanceMap::iterator		it = _keeper.find(name);

  if (it != _keeper.end())
    delete it->second;
  _keeper[name] = new GameStateInstance<T>;
}
