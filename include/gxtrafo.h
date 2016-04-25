/******************************************************************************
 * GX TRAFO header file - V7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Transformation handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * The GX system supports transformations between different coordinate systems.
 * It is easy to realize transformations from a plain rotation to the more
 * difficult image straightening ones using these functions. Every transformation
 * structure contains the mappings needed for the transformation. These mappings
 * describe the location of a specific point in the other coordinate system.
 *
 * This file contains the descriptions of classes and functions of the transformation handling module.
 */
/******************************************************************************/
#ifndef GX_TRAFO_INCL
#define GX_TRAFO_INCL
/******************************************************************************/
#include "gxsd.h"
#include "gxerror.h"
#include "gxvariant.h"
#include <assert.h>
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -rch
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#if defined(GX_DOTNET) && !defined(GX_MANUAL)
	#pragma unmanaged
	#define gxTRAFO _gxTRAFO
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/******************************************************************************/
/** Call codes for transformation operations. */
enum {
	GX_CALL_INITTRAFO	= GX_CALL_GROUP_GX_TRAFO,	/**< Call code for the gx_inittrafo() function. */
	GX_CALL_ALLOCTRAFO,			/**< Call code for the gx_alloctrafo() function. */
	GX_CALL_FREETRAFO,			/**< Call code for the gx_freetrafo() function. */
	GX_CALL_REFTRAFO,			/**< Call code for the gx_reftrafo() function. */
	GX_CALL_UNREFTRAFO,			/**< Call code for the gx_unreftrafo() function. */
	GX_CALL_CREATETRAFO,		/**< Call code for the gx_createtrafo() function. */
	GX_CALL_LOADTRAFO,			/**< Call code for the gx_loadtrafo() function (Unicode version). */
	GX_CALL_LOADTRAFOA,			/**< Call code for the gx_loadtrafo() function (ASCII version). */
	GX_CALL_SAVETRAFO,			/**< Call code for the gx_savetrafo() function (Unicode version). */
	GX_CALL_SAVETRAFOA,			/**< Call code for the gx_savetrafo() function (ASCII version). */
	GX_CALL_COPYTRAFO,			/**< Call code for the gx_copytrafo() function. */
	GX_CALL_TRAFO,				/**< Call code for the gx_trafo() function. */
	GX_CALL_ISVALIDTRAFO,		/**< Call code for the gx_isvalidtrafo() function. */
	GX_CALL_ITRAFO,				/**< Call code for the gx_itrafo() function. */
	GX_CALL_TRAFOTOVARIANT,		/**< Call code for the gx_trafotovariant() function. */
	GX_CALL_TRAFOFROMVARIANT,	/**< Call code for the gx_trafofromvariant() function. */
	GX_CALL_ALLOCTRAFO_DBG,		/**< Call code for the gx_alloctrafo_dbg() function. */
};
#endif /*)*/

#ifndef GX_SWIGIF /* ( */
#ifndef GX_DOTNET
/** Structure which stores data of a trafo. */
struct gxTRAFO {
	int		gxid;			/**< Structure identifier. */
	int		ref;			/**< Reference counter. */
	gxRCT 	source_frame;	/**< The transformation works within this frame.  The coordinates are defined on the source coordinate system. */
	int		xsize;			/**< Horizontal size of the transformation structure. */
	int		ysize;			/**< Vertical size of the transformation structure. */
	gxPNTF	*base;			/**< Elements of the transformation structure (Size is xsize*ysize*3). */
	void	*reserved;		/**< Reserved for the inverse operation. */
};

#ifndef __cplusplus
	/** ANSI C workaround */
	typedef struct gxTRAFO gxTRAFO;
#endif

#ifndef GX_MANUAL
/** Parameter structure for the gx_createtrafo() function. */
struct GX_PARM_CREATETRAFO {
	gxTRAFO 	*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const gxPG2 *pairs;		/**< Pointer to the list point pairs. */
	int			 npair;		/**< Number of points in the list of point pairs. */
	const gxRCT *frame;		/**< The transformation works within this frame.  The coordinates are defined on the source coordinate system. */
	int			 resolution;/**< Distances between two transformation elements. */
};
#endif

#else
/** Unmanaged gxTRAFO structure for .net. */
struct gxTRAFO {
	int		gxid;			/**< Structure identifier. */
	int		ref;			/**< Reference counter. */
	_gxRCT source_frame;	/**< The transformation works within this frame.  The coordinates are defined on the source coordinate system. */
	int		xsize;			/**< Horizontal size of the transformation structure. */
	int		ysize;			/**< Vertical size of the transformation structure. */
	_gxPNTF *base;			/**< Elements of the transformation structure (Size is xsize*ysize*3). */
	void	*reserved;		/**< Reserved for the inverse operation. */
};

/** Unmanaged parameter structure for .net. */
struct GX_PARM_CREATETRAFO {
	gxTRAFO *ptrafo;		/**< Pointer to an initialized transformation structure. */
	const _gxPG2 *pairs;	/**< Pointer to the list point pairs. */
	int			 npair;		/**< Number of points in the list of point pairs. */
	const _gxRCT *frame;	/**< The transformation works within this frame.  The coordinates are defined on the source coordinate system. */
	int			 resolution;/**< Distances between two transformation elements. */
};
#endif
#endif /* SWIGIF ( */

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/

/** Parameter structure for the gx_loadtrafo() function (Unicode version). */
struct GX_PARM_LOADTRAFO {
	gxTRAFO	*ptrafo;		/**< Pointer to an initialized transformation structure. */
	const wchar_t *filename;/**< Name of the file containing the data. */
};

/** Parameter structure for the gx_loadtrafo() function (ASCII version). */
struct GX_PARM_LOADTRAFOA {
	gxTRAFO	*ptrafo;		/**< Pointer to an initialized transformation structure. */
	const char	*filename;	/**< Name of the file containing the data. */
};

/** Parameter structure for the gx_savetrafo() function (Unicode version). */
struct GX_PARM_SAVETRAFO {
	const gxTRAFO 	*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const wchar_t	*filename;	/**< Name of the file containing the data. */
};

/** Parameter structure for the gx_savetrafo() function (ASCII version). */
struct GX_PARM_SAVETRAFOA {
	const gxTRAFO *ptrafo;		/**< Pointer to an initialized transformation structure. */
	const char		*filename;	/**< Name of the file containing the data. */
};

