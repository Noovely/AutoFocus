// qthread.h
//

class qthread
{
protected:
	virtual ~qthread();
			qthread();

public:
			int32	start();
			int32	wait_terminate();

protected:
	virtual	int32	main() = 0;

protected:
	void*	m_thread;
	int32	m_exitcode;

#if defined( WIN32 )

	static	DWORD WINAPI threadentry( LPVOID pparam );

#elif defined( MACOSX ) || __ppc64__ || __i386__ || __x86_64__ || __aarch64__ || __arm__

	static	void*	threadentry(void* pparam );

#else
#error unknown operating system: class qthread
#endif

};

