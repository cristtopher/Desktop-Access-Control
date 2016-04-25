/*******************************************************************************
 * GX MOTDET header file - v7.2.10
 *
 * 2002-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Motion Detection interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the motion detection module.
 */
/******************************************************************************/
#ifndef MOTDET_INCL
#define MOTDET_INCL
/******************************************************************************/
#include "gxsd.h"
#include "gximage.h"
#include <assert.h>
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/******************************************************************************/
/** Call codes for MOTDET operations. */
enum MOTDET_CALL_CODE {
	GX_CALL_MOTDETITERATION			= GX_CALL_GROUP_GX_MOTDET	/**< One iteration step. */
};
/******************************************************************************/
/** Parameter structure for the gx_setupmotdet() function. */
struct GX_PARM_MOTDETITERATION {
	gxIMAGE	*image;			/**< Source image (it must be GX_GRAY). It contains a still of the stream. */
	int min_difference;		/**< The minimum of the blocks' pixel difference inside of the area. */
	int max_difference;		/**< The maximum of the blocks' pixel difference inside of the area. */
	int found_x1;			/**< The left upper horizontal coordinate of the founded area. */
	int found_y1;			/**< The left upper vertical coordinate of the founded area. */
	int found_x2;			/**< The right lower horizontal coordinate of the founded area. */
	int found_y2;			/**< The right lower vertical coordinate of the founded area. */
};
#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_motdet
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Adding a new image to the stream.
 *
 * \warning
 *		The size of the image must be the same as given by the properties.
 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
 *		pixel formats are allowed! In case of half frames
 *		use only the same field in one stream. For detecting motion on both
 *		odd and even fields, the using of two separated streams (opening twice the module)
 *		is recomended.
 *
 * @param handle	Handle of the module.
 * @param parm		Pointer to a data exchange structure.
 * @return	On error false is returned and the error code/string in the GX system
 *			is set appropriately ( see gx_geterror() ). */
