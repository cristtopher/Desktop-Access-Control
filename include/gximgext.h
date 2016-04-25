/*******************************************************************************
 * GX IMAGE EXTENSION header file - V7.2.10
 *
 * 2006-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Extended image handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the image handling module
 * with extended image manipulating functions that are not used in the normal image operations.
 */
/******************************************************************************/
#ifndef GX_IMGEXT_INCL
#define GX_IMGEXT_INCL
/******************************************************************************/
#include "gxsd.h"
#include "gximage.h"
#include "gxtrafo.h"
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/
/** Flags for color adjust functions. */
GX_ENUM GX_COLORADJUST_FLAGS {
	GX_COLORADJUST_BRIGHTNESS_BASIC		= 1,	/**< Basic brightness manipulating method */
	GX_COLORADJUST_BRIGHTNESS_ADVANCED	= 2,	/**< Advanced brightness manipulating method */
	GX_COLORADJUST_CONTRAST_BASIC		= 4,	/**< Basic contrast manipulating method */
	GX_COLORADJUST_CONTRAST_ADVANCED	= 8,	/**< Advanced contrast manipulating method */
};

/** Flags for image compose functions. */
GX_ENUM GX_COMPOSE_FLAGS {
	GX_COMPOSE_DONT_ENLARGE_IMAGE	= 0x01,		/**< Do not enlarge image if the upper image is larger the the other. */
	GX_COMPOSE_ENLARGE_IMAGE		= 0x02,		/**< Enlarge image if the upper image is larger the the other. */
	GX_COMPOSE_ALPHA				= 0x04,		/**< Basic composing when one image is over the other one, and alpha chanel is defined. */
	GX_COMPOSE_WEIGHTING			= 0x08,		/**< Weighting of two images. */
};

/** Flags for text draw functions. */
GX_ENUM GX_TEXT_FLAGS {
	GX_TEXT_ITALIC		= 0x01,					/**< The characters of the text are italic. */
	GX_TEXT_STRAIGHT	= 0x02,					/**< The characters of the text are straight. */
	GX_TEXT_BOLD		= 0x10,					/**< The characters of the text are bold. */
	GX_TEXT_NORMAL		= 0x20,					/**< The characters of the text are normal. */
	GX_TEXT_THIN		= 0x30,					/**< The characters of the text are thin. */
};

/******************************************************************************/
#if defined(GX_DOTNET) && !defined(GX_MANUAL)
	#pragma unmanaged
	#define gxPNT _gxPNT
	#define gxPG4 _gxPG4
#endif
/******************************************************************************/

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/

enum {
	GX_CALL_COLORADJUST			= GX_CALL_GROUP_GX_IMGEXT,		/* Call code of the gx_coloradjust() function. */
	GX_CALL_COLORMIXER			= GX_CALL_GROUP_GX_IMGEXT+1,	/* Call code of the gx_colormixer() function. */
	GX_CALL_IMAGEDIFFERENCE		= GX_CALL_GROUP_GX_IMGEXT+2,	/* Call code of the gx_imagedifference() function. */
	GX_CALL_IMAGETRANSFORM		= GX_CALL_GROUP_GX_IMGEXT+3,	/* Call code of the gx_imagetransform() function. */
	GX_CALL_IMAGEFTRANSFORM		= GX_CALL_GROUP_GX_IMGEXT+4,	/* Call code of the gx_imageftransform() function. */
	GX_CALL_IMAGECOMPOSE		= GX_CALL_GROUP_GX_IMGEXT+5,	/* Call code of the gx_imagecompose() function. */
	GX_CALL_DRAWTEXT			= GX_CALL_GROUP_GX_IMGEXT+6,	/* Call code of the gx_drawtext() function. */
};

/******************************************************************************/
/**	Parameter structure for the gx_coloradjust() function. */
struct GX_PARM_COLORADJUST {
	gxIMAGE	*image;		/* Image to adjust. */
	float	contrast;	/* Contrast adjust level. */
	float	brightness;	/* Brightness adjust level. */
	float	saturation;	/* Saturation adjust level. */
	float	gamma;		/* Gamma correction level. */
	int		flags;		/* Color adjusting flags, see \ref GX_COLORADJUST_FLAGS. */
};

