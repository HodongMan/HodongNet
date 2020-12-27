#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>


inline void ltrim( std::string& string ) noexcept
{
	string.erase( string.begin(), std::find_if( string.begin(), string.end(), []( int ch )
	{
		return !( ( true == std::isspace( ch ) ) || ( '\0' == ch ) );
	}));
}

inline void rtrim( std::string &string ) noexcept
{
	string.erase( std::find_if( string.rbegin(), string.rend(), []( int ch )
	{
		return !( ( true == std::isspace( ch ) ) || ( '\0' == ch ) );
	}).base(), string.end() );
}

// trim from both ends (in place)
inline void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s)
{
	ltrim(s);
	return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s)
{
	rtrim(s);
	return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s)
{
	trim(s);
	return s;
}