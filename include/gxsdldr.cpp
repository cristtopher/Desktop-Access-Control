/******************************************************************************
 * GXSD Loader file - V7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> GX system loader </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * The applications reaches the GX system modules through a defined interface.
 * This interface is a common interface implemented in the \c libgxsd.so on Linux
 * and \c gxsd.dll on Windows systems. The module openings are made using the
 * general dynamic loader functions.
 *
 * Windows example:
 * \verbatim

	HMODULE module = (HMODULE)LoadLibraryA("gxsd7.dll");
	...
	gx_call = GetProcAddress(module, "gx_call");
	...
	FreeLibrary(module);

   \endverbatim
 *
 * Linux example:
 * \verbatim

	void *module = dlopen("/usr/lib32/libgxsd.so.7", RTLD_NOW | RTLD_GLOBAL);
	...
	gx_call = dlsym(module, "gx_call");
	...
	dlclose(module);

   \endverbatim
 *
 * The \a gxsdldr.c(pp) file is a loader that loads the gxsd.dll (libgxsd.so) file.
 *
 * Recomended usage:
 *
 *  -  Including it in the main source file. (\a \#include \a "gxsdldr.c(pp)")
 *  -  Copying this file in the source directory, compiling and linking with the other object files.
 */
/******************************************************************************/
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "gxsd.h"
/******************************************************************************/
#ifdef ANDROID
extern void LOG(const char* msg,...);
#endif

