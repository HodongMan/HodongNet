#pragma once

#include "HodongNet/pch.h"


enum class SocketResult
{
	SocketSuccess,
	SocketGenericError
};

enum class IPVersion 
{
	IPv4,
	IPv6,
};

enum class SocketOption
{
	TCPNoDelay,
	IPv6Only,
};

using SocketHandle = SOCKET;