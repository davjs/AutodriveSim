/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_PLATFORM_H_
#define OPENDAVINCI_CORE_PLATFORM_H_

#include "core/native.h"

/**************************************************************************************/

#ifndef WIN32
	/*
	 * POSIX types.
	 */
	#include <stdint.h>

	/*
	 * POSIX network.
	 */
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/types.h>

	/*
	 * POSIX IPC.
	 */
	#include <pthread.h>
	#include <semaphore.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>
	#include <sys/stat.h>

	/*
	 * Other POSIX stuff.
	 */
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/time.h>

	/* Use regular unlink. */
	#define UNLINK unlink

#elif WIN32

	/* Prevent error C4003. */
	#define NOMINMAX

	/* Unlink causes an error under Windows. */
	#define UNLINK _unlink
	
	#include <Winsock2.h>
	#include <ws2tcpip.h>
#endif

/**************************************************************************************/

/*
 * C++ wrapping headers for C headers.
 */
#include <cassert>
#include <cerrno>
#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

/*
 * C++ headers.
 */
#include <algorithm>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

/*
 * Basic header for OpenDaVINCI macros.
 */
#include "core/macros.h"
#include "core/StringToolbox.h"

#endif // OPENDAVINCI_CORE_PLATFORM_H_
