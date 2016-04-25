#ifndef PRAPI_INCL
#define PRAPI_INCL
/*******************************************************************************
 * PR API 2004-2015 (c) ARH Inc.
 * 2015.03.18 v2.1.5.25
 ******************************************************************************/
#ifdef GX_DOTNET
	#using "gxdotnet7.dll"
#endif
#ifndef __cplusplus
	#define USE_COMPAT_VARIANT_1
#endif
#include "gxsd.h"
#include "prtypes.h"
#include "prerror.h"
#include "prdoctypes.h"
#include "gximage.h"
#include "gxtrafo.h"

#if defined(WIN32) && !defined(GX_DOTNET)
	#include <windows.h>
#endif
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4786)		/* truncated debug info */
#endif
#ifdef __BORLANDC__
	#pragma warn -rch
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace pr {
#endif

/**
 * \mainpage Passport Reader
 *
 * \section pr_sdk The Passport Reader SDK
 *
 * The \b Passport \b Reader is a travel document reader and analyser system by
 * <b>ARH Inc.</b>, which bases on the GX system and provides for software developers an
 * easy-to-program interface through its \e Application \e Programming \e Interface (\e API).
 * Currently the supported programming languages and the usable interfaces are the
 * followings: C, C++ (\c prapi.h); Java (\c jpr.jar); VB.Net, C# (\c prdotnet7.dll);
 * VBasic 6, Delphi (\c prapi.ocx).
 *
 * \if C
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the PR system.
 *		It contains the description of definitions, enumerations and functions for the ANSI C programming language.
 * \elseif CPP
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the PR system.
 *		It contains the description of definitions, enumerations, functions and classes for the C++ programming language.
 * \elseif NET
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the PR system.
 *		It contains the description of enumerations and classes for the .NET framework.
 * \endif
 *
 * \section pr_sec_basic Basic functionality
 *
 * The functionality of the Passport Reader is centered upon two base functions.
 * The \a Capture function takes images of the document at different lightnings and
 * stores the binary data in computer understandable format (bitmap). The \a Recognize
 * function analyses the taken image and generates text data in computer
 * understandable format (ascii/unicode). These representations can be later inserted
 * in a database or processed by other user programs.
 *
 * \section pr_sec_detail Detailed functionality
 *
 * The functionality of the Passport Reader is groupped as following:
 *	- \ref pr_group_devhand "Device handling"
 *	- \ref pr_group_capture "Image handling"
 *	- \ref pr_group_document "Document handling"
 *	- \ref pr_group_rfid "RFID handling"
 *	- <b>Other functions</b>
 *
 * \ifnot NET
 *		Next browse the groups list, check the \ref prapi.h for full reference or check the
 *		Change Log in the reference manual for differences against the previous versions.
 * \else
 *		Next browse the class and enumeration specifications for full reference or check the
 *		Change Log in the reference manual for differences against the previous versions.
 * \endif
 *
 * For complete understanding of the system internals please consult the \ref gx_progman
 * "GX programmers' manual".
 *
 */

/** \defgroup pr_group_devhand Device handling
 *
 * Functions for controlling the device.
 */

/** \defgroup pr_group_capture Image handling
 *
 * Functions for capturing, displaying and saving images.
 */

/** \defgroup pr_group_document Document handling
 *
 * Functions for recognizing, reading and handling documents.
 */

/** \defgroup pr_group_rfid RFID handling
 *
 * Functions for managing e-Passports.
 */

/**
 * \file prapi.h
 * <b>Passport Reader Api functions</b>
 *
 * The  Passport Reader  is a  travel  document  reader  and analyser  system by
 * <b>ARH Inc.</b>,  which bases  on the GX system.  The prapi.h is  the general
 * interface file for the Passport Reader package.
 *
 */

#ifndef GX_MANUAL
/* .NET Workarounds */
#ifdef GX_DOTNET
	#pragma unmanaged
	#define _GX_ENOENT 2
	#define _PR_UMODE_DISCONNECT 0
	#define _PR_PROP_TYPE_CONFIDENCE 3
	#define _PR_PROP_TYPE_RFID_FILES 2
	#define _PR_PROP_TYPE_BARCODE_TYPE 1
	#define _PR_DF_RFID_FACE 0x420000
	#define _PRV_RFIDDIR 0xd0500001
	#define _PRV_BARCODE 0xd0300000
	#define _PRV_CONFIDENCE 0xd0000005
	#define _GX_VARIANT_INT 1
	#define gxPG4 _gxPG4
	#ifdef WIN32
		#define HWND void*
		#define UINT unsigned int
	#endif
	#define GXVT GX_VARIANT_TYPES::
	#define GXVF GX_VARIANT_FLAGS::
	#define GXEC GX_ERROR_CODES::
#else
	#define _GX_ENOENT GX_ENOENT
	#define _PR_UMODE_DISCONNECT PR_UMODE_DISCONNECT
	#define _PR_PROP_TYPE_CONFIDENCE PR_PROP_TYPE_CONFIDENCE
	#define _PR_PROP_TYPE_RFID_FILES PR_PROP_TYPE_RFID_FILES
	#define _PR_PROP_TYPE_BARCODE_TYPE PR_PROP_TYPE_BARCODE_TYPE
	#define _PR_DF_RFID_FACE PR_DF_RFID_FACE
	#define _PRV_RFIDDIR PRV_RFIDDIR
	#define _PRV_BARCODE PRV_BARCODE
	#define _PRV_CONFIDENCE PRV_CONFIDENCE
	#define _GX_VARIANT_INT GX_VARIANT_INT
	#define GXVT
	#define GXVF
	#define GXEC
#endif
#endif/* GX_MANUAL */

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/

enum PR_MAXLEN_VALUES {
	MAX_LIGHTS = 8,		/* Maximum number of available light types */
};

/*******************************************************************************
 * call codes
 ******************************************************************************/

/* Call codes for the Passport Reader routines. */
enum {
	PR_CALL_GROUP_PRAPI						= 0x20080000,				/* Caller ID of the prapi module */
	PR_CALL_PRAPI_GETDEVICELIST				= PR_CALL_GROUP_PRAPI,		/* Call code of the pr_getdevicelist() function (Unicode version). */
	PR_CALL_PRAPI_GETDEVICELISTA			= PR_CALL_GROUP_PRAPI+1,	/* Call code of the pr_getdevicelist() function (ASCII version). */
	PR_CALL_PRAPI_USEDEVICE					= PR_CALL_GROUP_PRAPI+2,	/* Call code of the pr_usedevice() function (Unicode version). */
	PR_CALL_PRAPI_USEDEVICEA				= PR_CALL_GROUP_PRAPI+3,	/* Call code of the pr_usedevice() function (ASCII version). */
	PR_CALL_PRAPI_GETCONTROLLERHANDLE		= PR_CALL_GROUP_PRAPI+4,	/* Call code of the pr_getctrlhandle() function */
	PR_CALL_PRAPI_CALIBRATE					= PR_CALL_GROUP_PRAPI+60,	/* Call code of the pr_calibrate() function */
/*	PR_CALL_PRAPI_CALIBRATE_START			= PR_CALL_GROUP_PRAPI+6,
//	PR_CALL_PRAPI_CALIBRATE_GETSTATUS		= PR_CALL_GROUP_PRAPI+7,
//	PR_CALL_PRAPI_CALIBRATE_WAIT			= PR_CALL_GROUP_PRAPI+8, */
	PR_CALL_PRAPI_ISCALIBRATED				= PR_CALL_GROUP_PRAPI+61,	/* Call code of the pr_iscalibrated() function */
	PR_CALL_PRAPI_SETPAGELIGHT				= PR_CALL_GROUP_PRAPI+62,	/* Call code of the pr_setpagelight() function */
	PR_CALL_PRAPI_SETEVENTFUNCTION			= PR_CALL_GROUP_PRAPI+11,	/* Call code of the pr_seteventfunction() function */
	PR_CALL_PRAPI_TEST_DOCUMENT				= PR_CALL_GROUP_PRAPI+63,	/* Call code of the pr_testdocument() function */
	PR_CALL_PRAPI_CAPTURE					= PR_CALL_GROUP_PRAPI+13,	/* Call code of the pr_capture() function */
	PR_CALL_PRAPI_CAPTURE_START				= PR_CALL_GROUP_PRAPI+14,	/* Call code of the pr_capture_start() function */
	PR_CALL_PRAPI_CAPTURE_GETSTATUS			= PR_CALL_GROUP_PRAPI+15,	/* Call code of the pr_capture_getstatus() function */
	PR_CALL_PRAPI_CAPTURE_WAIT				= PR_CALL_GROUP_PRAPI+16,	/* Call code of the pr_capture_wait() function */
	PR_CALL_PRAPI_CAPTURE_PREVIEW			= PR_CALL_GROUP_PRAPI+64,	/* Call code of the pr_capture_preview() function */
	PR_CALL_PRAPI_SAVEIMAGE					= PR_CALL_GROUP_PRAPI+19,	/* Call code of the pr_saveimage() function (Unicode version). */
	PR_CALL_PRAPI_SAVEIMAGEA				= PR_CALL_GROUP_PRAPI+20,	/* Call code of the pr_saveimage() function (ASCII version). */
	PR_CALL_PRAPI_DRAWIMAGE					= PR_CALL_GROUP_PRAPI+21,	/* Call code of the pr_drawimage() function */
	PR_CALL_PRAPI_RESETDOCUMENT				= PR_CALL_GROUP_PRAPI+176,	/* Call code of the pr_resetdocument() function */
	PR_CALL_PRAPI_GETLIGHTNUMBER			= PR_CALL_GROUP_PRAPI+51,	/* Call code of the pr_getlightnumber() function */
	PR_CALL_PRAPI_GETRFIDCARDLIST			= PR_CALL_GROUP_PRAPI+126,	/* Call code of the pr_getrfidcardlist() function (Unicode version). */
	PR_CALL_PRAPI_GETRFIDCARDLISTA			= PR_CALL_GROUP_PRAPI+127,	/* Call code of the pr_getrfidcardlist() function (ASCII version). */
	PR_CALL_PRAPI_GETRFIDFILE				= PR_CALL_GROUP_PRAPI+73,	/* Call code of the pr_getrfidfile() function (Unicode version). */
	PR_CALL_PRAPI_GETRFIDFILEA				= PR_CALL_GROUP_PRAPI+74,	/* Call code of the pr_getrfidfile() function (ASCII version). */
	PR_CALL_PRAPI_GETLIGHTMASK				= PR_CALL_GROUP_PRAPI+65,	/* Call code of the pr_getlightmask() function */
	PR_CALL_PRAPI_GETWINDOWNUMBER			= PR_CALL_GROUP_PRAPI+66,	/* Call code of the pr_getwindownumber() function */
	PR_CALL_PRAPI_GETLIGHTLIST				= PR_CALL_GROUP_PRAPI+67,	/* Call code of the pr_getlightlist() function */
	PR_CALL_PRAPI_SET_STATUS_LED			= PR_CALL_GROUP_PRAPI+68,	/* Call code of the pr_setstatusled() function */
	PR_CALL_PRAPI_TEST_POWER				= PR_CALL_GROUP_PRAPI+69,	/* Call code of the pr_testpower() function */
	PR_CALL_PRAPI_TEST_BUTTON				= PR_CALL_GROUP_PRAPI+70,	/* Call code of the pr_testbutton() function */
	PR_CALL_PRAPI_MAKEBAC					= PR_CALL_GROUP_PRAPI+75,	/* Call code of the pr_makebac() function (Unicode version). */
	PR_CALL_PRAPI_MAKEBACA					= PR_CALL_GROUP_PRAPI+76,	/* Call code of the pr_makebac() function (ASCII version). */
	PR_CALL_PRAPI_MAKEPASSIVEAUTH			= PR_CALL_GROUP_PRAPI+77,	/* Call code of the pr_makepassiveauth() function (Unicode version). */
	PR_CALL_PRAPI_MAKEPASSIVEAUTHA			= PR_CALL_GROUP_PRAPI+78,	/* Call code of the pr_makepassiveauth() function (ASCII version). */
	PR_CALL_PRAPI_MAKEACTIVEAUTH			= PR_CALL_GROUP_PRAPI+79,	/* Call code of the pr_makeactiveauth() function (Unicode version). */
	PR_CALL_PRAPI_MAKEACTIVEAUTHA			= PR_CALL_GROUP_PRAPI+80,	/* Call code of the pr_makeactiveauth() function (ASCII version). */
	PR_CALL_PRAPI_BEGIN_WINDOW_MESSAGING	= PR_CALL_GROUP_PRAPI+82,	/* Call code of the pr_beginwindowmessaging() function */
	PR_CALL_PRAPI_END_WINDOW_MESSAGING		= PR_CALL_GROUP_PRAPI+83,	/* Call code of the pr_endwindowmessaging() function */
	PR_CALL_PRAPI_GET_BUTTON_EVENT			= PR_CALL_GROUP_PRAPI+84,	/* Call code of the pr_getbuttonevent() function */
	PR_CALL_PRAPI_SUSPEND					= PR_CALL_GROUP_PRAPI+85,	/* Call code of the pr_suspend() function */
	PR_CALL_PRAPI_WAKEUP					= PR_CALL_GROUP_PRAPI+86,	/* Call code of the pr_wakeup() function */
	PR_CALL_PRAPI_LOADCERTFILE				= PR_CALL_GROUP_PRAPI+132,	/* Call code of the pr_loadcertfile() function (Unicode version). */
	PR_CALL_PRAPI_LOADCERTFILEA				= PR_CALL_GROUP_PRAPI+133,	/* Call code of the pr_loadcertfile() function (ASCII version). */
	PR_CALL_PRAPI_GET_UDINFO				= PR_CALL_GROUP_PRAPI+94,	/* Call code of the pr_getudinfo() function */
	PR_CALL_PRAPI_READ_UD					= PR_CALL_GROUP_PRAPI+95,	/* Call code of the pr_readudata() function */
	PR_CALL_PRAPI_WRITE_UD					= PR_CALL_GROUP_PRAPI+96,	/* Call code of the pr_writeudata() function */
	PR_CALL_PRAPI_GETOCR_V					= PR_CALL_GROUP_PRAPI+97,	/* Call code of the pr_getocr() function */
	PR_CALL_PRAPI_GETMRZ_V					= PR_CALL_GROUP_PRAPI+98,	/* Call code of the pr_getmrz() function */
	PR_CALL_PRAPI_GETBARCODE_V				= PR_CALL_GROUP_PRAPI+99,	/* Call code of the pr_getbarcode() function */
	PR_CALL_PRAPI_GETDOCUMENTRECT_V			= PR_CALL_GROUP_PRAPI+100,	/* Call code of the pr_getdocumentrect() function */
	PR_CALL_PRAPI_RECOGNIZE_V				= PR_CALL_GROUP_PRAPI+101,	/* Call code of the pr_recognize() function */
	PR_CALL_PRAPI_RESOLVEMRZTEXT_V			= PR_CALL_GROUP_PRAPI+102,	/* Call code of the pr_resolvemrztext() function */
	PR_CALL_PRAPI_RESOLVEMRZTEXTA_V			= PR_CALL_GROUP_PRAPI+103,	/* Call code of the pr_resolvemrztext() function */
	PR_CALL_PRAPI_RESOLVERFIDDATA_V			= PR_CALL_GROUP_PRAPI+104,	/* Call code of the pr_resolverfiddata() function */
	PR_CALL_PRAPI_GETDOCUMENTSTATUS_V		= PR_CALL_GROUP_PRAPI+105,	/* Call code of the pr_getdocumentstatus() function */
	PR_CALL_PRAPI_GETFIELDFROMDOC_V			= PR_CALL_GROUP_PRAPI+106,	/* Call code of the pr_getfieldfromdoc() function */
	PR_CALL_PRAPI_GETFIELDIMAGE_V			= PR_CALL_GROUP_PRAPI+107,	/* Call code of the pr_getfieldimage() function */
	PR_CALL_PRAPI_COMPARE_FACE_V			= PR_CALL_GROUP_PRAPI+108,	/* Call code of the pr_compareface() function */
	PR_CALL_PRAPI_SAVEDOCUMENT_V			= PR_CALL_GROUP_PRAPI+109,	/* Call code of the pr_savedocument() function */
	PR_CALL_PRAPI_SAVEDOCUMENTA_V			= PR_CALL_GROUP_PRAPI+110,	/* Call code of the pr_savedocument() function */
	PR_CALL_PRAPI_LOADDOCUMENT_V			= PR_CALL_GROUP_PRAPI+111,	/* Call code of the pr_loaddocument() function */
	PR_CALL_PRAPI_LOADDOCUMENTA_V			= PR_CALL_GROUP_PRAPI+112,	/* Call code of the pr_loaddocument() function */
	PR_CALL_PRAPI_GETDOCUMENTROOT_V			= PR_CALL_GROUP_PRAPI+113,	/* Call code of the pr_getdocumentroot() function */
	PR_CALL_PRAPI_CONNECTRFIDCARD			= PR_CALL_GROUP_PRAPI+118,	/* Call code of the pr_connectrfidcard() function (Unicode version). */
	PR_CALL_PRAPI_CONNECTRFIDCARDA			= PR_CALL_GROUP_PRAPI+119,	/* Call code of the pr_connectrfidcard() function (ASCII version). */
	PR_CALL_PRAPI_DISCONNECTRFIDCARD		= PR_CALL_GROUP_PRAPI+120,	/* Call code of the pr_disconnectrfidcard() function (Unicode version). */
	PR_CALL_PRAPI_DISCONNECTRFIDCARDA		= PR_CALL_GROUP_PRAPI+121,	/* Call code of the pr_disconnectrfidcard() function (ASCII version). */
	PR_CALL_PRAPI_MAKECHIPAUTH				= PR_CALL_GROUP_PRAPI+122,	/* Call code of the pr_makechipauth() function (Unicode version). */
	PR_CALL_PRAPI_MAKECHIPAUTHA				= PR_CALL_GROUP_PRAPI+123,	/* Call code of the pr_makechipauth() function (ASCII version). */
	PR_CALL_PRAPI_MAKETERMINALAUTH			= PR_CALL_GROUP_PRAPI+124,	/* Call code of the pr_maketerminalauth() function (Unicode version). */
	PR_CALL_PRAPI_MAKETERMINALAUTHA			= PR_CALL_GROUP_PRAPI+125,	/* Call code of the pr_maketerminalauth() function (ASCII version). */
	PR_CALL_PRAPI_CHECKRFIDFILEHASH			= PR_CALL_GROUP_PRAPI+128,	/* Call code of the pr_checkrfidfilehash() function (Unicode version). */
	PR_CALL_PRAPI_CHECKRFIDFILEHASHA		= PR_CALL_GROUP_PRAPI+129,	/* Call code of the pr_checkrfidfilehash() function (ASCII version). */
	PR_CALL_PRAPI_GETIMAGE_V				= PR_CALL_GROUP_PRAPI+130,	/* Call code of the pr_getimage() function */
	PR_CALL_PRAPI_GETDEVICEINFO				= PR_CALL_GROUP_PRAPI+131,	/* Call code of the pr_getdeviceinfo() function */
	PR_CALL_PRAPI_GETRFIDCARDINFO			= PR_CALL_GROUP_PRAPI+134,	/* Call code of the pr_getrfidcardinfo() function (Unicode version). */
	PR_CALL_PRAPI_GETRFIDCARDINFOA			= PR_CALL_GROUP_PRAPI+135,	/* Call code of the pr_getrfidcardinfo() function (ASCII version). */
	PR_CALL_PRAPI_FINGERSTONIST				= PR_CALL_GROUP_PRAPI+139,	/* Call code of the pr_fingertonist() function */
	PR_CALL_PRAPI_FINGERSTONISTA			= PR_CALL_GROUP_PRAPI+140,	/* Call code of the pr_fingertonista() function */
	PR_CALL_PRAPI_FINGERSTONISTMEM			= PR_CALL_GROUP_PRAPI+141,	/* Call code of the pr_fingertonistmem() function */
	PR_CALL_PRAPI_INITTERMINALAUTH			= PR_CALL_GROUP_PRAPI+142,	/* Call code of the pr_initta() function */
	PR_CALL_PRAPI_INITTERMINALAUTHA			= PR_CALL_GROUP_PRAPI+143,	/* Call code of the pr_inittaa() function */
	PR_CALL_PRAPI_COMPLETETERMINALAUTH		= PR_CALL_GROUP_PRAPI+144,	/* Call code of the pr_completeta() function */
	PR_CALL_PRAPI_COMPLETETERMINALAUTHA		= PR_CALL_GROUP_PRAPI+145,	/* Call code of the pr_completetaa() function */
	PR_CALL_PRAPI_CLEARCERTLIST				= PR_CALL_GROUP_PRAPI+146,	/* Call code of the pr_clearcertlist() function */
	PR_CALL_PRAPI_BLINK_STATUS				= PR_CALL_GROUP_PRAPI+151,	/* Call code of the pr_blinkstatus() function */
	PR_CALL_PRAPI_LOADCERTFROMMEM			= PR_CALL_GROUP_PRAPI+152,	/* Call code of the pr_loadcertfrommem() function */
	PR_CALL_PRAPI_SELFTEST					= PR_CALL_GROUP_PRAPI+153,	/* Call code of the pr_selftest() function */
	PR_CALL_PRAPI_DECODELATENTIMAGE			= PR_CALL_GROUP_PRAPI+154,	/* Call code of the pr_decodelatentimage() function */
	PR_CALL_PRAPI_MAKEPACE					= PR_CALL_GROUP_PRAPI+155,	/* Call code of the pr_makepace() function */
	PR_CALL_PRAPI_MAKEPACEA					= PR_CALL_GROUP_PRAPI+156,	/* Call code of the pr_makepacea() function */
	PR_CALL_PRAPI_GETCERTIFICATEID			= PR_CALL_GROUP_PRAPI+157,	/* Call code of the pr_getcertificateid() function */
	PR_CALL_PRAPI_GETCERTIFICATEIDA			= PR_CALL_GROUP_PRAPI+158,	/* Call code of the pr_getcertificateida() function */
	PR_CALL_PRAPI_GETNEXTAUTHENTICATION		= PR_CALL_GROUP_PRAPI+159,	/* Call code of the pr_getnextauthentication() function */
	PR_CALL_PRAPI_GETNEXTAUTHENTICATIONA	= PR_CALL_GROUP_PRAPI+160,	/* Call code of the pr_getnextauthenticationa() function */
	PR_CALL_PRAPI_READMAGSTRIPE				= PR_CALL_GROUP_PRAPI+163,	/* Call code of the pr_readmagstripe() function */
	PR_CALL_PRAPI_READMAGSTRIPEA			= PR_CALL_GROUP_PRAPI+164,	/* Call code of the pr_readmagstripea() function */
	PR_CALL_PRAPI_LOADCERTFROMSTORE			= PR_CALL_GROUP_PRAPI+165,	/* Call code of the pr_loadcertfromstore() function */
	PR_CALL_PRAPI_LOADCERTFROMSTOREA		= PR_CALL_GROUP_PRAPI+166,	/* Call code of the pr_loadcertfromstorea() function */
	PR_CALL_PRAPI_RESOLVEMAGSTRIPE			= PR_CALL_GROUP_PRAPI+167,	/* Call code of the pr_resolvemagstripe() function */
	PR_CALL_PRAPI_RESOLVEMAGSTRIPEA			= PR_CALL_GROUP_PRAPI+168,	/* Call code of the pr_resolvemagstripea() function */
	PR_CALL_PRAPI_GETENHANCEDUV				= PR_CALL_GROUP_PRAPI+169,  /* Call code of the pr_getenhanceduv() function */
	PR_CALL_PRAPI_DOAUTHENTICATION			= PR_CALL_GROUP_PRAPI+170,	/* Call code of the pr_doauthentication() function */
	PR_CALL_PRAPI_DOAUTHENTICATIONA			= PR_CALL_GROUP_PRAPI+171,	/* Call code of the pr_doauthenticationa() function */
	PR_CALL_PRAPI_SELECT_APPLICATION		= PR_CALL_GROUP_PRAPI+172,	/* Call code of the pr_selectapplication() function */
	PR_CALL_PRAPI_SELECT_APPLICATIONA		= PR_CALL_GROUP_PRAPI+173,	/* Call code of the pr_selectapplicationa() function */
	PR_CALL_PRAPI_GETAPPLICATIONS			= PR_CALL_GROUP_PRAPI+174,	/* Call code of the pr_selectapplication() function */
	PR_CALL_PRAPI_GETAPPLICATIONSA			= PR_CALL_GROUP_PRAPI+175,	/* Call code of the pr_selectapplicationa() function */
	PR_CALL_PRAPI_GETRFIDFILE_START			= PR_CALL_GROUP_PRAPI+177,	/* Call code of the pr_getrfidfile_start() function (Unicode version). */
	PR_CALL_PRAPI_GETRFIDFILE_STARTA		= PR_CALL_GROUP_PRAPI+178,	/* Call code of the pr_getrfidfile_start() function (ASCII version). */
	PR_CALL_PRAPI_GETRFIDFILE_GETSTATUS		= PR_CALL_GROUP_PRAPI+179,	/* Call code of the pr_getrfidfile_getstatus() function. */
	PR_CALL_PRAPI_GETRFIDFILE_WAIT			= PR_CALL_GROUP_PRAPI+180,	/* Call code of the pr_getrfidfile_wait() function. */
	PR_CALL_PRAPI_GETRFIDFILE_STOP			= PR_CALL_GROUP_PRAPI+181,	/* Call code of the pr_getrfidfile_stop() function. */
	PR_CALL_PRAPI_SAVEDOCUMENTTOMEM			= PR_CALL_GROUP_PRAPI+182,	/* Call code of the pr_savedocumenttomem() function. */
	PR_CALL_PRAPI_LOADDOCUMENTFROMMEM		= PR_CALL_GROUP_PRAPI+183,	/* Call code of the pr_loaddocumentfrommem() function. */
	PR_CALL_PRAPI_ANALYZE					= PR_CALL_GROUP_PRAPI+184,	/* Call code of the pr_analyze() function */
	PR_CALL_PRAPI_ANALYZED					= PR_CALL_GROUP_PRAPI+185,	/* Call code of the pr_analyze() function */
	PR_CALL_PRAPI_GETREADERCARDLIST			= PR_CALL_GROUP_PRAPI+186,	/* Call code of the pr_getmagstripedatalength() function */
	PR_CALL_PRAPI_GETFILELIST				= PR_CALL_GROUP_PRAPI+187,	/* Call code of the pr_getmagstripedatalength() function */
																		/* 188: Call code of the pr_fingerminutiatomem() function */
																		/* 189: Call code of the pr_fingerminutiatofile() function */
																		/* 190:Call code of the pr_fingerminutiatofilea() function */
	PR_CALL_PRAPI_CLEARCERTLISTSCOPE		= PR_CALL_GROUP_PRAPI+191,
	PR_CALL_PRAPI_LOADCERTSCOPE				= PR_CALL_GROUP_PRAPI+192,
	PR_CALL_PRAPI_OPEN_CARDREADER			= PR_CALL_GROUP_PRAPI+193,
	PR_CALL_PRAPI_CLOSE_CARDREADER			= PR_CALL_GROUP_PRAPI+194,
	PR_CALL_PRAPI_CONVERTFID				= PR_CALL_GROUP_PRAPI+195,	/* Call code of the pr_convertfid() function (Unicode). */
	PR_CALL_PRAPI_GETAUTHRESULT				= PR_CALL_GROUP_PRAPI+196,	/* Call code of the pr_getrfidauthresult() function (Unicode). */
};

/*******************************************************************************
 * module structures
 ******************************************************************************/

/*
	Parameter structure for the pr_..._getstatus asynchronous functions.
*/
struct PR_PARM_PRAPI_GETSTATUS {
	int reqid;				/* Id returned by the pr_..._start asynchronous function. */
	int status;				/* The state of the process in percent, it can be negative when the task is in
								preprocess state. */
};

/*
	Parameter structure for the pr_getdevicelist() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETDEVICELIST {
	wchar_t **devices;		/* List of the device names. */
	bool *calibrated;		/* Obsolete parameter. */
	int ndevices;			/* Number of devices */
};

/*
	Parameter structure for the pr_getdevicelist() function (ASCII version).
*/
struct PR_PARM_PRAPI_GETDEVICELISTA {
	char **devices;			/* List of the device names. */
	bool *calibrated;		/* Obsolete parameter. */
	int ndevices;			/* Number of the devices. */
};

/*
	Parameter structure for the pr_usedevice() function (Unicode version).
*/
struct PR_PARM_PRAPI_USEDEVICE {
	const wchar_t *device;	/* Name of the device to connect to. */
	int mode;				/* Connection mode. The possible values are defined in the \ref PR_USAGEMODE
								enumeration. Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use. */
};

/*
	Parameter structure for the pr_usedevice() function (ASCII version).
*/
struct PR_PARM_PRAPI_USEDEVICEA {
	const char *device;		/* Name of the device to connect to. */
	int mode;				/* Connection mode. The possible values are defined in the \ref PR_USAGEMODE
								enumeration. Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use. */
};

/*
	Parameter structure for the pr_getctrlhandle() function.
*/
struct PR_PARM_PRAPI_GETCONTROLLERHANDLE {
	gxHANDLE *handle;		/* Handle for the hardware control module. */
};

/*
	Parameter structure for the pr_calibrate() function.
*/
struct PR_PARM_PRAPI_CALIBRATE {
	int windowid;			/* Id of the used window. The possible values are defined in the \ref PR_WINDOW_ID
								enumeration. */
};

/*
	Parameter structure for the pr_iscalibrated() function.
*/
struct PR_PARM_PRAPI_ISCALIBRATED {
	int windowid;			/* Id of the used window. The possible values are defined in the \ref PR_WINDOW_ID
								enumeration. */
};

/*
	Parameter structure for the pr_setpagelight() function.
*/
struct PR_PARM_PRAPI_SETPAGELIGHT {
	int pages;				/* Number of document pages to read. */

	/* Array of light masks where each integer represents a page.
	 * Each lower bit of them represents a light mask bit. The upper 8 bits represent the
	 * id of the object window. The light mask bits can be tested by the pr_getlightmask()
	 * function. The object window ids are defined in the \ref PR_WINDOW_ID enumeration. */
	unsigned int *lights;
};

/*
	Parameter structure for the pr_resetdocument() function.
*/
struct PR_PARM_PRAPI_RESETDOCUMENT {
	int lastpage;			/* Reset only last page or all. */
};

#endif/* GX_SWIGIF GX_MANUAL )*/
#if !defined(GX_SWIGIF) && !(defined(GX_MANUAL) && defined(GX_DOTNET))	/*(*/

/** \addtogroup pr_group_capture
 * @{
 */

/** The event function is a callback function which is called during capture.
 *
 * The event function of the PR system can be set with pr_seteventfunction().
 *
 * @param event		The event Id.
 * @param param1	The actual page if it is meaningful.
 * @param param2	The actual light if it is meaningful.
 * @param uparam	User parameter.
*/
typedef void GXAPI PR_EVFUNC(int event,int param1,int param2,void* uparam);

/** @} */

#endif/* GX_SWIGIF GX_MANUAL GX_DOTNET )*/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/

/*
	Parameter structure for the pr_seteventfunction() function.
*/
struct PR_PARM_PRAPI_SETEVENTFUNCTION {
	PR_EVFUNC *func;		/* Reference to the callback function. */
	void *param;			/* User parameter. */
};

/*
	Parameter structure for the pr_testdocument() function.
*/
struct PR_PARM_PRAPI_TEST_DOCUMENT {
	int state;				/* The result of the document (motion) test. */
	int windowid;			/* Id of the used window. The possible values are defined in the \ref PR_WINDOW_ID
								enumeration. */
};

/*
	Parameter structure for the pr_capture_start() function.
*/
struct PR_PARM_PRAPI_CAPTURE_START {
	int reqid;				/* Returned id for use in pr_capture_getstatus() and pr_capture_wait()
								functions. */
};

/*
	Parameter structure for the pr_capture_wait() function.
*/
struct PR_PARM_PRAPI_CAPTURE_WAIT {
	int reqid;				/* Id returned by the pr_capture_start() function. */
};

