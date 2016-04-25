/*******************************************************************************
 * GX error file - v7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> GX system error codes and messages </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy
 * to program interface to the hardware devices.
 *
 * This file contains the error codes and descriptions of the GX system.
 */
/******************************************************************************/
#ifndef GX_ERROR_INCL
#define GX_ERROR_INCL
/******************************************************************************/
#ifndef __KERNEL__
	#include "gxtypes.h"
#else
	#undef GX_NAMESPACES
	#undef GX_ENUM
	#define GX_ENUM enum
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifndef GX_EXT_MODULE
/******************************************************************************/
/** System and GX-specific error codes. */
GX_ENUM GX_ERROR_CODES {
	/* System error codes */
	GX_ENOERR			= 0x0000, /**< No Error								 */

	GX_ENOENT			= 0x0002, /**< Entry not found (ENOENT)				 */
	GX_ENOMEM			= 0x000c, /**< Memory allocation error (ENOMEM)		 */
	GX_EACCES			= 0x000d, /**< Permission denied (EACCES)			 */
	GX_EFAULT			= 0x000e, /**< Bad address or program error (EFAULT) */
	GX_EBUSY			= 0x0010, /**< Resource busy (EBUSY)				 */
	GX_EEXIST			= 0x0011, /**< File exists (EEXIST)					 */
	GX_ENODEV			= 0x0013, /**< No such device (ENODEV)				 */
	GX_EINVAL			= 0x0016, /**< Invalid parameter (EINVAL)			 */
	GX_ERANGE			= 0x0022, /**< Data out of range (ERANGE)			 */
	GX_EDATA			= 0x003D, /**< No data available (Linux - ENODATA)	 */
	GX_ECOMM			= 0x0046, /**< Communication error on send (Linux - ECOMM) */
	GX_ETIMEDOUT		= 0x006E, /**< Function timed out (Linux - ETIMEDOUT) */

	/* General error codes */
	GX_EOPEN			= 0x1000, /**< File open error						 */
	GX_ECREAT			= 0x1001, /**< File creation error					 */
	GX_EREAD			= 0x1002, /**< File read error						 */
	GX_EWRITE			= 0x1003, /**< File write error						 */
	GX_EFILE			= 0x1004, /**< Invalid file content					 */

	GX_EINVIMG			= 0x1010, /**< Invalid image						 */
	GX_EINVFUNC			= 0x1011, /**< Invalid function						 */

	GX_EHWKEY			= 0x1012, /**< Hardware key does not work properly	 */
	GX_EVERSION			= 0x1013, /**< Invalid version						 */
	GX_EASSERT			= 0x1014, /**< Assertion occurred					 */

	GX_EDISCON			= 0x1015, /**< Device is disconnected				 */

	GX_EIMGPROC			= 0x1016, /**< Image processing failed				 */

	GX_EAUTH			= 0x1017, /**< Authenticity cannot be determined	 */

/*	GX_ESTATE			= 0x1100, // Use GX_EFAULT */

	/* Module error codes */
	/* GX_xxx			= 0xmmmm8xxx	// mmmm => group code */

	GX_ENOMODULE		= 0x8000,	/**< The specified module cannot be found (module: '%ls') */
};
/******************************************************************************/
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif /* GX_ERROR_INCL */
/******************************************************************************/
