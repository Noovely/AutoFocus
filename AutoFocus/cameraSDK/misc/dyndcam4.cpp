// dyndcam4.cpp

#include "console4.h"

/* ---------------------------------------------------------------- */

typedef DCAMERR DCAMAPI proc_api_init( DCAMAPI_INIT* param );
typedef DCAMERR DCAMAPI proc_api_uninit();
typedef DCAMERR DCAMAPI proc_dev_open( DCAMDEV_OPEN* param );
typedef DCAMERR DCAMAPI proc_dev_close( HDCAM h );
typedef DCAMERR DCAMAPI proc_dev_showpanel( HDCAM h, int32 iKind );
typedef DCAMERR DCAMAPI proc_dev_getcapability( HDCAM h, DCAMDEV_CAPABILITY* param );
typedef DCAMERR DCAMAPI proc_dev_getstring( HDCAM h, DCAMDEV_STRING* param );
typedef DCAMERR DCAMAPI proc_dev_setdata( HDCAM h, DCAMDATA_HDR* param );
typedef DCAMERR DCAMAPI proc_dev_getdata( HDCAM h, DCAMDATA_HDR* param );
typedef DCAMERR DCAMAPI proc_prop_getattr( HDCAM h, DCAMPROP_ATTR* param );
typedef DCAMERR DCAMAPI proc_prop_getvalue( HDCAM h, int32 iProp, double* pValue );
typedef DCAMERR DCAMAPI proc_prop_setvalue( HDCAM h, int32 iProp, double  fValue );
typedef DCAMERR DCAMAPI proc_prop_setgetvalue( HDCAM h, int32 iProp, double* pValue, int32 option );
typedef DCAMERR DCAMAPI proc_prop_queryvalue( HDCAM h, int32 iProp, double* pValue, int32 option );
typedef DCAMERR DCAMAPI proc_prop_getnextid( HDCAM h, int32* pProp, int32 option );
typedef DCAMERR DCAMAPI proc_prop_getname( HDCAM h, int32 iProp, char* text, int32 textbytes );
typedef DCAMERR DCAMAPI proc_prop_getvaluetext( HDCAM h, DCAMPROP_VALUETEXT* param );
typedef DCAMERR DCAMAPI proc_buf_alloc( HDCAM h, int32 framecount );// call dcambuf_release() to free.
typedef DCAMERR DCAMAPI proc_buf_attach( HDCAM h, const DCAMBUF_ATTACH* param );
typedef DCAMERR DCAMAPI proc_buf_release( HDCAM h, int32 iKind );
typedef DCAMERR DCAMAPI proc_buf_lockframe( HDCAM h, DCAMBUF_FRAME* pFrame );
typedef DCAMERR DCAMAPI proc_buf_copyframe( HDCAM h, DCAMBUF_FRAME* pFrame );
typedef DCAMERR DCAMAPI proc_buf_copymetadata( HDCAM h, DCAM_METADATAHDR* hdr );
typedef DCAMERR DCAMAPI proc_cap_start( HDCAM h, int32 mode );
typedef DCAMERR DCAMAPI proc_cap_stop( HDCAM h );
typedef DCAMERR DCAMAPI proc_cap_status( HDCAM h, int32* pStatus );
typedef DCAMERR DCAMAPI proc_cap_transferinfo( HDCAM h, DCAMCAP_TRANSFERINFO* param );
typedef DCAMERR DCAMAPI proc_cap_firetrigger( HDCAM h, int32 iKind );
typedef DCAMERR DCAMAPI proc_cap_record( HDCAM h, HDCAMREC hrec );
typedef DCAMERR DCAMAPI proc_wait_open( DCAMWAIT_OPEN* param );
typedef DCAMERR DCAMAPI proc_wait_close( HDCAMWAIT hWait );
typedef DCAMERR DCAMAPI proc_wait_start( HDCAMWAIT hWait, DCAMWAIT_START* param );
typedef DCAMERR DCAMAPI proc_wait_abort( HDCAMWAIT hWait );
typedef DCAMERR DCAMAPI proc_rec_openA( DCAMREC_OPENA* param );
typedef DCAMERR DCAMAPI proc_rec_openW( DCAMREC_OPENW* param );
typedef DCAMERR DCAMAPI proc_rec_close( HDCAMREC hrec );
typedef DCAMERR DCAMAPI proc_rec_lockframe( HDCAMREC hrec, DCAMREC_FRAME* pFrame );
typedef DCAMERR DCAMAPI proc_rec_copyframe( HDCAMREC hrec, DCAMREC_FRAME* pFrame );
typedef DCAMERR DCAMAPI proc_rec_writemetadata( HDCAMREC hrec, const DCAM_METADATAHDR* hdr );
typedef DCAMERR DCAMAPI proc_rec_lockmetadata( HDCAMREC hrec, DCAM_METADATAHDR* hdr );
typedef DCAMERR DCAMAPI proc_rec_copymetadata( HDCAMREC hrec, DCAM_METADATAHDR* hdr );
typedef DCAMERR DCAMAPI proc_rec_lockmetadatablock( HDCAMREC hrec, DCAM_METADATABLOCKHDR* hdr );
typedef DCAMERR DCAMAPI proc_rec_copymetadatablock( HDCAMREC hrec, DCAM_METADATABLOCKHDR* hdr );
typedef DCAMERR DCAMAPI proc_rec_pause( HDCAMREC hrec );
typedef DCAMERR DCAMAPI proc_rec_resume( HDCAMREC hrec );
typedef DCAMERR DCAMAPI proc_rec_status( HDCAMREC hrec, DCAMREC_STATUS* pStatus );

