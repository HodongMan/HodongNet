#pragma once

#include "HodongNet/TypeSocket.h"

class IPEndPoint;


class Socket
{
public:

	Socket( void );
	~Socket( void );

	bool				create( void ) noexcept;
	bool				close( void ) noexcept;

	bool				bind( const IPEndPoint& endPoint ) noexcept;


	IPVersion			getIPVersion( void ) const noexcept;
	SocketHandle		getSocketHandle( void ) const noexcept;

	bool				setBlocking( const bool isBlocking ) noexcept;

private:

	IPVersion			_ipVersion;
	SocketHandle		_handle;


	bool				setSocketOption( const SocketOption socketOption, const bool value ) noexcept;
};