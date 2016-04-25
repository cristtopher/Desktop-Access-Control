/*******************************************************************************
 * GXSD header file - V7.2.10.0
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \mainpage GX
 *
 * \section gx_sec_sdk The GX SDK
 *
 * \anchor gx_progman
 *
 * The \c GX is the base system for the majority of the <b>ARH Inc.</b> products.
 * It is a collection of loadable modules and library
 * functions and gives an ease to program interface to the hardware devices.
 *
 * The currently supported programming languages and the usable interfaces are the
 * following: C, C++; Java (\c jgx.jar); VB.Net, C# (\c gxdotnet8.dll);
 * VBasic 6, Delphi (\c gximage.ocx, \c gxlabel.ocx, \c gxmotdet.ocx, \c gxvariant.ocx).
 *
 * \if C
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the GX system.
 *		It contains the description of definitions, enumerations and functions for the ANSI C programming language.
 * \elseif CPP
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the GX system.
 *		It contains the description of definitions, enumerations, functions and classes for the C++ programming language.
 * \elseif NET
 *		This documentation gives a detailed description of the \c Application \c Programming \c Interface (\c API) of the GX system.
 *		It contains the description of enumerations and classes for the .NET framework.
 * \endif
 *
 * \if CPP
 * \subsection gx_sec_sdk_general_GX_NAMESPACES The GX_NAMESPACES global define
 * \anchor GX_NAMESPACES
 *
 * The \c GX_NAMESPACES define enables the usage of GX system namespaces.
 * If it is globally defined the \c gx namespace is created and the GX system functions
 * and classes are added to this namespace. For the functions and classes of other systems based
 * on the GX system separate namespaces are defined.
 *
 * If this define is not set, then the GX system and the dependent systems do not use namespaces.
 * This does not forbit the usage of other namespaces just places the GX system and dependent
 * system functions in the global namespace.
 * \endif
 *
 * Next browse the groups list, check the \ref gxsd.h or check the
 * Change Log in the reference manual for differences against the previous versions.
 */
/******************************************************************************/
/** \defgroup gx_group_device Device handling
 *
 * Functions for device handling.
 */

/** \defgroup gx_group_module Module handling
 *
 * Functions for module handling.
 */

/** \defgroup gx_group_zlib Compression handling
 *
 * Functions for compression handling.
 */

/** \defgroup gx_group_image Image handling
 *
 * Functions for image handling.
 */

/** \defgroup gx_group_log Logging
 *
 * Functions for logging.
 */

/** \defgroup gx_group_motdet Motion detection
 *
 * Functions for motion detection.
 */

/** \defgroup gx_group_property Property handling
 *
 * Functions for property handling.
 */

/** \defgroup gx_group_trafo Transformations handling
 *
 * Functions for transformations handling.
 */

/** \defgroup gx_group_watchdog Watchdog handling
 *
 * Functions for watchdog handling.
 */

/** \defgroup gx_group_reference Reference handling
 *
 * Functions for reference handling.
 */

/** \defgroup gx_group_error Error handling
 *
 * Functions for error handling.
 */

/** \defgroup gx_group_memory Memory handling
 *
 * Functions for memory handling.
 */

/** \defgroup gx_group_variant Variants handling
 *
 * Functions for variants handling.
 */

/******************************************************************************/
/** \file
 * <b> Module handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an ease to program
 * interface to the hardware devices.
 *
 * The specific product functionalities are built in specific GX modules, that
 * can be accessed through the \c gxsd. Apart from the module handling functions
 * the gxsd module contains general functions like property, memory and image
 * handling functions, as well.
 *
 * This file contains the descriptions of classes and functions of the module handling module.
 *
 */
/******************************************************************************/
#ifndef GXSD_INCL
#define GXSD_INCL
/******************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "gxtypes.h"
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/******************************************************************************/
#if !defined(gx_strncpy)
	/* Visual Studio 8 workaround */
	#if _MSC_VER >= 1400

		inline int gx_snwprintf(wchar_t *buffer, size_t count, const wchar_t *format, ...) {
			int r;
			va_list args;
			va_start(args, format);
			r = _vsnwprintf_s(buffer,count,_TRUNCATE,format, args);
			va_end(args);
			return r;
		}

		inline int gx_snprintf(char *buffer, size_t count, const char *format, ...)	{
			int r;
			va_list args;
			va_start(args, format);
			r = _vsnprintf_s(buffer,count,_TRUNCATE,format,args);
			va_end(args);
			return r;
		}
		#define gx_strncpy(strDest,strSource,count)	strncpy_s(strDest,count,strSource,_TRUNCATE)
		#define gx_wcsncpy(strDest,strSource,count)	wcsncpy_s(strDest,count,strSource,_TRUNCATE)

		#define gx_strncat(strDest,strSource,count)	strncat_s(strDest,strlen(strDest)+count+1,strSource,_TRUNCATE)
		#define gx_wcsncat(strDest,strSource,count)	wcsncat_s(strDest,wcslen(strDest)+count+1,strSource,_TRUNCATE)

		inline size_t gx_wcstombs(char *mbstr, const wchar_t *wcstr, size_t count) {
			size_t pConvertedChars = 0;
			wcstombs_s(&pConvertedChars,mbstr,count,wcstr,_TRUNCATE);
			return pConvertedChars;
		}
		inline size_t gx_mbstowcs(wchar_t *wcstr, const char *mbstr, size_t count) {
			size_t pConvertedChars = 0;
			mbstowcs_s(&pConvertedChars,wcstr,count,mbstr,_TRUNCATE);
			return pConvertedChars;
		}

		#define gx_strdup							_strdup
		#define gx_wcsdup							_wcsdup
		#define gx_wcstol							wcstol

		#if defined(__INTEL_COMPILER) && !defined(_M_X64)
			#define __ptr32
		#endif

	#elif defined(WIN32)

		#define gx_snwprintf	_snwprintf
		#define gx_snprintf		_snprintf
		#define gx_strncpy		strncpy
		#define gx_strncat		strncat
		#define gx_wcsncat		wcsncat
		#define gx_wcsncpy		wcsncpy
		#define gx_wcstombs		wcstombs
		#define gx_mbstowcs		mbstowcs
		#define gx_strdup		_strdup
		#define gx_wcsdup		_wcsdup
		#define gx_wcstol		wcstol

		#define __ptr32

	#else //LINUX

		#ifdef ANDROID
		#include "unicode/ConvertUTF.h"
		#include "androidlog.h"
			inline wchar_t *wcsdup(const wchar_t *st)
			{
				if (!st) return NULL;
				wchar_t *pst = (wchar_t *)malloc((wcslen(st)+1)*sizeof(wchar_t));
				if (pst) wcscpy(pst,st);
				return pst;
			}
			inline size_t gx_wcstombs(char *mbstr,const wchar_t *wcstr,size_t count)
			{
				if (!mbstr || !wcstr || !count) return 0;
				size_t l = wcslen(wcstr);
				if (l > count) l = count;
				memset((void*)mbstr,0,count);
				//if (ConvertUTF16toUTF8((const UTF16**)&wcstr,(const UTF16*)(wcstr+wcslen(wcstr)-1),(UTF8**)&mbstr,(UTF8*)(mbstr+count-2),strictConversion) == conversionOK) return l;
				for(int i=0;i<l;i++)
				{
					if (wcstr[i] > 255) mbstr[i]='.';
					else mbstr[i] = (char)(wcstr[i] & 0xff);
				}
				return l;
			}
			inline size_t gx_mbstowcs(wchar_t *wcstr,const char *mbstr,size_t count)
			{
				if (!mbstr || !wcstr || !count) return 0;
				size_t l = strlen(mbstr);
				if (l > count) l = count;
				memset((void*)wcstr,0,count*sizeof(wchar_t));
				//if (ConvertUTF8toUTF16((const UTF8**)&mbstr,(const UTF8*)(mbstr+strlen(mbstr)-1),(UTF16**)&wcstr,(UTF16*)(wcstr+count-2),strictConversion) == conversionOK) return l;
				for(int i=0;i<l;i++)
				{
					wcstr[i] = (wchar_t)mbstr[i];
				}
				return l;
			}
			inline long int gx_wcstol(const wchar_t *wcstr, wchar_t **endptr, int base)
			{
			size_t s = (wcslen(wcstr)+1)*sizeof(char);
			char *pch = (char*)malloc(s);
			char *ep = 0;
			long int ret = 0;
				if (!pch) return 0;
				gx_wcstombs(pch,wcstr,s);
				ret = strtol(pch,&ep,base);
				if (endptr) *endptr = (wchar_t*)wcstr + (int)(ep-pch);
				free(pch);
				return ret;
			}
		#else
		#define gx_wcstombs		wcstombs
		#define gx_mbstowcs		mbstowcs
		#define gx_wcstol		wcstol
		#endif

		#define gx_snwprintf	swprintf
		#define gx_wcsncpy		wcsncpy
		#define gx_wcsncat		wcsncat
		#define gx_wcsdup		wcsdup
		#define gx_snprintf		snprintf
		#define gx_strncpy		strncpy
		#define gx_strncat		strncat
		#define gx_strdup		strdup
	#endif
#endif
/******************************************************************************/
#if defined(WIN32) && !defined(va_copy)
	#define va_copy(ap,v) (ap=(v))
#endif
#if defined(LINUX) && !defined(va_copy)
	#define va_copy	__va_copy
#endif
#include "gxerror.h"
#include "gxlibsd.h"
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -rch
#endif
#ifdef _MSC_VER
	#pragma warning(disable : 4127)		/* truncated debug info */
#endif
/******************************************************************************/
#endif /* GX_SWIGIF GX_MANUAL )*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
	#ifdef GX_DOTNET
		/* Unmanaged code for .net */
		#pragma unmanaged
	#endif
#endif
/******************************************************************************/
#ifndef GX_MANUAL
/* .NET workarounds */
#ifdef GX_DOTNET
	#define _GX_ERR_FLAG_CLEAR		0
	#define _GX_ERR_FLAG_APPEND		1
	#define _GX_ERR_FLAG_PREPEND	2
#else
	#define _GX_ERR_FLAG_CLEAR		GX_ERR_FLAG_CLEAR
	#define _GX_ERR_FLAG_APPEND		GX_ERR_FLAG_APPEND
	#define _GX_ERR_FLAG_PREPEND	GX_ERR_FLAG_PREPEND
#endif
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/******************************************************************************
 * Call groups and codes in the GX system.
 ******************************************************************************/
/** Enumerations for group codes. */
enum GX_CALL_GROUP_CODES {
/*******************************************************************************
 * GXSD groups
 ******************************************************************************/
	GX_CALL_GROUP_API			=	0x10000000,		/**< First code of the GX-API */
	GX_CALL_GROUP_API_FIRST		=	0x10000000,		/**< First code of the GX-API */
	GX_CALL_GROUP_API_LAST		=	0x10FFFFFF,		/**< Last code of the GX-API */

	GX_CALL_GROUP_ERROR			=	0x10010000,		/**< First code of the error group */
	GX_CALL_GROUP_MEMORY		=	0x10020000,		/**< First code of the memory group */
	GX_CALL_GROUP_MODULE		=	0x10030000,		/**< First code of the module group */
	GX_CALL_GROUP_VARIANT		=	0x10040000,		/**< First code of the variant group */

/*******************************************************************************
 * GX LICENCE operations
 ******************************************************************************/
	GX_CALL_GROUP_LICENCE		=	0x10900000,		/**< First code of the licence group */

/*******************************************************************************
 * GX DEVICE operations
 ******************************************************************************/
	GX_CALL_GROUP_GX_DEVICE		=	0x10FF0000,		/**< First code of the device module */

/*******************************************************************************
 * GX MODULES (gxImage, gxTrafo, ..)
 ******************************************************************************/
	GX_CALL_GROUP_GX			=	0x11000000,		/**< First code of the GX core */
	GX_CALL_GROUP_GX_FIRST		=	0x11000000,		/**< First code of the GX core */
	GX_CALL_GROUP_GX_LAST		=	0x1FFFFFFF,		/**< Last code of the GX core */

	GX_CALL_GROUP_GX_PROPERTY	=	0x11000000,		/**< First code of the property module */
	GX_CALL_GROUP_GX_LOG		=	0x11010000,		/**< First code of the log module */
	GX_CALL_GROUP_GX_STREAM		=	0x11020000,		/**< First code of the stream module */
	GX_CALL_GROUP_GX_TRAFO		=	0x11030000,		/**< First code of the trafo module */
	GX_CALL_GROUP_GX_IMAGE		=	0x11040000,		/**< First code of the image module */
	GX_CALL_GROUP_GX_BMP		=	0x11050000,		/**< First code of the BMP module */
	GX_CALL_GROUP_GX_JPEG		=	0x11060000,		/**< First code of the JPEG module */
	GX_CALL_GROUP_GX_WATCHDOG	=	0x11070000,		/**< First code of the watchdog module */
	GX_CALL_GROUP_GX_MOTDET		=	0x11080000,		/**< First code of the motion detector module */
	GX_CALL_GROUP_GX_JPEG2K		=	0x11090000,		/**< First code of the JPEG-2000 module */
	GX_CALL_GROUP_GX_ZLIB		=	0x110A0000,		/**< First code of the ZLIB module */
	GX_CALL_GROUP_GX_PNG 		=	0x110B0000,		/**< First code of the PNG module */
	GX_CALL_GROUP_GX_IMGEXT		=	0x110C0000,		/**< First code of the image extension module */
	GX_CALL_GROUP_GX_TEST		=	0x110D0000,		/**< First code of the test module */
	GX_CALL_GROUP_GX_PROPFILE	=	0x110E0000,		/**< First code of the property file module */
	GX_CALL_GROUP_GX_PROPCLIENT	=	0x110F0000,		/**< First code of the property client module */
	GX_CALL_GROUP_GX_JPEG8		=	0x11100000,		/**< First code of the JPEG-8 module */
	GX_CALL_GROUP_GX_JPEG12		=	0x11110000,		/**< First code of the JPEG-12 module */
	GX_CALL_GROUP_GX_CRYPTO		=	0x11120000,		/**< First code of the CRYPTO module */
	GX_CALL_GROUP_GX_WSQ		=	0x11130000,		/**< First code of the WSQ module */
	GX_CALL_GROUP_GX_VIDEO		=	0x11140000,		/**< First code of the VIDEO module */
	GX_CALL_GROUP_GX_LLJE		=	0x11150000,		/**< First code of the Lossless JPEG Edit module*/

/*******************************************************************************
 * ARH MODULES (Anpr, Fxvd4, Face Ident, Passport Reader)
 ******************************************************************************/
	GX_CALL_GROUP_OTHER			=	0x20000000,		/**< First code of other ARH modules */
	GX_CALL_GROUP_OTHER_FIRST	=	0x20000000,		/**< First code of other ARH modules */
	GX_CALL_GROUP_OTHER_LAST	=	0xEFFFFFFF,		/**< Last code of other ARH modules */

/*******************************************************************************
 * USER MODULES
 ******************************************************************************/
	GX_CALL_GROUP_USER			=	0xF0000000,		/**< First code of all user modules */
	GX_CALL_GROUP_USER_FIRST	=	0xF0000000,		/**< First code of all user modules */
	GX_CALL_GROUP_USER_LAST		=	0xFFFFFFFF		/**< Last code of all user modules */
};

/*******************************************************************************
 * GX call codes
 ******************************************************************************/

/** Enumerations for functions for default modules. */
enum GX_CALL_DEFMODULE_CODES {

	GX_CALL_SENDCOMPVERSION			= GX_CALL_GROUP_API | 0x000F,		/**< The application can specify the requested (compiled) version for the GX */
	GX_CALL_LISTMODULES				= GX_CALL_GROUP_API | 0x0010,
	GX_CALL_LISTMODULESA			= GX_CALL_GROUP_API | 0x0011,
};

/** Current version of the GX system. */
#define GX_CURRENT_VERSION	0x07020A01

/** Enumerations for functions for the module handle. */
enum GX_CALL_MODULE_CODES {
	GX_CALL_OPENMODULE				= GX_CALL_GROUP_MODULE	| 0x0000,	/**< Call code for the gx_openmodule() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_OPENMODULEA				= GX_CALL_GROUP_MODULE	| 0x0001,	/**< Call code for the gx_openmodule() function (ASCII version). */
#endif
	GX_CALL_CLOSEHANDLE				= GX_CALL_GROUP_MODULE	| 0x0002,	/**< Call code for the gx_closehandle() function. */
	GX_CALL_GETMODULEINFO			= GX_CALL_GROUP_MODULE	| 0x0004,	/**< Call code for the gx_getmoduleinfo() function. */
	GX_CALL_RESERVED				= GX_CALL_GROUP_MODULE	| 0x0005,	/**< Reserved, do not use. */

	GX_CALL_REFHANDLE				= GX_CALL_GROUP_MODULE	| 0x0006,	/**< Call code for the gx_refhandle() function. */
	GX_CALL_UNREFHANDLE				= GX_CALL_GROUP_MODULE	| 0x0007,	/**< Call code for the gx_unrefhandle() function. */

	GX_CALL_GETMODULEPROPERTY		= GX_CALL_GROUP_MODULE	| 0x0008,	/**< Call code for the gx_getmoduleproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETMODULEPROPERTYA		= GX_CALL_GROUP_MODULE	| 0x0009,	/**< Call code for the gx_getmoduleproperty() function (ASCII version). */
#endif
	GX_CALL_SETMODULEPROPERTY		= GX_CALL_GROUP_MODULE	| 0x000A,	/**< Call code for the gx_setmoduleproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETMODULEPROPERTYA		= GX_CALL_GROUP_MODULE	| 0x000B,	/**< Call code for the gx_setmoduleproperty() function (ASCII version). */
#endif
	GX_CALL_SAVEMODULEPROPERTIESOLD	= GX_CALL_GROUP_MODULE	| 0x000C,	/**< Deprecated. */
#ifndef ANDROID
	GX_CALL_SAVEMODULEPROPERTIESOLDA= GX_CALL_GROUP_MODULE	| 0x000D,	/**< Deprecated. */
#endif
	GX_CALL_SAVEMODULEPROPERTIES	= GX_CALL_GROUP_MODULE	| 0x000E,	/**< Call code for the gx_savemoduleproperties() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_SAVEMODULEPROPERTIESA	= GX_CALL_GROUP_MODULE	| 0x000F, 	/**< Call code for the gx_savemoduleproperties() function (ASCII version). */
#endif
	GX_CALL_MPSTARTTRANSACTION		= GX_CALL_GROUP_MODULE	| 0x0010,	/**< Call code for the gx_mpstarttransaction() function. */
	GX_CALL_MPCOMMIT				= GX_CALL_GROUP_MODULE	| 0x0011,	/**< Call code for the gx_mpcommit() function. */
};

