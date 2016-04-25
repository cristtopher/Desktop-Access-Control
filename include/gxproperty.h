/*******************************************************************************
 * GX PROPERTY header file - V7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Property handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an ease to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the property handling module.
 */
/******************************************************************************/
#ifndef GX_PROPERTY_INCL
#define GX_PROPERTY_INCL
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4786)		/* truncated debug info */
#endif
/******************************************************************************/
#include "gxsd.h"
#include <wchar.h>
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/
/** Enumerations for property types. */
GX_ENUM GX_PROPERTYTYPES {
	GX_PROPERTY_INVALID		= 0,	/**< The item is not found in the property tree. */
	GX_PROPERTY_NOVALUE		= 1,	/**< Property without value. */
	GX_PROPERTY_DIRECT		= 2,	/**< Property with direct value. */
	GX_PROPERTY_INHERIT		= 3,	/**< Property with inherited value. */
	GX_PROPERTY_DEFAULT		= 4		/**< Property value in the default group. */
};
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/** Call codes for PROPERTY operations. */
enum {
	GX_CALL_GETPROPERTY		=	GX_CALL_GROUP_GX_PROPERTY	| 0x0000,	/**< Gets a value of the specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETPROPERTYA,			/**< Gets a value of the specified property (ASCII version). */
#endif
	GX_CALL_SETPROPERTY,			/**< Sets a value of the specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETPROPERTYA,			/**< Sets a value of the specified property (ASCII version). */
#endif
	GX_CALL_GETPROPERTYTYPE,		/**< Gets a type of the specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETPROPERTYTYPEA,		/**< Gets a type of the specified property (ASCII version). */
#endif
	GX_CALL_RMPROPERTIES,			/**< Removes a property and its subproperties (Unicode version). */
#ifndef ANDROID
	GX_CALL_RMPROPERTIESA,			/**< Removes a property and its subproperties (ASCII version). */
#endif
	GX_CALL_GETPROPERTIES,			/**< Gets the subproperties of a specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETPROPERTIESA,			/**< Gets the subproperties of a specified property (ASCII version). */
#endif
	GX_CALL_GETALLPROPERTIES,		/**< Gets the subproperties and parents of a specified property and from the \a /default tree (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETALLPROPERTIESA,		/**< Gets the subproperties and parents of a specified property and from the \a /default tree (ASCII version). */
#endif
	GX_CALL_GETPROPERTYPARENT,		/**< Gets the parent of a specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_GETPROPERTYPARENTA,		/**< Gets the parent of a specified property (ASCII version). */
#endif
	GX_CALL_SETPROPERTYPARENT,		/**< Changes the parent of a specified property (Unicode version). */
#ifndef ANDROID
	GX_CALL_SETPROPERTYPARENTA,		/**< Changes the parent of a specified property (ASCII version). */
#endif

	GX_CALL_LOADPROPERTIES	=	GX_CALL_GROUP_GX_PROPERTY	| 0x1000,	/**< Loads properties from a specified file (Unicode version). */
#ifndef ANDROID
	GX_CALL_LOADPROPERTIESA,		/**< Loads properties from a specified file (ASCII version). */
#endif
	GX_CALL_SAVEPROPERTIES,			/**< Saves properties into a specified file (Unicode version). */
#ifndef ANDROID
	GX_CALL_SAVEPROPERTIESA,		/**< Saves properties into a specified file (ASCII version). */
#endif
	GX_CALL_FLUSHPROPERTIES			/**< Forces writing of the buffered data. */
};

