// qthread.cpp :
//

#include "console4.h"
#include "qthread.h"

#if defined( WIN32 )

qthread::~qthread()
{
	if( m_thread != NULL )
	{
		CloseHandle( m_thread );
	}
}

qthread::qthread()
{
	m_thread	= NULL;
	m_exitcode	= 0;
}

int32 qthread::start()
{
	DWORD	dwThreadID;
	m_thread = CreateThread( NULL, 0, threadentry, this, NULL, &dwThreadID );
	return m_thread != NULL;
}

int32 qthread::wait_terminate()
{
	WaitForSingleObject( m_thread, INFINITE );
	return m_exitcode;
}

DWORD WINAPI qthread::threadentry( LPVOID pparam )
{
	qthread*	pThis = (qthread*)pparam;

	pThis->m_exitcode = pThis->main();

	return 0;
}

#elif defined( MACOSX ) || __ppc64__ || __i386__ || __x86_64__

#include <pthread.h>

qthread::~qthread()
{
}

qthread::qthread()
{
	m_thread	= NULL;
	m_exitcode	= 0;
}

int32 qthread::start()
{
	pthread_create( (pthread_t*)&m_thread, NULL, threadentry, this );
	return m_thread != NULL;
}

int32 qthread::wait_terminate()
{
	void*	ret;
	if( pthread_join( (pthread_t)m_thread, &ret ) == 0 )
		pthread_detach( (pthread_t)m_thread );

	return m_exitcode;
}

void* qthread::threadentry(void* pparam )
{
	qthread*	pThis = (qthread*)pparam;
	
	pThis->main();
	
	return NULL;
}

#else
#error unknown operating system: qthread.cpp
#endif
