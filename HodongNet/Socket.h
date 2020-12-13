#pragma once

#include "HodongNet/TypeSocket.h"


class Socket
{
public:

	Socket( void );
	~Socket( void );

	bool				create( void ) noexcept;
	bool				close( void ) noexcept;


	IPVersion			getIPVersion( void ) const noexcept;
	SocketHandle		getSocketHandle( void ) const noexcept;

private:

	IPVersion			_ipVersion;
	SocketHandle		_handle;

};