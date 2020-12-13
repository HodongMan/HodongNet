#pragma once


class NetworkInitializer
{
public:

	NetworkInitializer( void ) = default;

	bool			initialize( void ) noexcept;
	void			shutdown( void ) noexcept;
};