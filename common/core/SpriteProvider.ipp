template <typename T>
void			SpriteProvider::loadElement(TiXmlNode *parent, T data,
							Method<T> const *tab, size_t sizeTab)
{
	if (!parent || !tab || !sizeTab)
		return ;
	std::string		name;
	for (TiXmlNode *child = parent->FirstChild(); child != 0;
		 child = child->NextSibling())
	{
		if (child->Type() == TiXmlNode::ELEMENT)
		{
			name = child->Value();
			for (size_t i = 0; i < sizeTab; i++)
			{
				if (name == tab[i].name)
				{
					(this->*tab[i].func)(static_cast<TiXmlElement*>(child), data);
					break ;
				}
			}
		}
	}
}

