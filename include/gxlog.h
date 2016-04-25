/*******************************************************************************
 * GX LOG header file - V7.2.10
 *
 * 2004-2011(c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Logging interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the logging module.
 */
/******************************************************************************/
#ifndef GX_LOG_INCL
#define GX_LOG_INCL
/******************************************************************************/
#include <assert.h>
#if defined(WIN32) && !defined(GX_DOTNET)
	#include <windows.h>
#endif
#ifdef LINUX
	#include <pthread.h>
#endif
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include "gxsd.h"
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/
/** Enumerations for the log levels. */
GX_ENUM GX_LOGLEVELS {
	GX_NONE	= 0,		/**< No log messages. */
	GX_EMERG,			/**< Emergency messages, application broken and probably loss of data. */
	GX_FATAL,			/**< Fatal error, the application can not be continued. */
	GX_ERROR,			/**< Normal error, the application can be continued or terminated with error. */
	GX_WARN,			/**< Warning messages, the application can be continued. */
	GX_INFO,			/**< Information 1. */
	GX_INFO2,			/**< Information 2. */
	GX_INFO3,			/**< Information 3. */
	GX_DEBUG,			/**< Normal debug. (Only if the NDEBUG was not defined) */
	GX_DEBUG2			/**< Debug in low-level mode. (Only if the NDEBUG was not defined) */
};
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/******************************************************************************/
/** Call codes for LOG operations. */
enum {
	GX_CALL_WRITELOG	= GX_CALL_GROUP_GX_LOG,	/**< Writes a log. (Unicode version) */
	GX_CALL_WRITELOGA		/**< Writes a log. (ASCII version) */
};

/** Parameter structure for the gx_writelog() function. (Unicode version) */
struct GX_PARM_WRITELOG {
	gxi32		 level;			/**< Level of the log item. (see \ref GX_LOGLEVELS) */
	const char	*file;			/**< Name of the source file where the function is called (in debug mode). */
	gxi32		 line;			/**< Line number of the source file where the function is called (in debug mode). */
	const char	*function;		/**< Name of the function where the log function is called (in debug mode). */
	const wchar_t *string;		/**< Description text of the log. */
	va_list		 args;			/**< Arguments for the log function. */
};