/** Enumerations for error management. */
enum GX_CALL_ERROR_CODES {
	GX_CALL_GETERROR				= GX_CALL_GROUP_ERROR	| 0x0000,	/**< Call code for the gx_geterror() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETERRORA				= GX_CALL_GROUP_ERROR	| 0x0001,	/**< Call code for the gx_geterror() function (ASCII version). */
#endif
	GX_CALL_SETERROR				= GX_CALL_GROUP_ERROR	| 0x0002,	/**< Call code for the gx_seterror() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETERRORA				= GX_CALL_GROUP_ERROR	| 0x0003,	/**< Call code for the gx_seterror() function (ASCII version). */
#endif
	GX_CALL_PUSHERROR				= GX_CALL_GROUP_ERROR	| 0x0004,	/**< Call code for the gx_pusherror() function. */
	GX_CALL_POPERROR				= GX_CALL_GROUP_ERROR	| 0x0005,	/**< Call code for the gx_poperrro() function. */
	GX_CALL_UPDATEERRTABLE			= GX_CALL_GROUP_ERROR	| 0x000F 	/**< Call code for the gx_updateerrtable() function. */
};

/** Enumerations for memory operations. */
enum GX_CALL_MEMORY_CODES {
	GX_CALL_GLOBALREALLOC			= GX_CALL_GROUP_MEMORY	| 0x0000,	/**< Call code for the gx_globalrealloc() function. */
	GX_CALL_GLOBALSIZE				= GX_CALL_GROUP_MEMORY	| 0x0001,	/**< Call code for the gx_globalsize() function. */
	GX_CALL_GLOBALREALLOC_DBG		= GX_CALL_GROUP_MEMORY	| 0x0002,	/**< Call code for the gx_globalrealloc_dbg() function. */
	GX_CALL_GLOBALCHECK_DBG			= GX_CALL_GROUP_MEMORY	| 0x0003,	/**< Call code for the gx_globalcheck_dbg() function. */
	GX_CALL_GLOBALTESTMEM_DBG		= GX_CALL_GROUP_MEMORY	| 0x0004,	/**< Call code for the gx_globaltestmem_dbg() function. */
	GX_CALL_CREATEMEMSLOT			= GX_CALL_GROUP_MEMORY	| 0x0005,	/**< Call code for the gx_creatememslot() function. */
	GX_CALL_GETMEMSLOT				= GX_CALL_GROUP_MEMORY	| 0x0006,	/**< Call code for the gx_getmemslot() function. */
	GX_CALL_UNREFMEMSLOT			= GX_CALL_GROUP_MEMORY	| 0x0007,	/**< Call code for the gx_unrefmemslot() function. */
};

/** Enumerations for device operations. */
enum GX_CALL_DEVICE_CODES {
	GX_CALL_LISTDEVICES				= GX_CALL_GROUP_GX_DEVICE | 0x0000,	/**< Call code for the gx_listdevices() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_LISTDEVICESA			= GX_CALL_GROUP_GX_DEVICE | 0x0001,	/**< Call code for the gx_listdevices() function (ASCII version). */
#endif
	GX_CALL_OPENDEVICE				= GX_CALL_GROUP_GX_DEVICE | 0x0002,	/**< Call code for the gx_opendevice() function (Unicode versin). */
#ifndef ANDROID
	GX_CALL_OPENDEVICEA				= GX_CALL_GROUP_GX_DEVICE | 0x0003,	/**< Call code for the gx_opendevice() function (ASCII version). */
#endif
	GX_CALL_GETDEVICEPROPERTY		= GX_CALL_GROUP_GX_DEVICE | 0x0004,	/**< Call code for the gx_getdeviceproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETDEVICEPROPERTYA		= GX_CALL_GROUP_GX_DEVICE | 0x0005,	/**< Call code for the gx_getdeviceproperty() function (ASCII version). */
#endif
	GX_CALL_SETDEVICEPROPERTY		= GX_CALL_GROUP_GX_DEVICE | 0x0006,	/**< Call code for the gx_setdeviceproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETDEVICEPROPERTYA		= GX_CALL_GROUP_GX_DEVICE | 0x0007,	/**< Call code for the gx_setdeviceproperty() function (ASCII version). */
#endif
	GX_CALL_GETDRIVERPROPERTY		= GX_CALL_GROUP_GX_DEVICE | 0x0008,	/**< Call code for the gx_getdriverproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETDRIVERPROPERTYA		= GX_CALL_GROUP_GX_DEVICE | 0x0009,	/**< Call code for the gx_getdriverproperty() function (ASCII version). */
#endif
	GX_CALL_SETDRIVERPROPERTY		= GX_CALL_GROUP_GX_DEVICE | 0x000A,	/**< Call code for the gx_setdriverproperty() function (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETDRIVERPROPERTYA		= GX_CALL_GROUP_GX_DEVICE | 0x000B,	/**< Call code for the gx_setdriverproperty() function (ASCII version). */
#endif
	GX_CALL_GETSYSTEMINFO			= GX_CALL_GROUP_GX_DEVICE | 0x000C,	/**< Call code for the gx_getsysteminfo() function. */
};

#endif /* GX_SWIGIF GX_MANUAL )*/
#ifdef GX_SWIGIF
%define GX_CALL_GROUP_GX_BMP	0x11050000 %enddef
%define GX_CALL_GROUP_GX_JPEG	0x11060000 %enddef
%define GX_CALL_GROUP_GX_JPEG2K	0x11090000 %enddef
%define GX_CALL_GROUP_GX_WSQ	0x11130000 %enddef
#endif
/******************************************************************************/

/*******************************************************************************
 * Types and structures
 ******************************************************************************/
#ifdef GX_DOTNET
	/* managed code in the .net */
	#pragma managed
#endif

#ifndef GX_EXT_MODULE /*(*/
/** Rectangle definition */
GX_STRUCT gxRCT {
	int left;			/**< Left coordinate (X1) of the rectangle */
	int top;			/**< Top coordinate (Y1) of the rectangle */
	int right;			/**< Right coordinate (X2) of the rectangle */
	int bottom;			/**< Bottom coordinate (Y2) of the rectangle */
};

#ifndef __cplusplus
	typedef struct gxRCT gxRCT;	/**< Workaround for ANSI C */
#endif

/** Defines a single point */
GX_STRUCT gxPNT {
	int x;			/**< Horizontal coordinate of the point */
	int y;			/**< Vertical coordinate of the point */
};

#ifndef __cplusplus
	typedef struct gxPNT gxPNT;	/**< Workaround for ANSI C */
#endif

#ifdef GX_DOTNET
	#ifndef GX_DOTNET_20
	typedef gxPNT gxPNT_ARRAY [];		/**< Point array type definition */
	#else
	typedef array<gxPNT>^ gxPNT_ARRAY;	/**< Point array type definition */
	#endif
#else
	typedef gxPNT gxPNT_ARRAY [];	/**< Point array type definition */
#endif

/** Defines two points */
GX_STRUCT gxPG2 {
	int x1;		/**< Horizontal coordinate of the first point */
	int y1;		/**< Vertical coordinate of the first point */
	int x2;		/**< Horizontal coordinate of the second point */
	int y2;		/**< Vertical coordinate of the second point */
};

#ifndef __cplusplus
	typedef struct gxPG2 gxPG2;	/**< Workaround for ANSI C */
#endif

/** Defines four points */
GX_STRUCT gxPG4 {
	int x1;		/**< Horizontal coordinate of the first point */
	int y1;		/**< Vertical coordinate of the first point */
	int x2;		/**< Horizontal coordinate of the second point */
	int y2;		/**< Vertical coordinate of the second point */
	int x3;		/**< Horizontal coordinate of the third point */
	int y3;		/**< Vertical coordinate of the third point */
	int x4;		/**< Horizontal coordinate of the fourth point */
	int y4;		/**< Vertical coordinate of the fourth point */
};

#ifndef __cplusplus
	typedef struct gxPG4 gxPG4;	/**< Workaround for ANSI C */
#endif

/** Defines one point with floating-point values */
GX_STRUCT gxPNTF {
	float x;		/**< Horizontal coordinate of the point */
	float y;		/**< Vertical coordinate of the point */
};

#ifndef __cplusplus
	typedef struct gxPNTF gxPNTF;	/**< Workaround for ANSI C */
#endif

#endif	/*)*/

#if defined(GX_DOTNET) && !defined(GX_MANUAL)	/*(*/
#pragma unmanaged

/** Defines one rectangle. */
struct _gxRCT {
	int left;	/**< Left coordinate. */
	int top;	/**< Top coordinate. */
	int right;	/**< Right coordinate. */
	int bottom;	/**< Bottom coordinate. */
};

/** Defines one point. */
struct _gxPNT {
	int x;	/**< X parameter. */
	int y;	/**< Y parameter. */
};

/** Defines two points. */
struct _gxPG2 {
	int x1;		/**< X parameter of the first point. */
	int y1;		/**< Y parameter of the first point. */
	int x2;		/**< X parameter of the second point. */
	int y2;		/**< Y parameter of the second point. */
};

/** Defines four points. */
struct _gxPG4 {
	int x1;		/**< X parameter of the first point. */
	int y1;		/**< Y parameter of the first point. */
	int x2;		/**< X parameter of the second point. */
	int y2;		/**< Y parameter of the second point. */
	int x3;		/**< X parameter of the third point. */
	int y3;		/**< Y parameter of the third point. */
	int x4;		/**< X parameter of the fourth point. */
	int y4;		/**< Y parameter of the fourth point. */
};

/** Defines one point with floating-point values */
struct _gxPNTF {
	float x;	/**< X parameter. */
	float y;	/**< Y parameter. */
};

#endif	/*)*/

/*******************************************************************************
 * Data structures for error management
 ******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/** Parameter structure for the gx_geterror() function (Unicode version). */
struct GX_PARM_GETERROR {
	int				 code;		/**< Error code (Specified in gxerror.h or error codes also used in modules or system). */
	wchar_t			*string;	/**< Memory pointer where the function writes the descriptive text of the error. Can be NULL, when there is no description. */
	int				 maxlen;	/**< Length of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_geterror() function (ASCII version). */
struct GX_PARM_GETERRORA {
	int				 code;		/**< Error code (Specified in gxerror.h or error codes also used in modules or system). */
	char			*string;	/**< Memory pointer where the function writes the descriptive text of the error. Can be NULL, when there is no description. */
	int				 maxlen;	/**< Length of the memory area in characters (or bytes). */
};
#endif
#endif /* GX_SWIGIF GX_MANUAL )*/

#ifndef GX_EXT_MODULE /*(*/

#ifdef GX_DOTNET
#pragma managed
#endif

/** Enumerations for flags parameter of gx_seterror() function. */
GX_ENUM GX_ERROR_FLAGS {
	GX_ERR_FLAG_CLEAR	=	0,	/**< Clears the thread-local buffer of the error */
	GX_ERR_FLAG_APPEND	=	1,	/**< Inserts the text to the end of the buffer */
	GX_ERR_FLAG_PREPEND	=	2,	/**< Inserts the text to the start of the buffer */

	GX_ERR_FLAG_APPMODE =	(GX_ERR_FLAG_CLEAR | GX_ERR_FLAG_APPEND | GX_ERR_FLAG_PREPEND), /**< Default flag for GX applications */

	GX_ERR_FLAG_NOARGS	=	0x100,	/**< The function doesn't use the argument parameter */

	GX_ERR_FLAG_LOCAL	=	0x1000, /**< Do not use this! (It is required for backward compatibility) */
	GX_ERR_FLAG_DIRECT	=	0x2000	/**< Do not use the default error string */
};

#ifdef GX_DOTNET
#pragma unmanaged
#endif

#endif /*)*/

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/** Parameter structure for the gx_seterror() function (Unicode version). */
struct GX_PARM_SETERROR {
	int				 flags;			/**< Flags (see \ref GX_ERROR_FLAGS */
	int				 code;			/**< Error code (Specified in gxerror.h or error codes also used in modules or system). */
	const wchar_t	*appformat;		/**< Format string (as for printf). */
	va_list			 arguments;		/**< Arguments for the format string. \warning The overall format string is computed from the <GX system defined string> and the user defined <appformat> string. */
};

#ifndef ANDROID
/** Parameter structure for the gx_seterror() function (Unicode version). */
struct GX_PARM_SETERRORA {
	int				 flags;			/**< Flags. see \ref GX_ERROR_FLAGS */
	int				 code;			/**< Error code (Specified in gxerror.h or error codes also used in modules or system). */
	const char		*appformat;		/**< Format string (as for printf). */
	va_list			 arguments;		/**< Arguments for the format string. \a Warning! The overall format string is computed from the <GX system defined string> and the user defined <appformat> string. */
};
#endif
#endif /* GX_SWIGIF GX_MANUAL )*/

#if !defined(GX_SWIGIF) && !(defined(GX_DOTNET) && defined(GX_MANUAL)) /*(*/

/** One entry in the error table of GX module. */
struct gxERRITEM {
	int		 code;		/**< Error code (Specified in gxerror.h or error codes also used in modules or system). */
	wchar_t	*string;	/**< Error string. This is the GX system defined string. */
};

#ifndef __cplusplus
	typedef struct gxERRITEM gxERRITEM;	/**< Workaround for ANSI C */
#endif

#endif /* GX_SWIGIF GX_DOTNET GX_MANUAL )*/

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/

/** Error table for GX modules. */
struct GX_PARM_UPDATEERRTABLE {
	int				nitems;		/**< Number of items in the table. */
	const gxERRITEM	*items;		/**< Items of the table. */
};

/*******************************************************************************
 * Data structures for memory operations
 ******************************************************************************/

/******************************************************************************/
/** Parameter structure for the gx_globalrealloc() function. */
struct GX_PARM_GLOBALREALLOC {
	void *buffer;	/**< Pointer to a memory area in which the function receives a previously
					 * allocated memory area and where it writes the address of the reallocated area. */
	int size;		/**< Size of the new memory area in bytes. If it is zero it frees the area. */
};

/******************************************************************************/
/** Parameter structure for the gx_globalsize() function. */
struct GX_PARM_GLOBALSIZE {
	void *buffer;	/**< Pointer to the memory area. */
	int	  size;		/**< Variable where the function writes the size of the area. */
};

/******************************************************************************/
/** Parameter structure for the gx_globalrealloc_dbg() function. */
struct GX_PARM_GLOBALREALLOC_DBG {
	void *buffer;		/**< Pointer to a memory area in which the function receives a previously
						 * allocated memory area and where it writes the address of the reallocated area. */
	int size;			/**< Size of the new memory area in bytes. If it is zero it frees the area. */
	const char *file;	/**< Name of the file. */
	int line;			/**< Line number. */
};

/** Parameter structure for the gx_globaltestmem_dbg() function. */
struct GX_PARM_GLOBALTESTMEM_DBG {
	int index;			/**< Entry index. */
	char *fnbuffer;		/**< Buffer for the file name. */
	int fnbsize;		/**< Size of the preallocated buffer. */
	char *membuffer;	/**< Buffer for the memory content. */
	int mbsize;			/**< Size of the preallocated buffer. */
	int line;			/**< Line number. */
	int size;			/**< Size of the allocated memory area. */
	void *address;		/**< Pointer to the allocated memory area. */
};

/**< Parameter structure for the gx_creatememslot() function. */
struct GX_PARM_CREATEMEMSLOT {
	int handle;
	void *mem;
};

/**< Parameter structure for the gx_getmemslot() function. */
struct GX_PARM_GETMEMSLOT {
	int handle;
	void *mem;
};

/**< Parameter structure for the gx_unrefmemslot() function. */
struct GX_PARM_UNREFMEMSLOT {
	int handle;
};

/*******************************************************************************
 * Structures of the module handle
 ******************************************************************************/
/** Parameter structure for the gx_getdefmodulename() function (Unicode version). */
struct GX_PARM_GETDEFMODULENAME {
	int		 group;		/**< Code of the GX group (GX_CALL_GROUP_xxx). */
	wchar_t	*string;	/**< Memory pointer where the function writes the name of the module. */
	int		 maxlen;	/**< Length of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getdefmodulenamea() function (ASCII version). */
struct GX_PARM_GETDEFMODULENAMEA {
	int		 group;		/**< Code of the GX group (GX_CALL_GROUP_xxx). */
	char	*string;	/**< Memory pointer where the function writes the name of the module. */
	int		 maxlen;	/**< Length of the memory area in characters (or bytes). */
};
#endif
/** Parameter structure for the gx_setdefmodulename() function (Unicode version). */
struct GX_PARM_SETDEFMODULENAME {
	int				 group;		/**< Code of the GX group (GX_CALL_GROUP_xxx). */
	const wchar_t	*string;	/**< Memory pointer to the new name of the module. */
};

#ifndef ANDROID
/** Parameter structure for the gx_setdefmodulenamea() function (ASCII version). */
struct GX_PARM_SETDEFMODULENAMEA {
	int				 group;		/**< Code of the GX group (GX_CALL_GROUP_xxx). */
	const char		*string;	/**< Memory pointer to the new name of the module. */
};
#endif
/** Parameter structure for the version information sender. */
struct GX_PARM_SENDCOMPVERSION {
	unsigned int	version;	/**< Version code. The application can send the requested version code to the GX in the loader (gxsdldr.cpp) (version = 0x07010203 -> v7.1.2.3). */
};


#ifndef ANDROID
/** Parameter structure for the gx_listmodulesa() function (ASCII version). */
struct GX_PARM_LISTMODULESA {
	unsigned int	 flags;			/**< Flags (currently must be 0). */
	const char		*filter;		/**< Filter (usable '*' and '?').*/
	char			**files;		/**< Array of files (with path).*/
	unsigned int	*versions;		/**< Array of versions.*/
	int				 nitems;		/**< Number of items in files and versions table.*/
};
#endif
/** Parameter structure for the gx_listmodules() function (Unicode version). */
struct GX_PARM_LISTMODULES {
	unsigned int	 flags;			/**< Flags (currently must be 0). */
	const wchar_t	*filter;		/**< Filter (usable '*' and '?').*/
	wchar_t			**files;		/**< Array of files (with path).*/
	unsigned int	*versions;		/**< Array of versions.*/
	int				 nitems;		/**< Number of items in files and versions table.*/
};


#ifdef GX_DOTNET
	#define gxHANDLE _gxHANDLE
#endif

#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/

#if !defined(GX_SWIGIF) && !(defined(GX_DOTNET) && defined(GX_MANUAL)) /*(*/

/** Handle of the GX module. */
struct gxHANDLE {
	gxu32 handle;	/**< Handle of the module. If it is zero, it is invalid. @see gx_isvalidhandle() */
};

#ifndef __cplusplus
	typedef struct gxHANDLE gxHANDLE;	/**< Workaround for ANSI C */
#endif

#endif /* GX_SWIGIF GX_DOTNET GX_MANUAL )*/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/

/** Parameter structure for the gx_openmodule() function (Unicode version). */
struct GX_PARM_OPENMODULE {
	const wchar_t	*modulename;	/**< Name of the module. */
	const wchar_t	*groupname;		/**< Property group name for the module. Can be NULL (Not every module uses properties). */
	gxHANDLE	 	handle;			/**< Gap area where the function writes the handle of the opened module. */
};

#ifndef ANDROID
/** Parameter structure for the gx_openmodule() function (ASCII version). */
struct GX_PARM_OPENMODULEA {
	const char		*modulename;	/**< Name of the module. */
	const char		*groupname;		/**< Property group name for the module. Can be NULL (Not every module uses properties). */
	gxHANDLE		handle;			/**< Gap area where the function writes the handle of the opened module. */
};
#endif
/** Parameter structure for the gx_closehandle() function. */
struct GX_PARM_CLOSEHANDLE {
	gxHANDLE	 handle;		/**< Handle of an opened module */
};

#endif /* GX_SWIGIF GX_MANUAL )*/

#if !defined(GX_SWIGIF) /*(*/

/** Identification numbers for gxMODULEINFO structure (for GXSD 7.x modules). */
enum GX_INFO_IDS {
	GXMODULE_INFO_ID		= 0x67780000,	/**< Module identification number for gxMODULEINFO structure (for GXSD 7.x modules). */
	GXUSRDRV_INFO_ID		= 0x67786400,	/**< User driver identification number for gxMODULEINFO structure (for GXSD 7.x modules). */
};

#endif /* GX_SWIGIF )*/

#if !defined(GX_SWIGIF) && !(defined(GX_DOTNET) && defined(GX_MANUAL)) /*(*/

#ifdef WIN32
	/** Calling type definition for gx_call or gxMODULEINFO's entry function of the GX modules */
	#define GXAPI __stdcall
#endif
#ifdef LINUX
	/** Calling type definition for gx_call or gxMODULEINFO's entry function of the GX modules */
	#define GXAPI
#endif

/** Function definition for gxMODULEINFO structure (type of the entry function) */
typedef int GXAPI gxmodule_process_t(gxHANDLE mhandle, int function, void *param);

/** Information structure of GX modules. */
struct gxMODULEINFO {
	int			 	 id;			/**< Identification number. @see \ref GXMODULE_INFO_ID */
	int			 	 version;		/**< Module version number (Format: major, minor, sub minor, build - 8,8,8,8 bit). */
	const char		*description;	/**< Description of the module in ASCII format. */
	const wchar_t	*wdescription;	/**< Description of the module in unicode format. */

