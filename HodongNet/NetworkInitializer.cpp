#include "HodongNet/pch.h"

#include "NetworkInitializer.h"


bool NetworkInitializer::initialize( void ) noexcept
{
	WSAData wsadata;

	int result = ::WSAStartup( MAKEWORD( 2, 2 ), &wsadata );
	if ( 0 != result )
	{
		std::cerr << "WSAStartup Failed" << std::endl;
		return false;
	}

	if ( ( 2 != LOBYTE( wsadata.wVersion ) ) || ( 2 != HIBYTE( wsadata.wVersion ) ) )
	{
		std::cerr << "WSAStartup Version is not initialize." << std::endl;
		return false;
	}

	return true;
}

void NetworkInitializer::shutdown( void ) noexcept
{
	::WSACleanup();
}