/**	Parameter structure for the gx_colormixer() function. */
struct GX_PARM_COLORMIXER {
	gxIMAGE	*target;	/* Preallocated image to return the result. */
	gxIMAGE	*source;	/* Image to process. */
	int		r1;			/* Adaptable weight. */
	int		g1;			/* Adaptable weight. */
	int		b1;			/* Adaptable weight. */
	int		r2;			/* Adaptable weight. */
	int		g2;			/* Adaptable weight. */
	int		b2;			/* Adaptable weight. */
	int		r3;			/* Adaptable weight. */
	int		g3;			/* Adaptable weight. */
	int		b3;			/* Adaptable weight. */
};

/**	Parameter structure for the gx_imagedifference() function. */
struct GX_PARM_IMAGEDIFFERENCE {
	gxIMAGE	*target;	/* Preallocated image to return the result. */
	gxIMAGE	*source1;	/* First image. */
	gxIMAGE	*source2;	/* Second image. */
};

/** Parameter structure for the gx_imagetransform() function. */
struct GX_PARM_IMAGETRANSFORM {
	gxIMAGE	*target;	/* Preallocated image to return the result. */
	gxIMAGE	*source;	/* Image to process. */
	gxPG4	area;		/* Area defined on the source image to transform in the target image. */
	void	*bgcolor;	/* Background color for filling parts that are not defined by the source image. */
};

/**	Parameter structure for the gx_imageftransform() function. */
struct GX_PARM_IMAGEFTRANSFORM {
	gxIMAGE	*target;	/* Preallocated image to return the result. */
	gxIMAGE	*source;	/* Image to process. */
	gxTRAFO	*trafo;		/* Transformation descriptor. */
	void	*bgcolor;	/* Background color for filling parts that are not defined by the source image. */
};

/**	Parameter structure for the gx_imagecompose() function. */
struct GX_PARM_IMAGECOMPOSE {
	gxIMAGE *target;	/* Preallocated image to return the result. */
	gxIMAGE *upper;		/* Upper image. */
	gxIMAGE *lower;		/* Lower image. */
	gxPNT	position;	/* Position of the upper image on the lower image. */
	float	alpha_u;	/* Alpha channel for the upper image. */
	float	alpha_l;	/* Alpha channel for the lower image. */
	int		flags;		/* Image composing flags, see \ref GX_COMPOSE_FLAGS. */
	void	*bgcolor;	/* Background color for filling parts that are not defined by the source images. */
};

/**	Parameter structure for the gx_drawtext() function. */

struct GX_PARM_DRAWTEXT {
	gxIMAGE		*image;			/* Image to return the result. */
	const char	*text;			/* Text to draw */
	gxPNT		position;		/* Position of the text on image */
	const char	*fonttype;		/* Name of the fontface (WIN32) or path of the font file (LINUX) */
	int			fontheight;		/* Character height of the text in logical units */
	int			fontwidth;		/* Average character width in logical units */
	void		*txtcolor;		/* Text color */
	int			flags;			/* Image composing flags, see \ref GX_COMPOSE_FLAGS. */
};

#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)	/*(*/
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Makes contrast, brightness, saturation and gamma correction on the image.
 *
 * The usual values for the adjusting values are between [-1, 1], the level change
 * calculation can be expressed by the \verbatim new_level = (1+f)*old_level \endverbatim
 * abstraction.
 *
 * The value of -1 discards all the partial information, a value of 0 does not
 * modify the image setting.
 *
 * For the gamma correction other rules are applied. The value of 1 leaves the
 * image unchanged.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param image			Image to process.
 * @param contrast		Contrast adjust level.
 * @param brightness	Brightness adjust level.
 * @param saturation	Saturation adjust level.
 * @param gamma			Gamma correction level.
 * @param flags			Color adjusting flags, see \ref GX_COLORADJUST_FLAGS.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_coloradjust(gxHANDLE imgexthandle, gxIMAGE *image,
			float contrast GX_DEFARG(0), float brightness GX_DEFARG(0), float saturation GX_DEFARG(0),
			float gamma GX_DEFARG(1), int flags GX_DEFARG(0))
{
	struct GX_PARM_COLORADJUST col;
	assert(image);
	col.image = image;
	col.contrast = contrast;
	col.brightness = brightness;
	col.saturation = saturation;
	col.gamma = gamma;
	col.flags = flags;
	return gx_call(imgexthandle, GX_CALL_COLORADJUST, &col);
}