/******************************************************************************/
/** Parameter structure for the gx_getproperty() function (Unicode version). */
struct GX_PARM_GETPROPERTY {
	const wchar_t *name;		/**< Name of the property and place in the property tree. */
	wchar_t		  *string;		/**< Pointer to a memory area where to store the value. */
	int			   maxlen;		/**< Size of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getproperty() function (ASCII version). */
struct GX_PARM_GETPROPERTYA {
	const char	*name;			/**< Name of the property and place in the property tree. */
	char		*string;		/**< Pointer to a memory area where to store the value. */
	int			 maxlen;		/**< Size of the memory area in characters (or bytes). */
};
#endif

/** Parameter structure for the gx_setproperty() function (Unicode version). */
struct GX_PARM_SETPROPERTY {
	const wchar_t *name;		/**< Name of the property and place in the property tree. */
	const wchar_t *string;		/**< Value of the property. */
};

#ifndef ANDROID
/** Parameter structure for the gx_setproperty() function (ASCII version). */
struct GX_PARM_SETPROPERTYA {
	const char	*name;		/**< Name of a the property and place in the property tree. */
	const char	*string;	/**< Value of the property. */
};
#endif

/** Parameter structure for the gx_setproperttype() function (Unicode version). */
struct GX_PARM_GETPROPERTYTYPE {
	const wchar_t *name;	/**< Name of the property and place in the property tree. */
	int			   type;	/**< Type of the property. */
};

#ifndef ANDROID
/** Parameter structure for the gx_setproperttype() function (ASCII version). */
struct GX_PARM_GETPROPERTYTYPEA {
	const char	*name;		/**< Name of the property and place in the property tree. */
	int			 type;		/**< Type of the property. */
};
#endif

/** Parameter structure for the gx_rmproperties() function (Unicode version). */
struct GX_PARM_RMPROPERTIES {
	const wchar_t *name;	/**< Name of the property and/or place in the property tree. */
};

#ifndef ANDROID
/** Parameter structure for the gx_rmproperties() function (ASCII version). */
struct GX_PARM_RMPROPERTIESA {
	const char *name;		/**< Name of the property and/or place in the property tree. */
};
#endif

/** Parameter structure for the gx_getproperties() function (Unicode version). */
struct GX_PARM_GETPROPERTIES {
	const wchar_t *name;	/**< Place of the property in the property tree. */
	wchar_t		  *string;	/**< Pointer to a memory area where to store the names. */
	int 		   maxlen;	/**< Size of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getproperties() function (ASCII version). */
struct GX_PARM_GETPROPERTIESA {
	const char *name;		/**< Place of the property in the property tree. */
	char	   *string;		/**< Pointer to a memory area where to store the names. */
	int 	    maxlen;		/**< Size of the memory area in characters (or bytes). */
};
#endif

/** Parameter structure for the gx_getallproperties() function (Unicode version). */
struct GX_PARM_GETALLPROPERTIES {
	const wchar_t *name;	/**< Place of the property in the property tree. */
	wchar_t		  *string;	/**< Pointer to a memory area where to store the names. */
	int			   maxlen;	/**< Size of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getallproperties() function (ASCII version). */
struct GX_PARM_GETALLPROPERTIESA {
	const char	*name;		/**< Place of the property in the property tree. */
	char		*string;	/**< Pointer to a memory area where to store the names. */
	int			 maxlen;	/**< Size of the memory area in characters (or bytes). */
};
#endif

/** Parameter structure for the gx_getpropertyparent() function (Unicode version). */
struct GX_PARM_GETPROPERTYPARENT {
	const wchar_t *name;	/**< Name of the property and place in the property tree. */
	wchar_t 	  *string;	/**< Pointer to a memory area where to store the parent of the property. */
	int			   maxlen;	/**< Size of the memory area in characters (not bytes). */
};

#ifndef ANDROID
/** Parameter structure for the gx_getpropertyparent() function (ASCII version). */
struct GX_PARM_GETPROPERTYPARENTA {
	const char	*name;		/**< Name of the property and place in the property tree. */
	char 		*string;	/**< Pointer to a memory area where to store the parent of the property. */
	int			 maxlen;	/**< Size of the memory area in characters (or bytes). */
};
#endif

/** Parameter structure for the gx_setpropertyparent() function (Unicode version). */
struct GX_PARM_SETPROPERTYPARENT {
	const wchar_t *name;	/**< Name of the property and place in the property tree. */
	const wchar_t *string;	/**< Parent of the property. */
};

#ifndef ANDROID
/** Parameter structure for the gx_setpropertyparent() function (ASCII version). */
struct GX_PARM_SETPROPERTYPARENTA {
	const char *name;		/**< Name of the property and place in the property tree. */
	const char *string;		/**< Parent of the property. */
};
#endif

/** Parameter structure for the gx_loadproperties() function (Unicode version). */
struct GX_PARM_LOADPROPERTIES {
	const wchar_t *filename;	/**< Name of the property file. */
};

#ifndef ANDROID
/** Parameter structure for the gx_loadproperties() function (ASCII version). */
struct GX_PARM_LOADPROPERTIESA {
	const char *filename;		/**< Name of the property file. */
};
#endif

/** Parameter structure for the gx_saveproperties() function (Unicode version). */
struct GX_PARM_SAVEPROPERTIES {
	const wchar_t *filename;	/**< Name of the property file. */
	int			unicode;		/**< If it true, the file will be unicode. */
};

#ifndef ANDROID
/** Parameter structure for the gx_saveproperties() function (ASCII version). */
struct GX_PARM_SAVEPROPERTIESA {
	const char *filename;		/**< Name of the property file. */
	int			unicode;		/**< If it true, the file will be unicode. */
};
#endif
#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_property
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Gets the value of the specified property (Unicode version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const wchar_t *name,
						wchar_t *string, int maxlen) {

	struct GX_PARM_GETPROPERTY gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTY, &gp);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertya(gxHANDLE handle, const char *name,
						char *string, int maxlen) {

	struct GX_PARM_GETPROPERTYA gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTYA, &gp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const char *name,
						char *string, int maxlen) {
	return gx_getpropertya(handle, name, string, maxlen);
}
#endif
#endif
/******************************************************************************/
/** Gets the integer value of the specified property (Unicode version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyint(gxHANDLE handle, const wchar_t *name, int *ivalue) {
	wchar_t ibuf[GX_MAXLEN_INT];
	ibuf[GX_MAXLEN_INT-1] = 0;
	if(!gx_getproperty(handle, name, ibuf, GX_MAXLEN_INT-1)) return false;
	if(ivalue) *ivalue = gx_wcstol(ibuf, 0, 10);
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the integer value of the specified property (Unicode version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const wchar_t *name, int *ivalue) {
	return gx_getpropertyint(handle, name, ivalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Gets the integer value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyinta(gxHANDLE handle, const char *name, int *ivalue) {
	char ibuf[GX_MAXLEN_INT];
	ibuf[GX_MAXLEN_INT-1] = 0;
	if(!gx_getpropertya(handle, name, ibuf, GX_MAXLEN_INT-1)) return false;
	if(ivalue) *ivalue = atoi(ibuf);
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the integer value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const char *name, int *ivalue) {
	return gx_getpropertyinta(handle, name, ivalue);
}

/******************************************************************************/
/** Gets the integer value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyint(gxHANDLE handle, const char *name, int *ivalue) {
	return gx_getpropertyinta(handle, name, ivalue);
}
#endif
#endif
/******************************************************************************/
/** Gets the floating-point value of the specified property (Unicode version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyfloat(gxHANDLE handle, const wchar_t *name, double *fvalue) {
	wchar_t fbuf[GX_MAXLEN_FLOAT];
	fbuf[GX_MAXLEN_FLOAT-1] = 0;
	if(!gx_getproperty(handle, name, fbuf, GX_MAXLEN_FLOAT-1)) return false;
	if(fvalue) *fvalue = wcstod(fbuf, 0);
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the floating-point value of the specified property (Unicode version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const wchar_t *name, double *fvalue) {
	return gx_getpropertyfloat(handle, name, fvalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Gets the floating-point value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyfloata(gxHANDLE handle, const char *name, double *fvalue) {
	char fbuf[GX_MAXLEN_FLOAT];
	fbuf[GX_MAXLEN_FLOAT-1] = 0;
	if(!gx_getpropertya(handle, name, fbuf, sizeof(fbuf)-1)) return false;
	if(fvalue) *fvalue = atof(fbuf);
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the floating-point value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(gxHANDLE handle, const char *name, double *fvalue) {
	return gx_getpropertyfloata(handle, name, fvalue);
}

/******************************************************************************/
/** Gets the floating-point value of the specified property (ASCII version).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return
 *	the value from the inherited path or the \a /default path of the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyfloat(gxHANDLE handle, const char *name, double *fvalue) {
	return gx_getpropertyfloata(handle, name, fvalue);
}
#endif
#endif
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Unicode version).
 *
 * \note If the property exists it changes the value.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const wchar_t *name, const wchar_t *string) {
	struct GX_PARM_SETPROPERTY sp;
	sp.name = name;
	sp.string = string;
	return gx_call(handle, GX_CALL_SETPROPERTY, &sp);
}

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note If the property exists it changes the value.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertya(gxHANDLE handle, const char *name, const char *string) {
	struct GX_PARM_SETPROPERTYA sp;
	sp.name = name;
	sp.string = string;
	return gx_call(handle, GX_CALL_SETPROPERTYA, &sp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note If the property exists it changes the value.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const char *name, const char *string) {
	return gx_setpropertya(handle, name, string);
}
#endif
#endif
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Unicode version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The integer value is converted to string and then written in the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyint(gxHANDLE handle, const wchar_t *name, int ivalue) {
	wchar_t ibuf[GX_MAXLEN_INT];
	gx_snwprintf(ibuf, GX_MAXLEN_INT, L"%i", ivalue);
	ibuf[GX_MAXLEN_INT-1] = 0;
	return gx_setproperty(handle, name, ibuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Unicode version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The integer value is converted to string and then written in the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const wchar_t *name, int ivalue) {
	return gx_setpropertyint(handle, name, ivalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The integer value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyinta(gxHANDLE handle, const char *name, int ivalue) {
	char ibuf[GX_MAXLEN_INT];
	gx_snprintf(ibuf, GX_MAXLEN_INT, "%i", ivalue);
	ibuf[GX_MAXLEN_INT-1] = 0;
	return gx_setpropertya(handle, name, ibuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The integer value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const char *name, int ivalue) {
	return gx_setpropertyinta(handle, name, ivalue);
}

/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The integer value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyint(gxHANDLE handle, const char *name, int ivalue) {
	return gx_setpropertyinta(handle, name, ivalue);
}
#endif
#endif
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Unicode version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The floating-point value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyfloat(gxHANDLE handle, const wchar_t *name, double fvalue) {
	wchar_t fbuf[GX_MAXLEN_FLOAT];
	gx_snwprintf(fbuf, GX_MAXLEN_FLOAT, L"%f", fvalue);
	fbuf[GX_MAXLEN_FLOAT-1] = 0;
	return gx_setproperty(handle, name, fbuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Unicode version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The floating-point value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const wchar_t *name, double fvalue) {
	return gx_setpropertyfloat(handle, name, fvalue);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The floating-point value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyfloata(gxHANDLE handle, const char *name, double fvalue) {
	char fbuf[GX_MAXLEN_FLOAT];
	gx_snprintf(fbuf, sizeof(fbuf), "%f", fvalue);
	fbuf[GX_MAXLEN_FLOAT-1] = 0;
	return gx_setpropertya(handle, name, fbuf);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The floating-point value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(gxHANDLE handle, const char *name, double fvalue) {
	return gx_setpropertyfloata(handle, name, fvalue);
}

/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (ASCII version).
 *
 * \note
 *	If the property exists it changes the value.
 *	The floating-point value is converted to string and then written to the tree.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyfloat(gxHANDLE handle, const char *name, double fvalue) {
	return gx_setpropertyfloata(handle, name, fvalue);
}
#endif
#endif
/******************************************************************************/
/** Gets the type of the specified property (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertytype(gxHANDLE handle, const wchar_t *name, int *type) {
	struct GX_PARM_GETPROPERTYTYPE pt;
	int ret;
	pt.name = name;
	ret = gx_call(handle, GX_CALL_GETPROPERTYTYPE, &pt);
	if(ret) *type = pt.type;
	return ret;
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the type of the specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertytypea(gxHANDLE handle, const char *name, int *type) {
	struct GX_PARM_GETPROPERTYTYPEA pt;
	int ret;
	pt.name = name;
	ret = gx_call(handle, GX_CALL_GETPROPERTYTYPEA, &pt);
	if(ret) *type = pt.type;
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the type of the specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertytype(gxHANDLE handle, const char *name, int *type) {
	return gx_getpropertytypea(handle, name, type);
}
#endif
#endif
/******************************************************************************/
/** Removes a property and its subproperties from the specified place in the
 * property tree (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_rmproperties(gxHANDLE handle, const wchar_t *name) {
	struct GX_PARM_RMPROPERTIES rm;
	rm.name = name;
	return gx_call(handle, GX_CALL_RMPROPERTIES, &rm);
}

#ifndef ANDROID
/******************************************************************************/
/** Removes a property and its subproperties from the specified place in the
 * property tree (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_rmpropertiesa(gxHANDLE handle, const char *name) {
	struct GX_PARM_RMPROPERTIESA rm;
	rm.name = name;
	return gx_call(handle, GX_CALL_RMPROPERTIESA, &rm);
}

#ifdef __cplusplus
/******************************************************************************/
/** Removes a property and its subproperties from the specified place in the
 * property tree (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_rmproperties(gxHANDLE handle, const char *name) {
	return gx_rmpropertiesa(handle, name);
}
#endif
#endif

/******************************************************************************/
/** Gets the subproperties of a specified property from the property tree (Unicode version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperties(gxHANDLE handle, const wchar_t *name, wchar_t *string, int maxlen) {
	struct GX_PARM_GETPROPERTIES gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTIES, &gp);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the subproperties of a specified property from the property tree (ASCII version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertiesa(gxHANDLE handle, const char *name, char *string, int maxlen) {
	struct GX_PARM_GETPROPERTIESA gp;
	gp.name = name;
	gp.string = string;
	gp.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTIESA, &gp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the subproperties of a specified property from the property tree (ASCII version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperties(gxHANDLE handle, const char *name, char *string, int maxlen) {
	return gx_getpropertiesa(handle, name, string, maxlen);
}
#endif
#endif
/******************************************************************************/

/******************************************************************************/
/** Gets the subproperties and parents of a specified property from the property
 * tree and from the \a /default subtree (Unicode version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getallproperties(gxHANDLE handle, const wchar_t *name, wchar_t *string, int maxlen) {
	struct GX_PARM_GETALLPROPERTIES ap;
	ap.name = name;
	ap.string = string;
	ap.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETALLPROPERTIES, &ap);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the subproperties and parents of a specified property from the property
 * tree and from the \a /default subtree (ASCII version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getallpropertiesa(gxHANDLE handle, const char *name, char *string, int maxlen) {
	struct GX_PARM_GETALLPROPERTIESA ap;
	ap.name = name;
	ap.string = string;
	ap.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETALLPROPERTIESA, &ap);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the subproperties and parents of a specified property from the property
 * tree and from the \a /default subtree (ASCII version).
 *
 * \note The names are separated with LF.
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getallproperties(gxHANDLE handle, const char *name, char *string, int maxlen) {
	return gx_getallpropertiesa(handle, name, string, maxlen);
}
#endif
#endif
/******************************************************************************/

/******************************************************************************/
/** Changes the parent of a specified property (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Parent of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyparent(gxHANDLE handle, const wchar_t *name, const wchar_t *string) {
	struct GX_PARM_SETPROPERTYPARENT pd;
	pd.name = name;
	pd.string = string;
	return gx_call(handle, GX_CALL_SETPROPERTYPARENT, &pd);
}

#ifndef ANDROID
/******************************************************************************/
/** Changes the parent of a specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Parent of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyparenta(gxHANDLE handle, const char *name, const char *string) {
	struct GX_PARM_SETPROPERTYPARENTA pd;
	pd.name = name;
	pd.string = string;
	return gx_call(handle, GX_CALL_SETPROPERTYPARENTA, &pd);
}

#ifdef __cplusplus
/******************************************************************************/
/** Changes the parent of a specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Parent of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyparent(gxHANDLE handle, const char *name, const char *string) {
	return gx_setpropertyparenta(handle, name, string);
}
#endif
#endif
/******************************************************************************/
/******************************************************************************/
/** Gets the parent of a specified property (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the parent of the property.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyparent(gxHANDLE handle, const wchar_t *name, wchar_t *string, int maxlen) {
	struct GX_PARM_GETPROPERTYPARENT gd;
	gd.name = name;
	gd.string = string;
	gd.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTYPARENT, &gd);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the parent of a specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the parent of the property.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyparenta(gxHANDLE handle, const char *name, char *string, int maxlen) {
	struct GX_PARM_GETPROPERTYPARENTA gd;
	gd.name = name;
	gd.string = string;
	gd.maxlen = maxlen;
	return gx_call(handle, GX_CALL_GETPROPERTYPARENTA, &gd);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the parent of a specified property (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the parent of the property.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyparent(gxHANDLE handle, const char *name, char *string, int maxlen) {
	return gx_getpropertyparenta(handle, name, string, maxlen);
}
#endif
#endif
/******************************************************************************/
/** Loads properties from a specified file (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadproperties(gxHANDLE handle, const wchar_t *name) {
	struct GX_PARM_LOADPROPERTIES lp;
	lp.filename = name;
	return gx_call(handle, GX_CALL_LOADPROPERTIES, &lp);
}

#ifndef ANDROID
/******************************************************************************/
/** Loads properties from a specified file (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadpropertiesa(gxHANDLE handle, const char *name) {
	struct GX_PARM_LOADPROPERTIESA lp;
	lp.filename = name;
	return gx_call(handle, GX_CALL_LOADPROPERTIESA, &lp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Loads properties from a specified file (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadproperties(gxHANDLE handle, const char *name) {
	return gx_loadpropertiesa(handle, name);
}
#endif
#endif
/******************************************************************************/
/** Saves properties into a specified file (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @param unicode If it is true, the file will be unicode.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_saveproperties(gxHANDLE handle, const wchar_t *name, int unicode) {
	struct GX_PARM_SAVEPROPERTIES sp;
	sp.filename = name;
	sp.unicode = unicode;
	return gx_call(handle, GX_CALL_SAVEPROPERTIES, &sp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Saves properties into a specified file (Unicode version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_saveproperties(gxHANDLE handle, const wchar_t *name) {
	return gx_saveproperties(handle, name, false);
}
#endif

#ifndef ANDROID
/******************************************************************************/
/** Saves properties into a specified file (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @param unicode If it is true, the file will be unicode.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savepropertiesa(gxHANDLE handle, const char *name, int unicode GX_DEFARG(false)) {
	struct GX_PARM_SAVEPROPERTIESA sp;
	sp.filename = name;
	sp.unicode = unicode;
	return gx_call(handle, GX_CALL_SAVEPROPERTIESA, &sp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Saves properties into a specified file (ASCII version).
 *
 * @param handle Handle of an opened property module.
 * @param name Name of the property file.
 * @param unicode If it is true, the file will be unicode.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_saveproperties(gxHANDLE handle, const char *name, int unicode GX_DEFARG(false)) {
	return gx_savepropertiesa(handle, name, unicode);
}
#endif
#endif
/******************************************************************************/
/** Forces writing of all buffered data.
 *
 * @param handle Handle of an opened property module.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_flushproperties(gxHANDLE handle) {
	return gx_call(handle, GX_CALL_FLUSHPROPERTIES, (void *)0);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gets the value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const wchar_t *name, wchar_t *string, int maxlen) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the value.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const char *name, char *string, int maxlen) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}
#endif
/******************************************************************************/
/** Gets the integer value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const wchar_t *name, int *ivalue) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, ivalue);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the integer value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param ivalue Pointer to a memory area where to store the integer value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const char *name, int *ivalue) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, ivalue);
}
#endif
/******************************************************************************/
/** Gets the floating-point value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const wchar_t *name, double *fvalue) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, fvalue);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the floating-point value of the specified property (Obsolete).
 *
 * \note
 *	If there is no such property in the property tree, it tries to return the
 *	value from the inherited path or the \a /default path of the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param fvalue Pointer to a memory area where to store the floating-point value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperty(const char *name, double *fvalue) {
	return gx_getproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, fvalue);
}
#endif
/******************************************************************************/
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note If the property exists it changes the value.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const wchar_t *name, const wchar_t *string) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string);
}

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note If the property exists it changes the value.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const char *name, const char *string) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string);
}
#endif
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note
 *	If the property exists it changes the value. The integer value is converted
 *	to string and then written to the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const wchar_t *name, int ivalue) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, ivalue);
}

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note
 *	If the property exists it changes the value. The integer value is converted
 *	to string and then written to the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param ivalue Integer value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const char *name, int ivalue) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, ivalue);
}
#endif
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note
 *	If the property exists it changes the value. The floating-point value is
 *	converted to string and then written to the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const wchar_t *name, double fvalue) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, fvalue);
}

