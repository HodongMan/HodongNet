#pragma once

#include "HodongNet/TypeSocket.h"

class IPEndPoint;


class Socket
{
public:

	Socket( void );
	Socket( IPVersion ipVersion, SocketHandle handle );
	~Socket( void );

	bool				create( void ) noexcept;
	bool				close( void ) noexcept;

	bool				bind( const IPEndPoint& endPoint ) noexcept;
	bool				listen( const IPEndPoint& endPoint, const int backlog ) noexcept;
	bool				accept( _Out_ Socket & outSocket, IPEndPoint* endpoint = nullptr ) noexcept;
	bool				connect( const IPEndPoint& endpoint ) noexcept;

	IPVersion			getIPVersion( void ) const noexcept;
	SocketHandle		getSocketHandle( void ) const noexcept;

	bool				setBlocking( const bool isBlocking ) noexcept;

private:

	IPVersion			_ipVersion;
	SocketHandle		_handle;


	bool				setSocketOption( const SocketOption socketOption, const bool value ) noexcept;
};