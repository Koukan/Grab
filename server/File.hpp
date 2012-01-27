#pragma once

#include "Net.hpp"

class File
{
  public:
    File();
    ~File();
	bool				load(std::string const &path);
	std::string const 	&getMD5() const;

  private:
	std::string					_path;
	std::list<Net::DataBlock*>	_list;
	std::string					_md5;
};