#ifndef ANDROID
/******************************************************************************/
/** Creates a property with the specified name in the property tree and assigns
 * the specified value to it (Obsolete).
 *
 * \note
 *	If the property exists it changes the value. The floating-point value is
 * converted to string and then written to the tree.
 *
 * @param name Name of the property and place in the property tree.
 * @param fvalue Floating-point value of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setproperty(const char *name, double fvalue) {
	return gx_setproperty(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, fvalue);
}
#endif
/******************************************************************************/
/** Gets the type of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertytype(const wchar_t *name, int *type) {
	return gx_getpropertytype(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, type);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the type of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertytype(const char *name, int *type) {
	return gx_getpropertytype(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, type);
}
#endif
/******************************************************************************/
/** Removes a property and its subproperties at the specified place from the
 * property tree (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_rmproperties(const wchar_t *name) {
	return gx_rmproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name);
}

#ifndef ANDROID
/******************************************************************************/
/** Removes a property and its subproperties the a specified place from the
 * property tree (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_rmproperties(const char *name) {
	return gx_rmproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name);
}
#endif
/******************************************************************************/
/******************************************************************************/
/** Gets the subproperties of the specified property from the property tree (Obsolete).
 *
 * \note The names are separated with LF.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperties(const wchar_t *name, wchar_t *string, int maxlen) {
	return gx_getproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}
#ifndef ANDROID
/******************************************************************************/
/** Gets the subproperties of the specified property from the property tree (Obsolete).
 *
 * \note The names are separated with LF.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getproperties(const char *name, char *string, int maxlen) {
	return gx_getproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}
#endif
/******************************************************************************/
/******************************************************************************/
/** Gets the subproperties and parents of a specified property from the property
 * tree and from the \a /default subtree (Obsolete).
 *
 * \note The names are separated with LF.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getallproperties(const wchar_t *name, wchar_t *string, int maxlen) {
	return gx_getallproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the subproperties and parents of a specified property from the property
 * tree and from the \a /default subtree (Obsolete).
 *
 * \note The names are separated with LF.
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the names.
 * @param maxlen Size of the memory area in characters (or bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getallproperties(const char *name, char *string, int maxlen) {
	return gx_getallproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}
#endif
/******************************************************************************/
/******************************************************************************/
/** Changes the parent of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param string Parent of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyparent(const wchar_t *name, const wchar_t *string) {
	return gx_setpropertyparent(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string);
}

#ifndef ANDROID
/******************************************************************************/
/** Changes the parent of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param string Parent of the property.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_setpropertyparent(const char *name, const char *string) {
	return gx_setpropertyparent(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string);
}
#endif
/******************************************************************************/
/******************************************************************************/
/** Gets the parent of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the parent of the property.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyparent(const wchar_t *name, wchar_t *string, int maxlen) {
	return gx_getpropertyparent(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}

#ifndef ANDROID
/******************************************************************************/
/** Gets the parent of a specified property (Obsolete).
 *
 * @param name Name of the property and place in the property tree.
 * @param string Pointer to a memory area where to store the parent of the property.
 * @param maxlen Size of the memory area in characters (not bytes).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_getpropertyparent(const char *name, char *string, int maxlen) {
	return gx_getpropertyparent(gx_direct(GX_CALL_GROUP_GX_PROPERTY), name, string, maxlen);
}
#endif
/******************************************************************************/
/** Forces a write of all buffered data (Obsolete).
 *
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_flushproperties(void) {
	return gx_flushproperties(gx_direct(GX_CALL_GROUP_GX_PROPERTY));
}
#endif
#endif

/******************************************************************************/
/** @} */
/******************************************************************************/