/******************************************************************************/
/** Changes the colors of the source image based on the weight parameters.
 *
 * This function is an advanced image manipulating function that can be used in
 * adaptive processes by setting the weights.
 *
 * \note If only the first three weights are defined the resulted image will be
 * a grayscale image.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param target		Preallocated image to return the result.
 * @param source		Image to process.
 * @param r1			Adaptable weight.
 * @param g1			Adaptable weight.
 * @param b1			Adaptable weight.
 * @param r2			Adaptable weight.
 * @param g2			Adaptable weight.
 * @param b2			Adaptable weight.
 * @param r3			Adaptable weight.
 * @param g3			Adaptable weight.
 * @param b3			Adaptable weight.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_colormixer(gxHANDLE imgexthandle, gxIMAGE *target,
			gxIMAGE *source, int r1, int g1, int b1,
			int r2 GX_DEFARG(0), int g2 GX_DEFARG(0), int b2 GX_DEFARG(0),
			int r3 GX_DEFARG(0), int g3 GX_DEFARG(0), int b3 GX_DEFARG(0))
{
	struct GX_PARM_COLORMIXER col;
	assert(target);
	assert(source);
	col.target = target;
	col.source = source;
	col.r1 = r1;
	col.g1 = g1;
	col.b1 = b1;
	col.r2 = r2;
	col.g2 = g2;
	col.b2 = b2;
	col.r3 = r3;
	col.g3 = g3;
	col.b3 = b3;
	return gx_call(imgexthandle, GX_CALL_COLORMIXER, &col);
}

/******************************************************************************/
/** Generates a differential image from two images.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param target		Preallocated image to return the result.
 * @param source1		First image.
 * @param source2		Second image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_imagedifference(gxHANDLE imgexthandle, gxIMAGE *target,
			gxIMAGE *source1, gxIMAGE *source2)
{
	struct GX_PARM_IMAGEDIFFERENCE idf;
	assert(target);
	assert(source1);
	assert(source2);
	idf.target = target;
	idf.source1 = source1;
	idf.source2 = source2;
	return gx_call(imgexthandle, GX_CALL_IMAGEDIFFERENCE, &idf);
}

/******************************************************************************/
/** Transforms a general area from the source image in the target image.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param target		Preallocated image to return the result.
 * @param source		Image to process.
 * @param area			General area defined on the source image.
 * @param bgcolor		Background color for filling parts that are not defined by the source image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_imagetransform(gxHANDLE imgexthandle, gxIMAGE *target,
			gxIMAGE *source, gxPG4 area, void *bgcolor GX_DEFARG(0))
{
	struct GX_PARM_IMAGETRANSFORM itr;
	assert(target);
	assert(source);
	itr.target = target;
	itr.source = source;
	itr.area = area;
	itr.bgcolor = bgcolor;
	return gx_call(imgexthandle, GX_CALL_IMAGETRANSFORM, &itr);
}

/******************************************************************************/
/** Fine transforms an image with the transformation described by the trafo.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param target		Preallocated image to return the result.
 * @param source		Image to process.
 * @param trafo			Transformation descriptor.
 * @param bgcolor		Background color for filling parts that are not defined by the source image.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_imageftransform(gxHANDLE imgexthandle, gxIMAGE *target,
			gxIMAGE *source, gxTRAFO *trafo, void *bgcolor GX_DEFARG(0))
{
	struct GX_PARM_IMAGEFTRANSFORM ftr;
	assert(target);
	assert(source);
	assert(trafo);
	ftr.target = target;
	ftr.source = source;
	ftr.trafo = trafo;
	ftr.bgcolor = bgcolor;
	return gx_call(imgexthandle, GX_CALL_IMAGEFTRANSFORM, &ftr);
}

/******************************************************************************/
/** Composes two images.
 *
 * @param imgexthandle	Handle to the imgext module.
 * @param target		Preallocated image to return the result.
 * @param upper			Upper image.
 * @param lower			Lower image.
 * @param position		Position of the upper image defined on the lower image.
 * @param alpha_u		Alpha channel of the upper image.
 * @param alpha_l		Alpha channel of the lower image.
 * @param flags			Image composing flags, see \ref GX_COMPOSE_FLAGS.
 * @param bgcolor		Background color for filling parts that are not defined by the source images.
 * @return		On error false is returned and the error code/string in the GX system
 *				is set appropriately ( see gx_geterror() ). */