	gxmodule_process_t	*process;	/**< Pointer to the entry function of the module. */
};

#ifndef __cplusplus
	typedef struct gxMODULEINFO gxMODULEINFO;	/**< Workaround for ANSI C */
#endif

#endif /* GX_SWIGIF GX_DOTNET GX_MANUAL )*/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/

/** Parameter structure for the gx_getmoduleproperty() function (Unicode version). */
struct GX_PARM_GETMODULEPROPERTY {
	const wchar_t	*name;			/**< Name of the property. */
	wchar_t			*string;		/**< Pointer to a memory area where to store the value of the property. */
	int				 maxlen;		/**< Size of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getmoduleproperty() function (ASCII version). */
struct GX_PARM_GETMODULEPROPERTYA {
	const char		*name;			/**< Name of the property. */
	char			*string;		/**< Pointer to a memory area where to store the value of the property. */
	int			 	 maxlen;		/**< Size of the memory area in characters (not bytes). */
};
#endif
/** Parameter structure for the gx_setmoduleproperty() function (Unicode version). */
struct GX_PARM_SETMODULEPROPERTY {
	const wchar_t	*name;			/**< Name of the property. */
	const wchar_t	*string;		/**< Value of the property. Can be NULL. */
};

#ifndef ANDROID
/** Parameter structure for the gx_setmoduleproperty() function (ASCII version). */
struct GX_PARM_SETMODULEPROPERTYA {
	const char		*name;			/**< Name of the property. */
	const char		*string;		/**< Value of the property. Can be NULL. */
};
#endif
/** Parameter structure for the gx_savemoduleproperties() function (Unicode version). */
struct GX_PARM_SAVEMODULEPROPERTIES {
	const wchar_t	*name;			/**< Place of the property in the property tree. */
	int				 level;			/**< Detail level (0 = basic .. 100 = all properties). */
};

#ifndef ANDROID
/** Parameter structure for the gx_savemoduleproperties() function (ASCII version). */
struct GX_PARM_SAVEMODULEPROPERTIESA {
	const char		*name;			/**< Place of the property in the property tree. */
	int				 level;			/**< Detail level (0 = basic .. 100 = all properties). */
};
#endif
#endif	/* GX_SWIGIF GX_MANUAL )*/

#ifdef GX_DOTNET
	#pragma managed
#endif

#ifndef GX_EXT_MODULE /*(*/
/******************************************************************************/
/** Flags for device operations. */
GX_ENUM GX_DEVICE_FLAGS {
	GX_DEVICE_FLAG_TYPE			=	1,	/**< Type of the device. */
	GX_DEVICE_FLAG_NAME			=	2,	/**< Name of the device. */
	GX_DEVICE_FLAG_SERIAL		=	4,	/**< Serial number of the device. */
	GX_DEVICE_FLAG_SERIAL_NOMSK	=	8,	/**< NNC serial number of the device. */

	GX_DEVICE_FLAG_EXCLUSIVE	=	0x100,	/**< Exclusive open mode. */
};

/** Flags for querying the GX system info. */
GX_ENUM GX_SYSINFO_FLAGS {
	GX_SYSINFO_FLAG_FREEFLOW	=	1,	/**< Querying the number of the freeflow licence. */
	GX_SYSINFO_FLAG_PARKING		=	2,	/**< Querying the number of the parking licence. */
	GX_SYSINFO_FLAG_ACCR		=	3,	/**< Querying the number of the container licence. */
	GX_SYSINFO_FLAG_PARKINGLANE	=	4,	/**< Querying the number of the parking lane licence. */
	GX_SYSINFO_FLAG_FACE		=	5,	/**< Querying the number of the face ident licence. */
	GX_SYSINFO_FLAG_PR			=	6,	/**< Querying the number of the passport reader licence. */
};

#endif	/*)*/

#ifdef GX_DOTNET
	#pragma unmanaged
#endif

#if !defined(GX_SWIGIF) && !(defined(GX_MANUAL) && defined(GX_DOTNET))	/*(*/

/** Information structure for a device (Unicode). */
struct GX_DEVICE_INFO {
	wchar_t			type[8];		/**< Type of the device (for example 'NNC'). */
	wchar_t			devname[64];	/**< The unique name of the device. */
	unsigned int	serial;			/**< Serial number of the device. */
	int				priority;		/**< Priority level of the device. */
};

#ifndef __cplusplus
	typedef struct GX_DEVICE_INFO GX_DEVICE_INFO;	/**< Workaround for ANSI C */
#endif

#ifndef ANDROID
/** Information structure for a device (ASCII). */
struct GX_DEVICE_INFOA {
	char			type[8];		/**< Type of the device (for example 'NNC'). */
	char			devname[64];	/**< The unique name of the device. */
	unsigned int	serial;			/**< Serial number of the device. */
	int				priority;		/**< Priority level of the device. */
};
#endif
#ifndef __cplusplus
	typedef struct GX_DEVICE_INFOA GX_DEVICE_INFOA;	/**< Workaround for ANSI C */
#endif

/** Information structure for the GX system. */
struct GX_SYSTEM_INFO {
	int				size;		/**< Size of the structure. */
	int				cm_ff;		/**< Number of CARMEN freeflow licences. */
	int				cm_park;	/**< Number of CARMEN parking licences. */
	int				cm_accr;	/**< Number of CARMEN container licences. */
	int				cm_pl;		/**< Number of CARMEN parking lane licences. */
	int				cm_face;	/**< Number of CARMEN face licences. */
	int				pr;			/**< Number of Passport Reader licences. */
};

#ifndef __cplusplus
	typedef struct GX_SYSTEM_INFO GX_SYSTEM_INFO;	/**< Workaround for ANSI C */
#endif

#endif /* GX_SWIGIF GX_MANUAL GX_DOTNET )*/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/

#ifndef ANDROID
/** Parameter structure for the gx_listdevices() function (ASCII version). */
struct GX_PARM_LISTDEVICESA {
	unsigned int	 flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFOA	 filter;/**< Filter. */
	int		 		 maxitems;		/**< Number of items in the array. */
	struct GX_DEVICE_INFOA	*items;	/**< Pointer to the array. */
};
#endif
/** Parameter structure for the gx_listdevices() function (Unicode version). */
struct GX_PARM_LISTDEVICES {
	unsigned int	 flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFO	 filter;/**< Filter. */
	int		 		 maxitems;		/**< Number of items in the array. */
	struct GX_DEVICE_INFO	*items;	/**< Pointer to the array. */
};

/** Parameter structure for the the gx_opendevice() function (Unicode version). */
struct GX_PARM_OPENDEVICE {
	unsigned int	  flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFO	filter;		/**< Filter. */
	int				  nproperties;		/**< Number of device properties. */
	const wchar_t	**properties;		/**< Device properties. */
	int				  timeoutms;		/**< Timeout in milliseconds. */
	gxHANDLE		  handle;			/**< The function updates it with the opened handle. */
	struct GX_DEVICE_INFO	info;		/**< The function fills it with the information about the opened device. */
};

#ifndef ANDROID
/** Parameter structure for the gx_opendevicea() function (ASCII version). */
struct GX_PARM_OPENDEVICEA {
	unsigned int	  flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFOA	filter;		/**< Filter. */
	int				  nproperties;		/**< Number of device properties. */
	const char		**properties;		/**< Device properties. */
	int				  timeoutms;		/**< Timeout in milliseconds. */
	gxHANDLE		  handle;			/**< The function updates it with the opened handle. */
	struct GX_DEVICE_INFOA	info;		/**< The function fills it with the information about the opened device. */
};
/** Parameter structure for device property functions. */
struct GX_PARM_GETDEVICEPROPERTYA {
	const char		*name;				/**< The name of the property. */
	int				sname;				/**< The size of the property name. */
	char			*value;				/**< The value of the property. */
	int				svalue;				/**< The size of the property value. */
};

/** Parameter structure for device property functions. */
struct GX_PARM_SETDEVICEPROPERTYA {
	const char		*name;				/**< The name of the property. */
	int				sname;				/**< The size of the property name. */
	const char		*value;				/**< The value of the property. Can be NULL. */
	int				svalue;				/**< The size of the property value. */
};
#endif

/** Parameter structure for the gx_getsysteminfo() function. */
#define GX_PARM_GETSYSTEMINFO	GX_SYSTEM_INFO	/**< GX system information structure. */

#if defined(WIN32)
/** Parameter structure for the gx_listdevices() function (ASCII version).
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_LISTDEVICESA32 {
	unsigned int					flags;		/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFOA			filter;		/**< Filter. */
	int		 						maxitems;	/**< Number of items in the array. */
	struct GX_DEVICE_INFOA* __ptr32 items;		/**< Pointer to the array. */
};

/** Parameter structure for the gx_listdevices() function (Unicode version).
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_LISTDEVICES32 {
	unsigned int					flags;		/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFO			filter;		/**< Filter. */
	int		 						maxitems;	/**< Number of items in the array. */
	struct GX_DEVICE_INFO* __ptr32	items;		/**< Pointer to the array. */
};

/** Parameter structure for the the gx_opendevice() function (Unicode version).
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_OPENDEVICE32 {
	unsigned int						flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFO				filter;			/**< Filter. */
	int									nproperties;	/**< Number of device properties. */
	const wchar_t* __ptr32 * __ptr32	properties;		/**< Device properties. */
	int									timeoutms;		/**< Timeout in milliseconds. */
	gxHANDLE							handle;			/**< The function updates it with the opened handle. */
	struct GX_DEVICE_INFO				info;			/**< The function fills it with the information about the opened device. */
};

/**Parameter structure for the gx_opendevicea() function (ASCII version).
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_OPENDEVICEA32 {
	unsigned int					flags;			/**< Flags (see \ref GX_DEVICE_FLAGS). */
	struct GX_DEVICE_INFOA			filter;			/**< Filter. */
	int								nproperties;	/**< Number of device properties. */
	const char* __ptr32 * __ptr32	properties;		/**< Device properties. */
	int								timeoutms;		/**< Timeout in milliseconds. */
	gxHANDLE						handle;			/**< The function updates it with the opened handle. */
	struct GX_DEVICE_INFOA			info;			/**< The function fills it with the information about the opened device. */
};

/** Parameter structure for device property functions.
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_GETDEVICEPROPERTYA32 {
	const char* __ptr32 name;			/**< The name of the property. */
	int					sname;			/**< The size of the property name. */
	char* __ptr32		value;			/**< The value of the property. */
	int					svalue;			/**< The size of the property value. */
};

/** Parameter structure for device property functions.
 *
 * \note (32 bit calling in x64) */
struct GX_PARM_SETDEVICEPROPERTYA32 {
	const char* __ptr32 name;			/**< The name of the property. */
	int					sname;			/**< The size of the property name. */
	char* __ptr32		value;			/**< The value of the property. Can be NULL. */
	int					svalue;			/**< The size of the property value. */
};
#endif
/******************************************************************************/
#endif /* GX_SWIGIF GX_MANUAL )*/
#if !defined(GX_SWIGIF) && !(defined(GX_MANUAL) && defined(GX_DOTNET))	/*(*/

#ifdef __cplusplus
	extern "C"
	{
#endif
/** Calls a module process with the specified parameters.
 *
 * The functions and parameters usable inside the modules can be found in the
 * documentation of the modules. The headers given with the modules contain
 * inline functions, that make the access to the functions of the module easier.
 *
 * @see gx_openmodule() gx_closehandle() gx_direct()
 *
 * @param handle	Handle of an opened module or special system handle ( see gx_direct() ).
 * @param function	Identifier of the function (GX_CALL_xxx).
 * @param params	Parameters to give for the function (GX_PARM_xxx).
 * @return Module defined, usually non-zero on success. */
int GXAPI gx_call(struct gxHANDLE handle, int function, void *params);
#ifdef __cplusplus
	}
#endif

#endif	/* GX_SWIGIF GX_MANUAL GX_DOTNET )*/
/******************************************************************************/

/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
enum GX_MAXLEN_VALUES {
	GX_MAXLEN_STRING	= 1023,
	GX_MAXLEN_ERRVALUE	= 255,
	GX_MAXLEN_PROPVALUE	= 255,
	GX_MAXLEN_INT		= 32,
	GX_MAXLEN_FLOAT		= 64,
	GX_MAXLEN_VERSION	= 20
};
#endif	/* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(NO_GX_FUNCTIONS)	/*(*/
/*******************************************************************************
 * Inline functions
 ******************************************************************************/

/******************************************************************************/
/** Creates a handle for the direct access.
 *
 * @param call_group Call-group of the module (specified in gxsd.h: \a GX_CALL_GROUP_xxx).
 * @return Generated handle.
 */
inline gxHANDLE gx_direct(int call_group) {
	gxHANDLE ret;
	assert((unsigned int)call_group >= (unsigned int)GX_CALL_GROUP_API_FIRST);
	ret.handle = (((unsigned int)call_group >> 16) | 0xFFFF0000);
	return ret;
}

/******************************************************************************/
/** Lists path and version of modules (Unicode version).
 *
 * @param flags Reserved for future usage. Currently must be 0.
 * @param filter Name of the module (usable '*' and '?' character, e.g. 'cmanpr*')
 * @param files The function creates a table with full path and module names.
 *        You must free every item and table by gx_globalfree function.
 *		  'for(int ix = 0; ix < nitems; ix++) { gx_globalfree(files[ix]); }
 *         gx_globalfree(files);'
 * @param versions The function creates a table with file versions (it can be 0.0.0.0).
 *        You must free the table with gx_globalfree function.
 * @param nitems The function returns number of items of tables (files, versions).
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately ( see gx_geterror() ). */
inline int gx_listmodules(unsigned int flags, const wchar_t *filter, wchar_t ***files,
							unsigned int **versions, int *nitems) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_LISTMODULES m;
	int st = 0;
	m.flags = flags;
	m.filter = filter;
	m.files = NULL;
	m.versions = NULL;
	m.nitems = 0;

	st = gx_call(nullhandle, GX_CALL_LISTMODULES, &m);
	if(st) {
		*files = m.files;
		*versions = m.versions;
		*nitems = m.nitems;
	} else {
		*files = NULL;
		*versions = NULL;
		*nitems = 0;
	}
	return st;
}

