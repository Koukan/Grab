/*
 * Packet.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: snap
 */

#ifndef PACKET_HPP_
#define PACKET_HPP_
#include <cstring>

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include "InetAddr.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Packet to be sent across the network
 */
class NET_DLLREQ Packet
{
public:
	Packet();
	~Packet();
	Packet(Packet const &other);
	Packet(Packet &&other);
	Packet& operator=(Packet const &other);
	
	Packet& operator<<(std::string const &str);
	Packet& operator>>(std::string &str);
	Packet& operator<<(std::wstring const &str);
	Packet& operator>>(std::wstring &str);


	/*!
	 \brief Insert value in the Packet

	 \tparam T Type of the value to insert
	 \param value Source
	 \details Increment the write pointer
	 \return A reference to the Packet, to chain insertion
	 */
	template <typename T>
	Packet& operator<<(T value) // works only for primary types
	{
		this->addBuffer((char*)&value, sizeof(T));
		return *this;
	}

	/*!
	 \brief Extract value from the Packet

	 \tparam T Type of the value to extract
	 \param value Destination
	 \details Increment the read pointer
	 \return A reference to the Packet, to chain extraction
	 */
	template <typename T>
	Packet& operator>>(T &value) // works only for primary types
	{
		if (_size - _rindex < sizeof(T))
			throw std::runtime_error("Insuffient place to extract data");
		T *tmp = (T*)this->rd_ptr();
		value = *tmp;
		_rindex += sizeof(T);
		return *this;
	}

	/*!
	 \brief Add a C buffer to the Packet
	 \details The buffer can contain all value permitted by char
	 \param buf The source buffer
	 \param size The size of the source buffer
	 */
	void	addBuffer(char const *buf, size_t size);
	/*!
	 \brief Get the size of the packet

	 \return the size of the packet
	 */
	size_t	size() const;
	size_t	capacity() const;
	char const	*rd_ptr();
	char const	*wr_ptr();
	/*!
	 \brief Set the read pointer

	 \param index the offset
	 */
	void	rd_ptr(size_t index);
	/*!
	 \brief Set the write pointer 

	 \param index the offset
	 */
	void	wr_ptr(size_t index);
	char const 	*base() const;
	/*!
	 \brief Reset all the offset of the internal pointers
	 */
	void	reset();
	/*!
	 \brief Get the read pointer

	 \return the offset of the read pointer
	 */
	size_t	getRindex() const;
	/*!
	 \brief Get the write pointer

	 \return the offser of the write pointer
	 */
	size_t	getWindex() const;
	bool	isConsumned() const;
	/*!
	 \brief Get the destination

	 \return the address of the destination
	 */
	InetAddr const	&getAddr() const;
	void	setSize(size_t size);
	/*!
	 \brief Set the destination of the Packet
	 \details Useful for connectionless protocol like UDP
	 \param addr Address of the destination
	 */
	void	setDestination(InetAddr const &addr);

	std::string const &getString() const;

	void	reserve(size_t size);
	void	assign(std::string &&string);

protected:
	size_t			_rindex;
	size_t			_windex;
	size_t			_size;
	InetAddr		_addr;

private:
	std::shared_ptr<std::string>	_ss;
};

NET_END_NAMESPACE

#endif /* Packet_HPP_ */
