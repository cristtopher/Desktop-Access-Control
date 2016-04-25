/******************************************************************************
 * GX Watchdog header file - V7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Watchdog handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * The GX system implements the handling of the hardware watchdog devices
 * connected to it. The watchdog device is a counter, which should be refreshed
 * in certain time intervals. If the counter value becomes zero the device
 * gives a hardware reboot signal. If the device is hardwired to the mainboard
 * the system will restart.
 *
 * This file contains the descriptions of classes and functions of the watchdog handling module.
 */
/******************************************************************************/
#ifndef GX_WATCHDOG_INCL
#define GX_WATCHDOG_INCL
/******************************************************************************/
#include "gxsd.h"
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/******************************************************************************/
/** Call codes for the watchdog operations. */
enum {
	GX_CALL_WATCHDOG			=	GX_CALL_GROUP_GX_WATCHDOG	|	0x0000 /**< Updates the watchdog counter. */
};
/******************************************************************************/
/** Parameter structure for the gx_watchdog() function. */
struct GX_PARM_WATCHDOG {
	int	 timersec;	/**< Watchdog timer value in seconds. If it is zero it disables the watchdog. */
};
#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_watchdog
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Updates the watchdog counter.
 *
 * @param handle Handle of the module.
 * @param timersec Watchdog timer value in seconds. If it is zero it disables
 *               the watchdog.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_watchdog(gxHANDLE handle, int timersec) {
	struct GX_PARM_WATCHDOG	p;
	p.timersec = timersec;
	return gx_call(handle, GX_CALL_WATCHDOG, &p);
}

#ifdef __cplusplus
/******************************************************************************/
/** Updates the watchdog counter.
 *
 * @param timersec Watchdog timer value in seconds. If it is zero it disables
 *               the watchdog.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_watchdog(int timersec) {
	return gx_watchdog(gx_direct(GX_CALL_GROUP_GX_WATCHDOG), timersec);
}
#endif

/******************************************************************************/
/** @} */
/******************************************************************************/

#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/
#ifndef NO_GX_CLASSES
/******************************************************************************/
/** Class for the watchdog functions. */
GX_CLASS gxWatchdog : public gxHandle {
public:
	/** Class initialization. */
	inline gxWatchdog() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxwatchdog", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxwatchdog", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group).
	 * @param modname Name of the module. */
	inline gxWatchdog(const wchar_t *propname, const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError {
		if(!gx_openmodule(this, modname ? modname : L"gxwatchdog", propname)) gxthrow;
	}

	/** Class initialization with place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group).
	 * @param modname Name of the module. */
	inline gxWatchdog(const char *propname, const char *modname = (const char *)0) gxFuncThrowsError {
		if(!gx_openmodulea(this, modname ? modname : "gxwatchdog", propname)) gxthrow;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Class initialization with place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group).
	 * @param modname Name of the module. */
	inline gxWatchdog(gxInStr propname, gxInStr modname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
		GX_GETSTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
	/** Class initialization with place of the properties (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group). */
	inline gxWatchdog(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxwatchdog", _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxwatchdog", _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif
#ifdef GX_ASCII
	/** Class initialization with place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group).
	 * @param modname Name of the module. */
	inline gxWatchdog(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, _propname)) gxthrow;
	}
	/** Class initialization with place of the properties (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of the property group). */
	inline gxWatchdog(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		if(!gx_openmodulea(this, "gxwatchdog", _propname)) gxthrow;
	}
#endif

	/** Updates the watchdog counter.
	 *
	 * @param timersec Watchdog timer value in seconds. If it is zero it disables
	 *               the watchdog.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Set(int timersec) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_watchdog(h, timersec) ? true : false;
		gxcondthrow(!st);
		return st;
	}
};
/******************************************************************************/
#endif	// NO_GX_CLASSES
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif	// GX_WATCHDOG_INCL
/******************************************************************************/
