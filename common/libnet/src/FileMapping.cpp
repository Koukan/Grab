#include <stdexcept>
#include <unordered_map>
#include "Error.hpp"
#include "FileMapping.hpp"

static std::unordered_map<void *, void*>	_handles;

#if defined (_WIN32)
#include <unordered_map>
#include <windows.h>

NET_USE_NAMESPACE

struct wininfo
{
	wininfo() : file(INVALID_HANDLE_VALUE), file_mapping(INVALID_HANDLE_VALUE)
	{}

	~wininfo()
	{
		if (file != INVALID_HANDLE_VALUE)
			::CloseHandle(file);
		if (file_mapping != INVALID_HANDLE_VALUE)
			::CloseHandle(file_mapping);
	}

	HANDLE file;
	HANDLE file_mapping;
};

std::tuple<void *, std::size_t> FileMapping::map(std::string const &path, std::size_t offset, std::size_t size)
{
	struct wininfo local;
	local.file = ::CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (local.file == INVALID_HANDLE_VALUE)
		throw std::runtime_error(getLastError());
	local.file_mapping = ::CreateFileMapping(local.file, NULL, PAGE_READONLY, 0, 0, NULL);
	if (local.file_mapping == INVALID_HANDLE_VALUE)
		throw std::runtime_error(getLastError());
	void *ret = ::MapViewOfFile(local.file_mapping, FILE_MAP_READ, 0, offset, size);
	if (!ret)
		throw std::runtime_error(getLastError());
	wininfo *tmp = new wininfo(local);
	local.file = INVALID_HANDLE_VALUE;
	local.file_mapping = INVALID_HANDLE_VALUE;
	_handles[ret] = tmp;
	return std::make_tuple(ret, ::GetFileSize(tmp->file, NULL));
}

void	FileMapping::unmap(void *addr)
{
	auto it = _handles.find(addr);
	if (it == _handles.end())
		return;
	wininfo *tmp = static_cast<wininfo*>(it->second);
	::UnmapViewOfFile(addr);
	delete tmp;
}
#else

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

NET_USE_NAMESPACE

struct unixinfo
{
	unixinfo() : file(-1), size(0)
	{}

	~unixinfo()
	{
		if (file != -1)
			::close(file);
	}

	int file;
	std::size_t size;
};

std::tuple<void *, std::size_t> FileMapping::map(std::string const &path, std::size_t offset, std::size_t size)
{
	struct unixinfo local;
	local.file = ::open(path.c_str(), O_RDWR);
	if (local.file == -1)
		return std::make_tuple(nullptr, 0);
		//throw std::runtime_error(getLastError());
	if (size == 0)
	{
		struct stat buf;
		fstat(local.file, &buf);
		size = buf.st_size;
	}
	void *ret = ::mmap(0, size, PROT_READ, MAP_PRIVATE, local.file, offset);
	if (ret == (void*)-1)
		return std::make_tuple(nullptr, 0);
		//throw std::runtime_error(getLastError());
	unixinfo *tmp = new unixinfo(local);
	tmp->size = size;
	local.file = -1;
	_handles[ret] = tmp;
	return std::make_tuple(ret, size);
}

void	FileMapping::unmap(void *addr)
{
	auto it = _handles.find(addr);
	if (it == _handles.end())
		return;
	unixinfo *tmp = static_cast<unixinfo*>(it->second);
	::munmap(addr, tmp->size);
	delete tmp;
}
#endif