#ifndef ANDROID
/******************************************************************************/
/** Lists path and version of modules (ASCII version).
 *
 * @param flags Reserved for future usage. Currently must be 0.
 * @param filter Name of the module (usable '*' and '?' character, e.g. 'cmanpr*')
 * @param files The function creates a table with full path and module names.
 *        You must free every item and table by gx_globalfree function.
 *		  'for(int ix = 0; ix < nitems; ix++) { gx_globalfree(files[ix]); }
 *         gx_globalfree(files);'
 * @param versions The function creates a table with file versions (it can be 0.0.0.0).
 *        You must free the table with gx_globalfree function.
 * @param nitems The function returns number of items of tables (files, versions).
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately ( see gx_geterror() ). */
inline int gx_listmodulesa(unsigned int flags, const char *filter, char ***files,
							unsigned int **versions, int *nitems) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_LISTMODULESA m;
	int st = 0;
	m.flags = flags;
	m.filter = filter;
	m.files = NULL;
	m.versions = NULL;
	m.nitems = 0;

	st = gx_call(nullhandle, GX_CALL_LISTMODULESA, &m);
	if(st) {
		*files = m.files;
		*versions = m.versions;
		*nitems = m.nitems;
	} else {
		*files = NULL;
		*versions = NULL;
		*nitems = 0;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Lists path and version of modules (ASCII version).
 *
 * @param flags Reserved for future usage. Currently must be 0.
 * @param filter Name of the module (usable '*' and '?' character, e.g. 'cmanpr*')
 * @param files The function creates a table with full path and module names.
 *        You must free every item and table by gx_globalfree function.
 *		  'for(int ix = 0; ix < nitems; ix++) { gx_globalfree(files[ix]); }
 *         gx_globalfree(files);'
 * @param versions The function creates a table with file versions (it can be 0.0.0.0).
 *        You must free the table with gx_globalfree function.
 * @param nitems The function returns number of items of tables (files, versions).
 * @return On error false is returned and the error code/string in the GX system
 * is set appropriately ( see gx_geterror() ). */
inline int gx_listmodules(unsigned int flags, const char *filter, char ***files,
							unsigned int **versions, int *nitems) {
	return gx_listmodulesa(flags, filter, files, versions, nitems);
}
#endif
#endif

/*******************************************************************************
 * Memory operations
 ******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_memory
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Reallocates or frees a previously allocated memory area or allocates a new area.
 *
 * @param buffer Pointer to a memory area pointer where the function receives the address of a
 *               previously allocated memory area and where it writes the
 *               address of the reallocated area.
 *               This function is also suitable for allocation if the value of
 *               *buffer is zero.
 *               If sbuffer is zero the function frees the specified memory area.
 * @param sbuffer Size of the new memory area in bytes. If it is zero it frees the area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
/******************************************************************************/
inline int gx_globalrealloc(void **buffer, int sbuffer) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GLOBALREALLOC r;
	int ret;

	assert(buffer);
	assert(sbuffer >= 0);
	r.buffer = *buffer;
	r.size = sbuffer;
	ret = gx_call(nullhandle, GX_CALL_GLOBALREALLOC, &r);
	if(ret) *buffer = r.buffer;
	return ret;
}

/******************************************************************************/
/** Allocates a memory area that can be passed between modules.
 *
 * @param buffer Pointer to a memory area pointer where the function writes
 *               the address of the newly allocated area. If the original value
 *               of the pointer was non-zero the memory area will be lost after
 *               the allocation.
 * @param sbuffer Size of the memory area to allocate.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globalalloc(void **buffer, int sbuffer) {
	assert(buffer);
	*buffer = 0;
	return gx_globalrealloc(buffer, sbuffer);
}

/******************************************************************************/
/** Frees a previously allocated memory area.
 *
 * @param buffer Pointer to a memory area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globalfree(void *buffer) {
	assert(buffer);
	return gx_globalrealloc(&buffer, 0);
}

/******************************************************************************/
/** Gets the size of a previously allocated memory area in bytes.
 *
 * @param sbuffer Pointer where the function writes the size of the area.
 * @param buffer  Pointer to the memory area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globalsize(int *sbuffer, void *buffer) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GLOBALSIZE s;
	int ret;

	assert(sbuffer);
	assert(buffer);
	s.buffer = buffer;
	ret = gx_call(nullhandle, GX_CALL_GLOBALSIZE, &s);
	if(ret) *sbuffer = s.size;
	return ret;
}

/******************************************************************************/
/** Reallocates or frees a previously allocated memory area or allocates a new area (Debug version).
 *
 * @param buffer Pointer to a memory area pointer where the function receives the address of a
 *               previously allocated memory area and where it writes the
 *               address of the reallocated area.
 *               This function is also suitable for allocation if the value of
 *               *buffer is zero.
 *               If sbuffer is zero the function frees the specified memory area.
 * @param sbuffer Size of the new memory area in bytes. If it is zero it frees the area.
 * @param file File name.
 * @param line Line number.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
/******************************************************************************/
inline int gx_globalrealloc_dbg(void **buffer, int sbuffer, const char *file, int line) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GLOBALREALLOC_DBG r;
	int ret;

	assert(buffer);
	assert(sbuffer >= 0);
	r.buffer = *buffer;
	r.size = sbuffer;
	r.file = file;
	r.line = line;
	ret = gx_call(nullhandle, GX_CALL_GLOBALREALLOC_DBG, &r);
	if(ret) *buffer = r.buffer;
	return ret;
}

/******************************************************************************/
/** Allocates a memory area that can be passed between modules (Debug version).
 *
 * @param buffer Pointer to a memory area pointer where the function writes
 *               the address of the newly allocated area. If the original value
 *               of the pointer was non-zero the memory area will be lost after
 *               the allocation.
 * @param sbuffer Size of the memory area to allocate.
 * @param file File name.
 * @param line Line number.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globalalloc_dbg(void **buffer, int sbuffer,const char *file, int line) {
	assert(buffer);
	*buffer = 0;
	return gx_globalrealloc_dbg(buffer, sbuffer, file, line);
}

/******************************************************************************/
/** Checks the memory consistency previously allocated with the gx_globalalloc()
 * or gx_globalrealloc() functions (Debug version).
 *
 * @return On memory inconsistency error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globalcheck_dbg() {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_GLOBALCHECK_DBG, 0);
}

/******************************************************************************/
/** Returns details about the unfreed memory previously allocated with the gx_globalalloc()
 * or gx_globalrealloc() functions (Debug version).
 *
 * @param index		The index of the allocated memory (global).
 * @param fnbuffer	Preallocated buffer for returning the file name where the allocation happened.
 * @param fnbsize	The size of the preallocated file name buffer.
 * @param membuffer	Preallocated buffer for returning the memory content (human readable format).
 * @param mbsize	The size of the preallocated memory content buffer.
 * @param line		The line number where the allocation happened.
 * @param size		The size of the allocated memory area.
 * @param address	Pointer for returning the allocate memory address.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_globaltestmem_dbg(int index, char *fnbuffer, int fnbsize, char *membuffer, int mbsize
							, int *line, int *size, void **address) {

	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GLOBALTESTMEM_DBG gtm;

	gtm.index = index;
	gtm.fnbuffer = fnbuffer;
	gtm.fnbsize = fnbsize;
	gtm.membuffer = membuffer;
	gtm.mbsize = mbsize;
	if(!gx_call(nullhandle, GX_CALL_GLOBALTESTMEM_DBG, &gtm)) return 0;
	if(line) *line = gtm.line;
	if(size) *size = gtm.size;
	if(address) *address = gtm.address;
	return true;
}

#if defined(GX_TESTMEMORY) || defined(GX_TESTLEAKS)

/** Release/Debug workaround. */
#define gx_globalrealloc(buf,sbuf) gx_globalrealloc_dbg(buf,sbuf, __FILE__, __LINE__)
/** Release/Debug workaround. */
#define gx_globalalloc(buf,sbuf) gx_globalalloc_dbg(buf,sbuf, __FILE__, __LINE__)

#else

/** Release/Debug workaround. */
#define gx_globalrealloc_dbg(buf,sbuf,f,l) gx_globalrealloc(buf,sbuf)
/** Release/Debug workaround. */
#define gx_globalalloc_dbg(buf,sbuf,f,l) gx_globalalloc(buf,sbuf)

#endif

/******************************************************************************/
/** Allocates a memory slot and returns a handle to it.
 *
 * \note The reference counter is set to 1.
 *
 * @param handle	Preallocated buffer for the result.
 * @param mem		Preallocated buffer for getting the memslot address.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_creatememslot(int *handle,void **mem) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CREATEMEMSLOT cm;
	assert(handle && mem);
	if(!gx_call(nullhandle, GX_CALL_CREATEMEMSLOT, &cm)) return 0;
	if(handle) *handle = cm.handle;
	if(mem) *mem = cm.mem;
	return true;
}

/******************************************************************************/
/** Returns the memory pointer to use on data update.
 *
 * @param handle	The handle of the memslot.
 * @param mem		Preallocated buffer for the result.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmemslot(int handle,void **mem) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETMEMSLOT gm;
	assert(mem);
	gm.handle = handle;
	if(!gx_call(nullhandle, GX_CALL_GETMEMSLOT, &gm)) return 0;
	if(mem) *mem = gm.mem;
	return true;
}

/******************************************************************************/
/** Decrements the memory slot's reference counter.
 *
 * \note If the reference counter becames 0 the memory slot is deleted.
 *
 * @param handle	The handle of the memslot.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_unrefmemslot(int handle) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UNREFMEMSLOT um;
	um.handle = handle;
	return gx_call(nullhandle, GX_CALL_UNREFMEMSLOT, &um);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/*******************************************************************************
 * Module operations
 ******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_module
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Opens a GX system compatible module (Unicode version).
 *
 * \par
 * The modules can be found in \a /usr/lib/gx under GNU/Linux system. It is not
 * necessary to give the whole path and the extension when referring to a module name
 * (for example \a fxvd4 is enough instead of \a /usr/lib/gx/fxvd4.so).
 *
 * \par
 * The system searches for the modules in the system directory, in the default module directory and in the directories
 * stored in the PATH environment variable under Windows systems. Specifying the
 * whole path is needed only if the module cannot be found in the standard directories.
 *
 * \par
 * The third parameter is for giving the location of the properties of the module
 * in the property tree. If it is not specified the module will work with the default
 * settings.
 *
 * \par
 * Note: Not every module uses properties. In case of not using properties
 * give NULL for the propname parameter.
 *
 * @see gx_closehandle() gx_isvalidhandle()
 *
 * @param handle Writes the handle of the opened module to the memory area where this pointer refers.
 * @param modulename Name of the module.
 * @param groupname Place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_openmodule(gxHANDLE *handle, const wchar_t *modulename, const wchar_t *groupname) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_OPENMODULE op;

	assert(handle);
	assert(modulename);
	op.modulename = modulename;
	op.groupname = groupname;
	if(!gx_call(nullhandle, GX_CALL_OPENMODULE, &op)) return false;
	*handle = op.handle;
	return true;
}

#ifndef ANDROID
/******************************************************************************/
/** Opens a GX system compatible module (ASCII version).
 *
 * \par
 * The modules can be found in \a /usr/lib/gx under GNU/Linux system. It is not
 * necessary to give the whole path and the extension when referring to a module name
 * (for example \a fxvd4 is enough instead of \a /usr/lib/gx/fxvd4.so).
 *
 * \par
 * The system searches for the modules in the system directory, in the default module directory and in the directories
 * stored in the PATH environment variable under Windows systems. Specifying the
 * whole path is needed only if the module cannot be found in the standard directories.
 *
 * \par
 * The third parameter is for giving the location of the properties of the module
 * in the property tree. If it is not specified the module will work with the default
 * settings.
 *
 * \par
 * Note: Not every module uses properties. In case of not using properties
 * give NULL for the propname parameter.
 *
 * @see gx_closehandle() gx_isvalidhandle()
 *
 * @param handle Writes the handle of the opened module to the memory area where this pointer refers.
 * @param modulename Name of module.
 * @param groupname Place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_openmodulea(gxHANDLE *handle, const char *modulename, const char *groupname) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_OPENMODULEA op;

	assert(handle);
	assert(modulename);
	op.modulename = modulename;
	op.groupname = groupname;
	if(!gx_call(nullhandle, GX_CALL_OPENMODULEA, &op)) return false;
	*handle = op.handle;
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Opens a GX system compatible module (ASCII version).
 *
 * \par
 * The modules can be found in \a /usr/lib/gx under GNU/Linux system. It is not
 * necessary to give the whole path and the extension when referring to a module name
 * (for example \a fxvd4 is enough instead of \a /usr/lib/gx/fxvd4.so).
 *
 * \par
 * The system searches for the modules in the system directory, in the default module directory and in the directories
 * stored in the PATH environment variable under Windows systems. Specifying the
 * whole path is needed only if the module cannot be found in the standard directories.
 *
 * \par
 * The third parameter is for giving the location of the properties of the module
 * in the property tree. If it is not specified the module will work with the default
 * settings.
 *
 * \par
 * Note: Not every module uses properties. In case of not using properties
 * give NULL for the propname parameter.
 *
 * @see gx_closehandle() gx_isvalidhandle()
 *
 * @param handle Writes the handle of the opened module to the memory area where this pointer refers.
 * @param modulename Name of module.
 * @param groupname Place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_openmodule(gxHANDLE *handle, const char *modulename, const char *groupname) {
	return gx_openmodulea(handle, modulename, groupname);
}
#endif
#endif
/******************************************************************************/
/** Closes a previously opened module. In case of successful execution the
 * handle will be cleared.
 *
 * @see gx_openmodule() gx_isvalidhandle()
 *
 * @param handle Pointer to the module handle.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_closehandle(gxHANDLE *handle) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CLOSEHANDLE cl;
	assert(handle);
	cl.handle = *handle;
	if(!gx_call(nullhandle, GX_CALL_CLOSEHANDLE, &cl)) return false;
	handle->handle = 0;  /* invalid handle */
	return true;
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_reference
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Increases the reference counter of a GX handle.
 *
 * @param handle Handle of the module.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_refhandle(gxHANDLE handle) {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_REFHANDLE, &handle);
}

/******************************************************************************/
/** Decreases the reference counter of a GX handle.
 *
 * @param handle Handle of the module.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_unrefhandle(gxHANDLE *handle) {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_UNREFHANDLE, handle);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/******************************************************************************/
/** Checks if the handle of a module is valid.
 *
 * @see gx_openmodule() gx_closehandle()
 *
 * @param handle Handle of the module.
 * @return In case of existing handle the return value is non-zero. */
inline int gx_isvalidhandle(gxHANDLE handle) {
	return handle.handle ? true : false;
}

