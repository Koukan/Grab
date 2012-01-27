template <class InstanceClass>
void	GameObjectManager::setCollisionGroups(const std::string &group1,
		const std::string &group2,
		void (InstanceClass::*function)(GameObject&))
{
  _collisionGroups[stringPair(group1, group2)] =
	  new PhysicsSubscriber2<InstanceClass>(function);
}
