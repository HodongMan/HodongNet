#include "HodongNet/pch.h"

#include "Socket.h"

#include "HodongNet/IPEndpoint.h"


Socket::Socket( void )
	: _ipVersion{ IPVersion::IPv4 }
	, _handle{ INVALID_SOCKET }
{

}

Socket::Socket( IPVersion ipVersion, SocketHandle handle )
	: _ipVersion{ ipVersion }
	, _handle{ handle }
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

	if ( false == setBlocking( false ) )
	{
		return false;
	}

	if ( false == setSocketOption( SocketOption::TCPNoDelay, true ) )
	{
		return false;
	}

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

bool Socket::bind( const IPEndPoint & endPoint) noexcept
{
	assert( _ipVersion == endPoint.getIPVersion() );

	if ( IPVersion::IPv4 == _ipVersion )
	{
		const sockaddr_in address	= endPoint.getSockaddrIPv4();
		
		const int result			= ::bind( _handle, reinterpret_cast<const sockaddr*>( &address ), sizeof( sockaddr_in ) );
		if ( 0 != result )
		{
			const int error			= WSAGetLastError();

			return false;
		}
	}
	else
	{

	}

	return true;
}

bool Socket::listen(const IPEndPoint & endPoint, const int backlog) noexcept
{
	if ( IPVersion::IPv6 == _ipVersion )
	{
		if ( false == setSocketOption( SocketOption::IPv6Only, FALSE ) )
		{
			return false;
		}
	}

	if ( false == bind( endPoint ) )
	{
		return false;
	}

	int result = ::listen( _handle, backlog );
	if ( 0 != result )
	{
		const int error = WSAGetLastError();

		return false;
	}

	return true;
}

bool Socket::accept( Socket& outSocket, IPEndPoint* endpoint ) noexcept
{
	assert( ( IPVersion::IPv4  == _ipVersion )  || ( IPVersion::IPv6 == _ipVersion ) );

	if ( IPVersion::IPv4  == _ipVersion )
	{
		sockaddr_in addr = {};
		int len = sizeof( sockaddr_in );

		SocketHandle acceptedConnectionHandle = ::WSAAccept( _handle, (sockaddr*)(&addr), &len, nullptr, NULL );
		if ( INVALID_SOCKET == INVALID_SOCKET )
		{
			int error = WSAGetLastError();

			return false;
		}

		if ( nullptr != endpoint)
		{
			*endpoint = IPEndPoint( (sockaddr*)&addr );
		}

		outSocket = Socket(IPVersion::IPv4, acceptedConnectionHandle);
	}
	else
	{

	}

	return true;
}

bool Socket::connect( const IPEndPoint& endpoint ) noexcept
{
	assert( _ipVersion == endpoint.getIPVersion() );

	int result = 0;
	if ( IPVersion::IPv4 == _ipVersion )
	{
		const sockaddr_in addr = endpoint.getSockaddrIPv4();
		result = ::WSAConnect( _handle, reinterpret_cast<const sockaddr*>( &addr ), sizeof( sockaddr_in ), nullptr, nullptr, nullptr, nullptr );
	}
	else
	{

	}

	if ( 0 != result )
	{
		int error = WSAGetLastError();
		
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

bool Socket::setBlocking( const bool isBlocking ) noexcept
{
	unsigned long nonBlocking = 1;
	unsigned long blocking = 0;

	int result = ioctlsocket( _handle, FIONBIO, ( isBlocking ? &blocking : &nonBlocking ) );
	if ( SOCKET_ERROR == result )
	{
		//int error = WSAGetLastError();
		return false;
	}

	return true;
}

bool Socket::setSocketOption( const SocketOption socketOption, const bool value ) noexcept
{
	int result = 0;

	switch ( socketOption )
	{
	case SocketOption::TCPNoDelay:
		{
			result = setsockopt( _handle, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>( &value ), sizeof( value ) );
		}
		break;
	case SocketOption::IPv6Only:
		{
			result = setsockopt( _handle, IPPROTO_IPV6, IPV6_V6ONLY, reinterpret_cast<const char*>( &value ), sizeof( value ) );
		}
		break;
	default:
		{
			assert( true == false );
		}
		break;
	}

	if ( 0 != result )
	{
		//int error = WSAGetLastError();
		return false;
	}

	return true;
}