/*
	Parameter structure for the pr_capture_preview() function.
*/
struct PR_PARM_PRAPI_CAPTURE_PREVIEW {
	int windowid;			/* Id of the used window. The possible values are defined in the \ref PR_WINDOW_ID enumeration. */
};

/*
	Parameter structure for the pr_getimage() function.
*/
struct PR_PARM_PRAPI_GETIMAGE_V {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. The possible values are defined in the \ref PR_IMAGE_TYPE
								enumeration. If the type is \ref PR_IT_PREVIEW the page and light parameters have no meanings. */
	gxVARIANT img;			/* Reference for the image. */
};

/*
	Parameter structure for thr pr_getenhanceduv() function.
*/
struct PR_PARM_PRAPI_GETENHANCEDUV {
	int page;				/* The actual page of the image. */
	int imgtype;			/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	gxVARIANT result;		/* The result uv image. */
};

/*
	Parameter structure for the pr_saveimage() function (Unicode version).
*/
struct PR_PARM_PRAPI_SAVEIMAGE {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. The possible values are defined in the \ref PR_IMAGE_TYPE
									enumeration. If the type is \ref PR_IT_PREVIEW the page and light parameters have no meanings. */
	const wchar_t *filename;/* The name of the file for saving the image. */
	int filetype;			/* The type of the file. The currently supported file types are defined in the file gximage.h . */
};

/*
	Parameter structure for the pr_saveimage() function (ASCII version).
*/
struct PR_PARM_PRAPI_SAVEIMAGEA {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. The possible values are defined in the \ref PR_IMAGE_TYPE
									enumeration. If the type is \ref PR_IT_PREVIEW the page and light parameters have no meanings. */
	const char *filename;	/* The name of the file for saving the image. */
	int filetype;			/* The type of the file. The currently supported file types are defined in the file gximage.h . */
};

#if defined(WIN32) && !defined(GX_DOTNET)

/*
	Parameter structure for the pr_drawimage() function.
*/
struct PR_PARM_PRAPI_DRAWIMAGE {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. The possible values are defined in the \ref PR_IMAGE_TYPE
								enumeration. If the type is \ref PR_IT_PREVIEW the page and light parameters have no meanings. */
	HDC hdc;				/* Handle to the device context. */
	int x;					/* Left side of the drawing area. */
	int y;					/* Upper side of the drawing area. */
	int xsize;				/* Horizontal size of the drawing area. */
	int ysize;				/* Vertical size of the drawing area. */
	gxRCT *frame;			/* Frame of the area of the image to display. */
};

#endif/* WIN32 GX_DOTNET */

/*
	Parameter structure for the pr_getlightnumber() function.
*/
struct PR_PARM_PRAPI_GETLIGHTNUMBER {
	int lights;				/* The number of the usable lights of the device. */
};

/*
	Parameter structure for the pr_getrfidcardlist() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETRFIDCARDLIST {
	wchar_t **cards;		/* List of card serial numbers. */
	int ncards;				/* Number of cards. */
};

/*
	Parameter structure for the pr_getrfidcardlist() function (ASCII version).
*/
struct PR_PARM_PRAPI_GETRFIDCARDLISTA {
	char **cards;			/* List of card serial numbers. */
	int ncards;				/* Number of cards. */
};

struct PR_PARM_PRAPI_GETREADERCARDLIST {
	wchar_t *reader;			/* Name of the selected cardreader. */
	wchar_t **cards;			/**< List of card serial numbers. */
	int ncards;					/**< Number of cards. */
};

struct PR_PARM_PRAPI_GETFILELIST {
	const wchar_t *card;		/* Serial number of the selected card. */
	int *files;
	int nfiles;					/**< Number of files. */
};

/*
	Parameter structure for the pr_getrfidfile() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETRFIDFILE {
	const wchar_t *card;	/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
	void *data;				/* File contents returned by the card. */
	int sdata;				/* Size of the returned data block. */
};

/*
	Parameter structure for the pr_getrfidfile() function (ASCII version).
*/
struct PR_PARM_PRAPI_GETRFIDFILEA {
	const char *card;		/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
	void *data;				/* File contents returned by the card. */
	int sdata;				/* Size of the returned data block. */
};

/*
	Parameter structure for the pr_getrfidfile_start() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETRFIDFILE_START {
	const wchar_t *card;	/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
	int reqid;				/* Returned id for use in pr_getrfidfile_getstatus() and pr_getrfidfile_wait()
								functions. */
};

/*
	Parameter structure for the pr_getrfidfile_start() function (ASCII version).
*/
struct PR_PARM_PRAPI_GETRFIDFILE_STARTA {
	const char *card;		/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
	int reqid;				/* Returned id for use in pr_getrfidfile_getstatus() and pr_getrfidfile_wait()
								functions. */
};

/*
	Parameter structure for the pr_getrfidfile_wait() function.
*/
struct PR_PARM_PRAPI_GETRFIDFILE_WAIT {
	int reqid;				/* Id returned by the pr_getrfidfile_start() function. */
	void *data;				/* File contents returned by the card. */
	int sdata;				/* Size of the returned data block. */
};

struct PR_PARM_PRAPI_OPEN_CARDREADER {
	const wchar_t *devname;		/**< Name of the selected reader. */
	gxVARIANT *devinfo;
};

struct PR_PARM_PRAPI_CLOSE_CARDREADER {
	const wchar_t *devname;		/**< Name of the selected reader. */
	gxVARIANT *devinfo;
};

/*
	Parameter structure for the pr_getlightmask() function.
*/
struct PR_PARM_PRAPI_GETLIGHTMASK {
	int lightid;			/* The id of the interesting light. The possible values are defined
								in the \ref PR_LIGHT enumeration. If this value is null the fuction returns the whole
								light mask of the given object window. */
	int windowid;			/* The id of the interesting object window. The possible values
								are defined in the \ref PR_WINDOW_ID enumeration. If the value is \ref PR_OW_DEFAULT (null)
								the fuction returns the light mask of the device. */
	int lightmask;			/* The result light mask. */
};

/*
	Parameter structure for the pr_getwindownumber() function.
*/
struct PR_PARM_PRAPI_GETWINDOWNUMBER {
	int windows;			/* The number of object windows of the device. */
};

/*
	Parameter structure for the pr_getlightlist() function.
*/
struct PR_PARM_PRAPI_GETLIGHTLIST {
	int *lightbuf;			/* Preallocated buffer for the lightlist items. */
	int nlights;			/* Size of the preallocated buffer. */
};

/*
	Parameter structure for the pr_setstatusled() function.
*/
struct PR_PARM_PRAPI_SET_STATUS_LED {
	int ledmask;			/* Mask representing the status leds. Each bit represents a status led on the device. */
	int color;				/* The color to display on the specified status leds. The predefined values of the lights
								are stored in the \ref PR_STATUS_LED_COLOR enumeration. Bit 7 represents the on/off
								parameter of the light so any value below 80 hex means led off.*/
};

/*
	Parameter structure for the pr_blinkstatus() function.
*/
struct PR_PARM_PRAPI_BLINK_STATUS {
	int coding;				/* Coding of the data. The possible values are:
								0: stop pulses,
								1: data[odd]: time duration output high level [ms], data[even]: time duration output low level [ms]
							*/
	int iteration;			/* Number of repeat, 0 means forever. */
	int mask;				/* Mask representing the status leds and buzzer. Each bit represents a status led or buzzer on the device. */
	int type;				/* Led color id or buzzer id. Its predefined values are stored in the
								\ref PR_STATUS_LED_COLOR and \ref PR_BUZZER enumerations. */
	unsigned int datalength;/* Length of the data, (maximum 16). */
	unsigned int *data;		/* Data of blinking. */
};

/*
	Parameter structure for the pr_testpower() function.
*/
struct PR_PARM_PRAPI_TEST_POWER {
	int state;				/* Device state mask. */
	int level;				/* Battery power level. */
};

/*
	Parameter structure for the pr_testbutton() function.
*/
struct PR_PARM_PRAPI_TEST_BUTTON {
	int code;				/* Code of the button. */
	int state;				/* State of the button. */
};

/*
	Parameter structure for the pr_getbuttonevent() function.
*/
struct PR_PARM_PRAPI_GET_BUTTON_EVENT {
	int code;				/* Code of the button. */
	int state;				/* State of the button. */
};

/*
	Parameter structure for the pr_getapplications() function (Unicode version).
*/
struct PR_PARM_PRAPI_GET_APPLICATIONS {
	const wchar_t *card;		/* Serial number of the selected card. */
	int *apps;					/* Array of the applications. The possible values are
									defined in the \ref PR_APP_TYPE enumeration. */
	int napps;					/* Number of items in the application array. */
};

/*
	Parameter structure for the pr_getapplications() function (ASCII version).
*/
struct PR_PARM_PRAPI_GET_APPLICATIONSA {
	const char *card;			/* Serial number of the selected card. */
	int *apps;					/* Array of the applications. The possible values are
									defined in the \ref PR_APP_TYPE enumeration. */
	int napps;					/* Number of items in the application array. */
};

/*
	Parameter structure for the pr_selectapplication() function (Unicode version).
*/
struct PR_PARM_PRAPI_SELECT_APPLICATION {
	const wchar_t *card;	/* Serial number of the selected card. */
	int application;		/* Application type. */
};

/*
	Parameter structure for the pr_selectapplication() function (ASCII version).
*/
struct PR_PARM_PRAPI_SELECT_APPLICATIONA {
	const char *card;		/* Serial number of the selected card. */
	int application;		/* Application type. */
};

/*
	Parameter structure for the pr_makebac() function (Unicode version).
*/
struct PR_PARM_PRAPI_MAKEBAC {
	const wchar_t *card;	/* Serial number of the selected card. */
	const wchar_t **lines;	/* Array of row string MRZ lines. */
	int nlines;				/* Number of rows. */
};

/*
	Parameter structure for the pr_makebac() function (ASCII version).
*/
struct PR_PARM_PRAPI_MAKEBACA {
	const char *card;		/* Serial number of the selected card. */
	const char **lines;		/* Array of row string MRZ lines. */
	int nlines;				/* Number of rows. */
};

/*
	Parameter structure for the pr_makepace() function (Unicode version).
*/
struct PR_PARM_PRAPI_MAKEPACE {
	const wchar_t *card;		/**< Serial number of the selected card. */
	const wchar_t **lines;		/**< Array of row string MRZ or CAN lines. */
	int nlines;					/**< Number of rows. */
	int PasswordType;			/**< The type of the password. The possible values are
 								defined in the \ref PR_PACE_PASSWORD enumeration.*/
};

/*
	Parameter structure for the pr_rfid_makepace() function (ASCII version).
*/
struct PR_PARM_PRAPI_MAKEPACEA {
	const char *card;			/**< Serial number of the selected card. */
	const char **lines;			/**< Array of row string MRZ or CAN lines. */
	int nlines;					/**< Number of rows. */
	int PasswordType;			/**< The type of the password. The possible values are
								defined in the \ref PR_PACE_PASSWORD enumeration.*/
};


/*
	Parameter structure for the pr_loadcertfile() function (Unicode version).
*/
struct PR_PARM_PRAPI_LOADCERTFILE {
	const wchar_t *certificate;	/* Name of the selected certificate file. */
	const wchar_t *privateKey;	/* Name of the private key file connected to the certificate. */
};

/*
	Parameter structure for the pr_loadcertfile() function (ASCII version).
*/
struct PR_PARM_PRAPI_LOADCERTFILEA {
	const char *certificate;	/* Name of the selected certificate file. */
	const char *privateKey;		/* Name of the private key file connected to the certificate. */
};

/*
	Parameter structure for the pr_loadcertfromstore() function (Unicode version).
*/
struct PR_PARM_PRAPI_LOADCERTFROMSTORE {
	const wchar_t *storename;	/* Name of the selected store. */
};

/*
	Parameter structure for the pr_loadcertfromstore() function (ASCII version).
*/
struct PR_PARM_PRAPI_LOADCERTFROMSTOREA {
	const char *storename;	/* Name of the selected store. */
};

/*
	Parameter structure for the pr_loadcertfrommem() function.
*/
struct PR_PARM_PRAPI_LOADCERTFROMMEM{
	void* certificate_data;
	unsigned int certificate_length;
	void* privateKey_data;
	unsigned int privateKey_length;
};


struct PR_PARM_PRAPI_LOADCERTSCOPE {
	int scope;
	const wchar_t *owner;
	
	void* certificate_data;
	unsigned int certificate_length;
	void* privateKey_data;
	unsigned int privateKey_length;
	
	unsigned int Id;
};

/*
	Parameter structure for the pr_beginwindowmessaging() function.
*/
struct PR_PARM_PRAPI_BEGIN_WINDOW_MESSAGING {
#if defined(WIN32)
	HWND hwnd;				/* Window handle to send the messages to. */
	UINT base_msg;			/* Message id base. */
#else
	int rfu1;
#endif
};


/*
	Parameter structure for the pr_getudinfo() function.
*/
struct PR_PARM_PRAPI_GET_UDINFO {
	int nblocks;			/* Number of blocks. */
	int sblock;				/* Size of a block. */
};

/*
	Parameter structure for the pr_readudata() function.
*/
struct PR_PARM_PRAPI_READ_UD {
	int fblock;				/* First block to read. */
	int nblocks;			/* Number of blocks to read. */
	void *data;				/* Bytes read. */
};

/*
	Parameter structure for the pr_writeudata() function.
*/
struct PR_PARM_PRAPI_WRITE_UD {
	int fblock;				/* First block to write. */
	int nblocks;			/* Number of blocks to write. */
	const void *data;		/* Bytes to write. */
};

/*
	Parameter structure for the pr_getocr() function.
*/
struct PR_PARM_PRAPI_GETOCR_V {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	gxVARIANT doc;			/* The result document structure. */
	gxVARIANT params;		/* OCR parameters */
};