/******************************************************************************/
/** \addtogroup gx_group_module
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Gives information about an opened module.
 *
 * @see gx_openmodule()
 *
 * @param handle Handle of the module.
 * @param moduleinfo Pointer to an information structure pointer where the
 *        system writes the data of the specified module.
 *        ( see gxMODULEINFO )
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleinfo(gxHANDLE handle, const gxMODULEINFO **moduleinfo) {
	assert(moduleinfo);
	return gx_call(handle, GX_CALL_GETMODULEINFO, (void *)moduleinfo);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_property
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Gets a property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const wchar_t *name, wchar_t *string, int maxlen) {
	struct GX_PARM_GETMODULEPROPERTY gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETMODULEPROPERTY, &gp);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets a property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertya(gxHANDLE handle, const char *name, char *string, int maxlen) {
	struct GX_PARM_GETMODULEPROPERTYA gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETMODULEPROPERTYA, &gp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets a property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const char *name, char *string, int maxlen) {
	return gx_getmodulepropertya(handle, name, string, maxlen);
}
#endif
#endif
/******************************************************************************/
/** Gets an integer property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Pointer to an integer where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyint(gxHANDLE handle, const wchar_t *name, int *ivalue) {
	wchar_t ibuf[GX_MAXLEN_INT+1];
	int ret;
	assert(ivalue);
	ibuf[GX_MAXLEN_INT] = 0;
	ret = gx_getmoduleproperty(handle, name, ibuf, GX_MAXLEN_INT);
	if(ret) {
		*ivalue = (int)gx_wcstol(ibuf, 0, 10);
	}
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets an integer property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Pointer to an integer where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const wchar_t *name, int *ivalue) {
	return gx_getmodulepropertyint(handle, name, ivalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Gets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Pointer to an integer where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyinta(gxHANDLE handle, const char *name, int *ivalue) {
	char ibuf[GX_MAXLEN_INT+1];
	int ret;
	assert(ivalue);
	ibuf[sizeof(ibuf)-1] = 0;
	ret = gx_getmodulepropertya(handle, name, ibuf, sizeof(ibuf)-1);
	if(ret) {
		*ivalue = atoi(ibuf);
	}
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Pointer to an integer where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const char *name, int *ivalue) {
	return gx_getmodulepropertyinta(handle, name, ivalue);
}

/******************************************************************************/
/** Gets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Pointer to an integer where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyint(gxHANDLE handle, const char *name, int *ivalue) {
	return gx_getmodulepropertyinta(handle, name, ivalue);
}
#endif
#endif
/******************************************************************************/
/** Gets a floating-point property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Pointer to a floating-point where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyfloat(gxHANDLE handle, const wchar_t *name, double *fvalue) {
	wchar_t fbuf[GX_MAXLEN_FLOAT+1];
	int ret;
	assert(fvalue);
	fbuf[GX_MAXLEN_FLOAT] = 0;
	ret = gx_getmoduleproperty(handle, name, fbuf, GX_MAXLEN_FLOAT);
	if(ret) {
		*fvalue = (double)wcstod(fbuf, 0);
	}
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets a floating-point property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Pointer to a floating-point where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const wchar_t *name, double *fvalue) {
	return gx_getmodulepropertyfloat(handle, name, fvalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Gets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Pointer to a floating-point where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyfloata(gxHANDLE handle, const char *name, double *fvalue) {
	char fbuf[GX_MAXLEN_FLOAT+1];
	int ret;
	assert(fvalue);
	fbuf[sizeof(fbuf)-1] = 0;
	ret = gx_getmodulepropertya(handle, name, fbuf, sizeof(fbuf)-1);
	if(ret) {
		*fvalue = (double)atof(fbuf);
	}
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Pointer to a floating-point where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmoduleproperty(gxHANDLE handle, const char *name, double *fvalue) {
	return gx_getmodulepropertyfloata(handle, name, fvalue);
}
/******************************************************************************/
/** Gets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Pointer to a floating-point where to store the value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyfloat(gxHANDLE handle, const char *name, double *fvalue) {
	return gx_getmodulepropertyfloata(handle, name, fvalue);
}
#endif
#endif

/******************************************************************************/
/** Gets a version property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param version Pointer to an integer where to store the version.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyversion(gxHANDLE handle, const wchar_t *name, unsigned int *version) {
	wchar_t fbuf[GX_MAXLEN_VERSION+1];
	int ret;
	assert(version);
	fbuf[GX_MAXLEN_VERSION] = 0;
	ret = gx_getmoduleproperty(handle, name, fbuf, GX_MAXLEN_VERSION);
	if(ret) {
		int ix;
		unsigned int ver = 0;
		wchar_t *s = fbuf;
		for(ix = 0; (ix < 4) && *s; ix++) {
			ver = (ver << 8) + gx_wcstol(s, &s, 10);
			if(*s == '.') s++;
		}
		*version = ver;
	}
	return ret;
}

#ifndef ANDROID
/******************************************************************************/
/** Gets a version property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param version Pointer to an integer where to store the version.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyversiona(gxHANDLE handle, const char *name, unsigned int *version) {
	char fbuf[GX_MAXLEN_VERSION+1];
	int ret;
	fbuf[sizeof(fbuf)-1] = 0;
	ret = gx_getmodulepropertya(handle, name, fbuf, sizeof(fbuf)-1);
	if(ret) {
		int ix;
		unsigned int ver = 0;
		char *s = fbuf;
		for(ix = 0; (ix < 4) && *s; ix++) {
			ver = (ver << 8) + strtol(s, &s, 10);
			if(*s == '.') s++;
		}
		*version = ver;
	}
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets a version property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param version Pointer to an integer where to store the version.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getmodulepropertyversion(gxHANDLE handle, const char *name, unsigned int *version) {
	return gx_getmodulepropertyversiona(handle, name, version);
}
#endif
#endif
/******************************************************************************/
/** Sets a property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const wchar_t *name, const wchar_t *string) {
	struct GX_PARM_SETMODULEPROPERTY sp;
	sp.name = name;
	sp.string = string;
	return gx_call(handle, GX_CALL_SETMODULEPROPERTY, &sp);
}

#ifndef ANDROID
/******************************************************************************/
/** Sets a property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertya(gxHANDLE handle, const char *name, const char *string) {
	struct GX_PARM_SETMODULEPROPERTYA sp;
	sp.name = name;
	sp.string = string;
	return gx_call(handle, GX_CALL_SETMODULEPROPERTYA, &sp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets a property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const char *name, const char *string) {
	return gx_setmodulepropertya(handle, name, string);
}
#endif
#endif
/******************************************************************************/
/** Sets an integer property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyint(gxHANDLE handle, const wchar_t *name, int ivalue) {
	wchar_t ibuf[GX_MAXLEN_INT+1];
	gx_snwprintf(ibuf, GX_MAXLEN_INT+1, L"%i", ivalue);
	ibuf[GX_MAXLEN_INT] = 0;
	return gx_setmoduleproperty(handle, name, ibuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets an integer property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const wchar_t *name, int ivalue) {
	return gx_setmodulepropertyint(handle, name, ivalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Sets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyinta(gxHANDLE handle, const char *name, int ivalue) {
	char ibuf[GX_MAXLEN_INT+1];
	gx_snprintf(ibuf, GX_MAXLEN_INT+1, "%i", ivalue);
	ibuf[GX_MAXLEN_INT] = 0;
	return gx_setmodulepropertya(handle, name, ibuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const char *name, int ivalue) {
	return gx_setmodulepropertyinta(handle, name, ivalue);
}

/******************************************************************************/
/** Sets an integer property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyint(gxHANDLE handle, const char *name, int ivalue) {
	return gx_setmodulepropertyinta(handle, name, ivalue);
}
#endif
#endif
/******************************************************************************/
/** Sets a floating-point property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle handle of the module.
 * @param name Name of the property.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyfloat(gxHANDLE handle, const wchar_t *name, double fvalue) {
	wchar_t fbuf[GX_MAXLEN_FLOAT+1];
	gx_snwprintf(fbuf, GX_MAXLEN_FLOAT+1, L"%f", fvalue);
	fbuf[GX_MAXLEN_FLOAT] = 0;
	return gx_setmoduleproperty(handle, name, fbuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets a floating-point property of the specified module (Unicode version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle handle of the module.
 * @param name Name of the property.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const wchar_t *name, double fvalue) {
	return gx_setmodulepropertyfloat(handle, name, fvalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Sets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyfloata(gxHANDLE handle, const char *name, double fvalue) {
	char fbuf[GX_MAXLEN_FLOAT+1];
	gx_snprintf(fbuf, GX_MAXLEN_FLOAT+1, "%f", fvalue);
	fbuf[GX_MAXLEN_FLOAT] = 0;
	return gx_setmodulepropertya(handle, name, fbuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmoduleproperty(gxHANDLE handle, const char *name, double fvalue) {
	return gx_setmodulepropertyfloata(handle, name, fvalue);
}

/******************************************************************************/
/** Sets a floating-point property of the specified module (ASCII version).
 *
 * \par
 * Module properties can be found at the description of the specified module.
 * These settings are unique for each
 * module handle and are not stored on the mass storage device.
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Name of the property.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setmodulepropertyfloat(gxHANDLE handle, const char *name, double fvalue) {
	return gx_setmodulepropertyfloata(handle, name, fvalue);
}
#endif
#endif
/******************************************************************************/
/** It starts the property transaction. The module accepts but doesn't update
 *  properties (setmoduleproperty). You must use 'gx_mpcommit' to updates
 *  these properties.
 * \warning Not supported by each module!
 * @param handle Handle of the module.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_mpstarttransaction(gxHANDLE handle) {
	return gx_call(handle, GX_CALL_MPSTARTTRANSACTION, (void *)0);
}

/******************************************************************************/
/** It ends the property transaction and updates your changes to module.
 * \warning Not supported by each module!
 * @param handle Handle of the module.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_mpcommit(gxHANDLE handle) {
	return gx_call(handle, GX_CALL_MPCOMMIT, (void *)0);
}

/******************************************************************************/
/** Saves properties of a module stored in the memory to a branch of the
 * property tree stored on a mass storage device (Unicode version).
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Place of property in the property tree.
 * @param level Higher numbers give more details (0 = basic properties, 100 = all properties).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savemoduleproperties(gxHANDLE handle, const wchar_t *name, int level GX_DEFARG(0)) {
	struct GX_PARM_SAVEMODULEPROPERTIES mp;
	mp.name = name;
	mp.level = level;
	return gx_call(handle, GX_CALL_SAVEMODULEPROPERTIES, &mp);
}

#ifndef ANDROID
/******************************************************************************/
/** Saves properties of a module stored in the memory to a branch of the
 * property tree stored on a mass storage device (ASCII version).
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Place of property in the property tree.
 * @param level Higher numbers give more details (0 = basic properties,	100 = all properties).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savemodulepropertiesa(gxHANDLE handle, const char *name, int level GX_DEFARG(0)) {
	struct GX_PARM_SAVEMODULEPROPERTIESA mp;
	mp.name = name;
	mp.level = level;
	return gx_call(handle, GX_CALL_SAVEMODULEPROPERTIESA, &mp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Saves properties of a module stored in the memory to a branch of the
 * property tree stored on a mass storage device (ASCII version).
 *
 * \warning Not supported by each module!
 *
 * @param handle Handle of the module.
 * @param name Place of property in the property tree.
 * @param level Higher numbers give more details (0 = basic properties,	100 = all properties).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savemoduleproperties(gxHANDLE handle, const char *name, int level = 0) {
	return gx_savemodulepropertiesa(handle, name, level);
}
#endif
#endif
/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_error
 * @{
 */
/******************************************************************************/

/*******************************************************************************
 * ERRORS
 ******************************************************************************/

/******************************************************************************/
/** You can query the error code and string with this function (Unicode version).
 *
 * @param code The function will update it with the error code (Can be NULL).
 * @param string Memory pointer where the function writes the descriptive text
 *             of the error. Can be NULL, in that case there is no description.
 * @param maxlen Length of the memory area in characters (not bytes).
 * @return It returns error code. */
inline int gx_geterror(int *code, wchar_t *string, int maxlen) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETERROR me;
	int err_code;
	me.string = string;
	me.maxlen = maxlen;
	err_code = gx_call(nullhandle, GX_CALL_GETERROR, &me);
	if(code) *code = me.code;
	return err_code;
}

#ifndef ANDROID
/******************************************************************************/
/** You can query the error code and string with this function (ASCII version).
 *
 * @param code The function will update it with the error code (Can be NULL).
 * @param string Memory pointer where the function writes the descriptive text
 *             of the error. Can be NULL, in that case there is no description.
 * @param maxlen Length of the memory area in characters (not bytes).
 * @return The error code. */
inline int gx_geterrora(int *code, char *string, int maxlen) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETERRORA me;
	int err_code;
	me.string = string;
	me.maxlen = maxlen;
	err_code = gx_call(nullhandle, GX_CALL_GETERRORA, &me);
	if(code) *code = me.code;
	return err_code;
}
/******************************************************************************/

#ifdef __cplusplus
/** Usable in C++. It is the same function as the \ref gx_geterrora.
 *
 * @param code The function will update it with the error code (Can be NULL).
 * @param string Memory pointer where the function writes the descriptive text
 *             of the error. Can be NULL, in that case there is no description.
 * @param maxlen Length of the memory area in characters (not bytes).
 * @return The error code. */
inline int gx_geterror(int *code, char *string = (char *)0, int maxlen = 0) {
	return gx_geterrora(code, string, maxlen);
}
#endif
#endif
/******************************************************************************/
/** You can query the error code with this function.
 *
 * @return The error code. */
inline int gx_geterrorcode(void) {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_GETERROR, (void *)0);
}
/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_geterrorcode().
 *
 * @return The error code. */
inline int gx_geterror(void) {
	return gx_geterrorcode();
}
#endif

/******************************************************************************/
/** Updates a thread-local error buffer (Unicode version).
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorfv(int flags, int code, const wchar_t *wformat, va_list args) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_SETERROR se;
	int st;
	se.flags = flags;
	se.code = code;
	se.appformat = wformat;
	if(wformat) va_copy(se.arguments, args);
	st = gx_call(nullhandle, GX_CALL_SETERROR, &se);
	if(wformat) va_end(se.arguments);
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorfv().
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorv(int flags, int code, const wchar_t *wformat, va_list args) {
	return gx_seterrorfv(flags, code, wformat, args);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Updates a thread-local error buffer (ASCII version).
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorafv(int flags, int code, const char *wformat, va_list args) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_SETERRORA se;
	int st;
	se.flags = flags;
	se.code = code;
	se.appformat = wformat;
	if(wformat) va_copy(se.arguments, args);
	st = gx_call(nullhandle, GX_CALL_SETERRORA, &se);
	if(wformat) va_end(se.arguments);
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorafv().
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorv(int flags, int code, const char *wformat, va_list args) {
	return gx_seterrorafv(flags, code, wformat, args);
}
#endif
#endif
/******************************************************************************/
/** Clears and updates a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorv(int code, const wchar_t *wformat, va_list args) {
	return gx_seterrorfv(_GX_ERR_FLAG_CLEAR, code, wformat, args);
}

#ifndef ANDROID
/******************************************************************************/
/** Clears and updates a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorav(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_CLEAR, code, wformat, args);
}

#ifdef __cplusplus
/******************************************************************************/
/** Usable in C++. It is the same function as the gx_seterrorav().
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorv(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_CLEAR, code, wformat, args);
}
#endif
#endif
/******************************************************************************/
/** Appends a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderrorv(int code, const wchar_t *wformat, va_list args) {
	return gx_seterrorfv(_GX_ERR_FLAG_APPEND, code, wformat, args);
}

#ifndef ANDROID
/******************************************************************************/
/** Appends a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderrorav(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_APPEND, code, wformat, args);
}

#ifdef __cplusplus
/******************************************************************************/
/** Usable in C++. It is the same function as the gx_appenderrorav().
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderrorv(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_APPEND, code, wformat, args);
}
#endif
#endif
/******************************************************************************/
/** Prepends a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerrorv(int code, const wchar_t *wformat, va_list args) {
	return gx_seterrorfv(_GX_ERR_FLAG_PREPEND, code, wformat, args);
}

#ifndef ANDROID
/******************************************************************************/
/** Prepends a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerrorav(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_PREPEND, code, wformat, args);
}

#ifdef __cplusplus
/******************************************************************************/
/** Usable in C++. It is the same function as the gx_prependerrorav().
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param args  Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerrorv(int code, const char *wformat, va_list args) {
	return gx_seterrorafv(_GX_ERR_FLAG_PREPEND, code, wformat, args);
}
#endif
#endif
/******************************************************************************/
/** Updates a thread-local error buffer with variable number of arguments (...).
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for printf).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorf(int flags, int code, const wchar_t *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorfv(flags, code, wformat, args);
	va_end(args);
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorf().
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for printf).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterror(int flags, int code, const wchar_t *wformat = (const wchar_t *)0, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorfv(flags, code, wformat, args);
	va_end(args);
	return st;
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Updates a thread-local error buffer with variable number of arguments (...) (ASCII version).
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for printf).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterroraf(int flags, int code, const char *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorafv(flags, code, wformat, args);
	va_end(args);
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorf().
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for printf).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterror(int flags, int code, const char *wformat = (const char *)0, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorafv(flags, code, wformat, args);
	va_end(args);
	return st;
}
#endif
#endif
/******************************************************************************/
/** Clears a thread-local error buffer.
 *
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_clearerror(void) {
	return gx_seterrorf(_GX_ERR_FLAG_CLEAR, 0, L"");
}

/******************************************************************************/
/** Updates a thread-local error buffer with flags and error code.
 *
 * @param flags Clear/Insert/Append mode ( see \ref GX_ERR_FLAG_CLEAR, \ref GX_ERR_FLAG_APPEND,
 *              \ref GX_ERR_FLAG_PREPEND, \ref GX_ERR_FLAG_APPMODE, \ref GX_ERR_FLAG_LOCAL )
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorcodef(int flags, int code) {
	return gx_seterrorf(flags, code, L"");
}

/******************************************************************************/
/** Updates a thread-local error buffer with error code.
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrorcode(int code) {
	return gx_seterrorf(_GX_ERR_FLAG_CLEAR, code, L"");
}

/******************************************************************************/
/** Appends a thread-local error buffer with error code.
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderrorcode(int code) {
	return gx_seterrorf(_GX_ERR_FLAG_APPEND, code, L"");
}

/******************************************************************************/
/** Prepends a thread-local error buffer with error code.
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerrorcode(int code) {
	return gx_seterrorf(_GX_ERR_FLAG_PREPEND, code, L"");
}

/******************************************************************************/
/** Clears and updates a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string. (like for wprintf, use %hs and %ls instead of %s)
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterror(int code, const wchar_t *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorv(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorcode() (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterror(int code) {
	return gx_seterrorcode(code);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Clears and updates a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterrora(int code, const char *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_seterrorav(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrora() (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_seterror(int code, const char *wformat, ...) {
	va_list args;
	va_start(args, wformat);
	int st = gx_seterrorav(code, wformat, args);
	va_end(args);
	return st;
}
#endif
#endif

/******************************************************************************/
/** Appends a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderror(int code, const wchar_t *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_appenderrorv(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_appenderrorcode() (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderror(int code) {
	return gx_appenderrorcode(code);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Appends a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderrora(int code, const char *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_appenderrorav(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorv() (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_appenderror(int code, const char *wformat, ...) {
	va_list args;
	va_start(args, wformat);
	int st = gx_appenderrorav(code, wformat, args);
	va_end(args);
	return st;
}
#endif
#endif

/******************************************************************************/
/** Prepends a thread-local error buffer (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerror(int code, const wchar_t *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_prependerrorv(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_prependerrorcode() (Unicode version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerror(int code) {
	return gx_prependerrorcode(code);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Prepends a thread-local error buffer (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerrora(int code, const char *wformat, ...) {
	va_list args;
	int st;
	va_start(args, wformat);
	st = gx_prependerrorav(code, wformat, args);
	va_end(args);
	return st;
}

/******************************************************************************/
#ifdef __cplusplus
/** Usable in C++. It is the same function as the gx_seterrorv() (ASCII version).
 *
 * @param code  Error code (Specified in gxerror.h or error codes also used
 *              in modules or system).
 * @param wformat Format string (like for wprintf, use %hs and %ls instead of %s).
 * @param ...   Arguments for format strings.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_prependerror(int code, const char *wformat, ...) {
	va_list args;
	va_start(args, wformat);
	int st = gx_prependerrorv(code, wformat, args);
	va_end(args);
	return st;
}
#endif
#endif
/******************************************************************************/
/** Updates the error table in the memory.
 *
 * @param nitems Number of items in the table.
 * @param items Items of the table.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_updateerrtable(int nitems, const gxERRITEM *items) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEERRTABLE ut;
	ut.nitems = nitems;
	ut.items = items;
	return gx_call(nullhandle, GX_CALL_UPDATEERRTABLE, &ut);
}

/******************************************************************************/
/** Pushes the error code and string to the error stack.
 *
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_pusherror(void) {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_PUSHERROR, (void *)0);
}

/******************************************************************************/
/** Pops the error code and string from the error stack.
 *
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_poperror(void) {
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_POPERROR, (void *)0);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/*******************************************************************************
 * DEVICE HANDLING
 ******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_device
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Lists the available GX devices (Unicode version).
 *
 * @param nitems Number of items in the array. On input set the maximal size of
 *               the array.  The function will updates it with the number of the
 *               devices found.
 * @param items  Pointer to the items of the array.
 * @param flags  Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_listdevices(int *nitems, GX_DEVICE_INFO *items,
				unsigned int flags GX_DEFARG(0), GX_DEVICE_INFO *filter GX_DEFARG(0)) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_LISTDEVICES pr;
	int st;

	assert(nitems && items);
	memset(&pr, 0, sizeof(pr));
	pr.flags = flags;
	if(filter) memcpy(&pr.filter, filter, sizeof(pr.filter));
	pr.maxitems = *nitems;
	pr.items = items;
	st = gx_call(nullhandle, GX_CALL_LISTDEVICES, &pr);
	if(st) *nitems = pr.maxitems;
	return st;
}

#ifndef ANDROID
/******************************************************************************/
/** Lists the available GX devices (ASCII version).
 *
 * @param nitems Number of items in the array. On input set the maximal size of
 *               the array.  The function will updates it with the number of the
 *               devices found.
 * @param items  Pointer to items of the array.
 * @param flags  Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_listdevicesa(int *nitems, GX_DEVICE_INFOA *items,
				unsigned int flags, GX_DEVICE_INFOA *filter) {

	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_LISTDEVICESA pr;
	int st;

	assert(nitems && items);
	memset(&pr, 0, sizeof(pr));
	pr.flags = flags;
	if(filter) memcpy(&pr.filter, filter, sizeof(pr.filter));
	pr.maxitems = *nitems;
	pr.items = items;
	st = gx_call(nullhandle, GX_CALL_LISTDEVICESA, &pr);
	if(st) *nitems = pr.maxitems;
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Lists the available GX devices (ASCII version).
 *
 * @param nitems Number of items in the array. On input set the maximal size of
 *               the array.  The function will updates it with the number of the
 *               devices found.
 * @param items  Pointer to items of the array.
 * @param flags  Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_listdevices(int *nitems, GX_DEVICE_INFOA *items,
			unsigned int flags = 0, GX_DEVICE_INFOA *filter = 0) {
	return gx_listdevicesa(nitems, items, flags, filter);
}
#endif

/******************************************************************************/
/** Selects and opens a device in the GX system (ASCII version).
 *
 * @param handle The function will update it with the opened handle.
 * @param info The function will fill it with the information of the opened device.
 * @param flags Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure. You can pass NULL to it (if the flags field is zero too).
 * @param nproperties Number of properties of the device. It can be zero.
 * @param properties Pointer to properties of the device. It can be NULL.
 * @param timeoutms Timeout in milliseconds.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_opendevicea(gxHANDLE *handle, GX_DEVICE_INFOA *info,
				unsigned int flags, GX_DEVICE_INFOA *filter,
				int nproperties, const char **properties,
				int timeoutms) {

	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_OPENDEVICEA pr;
	int st;

	assert(handle);
	pr.flags = flags;
	if(filter) memcpy(&pr.filter, filter, sizeof(pr.filter));
	pr.properties = properties;
	pr.nproperties = nproperties;
	pr.timeoutms = timeoutms;
	st = gx_call(nullhandle, GX_CALL_OPENDEVICEA, &pr);
	if(st) {
		*handle = pr.handle;
		if(info) memcpy(info, &pr.info, sizeof(GX_DEVICE_INFOA));
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Selects and opens a device in the GX system (ASCII version).
 *
 * @param handle The function will update it with the opened handle.
 * @param info The function will fill it with the information of the opened device.
 * @param flags Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure. You can pass NULL to it (if the flags field is zero too).
 * @param nproperties Number of properties of the device. It can be zero.
 * @param properties Pointer to properties of the device. It can be NULL.
 * @param timeoutms Timeout in milliseconds.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_opendevice(gxHANDLE *handle, GX_DEVICE_INFOA *info,
				unsigned int flags = 0, GX_DEVICE_INFOA *filter = 0,
				int nproperties = 0, const char **properties = 0,
				int timeoutms = 0) {

	return gx_opendevicea(handle, info, flags, filter,
					nproperties, properties, timeoutms);
}
#endif
#endif
/******************************************************************************/
/** Selects and opens a device in the GX system (Unicode version).
 *
 * @param handle The function will update it with the opened handle.
 * @param info The function will fill it with the information of the opened device.
 * @param flags Flags for the filter structure (see \ref GX_DEVICE_FLAGS).
 * @param filter The filter structure. You can pass NULL to it (if the flags field is zero too).
 * @param nproperties Number of properties of the device. It can be zero.
 * @param properties Pointer to properties of the device. It can be NULL.
 * @param timeoutms Timeout in milliseconds.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_opendevice(gxHANDLE *handle, GX_DEVICE_INFO *info,
				unsigned int flags GX_DEFARG(0), GX_DEVICE_INFO *filter GX_DEFARG(0),
				int nproperties GX_DEFARG(0), const wchar_t **properties GX_DEFARG(0),
				int timeoutms GX_DEFARG(0)) {
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_OPENDEVICE pr;
	int st;

	assert(handle);
	pr.flags = flags;
	if(filter) memcpy(&pr.filter, filter, sizeof(pr.filter));
	pr.properties = properties;
	pr.nproperties = nproperties;
	pr.timeoutms = timeoutms;
	st = gx_call(nullhandle, GX_CALL_OPENDEVICE, &pr);
	if(st) {
		*handle = pr.handle;
		if(info) memcpy(info, &pr.info, sizeof(GX_DEVICE_INFO));
	}
	return st;
}

/******************************************************************************/
/** Returns information about the GX system.
 *
 * @param info	Buffer for the result.
 *				Before calling this function, do not forget to set the \c size member of the structure.
 *				A non 0 value specifies the number of bytes required.
 *				If it is set to 0, the function returns the proper size that can be used in a successive call.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getsysteminfo(GX_SYSTEM_INFO *info) {
	gxHANDLE nullhandle = { 0 };
	assert(info);
	return gx_call(nullhandle, GX_CALL_GETSYSTEMINFO, info);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/******************************************************************************/