inline int gx_motdetiteration(gxHANDLE handle, struct GX_PARM_MOTDETITERATION *parm) {
	assert(parm);
	return gx_call(handle, GX_CALL_MOTDETITERATION, parm);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

#endif

/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/

/******************************************************************************/
#ifndef NO_GX_CLASSES

/******************************************************************************/
/** Class for the motion detection functions. */
GX_CLASS gxMotionDetectorResult {
public:
	int min_difference;		/**< The minimum of the blocks' pixel difference inside of the area. */
	int max_difference;		/**< The maximum of the blocks' pixel difference inside of the area. */
	int found_x1;			/**< The left upper horizontal coordinate of the founded area. */
	int found_y1;			/**< The left upper vertical coordinate of the founded area. */
	int found_x2;			/**< The right lower horizontal coordinate of the founded area. */
	int found_y2;			/**< The right lower vertical coordinate of the founded area. */

	/** Constructor. */
	inline gxMotionDetectorResult() {
		min_difference = max_difference = 0;
		found_x1 = found_y1 = found_x2 = found_y2 = 0;
	}
	
	/** Returns the value of the \a min_difference variable. */
	inline int GetMinDifference(void) GX_CONST {
		return min_difference;
	}
	/** Returns the value of the \a max_difference variable. */
	inline int GetMaxDifference(void) GX_CONST {
		return max_difference;
	}
	/** Returns the value of the \a found_x1 variable. */
	inline int GetFoundX1(void) GX_CONST {
		return found_x1;
	}
	/** Returns the value of the \a found_y1 variable. */
	inline int GetFoundY1(void) GX_CONST {
		return found_y1;
	}
	/** Returns the value of the \a found_x2 variable. */
	inline int GetFoundX2(void) GX_CONST {
		return found_x2;
	}
	/** Returns the value of the \a found_y2 variable. */
	inline int GetFoundY2(void) GX_CONST {
		return found_y2;
	}
};
/******************************************************************************/
/** Class implementation of the motion detection module functions. */
GX_CLASS gxMotionDetector : public gxHandle {
public:
	/** Class initialization. */
	inline gxMotionDetector() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxmotdet", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxmotdet", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)

	/** Class initialization with place of properties and name of the module (Unicode version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 * @param modname	Name of the module.
	 */
	inline gxMotionDetector(const wchar_t *propname, const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError {
		if(!gx_openmodule(this, modname ? modname : L"gxmotdet", propname)) gxthrow;
	}

	/** Class initialization with place of properties and name of the module (ASCII version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 * @param modname	Name of the module.
	 */
	inline gxMotionDetector(const char *propname, const char *modname = (const char *)0) gxFuncThrowsError {
		if(!gx_openmodule(this, modname ? modname : "gxmotdet", propname)) gxthrow;
	}
#endif

#ifdef GX_UNICODE
	/** Class initialization with place of properties and name of the module (Unicode version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 * @param modname	Name of the module.
	 */
	inline gxMotionDetector(gxInStr propname, gxInStr modname) gxFuncThrowsError {
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

	/** Class initialization with place of properties (Unicode version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 */
	inline gxMotionDetector(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxmotdet", _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxmotdet", _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif

#ifdef GX_ASCII
	/** Class initialization with place of properties and name of the module (ASCII version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 * @param modname	Name of the module.
	 */
	inline gxMotionDetector(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodule(this, _modname, _propname)) gxthrow;
	}

	/** Class initialization with place of properties (ASCII version).
	 *
	 * @param propname	Place of properties in the property tree (name of the property group).
	 */
	inline gxMotionDetector(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		if(!gx_openmodule(this, "gxmotdet", _propname)) gxthrow;
	}
#endif
	
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image				Pointer to an image which represents the next still of the stream.
	 * @param max_difference	Pointer to an integer. The function updates it to
	 *							the maximum of the blocks' pixel difference. If the image is the
	 *							first still in the stream, -1 is returned.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Iteration(gxIMAGE *image, int *max_difference) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		parm.image = image;
		bool st = gx_motdetiteration(*this, &parm) ? true : false;
		if(st) {
			if(max_difference) *max_difference = parm.max_difference;
		} else {
			gxthrow;
		}
		return st;
	}

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image	Pointer to an image which represents the next still of the stream.
	 * @return	The function returns the maximum of the blocks' pixel difference. If the
	 *			image is the first still in the stream, -1 is returned. */
	inline int Iteration(gxIMAGE *image) gxFuncThrowsError {
		int ret = -1;
		Iteration(image, &ret);
		return ret;
	}
#endif

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image	Pointer to an image which represents the next still of the stream.
	 * @return	The function returns the maximum of the blocks' pixel difference. If the
	 *			image is the first still in the stream, -1 is returned. */
	inline int Iteration(gxImageData GX_REF_CLASS(image)) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		GX_GETHANDLE(h);
#ifndef GX_DOTNET
		parm.image = image;
#else
		parm.image = (gxIMAGE *)image GX_M _get_image().ToPointer();
#endif
		if(gx_motdetiteration(h, &parm)) return parm.max_difference;
		gxthrow;
		return -1;
	}

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image	Pointer to an image which represents the next still of the stream.
	 * @return	The function returns the maximum of the blocks' pixel difference. If the
	 *			image is the first still in the stream, -1 is returned. */
	inline int Iteration(gxImage GX_REF_CLASS(image)) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		GX_GETHANDLE(h);
#ifndef GX_DOTNET
		parm.image = image;
#else
		parm.image = (gxIMAGE *)image GX_M _get_image().ToPointer();
#endif
		if(gx_motdetiteration(h, &parm)) return parm.max_difference;
		gxthrow;
		return -1;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image				Pointer to an image which represents the next still of the stream.
	 * @param min_difference	Pointer to an integer.
	 *								The function updates it to the minimum of the blocks' pixel difference.
	 *								If the image is the first still in the stream, -1 is returned.
	 *								This pointer can be NULL.
	 * @param max_difference	Pointer to an integer.
	 *								The function updates it to the maximum of the blocks' pixel difference.
	 *								If the image is the first still in the stream, -1 is returned.
	 *								This pointer can be NULL.
	 * @param found_x1			Pointer to an integer.
	 *								The function updates it to the left upper horizontal coordinate of the founded area.
	 *								If the image is the first still in the stream, it will be undefined.
	 *								This pointer can be NULL.
	 * @param found_y1			Pointer to an integer.
	 *								The function updates it to the left upper vertical coordinate of the founded area.
	 *								If the image is the first still in the stream, it will be undefined.
	 *								This pointer can be NULL.
	 * @param found_x2			Pointer to an integer.
	 *								The function updates to the right lower horizontal coordinate of the founded area.
	 *								If the image is the first still in the stream, it will be undefined.
	 *								This pointer can be NULL.
	 * @param found_y2			Pointer to an integer.
	 *								The function updates it to the right lower vertical coordinate of the founded area.
	 *								If the image is the first still in the stream, it will be undefined.
	 *								This pointer can be NULL.
	 * @return	An exception is thrown or false is returned in case of error. */
	inline bool Iteration(gxIMAGE *image, int *max_difference, int *min_difference,
				int *found_x1, int *found_y1, int *found_x2, int *found_y2) gxFuncThrowsError {

		GX_PARM_MOTDETITERATION parm;
		parm.image = image;
		int st = gx_motdetiteration(*this, &parm);
		if(!st) {
			gxthrow;
			return false;
		}
		if(max_difference) *max_difference = parm.max_difference;
		if(min_difference) *min_difference = parm.min_difference;
		if(found_x1) *found_x1 = parm.found_x1;
		if(found_y1) *found_y1 = parm.found_y1;
		if(found_x2) *found_x2 = parm.found_x2;
		if(found_y2) *found_y2 = parm.found_y2;
		return true;
	}

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image		Pointer to an image which represents the next still of the stream.
	 * @param result	The result structure which the function will updates it.
	 * @return	An exception is thrown or false is returned in case of error. */
	inline bool Iteration(gxIMAGE *image, gxMotionDetectorResult &result) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		parm.image = image;
		int st = gx_motdetiteration(*this, &parm);
		if(!st) {
			gxthrow;
			return false;
		}
		result.max_difference = parm.max_difference;
		result.min_difference = parm.min_difference;
		result.found_x1 = parm.found_x1;
		result.found_y1 = parm.found_y1;
		result.found_x2 = parm.found_x2;
		result.found_y2 = parm.found_y2;
		return true;
	}
