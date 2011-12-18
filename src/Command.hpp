#pragma once

class Command
{
  public:
    Command(std::string const &name) : name(name)
	{
	}
    virtual ~Command()
	{
	}

	std::string const		name;
};