/* ---------------------------------------------------------------- */

static HINSTANCE	hInstDcamapi4;

static struct {
	proc_api_init*				api_init;
	proc_api_uninit*			api_uninit;
	proc_dev_open*				dev_open;
	proc_dev_close*				dev_close;
	proc_dev_showpanel*			dev_showpanel;
	proc_dev_getcapability*		dev_getcapability;
	proc_dev_getstring*			dev_getstring;
	proc_dev_setdata*			dev_setdata;
	proc_dev_getdata*			dev_getdata;
	proc_prop_getattr*			prop_getattr;
	proc_prop_getvalue*			prop_getvalue;
	proc_prop_setvalue*			prop_setvalue;
	proc_prop_setgetvalue*		prop_setgetvalue;
	proc_prop_queryvalue*		prop_queryvalue;
	proc_prop_getnextid*		prop_getnextid;
	proc_prop_getname*			prop_getname;
	proc_prop_getvaluetext*		prop_getvaluetext;
	proc_buf_alloc*				buf_alloc;
	proc_buf_attach*			buf_attach;
	proc_buf_release*			buf_release;
	proc_buf_lockframe*			buf_lockframe;
	proc_buf_copyframe*			buf_copyframe;
	proc_buf_copymetadata*		buf_copymetadata;
	proc_cap_start*				cap_start;
	proc_cap_stop*				cap_stop;
	proc_cap_status*			cap_status;
	proc_cap_transferinfo*		cap_transferinfo;
	proc_cap_firetrigger*		cap_firetrigger;
	proc_cap_record*			cap_record;
	proc_wait_open*				wait_open;
	proc_wait_close*			wait_close;
	proc_wait_start*			wait_start;
	proc_wait_abort*			wait_abort;
	proc_rec_openA*				rec_openA;
	proc_rec_openW*				rec_openW;
	proc_rec_close*				rec_close;
	proc_rec_lockframe*			rec_lockframe;
	proc_rec_copyframe*			rec_copyframe;
	proc_rec_writemetadata*		rec_writemetadata;
	proc_rec_lockmetadata*		rec_lockmetadata;
	proc_rec_copymetadata*		rec_copymetadata;
	proc_rec_lockmetadatablock*	rec_lockmetadatablock;
	proc_rec_copymetadatablock*	rec_copymetadatablock;
	proc_rec_pause*				rec_pause;
	proc_rec_resume*			rec_resume;
	proc_rec_status*			rec_status;
} entry;

static FARPROC getproc( const char* procname )
{
	return GetProcAddress( hInstDcamapi4, procname );
}

