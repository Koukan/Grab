#include <fstream>
#include "File.hpp"
#include "md5.h"

CORE_USE_NAMESPACE

File::File()
{
}

File::~File()
{
}

bool		File::load(std::string const &path)
{
	std::ifstream	file(path.c_str());
	char			*buffer;
	size_t			size = 1300;
	char			md5[16];
	md5_state_t		pms;

	if (file)
	{
		::md5_init(&pms);
		while (!file.eof())
		{
			buffer = new char[size];
			file.read(buffer, size);
			if (file.eof())
				size = static_cast<size_t>(file.gcount());
			::md5_append(&pms, reinterpret_cast<md5_byte_t*>(buffer), size);
			this->_list.push_back(new Net::DataBlock(buffer, size));
		}
		::md5_finish(&pms, reinterpret_cast<md5_byte_t*>(md5));
		this->_md5.assign(md5, 16);
		this->_path = path;
		file.close();
	}
	return false;
}

bool				File::save()
{
	std::ofstream	out(this->_path.c_str(), std::ios_base::out | std::ios_base::trunc);

	if (!out.good())
		return false;
	for (std::list<Net::DataBlock*>::const_iterator it = this->_list.begin();
		 it != this->_list.end(); it++)
		 out.write(reinterpret_cast<char *>((*it)->_vec.iov_base), (*it)->_vec.iov_len);
	if (!out.good())
		return false;
	return true;
}

bool				File::save(std::string const &path)
{
	this->_path = path;
	return this->save();
}

void				File::addContent(std::string const &data, int position)
{
	if (position == -1)
		this->_list.push_back(new Net::DataBlock(data));
	else
		this->_list.push_front(new Net::DataBlock(data));
}

std::string const	&File::calcMD5()
{
	md5_state_t		pms;
	char			md5[16];

	::md5_init(&pms);
	for (std::list<Net::DataBlock*>::const_iterator it = this->_list.begin();
		 it != this->_list.end(); it++)
		::md5_append(&pms, reinterpret_cast<md5_byte_t*>((*it)->_vec.iov_base), (*it)->_vec.iov_len);
	::md5_finish(&pms, reinterpret_cast<md5_byte_t*>(md5));
	this->_md5.assign(md5, 16);
}

void				File::setPath(std::string const &path)
{
	this->_path = path;
}

std::string const	&File::getPath() const
{
	return this->_path;
}

std::string const	&File::getMD5() const
{
	return this->_md5;
}
