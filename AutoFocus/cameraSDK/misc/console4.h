// console4.h

// ----------------------------------------------------------------

#ifdef _WIN32

// Windows

#include	<windows.h>

#else // ! _WIN32

#include    <stdlib.h>
#include    <string.h>
#include    <stdint.h>

#if defined( LINUX )

// Linux

#include	<pthread.h>
#include	<ctype.h>

#elif defined( MACOSX )

// Mac
// No carbon

#include    <unistd.h>

#endif
#endif // _WIN32

// common headers

#include	<stdio.h>

// DCAM-API headers

#ifndef _NO_DCAMAPI

#ifndef DCAMAPI_VER
#define	DCAMAPI_VER		4000
#endif

#ifndef DCAMAPI_VERMIN
#define	DCAMAPI_VERMIN	4000
#endif

#if	defined( LINUX )
#include			"dcamapi4.h"
#include			"dcamprop.h"
#else
#include			"cameraSDK/inc/dcamapi4.h"
#include			"cameraSDK/inc/dcamprop.h"
#endif

#if defined( _WIN64 )
#pragma comment(lib,"cameraSDK/lib/win64/dcamapi.lib")
#elif defined( _WIN32 )
#pragma comment(lib,"cameraSDK/lib/win32/dcamapi.lib")
#endif

#endif // _NO_DCAMAPI

// ----------------------------------------------------------------

// define common macro

#ifndef ASSERT
#define	ASSERT(c)
#endif

// absorb different function

#ifdef _WIN32

#if defined(UNICODE) || defined(_UNICODE)
#define	_T(str)	L##str
#else
#define	_T(str)	str
#endif

#elif defined( MACOSX ) || __ppc64__ || __i386__ || __x86_64__ || defined( LINUX )

#define	_T(str)	str

#endif

// absorb Visual Studio 2005 and later

#if ! defined( WIN32 ) || _MSC_VER < 1400

#define	_stricmp(str1, str2)				strncasecmp( str1, str2, strlen(str2) )
#define	sprintf_s							snprintf

#define	BOOL			int
#define	BYTE			uint8_t
#define	WORD			uint16_t
#define	DWORD			uint32_t
#define	LONGLONG		int64_t

#define	MAX_PATH		256
#define	TRUE			1
#define	FALSE			0

inline int fopen_s( FILE** fpp, const char* filename, const char* filemode )
{
	*fpp = fopen( filename, filemode );
	if( fpp == NULL )
		return 1;
	else
		return 0;
}

inline void Sleep( DWORD dwMillseconds )
{
#if defined( MACOSX )
    int usec = dwMillseconds * 1000;
    usleep(usec);
#else // expect defined( LINUX )
	struct timespec t;
	t.tv_sec = dwMillseconds / 1000;
	t.tv_nsec = ( dwMillseconds % 1000 ) * 1000000;
	nanosleep( &t, NULL );
#endif
}

inline void* memcpy_s( void* dst, size_t dstsize, const void* src, size_t srclen )
{
	if( dstsize < srclen )
		return memcpy( dst, src, dstsize );
	else
		return memcpy( dst, src, srclen );
}

inline char* strcpy_s( char* dst, size_t dstsize, const char* src )
{
	return (char*)memcpy_s( dst, dstsize, src, strlen(src) );
}

inline char* strcat_s( char* dst, size_t dstsize, const char* src )
{
	size_t	dstused = strlen(dst);
	strcpy_s( dst + dstused, dstsize - dstused, src );
	return dst;
}

#endif

// ----------------------------------------------------------------