static void load_dcamapi4()
{
	if( hInstDcamapi4 != NULL )
		return;	// nothing to do.

	hInstDcamapi4 = LoadLibrary( _T("dcamapi.dll") );
	if( hInstDcamapi4 == NULL )
		return;	// DLL is not found

	if( (entry.api_init				= (proc_api_init*)				getproc( "dcamapi_init" )				) != NULL
	 && (entry.api_uninit			= (proc_api_uninit*)			getproc( "dcamapi_uninit" )				) != NULL
	 && (entry.dev_open				= (proc_dev_open*)				getproc( "dcamdev_open" )				) != NULL
	 && (entry.dev_close			= (proc_dev_close*)				getproc( "dcamdev_close" )				) != NULL
	 && (entry.dev_showpanel		= (proc_dev_showpanel*)			getproc( "dcamdev_showpanel" )			) != NULL
	 && (entry.dev_getcapability	= (proc_dev_getcapability*)		getproc( "dcamdev_getcapability" )		) != NULL
	 && (entry.dev_getstring		= (proc_dev_getstring*)			getproc( "dcamdev_getstring" )			) != NULL
	 && (entry.dev_setdata			= (proc_dev_setdata*)			getproc( "dcamdev_setdata" )			) != NULL
	 && (entry.dev_getdata			= (proc_dev_getdata*)			getproc( "dcamdev_getdata" )			) != NULL
	 && (entry.prop_getattr			= (proc_prop_getattr*)			getproc( "dcamprop_getattr" )			) != NULL
	 && (entry.prop_getvalue		= (proc_prop_getvalue*)			getproc( "dcamprop_getvalue" )			) != NULL
	 && (entry.prop_setvalue		= (proc_prop_setvalue*)			getproc( "dcamprop_setvalue" )			) != NULL
	 && (entry.prop_setgetvalue		= (proc_prop_setgetvalue*)		getproc( "dcamprop_setgetvalue" )		) != NULL
	 && (entry.prop_queryvalue		= (proc_prop_queryvalue*)		getproc( "dcamprop_queryvalue" )		) != NULL
	 && (entry.prop_getnextid		= (proc_prop_getnextid*)		getproc( "dcamprop_getnextid" )			) != NULL
	 && (entry.prop_getname			= (proc_prop_getname*)			getproc( "dcamprop_getname" )			) != NULL
	 && (entry.prop_getvaluetext	= (proc_prop_getvaluetext*)		getproc( "dcamprop_getvaluetext" )		) != NULL
	 && (entry.buf_alloc			= (proc_buf_alloc*)				getproc( "dcambuf_alloc" )				) != NULL
	 && (entry.buf_attach			= (proc_buf_attach*)			getproc( "dcambuf_attach" )				) != NULL
	 && (entry.buf_release			= (proc_buf_release*)			getproc( "dcambuf_release" )			) != NULL
	 && (entry.buf_lockframe		= (proc_buf_lockframe*)			getproc( "dcambuf_lockframe" )			) != NULL
	 && (entry.buf_copyframe		= (proc_buf_copyframe*)			getproc( "dcambuf_copyframe" )			) != NULL
	 && (entry.buf_copymetadata		= (proc_buf_copymetadata*)		getproc( "dcambuf_copymetadata" )		) != NULL
	 && (entry.cap_start			= (proc_cap_start*)				getproc( "dcamcap_start" )				) != NULL
	 && (entry.cap_stop				= (proc_cap_stop*)				getproc( "dcamcap_stop" )				) != NULL
	 && (entry.cap_status			= (proc_cap_status*)			getproc( "dcamcap_status" )				) != NULL
	 && (entry.cap_transferinfo		= (proc_cap_transferinfo*)		getproc( "dcamcap_transferinfo" )		) != NULL
	 && (entry.cap_firetrigger		= (proc_cap_firetrigger*)		getproc( "dcamcap_firetrigger" )		) != NULL
	 && (entry.cap_record			= (proc_cap_record*)			getproc( "dcamcap_record" )				) != NULL
	 && (entry.wait_open			= (proc_wait_open*)				getproc( "dcamwait_open" )				) != NULL
	 && (entry.wait_close			= (proc_wait_close*)			getproc( "dcamwait_close" )				) != NULL
	 && (entry.wait_start			= (proc_wait_start*)			getproc( "dcamwait_start" )				) != NULL
	 && (entry.wait_abort			= (proc_wait_abort*)			getproc( "dcamwait_abort" )				) != NULL
	 && (entry.rec_openA			= (proc_rec_openA*)				getproc( "dcamrec_openA" )				) != NULL
	 && (entry.rec_openW			= (proc_rec_openW*)				getproc( "dcamrec_openW" )				) != NULL
	 && (entry.rec_close			= (proc_rec_close*)				getproc( "dcamrec_close" )				) != NULL
	 && (entry.rec_lockframe		= (proc_rec_lockframe*)			getproc( "dcamrec_lockframe" )			) != NULL
	 && (entry.rec_copyframe		= (proc_rec_copyframe*)			getproc( "dcamrec_copyframe" )			) != NULL
	 && (entry.rec_writemetadata	= (proc_rec_writemetadata*)		getproc( "dcamrec_writemetadata" )		) != NULL
	 && (entry.rec_lockmetadata		= (proc_rec_lockmetadata*)		getproc( "dcamrec_lockmetadata" )		) != NULL
	 && (entry.rec_copymetadata		= (proc_rec_copymetadata*)		getproc( "dcamrec_copymetadata" )		) != NULL
	 && (entry.rec_lockmetadatablock= (proc_rec_lockmetadatablock*)	getproc( "dcamrec_lockmetadatablock" )	) != NULL
	 && (entry.rec_copymetadatablock= (proc_rec_copymetadatablock*)	getproc( "dcamrec_copymetadatablock" )	) != NULL
	 && (entry.rec_pause			= (proc_rec_pause*)				getproc( "dcamrec_pause" )				) != NULL
	 && (entry.rec_resume			= (proc_rec_resume*)			getproc( "dcamrec_resume" )				) != NULL
	 && (entry.rec_status			= (proc_rec_status*)			getproc( "dcamrec_status" )				) != NULL )
		return;	// success

	// DCAMAPI.DLL does not include all entry.
	memset( &entry, 0, sizeof(entry) );
	
	return;	// failed
}

