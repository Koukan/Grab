#pragma once

#include "Net.hpp"


class File
{
  public:
    File();
    ~File();
	bool				load(std::string const &path);
	bool				save();
	bool				save(std::string const &path);
	void				addContent(std::string const &data, int	position = -1);
	std::string const 	&calcMD5();

	// setter
	void				setPath(std::string const &path);

	// getter
	std::string const	&getPath() const;
	std::string const 	&getMD5() const;

  private:
	std::string					_path;
	std::list<Net::DataBlock*>	_list;
	std::string					_md5;
};