/** Parameter structure for the gx_writelog() function. (ASCII version) */
struct GX_PARM_WRITELOGA {
	gxi32		 level;			/**< Level of the log item. (see \ref GX_LOGLEVELS) */
	const char	*file;			/**< Name of the source file where the function is called (in debug mode). */
	gxi32		 line;			/**< Line number of the source file where the function is called (in debug mode). */
	const char	*function;		/**< Name of the function where the log function is called (in debug mode). */
	const char	*string;		/**< Description text of the log. */
	va_list		 args;			/**< Arguments for the log function. */
};
#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_log
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Writes a log with debug information. (Unicode version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const wchar_t *str, va_list args) {
	struct GX_PARM_WRITELOG wl;
	gxi32 st;
	wl.level = level;
	wl.file = file;
	wl.line = line;
	wl.function = function;
	wl.string = str;
	va_copy(wl.args, args);
	st = gx_call(handle, GX_CALL_WRITELOG, &wl);
	va_end(wl.args);
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Writes a log. (Unicode version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxHANDLE handle, gxi32 level, const wchar_t *str, va_list args) {
	return gx_writelogv(handle, level,
					(const char *)0, 0, (const char *)0, str, args);
}
#endif

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogva(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, va_list args) {
	struct GX_PARM_WRITELOGA wl;
	gxi32 st;
	wl.level = level;
	wl.file = file;
	wl.line = line;
	wl.function = function;
	wl.string = str;
	va_copy(wl.args, args);
	st = gx_call(handle, GX_CALL_WRITELOGA, &wl);
	va_end(wl.args);
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Writes a log. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxHANDLE handle, gxi32 level,
						const char *str, va_list args) {
	return gx_writelogva(handle, level,
					(const char *)0, 0, (const char *)0, str, args);
}

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, va_list args) {
	return gx_writelogva(handle, level, file, line, function, str, args);
}
#endif
/******************************************************************************/
/** Writes a log with debug information. (Unicode version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const wchar_t *str, ...) {
	gxi32 st;
	va_list args;
	va_start(args, str);
	st = gx_writelogv(handle, level, file, line, function, str, args);
	va_end(args);
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Writes a log. (Unicode version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxHANDLE handle, gxi32 level, const wchar_t *str, ...) {
	va_list args;
	va_start(args, str);
	gxi32 st = gx_writelogv(handle, level, str, args);
	va_end(args);
	return st;
}
#endif

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writeloga(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, ...) {
	gxi32 st;
	va_list args;
	va_start(args, str);
	st = gx_writelogva(handle, level, file, line, function, str, args);
	va_end(args);
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Writes a log. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxHANDLE handle, gxi32 level, const char *str, ...) {
	va_list args;
	va_start(args, str);
	int st = gx_writelogv(handle, level, str, args);
	va_end(args);
	return st;
}

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param handle Handle of an opened LOG module.
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxHANDLE handle, gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, ...) {
	gxi32 st;
	va_list args;
	va_start(args, str);
	st = gx_writelogv(handle, level, file, line, function, str, args);
	va_end(args);
	return st;
}
#endif

#ifdef __cplusplus
/******************************************************************************/
/** Writes a log with debug information. (Unicode version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxi32 level,
						const char *file, gxi32 line, const char *function,
						const wchar_t *str, va_list args) {
	return gx_writelogv(gx_direct(GX_CALL_GROUP_GX_LOG), level,
						file, line, function, str, args);
}

/******************************************************************************/
/** Writes a log. (Unicode version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxi32 level, const wchar_t *str, va_list args) {
	return gx_writelogv(level, (const char *)0, 0, (const char *)0, str, args);
}

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, va_list args) {
	return gx_writelogv(gx_direct(GX_CALL_GROUP_GX_LOG), level,
						file, line, function, str, args);
}

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param args Arguments for the log function.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelogv(gxi32 level, const char *str, va_list args) {
	return gx_writelogv(level, (const char *)0, 0, (const char *)0, str, args);
}

/******************************************************************************/
/** Writes a log with debug information. (Unicode version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxi32 level,
						const char *file, gxi32 line, const char *function,
						const wchar_t *str, ...) {
	va_list args;
	va_start(args, str);
	gxi32 st = gx_writelogv(gx_direct(GX_CALL_GROUP_GX_LOG), level,
						file, line, function, str, args);
	va_end(args);
	return st;
}
/******************************************************************************/
/** Writes a log with debug information. (Unicode version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxi32 level, const wchar_t *str, ...) {
	va_list args;
	va_start(args, str);
	gxi32 st = gx_writelogv(level, str, args);
	va_end(args);
	return st;
}

/******************************************************************************/
/** Writes a log with debug information. (ASCII version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param file Name of the source file where the function is called (in debug mode).
 * @param line Line number of the source file where the function is called (in debug mode).
 * @param function Name of the function where the log function is called (in debug mode).
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxi32 level,
						const char *file, gxi32 line, const char *function,
						const char *str, ...) {
	va_list args;
	va_start(args, str);
	gxi32 st = gx_writelogv(gx_direct(GX_CALL_GROUP_GX_LOG), level,
						file, line, function, str, args);
	va_end(args);
	return st;
}

/******************************************************************************/
/** Writes a log. (ASCII version)
 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
 * @param str Description text of the log.
 * @param ... Arguments for the log function (like printf).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_writelog(gxi32 level, const char *str, ...) {
	va_list args;
	va_start(args, str);
	int st = gx_writelogv(level, str, args);
	va_end(args);
	return st;
}
#endif

/******************************************************************************/
/** @} */
/******************************************************************************/

#endif // !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)

#ifdef GX_DOTNET
#pragma managed
#endif