/** Parameter structure for the gx_copytrafo() function. */
struct GX_PARM_COPYTRAFO {
	gxTRAFO			*target;	/**< Pointer to an initialized destination structure. */
	const gxTRAFO	*source;	/**< Pointer to the source. */
};

#ifndef GX_DOTNET
/** Parameter structure for the gx_trafo() function. */
struct GX_PARM_TRAFO {
	gxTRAFO		*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const gxPNT	*source;	/**< List of source points. */
	gxPNT		*target;	/**< Place of transformed points. */
	int			 npoints;	/**< Number of points in the list. */
};

/** Parameter structure for the gx_itrafo() function. */
struct GX_PARM_ITRAFO {
	gxTRAFO		*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const gxPNT	*source;	/**< List of source points. */
	gxPNT		*target;	/**< Place of transformed points. */
	int			 npoints;	/**< Number of points in the list. */
};
#else
/** Unmanaged parameter structure for .net. */
struct GX_PARM_TRAFO {
	gxTRAFO			*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const _gxPNT	*source;	/**< List of source points. */
	_gxPNT			*target;	/**< Place of transformed points. */
	int				 npoints;	/**< Number of points in the list. */
};

/** Unmanaged parameter structure for .net. */
struct GX_PARM_ITRAFO {
	gxTRAFO			*ptrafo;	/**< Pointer to an initialized transformation structure. */
	const _gxPNT	*source;	/**< List of source points. */
	_gxPNT			*target;	/**< Place of transformed points. */
	int			 	npoints;	/**< Number of points in the list. */
};
#endif	// !GX_DOTNET

/** Parameter structure for the gx_trafotovariant() function. */
struct GX_PARM_TRAFOTOVARIANT {
	gxTRAFO		*ptrafo;	/**< Source transformation structure. */
	int			varid;		/**< New variant identifier. */
	gxVARIANT	variant;	/**< Initialized variant structure. */
};

/** Parameter structure for the gx_trafofromvariant() function. */
struct GX_PARM_TRAFOFROMVARIANT {
	gxTRAFO		*ptrafo;	/**< Pointer to an initialized transformation structure. */
	gxVARIANT	variant;	/**< Variant with an embedded transformation structure. */
};

/** Parameter structure for the gx_alloctrafo_dbg() function. */
struct GX_PARM_ALLOCTRAFO_DBG {
	gxTRAFO		*ptrafo;	/**< Trafo allocated by the alloc function. */
	const char	*file;		/**< Name of the file. */
	int			 line;		/**< Line number. */
};

