#pragma once

#include "HodongNet/TypeSocket.h"


class IPEndPoint
{
public:
	IPEndPoint( void );
	IPEndPoint( const char * ip, const unsigned short port );
	IPEndPoint( const sockaddr* address );

	IPVersion				getIPVersion( void ) const noexcept;
	std::vector<uint8_t>	getIPBytes( void ) const noexcept;
	std::string				getHostname( void ) const noexcept;
	std::string				getIPString( void ) const noexcept;
	unsigned short			getPort( void ) const noexcept;
	sockaddr_in				getSockaddrIPv4( void ) const noexcept;
	sockaddr_in6			getSockaddrIPv6( void ) const noexcept;

private:
	IPVersion				_ipVersion;
	std::string				_hostName;
	std::string				_ipString;
	std::vector<uint8_t>	_ipBytes;
	unsigned short			_port;
};