#endif /* GX_SWIGIF NO_GX_FUNCTIONS )*/
/******************************************************************************/
/******************************************************************************/

#ifdef GX_DOTNET
	#pragma managed
#endif

#if !defined(NO_GX_CLASSES) && !defined(ANDROID)	/*(*/

/*******************************************************************************
 * Classes
 ******************************************************************************/

#if !defined(GX_EXT_MODULE) && !defined(__BORLANDC__)	/*(*/

#ifdef GX_UNICODE	/*(*/

/******************************************************************************/
/** \brief Class for the device information (Unicode version). */
#if !defined(GX_DOTNET)
GX_CLASS gxDeviceInfo : private GX_DEVICE_INFO {
#else
GX_CLASS gxDeviceInfo
#ifdef GX_DOTNET
: public System::IDisposable
#endif
{	/*}*/
private:
	gxString type;
	gxString devname;
	unsigned int serial;
	int priority;
#endif
public:
	/** Initializes the class. */
	inline gxDeviceInfo() {
#if !defined(GX_DOTNET)
		memset(static_cast<GX_DEVICE_INFO *>(this), 0, sizeof(GX_DEVICE_INFO));
#else
		type = GX_NULLPTR;
		devname = GX_NULLPTR;
		serial = 0;
		priority = 0;
#endif
	}

	/** Copy constructor.
	 * @param src The source information structure. */
	inline gxDeviceInfo(GX_CONST gxDeviceInfo GX_REF_CLASS(src)) {
#if !defined(GX_DOTNET)
		memcpy(static_cast<GX_DEVICE_INFO *>(this), static_cast<const GX_DEVICE_INFO *>(&src),
				sizeof(GX_DEVICE_INFO));
#else
		SetType(src GX_M GetType());
		SetName(src GX_M GetName());
		SetSerial(src GX_M GetSerial());
		SetPriority(src GX_M GetPriority());
#endif
	}

	/** Destructs the class. */
	inline ~gxDeviceInfo() {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxDeviceInfo() {
		_Dispose();
	}
#else
	/** It disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);//do not call it from a destructor explicitly!
#endif
		_Dispose();
		/** no base class */
	}
#endif

private:
	inline void _Dispose(void) {
#if defined(GX_DOTNET)
		type = GX_NULLPTR;
		devname = GX_NULLPTR;
#endif
	}
public:


#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Convert the class into the pointer of the GX_DEVICE_INFO. */
	inline operator GX_DEVICE_INFO *() {
		return static_cast<GX_DEVICE_INFO *>(this);
	}
	/** Sets the type field.
	 *
	 * @param _type Type of the device. */
	inline void SetType(const wchar_t *_type) {
		memset(type, 0, sizeof(type));
		gx_wcsncpy(type, _type ? _type : L"", sizeof(type)/sizeof(wchar_t));
	}
	/** Sets the name field.
	 *
	 * @param _devname Name of the device. */
	inline void SetName(const wchar_t *_devname) {
		memset(devname, 0, sizeof(devname));
		gx_wcsncpy(devname, _devname ? _devname : L"", sizeof(devname)/sizeof(wchar_t));
	}
#endif	/*)*/
	/** Sets the serial field.
	 *
	 * @param _serial Serial of the device. */
	inline void SetSerial(unsigned int _serial) {
		serial = _serial;
	}
	/** Sets the priority field.
	 *
	 * @param _priority Priority level of the device. */
	inline void SetPriority(int _priority) {
		priority = _priority;
	}

	/** Retrieves the serial field.
	 *
	 * @return The serial number of the device. */
	inline unsigned int GetSerial(void) GX_CONST {
		return serial;
	}
	/** Retrieves the priority field.
	 *
	 * @return The priority level of the device. */
	inline int GetPriority(void) GX_CONST {
		return priority;
	}

	/** Updates the type field.
	 *
	 * @param _type Type of the device. */
	inline void SetType(gxInStr _type) {
#if !defined(GX_DOTNET)
		GX_GETSTRING(__type, _type);
		memset(type, 0, sizeof(type));
		gx_wcsncpy(type, __type ? __type : L"", sizeof(type)/sizeof(wchar_t));
#else
		type = _type;
#endif
	}

	/** Updates the name field.
	 *
	 * @param _devname Name of the device. */
	inline void SetName(gxInStr _devname) {
#if !defined(GX_DOTNET)
		GX_GETSTRING(__devname, _devname);
		memset(devname, 0, sizeof(devname));
		gx_wcsncpy(devname, __devname ? __devname : L"", sizeof(devname)/sizeof(wchar_t));
#else
		devname = _devname;
#endif
	}

	/** Retrieves the type field.
	 *
	 * @return Type of the device. */
	inline gxOutStr GetType(void) GX_CONST {
#if !defined(GX_DOTNET)
		wchar_t buffer[1+(sizeof(type)/sizeof(wchar_t))];
		memcpy(buffer, type, sizeof(type));
		buffer[sizeof(type)/sizeof(wchar_t)] = 0;
		return GX_PUTSTRING(buffer);
#else
		return type;
#endif
	}

	/** Retrieves the name field.
	 *
	 * @return Name of the device. */
	inline gxOutStr GetName(void) GX_CONST {
#if !defined(GX_DOTNET)
		wchar_t buffer[1+(sizeof(devname)/sizeof(wchar_t))];
		memcpy(buffer, devname, sizeof(devname));
		buffer[sizeof(devname)/sizeof(wchar_t)] = 0;
		return GX_PUTSTRING(buffer);
#else
		return devname;
#endif
	}
};

#endif	/* GX_UNICODE )*/

/******************************************************************************/

#ifdef GX_ASCII	/*(*/
/******************************************************************************/
/** \brief Class for the device information (ASCII version). */
GX_CLASS gxDeviceInfoA : private GX_DEVICE_INFOA {
public:
	/** Initializes the class. */
	inline gxDeviceInfoA() {
		memset(static_cast<GX_DEVICE_INFOA *>(this), 0, sizeof(GX_DEVICE_INFOA));
	}

	/** Copy constructor.
	 *
	 * @param src The source information structure. */
	inline gxDeviceInfoA(GX_CONST gxDeviceInfoA GX_REF_CLASS(src)) {
		memcpy(static_cast<GX_DEVICE_INFOA *>(this), static_cast<const GX_DEVICE_INFOA *>(&src),
				sizeof(GX_DEVICE_INFOA));
	}

#if !defined(GX_SWIGIF)
	/** Convert the class into the pointer of the GX_DEVICE_INFO. */
	inline operator GX_DEVICE_INFOA *() {
		return static_cast<GX_DEVICE_INFOA *>(this);
	}
	/** Sets the type field.
	 *
	 * @param _type Type of the device. */
	inline void SetType(const char *_type) {
		memset(type, 0, sizeof(type));
		gx_strncpy(type, _type ? _type : "", sizeof(type));
	}
	/** Sets the name field.
	 *
	 * @param _devname Name of the device. */
	inline void SetName(const char *_devname) {
		memset(devname, 0, sizeof(devname));
		gx_strncpy(devname, _devname ? _devname : "", sizeof(devname));
	}
#endif	/* GX_SWIGIF */

	/** Sets the serial field.
	 *
	 * @param _serial Serial of the device. */
	inline void SetSerial(unsigned int _serial) {
		serial = _serial;
	}
	/** Sets the priority field.
	 *
	 * @param _priority Priority level of the device. */
	inline void SetPriority(int _priority) {
		priority = _priority;
	}

	/** Retrieves the serial field.
	 *
	 * @return The serial number of the device. */
	inline unsigned int GetSerial(void) GX_CONST {
		return serial;
	}
	/** Retrieves the priority field.
	 * @return The priority level of the device. */
	inline int GetPriority(void) GX_CONST {
		return priority;
	}

	/** Updates the type field.
	 *
	 * @param _type Type of the device. */
	inline void SetType(gxInAStr _type) {
		GX_GETASTRING(__type, _type);
		memset(type, 0, sizeof(type));
		gx_strncpy(type, __type ? __type : "", sizeof(type));
	}

	/** Updates the name field.
	 *
	 * @param _devname Name of the device. */
	inline void SetName(gxInAStr _devname) {
		GX_GETASTRING(__devname, _devname);
		memset(devname, 0, sizeof(devname));
		gx_strncpy(devname, __devname ? __devname : "", sizeof(devname));
	}

	/** Retrieves the type field.
	 *
	 * @return Type of the device. */
	inline gxOutAStr GetType(void) GX_CONST {
		char buffer[1+sizeof(type)];
		memcpy(buffer, type, sizeof(type));
		buffer[sizeof(type)] = 0;
		return GX_PUTASTRING(buffer);
	}

	/** Retrieves the name field.
	 *
	 * @return Name of the device. */
	inline gxOutAStr GetName(void) GX_CONST {
		char buffer[1+sizeof(devname)];
		memcpy(buffer, devname, sizeof(devname));
		buffer[sizeof(devname)] = 0;
		return GX_PUTASTRING(buffer);
	}
};
#endif	/* GX_ASCII )*/

#endif	/* GX_EXT_MODULE __BORLANDC__ )*/
/******************************************************************************/

/******************************************************************************/
#ifdef GX_DOTNET	/*(*/

#ifndef GX_EXT_MODULE
/** The exception thrown when a GX error occurs. */
GX_CLASS gxException : public System::ApplicationException {
public:
	/** Initializes the class. */
	inline gxException();
};
#endif

/** The exception thrown when a GX error occurs. */
typedef GX_INDIRECTION1(gx::gxException) gxError;

#else	/*)(*/

#ifndef GX_EXT_MODULE	/*(*/
/** Class for the error handling.
 *
 * If an exception occurred, this gxError class will be thrown.
 * It doesn't store the error string or error code. All the errors are thread-local
 * in the GX system. The system preserves the error while new ones doesn't arrives. */
class gxException {
public:

	/** Getting the error code.
	 *
	 * @return The error code. */
	inline int GetErrorCode(void) {
		return gx_geterrorcode();
	}

#if !defined(GX_SWIGIF) /*(*/
	/** Getting the error code and string in unicode format.
	 *
	 * @param code Pointer where the function writes the error code.
	 * @param string Pointer to a memory area in which the function writes the string.
	 * @param maxlen Length of the memory area in characters.
	 * @return The error code (Yes, it is the code not status). */
	inline int GetError(int *code, wchar_t *string, int maxlen) {
		return gx_geterror(code, string, maxlen);
	}
	/** Getting the error code and string in ASCII format.
	 *
	 * @param code Pointer where the function writes the error code.
	 * @param string Pointer to a memory area in which the function writes the string.
	 * @param maxlen Length of the memory area in characters.
	 * @return The error code (Yes, it is the code not status). */
	inline int GetError(int *code, char *string, int maxlen) {
		return gx_geterrora(code, string, maxlen);
	}
#endif	/*)*/
#ifdef GX_UNICODE
	/** Getting the error string in unicode format.
	 *
	 * @return The error string. */
	inline gxOutStr GetErrorString(void) {
		wchar_t errbuf[GX_MAXLEN_ERRVALUE+1];
		gx_geterror(0, errbuf, GX_MAXLEN_ERRVALUE);
		errbuf[GX_MAXLEN_ERRVALUE] = 0;
		return GX_PUTSTRING(errbuf);
	}
#endif
#ifdef GX_ASCII
	/** Getting the error string in ASCII format.
	 *
	 * @return The error string. */
	inline gxOutAStr GetErrorStringA(void) {
		char errbuf[GX_MAXLEN_ERRVALUE+1];
		gx_geterrora(0, errbuf, GX_MAXLEN_ERRVALUE);
		errbuf[GX_MAXLEN_ERRVALUE] = 0;
		return GX_PUTASTRING(errbuf);
	}
#endif
};
#endif	/*)*/

/** The exception thrown when a GX error occurs. */
typedef gxException gxError;
#endif	/*)*/

#ifndef GX_EXT_MODULE	/*(*/
/******************************************************************************/
/** \brief Class for the GX-system specific operations. */
GX_CLASS gxSystem {
public:

	/***************************************************************************
	 * Set error
	 **************************************************************************/

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Updates the thread-local error in the GX system (Unicode version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string. (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetErrorv(int flags, int code, const wchar_t *format, va_list args) {
		return gx_seterrorfv(flags, code, format, args) ? true : false;
	}
	/** Overwrites the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetErrorv(int code, const wchar_t *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_CLEAR, code, format, args);
	}
	/** Appends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool AppendErrorv(int code, const wchar_t *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_APPEND, code, format, args);
	}
	/** Prepends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool PrependErrorv(int code, const wchar_t *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_PREPEND, code, format, args);
	}

	/** Updates the thread-local error in the GX system (Unicode version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetError(int flags, int code, const wchar_t *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = SetErrorv(flags, code, format, args);
		va_end(args);
		return ret;
	}

	/** Updates the thread-local error in the GX system (ASCII version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetErrorv(int flags, int code, const char *format, va_list args) {
		return gx_seterrorafv(flags, code, format, args) ? true : false;
	}
	/** Overwrites the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetErrorv(int code, const char *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_CLEAR, code, format, args);
	}
	/** Appends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool AppendErrorv(int code, const char *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_APPEND, code, format, args);
	}
	/** Prepends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param args Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool PrependErrorv(int code, const char *format, va_list args) {
		return SetErrorv(GX_ERR_FLAG_PREPEND, code, format, args);
	}

	/** Updates the thread-local error in the GX system (ASCII version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetError(int flags, int code, const char *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = SetErrorv(flags, code, format, args);
		va_end(args);
		return ret;
	}
#endif	/*)*/

#if !defined(GX_SWIG) && !defined(GX_DOTNET)	/*(*/
	/** Overwrites the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetError(int code, const wchar_t *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = SetErrorv(code, format, args);
		va_end(args);
		return ret;
	}
	/** Overwrites the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool SetError(int code, const char *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = SetErrorv(code, format, args);
		va_end(args);
		return ret;
	}
	/** Appends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool AppendError(int code, const wchar_t *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = AppendErrorv(code, format, args);
		va_end(args);
		return ret;
	}
	/** Appends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool AppendError(int code, const char *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = AppendErrorv(code, format, args);
		va_end(args);
		return ret;
	}
	/** Prepends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool PrependError(int code, const wchar_t *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = PrependErrorv(code, format, args);
		va_end(args);
		return ret;
	}
	/** Prepends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param format The format string (like for wprintf, use %hs and %ls instead of %s).
	 * @param ... Arguments for the format string (like for wprintf).
	 * @return On success: non-zero. */
	inline static bool PrependError(int code, const char *format, ...) {
		va_list args;
		va_start(args, format);
		bool ret = PrependErrorv(code, format, args);
		va_end(args);
		return ret;
	}
#endif	/*)*/

	/** Clears the thread-local error buffer in the GX system.
	 *
	 * @return On success: non-zero. */
	inline static bool ClearError(void) {
		return gx_clearerror() ? true : false;
	}

	/** Overwrites the thread-local error in the GX system.
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @return On success: non-zero. */
	inline static bool SetError(int code) {
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_CLEAR, code, L"")!=0;
	}
	/** Appends the thread-local error in the GX system.
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @return On success: non-zero. */
	inline static bool AppendError(int code) {
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_APPEND, code, L"")!=0;
	}
	/** Prepends the thread-local error in the GX system.
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @return On success: non-zero. */
	inline static bool PrependError(int code) {
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_PREPEND, code, L"")!=0;
	}

#ifdef GX_UNICODE	/*(*/
	/** Updates the thread-local error in the GX system (Unicode version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool SetError(int flags, int code, gxInStr str) {
		GX_GETSTRING(_str, str);
		return gx_seterrorf(flags, code, L"%ls", _str) ? true : false;
	}
	/** Overwrites the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool SetError(int code, gxInStr str) {
		GX_GETSTRING(_str, str);
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_CLEAR, code, L"%ls", _str) ? true : false;
	}
	/** Appends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool AppendError(int code, gxInStr str) {
		GX_GETSTRING(_str, str);
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_APPEND, code, L"%ls", _str) ? true : false;
	}
	/** Prepends the thread-local error in the GX system (Unicode version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool PrependError(int code, gxInStr str) {
		GX_GETSTRING(_str, str);
		return gx_seterrorf((int)GX_ENUM_PATH(GX_ERROR_FLAGS) GX_ERR_FLAG_PREPEND, code, L"%ls", _str) ? true : false;
	}
#endif	/*)*/
#ifdef GX_ASCII	/*(*/
	/** Updates the thread-local error in the GX system (ASCII version).
	 *
	 * @param flags Modifier flags (see \ref GX_ERROR_FLAGS).
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool SetError(int flags, int code, gxInAStr str) {
		GX_GETASTRING(_str, str);
		return gx_seterrorf(flags, code, L"%hs", _str) ? true : false;
	}
	/** Overwrites the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool SetError(int code, gxInAStr str) {
		GX_GETASTRING(_str, str);
		return gx_seterrorf(GX_ERR_FLAG_CLEAR, code, L"%hs", _str) ? true : false;
	}
	/** Appends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool AppendError(int code, gxInAStr str) {
		GX_GETASTRING(_str, str);
		return gx_seterrorf(GX_ERR_FLAG_APPEND, code, L"%hs", _str) ? true : false;
	}
	/** Prepends the thread-local error in the GX system (ASCII version).
	 *
	 * @param code The error code (see \ref GX_ERROR_CODES).
	 * @param str The extension string.
	 *			(The result will be the system's string plus your extension string.)
	 * @return On success: non-zero. */
	inline static bool PrependError(int code, gxInAStr str) {
		GX_GETASTRING(_str, str);
		return gx_seterrorf(GX_ERR_FLAG_PREPEND, code, L"%hs", _str) ? true : false;
	}
#endif	/*)*/

	/*******************************************************************************
	 * Get error
	 ******************************************************************************/

	/** Getting the error code.
	 *
	 * @return The error code. */
	inline static int GetErrorCode(void) {
		return gx_geterrorcode();
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Getting the error code and string in unicode format.
	 *
	 * @param code Pointer where the function writes the error code.
	 * @param string Pointer to a memory area in which the function writes the string.
	 * @param maxlen Length of the memory area in characters.
	 * @return The error code (Yes, it is the code not status). */
	inline static int GetError(int *code, wchar_t *string, int maxlen) {
		return gx_geterror(code, string, maxlen);
	}
	/** Getting the error code and string in ASCII format.
	 *
	 * @param code Pointer where the function writes the error code.
	 * @param string Pointer to a memory area in which the function writes the string.
	 * @param maxlen Length of the memory area in characters.
	 * @return The error code (Yes, it is the code not status). */
	inline static int GetError(int *code, char *string, int maxlen) {
		return gx_geterrora(code, string, maxlen);
	}
#endif	/*)*/
#ifdef GX_UNICODE
	/** Getting the error string in unicode format.
	 *
	 * @return The error string. */
	inline static gxOutStr GetErrorString(void) {
		wchar_t errbuf[GX_MAXLEN_ERRVALUE+1];
		gx_geterror(0, errbuf, GX_MAXLEN_ERRVALUE);
		errbuf[GX_MAXLEN_ERRVALUE] = 0;
#ifndef GX_DOTNET_20
		return GX_PUTSTRING(errbuf);
#else
		return GX_PUTSTRING(GX_PUTPTR(errbuf));
#endif
	}
#endif
#ifdef GX_ASCII
	/** Getting the error string in ASCII format.
	 *
	 * @return The error string. */
	inline static gxOutAStr GetErrorStringA(void) {
		char errbuf[GX_MAXLEN_ERRVALUE+1];
		gx_geterrora(0, errbuf, GX_MAXLEN_ERRVALUE);
		errbuf[GX_MAXLEN_ERRVALUE] = 0;
		return GX_PUTASTRING(errbuf);
	}
#endif

#if defined(GX_UNICODE) && !defined(GX_DOTNET) && !defined(GX_SWIG) && !defined(__BORLANDC__)	/*(*/
	/** This function returns a filtered list of the available GX devices (Unicode version).
	 *
	 * @param flags Flags for filter class.
	 * @param filter The filter class.
	 * @return The array of the devices found. If an error occurred the function throws an exception. */
	inline static std::vector<gxDeviceInfo> ListDevices(unsigned int flags, gxDeviceInfo GX_REF_CLASS(filter)) gxFuncThrowsError {
		const int maxarray = 100;
		std::vector<gxDeviceInfo> ret;
		GX_DEVICE_INFO *array = (GX_DEVICE_INFO *)malloc(sizeof(GX_DEVICE_INFO)*maxarray);
		if(!array) {
			SetError(GX_ENOMEM);
			gxthrow;
		}
		int ndevices = maxarray;
		int st = gx_listdevices(&ndevices, array, flags, filter);
		if(!st) {
			free(array);
			gxthrow;
		}
		if(ndevices) {
			gxtry {
				ret.resize(ndevices);
				for(int ix = 0; ix < ndevices; ix++) {
					ret[ix].SetType(array[ix].type);
					ret[ix].SetName(array[ix].devname);
					ret[ix].SetSerial(array[ix].serial);
					ret[ix].SetPriority(array[ix].priority);
				}
			} gxcatch(...) {
				free(array);
				__gxthrow;
			}
		}
		free(array);
		return ret;
	}
#endif /* GX_UNICODE GX_DOTNET GX_SWIG __BORLANDC__ )*/

#if defined(GX_ASCII) && !defined(GX_SWIG) && !defined(__BORLANDC__)	/*(*/
	/** This function returns a filtered list of the available GX devices (ASCII version).
	 *
	 * @param flags Flags for filter class.
	 * @param filter The filter class.
	 * @return The array of the devices found. If an error occurred the function throws an exception. */
	inline static std::vector<gxDeviceInfoA> ListDevicesA(unsigned int flags, gxDeviceInfoA GX_REF_CLASS(filter)) gxFuncThrowsError {
		const int maxarray = 100;
		std::vector<gxDeviceInfoA> ret;
		GX_DEVICE_INFOA *array = (GX_DEVICE_INFOA *)malloc(sizeof(GX_DEVICE_INFOA)*maxarray);
		if(!array) {
			SetError(GX_ENOMEM);
			gxthrow;
		}
		int ndevices = maxarray;
		int st = gx_listdevicesa(&ndevices, array, flags, filter);
		if(!st) {
			free(array);
			gxthrow;
		}
		if(ndevices) {
			gxtry {
				ret.resize(ndevices);
				for(int ix = 0; ix < ndevices; ix++) {
					ret[ix].SetType(array[ix].type);
					ret[ix].SetName(array[ix].devname);
					ret[ix].SetSerial(array[ix].serial);
					ret[ix].SetPriority(array[ix].priority);
				}
			} gxcatch(...) {
				free(array);
				__gxthrow;
			}
		}
		free(array);
		return ret;
	}
#endif	/* GX_ASCII GX_SWIG __BORLANDC__ ) */

#if defined(GX_DOTNET)	/*(*/
	/** This function returns a filtered list of the available GX devices.
	 *
	 * @param flags Flags for filter class.
	 * @param filter The filter class.
	 * @return The array of founded devices. If an error occurred the function thrown an exception. */
	inline static gxSysArray ListDevices(unsigned int flags, GX_INDIRECTION_GC(gxDeviceInfo, filter)) gxFuncThrowsError {
		const int maxarray = 100;
		gxSysArray ret = GX_NULLPTR;

		GX_DEVICE_INFO *array = (GX_DEVICE_INFO *)malloc(sizeof(GX_DEVICE_INFO)*maxarray);
		if(!array) {
			SetError((int)GX_ENUM_PATH(GX_ERROR_CODES) GX_ENOMEM);
			gxthrow;
		}

		int ndevices = maxarray;
		gx::GX_DEVICE_INFO _filter;
		if(filter) {
			System::IntPtr wname = System::Runtime::InteropServices::Marshal::StringToBSTR(filter->GetType());
			if(wname.ToPointer()) {
				gx_wcsncpy(_filter.type, (const wchar_t *)wname.ToPointer(), sizeof(_filter.type)/sizeof(wchar_t));
			}
			System::Runtime::InteropServices::Marshal::FreeBSTR(wname);
			wname = System::Runtime::InteropServices::Marshal::StringToBSTR(filter->GetName());
			if(wname.ToPointer()) {
				gx_wcsncpy(_filter.devname, (const wchar_t *)wname.ToPointer(), sizeof(_filter.devname)/sizeof(wchar_t));
			}
			System::Runtime::InteropServices::Marshal::FreeBSTR(wname);
		}

		int st = gx_listdevices(&ndevices, array, flags, &_filter);
		if(!st) {
			free(array);
			gxthrow;
		}

		ret = System::Array::CreateInstance(GX_TYPEID(gxDeviceInfo), ndevices);
		if(ndevices) {
			gxtry {
				for(int ix = 0; ix < ndevices; ix++) {
					GX_INDIRECTION_GC(gxDeviceInfo, d) = gxnew gxDeviceInfo;
					d->SetType(GX_MARSHALPTRTOSTRING2(array[ix].type, sizeof(array[ix].type)/sizeof(wchar_t)));
					d->SetName(GX_MARSHALPTRTOSTRING2(array[ix].devname, sizeof(array[ix].devname)/sizeof(wchar_t)));
					d->SetSerial(array[ix].serial);
					d->SetPriority(array[ix].priority);
					ret->SetValue(d, ix);
				}
			} gxcatch(...) {
				__gxthrow;
			}
		}
		free(array);
		return ret;
	}
#endif	/*)*/

	/** This function pushes the error code and string to the error stack.
	 *
	 * @return On success: non-zero. */
	inline static bool PushError(void) gxFuncThrowsError {
		bool ret = gx_pusherror() ? true : false;
		gxcondthrow(!ret);
		return ret;
	}

	/** This function pops the error code and string from the error stack.
	 *
	 * @return On success: non-zero. */
	inline static bool PopError(void) gxFuncThrowsError {
		bool ret = gx_poperror() ? true : false;
		gxcondthrow(!ret);
		return ret;
	}
	/** Returns information about the GX system.
	 * @param flag Flag to select the type of the information.
	 * @return The result depends on the flag parameter. In case of error an exception is thrown. */
	inline static int GetSystemInfo(GX_SYSINFO_FLAGS flag) gxFuncThrowsError {
		GX_SYSTEM_INFO	info;
		int	ret = 0;
		memset(&info,0,sizeof(info));
		info.size = sizeof(info);
		if (gx_getsysteminfo(&info)) {
			switch (flag) {
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_FREEFLOW: ret = info.cm_ff; break;
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_PARKING: ret = info.cm_park; break;
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_ACCR: ret = info.cm_accr ; break;
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_PARKINGLANE: ret = info.cm_pl; break;
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_FACE: ret = info.cm_face; break;
				case GX_ENUM_PATH(GX_SYSINFO_FLAGS) GX_SYSINFO_FLAG_PR: ret = info.pr; break;
			}
		} else {
			gxcondthrow(!ret);
		}
		return ret;
	}
};
#endif	/*)*/
/******************************************************************************/

#if defined(GX_DOTNET) && !defined(GX_EXT_MODULE)
/** Constructor implementation for the gxException class in the .net. */
inline gxException::gxException() : System::ApplicationException(gx::gxSystem::GetErrorString()) {
}
#endif

/******************************************************************************/

#ifndef GX_EXT_MODULE	/*(*/
/******************************************************************************/
#if !defined(GX_SWIG) && !defined(GX_DOTNET)	/*(*/
/** Class for global memory operations (Obsolete). */
class gxPtr {
private:
	void	*ptr;		/**< Pointer to the memory area. */

public:
	/** Initializes the class */
	inline gxPtr() {
		ptr = (void *)0;
	}

	/** Initializes the class and allocates memory with specified size in bytes.
	 *
	 * @param size Size of memory area. */
	inline gxPtr(int size) {
		ptr = (void *)0;
		bool st;
		st = Alloc(size);
		gxassert(st);
	}

	/** Desctructs the class. */
	inline ~gxPtr() {
		 _Dispose();
	}

private:
inline void _Dispose(void) {
		if(ptr) Free();
	}
public:
	/** Reallocates or frees a previously allocated memory area or allocates a new area.
	 *
	 * @param size Size of the new memory area in bytes. If it is zero it
	 *             frees the area.
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool Realloc(int size) gxFuncThrowsError {
		gxassert(size >= 0);
		GX_PARM_GLOBALREALLOC gr;
		gr.buffer = ptr;
		gr.size = size;
		gxHANDLE nullhandle = { 0 };
		int st = gx_call(nullhandle, GX_CALL_GLOBALREALLOC, &gr);
		if(!st) {
			gxthrow;
			return false;
		}
		ptr = gr.buffer;
		return true;
	}

	/** Reallocates a previously allocated memory area or allocates a new area.
	 *
	 * @param size Size of the new memory area in bytes.
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool Alloc(int size) gxFuncThrowsError {
		gxassert(size > 0);
		return Realloc(size);
	}


	/** Frees a previously allocated memory area.
	 *
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool Free(void) gxFuncThrowsError {
		return Realloc(0);
	}

	/** Gets the size of a previously allocated memory area in bytes.
	 *
	 * @return The size of a previously allocated memory area in bytes. */
	inline int Size(void) const gxFuncThrowsError {
		GX_PARM_GLOBALSIZE gs;
		gs.buffer = ptr;
		gxHANDLE nullhandle = { 0 };
		int st = gx_call(nullhandle, GX_CALL_GLOBALSIZE, &gs);
		if(!st) {
			gxthrow;
			return -1;
		}
		return gs.size;
	}

	/** Gets the pointer of the memory area.
	 *
	 * @return Pointer of the memory area. */
	inline void *Ptr(void) const {
		return ptr;
	}

	/** Gets the pointer of the memory area.
	 *
	 * @return Pointer of the memory area. */
	inline operator void *() const {
		return ptr;
	}

	/** Gets the pointer of the memory area.
	 *
	 * @return Pointer of the memory area. */
	inline operator const void *() const {
		return ptr;
	}
};
#endif	/* GX_SWIG && GX_DOTNET )*/
#endif	/* GX_EXT_MODULE )*/
/******************************************************************************/

/*******************************************************************************
 * Module handling
 ******************************************************************************/
#if !defined(GX_MANUAL)
#if !defined(GX_DOTNET)
	#define GX_GETHANDLE(name)	gxHANDLE name = *this
#else
	#define GX_GETHANDLE(name)	gxHANDLE name = { _handle }
#endif
#endif

#ifndef GX_EXT_MODULE	/*(*/

/** The handler class of the GX system.
 *
 * It is the base class for most of the other classes and can be used as handle
 * for the GX modules. */

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
class gxHandle : public gxHANDLE {
public:
	/** Initializes the class with the call-group code (Obsolete).
	 *
	 * Use the Open method instead of it.
	 *
	 * @param call_group Group call code (GX_CALL_GROUP_xxx). */
	inline gxHandle(int call_group) {
		handle = ((unsigned int)call_group >> 16);
	}
	/** Initializes the class with another handle structure.
	 *
	 * This function increases the reference counter and copies
	 * the source handle. If an error occurred, an exception is thrown.
	 *
	 * @param src The source handle. */
	inline gxHandle(gxHANDLE GX_REF_CLASS(src)) gxFuncThrowsError {
		handle = src.handle;
		if(IsValid()) {
			if(!gx_refhandle(*this)) {
				handle = 0;
				gxthrow;
			}
		}
	}
	/** Initializes the class with another handle class.
	 *
	 * This function increases the reference counter and copies
	 * the source handle. If an error occurred, an exception is thrown.
	 *
	 * @param src The source handle. */
	inline gxHandle(gxHandle GX_REF_CLASS(src)) gxFuncThrowsError {
		handle = src.handle;
		if(IsValid()) {
			if(!gx_refhandle(*this)) {
				handle = 0;
				gxthrow;
			}
		}
	}

#else	/* GX_SWIGIF GX_DOTNET )(*/

GX_CLASS gxHandle
#ifdef GX_DOTNET
: public System::IDisposable
#endif
{

#if !defined(GX_SWIGIF) /*(*/

#if defined(GX_DOTNET)
#if !defined(GX_MANUAL)
protected:
#ifndef GX_DOTNET_20
	__value gxu32 _handle;
#else
	gxu32 _handle;
#endif
#endif

public:
	/** Returns the local handle pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxu32 _get_handle(void) GX_CONST {
		return _handle;
	}
	/** Modifies the local handle pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
	inline void _set_handle(gxu32 ptr) GX_CONST {
		_handle = ptr;
	}
#endif

#endif /*)*/

#endif	/* GX_SWIGIF GX_DOTNET )*/

public:
	/** Initializes the class.
	 *
	 * The class will be invalid. Use the Open method for module opening. */
	inline gxHandle() {
#ifndef GX_DOTNET
		handle = 0;
#else
		_handle = 0;
#endif
	}
	/** Destructs the class.
	 *
	 * It decreases the reference counter of the handle. The function closes
	 * the module if required (in case when the reference counter becames zero). */
	inline ~gxHandle() {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxHandle() {
		_Dispose();
	}
#else
	/** It disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
	 /** no base class. */
	}
#endif

private:
inline void _Dispose(void) {
		Close();
	}
public:

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Opens a GX system compatible module (Unicode version).
	 *
	 * @param modulename Name of the module.
	 * @param groupname Property place in the property tree.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const wchar_t *modulename, const wchar_t *groupname = (const wchar_t *)0) gxFuncThrowsError {
		gxassert(modulename);
		gxassert(!handle);
		bool st = gx_openmodule(this, modulename, groupname) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Opens a GX system compatible module (ASCII version).
	 *
	 * @param modulename Name of the module.
	 * @param groupname Property place in the property tree.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const char *modulename, const char *groupname = (const char *)0) gxFuncThrowsError {
		gxassert(modulename);
		gxassert(!handle);
		bool st = gx_openmodule(this, modulename, groupname) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Opens a GX system compatible module (Unicode version).
	 *
	 * @param modulename Name of the module.
	 * @param groupname Property place in the property tree.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInStr modulename, gxInStr groupname) gxFuncThrowsError {
		GX_GETSTRING(_modulename, modulename);
		GX_GETSTRING(_groupname, groupname);
#ifndef GX_DOTNET
		bool st = gx_openmodule(this, _modulename, _groupname) ? true : false;
#else
		GX_GETHANDLE(h);
		bool st = gx_openmodule(&h, _modulename, _groupname) ? true : false;
		if(st) _set_handle(h.handle);
#endif
		gxcondthrow(!st);
		return st;
	}
	/** Opens a GX system compatible module with the default properties (Unicode version).
	 *
	 * @param modulename Name of the module.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInStr modulename) gxFuncThrowsError {
		GX_GETSTRING(_modulename, modulename);
#ifndef GX_DOTNET
		bool st = gx_openmodule(this, _modulename, L"default")!=0;
#else
		GX_GETHANDLE(h);
		bool st = gx_openmodule(&h, _modulename, L"default")!=0;
		if(st) _set_handle(h.handle);
#endif
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII	/*(*/
	/** Opens a GX system compatible module (ASCII version).
	 *
	 * @param modulename Name of the module.
	 * @param groupname Property place in the property tree.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInAStr modulename, gxInAStr groupname) gxFuncThrowsError {
		GX_GETASTRING(_modulename, modulename);
		GX_GETASTRING(_groupname, groupname);
		bool st = gx_openmodulea(this, _modulename, _groupname)!=0;
		gxcondthrow(!st);
		return st;
	}
	/** Opens a GX system compatible module with the default properties (ASCII version).
	 *
	 * @param modulename Name of the module.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInAStr modulename) gxFuncThrowsError {
		GX_GETASTRING(_modulename, modulename);
		bool st = gx_openmodulea(this, _modulename, "default")!=0;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_ASCII )*/

	/** Closes a previously opened module.
	 *
	 * It decreases the reference counter of the handle. The function closes
	 * the module if required (in case when the reference counter becames zero).
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(void) gxFuncThrowsError {
		bool st = IsValid();
		if(st) {
#ifndef GX_DOTNET
			st = gx_unrefhandle(this) ? true : false;
			if(st) handle = 0;
#else
			gxHANDLE h = { _handle };
			st = gx_unrefhandle(&h) ? true : false;
			if(st) _handle = 0;
#endif
			gxcondthrow(!st);
		}
		return true;
	}

	/** Checks if the handle of the module is valid.
	 *
	 * @return In case of existing handle the return value is true. */
	inline bool IsValid(void) GX_CONST {
		if(!this) return false;
#ifndef GX_DOTNET
		return handle ? true : false;
#else
		return _handle ? true : false;
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gives information about an opened module.
	 *
	 * @param moduleinfo Pointer to an information structure pointer where the
	 *                   system returns the data of the specified module.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetInfo(const gxMODULEINFO **moduleinfo) gxFuncThrowsError {
		gxassert(moduleinfo);
		bool st = gx_getmoduleinfo(*this, moduleinfo) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Calls a process of the module with its parameters.
	 *
	 * The functions and parameters usable inside the modules can be found in
	 * the documentation of the modules. The headers given with the modules
	 * contain inline functions, which make easier to access the functions
	 * of the module.
	 *
	 * @param callcode Call code for the function (GX_CALL_xxx call codes).
	 * @param params Parameters to give for the function (GX_PARM_xxx structures).
	 * @return Module defined, usually success is true. */
	inline bool Call(int callcode, void *params) {
		return gx_call(*this, callcode, params) ? true : false;
	}

	/** Equal operator.
	 *
	 * @param src Source handle structure.
	 * @return The handle class or an exception is thrown in case of error. */
	inline gxHandle &operator = (gxHANDLE GX_REF_STRUCT(src)) gxFuncThrowsError {
		int st = true;
		if(src.handle) {
			gxHANDLE nullhandle = { 0 };
			int st = gx_call(nullhandle, GX_CALL_REFHANDLE, &src);
			if(!st) gxthrow;
		}
		if(st) {
			Close();
			handle = src.handle;
		}
		return *this;
	}
	/** Equal operator.
	 *
	 * @param src Source handle.
	 * @return The handle class or an exception is thrown in case of error. */
	inline gxHandle &operator = (gxHandle GX_REF_CLASS(src)) {
		int st = true;
		if(src.handle) {
			gxHANDLE nullhandle = { 0 };
			int st = gx_call(nullhandle, GX_CALL_REFHANDLE, &src);
			if(!st) gxthrow;
		}
		if(st) {
			Close();
			handle = src.handle;
		}
		return *this;
	}

	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param string Pointer to a memory area where to store the value.
	 * @param maxlen Size of memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getmoduleproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property or an exception is thrown in case of error. */
	inline std::wstring GetProperty(const wchar_t *name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getmoduleproperty(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::wstring(buf);
	}
#endif

	/** Gets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param string Pointer to a memory area where to store the value.
	 * @param maxlen Size of memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getmoduleproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property or an exception is thrown in case of error. */
	inline std::string GetProperty(const char *name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getmoduleproperty(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::string(buf);
	}
#endif
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_DOTNET
	/** Calls a process of the module with its parameters.
	 *
	 * The functions and parameters usable inside the modules can be found in
	 * the documentation of the modules. The headers given with the modules
	 * contain inline functions, which make easier to access the functions
	 * of the module.
	 *
	 * @param callcode Call code for the function (GX_CALL_xxx call codes).
	 * @param params Parameters to give for the function (GX_PARM_xxx structures).
	 * @return Module defined, usually success is true. */
	inline int Call(int callcode, System::IntPtr params) {
		gxHANDLE h = { _handle };
		return gx_call(h, callcode, params.ToPointer());
	}
#endif	/* GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property or an exception is thrown in case of error. */
	inline gxOutStr GetProperty(gxInStr name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		int st = gx_getmoduleproperty(*this, _name, buf, GX_MAXLEN_PROPVALUE);
#else
		gxHANDLE h = { _handle };
		int st = gx_getmoduleproperty(h, _name, buf, GX_MAXLEN_PROPVALUE);
#endif
		if(!st) return GX_PUTSTRING_NONE;
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTSTRING(buf);
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII
	/** Gets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property or an exception is thrown in case of error. */
	inline gxOutAStr GetProperty(gxInAStr name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETASTRING(_name, name);
		int st = gx_getmodulepropertya(*this, _name, buf, GX_MAXLEN_PROPVALUE);
		if(!st) return GX_PUTASTRING_NONE;
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTASTRING(buf);
	}
#endif	/* GX_ASCII */

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Pointer to an integer where to store the value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const wchar_t *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline int GetPropertyInt(const wchar_t *name) gxFuncThrowsError {
		int ret = -1;
		if(!gx_getmodulepropertyint(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline int GetPropertyInt(gxInStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		if(!gx_getmodulepropertyint(*this, _name, &ret)) gxthrow;
#else
		gxHANDLE h = { _handle };
		if(!gx_getmodulepropertyint(h, _name, &ret)) gxthrow;
#endif
		return ret;
	}
#endif	/* GX_UNICODE )*/

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Pointer to an integer where to store the value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const char *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline int GetPropertyInt(const char *name) gxFuncThrowsError {
		int ret = -1;
		if(!gx_getmodulepropertyinta(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_ASCII
	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline int GetPropertyInt(gxInAStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getmodulepropertyinta(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Pointer to a floating-point where to store the value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const wchar_t *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyfloat(*this, name, fvalue)!=0;
		gxcondthrow(!st);
		return st;
	}
	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The floating-point value of the property or an exception is thrown in case of error. */
	inline double GetPropertyFloat(const wchar_t *name) gxFuncThrowsError {
		double ret = -1;
		if(!gx_getmodulepropertyfloat(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The floating-point value of the property or an exception is thrown in case of error. */
	inline double GetPropertyFloat(gxInStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		if(!gx_getmodulepropertyfloat(*this, _name, &ret)) gxthrow;
#else
		gxHANDLE h = { _handle };
		if(!gx_getmodulepropertyfloat(h, _name, &ret)) gxthrow;
#endif
		return ret;
	}
#endif	/*)*/

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Pointer to a floating-point where to store the value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetProperty(const char *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyfloata(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The floating-point value of the property or an exception is thrown in case of error. */
	inline double GetPropertyFloat(const char *name) gxFuncThrowsError {
		double ret = -1;
		if(!gx_getmodulepropertyfloata(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_ASCII
	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The floating-point value of the property or an exception is thrown in case of error. */
	inline double GetPropertyFloat(gxInAStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getmodulepropertyfloata(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif


#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets a version property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param version Pointer to an integer where to store the version.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetPropertyVersion(const wchar_t *name, unsigned int *version) gxFuncThrowsError {
		bool st = gx_getmodulepropertyversion(*this, name, version)!=0;
		gxcondthrow(!st);
		return st;
	}

	/** Gets a version property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline unsigned int GetPropertyVersion(const wchar_t *name) gxFuncThrowsError {
		unsigned int ret = 0;
		if(!gx_getmodulepropertyversion(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Gets a version property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline unsigned int GetPropertyVersion(gxInStr name) gxFuncThrowsError {
		unsigned int ret = 0;
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		if(!gx_getmodulepropertyversion(*this, _name, &ret)) gxthrow;
#else
		gxHANDLE h = { _handle };
		if(!gx_getmodulepropertyversion(h, _name, &ret)) gxthrow;
#endif
		return ret;
	}
#endif	/*)*/

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Gets a version property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param version Pointer to an integer where to store the version.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetPropertyVersion(const char *name, unsigned int *version) gxFuncThrowsError {
		bool st = gx_getmodulepropertyversiona(*this, name, version) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets a version property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline unsigned int GetPropertyVersion(const char *name) gxFuncThrowsError {
		unsigned int ret = 0;
		if(!gx_getmodulepropertyversiona(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_ASCII
	/** Gets a version property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return The integer value of the property or an exception is thrown in case of error. */
	inline unsigned int GetPropertyVersion(gxInAStr name) gxFuncThrowsError {
		unsigned int ret = 0;
		GX_GETASTRING(_name, name);
		if(!gx_getmodulepropertyversiona(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif


	/**************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Sets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const wchar_t *name, const wchar_t *string) gxFuncThrowsError {
		bool st = gx_setmoduleproperty(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const char *name, const char *string) gxFuncThrowsError {
		bool st = gx_setmodulepropertya(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Sets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInStr name, gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETSTRING(_str, str);
#ifndef GX_DOTNET
		bool st = gx_setmoduleproperty(*this, _name, _str) ? true : false;
#else
		gxHANDLE h = { _handle };
		bool st = gx_setmoduleproperty(h, _name, _str) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII
	/** Sets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInAStr name, gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		GX_GETASTRING(_str, str);
		bool st = gx_setmodulepropertya(*this, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_ASCII */

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Sets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue An integer value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const wchar_t *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue An integer value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const char *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Sets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue An integer value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInStr name, int ivalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		bool st = gx_setmodulepropertyint(*this, _name, ivalue) ? true : false;
#else
		gxHANDLE h = { _handle };
		bool st = gx_setmodulepropertyint(h, _name, ivalue) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#endif	/*)*/
#ifdef GX_ASCII
	/** Sets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue An integer value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInAStr name, int ivalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setmodulepropertyinta(*this, _name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Sets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue A floating-point value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const wchar_t *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyfloat(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue A floating-point value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(const char *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyfloata(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Sets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue A floating-point value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInStr name, double fvalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		bool st = gx_setmodulepropertyfloat(*this, _name, fvalue) ? true : false;
#else
		gxHANDLE h = { _handle };
		bool st = gx_setmodulepropertyfloat(h, _name, fvalue) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII
	/** Sets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue A floating-point value of the property.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SetProperty(gxInAStr name, double fvalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setmodulepropertyfloata(*this, _name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_ASCII */

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Saves the properties of a module stored in the memory to a branch of the
	 * property tree stored on a mass storage device (Unicode version).
	 *
	 * @param name Place of property in the tree.
	 * @param level Higher numbers give more details (0 = basic properties,	100 = all properties).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveProperties(const wchar_t *name, int level = 0) gxFuncThrowsError {
		bool st = gx_savemoduleproperties(*this, name, level) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves the properties of a module stored in the memory to a branch of the
	 * property tree stored on a mass storage device (ASCII version).
	 *
	 * @param name Place of property in the tree.
	 * @param level Higher numbers give more details (0 = basic properties,	100 = all properties).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveProperties(const char *name, int level = 0) gxFuncThrowsError {
		bool st = gx_savemoduleproperties(*this, name, level) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Saves the properties of a module stored in the memory to a branch of the
	 * property tree stored on a mass storage device (Unicode version).
	 *
	 * @param name Place of property in the tree.
	 * @param level Higher numbers give more details (0 = basic properties, 100 = all properties).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveProperties(gxInStr name, int level) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		bool st = gx_savemoduleproperties(*this, _name, level) ? true : false;
#else
		gxHANDLE h = { _handle };
		bool st = gx_savemoduleproperties(h, _name, level) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Saves the properties of a module stored in the memory to a branch of the
	 * property tree stored on a mass storage device (Unicode version).
	 *
	 * @param name Place of property in the tree.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveProperties(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
#ifndef GX_DOTNET
		bool st = gx_savemoduleproperties(*this, _name, 0) ? true : false;
#else
		gxHANDLE h = { _handle };
		bool st = gx_savemoduleproperties(h, _name, 0) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII
	/** Saves the properties of a module stored in the memory to a branch of the
	 * property tree stored on a mass storage device (ASCII version).
	 *
	 * @param name Place of property in the tree.
	 * @param level Higher numbers give more details (0 = basic properties, 100 = all properties).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveProperties(gxInAStr name, int level = 0) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_savemodulepropertiesa(*this, _name, level) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/* GX_ASCII */

	/******************************************************************************/
	/** It starts the property transaction. The module accepts but doesn't update
	 *  properties (setmoduleproperty). You must use 'gx_mpcommit' to update
	 *  these properties.
	 * \warning Not supported by each module!
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool MPStartTransaction(void) {
		GX_GETHANDLE(h);
		bool st = gx_mpstarttransaction(h) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** It ends the property transaction and updates your changes to module.
	 * \warning Not supported by each module!
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool MPCommit(void) {
		GX_GETHANDLE(h);
		bool st = gx_mpcommit(h) ? true : false;
		gxcondthrow(!st);
		return st;
	}

};

#endif	/* GX_EXT_MODULE )*/
/******************************************************************************/
#endif /* NO_GX_CLASSES  !ANDROID)*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	} /* namespace gx */
#endif
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
#ifdef _MSC_VER
	#pragma warning(default: 4127)		/* truncated debug info */
#endif
/******************************************************************************/
#endif /*GXSD_INCL*/
/******************************************************************************/