#ifdef GX_NAMESPACES
	namespace gx {
#endif
#ifdef GX_DOTNET
	/* Unmanaged code for .net */
	#pragma unmanaged
#endif
/******************************************************************************/
/** Type of the gx_call function. @see gx_call */
typedef int GXAPI gxldr_callfunc_t(struct gxHANDLE handle, int function, void *params);
/******************************************************************************/
#ifdef LINUX
	#include <dlfcn.h>

	#ifdef __cplusplus
		extern "C" void gxsdldr_init(void) __attribute__((constructor));
		extern "C" void gxsdldr_destroy(void) __attribute__((destructor));
	#else
		void gxsdldr_init(void) __attribute__((constructor));
		void gxsdldr_destroy(void) __attribute__((destructor));
	#endif
#endif
/******************************************************************************/
#ifdef WIN32
	#include <windows.h>

	#ifdef __cplusplus
		extern "C" bool gxsdldr_init(gxldr_callfunc_t** gxsdldr_call);
	#else
		bool gxsdldr_init(gxldr_callfunc_t** gxsdldr_call);
	#endif
#endif
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -amp
#endif
/******************************************************************************/
/** Name of the library. */
extern const char *gxsdldr_modulename;

/** Error buffer. */
static char gxsdldr_errstr[256];

/** Main function pointer. */
#ifdef LINUX
	gxldr_callfunc_t *gxsdldr_call = 0;
#endif
/******************************************************************************
 * Common section
 ******************************************************************************/
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
int GXAPI
#if defined GX_ALLOW_GX_CALL_EXPORT
__declspec(dllexport)			/* to allow of building an import library */
#endif
gx_call(struct gxHANDLE handle, int function, void *params) {
#ifdef WIN32
static gxldr_callfunc_t *gxsdldr_call = 0;
	if (!gxsdldr_call)
	{
		/* Call the init function if the gx_call() is not found */
		gxsdldr_init(&gxsdldr_call);
	}
#else
	if(!gxsdldr_call) gxsdldr_init();
#endif
	if (gxsdldr_call) return gxsdldr_call(handle, function, params);	/* GXSD library is loaded */

	/* GXSD library not loaded */
	switch(function) {
		case GX_CALL_GETERROR:	/* gx_geterror() function - Unicode mode */
			{
				if(params){
					struct GX_PARM_GETERROR *mp = (struct GX_PARM_GETERROR *)params;
					mp->code = ENOENT;
					if(mp->string && mp->maxlen>0) {
						gx_snwprintf(mp->string, mp->maxlen, L"gxsdldr: open error in %hs (%hs)",
							gxsdldr_modulename, gxsdldr_errstr);
						mp->string[mp->maxlen-1] = 0;
					}
				}
				return ENOENT;
			}
#ifndef ANDROID
		case GX_CALL_GETERRORA:	/* gx_geterror() function - ASCII mode */
			{
				if(params){
					struct GX_PARM_GETERRORA *mp = (struct GX_PARM_GETERRORA *)params;
					mp->code = ENOENT;
					if(mp->string && mp->maxlen>0) {
						gx_snprintf(mp->string, mp->maxlen, "gxsdldr: open error in %s (%s)",
							gxsdldr_modulename, gxsdldr_errstr);
						mp->string[mp->maxlen-1] = 0;
					}
				}
				return ENOENT;
			}
#endif
		default:
			/* Unknown function */
			break;
	}

	/* Unknown function */
	errno = EINVAL;
	return 0;
}

/******************************************************************************
 * Linux specific section
 ******************************************************************************/
#ifdef LINUX

/** Name of the library. */
#ifdef GX64
	const char *gxsdldr_modulename = "/usr/lib64/libgxsd.so.7";
#else
	#ifdef ANDROID
		const char *gxsdldr_modulename = "/vendor/lib/libgxsd.so";
	#else
		const char *gxsdldr_modulename = "/usr/lib32/libgxsd.so.7";
	#endif
#endif

/** Handle of the opened gxsd library. */
void *gxsdldr_handle = (void *)0;

/** Init function. */
void gxsdldr_init(void) {
	//LOG("gxsdldr_init\n");
	if(!gxsdldr_handle) {
#ifndef ANDROID
		//LOG("dlopen(libgxsd.so.7)\n");
		gxsdldr_handle = dlopen("libgxsd.so.7", RTLD_NOW | RTLD_GLOBAL);
		if(!gxsdldr_handle) {
			//LOG("dlopen(%s)\n",gxsdldr_modulename);
			gxsdldr_handle = dlopen(gxsdldr_modulename, RTLD_NOW | RTLD_GLOBAL);
		}
#else
		//LOG("dlopen(%s)\n",gxsdldr_modulename);
		gxsdldr_handle = dlopen(gxsdldr_modulename, RTLD_NOW | RTLD_GLOBAL);
#endif
	}
	//LOG("gxsdldr_handle: %p\n",gxsdldr_handle);

	if(!gxsdldr_handle) {
		gxsdldr_errstr[sizeof(gxsdldr_errstr)-1] = 0;
		strncpy(gxsdldr_errstr, dlerror(), sizeof(gxsdldr_errstr)-1);
		//LOG("Error 1: %s\n",gxsdldr_errstr);
		return;
	}

	//LOG("dlsym(gx_call)\n");
	gxsdldr_call = (gxldr_callfunc_t *)dlsym(gxsdldr_handle, "gx_call");
	//LOG("gxsdldr_call: %p\n",gxsdldr_call);
	if(!gxsdldr_call) {
		gxsdldr_call = 0;
		gxsdldr_errstr[sizeof(gxsdldr_errstr)-1] = 0;
		strncpy(gxsdldr_errstr, dlerror(), sizeof(gxsdldr_errstr)-1);
		dlclose(gxsdldr_handle);
		gxsdldr_handle = 0;
		//LOG("Error 2: %s\n",gxsdldr_errstr);
		return;
	}

	//LOG("dlsym(gxmoduleinfo)\n");
	int* vi = (int*) dlsym(gxsdldr_handle, "gxmoduleinfo");
	//LOG("gxmoduleinfo: %p\n",vi);

	if(vi && (vi[2]<0x07000000)) {
		gxsdldr_call = 0;
		snprintf(gxsdldr_errstr, sizeof(gxsdldr_errstr), "Old version of %s.", gxsdldr_modulename);
		gxsdldr_errstr[sizeof(gxsdldr_errstr)-1] = 0;
		dlclose(gxsdldr_handle);
		gxsdldr_handle = 0;
		//LOG("Error 3: %s\n",gxsdldr_errstr);
		return;
	}

	/* OK */
	struct GX_PARM_SENDCOMPVERSION compversion;
	compversion.version = GX_CURRENT_VERSION;
	struct gxHANDLE nullhandle = { 0 };
	//LOG("GX_CALL_SENDCOMPVERSION( %x)\n",GX_CURRENT_VERSION);
	gx_call(nullhandle, GX_CALL_SENDCOMPVERSION, &compversion);
	//LOG("gxsdldr_init end\n");
}

/** Clean up function. */
void gxsdldr_destroy(void) {
	gxsdldr_call = 0;	/* Restore the pointer */
	if(gxsdldr_handle) {
		dlclose(gxsdldr_handle);		/* Close the module */
		gxsdldr_handle = 0;
	}
}

#endif

/******************************************************************************
 * Windows specific section
 ******************************************************************************/
#ifdef WIN32

/** Name of the library. */
const char *gxsdldr_modulename = "gxsd7.dll";

/** Handle of the opened gxsd library. */
HMODULE gxsdldr_handle = (HMODULE)0;

/** Init function
 *
 * @param gxsdldr_call	Buffer for the main calling function pointer. */
bool gxsdldr_init(gxldr_callfunc_t** gxsdldr_call) {
	int *vi;
	struct GX_PARM_SENDCOMPVERSION compversion;
	struct gxHANDLE nullhandle = { 0 };

#ifdef _DEBUG
	char errbuf[1024];
#endif
	for(;;) {
		gxsdldr_handle = (HMODULE)LoadLibraryA(gxsdldr_modulename);
		if(gxsdldr_handle) break;
		gx_snprintf(gxsdldr_errstr, sizeof(gxsdldr_errstr), "Could not load: %hs", gxsdldr_modulename);
		gxsdldr_errstr[sizeof(gxsdldr_errstr)-1] = 0;
#ifdef _DEBUG
		gx_snprintf(errbuf, sizeof(errbuf),
			"GXSD Loader: Could not load: %hs", gxsdldr_modulename);
		errbuf[sizeof(errbuf)-1] = 0;
		if(MessageBoxA(0, errbuf, "GXSD Loader",
			MB_RETRYCANCEL | MB_TASKMODAL | MB_ICONERROR) == IDCANCEL) return 0;
#else
		return 0;
#endif
	}
	gxsdldr_errstr[0] = 0;

	(*gxsdldr_call) = (gxldr_callfunc_t *)GetProcAddress(gxsdldr_handle, "gx_call");
	if(!(*gxsdldr_call)) {
		(*gxsdldr_call) = 0;
		FreeLibrary(gxsdldr_handle);
		gxsdldr_handle = 0;
		gx_strncpy(gxsdldr_errstr,"No 'gx_call' entry found.",255);
#ifdef _DEBUG
		MessageBoxA(0, "GXSD Loader: No 'gx_call' entry found.",
			"GXSD Loader", MB_OK | MB_TASKMODAL | MB_ICONERROR);
#endif
		return 0;
	}

	vi=(int*)GetProcAddress(gxsdldr_handle,"gxmoduleinfo");

	if(vi && (vi[2]<0x07000000)) {
		(*gxsdldr_call) = 0;
		FreeLibrary(gxsdldr_handle);
		gxsdldr_handle = 0;
		gx_snprintf(gxsdldr_errstr, sizeof(gxsdldr_errstr), "Old version of %hs.", gxsdldr_modulename);
		gxsdldr_errstr[sizeof(gxsdldr_errstr)-1] = 0;
#ifdef _DEBUG
		gx_snprintf(errbuf, sizeof(errbuf),
			"GXSD Loader: Old version of %hs.", gxsdldr_modulename);
		errbuf[sizeof(errbuf)-1] = 0;
		MessageBoxA(0, errbuf, "GXSD Loader", MB_OK | MB_TASKMODAL | MB_ICONERROR);
#endif
		return 0;
	}

	gxsdldr_errstr[0] = 0;

	compversion.version = GX_CURRENT_VERSION;
	gx_call(nullhandle, GX_CALL_SENDCOMPVERSION, &compversion);
	return 1;
}

#endif
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn .amp
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	};
#endif
/******************************************************************************/