#ifdef GX_DOTNET
#pragma managed
#endif

/******************************************************************************/
/******************************************************************************/
#if !defined(NO_GX_CLASSES) && !defined(ANDROID)
/******************************************************************************/
/** Base class for the GX property functions. */
GX_CLASS gxProperty : public gxHandle {
public:
	/** Class initialization. */
	inline gxProperty() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxproperty", L"")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxproperty", L"")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with property group.
	 *
	 * \note Do not use this directly. We recommend, to use the \ref gxPropertyFile class instead.
	 *
	 * @param groupcode The code of the call-group.
	 */
	inline gxProperty(int groupcode) gxFuncThrowsError : gxHandle(groupcode) {
	}

	/** Class initialization with the name of the module (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxProperty(const wchar_t *modname) gxFuncThrowsError {
		if(!gx_openmodule(this, modname ? modname : L"gxproperty", L"")) gxthrow;
	}

	/** Class initialization with the name of the module (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxProperty(const char *modname) gxFuncThrowsError {
		if(!gx_openmodulea(this, modname ? modname : "gxproperty", "")) gxthrow;
	}
#endif
#ifdef GX_UNICODE
	/** Class initialization with the name of the module (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxProperty(gxInStr modname) gxFuncThrowsError {
		GX_GETSTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, L"")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, L"")) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif
#ifdef GX_ASCII
	/** Class initialization with the name of the module (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxProperty(gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, "")) gxthrow;
	}
#endif
	
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Loads properties from a specified file (Unicode version).
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Load(const wchar_t *name) gxFuncThrowsError {
		bool st = gx_loadproperties(*this, name) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads properties from a specified file (ASCII version).
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Load(const char *name) gxFuncThrowsError {
		bool st = gx_loadproperties(*this, name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Loads properties from a specified file (Unicode version).
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Load(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_loadproperties(h, _name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Loads properties from a specified file (ASCII version).
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Load(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_loadpropertiesa(*this, _name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Saves properties into a specified file (Unicode version).
	 *
	 * @param name Name of the property file.
	 * @param unicode If it is true, the file will be unicode.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(const wchar_t *name, bool unicode = false) gxFuncThrowsError {
		bool st = gx_saveproperties(*this, name, (int)unicode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves properties into a specified file (ASCII version).
	 *
	 * @param name Name of the property file.
	 * @param unicode If it is true, the file will be unicode.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(const char *name, bool unicode = false) gxFuncThrowsError {
		bool st = gx_saveproperties(*this, name, (int)unicode) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Saves properties into a specified file (Unicode version).
	 *
	 * @param name Name of the property file.
	 * @param unicode If it is true, the file will be unicode.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(gxInStr name, bool unicode) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_saveproperties(h, _name, (int)unicode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves properties into a specified file in ASCII format.
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_saveproperties(h, _name, false) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// GX_UNICODE

#ifdef GX_ASCII
	/** Saves properties into a specified file in ASCII format.
	 *
	 * @param name Name of the property file.
	 * @param unicode If it is true, the file will be unicode.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(gxInAStr name, bool unicode) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_saveproperties(*this, _name, (int)unicode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves properties into a specified file in ASCII format.
	 *
	 * @param name Name of the property file.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Save(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_savepropertiesa(*this, _name, false) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Forces a write of all buffered data.
	 *
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool Flush(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_flushproperties(h) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the value.
	 * @param maxlen Size of the memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperty(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Value of the property. An exception is thrown or false is
	 *			returned if an error occurs. */
	inline std::wstring GetProperty(const wchar_t *name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getproperty(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::wstring(buf);
	}
#endif

	/** Gets the value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the value.
	 * @param maxlen Size of the memory area in characters (or bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperty(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Value of the property. An exception is thrown or false is
	 *			returned if an error occurs. */
	inline std::string GetProperty(const char *name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getproperty(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::string(buf);
	}
#endif

#endif
#ifdef GX_UNICODE
	/** Gets the value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The value of the property. An exception is thrown or false is
	 * 		returned if an error occurs. */
	inline gxOutStr GetProperty(gxInStr name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getproperty(h, _name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTSTRING(buf);
	}
#endif

#ifdef GX_ASCII
	/** Gets the value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The value of the property. An exception is thrown or false is
	 * 		returned if an error occurs. */
	inline gxOutAStr GetProperty(gxInAStr name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETASTRING(_name, name);
		if(!gx_getpropertya(*this, _name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTASTRING(buf);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the integer value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Pointer to a memory area where to store the integer value.
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool GetProperty(const wchar_t *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getpropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the integer value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Pointer to a memory area where to store the integer value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperty(const char *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getpropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Gets the integer value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The integer value of the property. An exception is thrown or
	 *			false is returned if an error occurs. */
	inline int GetPropertyInt(gxInStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getpropertyint(h, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#ifdef GX_ASCII
	/** Gets the integer value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The integer value of the property. An exception is thrown or
	 *			false is returned if an error occurs. */
	inline int GetPropertyInt(gxInAStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getpropertyinta(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the floating-point value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Pointer to a memory area where to store the floating-point value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperty(const wchar_t *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getpropertyfloat(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the floating-point value of the specified property (ASCII version). If there is no such
	 * property in the property tree, it tries to return the value from the inherited
	 * path or the \a /default path of the tree.
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Pointer to a memory area where to store the floating-point value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperty(const char *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getpropertyfloata(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets the floating-point value of the specified property (Unicode version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The floating-point value of the property. An exception is thrown or
	 *			false is returned if an error occurs. */
	inline double GetPropertyFloat(gxInStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getpropertyfloat(h, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#ifdef GX_ASCII
	/** Gets the floating-point value of the specified property (ASCII version).
	 *
	 * \note
	 *	If there is no such property in the property tree, it tries to return
	 *	the value from the inherited path or the \a /default path of the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The floating-point value of the property. An exception is thrown or
	 *			false is returned if an error occurs. */
	inline double GetPropertyFloat(gxInAStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getpropertyfloata(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note If the property exists it changes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(const wchar_t *name, const wchar_t *string) gxFuncThrowsError {
		bool st = gx_setproperty(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note If the property exists it changes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(const char *name, const char *string) gxFuncThrowsError {
		bool st = gx_setpropertya(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes the value of the property in the property tree (Unicode version).
	 *
	 * \note If the property does not exist it creates a new with no value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearProperty(const wchar_t *name) gxFuncThrowsError {
		bool st = gx_setproperty(*this, name, (const wchar_t *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes the value of the property in the property tree (ASCII version).
	 *
	 * \note If the property does not exist it creates a new with no value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearProperty(const char *name) gxFuncThrowsError {
		bool st = gx_setpropertya(*this, name, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note If the property exists it changes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInStr name, gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_setproperty(h, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a property with the specified name in the property tree with no value (Unicode version).
	 *
	 * \note If the property exists it removes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setproperty(h, _name, (const wchar_t *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes the value of the property in the property tree (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearProperty(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setproperty(h, _name, (const wchar_t *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// GX_UNICODE

#ifdef GX_ASCII
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note If the property exists it changes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInAStr name, gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		GX_GETASTRING(_str, str);
		bool st = gx_setpropertya(*this, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a property with the specified name in the property tree with no value (ASCII version).
	 *
	 * \note If the property exists it removes the value.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setpropertya(*this, _name, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes the value of the property in the property tree (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearProperty(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setpropertya(*this, _name, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The integer value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(const wchar_t *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setpropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The integer value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(const char *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setpropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The integer value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInStr name, int ivalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setpropertyint(h, _name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The integer value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInAStr name, int ivalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setpropertyinta(*this, _name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The floating-point value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(const wchar_t *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setpropertyfloat(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The floating-point value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Floating-point value of the property.
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool SetProperty(const char *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setproperty(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (Unicode version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The floating-point value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInStr name, double fvalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setpropertyfloat(h, _name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Creates a property with the specified name in the property tree and assigns
	 * the specified value to it (ASCII version).
	 *
	 * \note
	 *	If the property exists it changes the value.
	 *	The floating-point value is converted to string and then written to the tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetProperty(gxInAStr name, double fvalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setpropertyfloata(*this, _name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the type of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetPropertyType(const wchar_t *name, int *type) gxFuncThrowsError {
		bool st = gx_getpropertytype(*this, name, type) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the type of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param type Pointer to a memory area where to store the property type (see \ref GX_PROPERTYTYPES).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetPropertyType(const char *name, int *type) gxFuncThrowsError {
		bool st = gx_getpropertytypea(*this, name, type) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the type of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Type of the property. An exception is thrown or false is
	 *		returned if an error occurs. */
	inline int GetPropertyType(const wchar_t *name) gxFuncThrowsError {
		int type = -1;
		if(!gx_getpropertytype(*this, name, &type)) gxthrow;
		return type;
	}

	/** Gets the type of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Type of the property. An exception is thrown or false is
	 *		returned if an error occurs. */
	inline int GetPropertyType(const char *name) gxFuncThrowsError {
		int type = -1;
		if(!gx_getpropertytypea(*this, name, &type)) gxthrow;
		return type;
	}
#endif // !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets the type of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Type of the property. An exception is thrown or false is
	 *		returned if an error occurs. */
	inline int GetPropertyType(gxInStr name) gxFuncThrowsError {
		int type = -1;
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getpropertytype(h, _name, &type)) gxthrow;
		return type;
	}
#endif

#ifdef GX_ASCII
	/** Gets the type of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Type of the property. An exception is thrown or false is
	 *		returned if an error occurs. */
	inline int GetPropertyType(gxInAStr name) gxFuncThrowsError {
		int type = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getpropertytype(*this, _name, &type)) gxthrow;
		return type;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Removes a property and its subproperties from the specified place in the
	 * property tree (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool RmProperties(const wchar_t *name) gxFuncThrowsError {
		bool st = gx_rmproperties(*this, name) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes a property and its subproperties from the specified place in the
	 * property tree (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool RmProperties(const char *name) gxFuncThrowsError {
		bool st = gx_rmpropertiesa(*this, name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Removes a property and its subproperties from the specified place in the
	 * property tree (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool RmProperties(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_rmproperties(h, _name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Removes a property and its subproperties from the specified place in the
	 * property tree (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool RmProperties(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_rmpropertiesa(*this, _name) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the subproperties of a specified property from the property tree (Unicode version).
	 *
	 * \note The names are separated with LF.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the names.
	 * @param maxlen Size of the memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperties(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getproperties(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the subproperties of a specified property from the property tree (ASCII version).
	 *
	 * \note The names are separated with LF.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the names.
	 * @param maxlen Size of the memory area in characters (or bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetProperties(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getpropertiesa(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the subproperties of a specified property from the property tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline std::vector<std::wstring> GetProperties(const wchar_t *name) gxFuncThrowsError {
		std::vector<std::wstring> array;
		bool st;
		__gx_func_strarray(st, wchar_t, array, name, wcslen, gx_getproperties);
		return array;
	}

	/** Gets the subproperties of a specified property from the property tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline std::vector<std::string> GetProperties(const char *name) gxFuncThrowsError {
		std::vector<std::string> array;
		bool st;
		__gx_func_strarray(st, char, array, name, strlen, gx_getpropertiesa);
		return array;
	}
#endif
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets the subproperties of a specified property from the property tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline gxOutStrArray GetProperties(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		gxOutStrArray _array;
		int st;
#ifdef GX_DOTNET
		GX_GETHANDLE(h);
#endif
		__gx_func_outstrarray(st, _array, _name, gx_getproperties);
		return _array;
	}
#endif	// GX_UNICODE
#ifdef GX_ASCII
	/** Gets the subproperties of a specified property from the property tree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline gxOutAStrArray GetProperties(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		gxOutAStrArray array;
		bool st;
		__gx_func_outastrarray(st, array, _name, gx_getpropertiesa);
		return array;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the subproperties and parents of a specified property from the property tree and
	 * from the \a /default subtree (Unicode version).
	 *
	 * \note The names are separated with LF.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the names.
	 * @param maxlen Size of the memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetAllProperties(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getallproperties(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets the subproperties and parents of a specified property from the property tree and
	 * from the \a /default subtree (ASCII version).
	 *
	 * \note The names are separated with LF.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the names.
	 * @param maxlen Size of the memory area in characters (or bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetAllProperties(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getallproperties(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the subproperties and parents of a specified property from the property tree and
	 * from the \a /default subtree (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline std::vector<std::wstring> GetAllProperties(const wchar_t *name) gxFuncThrowsError {
		std::vector<std::wstring> array;
		bool st;
		__gx_func_strarray(st, wchar_t, array, name, wcslen, gx_getallproperties);
		return array;
	}

	/** Gets the subproperties and parents of a specified property from the property tree and
	 * from the \a /default subtree (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline std::vector<std::string> GetAllProperties(const char *name) gxFuncThrowsError {
		std::vector<std::string> array;
		bool st;
		__gx_func_strarray(st, char, array, name, strlen, gx_getallpropertiesa);
		return array;
	}
#endif
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets the subproperties and parents of a specified property from the property tree
	 * and from the \a /default subtree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline gxOutStrArray GetAllProperties(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		gxOutStrArray _array;
		int st;
#ifdef GX_DOTNET
		GX_GETHANDLE(h);
#endif
		__gx_func_outstrarray(st, _array, _name, gx_getallproperties);
		return _array;
	}
#endif
#ifdef GX_ASCII
	/** Gets the subproperties and parents of a specified property from the property tree
	 * and from the \a /default subtree.
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return The array of names. An exception is thrown or false is returned
	 *		 if an error occurs. */
	inline gxOutAStrArray GetAllProperties(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		gxOutAStrArray array;
		bool st;
		__gx_func_outastrarray(st, array, _name, gx_getallproperties);
		return array;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Changes the parent of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Parent of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetPropertyParent(const wchar_t *name, const wchar_t *string) gxFuncThrowsError {
		bool st = gx_setpropertyparent(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Changes the parent of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Parent of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetPropertyParent(const char *name, const char *string) gxFuncThrowsError {
		bool st = gx_setpropertyparent(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Changes the parent of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param str Parent of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetPropertyParent(gxInStr name, gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_setpropertyparent(h, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Changes the parent of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param str Parent of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetPropertyParent(gxInAStr name, gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		GX_GETASTRING(_str, str);
		bool st = gx_setpropertyparenta(*this, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets the parent of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the parent of the property.
	 * @param maxlen Size of the memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetPropertyParent(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getpropertyparent(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the parent of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Parent of the property. An exception is thrown or false is
	 *			returned if an error occurs. */
	inline std::wstring GetPropertyParent(const wchar_t *name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getpropertyparent(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::wstring(buf);
	}
#endif

	/** Gets the parent of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @param string Pointer to a memory area where to store the parent of the property.
	 * @param maxlen Size of the memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetPropertyParent(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getpropertyparenta(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets the parent of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Parent of the property. An exception is thrown or false is
	 *			returned if an error occurs. */
	inline std::string GetPropertyParent(const char *name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getpropertyparent(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::string(buf);
	}
#endif
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets the parent of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Parent of the property. An exception is thrown or false is returned
	 *			if an error occurs. */
	inline gxOutStr GetPropertyParent(gxInStr name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getpropertyparent(h, _name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTSTRING(buf);
	}
#endif
#ifdef GX_ASCII
	/** Gets the parent of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return Parent of the property. An exception is thrown or false is returned
	 *			if an error occurs. */
	inline gxOutAStr GetPropertyParent(gxInAStr name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETASTRING(_name, name);
		int st = gx_getpropertyparent(*this, _name, buf, GX_MAXLEN_PROPVALUE);
		if(!st) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTASTRING(buf);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Removes the parent link of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearPropertyParent(const wchar_t *name) gxFuncThrowsError {
		bool st = gx_setpropertyparent(*this, name, (const wchar_t *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes the parent link of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearPropertyParent(const char *name) gxFuncThrowsError {
		bool st = gx_setpropertyparent(*this, name, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Removes the parent link of a specified property (Unicode version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearPropertyParent(gxInStr name) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setpropertyparent(h, _name, (const wchar_t *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Removes the parent link of a specified property (ASCII version).
	 *
	 * @param name Name of the property and place in the property tree.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool ClearPropertyParent(gxInAStr name) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setpropertyparenta(*this, _name, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param string Pointer to a memory area where to store the value.
	 * @param maxlen Size of memory area in characters (not bytes).
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const wchar_t *name, wchar_t *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getmoduleproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property. An exception is thrown or false
	 *		 is returned if an error occurs. */
	inline std::wstring GetModuleProperty(const wchar_t *name) gxFuncThrowsError {
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
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const char *name, char *string, int maxlen) gxFuncThrowsError {
		bool st = gx_getmoduleproperty(*this, name, string, maxlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(NO_GX_STL)
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property. An exception is thrown or false
	 *		 is returned if an error occurs. */
	inline std::string GetModuleProperty(const char *name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		if(!gx_getmoduleproperty(*this, name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			buf[0] = 0;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return std::string(buf);
	}
#endif
#endif

#ifdef GX_UNICODE
	/** Gets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property. An exception is thrown or false
	 *		 is returned if an error occurs. */
	inline gxOutStr GetModuleProperty(gxInStr name) gxFuncThrowsError {
		wchar_t buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getmoduleproperty(h, _name, buf, GX_MAXLEN_PROPVALUE)) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTSTRING(buf);
	}
#endif

#ifdef GX_ASCII
	/** Gets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Value of the property. An exception is thrown or false
	 *		 is returned if an error occurs. */
	inline gxOutAStr GetModuleProperty(gxInAStr name) gxFuncThrowsError {
		char buf[GX_MAXLEN_PROPVALUE+1];
		GX_GETASTRING(_name, name);
		int st = gx_getmodulepropertya(*this, _name, buf, GX_MAXLEN_PROPVALUE);
		if(!st) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		buf[GX_MAXLEN_PROPVALUE] = 0;
		return GX_PUTASTRING(buf);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Pointer to an integer to store the value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const wchar_t *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Integer value of the property. An exception is thrown or false
	 *			is returned if an error occurs. */
	inline int GetModulePropertyInt(const wchar_t *name) gxFuncThrowsError {
		int ret = -1;
		if(!gx_getmodulepropertyint(*this, name, &ret)) gxthrow;
		return ret;
	}

	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Pointer to an integer to store the value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const char *name, int *ivalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Integer value of the property. An exception is thrown or false
	 *			is returned if an error occurs. */
	inline int GetModulePropertyInt(const char *name) gxFuncThrowsError {
		int ret = -1;
		if(!gx_getmodulepropertyinta(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif

#ifdef GX_UNICODE
	/** Gets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Integer value of the property. An exception is thrown or false
	 *			is returned if an error occurs. */
	inline int GetModulePropertyInt(gxInStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getmodulepropertyint(h, _name, &ret)) gxthrow;
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Gets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Integer value of the property. An exception is thrown or false
	 *			is returned if an error occurs. */
	inline int GetModulePropertyInt(gxInAStr name) gxFuncThrowsError {
		int ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getmodulepropertyinta(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Pointer to a floating-point to store the value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const wchar_t *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyfloat(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Floating-point value of the property. An exception is thrown
	 *			or false is returned if an error occurs. */
	inline double GetModulePropertyFloat(const wchar_t *name) gxFuncThrowsError {
		double ret = -1;
		if(!gx_getmodulepropertyfloat(*this, name, &ret)) gxthrow;
		return ret;
	}

	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Pointer to a floating-point to store the value.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool GetModuleProperty(const char *name, double *fvalue) gxFuncThrowsError {
		bool st = gx_getmodulepropertyfloata(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Floating-point value of the property. An exception is thrown
	 *			or false is returned if an error occurs. */
	inline double GetModulePropertyFloat(const char *name) gxFuncThrowsError {
		double ret = -1;
		if(!gx_getmodulepropertyfloata(*this, name, &ret)) gxthrow;
		return ret;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Gets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @return Floating-point value of the property. An exception is thrown
	 *			or false is returned if an error occurs. */
	inline double GetModulePropertyFloat(gxInStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		if(!gx_getmodulepropertyfloat(h, _name, &ret)) gxthrow;
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Gets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @return Floating-point value of the property. An exception is thrown
	 *			or false is returned if an error occurs. */
	inline double GetModulePropertyFloat(gxInAStr name) gxFuncThrowsError {
		double ret = -1;
		GX_GETASTRING(_name, name);
		if(!gx_getmodulepropertyfloata(*this, _name, &ret)) gxthrow;
		return ret;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Sets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const wchar_t *name, const wchar_t *string) gxFuncThrowsError {
		bool st = gx_setmoduleproperty(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param string Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const char *name, const char *string) gxFuncThrowsError {
		bool st = gx_setmoduleproperty(*this, name, string) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Sets a property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInStr name, gxInStr str) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETSTRING(_str, str);
		GX_GETHANDLE(h);
		bool st = gx_setmoduleproperty(h, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Sets a property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param str Value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInAStr name, gxInAStr str) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		GX_GETASTRING(_str, str);
		bool st = gx_setmoduleproperty(*this, _name, _str) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Sets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const wchar_t *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyint(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const char *name, int ivalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyinta(*this, name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Sets an integer property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInStr name, int ivalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setmodulepropertyint(h, _name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Sets an integer property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param ivalue Integer value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInAStr name, int ivalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setmodulepropertyinta(*this, _name, ivalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Sets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const wchar_t *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyfloat(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Sets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(const char *name, double fvalue) gxFuncThrowsError {
		bool st = gx_setmodulepropertyfloata(*this, name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Sets a floating-point property of the specified module (Unicode version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInStr name, double fvalue) gxFuncThrowsError {
		GX_GETSTRING(_name, name);
		GX_GETHANDLE(h);
		bool st = gx_setmodulepropertyfloat(h, _name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Sets a floating-point property of the specified module (ASCII version).
	 *
	 * @param name Name of the property.
	 * @param fvalue Floating-point value of the property.
	 * @return An exception is thrown or false is returned if an error occurs. */
	inline bool SetModuleProperty(gxInAStr name, double fvalue) gxFuncThrowsError {
		GX_GETASTRING(_name, name);
		bool st = gx_setmodulepropertyfloata(*this, _name, fvalue) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
};

/******************************************************************************/
/** Class for the GX properties stored in file. */
GX_CLASS gxPropertyFile : public gxProperty {
private:
	/** This function does nothing in the gxpropfile module. */
	inline bool Flush(void) {
		return false;
	}

public:
	/** Class initialization. */
	inline gxPropertyFile() gxFuncThrowsError : gxProperty(L"gxpropfile") {
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with the name of the module (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyFile(const wchar_t *modname) gxFuncThrowsError :
		gxProperty(modname ? modname : L"gxpropfile") {
	}

	/** Class initialization with the name of the module (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyFile(const char *modname) gxFuncThrowsError :
		gxProperty(modname) {
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Class initialization with module name (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyFile(gxInStr modname) gxFuncThrowsError {
		GX_GETSTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, 0)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, 0)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif
#ifdef GX_ASCII
	/** Class initialization with module name (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyFile(gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, 0)) gxthrow;
	}
#endif
	
};
/******************************************************************************/
#if 0
/** Class for the GX properties cached in the server process. */
GX_CLASS gxPropertyClient : public gxProperty {
private:
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter. */
	inline bool Load(const wchar_t *name) { return false; }
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter. */
	inline bool Load(const char *name) { return false; }
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.
	 * @param unicode Obsolete parameter. */
	inline bool Save(const wchar_t *name, bool unicode = false) { return false; }
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.
	 * @param unicode Obsolete parameter. */
	inline bool Save(const char *name, bool unicode = false) { return false; }
#endif

#ifdef GX_UNICODE
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.*/
	inline bool Load(gxInStr name) { return false; }
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.*/
	inline bool Save(gxInStr name) { return false; }
#endif
#ifdef GX_ASCII
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.*/
	inline bool Load(gxInAStr name) { return false; }
	/** This function does nothing in the gxpropclient module.
	 *
	 * @param name Obsolete parameter.*/
	inline bool Save(gxInAStr name) { return false; }
#endif

public:
	/** Class initialization. */
	inline gxPropertyClient() gxFuncThrowsError : gxProperty(L"gxpropclient") {
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with the name of the module (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyClient(const wchar_t *modname) gxFuncThrowsError :
				gxProperty(modname ? modname : L"gxpropclient") {
	}

	/** Class initialization with the name of the module (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyClient(const char *modname) gxFuncThrowsError :
				gxProperty(modname) {
	}
#endif

#ifdef GX_UNICODE
	/** Class initialization with the name of the module (Unicode version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyClient(gxInStr modname) gxFuncThrowsError {
		GX_GETSTRING(_modname, modname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, _modname, 0)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, _modname, 0)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif

#ifdef GX_ASCII
	/** Class initialization with the name of the module (ASCII version).
	 *
	 * @param modname Name of the module. */
	inline gxPropertyClient(gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, 0)) gxthrow;
	}
#endif
	
};
#endif
/******************************************************************************/
#endif	// !NO_GX_CLASSES && __cplusplus && !ANDROID
/******************************************************************************/
#ifdef GX_NAMESPACES
}
#endif
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(pop)
#endif
/******************************************************************************/
#endif//GXPROPERTY_INCL
/******************************************************************************/
