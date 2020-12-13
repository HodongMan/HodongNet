#include "HodongNet/pch.h"

#include "Socket.h"


Socket::Socket( void )
	: _ipVersion{ IPVersion::IPv4 }
	, _handle{ INVALID_SOCKET }
{

}

Socket::~Socket( void )
{

}

bool Socket::create( void ) noexcept
{
	assert( INVALID_SOCKET == _handle);

	_handle = ::WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL );
	if ( INVALID_SOCKET == _handle )
	{
		std::cout << "WSASocket Occured Error " << ::WSAGetLastError() << std::endl;

		return false;
	}

	//if (::SetBlocking)

	return true;
}

bool Socket::close( void ) noexcept
{
	assert( INVALID_SOCKET != _handle);

	::closesocket( _handle );
	if ( INVALID_SOCKET != _handle )
	{
		std::cout << "closesocket Occured Error " << ::WSAGetLastError() << std::endl;

		return false;
	}

	return true;
}

IPVersion Socket::getIPVersion( void ) const noexcept
{
	return _ipVersion;
}

SocketHandle Socket::getSocketHandle( void ) const noexcept
{
	return _handle;
}
