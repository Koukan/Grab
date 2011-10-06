template <class InstanceClass>
void	GameObjectManager::setRelatedGroups(const std::string &group1,
		const std::string &group2, InstanceClass *instance,
		void (InstanceClass::*function)(GameObject&, GameObject&))
{
  _relatedGroups[stringPair(group1, group2)] =
	  new Callback(instance, function);
}