static void unload_dcamapi4()
{
	if( hInstDcamapi4 != NULL )
	{
		FreeLibrary( hInstDcamapi4 );
	}
	
	memset( &entry, 0, sizeof(entry) );
}

/* ---------------------------------------------------------------- */

DCAMERR DCAMAPI dcamapi_init( DCAMAPI_INIT* param )
{
	load_dcamapi4();

	if( entry.api_init == NULL )
		return DCAMERR_NOMODULE;

	return entry.api_init( param );
}

DCAMERR DCAMAPI dcamapi_uninit()
{
	DCAMERR	err = DCAMERR_NOMODULE;

	if( entry.api_uninit != NULL )
		err = entry.api_uninit();

	unload_dcamapi4();

	return err;
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_open( DCAMDEV_OPEN* param )
{
	if( entry.dev_open == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_open( param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_close( HDCAM h )
{
	if( entry.dev_close == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_close( h );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_showpanel( HDCAM h, int32 iKind )
{
	if( entry.dev_showpanel == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_showpanel( h, iKind );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_getcapability( HDCAM h, DCAMDEV_CAPABILITY* param )
{
	if( entry.dev_getcapability == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_getcapability( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_getstring( HDCAM h, DCAMDEV_STRING* param )
{
	if( entry.dev_getstring == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_getstring( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_setdata( HDCAM h, DCAMDATA_HDR* param )
{
	if( entry.dev_setdata == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_setdata( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamdev_getdata( HDCAM h, DCAMDATA_HDR* param )
{
	if( entry.dev_getdata == NULL )
		return DCAMERR_NOMODULE;

	return entry.dev_getdata( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_getattr( HDCAM h, DCAMPROP_ATTR* param )
{
	if( entry.prop_getattr == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_getattr( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_getvalue( HDCAM h, int32 iProp, double* pValue )
{
	if( entry.prop_getvalue == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_getvalue( h, iProp, pValue );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_setvalue( HDCAM h, int32 iProp, double  fValue )
{
	if( entry.prop_setvalue == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_setvalue( h, iProp, fValue );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_setgetvalue( HDCAM h, int32 iProp, double* pValue, int32 option )
{
	if( entry.prop_setgetvalue == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_setgetvalue( h, iProp, pValue, option );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_queryvalue( HDCAM h, int32 iProp, double* pValue, int32 option )
{
	if( entry.prop_queryvalue == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_queryvalue( h, iProp, pValue, option );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_getnextid( HDCAM h, int32* pProp, int32 option )
{
	if( entry.prop_getnextid == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_getnextid( h, pProp, option );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_getname( HDCAM h, int32 iProp, char* text, int32 textbytes )
{
	if( entry.prop_getname == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_getname( h, iProp, text, textbytes );
}

/* ---------------- */

DCAMERR DCAMAPI dcamprop_getvaluetext( HDCAM h, DCAMPROP_VALUETEXT* param )
{
	if( entry.prop_getvaluetext == NULL )
		return DCAMERR_NOMODULE;

	return entry.prop_getvaluetext( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_alloc( HDCAM h, int32 framecount )
{
	if( entry.buf_alloc == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_alloc( h, framecount );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_attach( HDCAM h, const DCAMBUF_ATTACH* param )
{
	if( entry.buf_attach == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_attach( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_release( HDCAM h, int32 iKind )
{
	if( entry.buf_release == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_release( h, iKind );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_lockframe( HDCAM h, DCAMBUF_FRAME* pFrame )
{
	if( entry.buf_lockframe == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_lockframe( h, pFrame );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_copyframe( HDCAM h, DCAMBUF_FRAME* pFrame )
{
	if( entry.buf_copyframe == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_copyframe( h, pFrame );
}

/* ---------------- */

DCAMERR DCAMAPI dcambuf_copymetadata( HDCAM h, DCAM_METADATAHDR* hdr )
{
	if( entry.buf_copymetadata == NULL )
		return DCAMERR_NOMODULE;

	return entry.buf_copymetadata( h, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_start( HDCAM h, int32 mode )
{
	if( entry.cap_start == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_start( h, mode );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_stop( HDCAM h )
{
	if( entry.cap_stop == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_stop( h );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_status( HDCAM h, int32* pStatus )
{
	if( entry.cap_status == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_status( h, pStatus );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_transferinfo( HDCAM h, DCAMCAP_TRANSFERINFO* param )
{
	if( entry.cap_transferinfo == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_transferinfo( h, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_firetrigger( HDCAM h, int32 iKind )
{
	if( entry.cap_firetrigger == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_firetrigger( h, iKind );
}

/* ---------------- */

DCAMERR DCAMAPI dcamcap_record( HDCAM h, HDCAMREC hrec )
{
	if( entry.cap_record == NULL )
		return DCAMERR_NOMODULE;

	return entry.cap_record( h, hrec );
}

/* ---------------- */

DCAMERR DCAMAPI dcamwait_open( DCAMWAIT_OPEN* param )
{
	if( entry.wait_open == NULL )
		return DCAMERR_NOMODULE;

	return entry.wait_open( param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamwait_close( HDCAMWAIT hWait )
{
	if( entry.wait_close == NULL )
		return DCAMERR_NOMODULE;

	return entry.wait_close( hWait );
}

/* ---------------- */

DCAMERR DCAMAPI dcamwait_start( HDCAMWAIT hWait, DCAMWAIT_START* param )
{
	if( entry.wait_start == NULL )
		return DCAMERR_NOMODULE;

	return entry.wait_start( hWait, param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamwait_abort( HDCAMWAIT hWait )
{
	if( entry.wait_abort == NULL )
		return DCAMERR_NOMODULE;

	return entry.wait_abort( hWait );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_openA( DCAMREC_OPENA* param )
{
	if( entry.rec_openA == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_openA( param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_openW( DCAMREC_OPENW* param )
{
	if( entry.rec_openW == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_openW( param );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_close( HDCAMREC hrec )
{
	if( entry.rec_close == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_close( hrec );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_lockframe( HDCAMREC hrec, DCAMREC_FRAME* pFrame )
{
	if( entry.rec_lockframe == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_lockframe( hrec, pFrame );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_copyframe( HDCAMREC hrec, DCAMREC_FRAME* pFrame )
{
	if( entry.rec_copyframe == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_copyframe( hrec, pFrame );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_writemetadata( HDCAMREC hrec, const DCAM_METADATAHDR* hdr )
{
	if( entry.rec_writemetadata == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_writemetadata( hrec, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_lockmetadata( HDCAMREC hrec, DCAM_METADATAHDR* hdr )
{
	if( entry.rec_lockmetadata == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_lockmetadata( hrec, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_copymetadata( HDCAMREC hrec, DCAM_METADATAHDR* hdr )
{
	if( entry.rec_copymetadata == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_copymetadata( hrec, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_lockmetadatablock( HDCAMREC hrec, DCAM_METADATABLOCKHDR* hdr )
{
	if( entry.rec_lockmetadatablock == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_lockmetadatablock( hrec, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_copymetadatablock( HDCAMREC hrec, DCAM_METADATABLOCKHDR* hdr )
{
	if( entry.rec_copymetadatablock == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_copymetadatablock( hrec, hdr );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_pause( HDCAMREC hrec )
{
	if( entry.rec_pause == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_pause( hrec );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_resume( HDCAMREC hrec )
{
	if( entry.rec_resume == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_resume( hrec );
}

/* ---------------- */

DCAMERR DCAMAPI dcamrec_status( HDCAMREC hrec, DCAMREC_STATUS* pStatus )
{
	if( entry.rec_status == NULL )
		return DCAMERR_NOMODULE;

	return entry.rec_status( hrec, pStatus );
}