inline int gx_imagecompose(gxHANDLE imgexthandle, gxIMAGE *target,
			gxIMAGE *upper, gxIMAGE *lower, gxPNT position,
			float alpha_u GX_DEFARG(1),	float alpha_l GX_DEFARG(1),
			int flags GX_DEFARG(0), void *bgcolor GX_DEFARG(0))
{
	struct GX_PARM_IMAGECOMPOSE ic;
	assert(target);
	assert(upper);
	assert(lower);
	ic.target = target;
	ic.upper = upper;
	ic.lower = lower;
	ic.position = position;
	ic.alpha_u = alpha_u;
	ic.alpha_l = alpha_l;
	ic.flags = flags;
	ic.bgcolor = bgcolor;
	return gx_call(imgexthandle, GX_CALL_IMAGECOMPOSE, &ic);
}

/******************************************************************************/
/** Draw text on an image. If no image given, create a grayscale image.
	 *
	 * @param imgexthandle	Handle to the imgext module.
	 * @param image			Preallocated image to return the result.
	 * @param text			Text to draw.
	 * @param position		Position of the text on image.
	 * @param fonttype		Name of the fontface (WIN32) or path of the font file (LINUX).
	 * @param fontheight	Character height of the text in logical units.
	 * @param fontwidth		Average character width in logical units.
	 * @param txtcolor		Text color.
	 * @param flags			WIN32: see \ref GX_TEXT_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */

inline int gx_drawtext(gxHANDLE imgexthandle, gxIMAGE *image, const char *text,
			gxPNT position, const char *fonttype, int fontheight, int fontwidth,
			void *txtcolor, unsigned int flags)
{
	struct GX_PARM_DRAWTEXT dt;
	assert(text);
	assert(txtcolor);
	dt.image = image;
	dt.text = text;
	dt.position = position;
	dt.fonttype = fonttype;
	dt.fontheight = fontheight;
	dt.fontwidth = fontwidth;
	dt.txtcolor = txtcolor;
	dt.flags = flags;
	return gx_call(imgexthandle, GX_CALL_DRAWTEXT, &dt);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
#endif	/*)*/
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
	#undef gxPNT
	#undef gxPG4
#endif
/******************************************************************************/

/******************************************************************************/
#if !defined(NO_GX_CLASSES)	/*(*/
/******************************************************************************/
/** Class for the extended image functions. */
GX_CLASS gxImgExt : public gxHandle
{

public:

	/** Constructor. */
	gxImgExt() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gximgext", 0)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gximgext", 0)) gxthrow;
		_set_handle(h.handle);
