#include "HodongNet/pch.h"

#include "IPEndpoint.h"
#include "StringUtil.h"


IPEndPoint::IPEndPoint( void )
{

}

IPEndPoint::IPEndPoint( const char* ip, const unsigned short port )
	: _port( port ) 
{
	in_addr address;

	int result = ::inet_pton( AF_INET, ip, &address );
	if ( 1 == result )
	{
		if ( INADDR_NONE != address.S_un.S_addr )
		{
			_ipString = ip;
			_hostName = ip;

			trim( _ipString );
			trim( _hostName );

			_ipBytes.resize( sizeof( ULONG ) );
			::memcpy( &_ipBytes[0], &address.S_un.S_addr, sizeof( ULONG ) );

			_ipVersion = IPVersion::IPv4;

			return;
		}
	}

	addrinfo hints		= {};
	addrinfo* hostInfo	= nullptr;

	hints.ai_family		= AF_INET;
	result				= ::getaddrinfo( ip, NULL, &hints, &hostInfo );
	if ( 0 == result )
	{
		assert( nullptr != hostInfo );

		const sockaddr_in* hostAddress = reinterpret_cast<const sockaddr_in*>( hostInfo->ai_addr );
		assert( nullptr != hostAddress );

		_ipString.reserve( 16 );

		::inet_ntop( AF_INET, &hostAddress->sin_addr, &_ipString[0], 16 );

		_hostName = ip;
		trim( _ipString );
		trim( _hostName );

		const ULONG ip	= hostAddress->sin_addr.S_un.S_addr;
		
		_ipBytes.reserve( sizeof( ULONG ) );
		::memcpy( &_ipBytes[0], &ip, sizeof( ULONG ) );

		_ipVersion		= IPVersion::IPv4;

		freeaddrinfo( hostInfo );
		return;
	}
}

IPEndPoint::IPEndPoint( const sockaddr* address )
{

}

IPVersion IPEndPoint::getIPVersion( void ) const noexcept
{
	return _ipVersion;
}

std::vector<uint8_t> IPEndPoint::getIPBytes( void ) const noexcept
{
	return _ipBytes;
}

std::string IPEndPoint::getHostname( void ) const noexcept
{
	return _hostName;
}

std::string IPEndPoint::getIPString( void ) const noexcept
{
	return _ipString;
}

unsigned short IPEndPoint::getPort( void ) const noexcept
{
	return _port;
}

sockaddr_in IPEndPoint::getSockaddrIPv4( void ) const noexcept
{
	assert( IPVersion::IPv4 == _ipVersion );

	sockaddr_in address = {};
	address.sin_family	= AF_INET;
	memcpy( &address.sin_addr, &_ipBytes[0], sizeof( ULONG ) );
	address.sin_port	= htons( _port );

	return address;
}

sockaddr_in6 IPEndPoint::getSockaddrIPv6(void) const noexcept
{
	return sockaddr_in6();
}
