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


using SocketHandle = SOCKET;