#endif
	}

	/**************************************************************************/
	/** Makes contrast, brightness, saturation and gamma correction on the image.
	 *
	 * The usual values for the adjusting values are between [-1, 1], the level change
	 * calculation can be expressed by the \verbatim new_level = (1+f)*old_level \endverbatim
	 * abstraction.
	 *
	 * The value of -1 discards all the partial information, a value of 0 does not
	 * modify the image setting.
	 *
	 * For the gamma correction other rules are applied. The value of 1 leaves the
	 * image unchanged.
	 *
	 * @param image			Image to process.
	 * @param contrast		Contrast adjust level.
	 * @param brightness	Brightness adjust level.
	 * @param saturation	Saturation adjust level.
	 * @param gamma			Gamma correction level.
	 * @param flags			Color adjusting flags, see \ref GX_COLORADJUST_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool ColorAdjust(gxImage GX_REF_CLASS(image), float contrast GX_DEFARG(0), float brightness GX_DEFARG(0),
			float saturation GX_DEFARG(0), float gamma GX_DEFARG(1), int flags GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image, image);
		bool st = gx_coloradjust(h, _image, contrast, brightness, saturation, gamma, flags) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Makes contrast correction on the image.
	 *
	 * The usual values for the adjusting values are between [-1, 1], the level change
	 * calculation can be expressed by the \verbatim new_level = (1+f)*old_level \endverbatim
	 * abstraction.
	 *
	 * The value of -1 discards all the partial information, a value of 0 does not
	 * modify the image setting.
	 *
	 * In case of adjusting more than one image color parameter the ColorAdjust() function
	 * should be called for performance reasons.
	 *
	 * @param image			Image to process.
	 * @param contrast		Contrast adjust level.
	 * @param flags			Color adjusting flags, see \ref GX_COLORADJUST_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Contrast(gxImage GX_REF_CLASS(image), float contrast, int flags GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image,image);
		bool st = gx_coloradjust(h, _image, contrast, 0, 0, 1.f, flags) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Makes brightness correction on the image.
	 *
	 * The usual values for the adjusting values are between [-1, 1].
	 *
	 * The value of -1 results a black image, a value of 0 does not modify the image setting,
	 * and the value of 1 results a white image.
	 *
	 * In case of adjusting more than one image color parameter the ColorAdjust() function
	 * should be called for performance reasons.
	 *
	 * @param image			Image to process.
	 * @param brightness	Brightness adjust level.
	 * @param flags			Color adjusting flags, see \ref GX_COLORADJUST_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Brightness(gxImage GX_REF_CLASS(image), float brightness, int flags GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image, image);
		bool st = gx_coloradjust(h, _image, 0, brightness, 0, 1.f, flags) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Makes saturation correction on the image.
	 *
	 * The usual values for the adjusting values are between [-1, 1], the level change
	 * calculation can be expressed by the \verbatim new_level = (1+f)*old_level \endverbatim
	 * abstraction.
	 *
	 * The value of -1 discards all the partial information, a value of 0 does not
	 * modify the image setting.
	 *
	 * In case of adjusting more than one image color parameter the ColorAdjust() function
	 * should be called for performance reasons.
	 *
	 * @param image			Image to process.
	 * @param saturation	Saturation adjust level.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Saturation(gxImage GX_REF_CLASS(image), float saturation) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image, image);
		bool st = gx_coloradjust(h, _image, 0, 0, saturation, 1.f, 0) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Makes gamma correction on the image.
	 *
	 * In case of adjusting more than one image color parameter the ColorAdjust() function
	 * should be called for performance reasons.
	 *
	 * @param image		Image to process.
	 * @param gamma		Gamma correction level.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Gamma(gxImage GX_REF_CLASS(image), float gamma) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image, image);
		bool st = gx_coloradjust(h, _image, 0, 0, 0, gamma, 0) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Changes the colors of the source image based on the weight parameters.
	 *
	 * This function is an advanced image manipulating function that can be used in
	 * adaptive processes by setting the weights.
	 *
	 * \note If only the first three weights are defined the resulted image will be
	 * a grayscale image.
	 *
	 * @param target		Preallocated image to return the result.
	 * @param source		Image to process.
	 * @param r1			Adaptable weight.
	 * @param g1			Adaptable weight.
	 * @param b1			Adaptable weight.
	 * @param r2			Adaptable weight.
	 * @param g2			Adaptable weight.
	 * @param b2			Adaptable weight.
	 * @param r3			Adaptable weight.
	 * @param g3			Adaptable weight.
	 * @param b3			Adaptable weight.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool ColorMixer(gxImage GX_REF_CLASS(target), gxImage GX_REF_CLASS(source),
				int r1, int g1, int b1,
				int r2 GX_DEFARG(0), int g2 GX_DEFARG(0), int b2 GX_DEFARG(0),
				int r3 GX_DEFARG(0), int g3 GX_DEFARG(0), int b3 GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_target, target);
		GX_GETIMAGE2(_source, source);
		bool st = gx_colormixer(h, _target, _source, r1, g1, b1, r2, g2, b2, r3, g3, b3) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Generates a differential image from two images.
	 *
	 * @param target		Preallocated image to return the result.
	 * @param source1		First image.
	 * @param source2		Second image.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Difference(gxImage GX_REF_CLASS(target), gxImage GX_REF_CLASS(source1), gxImage GX_REF_CLASS(source2)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_target, target);
		GX_GETIMAGE2(_source1, source1);
		GX_GETIMAGE2(_source2, source2);
		bool st = gx_imagedifference(h, _target, _source1, _source2) != 0;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/**************************************************************************/
	/** Transforms a general area from the source image in the target image.
	 *
	 * @param target		Preallocated image to return the result.
	 * @param source		Image to process.
	 * @param area			General area defined on the source image.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Transform(gxImage & target, gxImage & source, gxPG4 area) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_target, target);
		GX_GETIMAGE2(_source, source);
		bool st = gx_imagetransform(h, _target, _source, area) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Fine transforms an image with the transformation described by the trafo.
	 *
	 * @param target		Preallocated image to return the result.
	 * @param source		Image to process.
	 * @param trafo			Transformation descriptor.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool FTransform(gxImage & target, gxImage & source, gxTrafo & trafo) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_target, target);
		GX_GETIMAGE2(_source, source);
		bool st = gx_imageftransform(h, _target, _source, trafo) != 0;
		gxcondthrow(!st);
		return st;
	}

	/**************************************************************************/
	/** Composes two images.
	 *
	 * @param target		Preallocated image to return the result.
	 * @param upper			Upper image.
	 * @param lower			Lower image.
	 * @param position		Position of the upper image defined on the lower image.
	 * @param alpha_u		Alpha channel of the upper image.
	 * @param alpha_l		Alpha channel of the lower image.
	 * @param flags			Image composing flags, see \ref GX_COMPOSE_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool Compose(gxImage & target, gxImage & upper, gxImage & lower, gxPNT position,
			float alpha_u GX_DEFARG(1),	float alpha_l GX_DEFARG(1), int flags GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_target, target);
		GX_GETIMAGE2(_upper, upper);
		GX_GETIMAGE2(_lower, lower);
		bool st = gx_imagecompose(h, _target, _upper, _lower, position, alpha_u, alpha_l, flags) != 0;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Draw text on an image. If no image given, create a grayscale image.
	 *
	 * @param image			Image to return the result.
	 * @param text			Text to draw.
	 * @param position		Position of the text on image.
	 * @param fonttype		Name of the fontface (WIN32) or path of the font file (LINUX).
	 * @param fontheight	Character height of the text in logical units.
	 * @param fontwidth		Average character width in logical units.
	 * @param txtcolor		Text color.
	 * @param flags			WIN32: see \ref GX_TEXT_FLAGS.
	 * @return		On error false is returned and the error code/string in the GX system
	 *				is set appropriately ( see gx_geterror() ). */
	inline bool DrawText(gxImage & image, const char *text, gxPNT position, const char *fonttype,
						 int fontheight, int fontwidth, void *txtcolor, unsigned int flags) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETIMAGE2(_image, image);

		bool st = gx_drawtext(h, _image, text, position, fonttype, fontheight,
								  fontwidth, txtcolor, flags) != 0;
		gxcondthrow(!st);
		return st;
	}

#endif /* GX_SWIG GX_DOTNET */

};

/******************************************************************************/
#endif	/* NO_GX_CLASSES )*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif /* GX_IMGEXT_INCL */
/******************************************************************************/