#endif	/* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_trafo
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Initializes a transformation structure.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an uninitialized transformation structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_inittrafo(gxHANDLE handle, gxTRAFO *ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_INITTRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** Allocates a transformation structure.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to a transformation structure pointer, where the
 *               function copies the recently allocated structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_alloctrafo(gxHANDLE handle, gxTRAFO **ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_ALLOCTRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** Allocates a transformation structure (Debug version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to a transformation structure pointer, where the
 *               function copies the recently allocated structure.
 * @param file File name.
 * @param line Line number.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_alloctrafo_dbg(gxHANDLE handle, gxTRAFO **ptrafo, const char *file, int line) {

	struct GX_PARM_ALLOCTRAFO_DBG atd;
	int ret;
	assert(ptrafo);
	atd.file = file;
	atd.line = line;
	ret = gx_call(handle, GX_CALL_ALLOCTRAFO_DBG, (void *)&atd);
	if(ret) *ptrafo = atd.ptrafo;
	return ret;
}

/******************************************************************************/
/** Frees the specified transformation structure.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_freetrafo(gxHANDLE handle, gxTRAFO *ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_FREETRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_reference
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Increases the reference number of the specified transformation structure.
 *
 * The reference number indicates how many processes are currently using the
 * specified structure.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_reftrafo(gxHANDLE handle, gxTRAFO *ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_REFTRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** Decreases the reference number of the specified transformation structure.
 *
 * As it reaches value zero the structure will be freed.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_unreftrafo(gxHANDLE handle, gxTRAFO *ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_UNREFTRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_trafo
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Creates a transformation structure based on the specified parameters.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param pairs Pointer to the list point pairs.
 * @param npair Number of points in the list of point pairs.
 * @param frame The transformation works with in this frame.  The coordinates are defined on the source coordinate system.
 * @param resolution Distances between two transformation elements.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_createtrafo(gxHANDLE handle, gxTRAFO *ptrafo,
#ifndef __cplusplus
							const gxPG2 *pairs, int npair,
						 	const gxRCT frame, int resolution)
#elif !defined GX_DOTNET
							const gxPG2 *pairs, int npair,
						 	const gxRCT GX_REF_STRUCT(frame), int resolution)
#else
							const _gxPG2 *pairs, int npair,
						 	const _gxRCT GX_REF_UNMANAGED_STRUCT(frame), int resolution)
#endif
								{

	struct GX_PARM_CREATETRAFO ct;
	assert(ptrafo);
	assert(pairs);
	assert(npair > 0);
	ct.ptrafo = ptrafo;
	ct.pairs = pairs;
	ct.npair = npair;
	ct.frame = &frame;
	ct.resolution = resolution;
	return gx_call(handle, GX_CALL_CREATETRAFO, (void *)&ct);
}

/******************************************************************************/
/** Loads data from the specified transformation file to an initialized structure (Unicode version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file containing the data.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadtrafo(gxHANDLE handle, gxTRAFO *ptrafo,
							const wchar_t *filename) {
	struct GX_PARM_LOADTRAFO lt;
	assert(ptrafo);
	assert(filename);
	lt.ptrafo = ptrafo;
	lt.filename = filename;
	return gx_call(handle, GX_CALL_LOADTRAFO, (void *)&lt);
}

/******************************************************************************/
/** Loads data from the specified transformation file to an initialized structure (ASCII version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file containing the data.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadtrafoa(gxHANDLE handle, gxTRAFO *ptrafo, const char *filename) {
	struct GX_PARM_LOADTRAFOA lt;
	assert(ptrafo);
	assert(filename);
	lt.ptrafo = ptrafo;
	lt.filename = filename;
	return gx_call(handle, GX_CALL_LOADTRAFOA, (void *)&lt);
}

#ifdef __cplusplus
/******************************************************************************/
/** Loads data from the specified transformation file to an initialized structure (ASCII version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file containing the data.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadtrafo(gxHANDLE handle, gxTRAFO *ptrafo, const char *filename) {
	return gx_loadtrafoa(handle, ptrafo, filename);
}
#endif

/******************************************************************************/
/** Saves the specified transformation structure to a file (Unicode version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savetrafo(gxHANDLE handle, gxTRAFO *ptrafo, const wchar_t *filename) {
	struct GX_PARM_SAVETRAFO st;
	assert(ptrafo);
	assert(filename);
	st.ptrafo = ptrafo;
	st.filename = filename;
	return gx_call(handle, GX_CALL_SAVETRAFO, (void *)&st);
}

/******************************************************************************/
/** Saves the specified transformation structure to a file (ASCII version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savetrafoa(gxHANDLE handle, gxTRAFO *ptrafo, const char *filename) {
	struct GX_PARM_SAVETRAFOA st;
	assert(ptrafo);
	assert(filename);
	st.ptrafo = ptrafo;
	st.filename = filename;
	return gx_call(handle, GX_CALL_SAVETRAFOA, (void *)&st);
}

#ifdef __cplusplus
/******************************************************************************/
/** Saves the specified transformation structure to a file (ASCII version).
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savetrafo(gxHANDLE handle, gxTRAFO *ptrafo, const char *filename) {
	return gx_savetrafoa(handle, ptrafo, filename);
}
#endif

/******************************************************************************/
/** Copies one transformation structure to another.
 *
 * The destination structure must be initialized. Its data will be overwritten.
 * The source structure remains unchanged.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized destination structure.
 * @param ptrafo_source Pointer to the source.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_copytrafo(gxHANDLE handle, gxTRAFO *ptrafo,
							const gxTRAFO *ptrafo_source) {
	struct GX_PARM_COPYTRAFO ct;
	assert(ptrafo);
	assert(ptrafo_source);
	ct.target = ptrafo;
	ct.source = ptrafo_source;
	return gx_call(handle, GX_CALL_COPYTRAFO, (void *)&ct);
}

/******************************************************************************/
/** Transforms points from the source sequence with the help of the specified
 * structure then writes the result to the destination sequence list.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source List of source points.
 * @param target Place of transformed points.
 * @param npoints Number of points in the list.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafo(gxHANDLE handle, gxTRAFO *ptrafo,
#ifndef GX_DOTNET
					  const gxPNT *source, gxPNT *target, int npoints)
#else
					  const _gxPNT *source, _gxPNT *target, int npoints)
#endif
							{
	struct GX_PARM_TRAFO tp;
	assert(ptrafo);
	assert(source);
	assert(target);
	assert(npoints > 0);
	tp.ptrafo = ptrafo;
	tp.source = source;
	tp.target = target;
	tp.npoints = npoints;
	return gx_call(handle, GX_CALL_TRAFO, (void *)&tp);
}

/******************************************************************************/
/** Transforms one point from the source with the help of the specified
 * structure then writes the result to the destination point.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source Pointer to the source point.
 * @param target Place of transformed point.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafo_pnt(gxHANDLE handle, gxTRAFO *ptrafo,
#ifndef GX_DOTNET
						  const gxPNT *source, gxPNT *target)
#else
						  const _gxPNT *source, _gxPNT *target)
#endif
								{
	struct GX_PARM_TRAFO tp;
	assert(ptrafo);
	assert(source);
	assert(target);
	tp.ptrafo = ptrafo;
	tp.source = source;
	tp.target = target;
	tp.npoints = 1;
	return gx_call(handle, GX_CALL_TRAFO, (void *)&tp);
}

/******************************************************************************/
/** Inverse transformation.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source List of source points.
 * @param target Place of transformed points.
 * @param npoints Number of points in the list.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_itrafo(gxHANDLE handle, gxTRAFO *ptrafo,
#ifndef GX_DOTNET
						const gxPNT *source, gxPNT *target,
#else
						const _gxPNT *source, _gxPNT *target,
#endif
						int npoints) {
	struct GX_PARM_ITRAFO tp;
	assert(ptrafo);
	assert(source);
	assert(target);
	assert(npoints > 0);
	tp.ptrafo = ptrafo;
	tp.source = source;
	tp.target = target;
	tp.npoints = npoints;
	return gx_call(handle, GX_CALL_ITRAFO, (void *)&tp);
}

/******************************************************************************/
/** Inverse transformation.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source Pointer to the source point.
 * @param target Place of transformed point.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_itrafo_pnt(gxHANDLE handle, gxTRAFO *ptrafo,
#ifndef GX_DOTNET
						   const gxPNT *source, gxPNT *target)
#else
						   const _gxPNT *source, _gxPNT *target)
#endif
							{
	struct GX_PARM_ITRAFO tp;
	assert(ptrafo);
	assert(source);
	assert(target);
	tp.ptrafo = ptrafo;
	tp.source = source;
	tp.target = target;
	tp.npoints = 1;
	return gx_call(handle, GX_CALL_ITRAFO, (void *)&tp);
}

/******************************************************************************/
/** Checks the specified transformation structure.
 *
 * @param handle Handle of the module.
 * @param ptrafo Pointer to an initialized transformation structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_isvalidtrafo(gxHANDLE handle, const gxTRAFO *ptrafo) {
	assert(ptrafo);
	return gx_call(handle, GX_CALL_ISVALIDTRAFO, (void *)ptrafo);
}

/******************************************************************************/
/** Embedds a transformation structure into a variant.
 *
 * @param handle	Handle of the module.
 * @param source	Pointer to the source transformation structure.
 * @param varid		The id for the created variant.
 * @param target	Pointer to the initialized destination variant.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafotovariant(gxHANDLE handle, gxTRAFO *source, int varid, gxVARIANT *target) {
	struct GX_PARM_TRAFOTOVARIANT ttv;
	int ret;
	assert(target);
	assert(source);
	ttv.ptrafo = source;
	ttv.varid = varid;
	ret = gx_call(handle, GX_CALL_TRAFOTOVARIANT, &ttv);
	if(ret && target) *target = ttv.variant;
	return ret;
}

/******************************************************************************/
/** Loads an embedded transformation structure from a variant.
 *
 * @param handle	Handle of the module.
 * @param target	Pointer to the destination transformation structure.
 * @param source	Variant with an embedded transformation structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafofromvariant(gxHANDLE handle, gxTRAFO **target, gxVARIANT source) {
	struct GX_PARM_TRAFOFROMVARIANT tfv;
	int ret;
	assert(target);
	tfv.variant = source;
	ret = gx_call(handle, GX_CALL_TRAFOFROMVARIANT, &tfv);
	if(ret && target) *target = tfv.ptrafo;
	return ret;
}

#ifdef __cplusplus
/******************************************************************************/
/** Initializes a transformation structure.
 *
 * @param ptrafo Pointer to a non initialized transformation structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_inittrafo(gxTRAFO *ptrafo) {
	return gx_inittrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** Allocates a transformation structure.
 *
 * @param ptrafo Pointer to a transformation structure pointer, to where the
 *               function copies the recently allocated structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_alloctrafo(gxTRAFO **ptrafo) {
	return gx_alloctrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** Allocates a transformation structure (Debug version).
 *
 * @param ptrafo Pointer to a transformation structure pointer, where the
 *               function copies the recently allocated structure.
 * @param file File name.
 * @param line Line number.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_alloctrafo_dbg(gxTRAFO **ptrafo, const char *file, int line) {
	return gx_alloctrafo_dbg(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, file, line);
}

#ifdef GX_TESTLEAKS
#if defined(_MSC_VER) && _MSC_VER<1400
	/** Release/Debug workaround. */
	#define gx_alloctrafo(ptrafo) gx_alloctrafo_dbg(ptrafo, __FILE__, __LINE__)
#else
	/** Release/Debug workaround. */
	#define gx_alloctrafo(...) gx_alloctrafo_dbg(__VA_ARGS__, __FILE__, __LINE__)
#endif
#endif

/******************************************************************************/
/** Frees the specified transformation structure.
 *
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_freetrafo(gxTRAFO *ptrafo) {
	return gx_freetrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_reference
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Increases the reference number of the specified transformation structure.
 *
 * The reference number indicates how many processes are currently using the
 * specified structure.
 *
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_reftrafo(gxTRAFO *ptrafo) {
	return gx_reftrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** Decreases the reference number of the specified transformation structure.
 *
 * As it reaches value zero the structure will be freed.
 *
 * @param ptrafo Pointer to an initialized structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_unreftrafo(gxTRAFO *ptrafo) {
	return gx_unreftrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_trafo
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Creates a transformation structure based on the specified parameters.
 *
 * @param ptrafo Pointer to an initialized structure.
 * @param pairs Pointer to the list of point pairs.
 * @param npair Number of point in the list of point pairs.
 * @param frame The transformation works with in this frame. The coordinates are
 *				defined on the source coordinate system.
 * @param resolution Distances between two transformation elements.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
#ifndef GX_DOTNET
inline int gx_createtrafo(gxTRAFO *ptrafo, const gxPG2 *pairs,
							int npair, const gxRCT GX_REF_STRUCT(frame), int resolution) {
#else
inline int gx_createtrafo(gxTRAFO *ptrafo, const _gxPG2 *pairs,
							int npair, const _gxRCT GX_REF_UNMANAGED_STRUCT(frame), int resolution) {
#endif

	return gx_createtrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, pairs,
						npair, frame, resolution);
}

/******************************************************************************/
/** Loads data from the specified transformation file to an initialized structure (Unicode version).
 *
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file containing the data.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadtrafo(gxTRAFO *ptrafo, const wchar_t *filename) {
	return gx_loadtrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, filename);
}

/******************************************************************************/
/** Loads data from the specified transformation file to an initialized structure (ASCII version).
 *
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file containing the data.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_loadtrafo(gxTRAFO *ptrafo, const char *filename) {
	return gx_loadtrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, filename);
}

/******************************************************************************/
/** Saves the specified transformation structure to a file (Unicode version).
 *
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savetrafo(gxTRAFO *ptrafo, const wchar_t *filename) {
	return gx_savetrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, filename);
}

/******************************************************************************/
/** Saves the specified transformation structure to a file (ASCII version).
 *
 * @param ptrafo Pointer to an initialized structure.
 * @param filename Name of the file.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_savetrafo(gxTRAFO *ptrafo, const char *filename) {
	return gx_savetrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, filename);
}

/******************************************************************************/
/** Copies one transformation structure to another.
 *
 * The destination structure must be initialized. Its data will be overwritten.
 * The source structure remains unchanged.
 *
 * @param ptrafo Pointer to an initialized destination structure.
 * @param ptrafo_source Pointer to the source.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_copytrafo(gxTRAFO *ptrafo, const gxTRAFO *ptrafo_source) {
	return gx_copytrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, ptrafo_source);
}

/******************************************************************************/
/** Transforms points from the source sequence with the help of the specified
 * structure then writes the result to the destination sequence list.
 *
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source List of source points.
 * @param target Place of transformed points.
 * @param npoints Number of points in the list.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
#ifndef GX_DOTNET
inline int gx_trafo(gxTRAFO *ptrafo, const gxPNT *source,
						gxPNT *target, int npoints) {
#else
inline int gx_trafo(gxTRAFO *ptrafo, const _gxPNT *source,
						_gxPNT *target, int npoints) {
#endif
	return gx_trafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, source, target, npoints);
}

/******************************************************************************/
/** Transforms one point from the source with the help of the specified
 * structure then writes the result to the destination point.
 *
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source Pointer to the source point.
 * @param target Place of transformed point.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
#ifndef GX_DOTNET
inline int gx_trafo_pnt(gxTRAFO *ptrafo, const gxPNT *source,
						gxPNT *target) {
#else
inline int gx_trafo_pnt(gxTRAFO *ptrafo, const _gxPNT *source,
						_gxPNT *target) {
#endif
	return gx_trafo_pnt(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, source, target);
}

/******************************************************************************/
/** Inverse transformation.
 *
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source List of source points.
 * @param target Place of transformed points.
 * @param npoints Number of points in the list.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
#ifndef GX_DOTNET
inline int gx_itrafo(gxTRAFO *ptrafo, const gxPNT *source,
						gxPNT *target, int npoints) {
#else
inline int gx_itrafo(gxTRAFO *ptrafo, const _gxPNT *source,
						_gxPNT *target, int npoints) {
#endif
	return gx_itrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, source, target, npoints);
}

/******************************************************************************/
/** Inverse transformation.
 *
 * @param ptrafo Pointer to an initialized transformation structure.
 * @param source Pointer to the source point.
 * @param target Place of transformed point.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
#ifndef GX_DOTNET
inline int gx_itrafo_pnt(gxTRAFO *ptrafo, const gxPNT *source,
						gxPNT *target) {
#else
inline int gx_itrafo_pnt(gxTRAFO *ptrafo, const _gxPNT *source,
						_gxPNT *target) {
#endif
	return gx_itrafo_pnt(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo, source, target);
}

/******************************************************************************/
/** Checks the specified transformation structure.
 *
 * @param ptrafo Pointer to an initialized transformation structure.
 * @return In case of existing structure the return value is non-zero. */
inline int gx_isvalidtrafo(const gxTRAFO *ptrafo) {
	return gx_isvalidtrafo(gx_direct(GX_CALL_GROUP_GX_TRAFO), ptrafo);
}

/******************************************************************************/
/** Embedds a transformation structure into a variant.
 *
 * @param source	Pointer to the source transformation structure.
 * @param varid		The id for the created variant.
 * @param target	Pointer to the initialized destination variant.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafotovariant(gxTRAFO *source, int varid, gxVARIANT *target) {
	return gx_trafotovariant(gx_direct(GX_CALL_GROUP_GX_TRAFO), source, varid, target);
}

/******************************************************************************/
/** Loads an embedded transformation structure from a variant.
 *
 * @param target	Pointer to the destination transformation structure.
 * @param source	Variant with an embedded transformation structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline int gx_trafofromvariant(gxTRAFO **target, gxVARIANT source) {
	return gx_trafofromvariant(gx_direct(GX_CALL_GROUP_GX_TRAFO), target, source);
}

#endif	// __cplusplus

/******************************************************************************/
/** @} */
/******************************************************************************/

#endif	// !NO_GX_FUNCTIONS && !GX_SWIGIF

/******************************************************************************/

#ifdef GX_DOTNET
#pragma managed
#endif

/******************************************************************************/
#ifndef NO_GX_CLASSES

#ifndef GX_EXT_MODULE
/******************************************************************************/
/** Class for the TRAFO data and some low-level functions. */
#ifndef GX_DOTNET
GX_CLASS gxTrafoData {
#else
GX_CLASS gxTrafoData : public System::IDisposable {
#endif

#if !defined(GX_SWIGIF) /*(*/

#if !defined(GX_DOTNET) && !defined(GX_MANUAL)
public:
	gxTRAFO *_trafo;	/**< Pointer to the allocated gxTRAFO structure. */
#endif

#if defined(GX_DOTNET)
#if !defined(GX_MANUAL)
private:
	GX_INDIRECTION_NOGC(gxTRAFO) _trafo;	/**< Pointer to the allocated gxTRAFO structure. */
#endif

public:
	/** Returns the local trafo data pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxOutPtr _get_trafo(void) GX_CONST {
		return GX_PUTPTR(_trafo);
	}
	/** Modifies the local trafo data pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
inline void _set_trafo(gxInPtr ptr) {
		_trafo = (GX_INDIRECTION_NOGC(gxTRAFO))ptr.ToPointer();
	}
#endif

#endif /*)*/

public:
	/** Class initialization. */
	inline gxTrafoData() {
		_trafo = (gxTRAFO *)0;
	}
	/** Class termination. */
	inline ~gxTrafoData() gxFuncThrowsError {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxTrafoData() gxFuncThrowsError {
		_Dispose();
	}
#else
	/** It disposes the class. */
inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
		/** no base class */		
}
#endif
	
private:

	inline void _Dispose(void) {
		gxassert(!_trafo || (_trafo->ref == 0));
	}

public:

	/** Returns the reference counter.
	 *
	 * @see gxTRAFO gx_reftrafo() gx_unreftrafo()
	 *
	 * @return Reference counter of the gxTRAFO structure. */
	inline int ref(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->ref;
	}
#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns the source frame.
	 *
	 * @return Source frame element of the gxTRAFO structure. */
	inline const gxRCT &source_frame(void) const gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->source_frame;
	}
#endif

	/** Returns the horizontal size of the transformation area.
	 *
	 * @return Horizontal size of the transformation area. */
	inline int xsize(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->xsize;
	}
	/** Returns the vertical size of the transformation area.
	 *
	 * @return Vertical size of the transformation area. */
	inline int ysize(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->ysize;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns the transformation points.
	 *
	 * @return Transformation points of the gxTRAFO structure. */
	inline const gxPNTF *base(void) const gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->base;
	}
	/** Returns the transformation structure.
	 *
	 * return Transformation structure. */
	inline const gxTRAFO *trafo(void) const gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo;
	}

	/** Returns a pointer to the transformation structure. */
	inline operator gxTRAFO *() const {
		return _trafo;
	}

	/** Returns the reference to the transformation structure. */
	inline operator gxTRAFO &() const gxFuncThrowsError {
		gxassert(_trafo);
		return *_trafo;
	}
#endif
};

/******************************************************************************/
/** Class for the TRAFO functions. */
GX_CLASS gxTrafoHandler : public gxHandle {
public:
	/** Class initialization with default arguments. */
	inline gxTrafoHandler() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxtrafo", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxtrafo", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Class initialization with another trafo handler.
	 *
	 * @param src Pointer to another trafo handler. The reference of
	 *		this trafo handle will be increased. */
	inline gxTrafoHandler(const gxHANDLE *src) gxFuncThrowsError : gxHandle() {
		if(src) {
			handle = src->handle;
			if(!gx_refhandle(*this)) gxthrow;
		}
	}
	/** Class initialization with another trafo handler.
	 *
	 * @param src Pointer to another trafo handle. The reference of
	 *		this trafo handle will be increased. */
	inline gxTrafoHandler(const gxHANDLE GX_REF_STRUCT(src)) gxFuncThrowsError : gxHandle() {
		handle = src.handle;
		if(!gx_refhandle(*this)) gxthrow;
	}
	/** Class initialization with the place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafoHandler(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError {

		if(!gx_openmodule(this, modname ? modname : L"gxtrafo", propname)) gxthrow;
	}

	/** Class initialization with the place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafoHandler(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError {

		if(!gx_openmodulea(this, modname ? modname : "gxtrafo", propname)) gxthrow;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Class initialization with place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafoHandler(gxInStr propname, gxInStr modname) gxFuncThrowsError {
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
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxTrafoHandler(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxtrafo", _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxtrafo", _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif	// GX_UNICODE

#ifdef GX_ASCII
	/** Class initialization with place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafoHandler(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, _propname)) gxthrow;
	}
	/** Class initialization with place of the properties (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxTrafoHandler(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		if(!gx_openmodulea(this, "gxtrafo", _propname)) gxthrow;
	}
#endif

	/** Class initalization with another trafo handle.
	 *
	 * @param src Source trafo handle. The reference of this
	 *		trafo handle will be increased. */
	inline gxTrafoHandler(GX_CONST gxTrafoHandler GX_REF_CLASS(src)) gxFuncThrowsError : gxHandle() {
#ifndef GX_DOTNET
		handle = src.handle;
		if(!gx_refhandle(*this)) gxthrow;
#else
		gxHANDLE h = { src GX_M _get_handle() };
		if(!gx_refhandle(h)) gxthrow;
		_set_handle(h.handle);
#endif
	}

};

#endif	// GX_EXT_MODULE
/******************************************************************************/
#if !defined(GX_MANUAL)

#if !defined(GX_DOTNET)
#define GX_GETTRAFO(name)	gxTRAFO *name = _trafo
#else
#define GX_GETTRAFO(name)	gxTRAFO *name = (gxTRAFO *)_get_trafo().ToPointer()
#endif

#endif
/******************************************************************************/
#ifndef GX_EXT_MODULE
/******************************************************************************/
/** Class for the transformation functions. */
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET) /*(*/
class gxTrafo : public gxTrafoHandler, public gxTrafoData {

#else

GX_CLASS gxTrafo : public gxTrafoHandler
#ifdef GX_DOTNET
, public System::IDisposable
#endif
{

#if !defined(GX_SWIGIF) /*(*/

#if !defined(GX_DOTNET) && !defined(GX_MANUAL)
public:
	gxTRAFO *_trafo;		/**< Pointer to the trafo structure. */
#endif

#if defined(GX_DOTNET)
#if !defined(GX_MANUAL)
private:
	GX_INDIRECTION_NOGC(gxTRAFO) _trafo;		/**< Pointer to the trafo structure. */
#endif

public:
	/** Returns the local trafo pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxOutPtr _get_trafo(void) GX_CONST {
		return GX_PUTPTR(_trafo);
	}
	/** Modifies the local trafo pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
	inline void _set_trafo(gxInPtr ptr) {
		_trafo = (GX_INDIRECTION_NOGC(gxTRAFO))GX_GETPTR(ptr);
	}
private:
	/** Modifies the local trafo pointer.
		 * @param ptr	New value. */
	inline void _set_trafo(GX_INDIRECTION_NOGC(gxTRAFO) ptr) {
		_trafo = ptr;
	}
public:
#endif
#endif /*)*/

public:
	/** It returns the reference counter.
	 *
	 * @see gxTRAFO gx_reftrafo() gx_unreftrafo()
	 *
	 * @return Reference counter of the gxTRAFO structure. */
	inline int ref(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->ref;
	}

	/** It returns the horizontal size of the transformation area.
	 *
	 * @return Horizontal size of the transformation area. */
	inline int xsize(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->xsize;
	}
	/** It returns the vertical size of the transformation area.
	 *
	 * @return Vertical size of the transformation area. */
	inline int ysize(void) GX_CONST gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo->ysize;
	}
#endif	/*)*/

public:
#if defined(GX_DOTNET) || defined(GX_SWIG)
	/** Class initialization with default properties. */
	inline gxTrafo() gxFuncThrowsError : gxTrafoHandler() {
#ifndef GX_DOTNET
		_trafo = 0;
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
#else
		_set_trafo(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETTRAFO(t);
			if(!gx_alloctrafo(h, &t)) gxthrow;
			_set_trafo(t);
		}
#endif
	}
#endif

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Class initialization with default properties. */
	inline gxTrafo() gxFuncThrowsError : gxTrafoHandler(), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}

	/** Class initialization with a source trafo handle.
	 *
	 * @param h Source trafo handle. The reference of this
	 *		trafo handle will be increased. */
	inline gxTrafo(const gxHANDLE GX_REF_STRUCT(h)) gxFuncThrowsError : gxTrafoHandler(h), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}
	/** Class initialization with a source trafo handle.
	 *
	 * @param h Source trafo handle. The reference of this
	 *		trafo handle will be increased. */
	inline gxTrafo(const gxHANDLE *h) gxFuncThrowsError : gxTrafoHandler(h), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}

	/** Class initialization with the place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}

	/** Class initialization with the place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of properties in property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}

	/** Class initialization with another trafo structure.
	 *
	 * @param src Source trafo. */
	inline gxTrafo(gxTRAFO GX_REF_STRUCT(src)) gxFuncThrowsError : gxTrafoHandler(), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another trafo structure, the place of the properties
	 * and name of the module (Unicode version).
	 *
	 * @param src Source trafo.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxTRAFO GX_REF_STRUCT(src), const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another trafo structure, the place of the properties
	 * and name of the module (ASCII version).
	 *
	 * @param src Source trafo.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxTRAFO GX_REF_STRUCT(src), const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another trafo class, the place of the properties
	 * and name of the module (Unicode version).
	 *
	 * @param src Source trafo.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxTrafo GX_REF_STRUCT(src), const wchar_t *propname, const wchar_t *modname = (const wchar_t *)0)
				gxFuncThrowsError : gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another trafo class, the place of the properties
	 * and name of the module (ASCII version).
	 *
	 * @param src Source trafo.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxTrafo GX_REF_STRUCT(src), const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#endif