/******************************************************************************/
/******************************************************************************/
#ifndef NO_GX_CLASSES
/******************************************************************************/
/******************************************************************************/
/** Class for the GX LOG functions. */
GX_CLASS gxLog : public gxHandle
#ifdef GX_DOTNET
, public System::IDisposable
#endif
{
#if (!defined(NDEBUG) || defined(DEBUG)) && !defined(GX_SWIGIF) && !defined(GX_DOTNET)
private:
#ifdef LINUX
	pthread_mutex_t	mutex;				/**< Mutexlock on Linux systems. */

	/** Initializes the mutex on Linux. */
	inline void _mutex_init(void) {
		pthread_mutex_init(&mutex, 0);
	}
	/** Destroyes the mutex on Linux. */
	inline void _mutex_destroy(void) {
		pthread_mutex_destroy(&mutex);
	}
	/** Locks the mutex on Linux. */
	inline void _mutex_lock(void) {
		pthread_mutex_lock(&mutex);
	}
	/** Unlocks the mutex on Linux. */
	inline void _mutex_unlock(void) {
		pthread_mutex_unlock(&mutex);
	}
#endif

#ifdef WIN32
	HANDLE	mutex;						/**< Mutexlock on Win32 systems. */

	/** Initializes the mutex on Win32. */
	inline void _mutex_init(void) {
		mutex = CreateSemaphore(0, 1, 1, 0);
	}
	/** Destroyes the mutex on Win32. */
	inline void _mutex_destroy(void) {
		CloseHandle(mutex);
	}
	/** Locks the mutex on Win32. */
	inline void _mutex_lock(void) {
		WaitForSingleObject(mutex, INFINITE);
	}
	/** Unlocks the mutex on Win32. */
	inline void _mutex_unlock(void) {
		ReleaseSemaphore(mutex, 1, 0);
	}
#endif

	gxi32 _level;					/**< Level of the log item. (see \ref GX_LOGLEVELS) */
	const char *_file;				/**< Name of the source file where the function is called. (In debug mode) */
	gxi32 _line;					/**< Line number of the source file where the function is called. (In debug mode) */
	const char *_pretty_function;	/**< Name of the function where the log function is called. (In debug mode) */

public:
	/** Locks the mutex and settings local variables.
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file where the function is called. (In debug mode)
	 * @param line Line number of the source file where the function is called. (In debug mode)
	 * @param pretty_function Name of the function where the log function is called. (In debug mode) */
	inline void _Set(gxi32 level, const char *file, gxi32 line, const char *pretty_function) {
		_mutex_lock();
		_level = level;
		_file = file;
		_line = line;
		_pretty_function = pretty_function;
	}

	/** Writes a log and unlocks the mutex. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf). */
	inline void _WriteLog(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		int st;
		st = gx_writelogv(*this, _level, _file, _line, _pretty_function, str, args);
		va_end(args);
		_mutex_unlock();
		gxcondthrow(!st);
	}

	/** Writes a log and unlocks the mutex. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf). */
	inline void _WriteLog(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		int st;
		st = gx_writelogv(*this, _level, _file, _line, _pretty_function, str, args);
		va_end(args);
		_mutex_unlock();
		gxcondthrow(!st);
	}
#endif

public:
	/** Class initialization. */
	inline gxLog() gxFuncThrowsError : gxHandle() {
#if (!defined(NDEBUG) || defined(DEBUG)) && !defined(GX_DOTNET)
		_mutex_init();
#endif
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxlog", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxlog", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Class initialization with place of the properties and name of the module. (Unicode version)
	 * @param propname Place of the properties in the property tree. (Name of the property group)
	 * @param modname Name of the module. */
	inline gxLog(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError : gxHandle() {

#if !defined(NDEBUG) || defined(DEBUG)
		_mutex_init();
#endif
		if(!gx_openmodule(this, modname ? modname : L"gxlog", propname)) gxthrow;
	}

	/** Class initialization with place of the properties and name of the module. (ASCII version)
	 * @param propname Place of the properties in the property tree. (Name of the property group)
	 * @param modname Name of the module. */
	inline gxLog(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError : gxHandle() {

#if !defined(NDEBUG) || defined(DEBUG)
		_mutex_init();
#endif
		if(!gx_openmodule(this, modname ? modname : "gxlog", propname)) gxthrow;
	}
#endif

#ifdef GX_UNICODE
	/** Class initialization with place of the properties and name of the module. (Unicode version)
	 * @param propname Place of the properties in the property tree. (Name of the property group)
	 * @param modname Name of the module. */
	inline gxLog(gxInStr propname, gxInStr modname) gxFuncThrowsError : gxHandle() {
		GX_GETSTRING(_propname, propname);
		GX_GETSTRING(_modname, modname);
#if (!defined(NDEBUG) || defined(DEBUG)) && !defined(GX_DOTNET)
		_mutex_init();
#endif
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}

	/** Class initialization with place of the properties and name of the module. (Unicode version)
	 * @param propname Place of the properties in the property tree. (Name of the property group) */
	inline gxLog(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#if (!defined(NDEBUG) || defined(DEBUG)) && !defined(GX_DOTNET)
		_mutex_init();
#endif
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxlog", _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxlog", _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif

#ifdef GX_ASCII
	/** Class initialization with place of the properties and name of the module. (ASCII version)
	 * @param propname Place of the properties in the property tree. (Name of the property group)
	 * @param modname Name of the module. */
	inline gxLog(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
#if !defined(NDEBUG) || defined(DEBUG)
		_mutex_init();
#endif
		if(!gx_openmodule(this, _modname, _propname)) gxthrow;
	}
	/** Class initialization with place of the properties. (ASCII version)
	 * @param propname Place of the properties in the property tree. (Name of the property group) */
	inline gxLog(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
#if !defined(NDEBUG) || defined(DEBUG)
		_mutex_init();
#endif
		if(!gx_openmodule(this, "gxlog", _propname)) gxthrow;
	}
#endif

	/** Class termination. */
	inline ~gxLog() {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxLog() {
		_Dispose();
	}
#else
	/** It disposes the class. */
inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
		/** call the base class */
		gxHandle::Dispose();
}
#endif

private:
	/** It disposes the class. */
	inline void _Dispose(void) {
#if (!defined(NDEBUG) || defined(DEBUG)) && !defined(GX_DOTNET)
		_mutex_destroy();
#endif		
	}

public:

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Writes a log with debug information. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file where the function is called (in debug mode).
	 * @param line Line number of the source file where the function is called (in debug mode).
	 * @param function Name of the function where the log function is called (in debug mode).
	 * @param str Description text of the log.
	 * @param args Arguments for the log function.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLogv(gxi32 level, const char *file, gxi32 line, const char *function,
						const wchar_t *str, va_list args) gxFuncThrowsError {
		bool st = gx_writelogv(*this, level, file, line, function, str, args) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Description text of the log.
	 * @param args Arguments for the log function.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLogv(gxi32 level, const wchar_t *str, va_list args) gxFuncThrowsError {
		bool st = gx_writelogv(*this, level, str, args) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with debug information. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file where the function is called (in debug mode).
	 * @param line Line number of the source file where the function is called (in debug mode).
	 * @param function Name of the function where the log function is called (in debug mode).
	 * @param str Description text of the log.
	 * @param args Arguments for the log function.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLogv(gxi32 level, const char *file, gxi32 line, const char *function,
						const char *str, va_list args) gxFuncThrowsError {
		bool st = gx_writelogv(*this, level, file, line, function, str, args) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Description text of the log.
	 * @param args Arguments for the log function.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLogv(gxi32 level, const char *str, va_list args) gxFuncThrowsError {
		bool st = gx_writelogv(*this, level, str, args) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with debug information. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file where the function is called (in debug mode).
	 * @param line Line number of the source file where the function is called (in debug mode).
	 * @param function Name of the function where the log function is called (in debug mode).
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, const char *file, gxi32 line, const char *function,
						const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = gx_writelogv(*this, level, file, line, function, str, args) ? true : false;
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = gx_writelogv(*this, level, str, args) ? true : false;
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with debug information. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file where the function is called (in debug mode).
	 * @param line Line number of the source file where the function is called (in debug mode).
	 * @param function Name of the function where the log function is called (in debug mode).
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, const char *file, gxi32 line, const char *function,
						const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = gx_writelogv(*this, level, file, line, function, str, args) ? true : false;
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = gx_writelogv(*this, level, str, args) ? true : false;
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with emergency level. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteEmergency(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_EMERG, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with emergency level. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteEmergency(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_EMERG, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with fatal level. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteFatal(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_FATAL, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with fatal level. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteFatal(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_FATAL, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with error level. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteError(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_ERROR, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with error level. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteError(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_ERROR, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with warning level. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteWarning(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_WARN, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with warning level. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteWarning(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_WARN, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with information level. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with information level 2. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo2(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO2, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 2. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo2(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO2, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with information level 3. (Unicode version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo3(const wchar_t *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO3, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 3. (ASCII version)
	 * @param str Description text of the log.
	 * @param ... Arguments for the log function (like printf).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo3(const char *str, ...) gxFuncThrowsError {
		va_list args;
		va_start(args, str);
		bool st = WriteLogv(GX_INFO3, str, args);
		va_end(args);
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Writes a log with debug information. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file the function is called from (in debug mode).
	 * @param line Line number of the source file the function is called from (in debug mode).
	 * @param function Name of the function the log function is called from (in debug mode).
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, gxInStr file, gxi32 line, gxInStr function,
					gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_file, file);
		GX_GETSTRING(_function, function);
		GX_GETSTRING(_str, str);
		char __file[1024];
		char __function[1024];
		gx_snprintf(__file,1024,"%ls",_file);
		gx_snprintf(__function,1024,"%ls",_function);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, level, __file, line, __function, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with debug information. (Unicode version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, level, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with emergency level. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteEmergency(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_EMERG, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with fatal level. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteFatal(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_FATAL, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with error level. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteError(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_ERROR, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with warning level. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteWarning(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_WARN, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_INFO, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 2. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo2(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_INFO2, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 3. (Unicode version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo3(gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_writelog(h, (int)GX_ENUM_PATH(GX_LOGLEVELS) GX_INFO3, L"%ls", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Writes a log with debug information. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param file Name of the source file the function is called from (in debug mode).
	 * @param line Line number of the source file the function is called from (in debug mode).
	 * @param function Name of the function the log function is called from (in debug mode).
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, gxInAStr file, gxi32 line, gxInAStr function,
					gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_file, file);
		GX_GETASTRING(_function, function);
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, level, _file, line, _function, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with debug information. (ASCII version)
	 * @param level Level of the log item. (see \ref GX_LOGLEVELS)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteLog(gxi32 level, gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, level, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Writes a log with emergency level. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteEmergency(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_EMERG, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with fatal level. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteFatal(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_FATAL, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with error level. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteError(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_ERROR, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with warning level. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteWarning(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_WARN, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_INFO, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 2. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo2(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_INFO2, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Writes a log with information level 3. (ASCII version)
	 * @param str Descriptive text of the log.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteInfo3(gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_str, str);
		bool st = gx_writelog(*this, GX_INFO3, "%hs", _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
};
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)

#if !defined(NDEBUG) || defined(DEBUG)

/** Writes an emergency item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_emerg \
			gxlog._Set(GX_EMERG, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes an emergency item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_emergency gx_emerg

/** Writes a fatal item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_fatal \
			gxlog._Set(GX_FATAL, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes an error item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_error \
			gxlog._Set(GX_ERROR, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes a warning item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_warn \
			gxlog._Set(GX_WARN, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes a warning item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_warning gx_warn

/** Writes an information item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_info \
			gxlog._Set(GX_INFO, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes an information item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_info2 \
			gxlog._Set(GX_INFO2, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes an information item to the log with debug information in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_info3 \
			gxlog._Set(GX_INFO3, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes a debug item to the log with debug information. Only works in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_debug \
			gxlog._Set(GX_DEBUG, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

/** Writes a low-level debug item to the log with debug information. Only works in debug mode.
 * \warning The 'gxlog' class must be defined. (gxLog gxlog) */
#define gx_debug2 \
			gxlog._Set(GX_DEBUG2, __FILE__, __LINE__, _GX_FUNCTION_), \
			gxlog._WriteLog

#else

// In the release mode does not write debug items. (file, line, pretty_function)

#define gx_emerg gxlog.WriteEmergency
#define gx_emergency gxlog.WriteEmergency

#define gx_fatal	gxlog.WriteFatal

#define gx_error	gxlog.WriteError

#define gx_warn		gxlog.WriteWarning
#define gx_warning	gxlog.WriteWarning

#define gx_info		gxlog.WriteInfo
#define gx_info2	gxlog.WriteInfo2
#define gx_info3	gxlog.WriteInfo3

inline void __gx_no_write(const char *str, ...) { }
inline void __gx_no_write(const wchar_t *str, ...) { }

#define gx_debug	if(0) __gx_no_write

#define gx_debug2	if(0) __gx_no_write

#endif	// !defined(NDEBUG) || defined(DEBUG)

#endif	// !defined(GX_SWIGIF) && !defined(GX_DOTNET)
/******************************************************************************/
/******************************************************************************/
#endif//NO_GX_CLASSES
/******************************************************************************/
#ifdef GX_NAMESPACES
}
#endif
/******************************************************************************/
#endif//GX_LOG_INCL
/******************************************************************************/