/*
	Parameter structure for the pr_getmrz() function.
*/
struct PR_PARM_PRAPI_GETMRZ_V {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_getbarcode() function.
*/
struct PR_PARM_PRAPI_GETBARCODE_V {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	int bctype;				/* The needed barcode type. The possible values are defined in the \ref PR_BCTYPE
								enumeration. If this parameter is NULL any type of barcode can be returned. */
	int index;				/* The ordinal number of the barcode. If more barcodes found. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_getdocumentrect() function.
*/
struct PR_PARM_PRAPI_GETDOCUMENTRECT_V {
	int page;				/* The actual page of the image. */
	int light;				/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int type;				/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_recognize() function.
*/
struct PR_PARM_PRAPI_RECOGNIZE_V {
	int page;				/* The actual page of the image. */
	gxVARIANT doc;			/* The resulted document structure. */
};

/*
	Parameter structure for the pr_resolvemrztext() function (Unicode version).
*/
struct PR_PARM_PRAPI_RESOLVEMRZTEXT_V {
	const wchar_t **lines;	/* Array of row strings. */
	int nlines;				/* Number of rows. */
	gxVARIANT doc;			/* The resulted document structure. */
};

/*
	Parameter structure for the pr_resolvemrztext() function (ASCII version).
*/
struct PR_PARM_PRAPI_RESOLVEMRZTEXTA_V {
	const char **lines;		/* Array of row strings. */
	int nlines;				/* Number of rows. */
	gxVARIANT doc;			/* The resulted document structure. */
};

/*
	Parameter structure for the pr_resolverfiddata() function.
*/
struct PR_PARM_PRAPI_RESOLVERFIDDATA_V {
	const void *data;		/* Buffer to resolve data from. */
	int sdata;				/* The size of the data buffer. */
	gxVARIANT doc;			/* document to retrive the rfid data. */
};

/*
	Parameter structure for the pr_getdocumentstatus() function.
*/
struct PR_PARM_PRAPI_GETDOCUMENTSTATUS_V {
	gxVARIANT doc;			/* A document structure to analyse. */
	int code;				/* Code of the document. */
	int status;				/* The worst field error code in the document. The error codes are defined in
								\ref PR_CHKERR enumeration. */
};

/*
	Parameter structure for the pr_getfieldfromdoc() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETFIELDFROMDOC_V {
	gxVARIANT doc;			/* A document structure to analyse. */
	int field_code;			/* The id of the needed field. The possible ids are defined in the \ref PR_DOCFIELD enumeration. */
	int index;				/* Ordinal number of field. */
	gxVARIANT field;		/* The field structure. */
};

/*
	Parameter structure for the pr_getfieldimage() function.
*/
struct PR_PARM_PRAPI_GETFIELDIMAGE_V {
	gxVARIANT doc;			/* A document structure to analyse. */
	int field_code;			/* The id of the needed field. The possible ids are defined in the \ref PR_DOCFIELD enumeration. */
	int index;				/* Ordinal number of field. */
	gxVARIANT img;			/* The image of the field. */
};

/*
	Parameter structure for the pr_compareface() function.
*/
struct PR_PARM_PRAPI_COMPARE_FACE_V {
	int page;				/* The actual page of the image. */
	int face_no;			/* The ordinal number of the face image in rfid data. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_savedocument() function (Unicode version).
*/
struct PR_PARM_PRAPI_SAVEDOCUMENT_V {
	gxVARIANT doc;			/* Document to save. */
	const wchar_t *filename;/* Name of the file. */
	int filetype;			/* Type of the file ( see \ref PR_DOCFILEFORMATS ). */
};

/*
	Parameter structure for the pr_savedocumenta() function (ASCII version).
*/
struct PR_PARM_PRAPI_SAVEDOCUMENTA_V {
	gxVARIANT doc;			/* Document to save. */
	const char *filename;	/* Name of the file. */
	int filetype;			/* Type of the file ( see \ref PR_DOCFILEFORMATS ). */
};

/*
	Parameter structure for the pr_loaddocument() function (Unicode version).
*/
struct PR_PARM_PRAPI_LOADDOCUMENT_V {
	const wchar_t *filename;/* Name of the file to load the document from. */
	gxVARIANT doc;			/* Pointer to a document for returning the loaded document. */
};

/*
	Parameter structure for the pr_loaddocumenta() function (ASCII version).
*/
struct PR_PARM_PRAPI_LOADDOCUMENTA_V {
	const char *filename;	/* Name of the file to load the document from. */
	gxVARIANT doc;			/* Pointer to a document to return the loaded document. */
};

/*
	Parameter structure for the pr_getdocumentroot() function.
*/
struct PR_PARM_PRAPI_GETDOCUMENTROOT_V {
	gxVARIANT doc;			/* Pointer to a document for returning the requested document. */
};

/*
	Parameter structure for the
		pr_connectrfidcard(), pr_disconnectrfidcard(),
		pr_makepassiveauth(), pr_makeactiveauth(),
		pr_makechipauth() and pr_maketerminalauth()
	functions (Unicode version).
*/
struct PR_PARM_PRAPI_RFIDCARD {
	const wchar_t *card;	/* Serial number of the selected card. */
};

/*
	Parameter structure for the
		pr_connectrfidcard(), pr_disconnectrfidcard(),
		pr_makepassiveauth(), pr_makeactiveauth(),
		pr_makechipauth() and pr_maketerminalauth()
	functions (ASCII version).
*/
struct PR_PARM_PRAPI_RFIDCARDA {
	const char *card;		/* Serial number of the selected card. */
};

/*
	Parameter structure for the pr_initta() and pr_completeta() functions (Unicode version).
*/
struct PR_PARM_PRAPI_TA {
	const wchar_t *card;
	void *data;
	int sdata;
};

/*
	Parameter structure for the pr_initta() and pr_completeta() functions (ASCII version).
*/
struct PR_PARM_PRAPI_TAA {
	const char *card;
	void *data;
	int sdata;
};

/*
	Parameter structure for the pr_checkrfidfilehash() function (Unicode version).
*/
struct PR_PARM_PRAPI_CHECKRFIDFILEHASH {
	const wchar_t *card;	/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
};

/*
	Parameter structure for the pr_checkrfidfilehash() function (ASCII version).
*/
struct PR_PARM_PRAPI_CHECKRFIDFILEHASHA {
	const char *card;		/* Serial number of the selected card. */
	int fileid;				/* Identifier of the requested file. */
};

/*
	Parameter structure for the pr_getdeviceinfo() function.
*/
struct PR_PARM_PRAPI_GETDEVICEINFO {
	gxVARIANT devinfo;		/* Device info. */
};

/*
	Parameter structure for the pr_getrfidcardinfo() function (Unicode version).
*/
struct PR_PARM_PRAPI_GETRFIDCARDINFO {
	const wchar_t *card;
	gxVARIANT cardinfo;
};

/*
	Parameter structure for the pr_getrfidcardinfo() function (ASCII version).
*/
struct PR_PARM_PRAPI_GETRFIDCARDINFOA {
	const char *card;
	gxVARIANT cardinfo;
};

/*
	Parameter structure for the pr_fingertonist() function.
*/
struct PR_PARM_PRAPI_FINGERSTONIST {
	const wchar_t *filename;	/* The name of the file for saving the data. */
	gxVARIANT		fields;		/* List of fields to add to the record. */
};

/*
	Parameter structure for the pr_fingertonista() function.
*/
struct PR_PARM_PRAPI_FINGERSTONISTA {
	const char *filename;	/* The name of the file for saving the data. */
	gxVARIANT	fields;		/* List of fields to add to the record. */
};

/*
	Parameter structure for the pr_fingertonistmem() function.
*/
struct PR_PARM_PRAPI_FINGERSTONISTMEM {
	void	**buffer;		/* Pointer to a memory area pointer. */
	gxi32	*buflen;		/* Size of memory area. */
	gxVARIANT	fields;		/* List of fields to add to the record. */
};

/*
	Parameter structure for the pr_clearcertlist() function.
*/
struct PR_PARM_PRAPI_CLEARCERTLIST {
	int		sel;			/* List selector. */
};

struct PR_PARM_PRAPI_CLEARCERTLISTSCOPE {
	gxi32 sel;
	int scope;
	const wchar_t *owner;
};

/*
	Parameter structure for the pr_selftest() function.
*/
struct PR_PARM_PRAPI_SELFTEST {
	int condition;			/* Test control condition that declares the type of object which is placed on the document window. */
	gxVARIANT result;		/* A list of partial test results. */
};

/*
	Decodes a latent image from a stored image.
*/
struct PR_PARM_PRAPI_DECODELATENTIMAGE {
	int			  page;		/* The actual page of the image. */
	int			  light;	/* The light settings. The possible values are defined in the \ref PR_LIGHT enumeration. */
	int			  type;		/* The type of the image. It must be \ref PR_IT_ORIGINAL. */
	const wchar_t *decpar;	/* Decoding parameter. */
	gxVARIANT	  image;	/* The latent image. */
};

/*
	Parameter structure for the pr_getcertificateida() function.
*/
struct PR_PARM_PRAPI_GETCERTIFICATEIDA {
	const char *card;
	int Authentication;
	gxVARIANT CertId;
};

/*
	Parameter structure for the pr_getcertificateid() function.
*/
struct PR_PARM_PRAPI_GETCERTIFICATEID {
	const wchar_t *card;
	int Authentication;
	gxVARIANT CertId;
};

/*
	Parameter structure for the pr_getnextauthentication() function.
*/
struct PR_PARM_PRAPI_GETNEXTAUTHENTICATIONA {
	const char *card;
	int ProcessName;
	int ForceNext;
};

/*
	Parameter structure for the pr_getnextauthentication() function.
*/
struct PR_PARM_PRAPI_GETNEXTAUTHENTICATION {
	const wchar_t *card;
	int ProcessName;
	int ForceNext;
};

/*
	Parameter structure for the pr_doauthentication() function.
*/
struct PR_PARM_PRAPI_DOAUTHENTICATIONA {
	const char *card;
	int ProcessName;
	const char **AuthData;
	int Lines;
	int PasswordType;
};

/*
	Parameter structure for the pr_doauthentication() function.
*/
struct PR_PARM_PRAPI_DOAUTHENTICATION {
	const wchar_t *card;
	int ProcessName;
	const wchar_t **AuthData;
	int Lines;
	int PasswordType;
};

/*
	Parameter structure for the pr_readmagstripe() function.
*/
struct PR_PARM_PRAPI_READMAGSTRIPE {
	wchar_t **tracks;		/* List of data tracks. */
	int ntracks;			/* Number of tracks. */
};

/*
	Parameter structure for the pr_readmagstripea() function.
*/
struct PR_PARM_PRAPI_READMAGSTRIPEA {
	char **tracks;			/* List of data tracks. */
	int ntracks;			/* Number of tracks. */
};

/*
	Parameter structure for the pr_resolvemagstripe() function.
*/
struct PR_PARM_PRAPI_RESOLVEMAGSTRIPE {
	const wchar_t **tracks;	/* List of data tracks. */
	int ntracks;			/* Number of tracks. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_resolvemagstripea() function.
*/
struct PR_PARM_PRAPI_RESOLVEMAGSTRIPEA {
	const char **tracks;	/* List of data tracks. */
	int ntracks;			/* Number of tracks. */
	gxVARIANT doc;			/* The result document structure. */
};

/*
	Parameter structure for the pr_savedocumenttomem() function.
*/
struct PR_PARM_PRAPI_SAVEDOCUMENTTOMEM {
	gxVARIANT doc;			/* Document to save. */
	int filetype;			/* Type of the data ( see \ref PR_DOCFILEFORMATS ). */
	gxu8 **buffer;			/* Pointer to memory area pointer. */
	int *buflen;			/* Size of memory area. */
};

/*
	Parameter structure for the pr_loaddocumentfrommem() function.
*/
struct PR_PARM_PRAPI_LOADDOCUMENTFROMMEM {
	gxVARIANT doc;			/* Document to save. */
	const gxu8 *buffer;		/* Pointer to memory area. */
	int buflen;				/* Size of memory area. */
};

/*
	Parameter structure for the pr_analyze() function.
*/
struct PR_PARM_PRAPI_ANALYZE {
	gxVARIANT	page;		/* Input image list. */
	int			takslen;	/* Number of item in the tasklist. */
	int		   *task;		/* The tasklist */
	gxVARIANT	doc;		/* The resulted document structure. */
};

/*
	Parameter structure for the pr_analyze() function.
*/
struct PR_PARM_PRAPI_ANALYZED {
	gxu8	   *buffer;		/* Input buffer. */
	int			buflen;		/* Number of bytes in the buffer. */
	gxVARIANT	doc;		/* The resulted document structure. */
};

/*
	Parameter structure for the pr_convertfid() function (Unicode).
*/
struct PR_PARM_PRAPI_CONVERTFID {
	const wchar_t *card;
	int fid;
};

/*
	Parameter structure for the pr_getrfidauthresult() function (Unicode).
*/
struct PR_PARM_PRAPI_GETAUTHRESULT {
	const wchar_t *card;
	gxVARIANT doc;
};

#endif/* GX_SWIGIF GX_MANUAL )*/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)	/*(*/

/** \addtogroup pr_group_devhand
 * @{
 */

/** Returns a list of the available Passport Reader devices (Unicode version).
 *
 * The application must call the gx_globalfree() function to
 * free the allocated memory for the devices parameter.
 *
 * @param handle		Handle of the prapi module.
 * @param devices		List of the device names. Data returned by this function
 *						must be freed by the gx_globalfree() function.
 * @param ndevices		Number of devices.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getdevicelist(gxHANDLE handle,wchar_t ***devices,int *ndevices) {
	struct PR_PARM_PRAPI_GETDEVICELIST gdl;
	int ret;
	assert(devices && ndevices);
	ret = gx_call(handle, PR_CALL_PRAPI_GETDEVICELIST, &gdl);
	*devices = gdl.devices;
	*ndevices = gdl.ndevices;
	return ret;
}

/** Returns a list of the available Passport Reader devices (ASCII version).
 *
 * The application must call the gx_globalfree() function to
 * free the allocated memory for the devices parameter.
 *
 * @param handle		Handle of the prapi module.
 * @param devices		List of the device names. Data returned by this function
 *						must be freed by the gx_globalfree() function.
 * @param ndevices		Number of devices.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getdevicelista(gxHANDLE handle,char ***devices,int *ndevices) {
	struct PR_PARM_PRAPI_GETDEVICELISTA gdl;
	int ret;
	assert(devices && ndevices);
	ret = gx_call(handle, PR_CALL_PRAPI_GETDEVICELISTA, &gdl);
	*devices = gdl.devices;
	*ndevices = gdl.ndevices;
	return ret;
}

#ifdef __cplusplus
/** Returns a list of the available Passport Reader devices (ASCII version).
 *
 * The application must call the gx_globalfree() function to
 * free the allocated memory for the devices parameter.
 *
 * @param handle		Handle of the prapi module.
 * @param devices		List of the device names. Data returned by this function
 *						must be freed by the gx_globalfree() function.
 * @param ndevices		Number of devices.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getdevicelist(gxHANDLE handle,char ***devices,int *ndevices) {
	return pr_getdevicelista(handle,devices,ndevices);
}
#endif

/** Connects a PR device. To get a list of the available
 * devices call the pr_getdevicelist() function (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param device	Name of the device to connect to.
 * @param mode		Connection mode. The possible values are defined in the \ref PR_USAGEMODE enumeration.
 *					Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_usedevice(gxHANDLE handle,const wchar_t *device,int mode) {
	struct PR_PARM_PRAPI_USEDEVICE ud;
	assert(device);
	ud.device = device;
	ud.mode = mode;
	return gx_call(handle, PR_CALL_PRAPI_USEDEVICE, &ud);
}

/** Conects to a PR device. To get a list of the available
 * devices call the pr_getdevicelist() function (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param device	Name of the device to connect to.
 * @param mode		Connection mode. The possible values are defined in the \ref PR_USAGEMODE enumeration.
 *					Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_usedevicea(gxHANDLE handle,const char *device,int mode) {
	struct PR_PARM_PRAPI_USEDEVICEA ud;
	assert(device);
	ud.device = device;
	ud.mode = mode;
	return gx_call(handle, PR_CALL_PRAPI_USEDEVICEA, &ud);
}

/** Conects to a PR device.
 *
 * @param handle	Handle of the prapi module.
 * @param devno		Ordinal number of the device to connect to.
 * @param mode		Connection mode. The possible values are defined in the \ref PR_USAGEMODE enumeration.
 *					Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_usedevicen(gxHANDLE handle,int devno,int mode) {
	char **devlist;
	int ndev,ret;
	assert(devno>=0);

	if(!pr_getdevicelista(handle,&devlist,&ndev))return 0;
	if(ndev<=devno){
		if(ndev)gx_globalfree(devlist);
		gx_seterror(_GX_ENOENT,L"No device found");
		return false;
	}

	ret=pr_usedevicea(handle,devlist[devno],mode);
	gx_globalfree(devlist);
	return ret;
}

#ifdef __cplusplus
/** Conects to a PR device (ASCII version).
 *
 * To get a list of the available devices call the pr_getdevicelist() function.
 *
 * @param handle	Handle of the prapi module.
 * @param device	Name of the device to connect to.
 * @param mode		Connection mode. The possible values are defined in the \ref PR_USAGEMODE enumeration.
 *					Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_usedevice(gxHANDLE handle,const char *device,int mode) {
	return pr_usedevicea(handle,device,mode);
}

/** Conects to a PR device.
 *
 * @param handle	Handle of the prapi module.
 * @param devno		Ordinal number of the device to connect to.
 * @param mode		Connection mode. The possible values are defined in the \ref PR_USAGEMODE enumeration.
 *					Generally the \ref PR_UMODE_FULL_CONTROL is recommended to use.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_usedevice(gxHANDLE handle,int devno,int mode) {
	return pr_usedevicen(handle,devno,mode);
}
#endif

/** Disconnects the connected device.
 *
 * @param handle	Handle of the prapi module.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_closedevice(gxHANDLE handle) {
	struct PR_PARM_PRAPI_USEDEVICEA ud;
	ud.device = 0;
	ud.mode=_PR_UMODE_DISCONNECT;
	return gx_call(handle, PR_CALL_PRAPI_USEDEVICEA, &ud);
}

/** Returns a handle of the capturing device. This handle
 * can be used for special hardware controls that differs from the usual PR activities
 * such as status led flushing or start button testing. The handle is valid while the
 * the PR device is connected.
 *
 * @param handle	Handle of the prapi module.
 * @param hctrl		Handle of the hardware controlling module.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getctrlhandle(gxHANDLE handle,gxHANDLE **hctrl) {
	struct PR_PARM_PRAPI_GETCONTROLLERHANDLE gch;
	int ret;
	assert(hctrl);
	ret = gx_call(handle, PR_CALL_PRAPI_GETCONTROLLERHANDLE, &gch);
	*hctrl=gch.handle;
	return ret;
}

/** Calibrates the used device.
 *
 * Generates data for correcting the geometrical and colour distortions of the capturing system.
 * This process can take up to 20-70 seconds according to the computer's speed.
 * The \e calibration \e image is needed to be put on the document window.
 *
 * @param handle	Handle of the prapi module.
 * @param windowid	Id of the used window. The possible values are defined in
 *					\ref PR_WINDOW_ID enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_calibrate(gxHANDLE handle,int windowid GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_CALIBRATE cal;
	cal.windowid = windowid;
	return gx_call(handle, PR_CALL_PRAPI_CALIBRATE, &cal);
}

/** Tests the calibrated state of the device.
 *
 * @param handle	Handle of the prapi module.
 * @param windowid	Id of the used window. The possible values are defined in
 *					\ref PR_WINDOW_ID enumeration.
 * @return		If the device is calibrated the function returns true. Otherwise it
 *				returns false and the error code/string in the GX system is set appropriately.
 *				( see gx_geterror() ) */
inline int pr_iscalibrated(gxHANDLE handle,int windowid GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_ISCALIBRATED cal;
	cal.windowid = windowid;
	return gx_call(handle, PR_CALL_PRAPI_ISCALIBRATED, &cal);
}

/** Gives back the result of the document (motion) detector module.
 *
 * The possible
 * result values are defined in the \ref PR_TESTDOC enumeration. Call this function
 * 2-3 times in every second. When the result is \ref PR_TD_IN the document is ready
 * for capturing. The document detection is work only when the freerun_mode property
 * contains the \ref PR_FRMODE_TESTDOCUMENT value.
 *
 * @param handle	Handle of the prapi module.
 * @param state		Buffer for the result.
 * @param windowid	Id of the used window. The possible values are defined in
 *					\ref PR_WINDOW_ID enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_testdocument(gxHANDLE handle,int *state,int windowid GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_TEST_DOCUMENT td;
	int ret;
	assert(state);
	td.windowid = windowid;
	ret = gx_call(handle, PR_CALL_PRAPI_TEST_DOCUMENT, &td);
	if(state)*state = td.state;
	return ret;
}

/** Gives back the number of usable lights of the device.
 *
 * @param handle	Handle of the prapi module.
 * @param lights	Buffer for the number of usable lights.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getlightnumber(gxHANDLE handle,int *lights) {
	struct PR_PARM_PRAPI_GETLIGHTNUMBER li;
	int ret;
	assert(lights);
	ret = gx_call(handle, PR_CALL_PRAPI_GETLIGHTNUMBER, &li);
	if(lights) *lights = li.lights;
	return ret;
}

/** Gives back a light mask for a given light and window.
 *
 * It is usable to test if the a light is available for the device or one of its object windows.
 * It can return a whole light mask for a given object window if the lightid is null.
 * Light masks are used by the pr_setpagelight() function.
 *
 * @param handle	Handle of the prapi module.
 * @param lightmask	The result light mask.
 * @param lightid	The id of the interesting light. The possible values are defined
 *					in the \ref PR_LIGHT enumeration. If this value is null the fuction returns the whole
 *					light mask of the given object window.
 * @param windowid	The id of the interesting object window. The possible values
 *					are defined in the \ref PR_WINDOW_ID enumeration. If the value is \ref PR_OW_DEFAULT (null)
 *					the fuction returns the light mask of the device.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getlightmask(gxHANDLE handle,int *lightmask,int lightid,int windowid) {
	struct PR_PARM_PRAPI_GETLIGHTMASK ll;
	int ret;
	assert(lightmask);
	ll.lightid = lightid;
	ll.windowid = windowid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETLIGHTMASK, &ll);
	if(lightmask) *lightmask = ll.lightmask;
	return ret;
}

/** Gives back a list of usable lights of the device.
 *
 * @param handle	Handle of the prapi module.
 * @param lightbuf	Preallocated buffer for the list of the usable lights.
 * @param nlights	Number of lights.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getlightlist(gxHANDLE handle,int *lightbuf,int nlights) {
	struct PR_PARM_PRAPI_GETLIGHTLIST ll;
	assert(lightbuf);
	ll.lightbuf = lightbuf;
	ll.nlights = nlights;
	return gx_call(handle, PR_CALL_PRAPI_GETLIGHTLIST, &ll);
}

/** Gives back the number of object windows of the device.
 *
 * @param handle	Handle of the prapi module.
 * @param windows	Buffer for the number of object windows.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getwindownumber(gxHANDLE handle,int *windows) {
	struct PR_PARM_PRAPI_GETWINDOWNUMBER wi;
	int ret;
	assert(windows);
	ret = gx_call(handle, PR_CALL_PRAPI_GETWINDOWNUMBER, &wi);
	if(windows) *windows = wi.windows;
	return ret;
}

/** Turns on/off the status leds.
 *
 * @param handle	Handle of the prapi module.
 * @param ledmask	Mask representing the status leds. Each bit represents a status led on the device.
 * @param color		The color to display on the specified status leds. The predefined values of the lights
					are stored in the \ref PR_STATUS_LED_COLOR enumeration. Bit 7 represents the on/off
					parameter of the light so any value below 80 hex means led off.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_setstatusled(gxHANDLE handle, int ledmask, int color) {
	struct PR_PARM_PRAPI_SET_STATUS_LED led;
	led.ledmask = ledmask;
	led.color = color;
	return gx_call(handle, PR_CALL_PRAPI_SET_STATUS_LED, &led);
}

/** Blinks status outputs (led or buzzer).
 *
 * @param handle		Handle of the prapi module.
 * @param coding		Coding of the data. The possible values are:
							0: stop pulses,
							1: data[odd]: time duration output high level [ms], data[even]: time duration output low level [ms]
 * @param mask			Mask representing the status leds and buzzer. Each bit represents a status led or buzzer on the device.
 * @param type			Led color id or buzzer id. Its predefined values are stored in the \ref PR_STATUS_LED_COLOR
						and \ref PR_BUZZER enumerations.
 * @param iteration		Number of repeat, 0 menas forever.
 * @param data			Data of blinking.
 * @param datalength	Length of the data, (maximum 16).
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_blinkstatus(gxHANDLE handle, int coding, int mask, int type, int iteration, unsigned int *data, unsigned int datalength) {

	struct PR_PARM_PRAPI_BLINK_STATUS out_data;

	out_data.coding = coding;
	out_data.mask = mask;
	out_data.type = type;
	out_data.iteration = iteration;
	out_data.data = data;
	out_data.datalength = datalength;

	return gx_call(handle, PR_CALL_PRAPI_BLINK_STATUS, &out_data);
}

/** Gets the power state of the device.
 *
 * @param handle	Handle of the prapi module.
 * @param state		Buffer for the device power state.
 * @param level		Buffer for the battery power level.
					In case of devices without battery -1 is returned.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_testpower(gxHANDLE handle, int *state, int *level) {
	struct PR_PARM_PRAPI_TEST_POWER tp;
	int ret;
	assert(state);
	ret = gx_call(handle, PR_CALL_PRAPI_TEST_POWER, &tp);
	if(state)*state = tp.state;
	if(level)*level = tp.level;
	return ret;
}

/** Gets the device's button state.
 *
 * @param handle	Handle of the prapi module.
 * @param keycode	The code of the button/key.
 * @param state		Buffer for the button/key state.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_testbutton(gxHANDLE handle, int keycode, int *state) {
	struct PR_PARM_PRAPI_TEST_BUTTON bt;
	int ret;
	assert(state);
	bt.code = keycode;
	ret = gx_call(handle, PR_CALL_PRAPI_TEST_BUTTON, &bt);
	if(state)*state = bt.state;
	return ret;
}

/** Gets the device's next button event.
 *
 * @param handle	Handle of the prapi module.
 * @param keycode	Buffer for the button/key code.
 * @param state		Buffer for the button/key state.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getbuttonevent(gxHANDLE handle, int *keycode, int *state) {
	struct PR_PARM_PRAPI_GET_BUTTON_EVENT bt;
	int ret;
	assert(state);
	assert(keycode);
	ret = gx_call(handle, PR_CALL_PRAPI_GET_BUTTON_EVENT, &bt);
	if(state)*state = bt.state;
	if(keycode)*keycode = bt.code;
	return ret;
}

/** Suspends the Passport Reader system.
 *
 * It may be called for example when the operating system tries to suspend or
 * for power saving reasons you want to suspend the connected device. Depending on the
 * type of the device and the control level set different suspend levels can be reached.
 *
 * @param handle	Handle of the prapi module.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_suspend(gxHANDLE handle) {
	return gx_call(handle,PR_CALL_PRAPI_SUSPEND,0);
}

/** Wakes up the previously suspended Passport Reader system.
 *
 * @param handle	Handle of the prapi module.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_wakeup(gxHANDLE handle) {
	return gx_call(handle,PR_CALL_PRAPI_WAKEUP,0);
}

/** Gets information about the available user data space.
 *
 * @param handle	Handle of the prapi module.
 * @param nblocks	Number of blocks.
 * @param sblock	Size of a block.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getudinfo(gxHANDLE handle, int *nblocks, int *sblock) {
	struct PR_PARM_PRAPI_GET_UDINFO gi;
	int ret;
	assert(nblocks);
	assert(sblock);
	ret = gx_call(handle, PR_CALL_PRAPI_GET_UDINFO, &gi);
	if(nblocks)*nblocks = gi.nblocks;
	if(sblock)*sblock = gi.sblock;
	return ret;
}

/** Reads the user data from the device.
 *
 * The application must call the gx_globalfree() function for the data to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param fblock	First block to read.
 * @param nblocks	Number of blocks to read.
 * @param data		Bytes read.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_readudata(gxHANDLE handle, int fblock, int nblocks, void **data) {
	struct PR_PARM_PRAPI_READ_UD ru;
	int ret;
	assert(data);
	ru.fblock = fblock;
	ru.nblocks = nblocks;
	ret = gx_call(handle, PR_CALL_PRAPI_READ_UD, &ru);
	if(data)*data = ru.data;
	return ret;
}

/** Writes the user data in the used device.
 *
 * @param handle	Handle of the prapi module.
 * @param fblock	First block to write.
 * @param nblocks	Number of blocks to write.
 * @param data		Bytes to write.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_writeudata(gxHANDLE handle, int fblock, int nblocks, const void *data) {
	struct PR_PARM_PRAPI_WRITE_UD wu;
	wu.fblock = fblock;
	wu.nblocks = nblocks;
	wu.data = data;
	return gx_call(handle, PR_CALL_PRAPI_WRITE_UD, &wu);
}

/** Gets information about the device used.
 *
 * @param handle	Handle of the prapi module.
 * @param devinfo	Variant structure for device information.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getdeviceinfo(gxHANDLE handle, gxVARIANT *devinfo) {
	struct PR_PARM_PRAPI_GETDEVICEINFO gdi;
	int ret;
	assert(devinfo);
	ret = gx_call(handle, PR_CALL_PRAPI_GETDEVICEINFO, &gdi);
	if(ret && devinfo)*devinfo = gdi.devinfo;
	return ret;
}

/** Performs a device self test.
 *
 * @param handle		Handle of the prapi module.
 * @param condition		Test control condition that declares the type of object which is placed
 *						on the document window (0: unknown/nothing, 1: white image, 2: calibration image, 3: document with MRZ line)
 * @param result		A list of partial test results. The test element ids are defined in \ref PR_SELFTEST_ELEMENTS enumeration, and
 *						the result values are defined in \ref PR_SELFTEST_RESULT enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_selftest(gxHANDLE handle, int condition, gxVARIANT *result)
{
	struct PR_PARM_PRAPI_SELFTEST self_test;
	int ret;
	assert(result);
	self_test.condition = condition;
	ret = gx_call(handle, PR_CALL_PRAPI_SELFTEST, &self_test);
	*result = self_test.result;
	return ret;
}

/** Reads magnetic stripe (Unicode version).
 *
 * The application must call the gx_globalfree() function for the tracks to
 * free the allocated memory.
 *
 * @param handle		Handle of the prapi module.
 * @param tracks		Buffer for a pointer to the list of tracks.
 * @param ntracks		Buffer for the number of tracks.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_readmagstripe(gxHANDLE handle, wchar_t ***tracks, int *ntracks)
{
	struct PR_PARM_PRAPI_READMAGSTRIPE gms;
	int ret;
	assert(tracks && ntracks);
	ret = gx_call(handle, PR_CALL_PRAPI_READMAGSTRIPE, &gms);
	if(ret) {
		*tracks = gms.tracks;
		*ntracks = gms.ntracks;
	}
	return ret;
}

/** Reads magnetic stripe (ASCII version).
 *
 * The application must call the gx_globalfree() function for the tracks to
 * free the allocated memory.
 *
 * @param handle		Handle of the prapi module.
 * @param tracks		Buffer for a pointer to the list of tracks.
 * @param ntracks		Buffer for the number of tracks.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_readmagstripea(gxHANDLE handle, char ***tracks, int *ntracks)
{
	struct PR_PARM_PRAPI_READMAGSTRIPEA gms;
	int ret;
	assert(tracks && ntracks);
	ret = gx_call(handle, PR_CALL_PRAPI_READMAGSTRIPEA, &gms);
	if(ret) {
		*tracks = gms.tracks;
		*ntracks = gms.ntracks;
	}
	return ret;
}

#ifdef __cplusplus
/** Reads magnetic stripe (ASCII version).
 *
 * The application must call the gx_globalfree() function for the tracks to
 * free the allocated memory.
 *
 * @param handle		Handle of the prapi module.
 * @param tracks		Buffer for a pointer to the list of tracks.
 * @param ntracks		Buffer for the number of tracks.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_readmagstripe(gxHANDLE handle, char ***tracks, int *ntracks) {
	return pr_readmagstripea(handle, tracks, ntracks);
}
#endif


/** @} */

/** The event function is a callback function which is called during capture.
 * There are different kind of events. The event types and the events are defined
 * in the \ref PR_EVENT enumeration. The invoked event types can be set through the
 * event_types property.
 *
 * @param handle		Handle of the prapi module.
 * @param eventhandler	Reference to the callback function.
 * @param param			User parameter.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_seteventfunction(gxHANDLE handle, PR_EVFUNC *eventhandler, void *param) {
	struct PR_PARM_PRAPI_SETEVENTFUNCTION sef;
	sef.func = eventhandler;
	sef.param = param;
	return gx_call(handle, PR_CALL_PRAPI_SETEVENTFUNCTION, &sef);
}

#if (defined(WIN32) || defined(GX_MANUAL)) && !defined(GX_SWIG)

/** Starts window messaging process (WIN32 function).
 *
 * After starting window messaging process the freerun mode events will be raised
 * and all the PR events will be appeared as standard window messages too.
 * No threaded poll is needed to test for example the state of the button.
 * The message will arrive to the window handle set in case of status change.
 * To stop the messaging process call the pr_endwindowmessaging() function.
 *
 * @param handle	Handle of the prapi module.
 * @param hwnd		Window handle to send the messages to. This parameter can be
 *					0 to disable window messaging.
 * @param base_msg	Message id base. Set this parameter if you want to use other
 *					than the default message id space. Make sure of not using
 *					the same space in other parts of your program.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_beginwindowmessaging(gxHANDLE handle, HWND hwnd, UINT base_msg GX_DEFARG(WM_USER)) {
	struct PR_PARM_PRAPI_BEGIN_WINDOW_MESSAGING bwm;
	bwm.hwnd = hwnd;
	bwm.base_msg = base_msg;
	return gx_call(handle,PR_CALL_PRAPI_BEGIN_WINDOW_MESSAGING,&bwm);
}

/** Ends window messaging process (WIN32 function).
 *
 * After calling this function no further window messages nor
 * freerun events will arrive.
 *
 * @param handle	Handle of the prapi module.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_endwindowmessaging(gxHANDLE handle) {
	return gx_call(handle,PR_CALL_PRAPI_END_WINDOW_MESSAGING,0);
}

#endif/* WIN32 GX_SWIG */

#if (defined(LINUX) || defined(GX_MANUAL)) && !defined(GX_SWIG)

/** Starts automated background process (Linux function).
 *
 * After starting the background process the freerun mode events will be raised.
 * No threaded poll is needed to test for example the state of the button.
 * To stop the messaging process call the pr_stopbgprocesses() function.
 *
 * @param handle	Handle of the prapi module.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_startbgprocesses(gxHANDLE handle) {
	struct PR_PARM_PRAPI_BEGIN_WINDOW_MESSAGING bwm;
	return gx_call(handle,PR_CALL_PRAPI_BEGIN_WINDOW_MESSAGING,&bwm);
}

/** Ends the automated background process (Linux function).
 *
 * After calling this function no further freerun events will arrive.
 *
 * @param handle	Handle of the prapi module.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_stopbgprocesses(gxHANDLE handle) {
	return gx_call(handle,PR_CALL_PRAPI_END_WINDOW_MESSAGING,0);
}

#endif/* LINUX GX_SWIG */

/** \addtogroup pr_group_capture
 * @{
 */

/** Sets the number of document pages to capture and the needed
 * lights for each page. More than one page is usable when visa is needed
 * for a passport or when both sides of an Id card is needed to be read.
 *
 * @param handle	Handle of the prapi module.
 * @param pages		Number of document pages to read.
 * @param lights	Array of light masks where each integer represents a page.
 *					Each lower bit of them represents a light mask bit. The upper 8 bits represent the
 *					id of the object window. The light mask bits can be tested by the pr_getlightmask()
 *					function. The object window ids are defined in the \ref PR_WINDOW_ID enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_setpagelight(gxHANDLE handle,int pages,unsigned int *lights) {
	struct PR_PARM_PRAPI_SETPAGELIGHT spl;
	spl.pages = pages;
	spl.lights = lights;
	return gx_call(handle, PR_CALL_PRAPI_SETPAGELIGHT, &spl);
}

/** Captures an image sequence from the object window of the PR
 * device. To set the lights needed for capture call the pr_setpagelight()
 * function. To set a callback function to inform the state of the capturing call
 * the pr_seteventfunction() function. The captured images are stored in an
 * inside array. The image handling functions are part of the api.
 * (draw, save, recognize...)
 *
 * @param handle	Handle of the prapi module.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_capture(gxHANDLE handle) {
	return gx_call(handle, PR_CALL_PRAPI_CAPTURE, 0);
}

/** Starts the image capturing process in asynchronous mode. See pr_capture()
 * for details. Only one capture can be started at a time. The
 * pr_capture_getstatus() or the pr_capture_wait() functions must be called
 * in order the system to call the Event function. (see pr_seteventfunction() )
 *
 * @param handle	Handle of the prapi module.
 * @param reqid		Id for the getstatus and the wait functions.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_capture_start(gxHANDLE handle,int *reqid) {
	struct PR_PARM_PRAPI_CAPTURE_START cap;
	int ret;
	assert(reqid);
	ret = gx_call(handle, PR_CALL_PRAPI_CAPTURE_START, &cap);
	if(reqid) *reqid = cap.reqid;
	return ret;
}

/** Returns the state of an image capture process started with the pr_capture_start()
 * function. If an internal event occurred this function calls the Event function.
 *
 * @param handle	Handle of the prapi module.
 * @param reqid		Id for the capture. The pr_capture_start() returned this value.
 * @param status	Buffer for the result. The value of the result is in percent,
 *					it can be negative when the capture is in preprocess state.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_capture_getstatus(gxHANDLE handle,int reqid,int *status) {
	struct PR_PARM_PRAPI_GETSTATUS stat;
	int ret;
	assert(status);
	stat.reqid = reqid;
	ret = gx_call(handle, PR_CALL_PRAPI_CAPTURE_GETSTATUS, &stat);
	if(status) *status = stat.status;
	return ret;
}

/** Ends the capture process started with the pr_capture_start() function. If
 * there are internal events waiting for report this function calls the Event
 * function.
 *
 * @param handle	Handle of the prapi module.
 * @param reqid		Id of the capture returned by the pr_capture_start().
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_capture_wait(gxHANDLE handle,int reqid) {
	struct PR_PARM_PRAPI_CAPTURE_WAIT cap;
	cap.reqid = reqid;
	return gx_call(handle, PR_CALL_PRAPI_CAPTURE_WAIT, &cap);
}

/** Captures a preview image. The preview image is a small resolution real-time
 * captured image. The lights for preview capture can be set through the
 * preview_light property. For preview light control the freerun_mode property
 * must contain the \ref PR_FRMODE_PREVIEWLIGHT value.
 *
 * @param handle	Handle of the prapi module.
 * @param windowid	Id of the used window. The possible values are defined in
 *					\ref PR_WINDOW_ID enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_capture_preview(gxHANDLE handle,int windowid GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_CAPTURE_PREVIEW cap;
	cap.windowid = windowid;
	return gx_call(handle, PR_CALL_PRAPI_CAPTURE_PREVIEW, &cap);
}

/** Returns a captured image.
 *
 * The Passport Reader system has several functions for working with the captured images.
 * In special cases user functions can be used that are not supported by the system.
 * This function references the image and returns a pointer to the image. The user
 * function can reach the image data through the pointer. After the process the
 * gx_unrefvariant() function must be called in order to decrease the reference counter.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
 *					the page and light parameters have no meanings.
 * @param img		Buffer for the image reference.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getimage(gxHANDLE handle,int page,int light,int type,gxVARIANT *img) {
	struct PR_PARM_PRAPI_GETIMAGE_V gi;
	int ret;
	assert(img);
	gi.page = page;
	gi.light = light;
	gi.type = type;
	ret = gx_call(handle, PR_CALL_PRAPI_GETIMAGE_V, &gi);
	*img = gi.img;
	return ret;
}

/** Remove white backligthing from uv image.
 * @param handle		Handle of the prapi module.
 * @param page			The actual page of the image.
 * @param imagetype		The type of the image. The possible values are defined in
 * 						the \ref PR_IMAGE_TYPE enumeration.
 * @param img			Buffer for the image reference.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int pr_getenhanceduv(gxHANDLE handle, int page, int imagetype, gxVARIANT *img)
{
	struct PR_PARM_PRAPI_GETENHANCEDUV euv;
	int ret;
	assert(img);
	euv.page = page;
	euv.imgtype = imagetype;
	ret = gx_call(handle, PR_CALL_PRAPI_GETENHANCEDUV, &euv);
	*img = euv.result;
	return ret;
}

/** Saves an image to a file (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
 *					the page and light parameters have no meanings.
 * @param filename	The name of the file where to save the image.
 * @param filetype	File type. The currently supported file types are defined in gximage.h.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_saveimage(gxHANDLE handle,int page,int light,int type,const wchar_t *filename,int filetype) {
	struct PR_PARM_PRAPI_SAVEIMAGE si;
	si.page = page;
	si.light = light;
	si.type = type;
	si.filename = filename;
	si.filetype = filetype;
	return gx_call(handle, PR_CALL_PRAPI_SAVEIMAGE, &si);
}

/** Saves an image to a file (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
 *					the page and light parameters have no meanings.
 * @param filename	The name of the file where to save the image.
 * @param filetype	File type. The currently supported file types are defined
 *					in gximage.h.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_saveimagea(gxHANDLE handle,int page,int light,int type,const char *filename,int filetype) {
	struct PR_PARM_PRAPI_SAVEIMAGEA si;
	si.page = page;
	si.light = light;
	si.type = type;
	si.filename = filename;
	si.filetype = filetype;
	return gx_call(handle, PR_CALL_PRAPI_SAVEIMAGEA, &si);
}

#ifdef __cplusplus
/** Saves an image to a file (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
 *					the page and light parameters have no meanings.
 * @param filename	The name of the file where to save the image.
 * @param filetype	File type. The currently supported file types are defined
 *					in gximage.h.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_saveimage(gxHANDLE handle,int page,int light,int type,const char *filename,int filetype) {
	return pr_saveimagea(handle,page,light,type,filename,filetype);
}
#endif

#if (defined(WIN32) || defined(GX_MANUAL)) && !defined(GX_DOTNET)
/** Displays an image (WIN32 function).
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
 *					the page and light parameters have no meaning.
 * @param hdc		Handle to the device context.
 * @param x			Left side of the draw area.
 * @param y			Upper side of the draw area.
 * @param xsize		Horizontal size of the draw area.
 * @param ysize		Vertical size of the draw area.
 * @param frame		Frame of the area on the image to display.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_drawimage(gxHANDLE handle,int page,int light,int type,HDC hdc,int x,int y,int xsize,int ysize,gxRCT *frame) {
	struct PR_PARM_PRAPI_DRAWIMAGE di;
	di.page = page;
	di.light = light;
	di.type = type;
	di.hdc = hdc;
	di.x = x;
	di.y = y;
	di.xsize = xsize;
	di.ysize = ysize;
	di.frame = frame;
	return gx_call(handle, PR_CALL_PRAPI_DRAWIMAGE, &di);
}
#endif/* WIN32 GX_DOTNET */

/** @} */

/** Saves the fingers to an nist file (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	The name of the file where to save the data.
 * @param fields	List of fields to add to the record.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_fingertonist(gxHANDLE handle,const wchar_t *filename,gxVARIANT fields) {
	struct PR_PARM_PRAPI_FINGERSTONIST fn;
	fn.filename = filename;
	fn.fields = fields;
	return gx_call(handle, PR_CALL_PRAPI_FINGERSTONIST, &fn);
}

/** Saves the fingers to an nist file (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	The name of the file where to save the data.
 * @param fields	List of fields to add to the record.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_fingertonista(gxHANDLE handle,const char *filename,gxVARIANT fields) {
	struct PR_PARM_PRAPI_FINGERSTONISTA fn;
	fn.filename = filename;
	fn.fields = fields;
	return gx_call(handle, PR_CALL_PRAPI_FINGERSTONISTA, &fn);
}

#ifdef __cplusplus
/** Saves the fingers to an nist file (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	The name of the file where to save the data.
 * @param fields	List of fields to add to the record.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_fingertonist(gxHANDLE handle,const char *filename,gxVARIANT fields) {
	return pr_fingertonista(handle,filename,fields);
}
#endif

/** Saves the fingers to a memory area as a nist file.
 *
 * @param handle	Handle of the prapi module.
 * @param buffer	Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen	Size of memory area.
 * @param fields	List of fields to add to the record.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_fingertonistmem(gxHANDLE handle,void **buffer, int *buflen,gxVARIANT fields) {
	struct PR_PARM_PRAPI_FINGERSTONISTMEM fn;
	fn.buffer = buffer;
	fn.buflen = buflen;
	fn.fields = fields;
	return gx_call(handle, PR_CALL_PRAPI_FINGERSTONISTMEM, &fn);
}

/** Clears all the image and document buffers and deletes the internal image and
 * document structures.
 *
 * It is called automatically when each previously
 * set number of pages are captured and a new capture process is started, or when the
 * number of pages are modified and the actual page number is greater than the new
 * number of pages.
 *
 * @param handle	Handle of the prapi module.
 * @param lastpage	Set it to true for reset only the last captured page.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resetdocument(gxHANDLE handle, int lastpage GX_DEFARG(0)) {
	struct 	PR_PARM_PRAPI_RESETDOCUMENT rd;
	rd.lastpage = lastpage;
	return gx_call(handle, PR_CALL_PRAPI_RESETDOCUMENT, &rd);
}

/** Loads a document from the mass storage device in the specific file format (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	Name of the file to load the document from.
 * @param pdoc		Pointer to the document structure pointer that will contain the pointer
 *					to the loaded document on success.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loaddocument(gxHANDLE handle, const wchar_t *filename, gxVARIANT *pdoc) {
	struct PR_PARM_PRAPI_LOADDOCUMENT_V ld;
	int st;
	assert(filename);
	ld.filename = filename;
	st = gx_call(handle,PR_CALL_PRAPI_LOADDOCUMENT_V,&ld);
	if(pdoc) *pdoc = ld.doc;
	return st;
}

/** Loads a document from the mass storage device in the specific file format (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	Name of the file to load the document from.
 * @param pdoc		Pointer to the document structure pointer that will contain the pointer
 *					to the loaded document on success.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loaddocumenta(gxHANDLE handle, const char *filename, gxVARIANT *pdoc) {
	struct PR_PARM_PRAPI_LOADDOCUMENTA_V ld;
	int st;
	assert(filename);
	ld.filename = filename;
	st = gx_call(handle,PR_CALL_PRAPI_LOADDOCUMENTA_V,&ld);
	if(pdoc) *pdoc = ld.doc;
	return st;
}

#ifdef __cplusplus
/** Loads a document from the mass storage device in the specific file format (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param filename	Name of the file to load the document from.
 * @param pdoc		Pointer to the document structure pointer that will contain the pointer
 *					to the loaded document on success.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loaddocument(gxHANDLE handle, const char *filename, gxVARIANT *pdoc) {
	return pr_loaddocumenta(handle, filename, pdoc);
}
#endif

/** Loads a document from the memory in the specific file format.
 *
 * @param handle	Handle of the prapi module.
 * @param buffer	Pointer to the data.
 * @param buflen	Length of data in bytes.
 * @param pdoc		Pointer to the document structure pointer that will contain the pointer
 *					to the loaded document on success.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loaddocumentfrommem(gxHANDLE handle, const gxu8 *buffer, int buflen, gxVARIANT *pdoc) {
	struct PR_PARM_PRAPI_LOADDOCUMENTFROMMEM ld;
	int st;
	ld.buffer = buffer;
	ld.buflen = buflen;
	st = gx_call(handle, PR_CALL_PRAPI_LOADDOCUMENTFROMMEM, &ld);
	if(pdoc) *pdoc = ld.doc;
	return st;
}

/** \addtogroup pr_group_document
 * @{
 */

/** Reads the OCR from an unknown document.
 *
 * The returned
 * document structure will contain just the recognized rows without additional
 * details, even when the type of the document is known.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
 * @param doc		Buffer for the result document structure.
 * @param ocrparams	Ocr parameters.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getocr(gxHANDLE handle, int page, int light, int type, gxVARIANT *doc,
					 gxVARIANT ocrparams GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_GETOCR_V gd;
	int ret;
	assert(doc);
	gd.page = page;
	gd.light = light;
	gd.type = type;
	gd.params = ocrparams;
	ret = gx_call(handle, PR_CALL_PRAPI_GETOCR_V, &gd);
	*doc = gd.doc;
	return ret;
}

/** Reads the MRZ lines from the document.
 *
 * It is for compatibility reasons with the old system.
 * The pr_recognize() function should be called instead, except when the speed
 * is important.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getmrz(gxHANDLE handle,int page,int light,int type,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_GETMRZ_V gd;
	int ret;
	assert(doc);
	gd.page = page;
	gd.light = light;
	gd.type = type;
	ret = gx_call(handle, PR_CALL_PRAPI_GETMRZ_V, &gd);
	*doc = gd.doc;
	return ret;
}

/** Reads the barcodes from an unknown document.
 *
 * The returned document structure will contain just the barcode data without
 * additional information, even when the type of the document is known.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
 * @param bctype	The needed barcode type. The possible values are defined in
 *					\ref PR_BCTYPE enumeration. If this parameter is NULL any
 *					type of barcode can be returned.
 * @param index		The ordinal number of the barcode. If more barcodes found.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getbarcode(gxHANDLE handle,int page,int light,int type,int bctype,int index,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_GETBARCODE_V gbc;
	int ret;
	assert(doc);
	gbc.page=page;
	gbc.light=light;
	gbc.type=type;
	gbc.bctype=bctype;
	gbc.index=index;
	ret = gx_call(handle, PR_CALL_PRAPI_GETBARCODE_V, &gbc);
	*doc = gbc.doc;
	return ret;
}

/** Returns the quad of the document.
 *
 * It is retained for compatibility reasons with the old system.
 * This quad was used to produce the document view.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getdocumentrect(gxHANDLE handle,int page,int light,int type,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_GETDOCUMENTRECT_V gd;
	int ret;
	assert(doc);
	gd.page = page;
	gd.light = light;
	gd.type = type;
	ret = gx_call(handle, PR_CALL_PRAPI_GETDOCUMENTRECT_V, &gd);
	*doc = gd.doc;
	return ret;
}

/** Reads all of the known data from a known document type.
 *
 * The function finds the quad of the document, recognizes it's type and reads
 * MRZ, VIZ and BC fields from it.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_recognize(gxHANDLE handle,int page,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RECOGNIZE_V gd;
	int ret;
	assert(doc);
	gd.page = page;
	ret = gx_call(handle, PR_CALL_PRAPI_RECOGNIZE_V, &gd);
	*doc = gd.doc;
	return ret;
}

/** Reads the data specified in task array from the document.
 *
 * @param handle	Handle of the prapi module.
 * @param page		List of images to read from.
 * @param tasklen	Size of the task array.
 * @param task		Int array specifies the reading task.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_analyze(gxHANDLE handle, gxVARIANT page, int tasklen, int *task, gxVARIANT *doc) {
	struct PR_PARM_PRAPI_ANALYZE an;
	int ret;
	assert(doc);
	an.page = page;
	an.takslen = tasklen;
	an.task = task;
	ret = gx_call(handle, PR_CALL_PRAPI_ANALYZE, &an);
	if(ret) {
		*doc = an.doc;
	}
	return ret;
}

/** Separates and processes the data fields in a given binary data array.
 *
 * @param handle	Handle of the prapi module.
 * @param buffer	Input buffer.
 * @param buflen	Number of bytes in the buffer.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_analyzed(gxHANDLE handle, gxu8 *buffer, int buflen, gxVARIANT *doc) {
	struct PR_PARM_PRAPI_ANALYZED an;
	int ret;
	assert(doc);
	an.buffer = buffer;
	an.buflen = buflen;
	ret = gx_call(handle, PR_CALL_PRAPI_ANALYZED, &an);
	if(ret) {
		*doc = an.doc;
	}
	return ret;
}

#ifdef __cplusplus
/** Separates and processes the data fields in a given binary data array.
 *
 * @param handle	Handle of the prapi module.
 * @param buffer	Input buffer.
 * @param buflen	Number of bytes in the buffer.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_analyze(gxHANDLE handle, gxu8 *buffer, int buflen, gxVARIANT *doc) {
	return pr_analyzed(handle, buffer, buflen, doc);
}
#endif

/** Separates the data fields in the given MRZ text (Unicode version).
 *
 * It can be used to separate user defined MRZ in appropriate document fields.
 *
 * @param handle	Handle of the prapi module.
 * @param lines		Array of row strings.
 * @param nlines	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemrztext(gxHANDLE handle,const wchar_t **lines,int nlines,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RESOLVEMRZTEXT_V rt;
	int ret;
	assert(doc);
	rt.lines = lines;
	rt.nlines = nlines;
	ret = gx_call(handle, PR_CALL_PRAPI_RESOLVEMRZTEXT_V, &rt);
	*doc = rt.doc;
	return ret;
}

/** Separates the data fields in the given MRZ text (ASCII version).
 *
 * It can be used to separate user defined MRZ in appropriate document fields.
 *
 * @param handle	Handle of the prapi module.
 * @param lines		Array of row strings.
 * @param nlines	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemrztexta(gxHANDLE handle,const char **lines,int nlines,gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RESOLVEMRZTEXTA_V rt;
	int ret;
	assert(doc);
	rt.lines = lines;
	rt.nlines = nlines;
	ret = gx_call(handle, PR_CALL_PRAPI_RESOLVEMRZTEXTA_V, &rt);
	*doc = rt.doc;
	return ret;
}

#ifdef __cplusplus
/** Separates the data fields in the given MRZ text (ASCII version).
 *
 * It can be used to separate user defined MRZ in appropriate document fields.
 *
 * @param handle	Handle of the prapi module.
 * @param lines		Array of row strings.
 * @param nlines	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemrztext(gxHANDLE handle,const char **lines,int nlines,gxVARIANT *doc) {
	return pr_resolvemrztexta(handle,lines,nlines,doc);
}
#endif

/** Document structure analyser function, it gives back the main document properties.
 *
 * @param handle	Handle of the prapi module.
 * @param doc		A document structure to analyse.
 * @param code		Buffer for the type of the document. The possible types are
 *					defined in the \ref PR_DOCUMENT enumeration.
 * @param status	Buffer for the worst field error code in the document. The
 * 					error codes are defined in the \ref PR_CHKERR enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getdocumentstatus(gxHANDLE handle,gxVARIANT doc,int *code,int *status) {
	struct PR_PARM_PRAPI_GETDOCUMENTSTATUS_V gds;
	int ret;
	gds.doc = doc;
	ret = gx_call(handle, PR_CALL_PRAPI_GETDOCUMENTSTATUS_V, &gds);
	if (code) *code = gds.code;
	if (status) *status = gds.status;
	return ret;
}

/** Document structure analyser function and gives back the properties
 * of a field.
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param index			The index if more than one fields exist with the same id.
 * @param field			The field structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, int index, gxVARIANT *field) {
	struct PR_PARM_PRAPI_GETFIELDFROMDOC_V gfd;
	int ret;
	assert(field);
	gfd.doc = doc;
	gfd.field_code = field_code;
	gfd.index = index;
	ret = gx_call(handle, PR_CALL_PRAPI_GETFIELDFROMDOC_V, &gfd);
	if(field) *field = gfd.field;
	return ret;
}

#ifndef GX_DOTNET
/** Document structure analyser function and gives back the properties
 * of a field (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			This buffer must contain the size of the string buffer, and
 * 						returns the size of the string.
 * @param status		Buffer for the error code of the field. The error codes are
 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdocw(gxHANDLE handle, gxVARIANT doc, int field_code, wchar_t *text, int *stext,
							 int *status, gxPG4 *frame) {
	int ret = true;
	int s, t = 0;
	gxVARIANT field;
	if(!stext) stext = &t;

	assert((!text && !*stext) || (text && *stext>0));

	if(text && *stext>0) text[0] = 0;
	if(status) *status = -1;
	if(frame) memset(frame, 0, sizeof(gxPG4));
	if(!pr_getfieldfromdoc(handle, doc, field_code, 0, &field)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*stext = 0;
			return true;
		}
		return false;
	}

	if(text && !gx_convertvariantchild(field, (int)PRV_FIELDVALUE, 0, GX_VARIANT_UNICODE, stext,0, text, *stext)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*stext = 0;
		}
		else ret = false;
	}
	s = sizeof(int);
	if(status && !gx_convertvariantchild(field, (int)PRV_CHECKSUM, 0, GX_VARIANT_INT, &s, 0, status, s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	s = sizeof(int); t = 8;
	if(frame && !gx_convertvariantchild(field, (int)PRV_WINDOWFRAME, 0, GX_VARIANT_INTARRAY, &s, &t, frame, 8*s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	if(!ret) gx_pusherror();
	gx_disposevariant(&field);
	if(!ret) gx_poperror();
	return ret;
}

#ifdef __cplusplus

/** Document structure analyser function and gives back the properties
 * of a field (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			This buffer must contain the size of the string buffer, and
 * 						returns the size of the string.
 * @param status		Buffer for the error code of the field. The error codes are
 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, wchar_t *text, int *stext,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdocw(handle, doc, field_code, text, stext, status, frame);
}

/** Document structure analyser function and gives back the properties
 * of a field (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			Size of the string buffer.
 * @param status		Buffer for the error code of the field. The error codes are
 * 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, const gxVARIANT doc, int field_code, wchar_t *text, int stext,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdocw(handle, doc, field_code, text, &stext, status, frame);
}

#endif

/** Document structure analyser function and gives back the properties
 * of a field (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			This buffer must contain the size of the string buffer, and
 *						returns the size of the string.
 * @param status		Buffer for the error code of the field. The error codes are
 * 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoca(gxHANDLE handle, gxVARIANT doc, int field_code, char *text, int *stext,
							 int *status, gxPG4 *frame) {
	int ret = true;
	int s, t = 0;
	gxVARIANT field;
	if(!stext) stext = &t;

	assert((!text && !*stext) || (text && *stext>0));

	if(text && *stext>0) text[0] = 0;
	if(status) *status = -1;
	if(frame) memset(frame, 0, sizeof(gxPG4));
	if(!pr_getfieldfromdoc(handle, doc, field_code, 0, &field)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*stext = 0;
			return true;
		}
		return false;
	}

	if(text && !gx_convertvariantchild(field, (int)PRV_FIELDVALUE, 0, GX_VARIANT_ASCII, stext, 0, text, *stext)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*stext = 0;
		}
		else ret = false;
	}
	s = sizeof(int);
	if(status && !gx_convertvariantchild(field, (int)PRV_CHECKSUM, 0, GX_VARIANT_INT, &s, 0, status, s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	s = sizeof(int); t = 8;
	if(frame && !gx_convertvariantchild(field, (int)PRV_WINDOWFRAME, 0, GX_VARIANT_INTARRAY, &s, &t, frame, 8*s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	if(!ret) gx_pusherror();
	gx_disposevariant(&field);
	if(!ret) gx_poperror();
	return ret;
}

#ifdef __cplusplus

/** Document structure analyser function and gives back the properties
 * of a field (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			This buffer must contain the size of the string buffer, and
 *						returns the size of the string.
 * @param status		Buffer for the error code of the field. The error codes are
 * 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, char *text, int *stext,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdoca(handle, doc, field_code, text, stext, status, frame);
}

/** Document structure analyser function and gives back the properties
 * of a field (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 *						defined in the \ref PR_DOCFIELD enumeration.
 * @param text			Buffer for the string of the field.
 * @param stext			Size of the string buffer.
 * @param status		Buffer for the error code of the field. The error codes are
 * 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, char *text, int stext,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdoc(handle, doc, field_code, text, &stext, status, frame);
}

#endif

/** Document structure analyser function and gives back the properties
 * of a field (Binary version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param data			Buffer for the data of the field.
 * @param sdata			This buffer must contain the size of the data buffer, and
 * 						returns the size of the data.
 * @param status		Buffer for the error code of the field. The error codes are
 *						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdocb(gxHANDLE handle, gxVARIANT doc, int field_code, void *data, int *sdata,
							 int *status, gxPG4 *frame) {
	int ret = true;
	int s, t = 0;
	gxVARIANT field;
	if(!sdata) sdata = &t;

	assert((!data && !*sdata) || (data && *sdata>0));

	if(status) *status = -1;
	if(frame) memset(frame, 0, sizeof(gxPG4));
	if(!pr_getfieldfromdoc(handle, doc,field_code, 0, &field)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*sdata = 0;
			return true;
		}
		return false;
	}

	if(data && !gx_convertvariantchild(field, (int)PRV_FIELDVALUE, 0, GX_VARIANT_BINARY, sdata, 0, data, *sdata)) {
		if(gx_geterrorcode()==GX_ENOENT) {
			*sdata = 0;
		}
		else ret = false;
	}
	s = sizeof(int);
	if(status && !gx_convertvariantchild(field, (int)PRV_CHECKSUM, 0, GX_VARIANT_INT, &s, 0, status, s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	s = sizeof(int); t = 8;
	if(frame && !gx_convertvariantchild(field, (int)PRV_WINDOWFRAME, 0, GX_VARIANT_INTARRAY, &s, &t, frame, 8*s)) {
		if(gx_geterrorcode()!=GX_ENOENT) ret = false;
	}
	if(!ret) gx_pusherror();
	gx_disposevariant(&field);
	if(!ret) gx_poperror();
	return ret;
}

#ifdef __cplusplus

/** Document structure analyser function and gives back the properties
 * of a field (Binary version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param data			Buffer for the data of the field.
 * @param sdata			This buffer must contain the size of the data buffer, and
 * 						returns the size of the data.
 * @param status		Buffer for the error code of the field. The error codes are
 *						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, void *data, int *sdata,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdocb(handle, doc, field_code, data, sdata, status, frame);
}

/** This is a document structure analyser function and gives back the properties
 * of a field (Binary version).
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param data			Buffer for the data of the field.
 * @param sdata			Size of the data buffer.
 * @param status		Buffer for the error code of the field. The error codes are
 * 						defined in the \ref PR_CHKERR enumeration.
 * @param frame			Buffer for the quad of the field.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, void *data, int sdata,
							 int *status, gxPG4 *frame) {
	return pr_getfieldfromdoc(handle, doc, field_code, data, &sdata, status, frame);
}

#endif
#endif

/** Returns a variant image from the document structure.
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param index			The index if more than one fields exist with the same id.
 * @param img			Pointer to the returned image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getfieldimage(gxHANDLE handle,gxVARIANT doc,int field_code,int index,gxVARIANT *img) {
	struct PR_PARM_PRAPI_GETFIELDIMAGE_V parm;
	int ret;
	assert(img);
	parm.doc = doc;
	parm.field_code = field_code;
	parm.index = index;
	ret = gx_call(handle, PR_CALL_PRAPI_GETFIELDIMAGE_V, &parm);
	if (ret && img) *img = parm.img;
	return ret;
}

/** Returns a gxIMAGE from the document structure.
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param img			Pointer to the returned image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getgximagefromdoc(gxHANDLE handle,gxVARIANT doc,int field_code, gxIMAGE **img) {
	int ret = true;
	gxVARIANT field;
	int ind=0;
	if(field_code>_PR_DF_RFID_FACE){
		ind=(field_code&0xffff)-1;
		field_code&=~0xffff;
	}
	if(!pr_getfieldimage(handle,doc,field_code,ind,&field)) return false;
	ret = gx_imagefromvariant(gx_direct(GX_CALL_GROUP_GX_IMAGE),img,field);
	if(!ret)gx_pusherror();
	gx_disposevariant(&field);
	if(!ret)gx_poperror();
	return ret;
}

/** Returns a property field from the document structure.
 *
 * @param handle		Handle of the prapi module.
 * @param doc			A document structure to analyse.
 * @param field_code	The id of the needed field. The possible ids are
 * 						defined in the \ref PR_DOCFIELD enumeration.
 * @param prop_code		The id of the needed property.
 * @param data			Preallocated buffer for the data.
 * @param sdata			Size of the preallocated buffer. On return it will contain the size of the returned data.
 * @param data_type		On return it will contain the type of the returned data ( see prPropFieldItem::DATA_TYPES enumeration).
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getpropfromdoc(gxHANDLE handle, gxVARIANT doc, int field_code, int prop_code,
							  void *data, int *sdata, int *data_type) {

	gxVARIANT d = doc, field = 0;
	int dc = 0, s = sizeof(int);
	int ret;
	assert(sdata);
	if(!pr_getfieldfromdoc(handle,d,field_code,0,&field)) return false;

	if(prop_code==_PR_PROP_TYPE_RFID_FILES) dc=(int)_PRV_RFIDDIR;
	if(prop_code==_PR_PROP_TYPE_BARCODE_TYPE) dc=(int)_PRV_BARCODE;
	if(prop_code==_PR_PROP_TYPE_CONFIDENCE) dc=(int)_PRV_CONFIDENCE;
	ret = gx_convertvariantchild(field,dc,0,_GX_VARIANT_INT,&s,0,data,*sdata);
	if(!ret)gx_pusherror();
	gx_unrefvariant(field);
	if(data_type)*data_type=0x14;
	if(!ret)gx_poperror();
	return ret;
}


/** Compares a captured face photo with one that is stored in rfid chip.
 *
 * The application must call pr_resolverfiddata() function first.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param face_no	The ordinal number of the face image in rfid data.
 * @param doc		Buffer for the result document structure.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_compareface(gxHANDLE handle, int page, int face_no, gxVARIANT *doc) {
	int ret;
	struct PR_PARM_PRAPI_COMPARE_FACE_V param;
	assert(doc);
	param.page = page;
	param.face_no = face_no;
	ret = gx_call(handle, PR_CALL_PRAPI_COMPARE_FACE_V, &param);
	*doc = param.doc;
	return ret;
}

/** Saves a document to a mass storage device in the specific file format (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param pdoc		Pointer to the document.
 * @param filename	Name of the file.
 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_savedocument(gxHANDLE handle, gxVARIANT pdoc, const wchar_t *filename, int filetype) {
	struct PR_PARM_PRAPI_SAVEDOCUMENT_V sd;
	assert(filename);
	sd.doc = pdoc;
	sd.filename = filename;
	sd.filetype = filetype;
	return gx_call(handle,PR_CALL_PRAPI_SAVEDOCUMENT_V,&sd);
}

/** Saves a document to a mass storage device in the specific file format (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param pdoc		Pointer to the document.
 * @param filename	Name of the file.
 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_savedocumenta(gxHANDLE handle, gxVARIANT pdoc, const char *filename, int filetype) {
	struct PR_PARM_PRAPI_SAVEDOCUMENTA_V sd;
	assert(filename);
	sd.doc = pdoc;
	sd.filename = filename;
	sd.filetype = filetype;
	return gx_call(handle,PR_CALL_PRAPI_SAVEDOCUMENTA_V,&sd);
}

#ifdef __cplusplus
/** Saves a document to a mass storage device in the specific file format (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param pdoc		Pointer to the document.
 * @param filename	Name of the file.
 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_savedocument(gxHANDLE handle, gxVARIANT pdoc, const char *filename, int filetype) {
	return pr_savedocumenta(handle, pdoc, filename, filetype);
}
#endif

/** Saves a document to memory in the specific file format.
 *
 * @param handle	Handle of the prapi module.
 * @param pdoc		Pointer to the document.
 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
 * @param buffer	Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen	Size of the memory area.
 */
inline int pr_savedocumenttomem(gxHANDLE handle, gxVARIANT pdoc, gxu8 **buffer, int *buflen, int filetype) {
	struct PR_PARM_PRAPI_SAVEDOCUMENTTOMEM stm;
	stm.doc = pdoc;
	stm.filetype = filetype;
	stm.buffer = buffer;
	stm.buflen = buflen;
	return gx_call(handle, PR_CALL_PRAPI_SAVEDOCUMENTTOMEM, &stm);
}

/** Returns the root document of the PR system.
 *
 * @param handle	Handle of the prapi module.
 * @param pdoc		Buffer for the root document.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getdocumentroot(gxHANDLE handle, gxVARIANT *pdoc) {
	struct PR_PARM_PRAPI_GETDOCUMENTROOT_V gd;
	int st;
	st = gx_call(handle, PR_CALL_PRAPI_GETDOCUMENTROOT_V, &gd);
	if(pdoc) *pdoc = gd.doc;
	return st;
}

/** Decodes a latent image from a stored image.
 *
 * @param handle	Handle of the prapi module.
 * @param page		The actual page of the image.
 * @param light		The light settings. The possible values are defined in the
 * 					\ref PR_LIGHT enumeration.
 * @param type		The type of the image. The possible values are defined in
 * 					the \ref PR_IMAGE_TYPE enumeration.
 * @param decpar	Decoding parameter.
 * @param image		The latent image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_decodelatentimage(gxHANDLE handle, int page, int light, int type, const wchar_t *decpar,
								gxVARIANT *image) {
	struct PR_PARM_PRAPI_DECODELATENTIMAGE dli;
	int st;
	assert(image);
	dli.page = page;
	dli.light = light;
	dli.type = type;
	dli.decpar = decpar;
	st = gx_call(handle, PR_CALL_PRAPI_DECODELATENTIMAGE, &dli);
	if(st && image) *image = dli.image;
	return st;
}

/** Separates the data fields in the given magnetic stripe text (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param tracks	Array of row strings.
 * @param ntracks	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemagstripe(gxHANDLE handle, const wchar_t **tracks, int ntracks, gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RESOLVEMAGSTRIPE rms;
	int ret;
	assert(doc);
	rms.tracks = tracks;
	rms.ntracks = ntracks;
	ret = gx_call(handle, PR_CALL_PRAPI_RESOLVEMAGSTRIPE, &rms);
	*doc = rms.doc;
	return ret;
}

/** Separates the data fields in the given magnetic stripe text (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param tracks	Array of row strings.
 * @param ntracks	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemagstripea(gxHANDLE handle, const char **tracks, int ntracks, gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RESOLVEMAGSTRIPEA rms;
	int ret;
	assert(doc);
	rms.tracks = tracks;
	rms.ntracks = ntracks;
	ret = gx_call(handle, PR_CALL_PRAPI_RESOLVEMAGSTRIPEA, &rms);
	*doc = rms.doc;
	return ret;
}

#ifdef __cplusplus
/** Separates the data fields in the given magnetic stripe text (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param tracks	Array of row strings.
 * @param ntracks	Number of rows.
 * @param doc		Buffer for the result document structure.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolvemagstripe(gxHANDLE handle, const char **tracks, int ntracks, gxVARIANT *doc) {
	return pr_resolvemagstripea(handle, tracks, ntracks, doc);
}
#endif

/** @} */

/** \addtogroup pr_group_rfid
 * @{
 */

/** Gets the list of cards in the range of the contactless reader (Unicode version).
 *
 * The application must call the gx_globalfree() function for the cards to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param cards		List of card serial numbers.
 * @param ncards	Number of cards in list.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidcardlist(gxHANDLE handle,wchar_t ***cards,int *ncards) {
	struct PR_PARM_PRAPI_GETRFIDCARDLIST gcl;
	int ret;
	assert(cards && ncards);
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDCARDLIST, &gcl);
	*cards = gcl.cards;
	*ncards = gcl.ncards;
	return ret;
}

/** Gets the list of cards in the range of the contactless reader (ASCII version).
 *
 * The application must call the gx_globalfree() function for the cards to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param cards		List of card serial numbers.
 * @param ncards	Number of cards in list.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidcardlista(gxHANDLE handle,char ***cards,int *ncards) {
	struct PR_PARM_PRAPI_GETRFIDCARDLISTA gcl;
	int ret;
	assert(cards && ncards);
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDCARDLISTA, &gcl);
	*cards = gcl.cards;
	*ncards = gcl.ncards;
	return ret;
}

#ifdef __cplusplus
/** Gets the list of cards in the range of the contactless reader (ASCII version).
 *
 * The application must call the gx_globalfree() function for the cards to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param cards		List of card serial numbers.
 * @param ncards	Number of cards in list.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidcardlist(gxHANDLE handle,char ***cards,int *ncards) {
	return pr_getrfidcardlista(handle,cards,ncards);
}
#endif

/** Reads files from the RFID card (Unicode version).
 *
 * The application must call the gx_globalfree() function for the data to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @param data		File contents returned by the card.
 * @param sdata		Size of the returned data block.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile(gxHANDLE handle,const wchar_t *card,int fileid,void **data,int *sdata) {
	struct PR_PARM_PRAPI_GETRFIDFILE gf;
	int ret;
	assert(data && sdata);
	gf.card = card;
	gf.fileid = fileid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE, &gf);
	*data = gf.data;
	*sdata = gf.sdata;
	return ret;
}

/** Reads files from the RFID card (ASCII version).
 *
 * The application must call the gx_globalfree() function for the data to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @param data		File contents returned by the card.
 * @param sdata		Size of the returned data block.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfilea(gxHANDLE handle,const char *card,int fileid,void **data,int *sdata) {
	struct PR_PARM_PRAPI_GETRFIDFILEA gf;
	int ret;
	assert(data && sdata);
	gf.card = card;
	gf.fileid = fileid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILEA, &gf);
	*data = gf.data;
	*sdata = gf.sdata;
	return ret;
}

#ifdef __cplusplus
/** Reads files from the RFID card (ASCII version).
 *
 * The application must call the gx_globalfree() function for the data to
 * free the allocated memory.
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @param data		File contents returned by the card.
 * @param sdata		Size of the returned data block.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile(gxHANDLE handle,const char *card,int fileid,void **data,int *sdata) {
	return pr_getrfidfilea(handle,card,fileid,data,sdata);
}
#endif

/** Starts reading files from the RFID card in asynchronous mode. (Unicode version)
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
 * @param reqid		Id for the getstatus and the wait functions.
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_start(gxHANDLE handle, const wchar_t *card, int fileid, int *reqid) {
	struct PR_PARM_PRAPI_GETRFIDFILE_START param;
	int ret;
	param.card = card;
	param.fileid = fileid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE_START, &param);
	if(reqid) *reqid = param.reqid;
	return ret;
}

/** Starts reading files from the RFID card in asynchronous mode. (ASCII version)
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
 * @param reqid		Id for the getstatus and the wait functions.
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_starta(gxHANDLE handle, const char *card, int fileid, int *reqid) {
	struct PR_PARM_PRAPI_GETRFIDFILE_STARTA param;
	int ret;
	param.card = card;
	param.fileid = fileid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE_STARTA, &param);
	if(reqid) *reqid = param.reqid;
	return ret;
}


#ifdef __cplusplus
/** Starts reading files from the RFID card in asynchronous mode. (ASCII version)
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
 * @param reqid		Id for the getstatus and the wait functions.
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_start(gxHANDLE handle,const char *card,int fileid,int *reqid) {
	return pr_getrfidfile_starta(handle,card,fileid,reqid);
}
#endif

/** Returns the state of a rfid reading process started with the pr_getrfidfile_start()
 * function. If an internal event occurred this function calls the Event function.
 *
 * @param handle	Handle of the prapi module.
 * @param reqid		Id for the process. The pr_getrfidfile_start() returned this value.
 * @param status	Buffer for the result. The value of the result is in percent,
 *					it can be negative when the capture is in preprocess state.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_getstatus(gxHANDLE handle,int reqid,int *status) {
	struct PR_PARM_PRAPI_GETSTATUS stat;
	int ret;
	assert(status);
	stat.reqid = reqid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE_GETSTATUS, &stat);
	if(status) *status = stat.status;
	return ret;
}

/** Wait for the finish of the rfid reading process started with the pr_getrfidfile_start() function. If
 * there are internal events waiting for report, this function calls the Event
 * function.
 *
 * @param handle	Handle of the prapi module.
 * @param reqid		Id of the capture returned by the pr_getrfidfile_start().
 * @param data		File contents returned by the card.
 * @param sdata		Size of the returned data block.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_wait(gxHANDLE handle, int reqid, void **data, int *sdata) {
	struct PR_PARM_PRAPI_GETRFIDFILE_WAIT param;
	int ret;
	assert(data && sdata);
	param.reqid = reqid;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE_WAIT, &param);
	*data = param.data;
	*sdata = param.sdata;
	return ret;
}

/** Cancel the rfid reading process started with the pr_getrfidfile_start() function. If
 * there are internal events waiting for report, this function calls the Event
 * function.
 *
 * @param handle	Handle of the prapi module.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_getrfidfile_stop(gxHANDLE handle) {
	int ret;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDFILE_STOP, 0);
	return ret;
}

/** Resolves a composite RFID data and fills a document structure with the descompounded data.
 *
 * @param handle	Handle of the prapi module.
 * @param data		Composite RFID data read from the chip.
 * @param sdata		The size of the data.
 * @param doc		Document structure filled with the descompounded rfid data.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_resolverfiddata(gxHANDLE handle, const void *data, int sdata, gxVARIANT *doc) {
	struct PR_PARM_PRAPI_RESOLVERFIDDATA_V rd;
	int ret;
	assert(doc);
	rd.data = data;
	rd.sdata = sdata;
	ret = gx_call(handle, PR_CALL_PRAPI_RESOLVERFIDDATA_V, &rd);
	*doc = rd.doc;
	return ret;
}

/**  Get applications supported by the card. (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param apps			Array of supported applications. The possible values are defined
 *						 in the \ref PR_APP_TYPE enumeration.
 * @param napps			Number of items in the application array.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getapplications(gxHANDLE handle, const wchar_t *card, int **apps, int *napps) {
	struct PR_PARM_PRAPI_GET_APPLICATIONS param;
	int ret;
	assert(apps && napps);
	param.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_GETAPPLICATIONS, &param);
	*apps = param.apps;
	*napps = param.napps;
	return ret;
}

/**   Get applications supported by the card. (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param apps			Array of supported applications. The possible values are defined
 *						 in the \ref PR_APP_TYPE enumeration.
 * @param napps			Number of items in the application array.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getapplicationsa(gxHANDLE handle, const char *card, int **apps, int *napps) {
	struct PR_PARM_PRAPI_GET_APPLICATIONSA param;
	int ret;
	param.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_GETAPPLICATIONSA, &param);
	*apps = param.apps;
	*napps = param.napps;
	return ret;
}

#ifdef __cplusplus
/**   Get applications supported by the card. (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param apps			Array of supported applications. The possible values are defined
 *						 in the \ref PR_APP_TYPE enumeration.
 * @param napps			Number of items in the application array.
 * @return				On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_getapplications(gxHANDLE handle, const char *card, int **apps, int *napps) {
	return pr_getapplicationsa(handle, card, apps, napps);
}

#endif

/**  Select the chip application. (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param application	Type of the application.The possible values are defined in the
 *						\ref PR_APP_TYPE enumeration.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_selectapplication(gxHANDLE handle, const wchar_t *card, int application) {
	struct PR_PARM_PRAPI_SELECT_APPLICATION param;
	param.card = card;
	param.application = application;
	return gx_call(handle, PR_CALL_PRAPI_SELECT_APPLICATION, &param);
}

/**  Select the chip application. (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param application	Type of the application.The possible values are defined in the
 *						\ref PR_APP_TYPE enumeration.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_selectapplicationa(gxHANDLE handle, const char *card, int application) {
	struct PR_PARM_PRAPI_SELECT_APPLICATIONA param;
	param.card = card;
	param.application = application;
	return gx_call(handle, PR_CALL_PRAPI_SELECT_APPLICATIONA, &param);
}

#ifdef __cplusplus
/**  Select the chip application. (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param application	Type of the application.The possible values are defined in the
 *						\ref PR_APP_TYPE enumeration.
 * @return				On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_selectapplication(gxHANDLE handle, const char *card, int application) {
	return pr_selectapplicationa(handle,card,application);
}

#endif

/** Switches to secure messaging by making Basic Access Control (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param lines		MRZ lines in array of row strings.
 * @param nlines	Number of MRZ lines supplied.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makebac(gxHANDLE handle, const wchar_t *card, const wchar_t **lines, int nlines) {
	struct PR_PARM_PRAPI_MAKEBAC param;
	param.card = card;
	param.lines = lines;
	param.nlines = nlines;
	return gx_call(handle, PR_CALL_PRAPI_MAKEBAC, &param);
}

/** Switches to secure messaging by making Basic Access Control (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param lines		MRZ lines in array of row strings.
 * @param nlines	Number of MRZ lines supplied.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makebaca(gxHANDLE handle, const char *card, const char **lines, int nlines) {
	struct PR_PARM_PRAPI_MAKEBACA param;
	param.card = card;
	param.lines = lines;
	param.nlines = nlines;
	return gx_call(handle, PR_CALL_PRAPI_MAKEBACA, &param);
}

#ifdef __cplusplus
/** Switches to secure messaging by making Basic Access Control (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param lines		MRZ lines in array of row strings.
 * @param nlines	Number of MRZ lines supplied.
 * @return			On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makebac(gxHANDLE handle, const char *card, const char **lines, int nlines) {
	return pr_makebaca(handle,card,lines,nlines);
}

#endif

/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param lines			MRZ lines in array of row strings.
 * @param nlines		Number of MRZ lines supplied.
 * @param PasswordType	The type of the password. The possible values are
 *						defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return				On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makepace(gxHANDLE handle, const wchar_t *card, const wchar_t **lines, int nlines, int PasswordType) {
	struct PR_PARM_PRAPI_MAKEPACE param;
	param.card = card;
	param.lines = lines;
	param.nlines = nlines;
	param.PasswordType = PasswordType;
	return gx_call(handle, PR_CALL_PRAPI_MAKEPACE, &param);
}

/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param lines			MRZ lines in array of row strings.
 * @param nlines		Number of MRZ lines supplied.
 * @param PasswordType	The type of the password. The possible values are
 *						defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return				On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makepacea(gxHANDLE handle, const char *card, const char **lines, int nlines, int PasswordType) {
	struct PR_PARM_PRAPI_MAKEPACEA param;
	param.card = card;
	param.lines = lines;
	param.nlines = nlines;
	param.PasswordType = PasswordType;
	return gx_call(handle, PR_CALL_PRAPI_MAKEPACEA, &param);
}

#ifdef __cplusplus
/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param card			Serial number of the selected card.
 * @param lines			MRZ lines in array of row strings.
 * @param nlines		Number of MRZ lines supplied.
 * @param PasswordType	The type of the password. The possible values are
 *						defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return				On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_makepace(gxHANDLE handle, const char *card, const char **lines, int nlines, int PasswordType) {
	return pr_makepacea(handle,card,lines,nlines,PasswordType);
}
#endif


/** Makes the Passive Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makepassiveauth(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKEPASSIVEAUTH, &param);
}

/** Makes the Passive Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makepassiveautha(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKEPASSIVEAUTHA, &param);
}

#ifdef __cplusplus
/** Makes the Passive Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makepassiveauth(gxHANDLE handle, const char *card) {
	return pr_makepassiveautha(handle,card);
}
#endif

/** Makes the Active Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 *
 * \note	Comparation of the MRZ read visually from the MRTD's data page and
 *			the MRZ value in Data Group 1 is skipped.
 */
inline int pr_makeactiveauth(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKEACTIVEAUTH, &param);
}

/** Makes the Active Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 *
 * \note	Comparation of the MRZ read visually from the MRTD's data page and
 *			the MRZ value in Data Group 1 is skipped.
 */
inline int pr_makeactiveautha(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKEACTIVEAUTHA, &param);
}

#ifdef __cplusplus
/** Makes the Active Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 *
 * \note	Comparation of the MRZ read visually from the MRTD's data page and
 *			the MRZ value in Data Group 1 is skipped.
 */
inline int pr_makeactiveauth(gxHANDLE handle, const char *card) {
	return pr_makeactiveautha(handle,card);
}
#endif

/** Makes the Chip Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makechipauth(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKECHIPAUTH, &param);
}

/** Makes the Chip Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makechipautha(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKECHIPAUTHA, &param);
}

#ifdef __cplusplus
/** Makes the Chip Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_makechipauth(gxHANDLE handle, const char *card) {
	return pr_makechipautha(handle,card);
}
#endif

/** Makes the Terminal Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_maketerminalauth(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKETERMINALAUTH, &param);
}

/** Makes the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_maketerminalautha(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_MAKETERMINALAUTHA, &param);
}

#ifdef __cplusplus
/** Makes the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_maketerminalauth(gxHANDLE handle, const char *card) {
	return pr_maketerminalautha(handle,card);
}
#endif

/** Initiates the Terminal Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Data to sign.
 * @param sdata		Size of the data.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_initta(gxHANDLE handle, const wchar_t *card, void **data, int *sdata) {
	struct PR_PARM_PRAPI_TA param;
	int ret;
	assert(data && sdata);
	param.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_INITTERMINALAUTH, &param);
	if (ret != 0) {
		*data = param.data;
		*sdata = param.sdata;
	}
	return ret;
}

/** Initiates the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Data to sign.
 * @param sdata		Size of the data.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_inittaa(gxHANDLE handle, const char *card, void **data, int *sdata) {
	struct PR_PARM_PRAPI_TAA param;
	int ret;
	assert(data && sdata);
	param.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_INITTERMINALAUTHA, &param);
	if (ret != 0) {
		*data = param.data;
		*sdata = param.sdata;
	}
	return ret;
}

#ifdef __cplusplus
/** Initiates the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Data to sign.
 * @param sdata		Size of the data.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_initta(gxHANDLE handle, const char *card, void **data, int *sdata) {
	return pr_inittaa(handle, card, data, sdata);
}
#endif

/** Completes the Terminal Authentication of the RFID chip (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Signature.
 * @param sdata		Size of the signature.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_completeta(gxHANDLE handle, const wchar_t *card, const void *data, int sdata) {
	struct PR_PARM_PRAPI_TA param;
	param.card = card;
	param.data = (void*)data;
	param.sdata = sdata;
	return gx_call(handle, PR_CALL_PRAPI_COMPLETETERMINALAUTH, &param);
}

/** Completes the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Signature.
 * @param sdata		Size of the signature.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_completetaa(gxHANDLE handle, const char *card, const void *data, int sdata) {
	struct PR_PARM_PRAPI_TAA param;
	param.card = card;
	param.data = (void*)data;
	param.sdata = sdata;
	return gx_call(handle, PR_CALL_PRAPI_COMPLETETERMINALAUTHA, &param);
}

#ifdef __cplusplus
/** Completes the Terminal Authentication of the RFID chip (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param data		Signature.
 * @param sdata		Size of the signature.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() ) */
inline int pr_completeta(gxHANDLE handle, const char *card, const void *data, int sdata) {
	return pr_completetaa(handle, card, data, sdata);
}
#endif

/** Loads a certificate and a private key from file (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param certificate	Name of the selected certificate file.
 * @param privateKey	Name of the private key file connected to the certificate. This can be NULL.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfile(gxHANDLE handle, const wchar_t *certificate, const wchar_t *privateKey GX_DEFARG(NULL)) {
	struct PR_PARM_PRAPI_LOADCERTFILE param;
	param.certificate = certificate;
	param.privateKey = privateKey;
	return gx_call(handle, PR_CALL_PRAPI_LOADCERTFILE, &param);
}

/** Loads a certificate and a private key from file (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param certificate	Name of the selected certificate file.
 * @param privateKey	Name of the private key file connected to the certificate. This can be NULL.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfilea(gxHANDLE handle, const char *certificate, const char *privateKey GX_DEFARG(NULL)) {
	struct PR_PARM_PRAPI_LOADCERTFILEA param;
	param.certificate = certificate;
	param.privateKey = privateKey;
	return gx_call(handle, PR_CALL_PRAPI_LOADCERTFILEA, &param);
}

#ifdef __cplusplus
/** Loads a certificate and a private key from file (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param certificate	Name of the selected certificate file.
 * @param privateKey	Name of the private key file connected to the certificate. This can be NULL.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfile(gxHANDLE handle, const char *certificate, const char *privateKey GX_DEFARG(NULL)) {
	return pr_loadcertfilea(handle, certificate, privateKey);
}

#endif

/** Loads certificates and CRLs from store (Unicode version).
 *
 * @param handle		Handle of the prapi module.
 * @param storename		Name of the store.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfromstore(gxHANDLE handle, const wchar_t *storename) {
	struct PR_PARM_PRAPI_LOADCERTFROMSTORE param;
	param.storename = storename;
	return gx_call(handle, PR_CALL_PRAPI_LOADCERTFROMSTORE, &param);
}

/** Loads certificates and CRLs from store (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param storename		Name of the store.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfromstorea(gxHANDLE handle, const char *storename) {
	struct PR_PARM_PRAPI_LOADCERTFROMSTOREA param;
	param.storename = storename;
	return gx_call(handle, PR_CALL_PRAPI_LOADCERTFROMSTOREA, &param);
}

#ifdef __cplusplus
/** Loads certificates and CRLs from store (ASCII version).
 *
 * @param handle		Handle of the prapi module.
 * @param storename		Name of the store.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfromstore(gxHANDLE handle, const char *storename) {
	return pr_loadcertfromstorea(handle, storename);
}

#endif


/** Loads a certificate and a private key from memory.
 *
 * @param handle				Handle of the prapi module.
 * @param certificate_data		Pointer to the certificate memory area.
 * @param certificate_length	Length of certificate_data [byte].
 * @param privateKey_data		Pointer to the private key memory area. This can be NULL.
 * @param privateKey_length		Length of privateKey_data [byte]. This can be 0.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_loadcertfrommem(gxHANDLE handle, void *certificate_data, unsigned int certificate_length, void *privateKey_data GX_DEFARG(NULL), unsigned int privateKey_length GX_DEFARG(0)) {
	struct PR_PARM_PRAPI_LOADCERTFROMMEM param;
	param.certificate_data = certificate_data;
	param.certificate_length = certificate_length;
	param.privateKey_data = privateKey_data;
	param.privateKey_length = privateKey_length;

	return gx_call(handle, PR_CALL_PRAPI_LOADCERTFROMMEM, &param);
}

/** Clears the internal certificate list.
 *
 * @param handle	Handle of the prapi module.
 * @param sel		List selector. Set 0 to clear all the certificate lists, set to 1 to clear PA certificate
 *					list, set to 2 to clear TA certificate list.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_clearcertlist(gxHANDLE handle, int sel) {
	struct PR_PARM_PRAPI_CLEARCERTLIST ccl;
	ccl.sel = sel;
	return gx_call(handle, PR_CALL_PRAPI_CLEARCERTLIST, &ccl);
}

/** Connects to an RFID card (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_connectrfidcard(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_CONNECTRFIDCARD, &param);
}

/** Connects to an RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_connectrfidcarda(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_CONNECTRFIDCARDA, &param);
}

#ifdef __cplusplus
/** Connects to an RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_connectrfidcard(gxHANDLE handle, const char *card) {
	return pr_connectrfidcarda(handle, card);
}
#endif

/** Disconnects from RFID card (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_disconnectrfidcard(gxHANDLE handle, const wchar_t *card) {
	struct PR_PARM_PRAPI_RFIDCARD param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_DISCONNECTRFIDCARD, &param);
}

/** Disconnects from an RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_disconnectrfidcarda(gxHANDLE handle, const char *card) {
	struct PR_PARM_PRAPI_RFIDCARDA param;
	param.card = card;
	return gx_call(handle, PR_CALL_PRAPI_DISCONNECTRFIDCARDA, &param);
}

#ifdef __cplusplus
/** Disconnects from an RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_disconnectrfidcard(gxHANDLE handle, const char *card) {
	return pr_disconnectrfidcarda(handle, card);
}
#endif

/** Checks the hash of the file read from the RFID card (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_checkrfidfilehash(gxHANDLE handle, const wchar_t *card, int fileid) {
	struct PR_PARM_PRAPI_CHECKRFIDFILEHASH param;
	param.card = card;
	param.fileid = fileid;
	return gx_call(handle, PR_CALL_PRAPI_CHECKRFIDFILEHASH, &param);
}

/** Checks the hash of the file read from the RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_checkrfidfilehasha(gxHANDLE handle, const char *card, int fileid) {
	struct PR_PARM_PRAPI_CHECKRFIDFILEHASHA param;
	param.card = card;
	param.fileid = fileid;
	return gx_call(handle, PR_CALL_PRAPI_CHECKRFIDFILEHASHA, &param);
}

#ifdef __cplusplus
/** Checks the hash of the file read from the RFID card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param fileid	Identifier of the requested file. The possible values are
 *					defined in the \ref PR_RFID_FILES enumeration.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately. ( see gx_geterror() ) */
inline int pr_checkrfidfilehash(gxHANDLE handle, const char *card, int fileid) {
	return pr_checkrfidfilehasha(handle, card, fileid);
}
#endif

/** Gets information about the rfid card (Unicode version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param cardinfo	Variant structure for card information.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getrfidcardinfo(gxHANDLE handle, const wchar_t *card, gxVARIANT *cardinfo) {
	struct PR_PARM_PRAPI_GETRFIDCARDINFO grci;
	int ret;
	assert(cardinfo);
	grci.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDCARDINFO, &grci);
	if(ret && cardinfo) *cardinfo = grci.cardinfo;
	return ret;
}

/** Gets information about the rfid card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param cardinfo	Variant structure for card information.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getrfidcardinfoa(gxHANDLE handle, const char *card, gxVARIANT *cardinfo) {
	struct PR_PARM_PRAPI_GETRFIDCARDINFOA grci;
	int ret;
	assert(cardinfo);
	grci.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_GETRFIDCARDINFOA, &grci);
	if(ret && cardinfo) *cardinfo = grci.cardinfo;
	return ret;
}

#ifdef __cplusplus
/** Gets information about the rfid card (ASCII version).
 *
 * @param handle	Handle of the prapi module.
 * @param card		Serial number of the selected card.
 * @param cardinfo	Variant structure for card information.
 * @return  On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getrfidcardinfo(gxHANDLE handle, const char *card, gxVARIANT *cardinfo) {
	return pr_getrfidcardinfoa(handle, card, cardinfo);
}
#endif

/** Gets information about certificate (Unicode version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
 * @param CertificateId		Id of the certificate.
 * @return					On error false is returned and the error code/string in the GX system
 *							is set appropriately. ( see gx_geterror() )
 */
inline int pr_getcertificateid(gxHANDLE handle, const wchar_t *card,int Authentication, gxVARIANT *CertificateId) {
	struct PR_PARM_PRAPI_GETCERTIFICATEID cid;
	int ret;
	assert(CertificateId);
	cid.card = card;
	cid.Authentication = Authentication;
	ret = gx_call(handle, PR_CALL_PRAPI_GETCERTIFICATEID, &cid);
	if(ret && CertificateId) *CertificateId = cid.CertId;
	return ret;
}

/** Gets information about certificate (ASCII version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
 * @param CertificateId		Id of the certificate.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getcertificateida(gxHANDLE handle, const char *card, int Authentication, gxVARIANT *CertificateId) {
	struct PR_PARM_PRAPI_GETCERTIFICATEIDA cid;
	int ret;
	cid.card = card;
	cid.Authentication = Authentication;
	assert(CertificateId);
	ret = gx_call(handle, PR_CALL_PRAPI_GETCERTIFICATEIDA, &cid);
	if(ret && CertificateId) *CertificateId = cid.CertId;
	return ret;
}

#ifdef __cplusplus
/** Gets information about certificate (ASCII version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
 * @param CertificateId		Id of the certificate.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getcertificateid(gxHANDLE handle, const char *card, int Authentication, gxVARIANT *CertificateId) {
	return pr_getcertificateida(handle, card, Authentication, CertificateId);
}
#endif


/** Gets information about the next suggested authentication process (Unicode version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Next authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param ForceNext			Skips the actual authentication.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getnextauthentication(gxHANDLE handle, const wchar_t *card, int *Authentication, int ForceNext GX_DEFARG(false)) {
	struct PR_PARM_PRAPI_GETNEXTAUTHENTICATION authproc;
	int ret;
	authproc.card = card;
	authproc.ForceNext = ForceNext;
	ret = gx_call(handle, PR_CALL_PRAPI_GETNEXTAUTHENTICATION, &authproc);
	*Authentication = authproc.ProcessName;
	return ret;
}

/** Gets information about the next suggested authentication process (Unicode version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Next authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param ForceNext			Skips the actual authentication.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getnextauthenticationa(gxHANDLE handle, const char *card, int *Authentication, int ForceNext GX_DEFARG(false)) {
	struct PR_PARM_PRAPI_GETNEXTAUTHENTICATIONA authproc;
	int ret;
	authproc.card = card;
	authproc.ForceNext = ForceNext;
	ret = gx_call(handle, PR_CALL_PRAPI_GETNEXTAUTHENTICATIONA, &authproc);
	*Authentication = authproc.ProcessName;
	return ret;
}

#ifdef __cplusplus
/** Gets information about the next suggested authentication process (ASCII version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Next authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param ForceNext			Skips the actual authentication.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getnextauthentication(gxHANDLE handle, const char *card, int *Authentication, int ForceNext = false) {
	return pr_getnextauthenticationa(handle, card,Authentication, ForceNext);
}
#endif

/** Making authentication process (ASCII version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
 * @param Lines				Number of rows in AuthData.
 * @param PasswordType		The type of the PACE password. The possible values are
 *							defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_doauthentication(gxHANDLE handle, const wchar_t *card, int Authentication, const wchar_t **AuthData GX_DEFARG(0), int Lines GX_DEFARG(0), int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) {
	struct PR_PARM_PRAPI_DOAUTHENTICATION params;
	int ret;
	params.card = card;
	params.ProcessName = Authentication;
	params.AuthData = AuthData;
	params.Lines = Lines;
	params.PasswordType = PasswordType;
	ret = gx_call(handle, PR_CALL_PRAPI_DOAUTHENTICATION, &params);
	return ret;
}

/** Making authentication process (Unicode version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
 * @param Lines				Number of rows in AuthData.
 * @param PasswordType		The type of the PACE password. The possible values are
 *							defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_doauthenticationa(gxHANDLE handle, const char *card, int Authentication, const char **AuthData GX_DEFARG(0), int Lines GX_DEFARG(0), int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) {
	struct PR_PARM_PRAPI_DOAUTHENTICATIONA params;
	int ret;
	params.card = card;
	params.ProcessName = Authentication;
	params.AuthData = AuthData;
	params.Lines = Lines;
	params.PasswordType = PasswordType;
	ret = gx_call(handle, PR_CALL_PRAPI_DOAUTHENTICATIONA, &params);
	return ret;
}

#ifdef __cplusplus
/** Making authentication process (ASCII version).
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param Authentication	Authentication process id. The possible values are defined in the
 *							\ref PR_AUTH_PROC enumeration.
 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
 * @param Lines				Number of rows in AuthData.
 * @param PasswordType		The type of the PACE password. The possible values are
 *							defined in the \ref PR_PACE_PASSWORD enumeration.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_doauthentication(gxHANDLE handle, const char *card, int Authentication, const char **AuthData GX_DEFARG(0), int Lines GX_DEFARG(0), int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) {
	return pr_doauthenticationa(handle, card,Authentication, AuthData, Lines, PasswordType);
}
#endif

/** Converts rfid file ids between general id and data group number form.
 * 
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param file_id			Buffer for file id.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_convertfid(gxHANDLE handle, const wchar_t *card, int *file_id) {
	int ret;
	PR_PARM_PRAPI_CONVERTFID cid;
	assert(file_id);
	cid.card = card;
	cid.fid = *file_id;
	ret = gx_call(handle, PR_CALL_PRAPI_CONVERTFID, &cid);
	if(ret) *file_id = cid.fid;
	return ret;
}

/** Returns the rfid authentication results in document form.
 *
 * @param handle			Handle of the prapi module.
 * @param card				Serial number of the selected card.
 * @param pdoc				Buffer for the result document structure.
 * @return					On error false is returned and the error code/string in the GX system
 * is set appropriately. ( see gx_geterror() )
 */
inline int pr_getrfidauthresult(gxHANDLE handle, const wchar_t *card, gxVARIANT *pdoc) {
	int ret;
	PR_PARM_PRAPI_GETAUTHRESULT gad;
	assert(pdoc);
	gad.card = card;
	ret = gx_call(handle, PR_CALL_PRAPI_GETAUTHRESULT, &gad);
	if(ret) *pdoc = gad.doc;
	return ret;
}

/** @} */

#endif	/*)*/

#ifdef GX_DOTNET
	#pragma managed
	#undef gxPG4
#endif

/******************************************************************************/
#if !defined(NO_GX_CLASSES)	/*(*/

/** \addtogroup pr_group_document
 * @{
 */

/**
	This class represents a recognized document structure in the PR system.
*/
GX_CLASS prDoc : public gxHandle
#ifdef GX_DOTNET
,public System::IDisposable
#endif
{
	/* Forbidden constructors. */
	inline prDoc() {}
	inline prDoc(prDoc &src) {}
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	inline prDoc& operator= (prDoc /* src */) { return *this; }
#endif

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
protected:
	/* Pointer to a document structure of the PR system. */
	gxVARIANT doc;

#endif /* GX_SWIGIF GX_MANUAL )*/

public:

	/** Destructor. */
	inline ~prDoc() throw(gxError) {
		Free();
	}

	/** Disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		Free();
		gxHandle::Dispose();
	}

#if !defined(GX_SWIGIF)	&& !defined(GX_MANUAL) /*(*/
#ifndef GX_DOTNET
	/** Returns a pointer to the document structure of the class.
	 * @return	If the class contains valid document data the function returns its reference.
	 *			In the other case 0 is returned.
	 */
	inline operator gxVARIANT () GX_CONST {
		return doc;
	}
#else
private public:
#endif

	/** Class initialization with an existing document structure.
	 *
	 * @param src	Pointer to an existing document structure.
	 */
	inline prDoc(gxVARIANT src, gxHANDLE h) throw(gxError) {
		doc = 0;
		if(!gx_refhandle(h)) { gxthrow; return; }
#ifdef GX_DOTNET
		_set_handle(h.handle);
#else
		handle = h.handle;
#endif
		if(src && !gx_refvariant(src)) {
			gx_pusherror();
			gx_unrefhandle(&h);
#ifdef GX_DOTNET
			_handle = 0;
#else
			handle = 0;
#endif
			gx_poperror();
			gxthrow;
			return;
		}
		doc = src;
	}
public:

#endif/* GX_SWIGIF && GX_MANUAL )*/

	/** Copies an existing prDoc object.
	 *
	 * @param src	An existing prDoc object.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Copy(prDoc &src) throw(gxError) {
		gxVARIANT d = doc;
		if(d) {
			if(!gx_unrefvariant(d)) {
				gxthrow;
				return false;
			}
		}
#ifndef GX_DOTNET
		bool st = gx_duplicatevariant(&d,src)!=0;
#else
		bool st = gx_duplicatevariant(&d,src.doc)!=0;
#endif
		if(!st){
			gxthrow;
			return false;
		}
		doc = d;
		return true;
	}

	/** Clears the prDoc object, deletes the document.
	 *
	 * @return On success: non-zero ( see gx_geterror() )
	 */
	inline bool Free(void) throw(gxError) {
		gxVARIANT d = doc;
		if(d) {
			if(!gx_unrefvariant(d)) {
				gxthrow;
				return false;
			}
			doc = 0;
		}
		return true;
	}

	/** Embedds the prDoc object into a variant.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline gxVariant * ToVariant() throw(gxError) {
		gxVARIANT d = doc;
		if(!d) {
			gxSystem::ClearError();
			return 0;
		}
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(d);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(d);
			gx_refvariant(d);
		#endif
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns a document task result from a root document.
	 *
	 * @param ix	Ordinal number of the requested task.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetDocPart(int ix) throw(gxError) {
		gxVARIANT  task;
		prDoc *cdoc = 0;
		char path[50];
		gx_snprintf(path, 50, "C,D=%i/L,X=%i", PRV_TASKLIST, ix);
		if(!gx_getvariantbypath(doc, path, &task)) {
			gxthrow;
			return cdoc;
		}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
		if(task) {
			cdoc = new prDoc(task, *this);
			gx_unrefvariant(task);
			if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		}
#else
		GX_GETHANDLE(h);
		cdoc = new prDoc(task, h);
		if(task) gx_unrefvariant(task);
		if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
#endif
		if(!task) gxSystem::ClearError();
		return cdoc;
	}

	/** Returns the code of the document.
	 *
	 * The possible document types are defined in the \ref PR_DOCUMENT enumeration.
	 *
	 * @return	If a document is copied to the class the function returns its code.
	 *			If there is no document copied it returns -1.
	 */
	inline int Code(void) GX_CONST throw(gxError) {
		int code = -1;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		if(!pr_getdocumentstatus(h,d,&code,0)) gxthrow;
		return code;
	}

	/** Returns the status of the document.
	 *
	 * The status of the document is the highest error code between the field errors.
	 * The error codes are defined in the \ref PR_CHKERR enumeration.
	 *
	 * @return	If a document is copied to the class the function returns its status.
	 *			If there is no document copied it returns -1.
	 */
	inline int Status(void) GX_CONST throw(gxError) {
		int status = -1;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		if(!pr_getdocumentstatus(h,d,0,&status)) gxthrow;
		return status;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)	/*(*/
	/** Returns the data of a field in string format (ASCII version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param text			Buffer for the string of the field.
	 * @param stext			Size of the string buffer.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, char *text, int stext, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(text && stext>0);
		return Field(field_code, text, &stext, index);
	}

	/** Returns the data of a field in string format (ASCII version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param text			Buffer for the string of the field.
	 * @param stext			This buffer must contain the size of the string buffer,
	 *						and returns the size of the string.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, char *text, int *stext, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(text && stext && *stext>0);
		gxVARIANT field=0;
 		if(field_code>_PR_DF_RFID_FACE) {
			if(field_code&0xffff) index += (field_code&0xffff)-1;
			field_code &= ~0xffff;
		}
		if(!pr_getfieldfromdoc(*this, doc, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				if(text && *stext>0)text[0]=0;
				*stext = 1;
				return true;
			}
			gxthrow;
			return false;
		}
		if(!gx_convertvariantchild(field,(int)PRV_FIELDVALUE,0,GXVT GX_VARIANT_ASCII,
								  stext,0,text,*stext)) {
			if(gx_geterror()==GX_ENOENT){
				if(text && *stext>0)text[0]=0;
				*stext = 1;
				gx_unrefvariant(field);
				return true;
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return false;
		}
		gx_unrefvariant(field);
		return true;
	}

	/** Returns the data of a field in string format (Unicode version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param text			Buffer for the string of the field.
	 * @param stext			Size of the string buffer.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, wchar_t *text, int stext, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(text && stext>0);
		return Field(field_code, text, &stext, index);
	}

	/** Returns the data of a field in string format (Unicode version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param text			Buffer for the string of the field.
	 * @param stext			This buffer must contain the size of the string buffer,
	 *						and returns the size of the string.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, wchar_t *text, int *stext, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(text && stext && *stext>0);
		gxVARIANT field=0;
 		if(field_code>_PR_DF_RFID_FACE) {
			if(field_code&0xffff) index += (field_code&0xffff)-1;
			field_code &= ~0xffff;
		}
		if(!pr_getfieldfromdoc(*this, doc, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				if(text && *stext>0)text[0]=0;
				*stext = 1;
				return true;
			}
			gxthrow;
			return false;
		}
		if(!gx_convertvariantchild(field,(int)PRV_FIELDVALUE,0,GXVT GX_VARIANT_UNICODE,
								  stext,0,text,*stext*sizeof(wchar_t))) {
			if(gx_geterror()==GX_ENOENT){
				if(text && *stext>0)text[0]=0;
				*stext = 1;
				gx_unrefvariant(field);
				return true;
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return false;
		}
		gx_unrefvariant(field);
		return true;
	}

	/** Returns the data of a field (Binary version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param data			Buffer for the data of the field.
	 * @param sdata			Size of the data buffer.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, void *data, int sdata, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(data && sdata>0);
		return Field(field_code, data, &sdata, index);
	}

	/** Returns the data of a field (Binary version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param data			Buffer for the data of the field.
	 * @param sdata			This buffer must contain the size of the data buffer,
	 *						and returns the size of the data.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	On success: non-zero ( see gx_geterror() )
	 */
	inline bool Field(int field_code, void *data, int *sdata, int index GX_DEFARG(0)) GX_CONST throw(gxError) {
		gxassert(data && sdata && *sdata>0);
		gxVARIANT field=0;
 		if(field_code>_PR_DF_RFID_FACE) {
			if(field_code&0xffff) index += (field_code&0xffff)-1;
			field_code &= ~0xffff;
		}
		if(!pr_getfieldfromdoc(*this, doc, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				*sdata = 0;
				return true;
			}
			gxthrow;
			return false;
		}
		if(!gx_convertvariantchild(field,(int)PRV_FIELDVALUE,0,GXVT GX_VARIANT_BINARY,
								  sdata,0,data,*sdata)) {
			if(gx_geterror()==GX_ENOENT){
				*sdata = 0;
				gx_unrefvariant(field);
				return true;
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return false;
		}
		gx_unrefvariant(field);
		return true;
	}

#endif /* GX_SWIG GX_DOTNET )*/

	/** Returns the image of a field.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @return	The image needed.
	 */
	inline gxImage * FieldImage(int field_code) GX_CONST throw(gxError) {
		int index = 0;
 		if(field_code>_PR_DF_RFID_FACE) {
			if(field_code&0xffff) index = (field_code&0xffff)-1;
			field_code &= ~0xffff;
		}
		return FieldImage(field_code, index);
	}

	/** Returns the image of a field.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	The image needed.
	 */
	inline gxImage * FieldImage(int field_code, int index) GX_CONST throw(gxError) {
		gxVARIANT vimg = 0;
		gxIMAGE *img = 0;
		gxImage *cimg = 0;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;

		if(!pr_getfieldimage(h, d, field_code, index ,&vimg)) {
			if(gx_geterror()!=GX_ENOENT){
				gxthrow;
				return cimg;
			}
		}
		bool ret = true;
		if(vimg) {
			ret = gx_imagefromvariant(&img,vimg)!=0;
			if(!ret)gx_pusherror();
			gx_unrefvariant(vimg);
			if(!ret){
				gx_poperror();
				gxthrow;
				return cimg;
			}
		}

		if(img){
#ifndef GX_DOTNET
			cimg = new gxImage(*img);
			gx_unrefimage(img);
			if(!cimg){gxSystem::SetError(GX_ENOMEM);gxthrow;}
#else
			cimg = new gxImage();
			if(!cimg){gxSystem::SetError(GX_ENOMEM);gxthrow;}
			else cimg->_set_image(img);
#endif
		}
		else gxSystem::ClearError();
		return cimg;
	}

#ifdef GX_UNICODE
	/** Returns the data of a field in string format (Unicode version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @return	The data of the field.
	 */
	inline gxOutStr Field(int field_code) GX_CONST throw(gxError) {
		return Field(field_code, 0);
	}

	/** Returns the data of a field in string format (Unicode version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	The data of the field.
	 */
	inline gxOutStr Field(int field_code, int index) GX_CONST throw(gxError) {
		wchar_t fieldbuf[GX_MAXLEN_STRING+1];
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		gxVARIANT field=0;
		if(!pr_getfieldfromdoc(h, d, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				fieldbuf[0]=0;
				return GX_PUTSTRING(fieldbuf);
			}
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		int s=GX_MAXLEN_STRING;
		if(!gx_convertvariantchild(field,(int)PRV_FIELDVALUE,0,GXVT GX_VARIANT_UNICODE,
								  &s,0,fieldbuf,s*sizeof(wchar_t))) {
			if(gx_geterror()==GX_ENOENT){
				fieldbuf[0]=0;
				gx_unrefvariant(field);
				return GX_PUTSTRING(fieldbuf);
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		gx_unrefvariant(field);
		fieldbuf[GX_MAXLEN_STRING] = 0;
		return GX_PUTSTRING(fieldbuf);
	}
#endif/* GX_UNICODE */

#ifdef GX_ASCII
	/** Returns the data of a field in string format (ASCII version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @return	The data of the field.
	 */
	inline gxOutAStr FieldA(int field_code) GX_CONST throw(gxError) {
		return FieldA(field_code, 0);
	}

	/** Returns the data of a field in string format (ASCII version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	The data of the field.
	 */
	inline gxOutAStr FieldA(int field_code, int index) GX_CONST throw(gxError) {
		char fieldbuf[GX_MAXLEN_STRING+1];
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		gxVARIANT field=0;
		if(!pr_getfieldfromdoc(h, d, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				fieldbuf[0]=0;
				return GX_PUTASTRING(fieldbuf);
			}
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		int s=GX_MAXLEN_STRING;
		if(!gx_convertvariantchild(field,(int)PRV_FIELDVALUE,0,GXVT GX_VARIANT_ASCII,
								  &s,0,fieldbuf,s)) {
			if(gx_geterror()==GX_ENOENT){
				fieldbuf[0]=0;
				gx_unrefvariant(field);
				return GX_PUTASTRING(fieldbuf);
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		gx_unrefvariant(field);
		fieldbuf[GX_MAXLEN_STRING] = 0;
		return GX_PUTASTRING(fieldbuf);
	}
#endif/* GX_ASCII */

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Returns the data of a field (Binary version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	Data of the field.
	 */
	inline gxOutData FieldB(int field_code, int index) GX_CONST throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		gxVARIANT field, data = 0;
		if(!pr_getfieldfromdoc(h, d, field_code, index, &field)) {
			if(gx_geterror()!=GX_ENOENT) {
				gxthrow;
			}
			return GX_PUTDATA_NONE;
		}
		int id = PRV_FIELDVALUE;
		if(!gx_getvariantchild(field, GXVF GX_VARIANT_BY_ID, &id, 0, &data)) {
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			if(gx_geterror()!=GX_ENOENT) {
				gxthrow;
			}
			return GX_PUTDATA_NONE;
		}
		gx_disposevariant(&field);

		int size = 0;
		gxu8 *fieldbuf = 0;
		int ret = 0;
		if(gx_getvariant(data, 0, 0, &size, 0, 0)) {
			fieldbuf = new gxu8[size];
			if(!fieldbuf) gx_seterror(GX_ENOENT);
			else if(gx_convertvariant(data, 0, GXVT GX_VARIANT_BINARY, &size, 0, fieldbuf, size))
				ret = 1;
		}

		if(!ret) gx_pusherror();
		gx_unrefvariant(data);
		if(!ret) {
			delete [] fieldbuf;
			gx_poperror();
			gxthrow;
			return GX_PUTDATA_NONE;
		}

		gxOutData od = GX_PUTDATA(fieldbuf, size);
		delete [] fieldbuf;
		return od;
	}
#endif/* GX_SWIG GX_DOTNET */

	/** Returns a field (Variant version).
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	The field in variant data type.
	 */
	inline gxVariant * FieldV(int field_code, int index) GX_CONST throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		gxVARIANT field=0;
		if(!pr_getfieldfromdoc(h, d, field_code, index, &field)) {
			gxthrow;
			return 0;
		}
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(field);
			gx_unrefvariant(field);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(field);
		#endif
		if(!vr){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns the error status of a field.
	 *
	 * The error codes are defined in the \ref PR_CHKERR enumeration.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @return	If a document is copied to the class the function returns the fields'
	 *			status. If there is no document copied or field is not exist it returns -1.
	 */
	inline int FieldStatus(int field_code) GX_CONST throw(gxError) {
		return FieldStatus(field_code, 0);
	}

	/** Returns the error status of a field.
	 *
	 * The error codes are defined in the \ref PR_CHKERR enumeration.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
 	 *						defined in the \ref PR_DOCFIELD enumeration.
	 * @param index			The index for the list of possible results if more than
	 *						one field was found with the same id.
	 * @return	If a document is copied to the class the function returns the fields'
	 *			status. If there is no document copied or field is not exist it returns -1.
	 */
	inline int FieldStatus(int field_code, int index) GX_CONST throw(gxError) {
		int status = -1;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		gxVARIANT field=0;
		if(!pr_getfieldfromdoc(h, d, field_code, index, &field)) {
			if(gx_geterror()==GX_ENOENT){
				return 1;
			}
			gxthrow;
			return -1;
		}
		int s=4;
		if(!gx_convertvariantchild(field,(int)PRV_CHECKSUM,0,GXVT GX_VARIANT_INT,
								  &s,0,&status,s)) {
			if(gx_geterror()==GX_ENOENT){
				gx_unrefvariant(field);
				return 1;
			}
			gx_pusherror();
			gx_unrefvariant(field);
			gx_poperror();
			gxthrow;
			return -1;
		}
		gx_unrefvariant(field);
		return status;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns a property of a field.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
	 * 						defined in the \ref PR_DOCFIELD enumeration.
	 * @param prop_code		The id of the needed property.
	 * @param data			Preallocated buffer for the data.
	 * @param sdata			Size of the preallocated buffer. On return it will contain the size of the returned data.
	 * @param data_type		On return it will contain the type of the returned data ( see prPropFieldItem::DATA_TYPES enumeration).
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool Prop(int field_code, int prop_code, void* data, int *sdata, int *data_type) GX_CONST throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		bool st = pr_getpropfromdoc(h,d,field_code, prop_code, data, sdata, data_type) != 0;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Returns a property of a field.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
	 * 						defined in the \ref PR_DOCFIELD enumeration.
	 * @param prop_code		The id of the needed property.
	 * @return		The data of the field. */
	inline gxOutData PropB(int field_code, int prop_code) GX_CONST throw(gxError) {
		const int sdata = 200*1024;
		char data[sdata];
		int data_type;
		int size = sdata;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		if(!pr_getpropfromdoc(h,d,field_code, prop_code, data, &size, &data_type)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		return GX_PUTDATA(data, size);
	}
#endif/* GX_SWIG GX_DOTNET */

	/** Returns a four bytes integer property of a field.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
	 * 						defined in the \ref PR_DOCFIELD enumeration.
	 * @param prop_code		The id of the needed property.
	 * @return		The value of the int property */
	inline int PropI32(int field_code, int prop_code) GX_CONST throw(gxError) {
		int data;
		int sdata = 4;
		int data_type;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		bool st = pr_getpropfromdoc(h,d,field_code, prop_code, &data, &sdata, &data_type) != 0;
		gxcondthrow(!st);
		return st?data:0;
	}

	/** Returns a property field from the document structure.
	 *
	 * @param field_code	The id of the needed field. The possible ids are
	 * 						defined in the \ref PR_DOCFIELD enumeration.
	 * @param prop_code		The id of the needed property.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline int PropType(int field_code, int prop_code) GX_CONST throw(gxError) {
		int data_type;
		int sdata;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		bool st = pr_getpropfromdoc(h,d,field_code, prop_code, 0, &sdata, &data_type) != 0;
		gxcondthrow(!st);
		return st ? 0 : data_type;
	}

	/** Checks if the document structure and the handle is valid.
	 *
	 * @return In case of valid document the return value is true.
	 */
	inline bool IsValid(void) GX_CONST {
		if(!gxHandle::IsValid())return false;
		return doc != 0 ? true : false;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Saves a document to a mass storage device in the specific file format (Unicode version).
	 *
	 * @param filename	Name of the file.
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Save(const wchar_t *filename, int filetype = PR_DFF_ZIPPED) GX_CONST throw(gxError) {
		bool st = pr_savedocument(*this,doc,filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Saves a document to a mass storage device in the specific file format (ASCII version).
	 *
	 * @param filename	Name of the file.
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Save(const char *filename, int filetype = PR_DFF_ZIPPED) GX_CONST throw(gxError) {
		bool st = pr_savedocument(*this,doc,filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Saves a document to memory in the specific file format.
	 *
	 * @param buffer	Pointer to the memory area pointer that is large enough or NULL.
	 * @param buflen	Size of the memory area.
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SaveToMem(gxu8 **buffer, int *buflen, int filetype = PR_DFF_XML) GX_CONST throw(gxError) {
		bool st = pr_savedocumenttomem(*this, doc, buffer, buflen, filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Saves a document to a mass storage device in the specific file format (Unicode version).
	 *
	 * @param filename	Name of the file.
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Save(gxInStr filename, int filetype GX_DEFARG(PR_DFF_ZIPPED)) GX_CONST throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		GX_GETSTRING(_filename, filename);
		bool st = pr_savedocument(h,d,_filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Saves a document to a mass storage device in the specific file format (ASCII version).
	 *
	 * @param filename	Name of the file.
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Save(gxInAStr filename, int filetype GX_DEFARG(PR_DFF_ZIPPED)) GX_CONST throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		GX_GETASTRING(_filename, filename);
		bool st = pr_savedocument(h,d,_filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Saves a document to memory in the specific file format.
	 *
	 * @param filetype	Format of the file ( see \ref PR_DOCFILEFORMATS ).
	 * @return  File data. An exception is thrown or null is returned in case of error.
	 */
	inline gxOutData SaveToMem(int filetype GX_DEFARG(PR_DFF_XML)) GX_CONST throw(gxError) {
		gxu8 *buffer;
		int buflen;
		GX_GETHANDLE(h);
		gxVARIANT d = doc;
		if(!pr_savedocumenttomem(h, d, &buffer, &buflen, filetype)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(buffer, buflen);
		if(buffer) gx_globalfree(buffer);
		return ret;
	}
#endif

};

/** @} */

/******************************************************************************/

/**
  This class represents a captured image in the PR system.
*/
GX_CLASS prImage
#ifdef GX_DOTNET
: public System::IDisposable
#endif
{
	/* Forbidden constructors. */
	inline prImage() {}
	inline prImage(prImage & /* src */) {}
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	inline prImage& operator= (prImage /* src */) { return *this; }
#endif

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
private:
	/* Pointer to the image structure in the PR system. */
	gxVARIANT image;

#endif	/* GX_SWIGIF GX_MANUAL )*/

public:

	/** Destructor. */
	inline ~prImage() throw(gxError) {
		Detach();
	}

	/** Disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		Detach();
	}

#if !defined(GX_SWIGIF)	/*(*/
#ifndef GX_DOTNET
	/** Returns a pointer to the image structure of the class.
	 * @return	If the class contains valid image data the function returns its reference.
	 *			In the other case 0 is returned.
	 */
	inline operator gxVARIANT () GX_CONST {
		return image;
	}
#else
private public:
#endif

	/** Class initialization with an existing image structure.
	 *
	 * @param src	Pointer to an existing image structure.
	 */
	inline prImage(gxVARIANT src) throw(gxError) {
		image = 0;
		if(src && !gx_refvariant(src)) {
			gxthrow;
			return;
		}
		image = src;
	}
public:

#endif/* GX_SWIGIF )*/

#if !defined(GX_SWIG) && !defined(GX_DOTNET)	/*(*/

	/** Attaches to an existing image structure.
	 *
	 * @param src	An existing image structure.
	 * @return On success: non-zero ( see gx_geterror() )
	 */
	inline bool Attach(gxVARIANT src) throw(gxError) {
		if(!gx_refvariant(src)){
			gxthrow;
			return false;
		}
		if(image)
			if(!gx_unrefvariant(image)){
				gx_pusherror();
				gx_unrefvariant(src);
				gx_poperror();
				gxthrow;
				return false;
			}
		image = src;
		return true;
	}
#endif	/*)*/

	/** Attaches to an existing image structure.
	 *
	 * @param src	An existing image structure.
	 * @return On success: non-zero ( see gx_geterror() )
	 */
	inline bool Attach(prImage &src) throw(gxError) {
		if(!gx_refvariant(src.image)) {
			gxthrow;
			return false;
		}
		if(image) {
			if(!gx_unrefvariant(image)) {
				gx_pusherror();
				gx_unrefvariant(src.image);
				gx_poperror();
				gxthrow;
				return false;
			}
		}
#ifndef GX_DOTNET
		image = src;
#else
		image = src.image;
#endif
		return true;
	}

	/**
	  Detaches the previously attached image.
	  @return Upon success: non-zero ( see gx_geterror() )
	*/
	inline bool Detach(void) throw(gxError) {
		if(image){
			if(!gx_unrefvariant(image)) {
				gxthrow;
				return false;
			}
			image = 0;
		}
		return true;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)	/*(*/
	/**
	  Returns the gxIMAGE structure element of the image.
	  @return If an image is attached to the class the function returns its gxIMAGE
	  element. If there is no image attached it returns 0.
	*/
	inline gxIMAGE* GxImage(void) const throw(gxError) {
		gxIMAGE *gim;
		gxassert(image);
		if(!image) return 0;
		if(!gx_imagefromvariant(&gim,image)){
			gxthrow;
			return 0;
		}
		return gim;
	}

	/**
	  Returns the gxTRAFO structure element of the image.
	  @return If an image is attached to the class the function returns one of its
	  gxTRAFO element. If there is no image attached it returns 0.
	*/
	inline const gxTRAFO* Trafo(void) const throw(gxError) {
		gxVARIANT vt;
		gxTRAFO *trf;
		gxassert(image);
		if(!image) return 0;
		if(!gx_getvariantchild(image,GX_VARIANT_BY_ID,(int)PRV_TRAFO,0,&vt)){
			gxthrow;
			return 0;
		}
		if(!gx_trafofromvariant(&trf,vt)){
			gx_pusherror();
			gx_unrefvariant(vt);
			gx_poperror();
			gxthrow;
			return 0;
		}
		gx_unrefvariant(vt);
		return trf;
	}
#else	/*)(*/
	/**
	  Returns the gxImage element of the prImage.
	  @return If an image is attached to the class the function returns its gxImage
	  element. If there is no image attached it returns 0.
	*/
	inline gxImage * GxImage(void) GX_CONST throw(gxError) {
		gxIMAGE *gim;
		gxassert(image);
		if(!image)return 0;
		if(!gx_imagefromvariant(&gim,image)){
			gxthrow;
			return 0;
		}
		gxImage *im = new gxImage();
#ifndef GX_DOTNET
		gxtry {
			if(gim)im->Attach(gim);
		} gxcatch(...) {
			gx_pusherror();
			if(gim)gx_unrefimage(gim);
			delete im;
			gx_poperror();
			__gxthrow;
			return 0;
		}
		if(gim)gx_unrefimage(gim);
#else
		if(gim) im->_set_image(gim);
#endif
		return im;
	}

	/**
	  Returns the gxTrafo element of the prImage.
	  @return If an image is attached to the class the function returns one of its
	  gxTrafo element. If there is no image attached it returns 0.
	*/
	inline gxTrafo* Trafo(void) GX_CONST throw(gxError) {
		gxVARIANT vt;
		gxTRAFO *trf;
		gxassert(image);
		if(!image)return 0;
		if(!gx_getvariantchild(image,GXVF GX_VARIANT_BY_ID,(int)PRV_TRAFO,0,&vt)){
			gxthrow;
			return 0;
		}
		if(!gx_trafofromvariant(&trf,vt)){
			gx_pusherror();
			gx_unrefvariant(vt);
			gx_poperror();
			gxthrow;
			return 0;
		}
		gx_unrefvariant(vt);
		gxTrafo *tr=new gxTrafo();
#ifndef GX_DOTNET
		gxtry {
			if(trf)tr->Attach(trf);
		} gxcatch(...) {
			gx_pusherror();
			if(trf)gx_unreftrafo(trf);
			delete tr;
			gx_poperror();
			__gxthrow;
			return 0;
		}
		if(trf)gx_unreftrafo(trf);
#else
		tr->_set_trafo(trf);
#endif
		return tr;
	}
#endif /* GX_SWIG GX_DOTNET )*/


	/**
	  Returns the capture time of the image.
	  @return If an image is attached to the class the function returns its capture
	  time. If there is no image attached it returns 0.
	*/
	inline int CaptureTime(void) GX_CONST throw(gxError) {
		int s=sizeof(gxi64);
		gxi64 captime;
		gxassert(image);
		if(!image) return 0;
		if(!gx_convertvariantchild(image,(int)PRV_CAPTIME,0,GX_VARIANT_INT,&s,0,&captime,s)) {
			gxthrow;
			return 0;
		}
		return int(captime/1000);
	}

	/**
	  Returns the page number of the image.
	  @return If an image is attached to the class the function returns its page
	  number. If there is no image attached it returns 0.
	*/
	inline int Page(void) GX_CONST throw(gxError) {
		int s=sizeof(int), page;
		gxassert(image);
		if(!image) return 0;
		if(!gx_convertvariantchild(image,(int)PRV_PAGE,0,GX_VARIANT_INT,&s,0,&page,s)) {
			gxthrow;
			return 0;
		}
		return page;
	}

	/**
	  Sets the page number of the image.
	  @param page	The new page number.
	  @return The new page number.
	*/
	inline int Page(int page) throw(gxError) {
		gxVARIANT vpage;
		gxassert(image);
		if(!image) return page;
		if(!gx_getvariantchild(image,GX_VARIANT_BY_ID,(int)PRV_PAGE,0,&vpage)) return page;
		if(!gx_updatevariantdata(vpage,(int)PRV_PAGE,GX_VARIANT_INT,sizeof(int),1,&page)) {
			gx_pusherror();
			gx_unrefvariant(vpage);
			gx_poperror();
			gxthrow;
			return page;
		}
		gx_unrefvariant(vpage);
		return page;
	}

	/**
	  Returns the light id of the image.
	  @return If an image is attached to the class the function returns its light
	  settings. The available light values are defined in \ref PR_LIGHT enumeration.
	  If there is no image attached the function returns 0.
	*/
	inline int Light(void) GX_CONST throw(gxError) {
		int s=sizeof(int), light;
		gxassert(image);
		if(!image) return 0;
		if(!gx_convertvariantchild(image,(int)PRV_LIGHT,0,GX_VARIANT_INT,&s,0,&light,s)) {
			gxthrow;
			return 0;
		}
		return light;
	}

	/**
	  Returns the camera id of the image.
	  @return If an image is attached to the class the function returns its camera
	  id number. If there is no image attached it returns 0.
	*/
	inline int Camera(void) GX_CONST throw(gxError) {
		int s=sizeof(int), camera;
		gxassert(image);
		if(!image) return 0;
		if(!gx_convertvariantchild(image,(int)PRV_CAMERA,0,GX_VARIANT_INT,&s,0,&camera,s)) {
			gxthrow;
			return 0;
		}
		return camera;
	}

	/**
	  Checks if the image structure and handle is valid.
	  @return In case of valid image the return value is true.
	*/
	inline bool IsValid(void) GX_CONST {
		if(!this) return false;
		return image ? true : false;
	}

};

/******************************************************************************/

#ifndef GX_MANUAL
#if !defined(GX_SWIG) && !defined(GX_DOTNET)	// C++
	#define ifDoc if(doc)
#else
	#define ifDoc
#endif
#endif/* GX_MANUAL */

/**
	This class contains functions that contol the Passport Reader system.
*/

GX_CLASS PassportReader : public gxHandle
#ifdef GX_DOTNET
,public System::IDisposable
#endif
{

public:

	/** Class initialization. */
	inline PassportReader() throw(gxError) {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"prapi", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"prapi", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Class initialization.
	 * @param proppath	Root node in the property tree.
	 */
	inline PassportReader(const wchar_t *proppath) throw(gxError) {
		if(!gx_openmodule(this, L"prapi", proppath)) gxthrow;
	}

	/** Class initialization.
	 * @param proppath	Root node in the property tree.
	 */
	inline PassportReader(const char *proppath) throw(gxError) {
		if(!gx_openmodule(this, "prapi", proppath)) gxthrow;
	}
#endif

#ifdef GX_UNICODE
	/** Class initialization.
	 * @param proppath	Root node in the property tree.
	 */
	inline PassportReader(gxInStr proppath) throw(gxError) {
		GX_GETSTRING(_proppath, proppath);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"prapi", _proppath)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"prapi", _proppath)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif

#ifdef GX_ASCII
	/** Class initialization.
	 * @param proppath	Root node in the property tree.
	 */
	inline PassportReader(gxInAStr proppath) throw(gxError) {
		GX_GETASTRING(_proppath, proppath);
		if(!gx_openmodule(this, "prapi", _proppath)) gxthrow;
	}
#endif

	/** Disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		gxHandle::Dispose();
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns a list of the available Passport Reader devices (Unicode version).
	 *
	 * The application must call the gx_globalfree() function for the devices list
	 * to free the allocated memory.
	 *
	 * @param devices		List of the device names.
	 * @param ndevices		Number of devices.
	 * @return	On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetDeviceList(wchar_t ***devices,int *ndevices) throw(gxError) {
		bool st = pr_getdevicelist(*this,devices,ndevices)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Returns a list of the available Passport Reader devices (ASCII version).
	 *
	 * The application must call the gx_globalfree() function for the devices list
	 * to free allocated memory.
	 *
	 * @param devices		List of the device names.
	 * @param ndevices		Number of devices.
	 * @return	On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetDeviceList(char ***devices,int *ndevices) throw(gxError) {
		bool st = pr_getdevicelist(*this,devices,ndevices)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Returns a list of the available Passport Reader devices (Unicode version).
	 *
	 * @return	The list of the available Passport Reader devices.
	 */
	inline gxOutStrArray GetDeviceList(void) throw(gxError) {
		wchar_t **devices;
		int ndevices = 0;
		GX_GETHANDLE(h);
		if(!pr_getdevicelist(h,&devices,&ndevices)) {
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		return GX_PUTGSTRINGARRAY(devices, ndevices, true);
	}
#endif

#ifdef GX_ASCII
	/** Returns a list of the available Passport Reader devices (ASCII version).
	 *
	 * @return	The list of the available Passport Reader devices.
	 */
	inline gxOutAStrArray GetDeviceListA(void) throw(gxError) {
		char **devices;
		int ndevices = 0;
		if(!pr_getdevicelist(*this,&devices,&ndevices)) {
			gxthrow;
			return GX_PUTGASTRINGARRAY_NONE;
		}
		return GX_PUTGASTRINGARRAY(devices, ndevices, true);
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Connects a PR device (Unicode version).
	 *
	 * To get a list of the available devices call the GetDeviceList() method.
	 *
	 * @param device	Name of the device to connect to.
	 * @param mode		Connection mode. The possible values are defined in the \ref
	 *					PR_USAGEMODE enumeration. Generally the \ref PR_UMODE_FULL_CONTROL
	 *					is recommended to use.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool UseDevice(wchar_t *device,int mode) throw(gxError) {
		bool st = pr_usedevice(*this,device,mode)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Conects to a PR device (ASCII version).
	 *
	 * To get a list of the available devices call the GetDeviceList() method.
	 *
	 * @param device	Name of the device to connect to.
	 * @param mode		Connection mode. The possible values are defined in the \ref
	 *					PR_USAGEMODE enumeration. Generally the \ref PR_UMODE_FULL_CONTROL
	 *					is recommended to use.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool UseDevice(char *device,int mode) throw(gxError) {
		bool st = pr_usedevice(*this,device,mode)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Conects to a PR device (Unicode version).
	 *
	 * To get a list of the available devices call the GetDeviceList() method.
	 *
	 * @param device	Name of the device to connect to.
	 * @param mode		Connection mode. The possible values are defined in the \ref
	 *					PR_USAGEMODE enumeration. Generally the \ref PR_UMODE_FULL_CONTROL
	 *					is recommended to use.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool UseDevice(gxInStr device,int mode) throw(gxError) {
		GX_GETSTRING(_device, device);
		GX_GETHANDLE(h);
		bool st = pr_usedevice(h, _device,mode)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Conects to a PR device (ASCII version).
	 *
	 * To get a list of the available devices call the GetDeviceListA() method.
	 *
	 * @param device	Name of the device to connect to.
	 * @param mode		Connection mode. The possible values are defined in the \ref
	 *					PR_USAGEMODE enumeration. Generally the \ref PR_UMODE_FULL_CONTROL
	 *					is recommended to use.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool UseDevice(gxInAStr device,int mode) throw(gxError) {
		GX_GETASTRING(_device, device);
		GX_GETHANDLE(h);
		bool st = pr_usedevice(h, _device,mode)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Conects to a PR device.
	 *
	 * @param devno		Ordinal number of the device to connect to.
	 * @param mode		Connection mode. The possible values are defined in the \ref
	 *					PR_USAGEMODE enumeration. Generally the \ref PR_UMODE_FULL_CONTROL
	 *					is recommended to use.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool UseDevice(int devno,int mode) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_usedevice(h,devno,mode)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Disconnects the connected device.
	 *
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CloseDevice(void) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_closedevice(h)!=0;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns the handle of the capturing device (Obsolete).
	 *
	 * @return The handle of the used device. On error 0 is returned and the error
	 *			code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline gxHANDLE * GetDeviceHandle(void) {
		gxHANDLE *hctrl;
		return pr_getctrlhandle(*this,&hctrl) ? hctrl : (gxHANDLE*)0;
	}
#endif

	/** Calibrates the used device.
	 *
	 * This method generates data for correcting the geometrical and colour distortions
	 * of the capturing system. This process can take up to 30-60 seconds according to the
	 * computer's speed. For this method to work the \e calibration \e image is needed.
	 *
	 * @param windowid	Id of the used window. The possible values are defined in the
	 *					\ref PR_WINDOW_ID enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Calibrate(int windowid GX_DEFARG(0)) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_calibrate(h,windowid)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Tests the calibrated state of the device.
	 *
	 * @param windowid	Id of the used window. The possible values are defined in the
	 *					\ref PR_WINDOW_ID enumeration.
	 * @return If the device is calibrated the method returns true. Otherwise it
	 *			returns false and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline bool IsCalibrated(int windowid GX_DEFARG(0)) {
		GX_GETHANDLE(h);
		return pr_iscalibrated(h,windowid)!=0;
	}

	/** Returns the result of the document (motion) detection module.
	 *
	 * The possible result values are defined in the \ref PR_TESTDOC enumeration. Call this method
	 * 2-3 times in every second. When the result is \ref PR_TD_IN the document is ready
	 * for capturing. The document detection is working only when the freerun_mode
	 * property contains the \ref PR_FRMODE_TESTDOCUMENT value.
	 *
	 * @param windowid	Id of the used window. The possible values are defined in
	 *					\ref PR_WINDOW_ID enumeration.
	 * @return The result of the motion detection. On error -1 is returned and the
	 *			error code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline int TestDocument(int windowid GX_DEFARG(0)) {
		int state;
		GX_GETHANDLE(h);
		return pr_testdocument(h,&state,windowid) ? state : -1;
	}

	/** Returns the number of usable lights of the device.
	 *
	 * @return The number of the usable lights. On error 0 is returned and the
	 *			error code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline int Lights(void) {
		int lights;
		GX_GETHANDLE(h);
		return pr_getlightnumber(h,&lights) ? lights : 0;
	}

	/** Returns the id of the light specified by the index.
	 *
	 * @param itemno	The index of the light.
	 * @return The id of the light. On error 0 is returned and the
	 *			error code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline int LightListItem(int itemno) {
		int lights[MAX_LIGHTS];
		if(itemno>=MAX_LIGHTS)return 0;
		GX_GETHANDLE(h);
		return pr_getlightlist(h,lights,MAX_LIGHTS) ? lights[itemno] : 0;
	}

	/** Returns a light mask for a given light and window.
	 *
	 * It is usable to test if the a light is available for the device or one of its object windows.
	 * It can return a whole light mask for a given object window if the lightid is null.
	 * Light masks are used by the SetPageLight() function.
	 *
	 * @param lightid	The id of the interesting light. The possible values are defined
	 *					in the \ref PR_LIGHT enumeration. If this value is null the fuction returns the whole
	 *					light mask of the given object window.
	 * @param windowid	The id of the interesting object window. The possible values
	 *					are defined in the \ref PR_WINDOW_ID enumeration. If the value is \ref PR_OW_DEFAULT (null)
	 *					the fuction returns the light mask of the device.
	 * @return The light mask. On error 0 is returned and the
	 *			error code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline int LightMask(int lightid,int windowid) {
		int lightmask;
		GX_GETHANDLE(h);
		return pr_getlightmask(h,&lightmask,lightid,windowid) ? lightmask : 0;
	}

	/** Returns the number of object windows of the device.
	 *
	 * @return The number of the usable lights. On error 0 is returned and the
	 *			error code/string in the GX system is set appropriately. ( see gx_geterror() )
	 */
	inline int ObjectWindows(void) {
		int windows;
		GX_GETHANDLE(h);
		return pr_getwindownumber(h,&windows) ? windows : 0;
	}

	/** Turns on/off the status leds.
	 *
	 * @param ledmask	Mask representing the status leds. Each bit represents a status led on the device.
	 * @param color		The color to display on the specified status leds. The predefined values of the lights
	 *					are stored in the \ref PR_STATUS_LED_COLOR enumeration. Bit 7 represents the on/off
	 *					parameter of the light so any value below 80 hex means led off.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool SetStatusLed(int ledmask, int color) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_setstatusled(h, ledmask, color)!=0;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Blinks status outputs (led or buzzer).
	 *
	 * @param coding		Coding of the data. The possible values are:
	 *							0: stop pulses,
	 *							1: data[odd]: time duration output high level [ms], data[even]: time duration output low level [ms]
	 * @param mask			Mask representing the status leds and buzzer. Each bit represents a status led or buzzer on the device.
	 * @param type			Led color id or buzzer id. Its predefined values are stored in the \ref PR_STATUS_LED_COLOR
	 *						and \ref PR_BUZZER enumerations.
	 * @param iteration		Number of repeat, 0 menas forever.
	 * @param data			Data of blinking.
	 * @param datalength	Length of the data, (maximum 16).
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool BlinkStatus(int coding, int mask, int type, int iteration, unsigned int *data, unsigned int datalength) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_blinkstatus(h, coding, mask, type, iteration, data, datalength)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifndef NO_GX_STL
	/** Blinks status outputs (led or buzzer).
	 *
	 * @param coding		Coding of the data. The possible values are:
	 *							0: stop pulses,
	 *							1: data[odd]: time duration output high level [ms], data[even]: time duration output low level [ms]
	 * @param mask			Mask representing the status leds and buzzer. Each bit represents a status led or buzzer on the device.
	 * @param type			Led color id or buzzer id. Its predefined values are stored in the \ref PR_STATUS_LED_COLOR
	 *						and \ref PR_BUZZER enumerations.
	 * @param iteration		Number of repeat, 0 menas forever.
	 * @param data			Data of blinking, (maximum 16).
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool BlinkStatus(int coding, int mask, int type, int iteration, gxInIntArray data) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETININTARRAY(data);
		bool st = pr_blinkstatus(h, coding, mask, type, iteration,(unsigned int *)GX_GETININTARRAY_PTR(data), GX_GETININTARRAY_LEN(data))!=0;
		GX_FREEININTARRAY(data);
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Gets the power state of the device.
	 *
	 * @return		On error -1 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline int TestPowerState(void) {
		int state;
		GX_GETHANDLE(h);
		return pr_testpower(h,&state,0) ? state : -1;
	}

	/** Gets the power level of the device.
	 *
	 * In case of devices without battery -1 is returned.
	 *
	 * @return		On error -2 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline int TestPowerLevel(void) {
		int state,level;
		GX_GETHANDLE(h);
		return pr_testpower(h,&state,&level) ? level : -1;
	}

	/** Gets the device's button state.
	 *
	 * @param keycode	The code of the button/key.
	 * @return		On error -1 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline int TestButton(int keycode) {
		int state;
		GX_GETHANDLE(h);
		return pr_testbutton(h,keycode,&state) ? state : -1;
	}

	/** Suspends the Passport Reader system.
	 *
	 * It may be called for example when the operating system tries to suspend or
	 * for power saving reasons you want to suspend the connected device. Depending on the
	 * type of the device and the control level set different suspend levels can be reached.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool Suspend() throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_suspend(h)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Wakes up the previously suspended Passport Reader system.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool WakeUp() throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_wakeup(h)!=0;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Gets information about the available user data space.
	 *
	 * @param nblocks	Number of blocks.
	 * @param sblock	Size of a block.
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetUDInfo(int *nblocks, int *sblock) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_getudinfo(h, nblocks, sblock) != 0;
		gxcondthrow(!st);
		return st;
	}

	/** Reads the user data from the device.
	 *
	 * The application must call the gx_globalfree() function for the data to
	 * free the allocated memory.
	 *
	 * @param fblock	First block to read.
	 * @param nblocks	Number of blocks to read.
	 * @param data		Bytes read.
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool ReadUData(int fblock, int nblocks, void **data) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_readudata(h, fblock, nblocks, data) != 0;
		gxcondthrow(!st);
		return st;
	}

	/** Writes the user data in the used device.
	 *
	 * @param fblock	First block to write.
	 * @param nblocks	Number of blocks to write.
	 * @param data		Bytes to write.
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool WriteUData(int fblock, int nblocks, const void *data) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_writeudata(h, fblock, nblocks, data) != 0;
		gxcondthrow(!st);
		return st;
	}
#else

	/** Reads the user data from the device.
	 *
	 * @param fblock	First block to read.
	 * @param nblocks	Number of blocks to read.
	 * @return  On error null is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline gxOutData ReadUData(int fblock, int nblocks) throw(gxError) {
		GX_GETHANDLE(h);
		void *data;
		if (pr_readudata(h, fblock, nblocks, &data) == 0) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		int i,sblock;
		if (pr_getudinfo(h, &i, &sblock) == 0) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		i=nblocks*sblock;
		gxOutData od = GX_PUTDATA(data, i);
		if(data) gx_globalfree(data);
		return od;
	}

	/** Writes the user data in the used device.
	 *
	 * @param fblock	First block to write.
	 * @param nblocks	Number of blocks to write.
	 * @param data		Bytes to write.
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool WriteUData(int fblock, int nblocks, gxInData data) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETDATA(data);
		bool st = pr_writeudata(h, fblock, nblocks, GX_DATAPTR(data)) != 0;
		gxcondthrow(!st);
		return st;
	}
#endif /* GX_SWIG && GX_DOTNET */

	/** Returns the number of blocks available in the user data space.
	 *
	 * @return		On error -1 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline int GetUDNumberOfBlocks(void) throw(gxError) {
		GX_GETHANDLE(h);
		int nblocks;
		int sblock;
		bool st = pr_getudinfo(h, &nblocks, &sblock) != 0;
		gxcondthrow(!st);
		return st ? nblocks : -1;
	}

	/** Returns the block size of the user data space.
	 *
	 * @return		On error -1 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline int GetUDBlockSize(void) throw(gxError) {
		GX_GETHANDLE(h);
		int nblocks;
		int sblock;
		bool st = pr_getudinfo(h, &nblocks, &sblock) != 0;
		gxcondthrow(!st);
		return st ? sblock : -1;
	}

	/** Returns the information about the used device.
	 *
	 * @return		The device info in variant data type.
	 */
	inline gxVariant * GetDeviceInfo() throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT d;
		bool st = pr_getdeviceinfo(h,&d) != 0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!d) return 0;
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(d);
			gx_unrefvariant(d);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(d);
		#endif
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Performs device self test.
	 *
	 * @param condition		Test control condition that declares the type of object which is placed
	 *						on the document window (0: unknown/nothing, 1: white image, 2: calibration image, 3: document with MRZ line)
	 * @return		A list of partial test results. The test element ids are defined in \ref PR_SELFTEST_ELEMENTS enumeration, and
	 *				the result values are defined in \ref PR_SELFTEST_RESULT enumeration.
	 */
	inline gxVariant * SelfTest(int condition) throw(gxError) {
		GX_GETHANDLE(h);
		gxVARIANT result;
		bool st = pr_selftest(h, condition, &result)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if (!result) return 0;
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(result);
			gx_unrefvariant(result);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(result);
		#endif
		if (!vr) { gxSystem::SetError(GXEC GX_ENOMEM); gxthrow; }
		return vr;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Reads magnetic stripe (Unicode version).
	 *
	 * The application must call the gx_globalfree() function for the tracks to
	 * free the allocated memory.
	 *
	 * @param tracks		Buffer for a pointer to the list of tracks.
	 * @param ntracks		Buffer for the number of tracks.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool ReadMagstripe(wchar_t ***tracks, int *ntracks) throw(gxError) {
		bool st = pr_readmagstripe(*this, tracks, ntracks)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Reads magnetic stripe (ASCII version).
	 *
	 * The application must call the gx_globalfree() function for the tracks to
	 * free the allocated memory.
	 *
	 * @param tracks		Buffer for a pointer to the list of tracks.
	 * @param ntracks		Buffer for the number of tracks.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool ReadMagstripe(char ***tracks, int *ntracks) throw(gxError) {
		bool st = pr_readmagstripe(*this, tracks, ntracks)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Reads magnetic stripe (Unicode version).
	 *
	 * @return		The list of the read tracks.
	 */
	inline gxOutStrArray ReadMagstripe(void) throw(gxError) {
		wchar_t **tracks;
		int ntracks = 0;
		GX_GETHANDLE(h);
		if(!pr_readmagstripe(h, &tracks, &ntracks)) {
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		return GX_PUTGSTRINGARRAY(tracks, ntracks, true);
	}
#endif

#ifdef GX_ASCII
	/** Reads magnetic stripe (ASCII version).
	 *
	 * @return		The list of the read tracks.
	 */
	inline gxOutAStrArray ReadMagstripeA(void) throw(gxError) {
		char **tracks;
		int ntracks = 0;
		GX_GETHANDLE(h);
		if(!pr_readmagstripe(h, &tracks, &ntracks)) {
			gxthrow;
			return GX_PUTGASTRINGARRAY_NONE;
		}
		return GX_PUTGASTRINGARRAY(tracks, ntracks, true);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** The event function is a callback function which is called during capture.
	 *
	 * There are different kind of events. The event types and the events are defined
	 * in the \ref PR_EVENT enumeration. The invoked event types can be set through the
	 * event_types property.
	 *
	 * @param eventhandler	Reference to the callback function.
	 * @param param			User parameter.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SetEventFunction(PR_EVFUNC *eventhandler,void *param) {
		return pr_seteventfunction(*this,eventhandler,param)!=0;
	}
#endif

#if (defined(WIN32) || defined(GX_MANUAL)) && !defined(GX_SWIG)

	/** Starts window messaging process (WIN32 function).
	 *
	 * After starting window messaging process the freerun mode events will be raised
	 * and all the PR events will be appeared as standard window messages too.
	 * No threaded poll is needed to test for example the state of the button.
	 * The message will arrive to the window handle set in case of status change.
	 * To stop the messaging process call the EndWindowMessaging() function.
	 *
	 * @param hwnd		Window handle to send the messages to. This parameter can be
	 *					0 to disable window messaging.
	 * @param base_msg	Message id base. Set this parameter if you want to use other
	 *					than the default message id space. Make sure of not using
	 *					the same space in other parts of your program.
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
#ifndef GX_DOTNET
	inline bool BeginWindowMessaging(HWND hwnd, UINT base_msg GX_DEFARG(WM_USER)) throw(gxError) {
		bool st = pr_beginwindowmessaging(*this,hwnd, base_msg)!=0;
		gxcondthrow(!st);
		return st;
	}
#else
	inline bool BeginWindowMessaging(gxInPtr hwnd, UINT base_msg GX_DEFARG(WM_USER)) throw(gxError) {
 		GX_GETHANDLE(h);
		bool st = pr_beginwindowmessaging(h,hwnd.ToPointer(), base_msg)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Ends window messaging process (WIN32 function).
	 *
	 * After calling this function no further window messages nor
	 * freerun events will arrive.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline bool EndWindowMessaging() throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_endwindowmessaging(h)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif/* WIN32 GX_SWIG */

#if (defined(LINUX) || defined(GX_MANUAL)) && !defined(GX_SWIG)

	/** Starts automated background process (Linux function).
	 *
	 * After starting the background process the freerun mode events will be raised.
	 * No threaded poll is needed to test for example the state of the button.
	 * To stop the messaging process call the StopBGProcesses() function.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int StartBGProcesses() throw(gxError) {
		bool st = pr_startbgprocesses(*this);
		gxcondthrow(!st);
		return st;
	}

	/** Ends the automated background process (Linux function).
	 *
	 * After calling this function no further freerun events will arrive.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int StopBGProcesses() {
		return pr_stopbgprocesses(*this);
	}

#endif/* LINUX GX_SWIG */

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Sets the number of document pages to capture and the needed lights for each page.
	 *
	 * More than one page is usable when visa is needed for a passport or when both sides
	 * of an Id card is needed to be read.
	 *
	 * @param pages		Number of document pages to read.
	 * @param lights	Array of light masks where each integer represents a page.
	 *					Each lower bit of them represents a light mask bit. The upper 8 bits represent the
	 *					id of the object window. The light mask bits can be tested by the LightMask()
	 *					function. The object window ids are defined in the \ref PR_WINDOW_ID enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SetPageLight(int pages,unsigned int *lights) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_setpagelight(h,pages,lights)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifndef NO_GX_STL
	/** Sets the number of document pages to capture and the needed lights for each page.
	 *
	 * More than one page is usable when visa is needed for a passport or when both sides
	 * of an Id card is needed to be read. The dimensions of the lights array parameter
	 * gives the number of document pages.
	 *
	 * @param lights	Array of light masks where each integer represents a page.
	 *					Each lower bit of them represents a light mask bit. The upper 8 bits represent the
	 *					id of the object window. The light mask bits can be tested by the LightMask()
	 *					function. The object window ids are defined in the \ref PR_WINDOW_ID enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SetPageLight(gxInIntArray lights) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETININTARRAY(lights);
		bool st = pr_setpagelight(h,GX_GETININTARRAY_LEN(lights),(unsigned int *)GX_GETININTARRAY_PTR(lights))!=0;
		GX_FREEININTARRAY(lights);
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Captures an image sequence from the object window of the PR device.
	 *
	 * To set the lights needed for capture call the SetPageLight()
	 * method. To set a callback function to inform the state of the capturing call
	 * the SetEventFunction() method. The captured images are stored in an internal
	 * array. The image handling functions are part of the api (draw, save, recognize...).
	 *
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool Capture(void) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_capture(h)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Starts the image capturing process in asynchronous mode.
	 *
	 * See Capture() for details. Only one capture can be started at a time. The CaptureStatus()
	 * or the CaptureWait() methods must be called in order the system to call the
	 * Event function. (see SetEventFunction() )
	 *
	 * @return Id for the CaptureStatus() and the CaptureWait() methods.
	 *			On error -1 is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline int CaptureStart() throw(gxError) {
		GX_GETHANDLE(h);
		int reqid;
		bool st = pr_capture_start(h,&reqid)!=0;
		gxcondthrow(!st);
		return st ? reqid : -1;
	}

	/** Returns the state of an image capture process started with the CaptureStart() method.
	 *
	 * If an internal event occurred this method calls the Event function.
	 *
	 * @param reqid		Id for the capture. The CaptureStart() returned this value.
	 * @return The value of the result is in percent, it can be negative when the capture is in
	 *			preprocess state. On error -1 is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline int CaptureStatus(int reqid) throw(gxError) {
		GX_GETHANDLE(h);
		int status;
		bool st = pr_capture_getstatus(h,reqid,&status)!=0;
		gxcondthrow(!st);
		return st ? status : -1;
	}

	/** Ends the capture process started with the CaptureStart() method.
	 *
	 * If there are internal events waiting for report this method calls the Event function.
	 *
	 * @param reqid		Id of the capture returned by the CaptureStart() method.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CaptureWait(int reqid) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_capture_wait(h,reqid)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Captures a preview image.
	 *
	 * The preview image is a small resolution real-time
	 * captured image. The lights for preview capture can be set through the
	 * preview_light property. For preview light control the freerun_mode property
	 * must contain the \ref PR_FRMODE_PREVIEWLIGHT value.
	 *
	 * @param windowid	Id of the used window. The possible values are defined in
	 *					\ref PR_WINDOW_ID enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CapturePreview(int windowid GX_DEFARG(0)) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_capture_preview(h,windowid)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** The Passport Reader system has several functions for working with the captured images.
	 * In special cases user functions can be used that are not supported by the system.
	 * This method returns a prImage object. The image data can be accessed throught this object.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meanings.
	 * @return	A prImage object that contains the image data.
	 *			On error 0 is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prImage * GetImage(int page,int light,int type) throw(gxError) {
		gxVARIANT img = 0;
		prImage *cimg = 0;
		GX_GETHANDLE(h);
		if(!pr_getimage(h,page,light,type,&img)) {
			gxthrow;
			return cimg;
		}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
		if(img)
#endif
			cimg = new prImage(img);
		if(img)gx_unrefvariant(img);
#if !defined(GX_DOTNET) && !defined(GX_SWIG)
		if(img)
#endif
			if(!cimg){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!img) gxSystem::ClearError();
		return cimg;
	}

	/** Get enhanced UV.
	 *
	 * Make enhanced UV image from the captured UV and white image.
	 * The Passport Reader system going to remove white backlight from UV.
	 *
	 * @param page		The actual page of the image.
	 * @param imgtype	The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration.
	 * @return	A gxVariant object that contains the image data.
	 *			On error 0 is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline gxVariant * GetEnhancedUV(int page, int imgtype) throw(gxError) {
		gxVARIANT img = 0;
		GX_GETHANDLE(h);
		if(!pr_getenhanceduv(h, page, imgtype, &img)) {
			gxthrow;
			return 0;
		}
		#ifndef GX_DOTNET
			gxVariant * im = new gxVariant(img);
			gx_unrefvariant(img);
		#else
			gxVariant * im = new gxVariant();
			im->_set_variant(img);
		#endif
		if(!im){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		return im;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Saves an image to a file (Unicode version).
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meanings.
	 * @param filename	The name of the file where to save the image.
	 * @param filetype	File type. The currently supported file types are defined in gximage.h.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SaveImage(int page,int light,int type,const wchar_t *filename,int filetype) throw(gxError) {
		bool st = pr_saveimage(*this,page,light,type,filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image to a file (ASCII version).
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meanings.
	 * @param filename	The name of the file where to save the image.
	 * @param filetype	File type. The currently supported file types are defined
	 *					in gximage.h.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SaveImage(int page,int light,int type,const char *filename,int filetype) throw(gxError) {
		bool st = pr_saveimage(*this,page,light,type,filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Saves an image to a file (Unicode version).
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meanings.
	 * @param filename	The name of the file where to save the image.
	 * @param filetype	File type. The currently supported file types are defined
	 *					in gximage.h.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SaveImage(int page,int light,int type,gxInStr filename,int filetype) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_filename, filename);
		bool st = pr_saveimage(h,page,light,type,_filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Saves an image to a file (ASCII version).
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meanings.
	 * @param filename	The name of the file where to save the image.
	 * @param filetype	File type. The currently supported file types are defined
	 *					in gximage.h.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool SaveImage(int page,int light,int type,gxInAStr filename,int filetype) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_filename, filename);
		bool st = pr_saveimage(h,page,light,type,_filename,filetype)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if (defined(WIN32) || defined(GX_MANUAL)) && !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Displays an image (WIN32 function).
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 *					the \ref PR_IMAGE_TYPE enumeration. If the type is \ref PR_IT_PREVIEW
	 *					the page and light parameters have no meaning.
	 * @param hdc		Handle to the device context.
	 * @param x			Left side of the draw area.
	 * @param y			Upper side of the draw area.
	 * @param xsize		Horizontal size of the draw area.
	 * @param ysize		Vertical size of the draw area.
	 * @param frame		Frame of the area on the image to display.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool DisplayImage(int page,int light,int type,HDC hdc,int x,int y,int xsize,int ysize,gxRCT *frame) throw(gxError) {
		bool st = pr_drawimage(*this,page,light,type,hdc,x,y,xsize,ysize,frame)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Saves the fingers to an nist file (Unicode version).
	 *
	 * @param filename	The name of the file where to save the data.
	 * @param fields	List of fields to add to the record.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool FingerToNist(const wchar_t *filename,gxVariant *fields) throw(gxError) {
		bool st = pr_fingertonist(*this,filename,(fields)?fields->_variant:0)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Saves the fingers to an nist file (ASCII version).
	 *
	 * @param filename	The name of the file where to save the data.
	 * @param fields	List of fields to add to the record.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool FingerToNist(const char *filename,gxVariant *fields) throw(gxError) {
		bool st = pr_fingertonist(*this,filename,(fields)?fields->_variant:0)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Saves the fingers to a memory area as a nist file.
	 *
	 * @param buffer	Pointer to the memory area pointer that is large enough or NULL.
	 * @param buflen	Size of memory area.
	 * @param fields	List of fields to add to the record.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool FingerToNistMem(void **buffer, int *buflen,gxVariant *fields) throw(gxError) {
		bool st = pr_fingertonistmem(*this,buffer,buflen,fields?fields->_variant:0)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Saves the fingers to an nist file (Unicode version).
	 *
	 * @param filename	The name of the file where to save the data.
	 * @param fields	List of fields to add to the record.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool FingerToNist(gxInStr filename,gxVariant *fields) throw(gxError) {
		GX_GETHANDLE(h);
#ifdef GX_DOTNET
		gxVARIANT var = fields?(gxVARIANT)GX_GETPTR(fields->_get_variant()):0;
#else
		gxVARIANT var = fields?fields->_variant:0;
#endif
		GX_GETSTRING(_filename, filename);
		bool st = pr_fingertonist(h,_filename,var)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Saves the fingers to an nist file (ASCII version).
	 *
	 * @param filename	The name of the file where to save the data.
	 * @param fields	List of fields to add to the record.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool FingerToNist(gxInAStr filename,gxVariant *fields) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_filename, filename);
		bool st = pr_fingertonist(h,_filename,(fields)?fields->_variant:0)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Saves the fingers to a memory area as a nist file.
	 *
	 * @param fields	List of fields to add to the record.
	 * @return		Saved nist data. An exception is thrown or null is returned in case of error. */
	inline gxOutData FingerToNistMem(gxVariant *fields) throw(gxError) {
		void *buffer = (void *)0;
		gxi32 buflen = 0;
		GX_GETHANDLE(h);
#ifdef GX_DOTNET
		gxVARIANT var = fields?(gxVARIANT)GX_GETPTR(fields->_get_variant()):0;
#else
		gxVARIANT var = fields?fields->_variant:0;
#endif
		if(!pr_fingertonistmem(h,&buffer,&buflen,var)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(buffer, buflen);
		if(buffer) gx_globalfree(buffer);
		return ret;
	}
#endif

	/** Clears all the image and document buffers and deletes the internal image and
	 * document structures.
	 *
	 * This method is called automatically when each previously set number of pages are
	 * captured and a new capture process is started, or when the number of pages are
	 * modified and the actual page number is greater than the new number of pages.
	 *
	 * @param lastpage	Set it to true for reset only the last captured page.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool ResetDocument(int lastpage GX_DEFARG(0)) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_resetdocument(h, lastpage)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Reads the OCR from an unknown document.
	 *
	 * The returned document structure will contain just the recognized rows without additional
	 * details, even when the type of the document is known.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
						\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetOcr(int page,int light,int type) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_getocr(h,page,light,type,&doc,0)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Reads the OCR from an unknown document.
	 *
	 * The returned document structure will contain just the recognized rows without additional
	 * details, even when the type of the document is known.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
						\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
	 * @param ocrparams	Ocr parameters.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetOcr(int page,int light,int type,gxVariant *ocrparams) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
#ifdef GX_DOTNET
		gxVARIANT var = ocrparams?(gxVARIANT)GX_GETPTR(ocrparams->_get_variant()):0;
#else
		gxVARIANT var = ocrparams?ocrparams->_variant:0;
#endif

		if(!pr_getocr(h,page,light,type,&doc,var)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Reads the MRZ lines from the document.
	 *
	 * This method is for compatibility reasons with the old system.
	 * The Recognize() method should be called instead, except when the speed is important.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
						\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetMrz(int page,int light,int type) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_getmrz(h,page,light,type,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Reads the barcodes from an unknown document.
	 *
	 * The returned document structure will contain just the barcode data without
	 * additional information, even when the type of the document is known.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 *					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
	 * @param bctype	The needed barcode type. The possible values are defined in
	 *					\ref PR_BCTYPE enumeration. If this parameter is NULL any
	 *					type of barcode can be returned.
	 * @param index		The ordinal number of the barcode. If more barcodes found.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetBarcode(int page,int light,int type,int bctype,int index) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_getbarcode(h,page,light,type,bctype,index,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Returns the quad of the document.
	 *
	 * This method is retained for compatibility reasons with the old system.
	 * This quad was used to produce the document view.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
						\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. It must be \ref PR_IT_ORIGINAL.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * GetDocumentRect(int page,int light,int type) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_getdocumentrect(h,page,light,type,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Reads all of the known data from a known document type.
	 *
	 * The method finds the quad of the document, recognizes it's type and reads
	 * MRZ, VIZ and BC fields from it.
	 *
	 * @param page		The actual page of the image.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * Recognize(int page) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_recognize(h,page,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Reads the data specified in task array from the document.
	 *
	 * @param page		List of images to read from.
	 * @param tasklen	Size of the task array.
	 * @param task		Int array specifies the reading task.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * Analyze(gxVariant *page, int tasklen, int *task) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!page) { gxSystem::SetError(GX_EINVAL, L"(page)"); gxthrow; return cdoc; }
#ifdef GX_DOTNET
		gxVARIANT var = page ? (gxVARIANT)GX_GETPTR(page->_get_variant()) : 0;
#else
		gxVARIANT var = page ? page->_variant : 0;
#endif
		if(!pr_analyze(h, var, tasklen, task, &doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Separates and processes the data fields in a given binary data array.
	 *
	 * @param page		List of images to read from.
	 * @param buffer	Input buffer.
	 * @param buflen	Number of bytes in the buffer.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * Analyze(gxu8 *buffer, int buflen) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_analyze(h, buffer, buflen, &doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#ifndef NO_GX_STL
	/** Reads the data specified in task array from the document.
	 *
	 * @param page		List of images to read from.
	 * @param task		Int array specifies the reading task.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * Analyze(gxVariant *page, gxInIntArray task) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!page) { gxSystem::SetError(GX_EINVAL); gxthrow; return cdoc; }
#ifdef GX_DOTNET
		gxVARIANT var = page ? (gxVARIANT)GX_GETPTR(page->_get_variant()) : 0;
#else
		gxVARIANT var = page ? page->_variant : 0;
#endif
		GX_GETININTARRAY(task);
		bool st = pr_analyze(h, var, GX_GETININTARRAY_LEN(task), GX_GETININTARRAY_PTR(task), &doc)!=0;
		GX_FREEININTARRAY(task);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Separates and processes the data fields in a given binary data array.
	 *
	 * @param page		List of images to read from.
	 * @param buffer	Input buffer.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * Analyze(gxInData buffer) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETDATA(buffer);
		bool st = pr_analyze(h, (gxu8*)GX_DATAPTR(buffer), GX_DATALEN(buffer), &doc)!=0;
		GX_FREEDATA(buffer);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Separates the data fields in the given MRZ text (Unicode version).
	 *
	 * It can be used to separate user defined MRZ in appropriate document fields.
	 *
	 * @param lines		Array of row strings.
	 * @param nlines	Number of rows.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMrzText(const wchar_t **lines,int nlines) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_resolvemrztext(*this,lines,nlines,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Separates the data fields in the given MRZ text (ASCII version).
	 *
	 * It can be used to separate user defined MRZ in appropriate document fields.
	 *
	 * @param lines		Array of row strings.
	 * @param nlines	Number of rows.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMrzText(const char **lines,int nlines) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_resolvemrztext(*this,lines,nlines,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#ifdef GX_UNICODE	/*(*/
	/** Separates the data fields in the given MRZ text (Unicode version).
	 *
	 * It can be used to separate user defined MRZ in appropriate document fields.
	 *
	 * @param lines		Array of row strings.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMrzText(gxInStrArray lines) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETINSTRARRAY(lines);
		bool st = pr_resolvemrztext(h,(const wchar_t**)GX_GETINSTRARRAY_PTR(lines),GX_GETINSTRARRAY_LEN(lines),&doc)!=0;
		GX_FREEINSTRARRAY(lines);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/*)*/

#ifdef GX_ASCII	/*(*/
	/** Separates the data fields in the given MRZ text (ASCII version).
	 *
	 * It can be used to separate user defined MRZ in appropriate document fields.
	 *
	 * @param lines		Array of row strings.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMrzText(gxInAStrArray lines) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETINASTRARRAY(lines);
		bool st = pr_resolvemrztext(h,(const char**)GX_GETINASTRARRAY_PTR(lines),GX_GETINASTRARRAY_LEN(lines),&doc)!=0;
		GX_FREEINASTRARRAY(lines);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/*)*/

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Separates the data fields in the given magnetic stripe text (Unicode version).
	 *
	 * @param tracks	Array of row strings.
	 * @param ntracks	Number of rows.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMagstripe(const wchar_t **tracks, int ntracks) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_resolvemagstripe(*this, tracks, ntracks, &doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Separates the data fields in the given magnetic stripe text (ASCII version).
	 *
	 * @param tracks	Array of row strings.
	 * @param ntracks	Number of rows.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMagstripe(const char **tracks, int ntracks) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_resolvemagstripe(*this, tracks, ntracks, &doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc, *this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#ifdef GX_UNICODE	/*(*/
	/** Separates the data fields in the given magnetic stripe text (Unicode version).
	 *
	 * @param tracks	Array of row strings.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMagstripe(gxInStrArray tracks) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETINSTRARRAY(tracks);
		bool st = pr_resolvemagstripe(h, (const wchar_t**)GX_GETINSTRARRAY_PTR(tracks), GX_GETINSTRARRAY_LEN(tracks), &doc)!=0;
		GX_FREEINSTRARRAY(tracks);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/*)*/

#ifdef GX_ASCII	/*(*/
	/** Separates the data fields in the given magnetic stripe text (ASCII version).
	 *
	 * @param tracks	Array of row strings.
	 * @return	A prDoc object that contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * ResolveMagstripe(gxInAStrArray tracks) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETINASTRARRAY(tracks);
		bool st = pr_resolvemagstripe(h, (const char**)GX_GETINASTRARRAY_PTR(tracks), GX_GETINASTRARRAY_LEN(tracks), &doc)!=0;
		GX_FREEINASTRARRAY(tracks);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc) { gxSystem::SetError(GX_ENOMEM); gxthrow; }
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/*)*/

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Gets the list of cards in the range of the contactless reader (Unicode version).
	 *
	 * The application must call the gx_globalfree() function for the cards to
	 * free the allocated memory.
	 *
	 * @param cards		List of card serial numbers.
	 * @param ncards	Number of cards in list.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetRfidCardList(wchar_t ***cards,int *ncards) throw(gxError) {
		bool st = pr_getrfidcardlist(*this,cards,ncards)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the list of cards in the range of the contactless reader (ASCII version).
	 *
	 * The application must call the gx_globalfree() function for the cards to
	 * free the allocated memory.
	 *
	 * @param cards		List of card serial numbers.
	 * @param ncards		Number of cards in list.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetRfidCardList(char ***cards,int *ncards) throw(gxError) {
		bool st = pr_getrfidcardlist(*this,cards,ncards)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Gets the list of cards in the range of the contactless reader (Unicode version).
	 *
	 * @return The list of cards.
	 */
	inline gxOutStrArray GetRfidCardList(void) throw(gxError) {
		wchar_t **cards;
		int ncards = 0;
		GX_GETHANDLE(h);
		if(!pr_getrfidcardlist(h,&cards,&ncards)) {
			gxthrow;
			return GX_PUTGSTRINGARRAY_NONE;
		}
		return GX_PUTGSTRINGARRAY(cards, ncards, true);
	}
#endif

#ifdef GX_ASCII
	/** Gets the list of cards in the range of the contactless reader (ASCII version).
	 *
	 * @return The list of cards.
	 */
	inline gxOutAStrArray GetRfidCardListA(void) throw(gxError) {
		char **cards;
		int ncards = 0;
		if(!pr_getrfidcardlist(*this,&cards,&ncards)) {
			gxthrow;
			return GX_PUTGASTRINGARRAY_NONE;
		}
		return GX_PUTGASTRINGARRAY(cards, ncards, true);
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Connects to an RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool ConnectRfidCard(const wchar_t *card) throw(gxError) {
		bool st = pr_connectrfidcard(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Connects to an RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool ConnectRfidCard(const char *card) throw(gxError) {
		bool st = pr_connectrfidcard(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Disconnects from an RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool DisconnectRfidCard(const wchar_t *card) throw(gxError) {
		bool st = pr_disconnectrfidcard(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Disconnects from an RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool DisconnectRfidCard(const char *card) throw(gxError) {
		bool st = pr_disconnectrfidcard(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_UNICODE

	/** Connects to an RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool ConnectRfidCard(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_connectrfidcard(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Disconnects from an RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool DisconnectRfidCard(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_disconnectrfidcard(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_ASCII

	/** Connects to an RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool ConnectRfidCard(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_connectrfidcard(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Disconnects from an RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool DisconnectRfidCard(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_disconnectrfidcard(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif/* GX_ASCII */

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Reads files from the RFID card (Unicode version).
	 *
	 * The application must call the gx_globalfree() function for the data to
	 * free the allocated memory.
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @param data		File contents returned by the card.
	 * @param sdata		Size of the returned data block.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetRfidFile(const wchar_t *card,int fileid,void **data,int *sdata) throw(gxError) {
		bool st = pr_getrfidfile(*this,card,fileid,data,sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Checks the hash of the file read from the RFID card (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CheckRfidFileHash(const wchar_t *card,int fileid) throw(gxError) {
		bool st = pr_checkrfidfilehash(*this,card,fileid)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Reads files from the RFID card (ASCII version).
	 *
	 * The application must call the gx_globalfree() function for the data to
	 * free the allocated memory.
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @param data		File contents returned by the card.
	 * @param sdata		Size of the returned data block.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool GetRfidFile(const char *card,int fileid,void **data,int *sdata) throw(gxError) {
		bool st = pr_getrfidfile(*this,card,fileid,data,sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Checks the hash of the file read from the RFID card (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CheckRfidFileHash(const char *card,int fileid) throw(gxError) {
		bool st = pr_checkrfidfilehash(*this,card,fileid)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)

#ifdef GX_UNICODE
	/** Reads files from the RFID card (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return The files requested.
	 */
	inline gxOutData GetRfidFile(gxInStr card, int fileid) throw(gxError) {
		GX_GETSTRING(_card, card);
		GX_GETHANDLE(h);
		void *data;
		int sdata;
		if(!pr_getrfidfile(h,_card,fileid,&data,&sdata)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData od = GX_PUTDATA(data, sdata);
		if(data) gx_globalfree(data);
		return od;
	}
#endif

#ifdef GX_ASCII
	/** Reads files from the RFID card (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return The files requested.
	 */
	inline gxOutData GetRfidFile(gxInAStr card,int fileid) throw(gxError) {
		GX_GETASTRING(_card, card);
		GX_GETHANDLE(h);
		void *data;
		int sdata;
		if(!pr_getrfidfile(h, _card,fileid,data,sdata)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData od = GX_PUTDATA(data, sdata);
		if(data) gx_globalfree(data);
		return od;
	}
#endif

#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Starts reading files from the RFID card in asynchronous mode. (Unicode version)
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
	 *
	 * @return Id for the getstatus and the wait methods. On error -1 is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() ) */
	inline int GetRfidFileStart(const wchar_t *card, int fileid) throw(gxError) {
		int reqid;
		bool st = pr_getrfidfile_start(*this, card, fileid, &reqid)!=0;
		gxcondthrow(!st);
		return st ? reqid : -1;
	}

	/** Starts reading files from the RFID card in asynchronous mode. (ASCII version)
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
	 *
	 * @return Id for the getstatus and the wait methods. On error -1 is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() ) */
	inline int GetRfidFileStart(const char *card, int fileid) throw(gxError) {
		int reqid;
		bool st = pr_getrfidfile_start(*this, card, fileid, &reqid)!=0;
		gxcondthrow(!st);
		return st ? reqid : -1;
	}

#endif

#ifdef GX_UNICODE
	/** Starts reading files from the RFID card in asynchronous mode. (Unicode version)
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
	 *
	 * @return Id for the getstatus and the wait methods. On error -1 is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() ) */
	inline int GetRfidFileStart(gxInStr card, int fileid) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		int reqid;
		bool st = pr_getrfidfile_start(h,_card,fileid,&reqid)!=0;
		gxcondthrow(!st);
		return st ? reqid : -1;
	}
#endif

#ifdef GX_ASCII
	/** Starts reading files from the RFID card in asynchronous mode. (ASCII version)
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file (see the \ref PR_RFID_FILES enumeration).
	 *
	 * @return Id for the getstatus and the wait methods. On error -1 is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() ) */
	inline int GetRfidFileStart(gxInAStr card, int fileid) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		int reqid;
		bool st = pr_getrfidfile_start(h,_card,fileid,&reqid)!=0;
		gxcondthrow(!st);
		return st ? reqid : -1;
	}
#endif

	/** Returns the state of an rfid reading process started with the GetRfidFileStart() method.
	 *
	 * If an internal event occurred this function calls the Event function.
	 *
	 * @param reqid		Id for the process. The GetRfidFileStart() returned this value.
	 *
	 * @return		The value of the result is in percent.
	 *				On error -1 is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline int GetRfidFileGetStatus(int reqid) throw(gxError) {
		GX_GETHANDLE(h);
		int status;
		bool st = pr_getrfidfile_getstatus(h,reqid,&status)!=0;
		gxcondthrow(!st);
		return st? status : -1;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Waits for the finish of the rfid reading process started with the GetRfidFileStart() method. If
	 * there are internal events waiting for report, this function calls the Event
	 * function.
	 *
	 * @param reqid		Id of the capture returned by the GetRfidFileStart().
	 * @param data		File contents returned by the card.
	 * @param sdata		Size of the returned data block.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool GetRfidFileWait(int reqid, void **data, int *sdata) throw(gxError) {
		bool st = pr_getrfidfile_wait(*this,reqid,data,sdata)!=0;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Waits for the finish of the rfid reading process started with the GetRfidFileStart() method. If
	 * there are internal events waiting for report, this function calls the Event
	 * function.
	 *
	 * @param reqid		Id of the capture returned by the GetRfidFileStart().
	 * @return			The files requested. */
	inline gxOutData  GetRfidFileWait(int reqid) throw(gxError) {
		GX_GETHANDLE(h);
		void *data;
		int sdata;
		if(!pr_getrfidfile_wait(h,reqid,&data,&sdata)){
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData od = GX_PUTDATA(data, sdata);
		if(data) gx_globalfree(data);
		return od;
	}
#endif

	/** Cancel the rfid reading process started with the GetRfidFileStart() method. If
	 * there are internal events waiting for report, this function calls the Event
	 * function.
	 *
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool GetRfidFileStop() throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_getrfidfile_stop(h)!=0;
		gxcondthrow(!st);
		return st;
	}

#ifdef GX_UNICODE
	/** Checks the hash of the file read from the RFID card (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CheckRfidFileHash(gxInStr card, int fileid) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_checkrfidfilehash(h,_card,fileid)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Checks the hash of the file read from the RFID card (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param fileid	Identifier of the requested file. The possible values are
	 *					defined in the \ref PR_RFID_FILES enumeration.
	 * @return On error false is returned and the error code/string in the GX system
	 *			is set appropriately. ( see gx_geterror() )
	 */
	inline bool CheckRfidFileHash(gxInAStr card, int fileid) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_checkrfidfilehash(h,_card,fileid)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Resolves a composite RFID data.
	 *
	 * @param data		Composite RFID data read from the chip.
	 * @param sdata		The size of the data.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 * ( see gx_geterror() )
	 */
	inline prDoc * ResolveRfidData(const void *data, int sdata) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_resolverfiddata(*this,data,sdata,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#else
	/** Resolves a composite RFID data.
	 *
	 * @param data		Composite RFID data read from the chip.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 * ( see gx_geterror() )
	 */
	inline prDoc * ResolveRfidData(gxInData data) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETDATA(data);
		bool st = pr_resolverfiddata(h,GX_DATAPTR(data),GX_DATALEN(data),&doc)!=0;
		GX_FREEDATA(data);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/**  Get applications supported by the card. (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @param apps		Array of supported applications. The possible values are defined
	 *					in the \ref PR_APP_TYPE enumeration.
	 * @param napps		Number of items in the application array.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool GetApplications(const wchar_t *card, int **apps, int *napps) throw(gxError) {
		bool st = pr_getapplications(*this, card, apps, napps)!=0;
		gxcondthrow(!st);
		return st;
	}

	/**  Get applications supported by the card. (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @param apps		Array of supported applications. The possible values are defined
	 *					in the \ref PR_APP_TYPE enumeration.
	 * @param napps		Number of items in the application array.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool GetApplications(const char *card, int **apps, int *napps) throw(gxError) {
		bool st = pr_getapplicationsa(*this, card, apps, napps)!=0;
		gxcondthrow(!st);
		return st;
	}
#else
	/**  Get applications supported by the card. (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		Return with the supported applications. The possible values are defined
	 *				in the \ref PR_APP_TYPE enumeration. On error an empty array is returned
	 *				and the error code/string in the GX system is set appropriately. ( see gx_geterror() ) */
	inline gxOutIntArray GetApplications(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		int apps_len = 0;
		int *apps_ptr = 0;
		gxOutIntArray apps = GX_INTARRAY_NONE;
		bool st = pr_getapplications(h, _card, &apps_ptr, &apps_len)!=0;
		if(apps_ptr && apps_len){
			apps = GX_PUTINTARRAY(apps_ptr, apps_len);
			gx_globalfree(apps_ptr);
		}
		return apps;
	}
#endif


#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Select the chip application. (Unicode version).
	 *
	 * @param card			The id of the RFID card.
	 * @param Application	Type of the application.The possible values are defined in the
	 *						\ref PR_APP_TYPE enumeration.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool SelectApplication(const wchar_t *card, PR_APP_TYPE Application) throw(gxError) {
		bool st = pr_selectapplication(*this,card,Application)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Select the chip application. (ASCII version).
	 *
	 * @param card			The id of the RFID card.
	 * @param Application	Type of the application.The possible values are defined in the
	 *						\ref PR_APP_TYPE enumeration.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool SelectApplication(const char *card, PR_APP_TYPE Application) throw(gxError) {
		bool st = pr_selectapplicationa(*this,card,Application)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_UNICODE

	/**  Select the chip application. (Unicode version).
	 *
	 * @param card			The id of the RFID card.
	 * @param Application	Type of the application.The possible values are defined in the
	 *						\ref PR_APP_TYPE enumeration.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool SelectApplication(gxInStr card, PR_APP_TYPE Application) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_selectapplication(h,_card,Application)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_ASCII

	/**  Select the chip application. (ASCII version).
	 *
	 * @param card			The id of the RFID card.
	 * @param Application	Type of the application.The possible values are defined in the
	 *						\ref PR_APP_TYPE enumeration.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool SelectApplication(gxInAStr card, PR_APP_TYPE Application) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_selectapplication(h,_card,Application)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif


#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Switches to secure messaging by making Basic Access Control (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @param lines		The MRZ lines printed on the MRTD (array of strings).
	 * @param nlines	The number of lines printed on the MRTD.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool MakeBAC(const wchar_t *card, const wchar_t **lines, int nlines) throw(gxError) {
		bool st = pr_makebac(*this,card,lines,nlines)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Switches to secure messaging by making Basic Access Control (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @param lines		The MRZ lines printed on the MRTD (array of strings).
	 * @param nlines	The number of lines printed on the MRTD.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool MakeBAC(const char *card, const char **lines, int nlines) throw(gxError) {
		bool st = pr_makebac(*this,card,lines,nlines)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_UNICODE

	/** Switches to secure messaging by making Basic Access Control (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @param lines		The MRZ lines printed on the MRTD (array of strings).
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool MakeBAC(gxInStr card, gxInStrArray lines) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		GX_GETINSTRARRAY(lines);
		bool st = pr_makebac(h,_card,(const wchar_t**)GX_GETINSTRARRAY_PTR(lines),GX_GETINSTRARRAY_LEN(lines))!=0;
		GX_FREEINSTRARRAY(lines);
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_ASCII

	/** Switches to secure messaging by making Basic Access Control (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @param lines		The MRZ lines printed on the MRTD (array of strings).
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() ) */
	inline bool MakeBAC(gxInAStr card, gxInAStrArray lines) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		GX_GETINASTRARRAY(lines);
		bool st = pr_makebac(h,_card,(const char**)GX_GETINASTRARRAY_PTR(lines),GX_GETINASTRARRAY_LEN(lines))!=0;
		GX_FREEINASTRARRAY(lines);
		gxcondthrow(!st);
		return st;
	}

#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (Unicode version).
	 *
	 * @param card			The id of the RFID card.
	 * @param lines			The MRZ or CAN(Card Access Number) lines printed on the MRTD (array of strings).
	 * @param nlines		The number of lines printed on the MRTD.
	 * @param PasswordType	The type of the password. The possible values are
	 *						defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return				On error false is returned and the error code/string in the GX system
	 *						is set appropriately. ( see gx_geterror() ) */
	inline bool MakePACE(const wchar_t *card, const wchar_t **lines, int nlines, int PasswordType) throw(gxError) {
		bool st = pr_makepace(*this,card,lines,nlines,PasswordType)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (ASCII version).
	 *
	 * @param card			The id of the RFID card.
	 * @param lines			The MRZ or CAN(Card Access Number) lines printed on the MRTD (array of strings).
	 * @param nlines		The number of lines printed on the MRTD.
	 * @param PasswordType	The type of the password. The possible values are
	 *						defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return				On error false is returned and the error code/string in the GX system
	 *						is set appropriately. ( see gx_geterror() ) */
	inline bool MakePACE(const char *card, const char **lines, int nlines, int PasswordType) throw(gxError) {
		bool st = pr_makepace(*this,card,lines,nlines,PasswordType)!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE

	/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (Unicode version).
	 *
	 * @param card			The id of the RFID card.
	 * @param lines			The MRZ or CAN(Card Access Number) lines printed on the MRTD (array of strings).
	 * @param PasswordType	The type of the password. The possible values are
	 *						defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return				On error false is returned and the error code/string in the GX system
	 *						is set appropriately. ( see gx_geterror() ) */
	inline bool MakePACE(gxInStr card, gxInStrArray lines, int PasswordType) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		GX_GETINSTRARRAY(lines);
		bool st = pr_makepace(h,_card,(const wchar_t**)GX_GETINSTRARRAY_PTR(lines),GX_GETINSTRARRAY_LEN(lines),PasswordType)!=0;
		GX_FREEINSTRARRAY(lines);
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII

	/** Switches to secure messaging by making Password Authenticated Connection Establishment (PACE) (ASCII version).
	 *
	 * @param card			The id of the RFID card.
	 * @param lines			The MRZ or CAN(Card Access Number) lines printed on the MRTD (array of strings).
	 * @param PasswordType	The type of the password. The possible values are
	 *						defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return				On error false is returned and the error code/string in the GX system
	 *						is set appropriately. ( see gx_geterror() ) */
	inline bool MakePACE(gxInAStr card, gxInAStrArray lines, int PasswordType) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		GX_GETINASTRARRAY(lines);
		bool st = pr_makepace(h,_card,(const char**)GX_GETINASTRARRAY_PTR(lines),GX_GETINASTRARRAY_LEN(lines),PasswordType)!=0;
		GX_FREEINASTRARRAY(lines);
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Returns the next suggested authentication process (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param ForceNext			Skips the actual authentication.
	 * @return					Next authentication process id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 *							On error -1 is returned and the error code/string in the GX system
	 *							is set appropriately. ( see gx_geterror() )
	 */
	inline int GetNextAuthentication(const wchar_t *card, int ForceNext = false) throw(gxError) {
		int Authentication;
		bool st = pr_getnextauthentication(*this,card,&Authentication,ForceNext)!=0;
		gxcondthrow(!st);
		return st ? Authentication : -1;
	}

	/** Returns the next suggested authentication process (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param ForceNext			Skips the actual authentication.
	 * @return					Next authentication process id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 *							On error -1 is returned and the error code/string in the GX system
	 *							is set appropriately. ( see gx_geterror() )
	 */
	inline int GetNextAuthentication(const char *card, int ForceNext = false) throw(gxError) {
		int Authentication;
		bool st = pr_getnextauthentication(*this,card,&Authentication,ForceNext)!=0;
		gxcondthrow(!st);
		return st ? Authentication : -1;
	}

	/** Making authentication process (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
	 * @param Lines				Number of rows in AuthData.
	 * @param PasswordType		The type of the PACE password. The possible values are
	 *							defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return					On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(const wchar_t *card, int Authentication, const wchar_t **AuthData GX_DEFARG(0), int Lines GX_DEFARG(0), int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) throw(gxError) {
		bool st = pr_doauthentication(*this, card, Authentication, AuthData, Lines, PasswordType)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Making authentication process (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
	 * @param Lines				Number of rows in AuthData.
	 * @param PasswordType		The type of the PACE password. The possible values are
	 *							defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return					On error false is returned and the error code/string in the GX syste
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(const char *card, int Authentication, const char **AuthData GX_DEFARG(0), int Lines GX_DEFARG(0), int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) throw(gxError) {
		bool st = pr_doauthenticationa(*this,card, Authentication, AuthData, Lines, PasswordType)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Passive Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakePassiveAuth(const wchar_t *card) throw(gxError) {
		bool st = pr_makepassiveauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Passive Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakePassiveAuth(const char *card) throw(gxError) {
		bool st = pr_makepassiveauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Active Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 *
	 * \note	Comparation of the MRZ read visually from the MRTD's data page and
	 *			the MRZ value in Data Group 1 is skipped.
	 */
	inline bool MakeActiveAuth(const wchar_t *card) throw(gxError) {
		bool st = pr_makeactiveauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Active Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 *
	 * \note	Comparation of the MRZ read visually from the MRTD's data page and
	 *			the MRZ value in Data Group 1 is skipped.
	 */
	inline bool MakeActiveAuth(const char *card) throw(gxError) {
		bool st = pr_makeactiveauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Chip Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeChipAuth(const wchar_t *card) throw(gxError) {
		bool st = pr_makechipauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Chip Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeChipAuth(const char *card) throw(gxError) {
		bool st = pr_makechipauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeTerminalAuth(const wchar_t *card) throw(gxError) {
		bool st = pr_maketerminalauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeTerminalAuth(const char *card) throw(gxError) {
		bool st = pr_maketerminalauth(*this,card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Initiates the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Data to sign.
	 * @param sdata		Size of the data.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool InitTerminalAuth(const wchar_t *card, void **data, int *sdata) throw(gxError) {
		bool st = pr_initta(*this, card, data, sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Initiates the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Data to sign.
	 * @param sdata		Size of the data.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool InitTerminalAuth(const char *card, void **data, int *sdata) throw(gxError) {
		bool st = pr_initta(*this, card, data, sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Completes the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Signature.
	 * @param sdata		Size of the signature.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool CompleteTerminalAuth(const wchar_t *card, const void *data, int sdata) throw(gxError) {
		bool st = pr_completeta(*this, card, data, sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Completes the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Signature.
	 * @param sdata		Size of the signature.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool CompleteTerminalAuth(const char *card, const void *data, int sdata) throw(gxError) {
		bool st = pr_completeta(*this, card, data, sdata)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads a certificate and a private key from file (Unicode version).
	 *
	 * @param certificate	The name of the certificate file.
	 * @param privateKey	The name of the private key file connected to the certificate. This can be NULL.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFile(const wchar_t *certificate, const wchar_t *privateKey = NULL) throw(gxError) {
		bool st = pr_loadcertfile(*this, certificate, privateKey)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads a certificate and a private key from file (ASCII version).
	 *
	 * @param certificate	The name of the certificate file.
	 * @param privateKey	The name of the private key file connected to the certificate. This can be NULL.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFile(const char *certificate, const char *privateKey = NULL) throw(gxError) {
		bool st = pr_loadcertfile(*this, certificate, privateKey)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads certificates and CRLs from store (Unicode version).
	 *
	 * @param storename	The name of the store.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFromStore(const wchar_t *storename) throw(gxError) {
		bool st = pr_loadcertfromstore(*this, storename)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads certificates and CRLs from store (ASCII version).
	 *
	 * @param storename	The name of the store.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFromStore(const char *storename) throw(gxError) {
		bool st = pr_loadcertfromstore(*this, storename)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads a certificate and a private key from memory.
	 *
	 * @param certificate_data		Pointer to the certificate memory area.
	 * @param certificate_length	Length of certificate_data [byte].
	 * @param privateKey_data		Pointer to the private key memory area. This can be NULL.
	 * @param privateKey_length		Length of privateKey_data [byte]. This can be 0.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFileFromMem(void *certificate_data, unsigned int certificate_length, void *privateKey_data = NULL, unsigned int privateKey_length = 0) throw(gxError) {
		bool st = pr_loadcertfrommem(*this, certificate_data, certificate_length, privateKey_data, privateKey_length)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)
/** Loads a certificate and a private key from memory.
	 *
	 * @param certificate		certificate data.
	 * @param privateKey		private key data. This can be NULL.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFileFromMem(gxInData certificate, gxInData privateKey) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETDATA(certificate);
		bool st;
		if(privateKey!=GX_NULLPTR) {
			GX_GETDATA(privateKey);
			st = pr_loadcertfrommem(h, (void*)GX_DATAPTR(certificate), (unsigned int)GX_DATALEN(certificate), (void*)GX_DATAPTR(privateKey), (unsigned int)GX_DATALEN(privateKey))!=0;
			GX_FREEDATA(privateKey);
		}
		else{
			st = pr_loadcertfrommem(h, (void*)GX_DATAPTR(certificate), (unsigned int)GX_DATALEN(certificate), 0, 0)!=0;
		}

		GX_FREEDATA(certificate);
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_UNICODE

	/** Returns the next suggested authentication process (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param ForceNext			Skips the actual authentication.
	 * @return					Next authentication process id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 *							On error -1 is returned and the error code/string in the GX system
	 *							is set appropriately. ( see gx_geterror() )
	 */
	inline int GetNextAuthentication(gxInStr card, int ForceNext GX_DEFARG(false)) throw(gxError) {
		int Authentication;
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_getnextauthentication(h,_card,&Authentication,ForceNext)!=0;
		gxcondthrow(!st);
		return st ? Authentication : -1;
	}

	/** Making authentication process (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
	 * @param PasswordType		The type of the PACE password. The possible values are
	 *							defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return					On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(gxInStr card, int Authentication, gxInStrArray AuthData, int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		GX_GETINSTRARRAY(AuthData);
		bool st = pr_doauthentication(h, _card, Authentication, (const wchar_t**)GX_GETINSTRARRAY_PTR(AuthData), GX_GETINSTRARRAY_LEN(AuthData), PasswordType)!=0;
		GX_FREEINSTRARRAY(AuthData);
		gxcondthrow(!st);
		return st;
	}

	/** Making authentication process (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @return					On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(gxInStr card, int Authentication) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_doauthentication(h, _card, Authentication, 0, 0, 0)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Passive Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakePassiveAuth(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_makepassiveauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Active Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 *
	 * \note	Comparation of the MRZ read visually from the MRTD's data page and
	 *			the MRZ value in Data Group 1 is skipped.
	 */
	inline bool MakeActiveAuth(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_makeactiveauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Chip Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeChipAuth(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_makechipauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeTerminalAuth(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		bool st = pr_maketerminalauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Initiates the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			Data to sign.
	 */
	inline gxOutData InitTerminalAuth(gxInStr card) throw(gxError) {
		GX_GETSTRING(_card, card);
		GX_GETHANDLE(h);
		void *data;
		int sdata;
		if(!pr_initta(h, _card, &data, &sdata)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData od = GX_PUTDATA(data, sdata);
		if(data) gx_globalfree(data);
		return od;
	}

	/** Completes the Terminal Authentication of the RFID chip (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Signature.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool CompleteTerminalAuth(gxInStr card, gxInData data) throw(gxError) {
		GX_GETSTRING(_card, card);
		GX_GETHANDLE(h);
		GX_GETDATA(data);
		bool st = pr_completeta(h, _card, GX_DATAPTR(data), GX_DATALEN(data))!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Loads a certificate and a private key from file (Unicode version).
	 *
	 * @param certificate	The name of the certificate file.
	 * @param privateKey	The name of the private key file connected to the certificate. This can be NULL.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFile(gxInStr certificate, gxInStr privateKey /*GX_DEFARG("")*/) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_certificate, certificate);
		GX_GETSTRING(_privateKey, privateKey);
		bool st = pr_loadcertfile(h,_certificate,_privateKey)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads certificates and CRLs from store (Unicode version).
	 *
	 * @param storename	The name of the store.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFromStore(gxInStr storename) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_storename, storename);
		bool st = pr_loadcertfromstore(h,_storename)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif

#ifdef GX_ASCII

	/** Returns the next suggested authentication process (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param ForceNext			Skips the actual authentication.
	 * @return					Next authentication process id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 *							On error -1 is returned and the error code/string in the GX system
	 *							is set appropriately. ( see gx_geterror() )
	 */
	inline int GetNextAuthentication(gxInAStr card, int ForceNext GX_DEFARG(false)) throw(gxError) {
		int Authentication;
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_getnextauthentication(h,_card,&Authentication,ForceNext)!=0;
		gxcondthrow(!st);
		return st ? Authentication : -1;
	}

	/** Making authentication process (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @param AuthData			MRZ,PIN,CAN data for BAC and PACE authentications.
	 * @param PasswordType		The type of the PACE password. The possible values are
	 *							defined in the \ref PR_PACE_PASSWORD enumeration.
	 * @return					On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(gxInAStr card, int Authentication, gxInAStrArray AuthData, int PasswordType GX_DEFARG(PR_PACE_PW_MRZ)) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		GX_GETINASTRARRAY(AuthData);
		bool st = pr_doauthenticationa(h, _card, Authentication, (const char **)GX_GETINASTRARRAY_PTR(AuthData), GX_GETINASTRARRAY_LEN(AuthData), PasswordType)!=0;
		GX_FREEINASTRARRAY(AuthData);
		gxcondthrow(!st);
		return st;
	}

	/** Making authentication process (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication process id. The possible values are defined in the
	 *							\ref PR_AUTH_PROC enumeration.
	 * @return					On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	inline int DoAuthentication(gxInAStr card, int Authentication) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_doauthenticationa(h, _card, Authentication, 0, 0, 0)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Passive Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakePassiveAuth(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_makepassiveauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Active Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 *
	 * \note	Comparation of the MRZ read visually from the MRTD's data page and
	 *			the MRZ value in Data Group 1 is skipped.
	 */
	inline bool MakeActiveAuth(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_makeactiveauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Chip Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeChipAuth(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_makechipauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Makes the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		The id of the RFID card.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool MakeTerminalAuth(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		bool st = pr_maketerminalauth(h,_card)!=0;
		gxcondthrow(!st);
		return st;
	}

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Initiates the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			Data to sign.
	 */
	inline gxOutData InitTerminalAuth(gxInAStr card) throw(gxError) {
		GX_GETASTRING(_card, card);
		GX_GETHANDLE(h);
		void *data;
		int sdata;
		if(!pr_initta(h, _card, &data, &sdata)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData od = GX_PUTDATA(data, sdata);
		if(data) gx_globalfree(data);
		return od;
	}

	/** Completes the Terminal Authentication of the RFID chip (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @param data		Signature.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool CompleteTerminalAuth(gxInAStr card, gxInData data) throw(gxError) {
		GX_GETASTRING(_card, card);
		GX_GETHANDLE(h);
		GX_GETDATA(data);
		bool st = pr_completeta(h, _card, GX_DATAPTR(data), GX_DATALEN(data))!=0;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Loads a certificate and a private key from file (ASCII version).
	 *
	 * @param certificate	The name of the certificate file.
	 * @param privateKey	The name of the private key file connected to the certificate. This can be NULL.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFile(gxInAStr certificate, gxInAStr privateKey /*GX_DEFARG("")*/) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_certificate, certificate);
		GX_GETASTRING(_privateKey, privateKey);
		bool st = pr_loadcertfile(h,_certificate,_privateKey)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Loads certificates and CRLs from store (ASCII version).
	 *
	 * @param storename	The name of the store.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool LoadCertFromStore(gxInAStr storename) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_storename, storename);
		bool st = pr_loadcertfromstore(h,_storename)!=0;
		gxcondthrow(!st);
		return st;
	}

#endif/* GX_ASCII */

	/** Clears the internal certificate list.
	 * @param sel	List selector. Set 0 to clear all the certificate lists, set to 1 to clear PA certificate
	 *				list, set to 2 to clear TA certificate list.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately. ( see gx_geterror() )
	 */
	inline bool ClearCertList(int sel) throw(gxError) {
		GX_GETHANDLE(h);
		bool st = pr_clearcertlist(h, sel)!=0;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)

	/** Returns information about the rfid card (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			The Rfid card info in variant data type.
	 */
	inline gxVariant * GetRfidCardInfo(const wchar_t *card) throw(gxError) {
		gxVARIANT cardinfo;
		bool st = pr_getrfidcardinfo(*this,card,&cardinfo)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!cardinfo) return 0;
		gxVariant * vr = new gxVariant(cardinfo);
		gx_unrefvariant(cardinfo);
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns information about the rfid card (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			The Rfid card info in variant data type.
	 */
	inline gxVariant * GetRfidCardInfo(const char *card) throw(gxError) {
		gxVARIANT cardinfo;
		bool st = pr_getrfidcardinfo(*this,card,&cardinfo)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!cardinfo) return 0;
		gxVariant * vr = new gxVariant(cardinfo);
		gx_unrefvariant(cardinfo);
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns information about the necessary certificate (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 * @return					The certificate Id info in variant data type.
	 */
	inline gxVariant* GetCertificateId(const char *card, int Authentication) throw(gxError) {
		gxVARIANT Id;
		bool st = pr_getcertificateid(*this,card,Authentication,&Id)!= 0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!Id) return 0;
		gxVariant *variant = new gxVariant(Id);
		gx_unrefvariant(Id);
		if(!variant){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return variant;
	}

	/** Returns information about the necessary certificate (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 * @return					The certificate Id info in variant data type.
	 */
	inline gxVariant* GetCertificateId(const wchar_t *card, int Authentication) throw(gxError) {
		gxVARIANT Id;
		bool st = pr_getcertificateid(*this,card,Authentication,&Id)!= 0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!Id) return 0;
		gxVariant *variant = new gxVariant(Id);
		gx_unrefvariant(Id);
		if(!variant){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return variant;
	}

#endif

#ifdef GX_UNICODE

	/** Returns information about the rfid card (Unicode version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			The Rfid card info in variant data type.
	 */
	inline gxVariant * GetRfidCardInfo(gxInStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		gxVARIANT cardinfo;
		bool st = pr_getrfidcardinfo(h,_card,&cardinfo)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!cardinfo) return 0;
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(cardinfo);
			gx_unrefvariant(cardinfo);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(cardinfo);
		#endif
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns information about the necessary certificate (Unicode version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 * @return					The certificate Id info in variant data type.
	 */
	inline gxVariant* GetCertificateId(gxInStr card, int Authentication) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_card, card);
		gxVARIANT Id;
		bool st = pr_getcertificateid(h,_card,Authentication,&Id)!= 0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!Id) return 0;
		#ifndef GX_DOTNET
			gxVariant *variant = new gxVariant(Id);
			gx_unrefvariant(Id);
		#else
			gxVariant *variant = new gxVariant();
			variant->_set_variant(Id);
		#endif
		if(!variant){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return variant;
	}


#endif

#ifdef GX_ASCII

	/** Returns information about the rfid card (ASCII version).
	 *
	 * @param card		Serial number of the selected card.
	 * @return			The Rfid card info in variant data type.
	 */
	inline gxVariant * GetRfidCardInfo(gxInAStr card) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		gxVARIANT cardinfo;
		bool st = pr_getrfidcardinfo(h,_card,&cardinfo)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!cardinfo) return 0;
		gxVariant * vr = new gxVariant(cardinfo);
		gx_unrefvariant(cardinfo);
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}

	/** Returns information about the necessary certificate (ASCII version).
	 *
	 * @param card				Serial number of the selected card.
	 * @param Authentication	Authentication Id. The possible values are defined in the \ref PR_AUTH_PROC enumeration.
	 * @return					The certificate Id info in variant data type.
	 */
	inline gxVariant* GetCertificateId(gxInAStr card, int Authentication) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETASTRING(_card, card);
		gxVARIANT Id=0;
		bool st = pr_getcertificateid(h,_card,Authentication,&Id)!= 0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!Id) return 0;
		gxVariant *variant = new gxVariant(Id);
		gx_unrefvariant(Id);
		if(!variant){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return variant;
	}

#endif

	/** Compares a captured face photo with one that is stored in rfid chip.
	 *
	 * The application must call ResolveRfidData() function first.
	 *
	 * @param page		The actual page of the image.
	 * @param face_no	The ordinal number of the face image in rfid data.
	 * @return	A prDoc object contains the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set appropriately.
	 *			( see gx_geterror() )
	 */
	inline prDoc * CompareFace(int page, int face_no) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_compareface(h,page,face_no,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Decodes a latent image from a stored image.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 * 					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 * 					the \ref PR_IMAGE_TYPE enumeration.
	 * @param decpar	Decoding parameter.
	 * @return		The latent image.
	 */
	inline gxVariant * DecodeLatentImage(int page, int light, int type, const wchar_t *decpar) throw(gxError) {
		gxVARIANT image;
		bool st = pr_decodelatentimage(*this, page, light, type, decpar, &image)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!image) return 0;
		gxVariant * vr = new gxVariant(image);
		gx_unrefvariant(image);
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}
#endif

#ifdef GX_UNICODE
	/** Decodes a latent image from a stored image.
	 *
	 * @param page		The actual page of the image.
	 * @param light		The light settings. The possible values are defined in the
	 * 					\ref PR_LIGHT enumeration.
	 * @param type		The type of the image. The possible values are defined in
	 * 					the \ref PR_IMAGE_TYPE enumeration.
	 * @param decpar	Decoding parameter.
	 * @return		The latent image.
	 */
	inline gxVariant * DecodeLatentImage(int page, int light, int type, gxInStr decpar) throw(gxError) {
		GX_GETHANDLE(h);
		GX_GETSTRING(_decpar, decpar);
		gxVARIANT image;
		bool st = pr_decodelatentimage(h, page, light, type, _decpar, &image)!=0;
		gxcondthrow(!st);
		if(st) gxSystem::ClearError();
		if(!image) return 0;
		#ifndef GX_DOTNET
			gxVariant * vr = new gxVariant(image);
			gx_unrefvariant(image);
		#else
			gxVariant * vr = new gxVariant();
			vr->_set_variant(image);
		#endif
		if(!vr){gxSystem::SetError(GXEC GX_ENOMEM);gxthrow;}
		return vr;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Loads a document from the mass storage device (Unicode version).
	 *
	 * @param filename	Name of the file to load the document from.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocument(const wchar_t *filename) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_loaddocument(*this,filename,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Loads a document from the mass storage device (ASCII version).
	 *
	 * @param filename	Name of the file to load the document from.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocument(const char *filename) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_loaddocument(*this,filename,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

	/** Loads a document from the memory.
	 *
	 * @param buffer	Pointer to the data.
	 * @param buflen	Length of data in bytes.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocumentFromMem(const gxu8 *buffer, gxi32 buflen) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		if(!pr_loaddocumentfrommem(*this, buffer, buflen, &doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,*this);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}

#endif/* GX_SWIG GX_DOTNET */

#ifdef GX_UNICODE
	/** Loads a document from the mass storage device (Unicode version).
	 *
	 * @param filename	Name of the file to load the document from.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocument(gxInStr filename) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETSTRING(_filename, filename);
		if(!pr_loaddocument(h,_filename,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/* GX_UNICODE */

#ifdef GX_ASCII
	/** Loads a document from the mass storage device (ASCII version).
	 *
	 * @param filename	Name of the file to load the document from.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocument(gxInAStr filename) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETASTRING(_filename, filename);
		if(!pr_loaddocument(h,_filename,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif/* GX_ASCII */

#if defined(GX_SWIG) || defined(GX_DOTNET)
	/** Loads a document from the memory.
	 *
	 * @param buffer	Pointer to the data.
	 * @return	A prDoc object containing the data of the document. On error an empty
	 *			object is returned and the error code/string in the GX system is set
	 *			appropriately. ( see gx_geterror() )
	 */
	inline prDoc * LoadDocumentFromMem(gxInData buffer) throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		GX_GETDATA(buffer);
		bool st = pr_loaddocumentfrommem(h, (const gxu8*)GX_DATAPTR(buffer), GX_DATALEN(buffer), &doc)!=0;
		GX_FREEDATA(buffer);
		if(!st) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc, h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	}
#endif

	/** Returns the root document of the PR system.
	 *
	 * @return  On error false is returned and the error code/string in the GX system
	 * is set appropriately. ( see gx_geterror() )
	 */
	 inline prDoc * GetDocumentRoot() throw(gxError) {
		gxVARIANT doc = 0;
		prDoc *cdoc = 0;
		GX_GETHANDLE(h);
		if(!pr_getdocumentroot(h,&doc)) {
			gxthrow;
			return cdoc;
		}
		ifDoc cdoc = new prDoc(doc,h);
		if(doc) gx_unrefvariant(doc);
		ifDoc if(!cdoc){gxSystem::SetError(GX_ENOMEM);gxthrow;}
		if(!doc) gxSystem::ClearError();
		return cdoc;
	 }
};

#ifndef GX_MANUAL
	#undef ifDoc
#endif

/******************************************************************************/
#endif/* NO_GX_CLASSES )*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
#ifdef _MSC_VER
	#pragma warning(pop)
#endif
/******************************************************************************/
#endif/* PRAPI_INCL */