#endif

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image		Pointer to an image which represents the next still of the stream.
	 * @param result	The result structure which the function will updates it.
	 * @return	An exception is thrown or false is returned in case of error. */
	inline bool Iteration(gxImageData GX_REF_CLASS(image), gxMotionDetectorResult GX_REF_CLASS(result)) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		GX_GETHANDLE(h);
#ifndef GX_DOTNET
		parm.image = image;
#else
		parm.image = (gxIMAGE *)image GX_M _get_image().ToPointer();
#endif
		int st = gx_motdetiteration(h, &parm);
		if(!st) {
			gxthrow;
			return false;
		}
		result GX_M max_difference = parm.max_difference;
		result GX_M min_difference = parm.min_difference;
		result GX_M found_x1 = parm.found_x1;
		result GX_M found_y1 = parm.found_y1;
		result GX_M found_x2 = parm.found_x2;
		result GX_M found_y2 = parm.found_y2;
		return true;
	}

	/** Adding a new image to the stream.
	 *
	 * \warning
	 *		The size of the image must be the same as given by the properties.
	 *		GX_GRAY (8 bit grayscale), GX_RGB (24 bit RGB) and GX_BGR (24 bit BGR)
	 *		pixel formats are allowed! In case of half frames
	 *		use only the same field in one stream. For detecting motion on both
	 *		odd and even fields, the using of two separated streams (opening twice the module)
	 *		is recomended.
	 *
	 * @param image		Pointer to an image which represents the next still of the stream.
	 * @param result	The result structure which the function will updates it.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Iteration(gxImage GX_REF_CLASS(image), gxMotionDetectorResult GX_REF_CLASS(result)) gxFuncThrowsError {
		GX_PARM_MOTDETITERATION parm;
		GX_GETHANDLE(h);
#ifndef GX_DOTNET
		parm.image = image;
#else
		parm.image = (gxIMAGE *)image GX_M _get_image().ToPointer();
#endif
		int st = gx_motdetiteration(h, &parm);
		if(!st) {
			gxthrow;
			return false;
		}
		result GX_M max_difference = parm.max_difference;
		result GX_M min_difference = parm.min_difference;
		result GX_M found_x1 = parm.found_x1;
		result GX_M found_y1 = parm.found_y1;
		result GX_M found_x2 = parm.found_x2;
		result GX_M found_y2 = parm.found_y2;
		return true;
	}
};
/******************************************************************************/
#endif	// NO_GX_CLASSES
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif	// MOTDET_INCL
/******************************************************************************/
