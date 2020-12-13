#pragma once

#pragma once

#include <SDKDDKVer.h>


#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <assert.h>
#include <set>
#include <deque>
#include <mutex>
#include <thread>
#include <iostream>
#include <utility>
#include <atomic>


#include <stdint.h>
#include <stdlib.h>


#if defined(_WIN32) || defined(_WIN64)
#define OS_PLATFORM_WINDOWS
#elif defined(LINUX32) || defined(LINUX64)
#define OS_PLATFORM_LINUX
#endif


#ifdef OS_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <io.h>
#include <process.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <mswsock.h>
#include <time.h>
#include <stdarg.h>
#pragma  comment(lib,"ws2_32")
#pragma  comment(lib, "Mswsock")

#endif