#ifdef GX_UNICODE
#ifndef GX_DOTNET
	/** Class initialization with the place of the properties (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxTrafo(gxInStr propname) gxFuncThrowsError
				: gxTrafoHandler(propname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}

	/** Class initialization with another trafo class, the place of the properties
	 * and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxInStr propname, gxInStr modname) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}
#else
	/** Class initialization with the place of the properties (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxTrafo(gxInStr propname) gxFuncThrowsError
				: gxTrafoHandler(propname) {
		_set_trafo(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETTRAFO(t);
			if(!gx_alloctrafo(h, &t)) gxthrow;
			_set_trafo(t);
		}
	}

	/** Class initialization with another trafo class, the place of the properties
	 * and name of the module (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxInStr propname, gxInStr modname) gxFuncThrowsError
				: gxTrafoHandler(propname, modname) {
		_set_trafo(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETTRAFO(t);
			if(!gx_alloctrafo(h, &t)) gxthrow;
			_set_trafo(t);
		}
	}
#endif	// GX_DOTNET
#endif	// GX_UNICODE

#ifdef GX_ASCII
	/** Class initialization with the place of the properties (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxTrafo(gxInAStr propname) gxFuncThrowsError
				: gxTrafoHandler(propname), gxTrafoData() {

		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}
	/** Class initialization with another trafo class, the place of the properties
	 * and name of the module (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxTrafo(gxInAStr propname, gxInAStr modname) gxFuncThrowsError
				: gxTrafoHandler(propname, modname), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}
#endif

#ifndef GX_DOTNET
	/** Class initialization with another trafo handler.
	 *
	 * @param h The source handler. */
	inline gxTrafo(gxTrafoHandler GX_REF_CLASS(h)) gxFuncThrowsError : gxTrafoHandler(h), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(!gx_alloctrafo(*this, &_trafo)) gxthrow;
		}
	}
	/** Class initialization with another trafo.
	 *
	 * @param src The source trafo. */
	inline gxTrafo(gxTrafo GX_REF_CLASS(src)) gxFuncThrowsError : gxTrafoHandler((const gxHANDLE &)src), gxTrafoData() {
		if(gxHandle::IsValid()) {
			if(gx_alloctrafo(*this, &_trafo)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#else
	/** Class initialization with another trafo handler.
	 *
	 * @param h The source handler. */
	inline gxTrafo(gxTrafoHandler GX_REF_CLASS(h)) gxFuncThrowsError : gxTrafoHandler(h) {
		_set_trafo(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETTRAFO(t);
			if(!gx_alloctrafo(h, &t)) gxthrow;
			_set_trafo(t);
		}
	}
	/** Class initialization with another trafo.
	 *
	 * @param src The source trafo. */
	inline gxTrafo(gxTrafo GX_REF_CLASS(src)) gxFuncThrowsError : gxTrafoHandler(src) {
		_set_trafo(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETTRAFO(t);
			if(gx_alloctrafo(h, &t)) {
				_set_trafo(t);
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#endif

	/** Class termination. */
	inline ~gxTrafo() gxFuncThrowsError {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxTrafo() gxFuncThrowsError {
		_Dispose();
	}
#else
	/** It disposes the class. */
	inline void Dispose(void) gxFuncThrowsError {
	#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
	 /** call the base class */
	gxHandle::Dispose();
	}
#endif

private:

	inline void _Dispose(void) gxFuncThrowsError {
#ifndef GX_DOTNET
		if(_trafo) {
			if(!gx_unreftrafo(*this, _trafo)) gxthrow;
		}
#else		
		GX_GETHANDLE(h);
		GX_GETTRAFO(t);
		if(t) {
			if(!gx_unreftrafo(h, t)) gxthrow;
		}
#endif
		_trafo=0;		
	}

public:

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Copies a trafo to the class.
	 *
	 * @param src	Source transformation structure. */
	inline gxTrafo &operator = (gxTRAFO GX_REF_STRUCT(src)) gxFuncThrowsError {
		Copy(src);
		return *this;
	}

	/** Copies a trafo to the class.
	 *
	 * @param src	Source transformation class. */
	inline gxTrafo &operator = (gxTrafo GX_REF_CLASS(src)) gxFuncThrowsError {
		Copy(src);
		return *this;
	}

	/** Returns a reference to the gxTRAFO structure.
	 *
     * @return Reference to the gxTRAFO structure. */
	inline operator gxTRAFO & () gxFuncThrowsError {
		gxassert(_trafo);
		return *_trafo;
	}
	/** Returns a pointer to the gxTRAFO structure.
	 *
     * @return Pointer to the gxTRAFO structure. */
	inline operator gxTRAFO * () gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo;
	}
	/** Returns a pointer to the gxTRAFO structure.
	 *
     * @return Pointer to the gxTRAFO structure. */
	inline operator const gxTRAFO * () const gxFuncThrowsError {
		gxassert(_trafo);
		return _trafo;
	}

	/** Attaches to an allocated trafo.
	 *
	 * @param src An allocated gxTRAFO structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Attach(gxTRAFO *src) gxFuncThrowsError {
		gxassert(_trafo && src);
		if(src->ref >= 0) {
			gx_seterror(GX_EINVAL, L"(src->ref < 0)");
			gxthrow;
			return false;
		}
		if(!gx_reftrafo(*this, src)) {
			gxthrow;
			return false;
		}
		if(!gx_unreftrafo(*this, _trafo)) {
			gx_unreftrafo(*this, src);
			gxthrow;
			return false;
		}
		_trafo = src;
		return true;
	}

	/** Detaches the trafo.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Detach(void) gxFuncThrowsError {
		if(!gx_unreftrafo(*this, _trafo)) {
			gxthrow;
			return false;
		}
		if(!gx_alloctrafo(*this, &_trafo)) {
			gxthrow;
			return false;
		}
		return true;
	}

	/** Creates a transformation structure based on the specified parameters.
	 *
	 * @param pairs Pointer to the list point pairs.
	 * @param npair Number of points in the list of point pairs.
	 * @param frame The transformation works with in this frame.  The coordinates are defined on the source coordinate system.
	 * @param resolution Distances between two transformation elements.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(const gxPG2 *pairs, int npair,
					const gxRCT GX_REF_STRUCT(frame), int resolution) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_createtrafo(*this, _trafo, pairs, npair, frame, resolution) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads data from the specified transformation file to an initialized structure (Unicode version).
	 *
	 * @param filename Name of the file containing the data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(const wchar_t *filename) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_loadtrafo(*this, _trafo, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Loads data from the specified transformation file to an initialized structure (ASCII version).
	 *
	 * @param filename Name of the file containing the data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(const char *filename) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_loadtrafoa(*this, _trafo, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves the specified transformation structure to a file (Unicode version).
	 *
	 * @param filename Name of the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const wchar_t *filename) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_savetrafo(*this, _trafo, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Saves the specified transformation structure to a file (ASCII version).
	 *
	 * @param filename Name of the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const char *filename) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_savetrafoa(*this, _trafo, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	// !GX_SWIGIF && !GX_DOTNET

#ifdef GX_UNICODE
	/** Loads data from the specified transformation file to an initialized structure (Unicode version).
	 *
	 * @param filename Name of the file containing the data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInStr filename) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		gxassert(_trafo);
		GX_GETHANDLE(h);
		GX_GETTRAFO(t);
		bool st = gx_loadtrafo(h, t, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Saves the specified transformation structure to a file (Unicode version).
	 *
	 * @param filename Name of the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInStr filename) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		gxassert(_trafo);
		GX_GETHANDLE(h);
		GX_GETTRAFO(t);
		bool st = gx_savetrafo(h, t, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Loads data from the specified transformation file to an initialized structure (ASCII version).
	 *
	 * @param filename Name of the file containing the data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInAStr filename) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		gxassert(_trafo);
		bool st = gx_loadtrafo(*this, _trafo, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
	/** Saves the specified transformation structure to a file (ASCII version).
	 *
	 * @param filename Name of the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInAStr filename) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		gxassert(_trafo);
		bool st = gx_savetrafo(*this, _trafo, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Copies one transformation structure to another.
	 *
	 * The destination structure must be initialized. Its data will be overwritten.
	 * The source structure remains unchanged.
	 *
	 * @param source Pointer to the source.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(const gxTRAFO *source) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_copytrafo(*this, _trafo, source) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Copies one transformation structure to another.
	 *
	 * The destination structure must be initialized. Its data will be overwritten.
	 * The source structure remains unchanged.
	 *
	 * @param source Pointer to the source.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(const gxTrafo *source) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_copytrafo(*this, _trafo, (const gxTRAFO *)*source) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Copies one transformation structure to another.
	 *
	 * The destination structure must be initialized. Its data will be overwritten.
	 * The source structure remains unchanged.
	 *
	 * @param source Source transformation structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(const gxTRAFO GX_REF_STRUCT(source)) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_copytrafo(*this, _trafo, &source) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Copies one transformation structure to another.
	 *
	 * The destination structure must be initialized. Its data will be overwritten.
	 * The source structure remains unchanged.
	 *
	 * @param source Source transformation structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(GX_CONST gxTrafo GX_REF_CLASS(source)) gxFuncThrowsError {
		gxassert(_trafo);
#ifndef GX_DOTNET
		bool st = gx_copytrafo(*this, _trafo, (const gxTRAFO *)source) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETTRAFO(t);
		bool st = gx_copytrafo(h, t, (gxTRAFO *)source GX_M _get_trafo().ToPointer()) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

#ifdef GX_DOTNET
	/** Transforms points from the source sequence with the help of the specified
	 * structure then writes the result to the destination sequence list.
	 *
	 * @param source List of source points.
	 * @param target Place of transformed points.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Trafo(gxPNT_ARRAY source, gxPNT_ARRAY target) gxFuncThrowsError {
		gxassert(_trafo);
		GX_GETHANDLE(h);
		GX_PIN_PTR(gxPNT, _source) = &source[0];
		GX_PIN_PTR(gxPNT, _target) = &target[0];
		const _gxPNT* ps = (const _gxPNT*)_source;
		_gxPNT* pt = (_gxPNT*)_target;
		bool st = gx_trafo(h, _trafo, ps, pt, source->Length) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#elif !defined(GX_SWIGIF)
	/** Transforms points from the source sequence with the help of the specified
	 * structure then writes the result to the destination sequence list.
	 *
	 * @param source List of source points.
	 * @param target Place of transformed points.
	 * @param npoints Number of points in the list.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Trafo(const gxPNT *source, gxPNT *target, int npoints GX_DEFARG(1)) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_trafo(*this, _trafo, source, target, npoints) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Transforms two points from the source with the help of the specified
	 * structure then writes the result to the destination area.
	 *
	 * @param source Pointer to the source.
	 * @param target Place of transformed area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Trafo(const gxPG2 *source, gxPNT *target) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_trafo(*this, _trafo, (const gxPNT *)source, target, 2) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Transforms four points from the source with the help of the specified
	 * structure then writes the result to the destination area.
	 *
	 * @param source Pointer to the source.
	 * @param target Place of transformed area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Trafo(const gxPG4 *source, gxPNT *target) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_trafo(*this, _trafo, (const gxPNT *)source, target, 4) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inverse transformation.
	 *
	 * @param source List of source points.
	 * @param target Place of the transformed points.
	 * @param npoints Number of points in the list.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool ITrafo(const gxPNT *source, gxPNT *target, int npoints = 1) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_itrafo(*this, _trafo, source, target, npoints) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inverse transformation.
	 *
	 * @param source Pointer to the source.
	 * @param target Place of the transformed area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool ITrafo(const gxPG2 *source, gxPNT *target) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_itrafo(*this, _trafo, (const gxPNT *)source, target, 2) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inverse transformation.
	 *
	 * @param source Pointer to the source.
	 * @param target Place of the transformed area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool ITrafo(const gxPG4 *source, gxPNT *target) gxFuncThrowsError {
		gxassert(_trafo);
		bool st = gx_itrafo(*this, _trafo, (const gxPNT *)source, target, 4) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Checks the specified transformation structure.
	 *
	 * @return In case of existing structure the return value is non-zero. */
	inline bool IsValid(void) GX_CONST {
		if(!gxHandle::IsValid()) return false;
		GX_GETHANDLE(h);
		GX_GETTRAFO(t);
		return gx_isvalidtrafo(h, t) ? true : false;
	}

	/** Loads an embedded transformation structure from a variant.
	 *
	 * @param variant	Variant with an embedded transformation structure.
	 * @return On error false is returned or an exception is thrown. */
	inline bool FromVariant(
		gxVariant GX_REF_CLASS(variant)
		) gxFuncThrowsError {

		GX_GETTRAFO(t);
#ifndef GX_DOTNET
		bool st = gx_trafofromvariant(&t, variant._variant) ? true : false;
		if(st) {
			gx_unreftrafo(_trafo);
			_trafo=t;
		}
#else
		bool st = gx_trafofromvariant(&t,
			variant ? variant->_variant : 0 ) ? true : false;
		if(st) {
			gx_unreftrafo(_trafo);
			_set_trafo(t);
		}
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Embedds the transformation structure into a variant.
	 *
	 * @param varid		The id for the created variant.
	 * @return The variant class. On error false is returned and an exception is thrown. */
	inline GX_INDIRECTION1(gxVariant) ToVariant(int varid) gxFuncThrowsError {

		GX_GETTRAFO(t);
		gxVARIANT vari;
		bool st = gx_trafotovariant(t, varid, &vari) != 0;
		gxcondthrow(!st);
		if(!st) return GX_NULLPTR;
		GX_INDIRECTION(gxVariant,vr) = gxnew gxVariant(vari);
		gx_unrefvariant(vari);
		if(!vr){gxSystem::SetError((int)GX_ENUM_PATH(GX_ERROR_CODES) GX_ENOMEM);gxthrow;}
		return vr;
	}
};
/******************************************************************************/
#endif	// GX_EXT_MODULE
/******************************************************************************/
#endif//NO_GX_CLASSES
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
/******************************************************************************/
#endif//GX_TRAFO_INCL
/******************************************************************************/
