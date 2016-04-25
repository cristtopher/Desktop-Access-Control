/*******************************************************************************
 * GX IMAGE header file - v7.2.10
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Image handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an ease to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the image handling module.
 */
/******************************************************************************/
#ifndef GX_IMAGE_INCL
#define GX_IMAGE_INCL
/******************************************************************************/
#include "gxsd.h"
#if defined(WIN32) && !defined(GX_DOTNET)
	#include <windows.h>
#endif
#include <assert.h>
#include "gxerror.h"
#include "gxvariant.h"
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -rch
#endif
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
#endif
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/
#ifndef GX_EXT_MODULE	/*(*/
/******************************************************************************/
/** Enumerations for pixel format */
GX_ENUM GX_PIXELFORMATS {
	GX_UNDEF	= 0x0000,		/**< Undefined format (for gx_loadimage() functions) */

	GX_GRAY		= 0x0001,		/**<  8 bit: 8 bit (grayscale) */
	GX_RGB555	= 0x0002,		/**< 16 bit: 1-5-5-5 bit (0,R,G,B) */
	GX_BGR555	= 0x0003,		/**< 16 bit: 1-5-5-5 bit (0,B,G,R) */
	GX_RGB565	= 0x0004,		/**< 16 bit: 5-6-5 bit (R,G,B) */
	GX_BGR565	= 0x0005,		/**< 16 bit: 5-6-5 bit (B,G,R) */
	GX_RGB		= 0x0006,		/**< 24 bit: 8-8-8 bit (R,G,B) */
	GX_BGR		= 0x0007,		/**< 24 bit: 8-8-8 bit (B,G,R) */
	GX_RGBA		= 0x0008,		/**< 32 bit: 8-8-8-8 bit (R,G,B,0) */
	GX_BGRA		= 0x0009,		/**< 32 bit: 8-8-8-8 bit (B,G,R,0) */
	GX_YUV422	= 0x000A,		/**< 32 bit/2 pixel: 8-8-8-8 bit (U,Y1,V,Y2) */
	GX_GRAY12	= 0x000B,		/**< 16 bit: 4-12 bit (0,grayscale) */
	GX_RGB12	= 0x000C,		/**< 48 bit: 4-12-4-12-4-12 bit (0,R,0,G,0,B) */
	GX_BGR12	= 0x000D,		/**< 48 bit: 4-12-4-12-4-12 bit (0,B,0,G,0,R) */
	GX_GBRG		= 0x000E,		/**< 32 bit/4 pixel: 8-8-8-8 bit Bayern-pattern (G,B,R,G) */
	GX_BGGR		= 0x000F,		/**< 32 bit/4 pixel: 8-8-8-8 bit Bayern-pattern (B,G,G,R) */
	GX_RGGB		= 0x0010,		/**< 32 bit/4 pixel: 8-8-8-8 bit Bayern-pattern (R,G,G,B) */
	GX_GRBG		= 0x0011,		/**< 32 bit/4 pixel: 8-8-8-8 bit Bayern-pattern (G,R,B,G) */

	GX_FORMAT_FIRST	= GX_GRAY,	/**< First available pixel format */
	GX_FORMAT_LAST	= GX_GRBG	/**< Last available pixel format */
};

/** Enumerations for image file format */
GX_ENUM GX_IMGFILEFORMATS {
	GX_BMP			= 1,			/**< BMP format */
	GX_JPEG			= 2,			/**< JPEG format (ISO/IEC 10918-1) */
	GX_JPEG2K_JPC	= 3,			/**< JPEG-2000 Code stream syntax (ISO/IEC 15444-1) */
	GX_JPEG2K_JP2	= 4,			/**< JPEG-2000 JP2 format syntax (ISO/IEC 15444-1) */
	GX_JPEG2K		= GX_JPEG2K_JP2,/**< JPEG-2000 JP2 format syntax (ISO/IEC 15444-1) */
	GX_RAW			= 5,			/**< RAW format (uncompressed pixel data without header) */
	GX_PNG			= 6,			/**< PNG format (Portable Network Graphics) */
	GX_WSQ			= 7				/**< WSQ format (Wavelet Scalar Quantization) */
};

/** Enumerations for mirror operations */
GX_ENUM GX_MIRRORFLAGS {
	GX_MIRROR_NOMIRROR	 = 0,	/**< No mirroring */
	GX_MIRROR_HORIZONTAL = 1,	/**< Horizontal mirroring */
	GX_MIRROR_VERTICAL	 = 2	/**< Vertical mirroring */
};

/** Enumerations for zoom modes */
GX_ENUM GX_ZOOMMODES {
	GX_ZOOM_NEAREST	= 0,		/**< Nearest algorithm (faster than linear) */
	GX_ZOOM_LINEAR	= 1			/**< Linear algorithm (better than nearest) */
};

/** Enumerations for quick convert */
GX_ENUM GX_QUICKCONVERT {
	GX_CONVERT_NORMAL	= 0,	/**< Normal algorithm */
	GX_CONVERT_QUICK	= 1		/**< Quick algorithm */
};

/** Enumerations for quick display */
GX_ENUM GX_QUICKDISPLAY {
	GX_DISPLAY_NORMAL	= 0,	/**< Normal algorithm */
	GX_DISPLAY_QUICK	= 1		/**< Quick algorithm */
};

/** Enumerations for image comments */
GX_ENUM GX_IMAGECOMMENTS {
	GX_IMGCOMM_GENERAL = 0,		/**< Type of the general image comment. */
	GX_IMGCOMM_JPEG_APP0,		/**< APP0 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP1,		/**< APP1 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP2,		/**< APP2 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP3,		/**< APP3 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP4,		/**< APP4 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP5,		/**< APP5 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP6,		/**< APP6 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP7,		/**< APP7 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP8,		/**< APP8 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP9,		/**< APP9 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP10,		/**< APP10 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP11,		/**< APP11 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP12,		/**< APP12 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP13,		/**< APP13 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP14,		/**< APP14 comment for jpeg applications. */
	GX_IMGCOMM_JPEG_APP15,		/**< APP15 comment for jpeg applications. */
	GX_IMGCOMM_INVALIDFORMAT	/**< Invalid format signal at image loading. */
};

/** Enumerations for image properties */
GX_ENUM GX_IMAGEPROPERTIES1 {
	GX_IMGPROP_BMP_FORCE24BPP = GX_CALL_GROUP_GX_BMP,		/**< Identifier for bmp/force24bpp property.
															 *
															 * The BMP writer forces the 24 bit per pixel mode.
															 * It can be:
															 *	- 0 : the indexed mode is used instead (default)
															 *	- 1 : the writer uses 24 bit per pixel (RGB/BGR) mode (faster than indexed) */

	GX_IMGPROP_BMP_ENABLERLE,								/**< Identifier for bmp/enablerle property.
															 *
															 * The BMP writer can use the RLE compression.
															 * It can be:
															 *	- 0 : disables the RLE compression (faster, default)
															 *	- 1 : enables the RLE compression */

	GX_IMGPROP_JPEG_SCALE_NUM = GX_CALL_GROUP_GX_JPEG,		/**< Identifier for jpeg/decompress/scale_num property. */
	GX_IMGPROP_JPEG_SCALE_DENOM,							/**< Identifier for jpeg/decompress/scale_denom property. */
	GX_IMGPROP_JPEG_DCT_METHOD,								/**< Identifier for jpeg/decompress/dct_method property. */
	GX_IMGPROP_JPEG_DO_FANCY_UPSAMPLING,					/**< Identifier for jpeg/decompress/do_fancy_unsampling property. */
	GX_IMGPROP_JPEG_DO_BLOCK_SMOOTHING,						/**< Identifier for jpeg/decompress/do_block_smoothing property. */

	GX_IMGPROP_JPEG_QUALITY,								/**< Identifier for jpeg/compress/quality property. */
	GX_IMGPROP_JPEG_PROGRESSIVE,							/**< Identifier for jpeg/compress/progressive property. */
	GX_IMGPROP_JPEG_OPTIMIZE_CODING,						/**< Identifier for jpeg/compress/optimize_coding property. */
	GX_IMGPROP_JPEG_RESTART_INTERVAL,						/**< Identifier for jpeg/compress/restart_interval property. */
	GX_IMGPROP_JPEG_RESTART_IN_ROWS,						/**< Identifier for jpeg/compress/restart_in_rows property. */
	GX_IMGPROP_JPEG_SMOOTHING_FACTOR,						/**< Identifier for jpeg/compress/smoothing_factor property. */

	GX_IMGPROP_JPEG2K_IMGAREATLX = GX_CALL_GROUP_GX_JPEG2K,	/**< Identifier for jpeg2k/imgareatlx property. */
	GX_IMGPROP_JPEG2K_IMGAREATLY,							/**< Identifier for jpeg2k/imgareatly property. */
	GX_IMGPROP_JPEG2K_TILEGRDTLX,							/**< Identifier for jpeg2k/tilegrdtlx property. */
	GX_IMGPROP_JPEG2K_TILEGRDTLY,							/**< Identifier for jpeg2k/tilegrdtly property. */
	GX_IMGPROP_JPEG2K_TILEWIDTH,							/**< Identifier for jpeg2k/tilewidth property. */
	GX_IMGPROP_JPEG2K_TILEHEIGHT,							/**< Identifier for jpeg2k/tileheight property. */
	GX_IMGPROP_JPEG2K_PRCWIDTH,								/**< Identifier for jpeg2k/prcwidth property. */
	GX_IMGPROP_JPEG2K_PRCHEIGHT,							/**< Identifier for jpeg2k/prcheight property. */
	GX_IMGPROP_JPEG2K_CBLKWIDTH,							/**< Identifier for jpeg2k/cblkwidth property. */
	GX_IMGPROP_JPEG2K_CBLKHEIGHT,							/**< Identifier for jpeg2k/cblkheight property. */
	GX_IMGPROP_JPEG2K_MODE,									/**< Identifier for jpeg2k/mode property. */
	GX_IMGPROP_JPEG2K_RATE,									/**< Identifier for jpeg2k/rate property. */
	GX_IMGPROP_JPEG2K_ILYRRATES,							/**< Identifier for jpeg2k/ilyrrates property. */
	GX_IMGPROP_JPEG2K_PRG,									/**< Identifier for jpeg2k/prg property. */
	GX_IMGPROP_JPEG2K_NOMCT,								/**< Identifier for jpeg2k/nomct property. */
	GX_IMGPROP_JPEG2K_NUMRLVLS,								/**< Identifier for jpeg2k/numrlvls property. */
	GX_IMGPROP_JPEG2K_SOP,									/**< Identifier for jpeg2k/sop property. */
	GX_IMGPROP_JPEG2K_EPH,									/**< Identifier for jpeg2k/eph property. */
	GX_IMGPROP_JPEG2K_LAZY,									/**< Identifier for jpeg2k/lazy property. */
	GX_IMGPROP_JPEG2K_TERMALL,								/**< Identifier for jpeg2k/termall property. */
	GX_IMGPROP_JPEG2K_SEGSYM,								/**< Identifier for jpeg2k/segsym property. */
	GX_IMGPROP_JPEG2K_VCAUSAL,								/**< Identifier for jpeg2k/vcausal property. */
	GX_IMGPROP_JPEG2K_PTERM,								/**< Identifier for jpeg2k/pterm property. */
	GX_IMGPROP_JPEG2K_RESETPROB,							/**< Identifier for jpeg2k/resetprob property. */
	GX_IMGPROP_JPEG2K_NUMGBITS,								/**< Identifier for jpeg2k/numgbits property. */

	GX_IMGPROP_WSQ_BITRATE	= GX_CALL_GROUP_GX_WSQ					/**< Identifier for WSQ bitrate property. */
};
/******************************************************************************/
#endif	/*)*/
/******************************************************************************/
#if defined(GX_DOTNET) && !defined(GX_MANUAL)
	#pragma unmanaged
	#define gxIMAGE _gxIMAGE
	#define HDC void*
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !(defined(GX_MANUAL) && defined(GX_DOTNET))	/*(*/
/** Structure which stores data of an image */
struct gxIMAGE {
	gxi32				gxid;	/**< Structure identifier. */
	gxi32				ref;	/**< Reference counter. */
	void*				image;	/**< Pointer to pixel data. */
	gxi32				simage;	/**< Size of an image area in bytes (allocated space = ysize*sline) */
	gxi32				format;	/**< Pixel format (see \ref GX_PIXELFORMATS) */
	gxi32				xsize;	/**< Horizontal size of the image in pixels. */
	gxi32				ysize;	/**< Vertical size of the image in pixels. */
	gxi32				sline;	/**< Size of a row in bytes. */

	/** Horizontal resolution.
	 * \par
	 * On a free air camera system such as number plate or face capturing
	 * this value is related to a PAL or NTSC image in percentage.\n
	 * For example:
	 *	- in case of PAL image 768 pixel = 100 %, 384 pixel = 50 %
	 *	- in case of NTSC image 640 pixel = 100 %, 320 pixel = 50 %
	 * \par
	 * On a fixed object windowed camera system like document capturing
	 * this value is definied in pixel-per-meter (for example 300 DPI = 11811 pix/m).
	 * \par
	 * (0 value = not defined) */
	gxi32				xres;
	/** Vertical resolution.
	 * \par
	 * On a free air camera system such as number plate or face capturing
	 * this value is related to a PAL or NTSC image in percentage.\n
	 * For example:
	 *	- in case of PAL image 576 pixel = 100 %, 288 pixel = 50 %
	 *	- in case of NTSC image 480 pixel = 100 %, 240 pixel = 50 %
	 * \par
	 * On a fixed object windowed camera system like document capturing
	 * this value is definied in pixel-per-meter (for example 300 DPI = 11811 pix/m).
	 * \par
	 * (0 value = not defined) */
	gxi32				yres;
};
/******************************************************************************/
#ifndef __cplusplus
	typedef struct gxIMAGE gxIMAGE;	/**< Workaround for ANSI C */
#endif
/******************************************************************************/
#endif	/* GX_SWIGIF GX_MANUAL GX_DOTNET )*/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/******************************************************************************/
/* Call codes for image operations. */
enum {
	GX_CALL_GETPIXELSIZE		= GX_CALL_GROUP_GX_IMAGE,	/**< Call code for the gx_getpixelsize() function. */
	GX_CALL_CONVERTPIXELS,		/**< Call code for the gx_convertpixels() function. */
	GX_CALL_FASTRECONVERT,		/**< Call code for the gx_fastreconvert() function. */
	GX_CALL_ZOOMPIXELS,			/**< Call code for the gx_zoompixels() function. */
	GX_CALL_ROTATEPIXELS,		/**< Call code for the gx_rotatepixels() function. */
	GX_CALL_MIRRORPIXELS,		/**< Call code for the gx_mirrorpixels() function. */
	GX_CALL_INITIMAGE,			/**< Call code for the gx_initimage() function. */
	GX_CALL_ALLOCIMAGE,			/**< Call code for the gx_allocimage() function. */
	GX_CALL_FREEIMAGE,			/**< Call code for the gx_freeimage() function. */
	GX_CALL_REFIMAGE,			/**< Call code for the gx_refimage() function. */
	GX_CALL_UNREFIMAGE,			/**< Call code for the gx_unrefimage() function. */
	GX_CALL_CREATEIMAGE,		/**< Call code for the gx_createimage() function. */
	GX_CALL_CONVERTIMAGE,		/**< Call code for the gx_convertimage() function. */
	GX_CALL_ZOOMIMAGE,			/**< Call code for the gx_zoomimage() function. */
	GX_CALL_ROTATEIMAGE,		/**< Call code for the gx_rotateimage() function. */
	GX_CALL_MIRRORIMAGE,		/**< Call code for the gx_mirrorimage() function. */
	GX_CALL_LOADIMAGE,			/**< Call code for the gx_loadimage() function (Unicode version). */
	GX_CALL_LOADIMAGEA,			/**< Call code for the gx_loadimage() function (ASCII version). */
	GX_CALL_SAVEIMAGE,			/**< Call code for the gx_saveimage() function (Unicode version). */
	GX_CALL_SAVEIMAGEA,			/**< Call code for the gx_saveimage() function (ASCII version). */
	GX_CALL_LOADFROMMEM,		/**< Call code for the gx_loadfrommem() function. */
	GX_CALL_SAVETOMEM,			/**< Call code for the gx_savetomem() function. */
	GX_CALL_ISVALIDIMAGE,		/**< Call code for the gx_isvalidimage() function. */
	GX_CALL_DISPLAYIMAGE,		/**< Call code for the gx_displayimage() function. */
	GX_CALL_GETPIXELPTR,		/**< Call code for the gx_getpixelptr() function. */
	GX_CALL_IMGTOCLIPBOARD,		/**< Call code for the gx_imgtoclipboard() function. */
	GX_CALL_PASTEIMAGE,			/**< Call code for the gx_pasteimage() function. */

	GX_CALL_LOADIMAGEFROMFILE,	/**< Call code for the gx_loadimagefromfile() function (Unicode version). */
	GX_CALL_LOADIMAGEFROMFILEA,	/**< Call code for the gx_loadimagefromfile() function (ASCII version). */
	GX_CALL_LOADIMAGEFROMMEM,	/**< Call code for the gx_loadfrommem() function. */
	GX_CALL_SAVEIMAGETOFILE,	/**< Call code for the gx_saveimagetofile() function (Unicode version). */
	GX_CALL_SAVEIMAGETOFILEA,	/**< Call code for the gx_saveimagetofile() function (ASCII version). */
	GX_CALL_SAVEIMAGETOMEM,		/**< Call code for the gx_saveimagetomem() function. */

	GX_CALL_COPYIMAGE,			/**< Call code for the gx_copyimage() function. */
	GX_CALL_IMAGETOVARIANT,		/**< Call code for the gx_imagetovariant() function. */
	GX_CALL_IMAGEFROMVARIANT,	/**< Call code for the gx_imagefromvariant() function. */

	GX_CALL_TESTIMAGEFILEFORMAT,	/**< Call code for the gx_testimagefileformat() function. */
	GX_CALL_TESTIMAGEFILEFORMATA,	/**< Call code for the gx_testimagefileformata() function. */
	GX_CALL_TESTIMAGEFILEFORMATMEM,	/**< Call code for the gx_testimagefileformatmem() function. */

	GX_CALL_GETIMAGEFILEFORMATINFO,	/**< Call code for the gx_getimagefileformatinfo() function. */
	GX_CALL_SAVEIMAGETOFILE2,	/**< Call code for the gx_saveimagetofile2() function (Unicode version). */
	GX_CALL_SAVEIMAGETOMEM2,	/**< Call code for the gx_saveimagetomem2() function. */

	GX_CALL_TESTIMAGEFILEFORMATID,	/**< Call code for the gx_testimagefileformatid() function. */
	GX_CALL_TESTIMAGEFILEFORMATIDMEM,	/**< Call code for the gx_testimagefileformatidmem() function. */
};
/******************************************************************************/
/* Parameter structure for the gx_getpixelsize() function. */
struct GX_PARM_GETPIXELSIZE {
	gxi32 format;	/**< Pixel format. */
	gxi32 size;		/**< Size of the pixel format. */
};

/* Parameter structure for the gx_convertpixels() function. */
struct GX_PARM_CONVERTPIXELS {
	void *target;			/**< Pointer to a pixel data to where the function stores the data. */
	gxi32 tformat;			/**< Pixel format of the target area. */
	gxi32 tsline;			/**< Size of a row of the target area in bytes. */
	const void *source;		/**< Pointer to a pixel data. */
	gxi32 sformat;			/**< Pixel format of the source area */
	gxi32 ssline;			/**< Size of a row of the source area in bytes. */
	gxi32 xsize;			/**< Horizontal size of the pixel area. */
	gxi32 ysize;			/**< Vertical size of the pixel area. */
};

/** Parameter structure for the gx_fastreconvert() function.
 *
 * The fast reconvert function can be used for converting:
 * - RGB555,BGR555,RGB565,BGR565 \<-\> RGB555,BGR555,RGB565,BGR565
 * - RGB,BGR \<-\> RGB,BGR
 * - RGBA,BGRA \<-\> RGBA,BGRA
 * - RGB12,BGR12 \<-\> RGB12,BGR12 */
struct GX_PARM_FASTRECONVERT {
	void *pixels;		/**< Pointer to a pixel data. */
	gxi32 tformat;		/**< Pixel format of the destination image. */
	gxi32 sformat;		/**< Pixel format of the source image. */
	gxi32 sline;		/**< Size of a row of the pixel area in bytes. */
	gxi32 xsize;		/**< Horizontal size of the pixel area. */
	gxi32 ysize;		/**< Vertical size of the pixel area. */
};

/** Parameter structure for the gx_zoompixels() function. */
struct GX_PARM_ZOOMPIXELS {
	void *target;		/**< Pointer to an allocated area where the zoom function places the converted image. */
	gxi32 tsline;		/**< Size of a row of the destination area. */
	gxi32 txsize;		/**< Horizontal size of the destination area. */
	gxi32 tysize;		/**< Vertical size of the destination area. */
	const void *source;	/**< Pointer to pixels of source area. */
	gxi32 ssline;		/**< Size of a row of the source area. */
	gxi32 sxsize;		/**< Horizontal size of the source area. */
	gxi32 sysize;		/**< Vertical size of the source area. */
	gxi32 format;		/**< Pixel format. */
	gxi32 sx1_8;		/**< Left coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32 sy1_8;		/**< Top coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32 sx2_8;		/**< Right coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32 sy2_8;		/**< Bottom coordinate of zoom area (shifted left with 8 bit = 256) */
};

/** Parameter structure for the gx_rotatepixels() function. */
struct GX_PARM_ROTATEPIXELS {
	void *target;		/**< Pointer to an allocated area where the rotate function places the rotated image. */
	gxi32 tsline;		/**< Size of a row of the destination area. */
	gxi32 txsize;		/**< Horizontal size of the destination area. */
	gxi32 tysize;		/**< Vertical size of the destination area. */
	const void *source;	/**< Pointer to pixels of source area. */
	gxi32 ssline;		/**< Size of a row of the source area. */
	gxi32 sxsize;		/**< Horizontal size of the source area. */
	gxi32 sysize;		/**< Vertical size of the source area. */
	gxi32 format;		/**< Pixel format. */
	gxi32 degree;		/**< Degree (Must be 0, 90, 180, 270). */
};

/** Parameter structure for the gx_mirrorpixels() function. */
struct GX_PARM_MIRRORPIXELS {
	void *target;		/**< Pointer to an allocated area where the mirror function places the mirror image. */
	gxi32 tsline;		/**< Size of a row of the destination area. */
	gxi32 txsize;		/**< Horizontal size of the destination area. */
	gxi32 tysize;		/**< Vertical size of the destination area. */
	const void *source;	/**< Pointer to pixels of source area. */
	gxi32 ssline;		/**< Size of a row of the source area. */
	gxi32 sxsize;		/**< Horizontal size of the source area. */
	gxi32 sysize;		/**< Vertical size of the source area. */
	gxi32 format;		/**< Pixel format. */
	gxi32 flags;		/**< Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL. */
};

/** Parameter structure for the gx_createimage() function. */
struct GX_PARM_CREATEIMAGE {
	gxIMAGE *pimage;	/**< Pointer to an initialized image structure. */
	gxi32	 format;	/**< Pixel format. */
	gxi32	 xsize;		/**< Horizontal size of the image in pixels. */
	gxi32	 ysize;		/**< Vertical size of the image in pixels. */
	gxi32	 sline;		/**< Length of a row in bytes (min.: xsize * size of a pixel in bytes). If zero the system computes the correct value. */
};

/** Parameter structure for the gx_convertimage() function. */
struct GX_PARM_CONVERTIMAGE {
	gxIMAGE *pdest;		/**< Pointer to an image where the function writes the converted image. */
	gxIMAGE *psrc;		/**< Pointer to the source image. If it is equal to pdest the function attempts to fast reconvert. */
	gxi32	 format;	/**< Pixel format. */
	gxi32	 xsize;		/**< Horizontal size of the image in pixels. */
	gxi32	 ysize;		/**< Vertical size of the image in pixels. */
	gxi32	 sline;		/**< Length of a row of the destination image in bytes. If zero the system computes the correct value. */
};

/** Parameter structure for the gx_zoomimage() function. */
struct GX_PARM_ZOOMIMAGE {
	gxIMAGE	 *pdest;	/**< Pointer to an image where the zoom function places the converted image. */
	gxi32	  xsize;	/**< Horizontal size of the destination image. */
	gxi32	  ysize;	/**< Vertical size of the destination image. */
	gxi32	  sline;	/**< Length of a row of the destination image in bytes. It can be zero. */
	gxIMAGE	 *psrc;		/**< Pointer to the source image. */
	gxi32	  sx1_8;	/**< Left coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32	  sy1_8;	/**< Top coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32	  sx2_8;	/**< Right coordinate of zoom area (shifted left with 8 bit = 256) */
	gxi32	  sy2_8;	/**< Bottom coordinate of zoom area (shifted left with 8 bit = 256) */
};

/** Parameter structure for the gx_rotateimage() function. */
struct GX_PARM_ROTATEIMAGE {
	gxIMAGE	*pdest;		/**< Pointer to an image where the rotate function places the converted image. */
	gxIMAGE *psrc;		/**< Pointer to the source image. */
	gxi32	 degree;	/**< Degree (Must be 0, 90, 180, 270). */
};

/** Parameter structure for the gx_mirrorimage() function. */
struct GX_PARM_MIRRORIMAGE {
	gxIMAGE	*pdest;		/**< Pointer to an image where the mirror function places the converted image. */
	gxIMAGE *psrc;		/**< Pointer to the source image. */
	gxi32	 flags;		/**< Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL. */
};

/** Parameter structure for the gx_loadimage() function (Unicode version). */
struct GX_PARM_LOADIMAGE {
	gxIMAGE *pimage;		/**< Pointer to an image where the function loads the data to. */
	const wchar_t *filename;/**< Name of the image file. */
	gxi32	 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale). */
};

/** Parameter structure for the gx_loadimage() function (ASCII version). */
struct GX_PARM_LOADIMAGEA {
	gxIMAGE *pimage;		/**< Pointer to an image where the function loads the data to. */
	const char *filename;	/**< Name of the image file. */
	gxi32	 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale). */
};

/** Parameter structure for the gx_saveimage() function (Unicode version). */
struct GX_PARM_SAVEIMAGE {
	gxIMAGE *pimage;		/**< Pointer to the image. */
	const wchar_t *filename;/**< Name of the image file. */
	gxi32	 fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
};

/** Parameter structure for the gx_saveimage() function (ASCII version). */
struct GX_PARM_SAVEIMAGEA {
	gxIMAGE *pimage;		/**< Pointer to the image. */
	const char *filename;	/**< Name of the image file. */
	gxi32	 fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
};

/** Parameter structure for the gx_loadfrommem() function. */
struct GX_PARM_LOADFROMMEM {
	gxIMAGE	*pimage;		/**< Pointer to an image where the function loads the data to. */
	const void *buffer;		/**< Pointer to the image data. */
	gxi32	 buflen;		/**< Length of image data in bytes. */
	gxi32	 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale). */
};

/** Parameter structure for the gx_savetomem() function. */
struct GX_PARM_SAVETOMEM {
	gxIMAGE *pimage;		/**< Pointer to the image. */
	void	**buffer;		/**< Pointer to a memory area pointer. */
	gxi32	*buflen;		/**< Size of memory area. */
	gxi32	 fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
};

#if defined(WIN32)
/** Parameter structure for the gx_displayimage() function. */
struct GX_PARM_DISPLAYIMAGE {
	HDC		 hdc;			/**< Device handle. */
	gxi32	 x;				/**< X1 coordinate where the function writes the first pixel of the image. */
	gxi32	 y;				/**< Y1 coordinate where the function writes the first pixel of the image. */
	gxi32	 xsize;			/**< Horizontal size of displayed area. */
	gxi32	 ysize;			/**< Vertical size of displayed area. */
	gxIMAGE *pimage;		/**< Pointer to the image. */
};
#endif

/** Parameter structure for the gx_getpixelptr() function. */
struct GX_PARM_GETPIXELPTR {
	gxIMAGE *pimage;		/**< Pointer to the image. */
	gxi32	 x;				/**< X coordinate of the pixel. */
	gxi32	 y;				/**< Y coordinate of the pixel. */
	void	*ptr;			/**< Returned pointer of the pixel. */
};

/** Parameter structure for the gx_loadimagefromfile() function (Unicode version). */
struct GX_PARM_LOADIMAGEFROMFILE {
	gxIMAGE			*pimage;		/**< Pointer to an image where the function loads the data to. */
	const wchar_t	*filename;		/**< Name of the image file. */
	gxi32			 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale) .*/
	gxVARIANT		 properties;	/**< Properties for the image loader. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_loadimagefromfilea() function (ASCII version). */
struct GX_PARM_LOADIMAGEFROMFILEA {
	gxIMAGE			*pimage;		/**< Pointer to an image where the function loads the data to. */
	const char		*filename;		/**< Name of the image file. */
	gxi32	 		 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale). */
	gxVARIANT		 properties;	/**< Properties for the image loader. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_saveimagetofile() function (Unicode version). */
struct GX_PARM_SAVEIMAGETOFILE {
	gxIMAGE			*pimage;		/**< Pointer to the image. */
	const wchar_t	*filename;		/**< Name of the image file. */
	gxi32	 		 fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
	gxVARIANT		 properties;	/**< Properties for the image creator. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_saveimagetofilea() function (ASCII version). */
struct GX_PARM_SAVEIMAGETOFILEA {
	gxIMAGE			*pimage;		/**< Pointer to the image. */
	const char		*filename;		/**< Name of the image file. */
	gxi32	 		 fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
	gxVARIANT		 properties;	/**< Properties for the image creator. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_saveimagetofile2() function (Unicode version). */
struct GX_PARM_SAVEIMAGETOFILE2 {
	gxIMAGE			*pimage;		/**< Pointer to the image. */
	const wchar_t	*filename;		/**< Name of the image file. */
	const wchar_t	*fileformat;	/**< Format of the image file (giving "bmp" writes the file in BMP format). */
	gxVARIANT		 properties;	/**< Properties for the image creator. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_loadimagefrommem() function. */
struct GX_PARM_LOADIMAGEFROMMEM {
	gxIMAGE			*pimage;		/**< Pointer to an image where the function loads the data to. */
	const void		*buffer;		/**< Pointer to the image data. */
	gxi32	 		 buflen;		/**< Length of image data in bytes. */
	gxi32	 		 format;		/**< The specific pixel format (giving GX_GRAY converts a color image to grayscale). */
	gxVARIANT		 properties;	/**< Properties for the image loader. It can be NULL. */
	gxVARIANT		 comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_saveimagetomem() function. */
struct GX_PARM_SAVEIMAGETOMEM {
	gxIMAGE			 *pimage;		/**< Pointer to the image. */
	void			**buffer;		/**< Pointer to a memory area pointer. */
	gxi32			 *buflen;		/**< Size of memory area. */
	gxi32	 		  fileformat;	/**< Format of the image file (giving GX_BMP writes the file in BMP format). */
	gxVARIANT		  properties;	/**< Properties for the image creator. It can be NULL. */
	gxVARIANT		  comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_saveimagetomem2() function. */
struct GX_PARM_SAVEIMAGETOMEM2 {
	gxIMAGE			 *pimage;		/**< Pointer to the image. */
	void			**buffer;		/**< Pointer to a memory area pointer. */
	gxi32			 *buflen;		/**< Size of memory area. */
	const wchar_t	 *fileformat;	/**< Format of the image file (giving "bmp" writes the file in BMP format). */
	gxVARIANT		  properties;	/**< Properties for the image creator. It can be NULL. */
	gxVARIANT		  comments;		/**< Comments of the image. It can be NULL. */
};

/** Parameter structure for the gx_copyimage() function. */
struct GX_PARM_COPYIMAGE {
	gxIMAGE		*target;		/**< Pointer to an initialized destination structure. */
	gxIMAGE		*source;		/**< Pointer to the source. */
};

/** Parameter structure for the gx_imagetovariant() function. */
struct GX_PARM_IMAGETOVARIANT {
	gxIMAGE		*pimage;		/**< Pointer to the image. */
	int			 varid;			/**< The new variant id. */
	gxVARIANT	 variant;		/**< Variant structure for result. */
};

/** Parameter structure for the gx_imagefromvariant() function. */
struct GX_PARM_IMAGEFROMVARIANT {
	gxIMAGE		*pimage;		/**< Pointer to an initialized destination structure. */
	gxVARIANT	 variant;		/**< Source variant structure. */
};

/** Parameter structure for the gx_testimagefileformat() function. */
struct GX_PARM_TESTIMAGEFILEFORMAT {
	const wchar_t	*filename;	/**< Name of the image file. */
	gxi32			 fileformat;	/**< Format of the image file. */
};

/** Parameter structure for the gx_testimagefileformata() function. */
struct GX_PARM_TESTIMAGEFILEFORMATA {
	const char	*filename;		/**< Name of the image file. */
	gxi32		 fileformat;	/**< Format of the image file. */
};

/** Parameter structure for the gx_testimagefileformatmem() function. */
struct GX_PARM_TESTIMAGEFILEFORMATMEM {
	const void	*buffer;		/**< Pointer to a memory area pointer. */
	gxi32		 buflen;		/**< Size of memory area. */
	gxi32		 fileformat;	/**< Format of the image file. */
};

/** Parameter structure for the gx_testimagefileformatid() function. */
struct GX_PARM_TESTIMAGEFILEFORMATID {
	const wchar_t	*filename;	/**< Name of the image file. */
	wchar_t*		 formatid;	/**< Format Id of the image file. */
	gxi32			 slen;		/**< Size of memory area. */
};

/** Parameter structure for the gx_testimagefileformatidmem() function. */
struct GX_PARM_TESTIMAGEFILEFORMATIDMEM {
	const void	*buffer;		/**< Pointer to a memory area pointer. */
	gxi32		 buflen;		/**< Size of memory area. */
	wchar_t*		 formatid;	/**< Format Id of the image file. */
	gxi32			 slen;		/**< Size of memory area. */
};

#endif	/* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)	/*(*/
/******************************************************************************/

/******************************************************************************/
/** Returns the size of a pixel in bytes.
 * @see GX_PARM_GETPIXELSIZE
 * @param handle Handle of the module.
 * @param size Size of the pixel format.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @return	On error false is returned and the error code/string in the GX system
 *			is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_getpixelsize(gxHANDLE handle, gxi32 *size, gxi32 format) {
	struct GX_PARM_GETPIXELSIZE ps;
	gxi32 ret;
	assert(size);
	ps.format = format;
	ret = gx_call(handle, GX_CALL_GETPIXELSIZE, &ps);
	if(ret) *size = ps.size;
	return ret;
}

/******************************************************************************/
/** Converts pixels to a specified format and size.
 * @see GX_PARM_CONVERTPIXELS
 * @param handle Handle of the module.
 * @param target Pointer to a pixel data to where the function stores the data.
 * @param tformat Pixel format of the target area (see \ref GX_PIXELFORMATS).
 * @param tsline Size of a row of the target area in bytes.
 * @param source Pointer to a pixel data.
 * @param sformat Pixel format of the source area (see \ref GX_PIXELFORMATS).
 * @param ssline Size of a row of the source area in bytes.
 * @param xsize Horizontal size of the pixel area.
 * @param ysize Vertical size of the pixel area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_convertpixels(gxHANDLE handle,
					void *target, gxi32 tformat, gxi32 tsline,
					const void *source, gxi32 sformat, gxi32 ssline,
					gxi32 xsize, gxi32 ysize) {

	struct GX_PARM_CONVERTPIXELS cp;
	cp.target = target;
	cp.tformat = tformat;
	cp.tsline = tsline;
	cp.source = source;
	cp.sformat = sformat;
	cp.ssline = ssline;
	cp.xsize = xsize;
	cp.ysize = ysize;
	return gx_call(handle, GX_CALL_CONVERTPIXELS, &cp);
}

/******************************************************************************/
/** Fast converts pixels to a specified format and size.
 *
 * The function is the same as gx_convertpixels(), only it works on the same memory area.
 * \par
 * The fast reconvert function can be used for converting:
 * - RGB555,BGR555,RGB565,BGR565 \<-\> RGB555,BGR555,RGB565,BGR565
 * - RGB,BGR \<-\> RGB,BGR
 * - RGBA,BGRA \<-\> RGBA,BGRA
 * - RGB12,BGR12 \<-\> RGB12,BGR12
 * @param handle Handle of the module.
 * @param pixels Pointer to a pixel data.
 * @param tformat Pixel format of the destination image (see \ref GX_PIXELFORMATS).
 * @param sformat Pixel format of the source image (see \ref GX_PIXELFORMATS).
 * @param sline Size of a row of the pixel area in bytes.
 * @param xsize Horizontal size of the pixel area.
 * @param ysize Vertical size of the pixel area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_fastreconvert(gxHANDLE handle,
						void *pixels, gxi32 tformat, gxi32 sformat,
						gxi32 sline, gxi32 xsize, gxi32 ysize) {

	struct GX_PARM_FASTRECONVERT fr;
	fr.pixels = pixels;
	fr.tformat = tformat;
	fr.sformat = sformat;
	fr.sline = sline;
	fr.xsize = xsize;
	fr.ysize = ysize;
	return gx_call(handle, GX_CALL_FASTRECONVERT, &fr);
}

/******************************************************************************/
/** Zooms pixels to a specified size.
 * @param handle Handle of the module.
 * @param target Pointer to an allocated area where the zoom function places the
 *               converted image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param sx1_8  Left coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sy1_8  Top coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sx2_8  Right coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sy2_8  Bottom coordinate of zoom area (shifted left with 8 bit = 256)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_zoompixels(gxHANDLE handle,
						void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format,
						gxi32 sx1_8 GX_DEFARG(0), gxi32 sy1_8 GX_DEFARG(0),
						gxi32 sx2_8 GX_DEFARG(0), gxi32 sy2_8 GX_DEFARG(0))
						{

	struct GX_PARM_ZOOMPIXELS zp;
	assert(target);
	assert(source);
	zp.target = target;
	zp.tsline = tsline;
	zp.txsize = txsize;
	zp.tysize = tysize;
	zp.source = (void *)source;
	zp.ssline = ssline;
	zp.sxsize = sxsize;
	zp.sysize = sysize;
	zp.format = format;
	zp.sx1_8  = sx1_8;
	zp.sy1_8  = sy1_8;
	zp.sx2_8  = sx2_8;
	zp.sy2_8  = sy2_8;
	return gx_call(handle, GX_CALL_ZOOMPIXELS, &zp);
}

/******************************************************************************/
/** Rotates pixels to a specified degree.
 * @param handle Handle of the module.
 * @param target Pointer to an allocated area where the rotate function places
 *               the rotated image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param degree Degree (Must be 0, 90, 180, 270).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_rotatepixels(gxHANDLE handle,
						void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format, gxi32 degree) {

	struct GX_PARM_ROTATEPIXELS rp;
	assert(target);
	assert(source);
	rp.target = target;
	rp.tsline = tsline;
	rp.txsize = txsize;
	rp.tysize = tysize;
	rp.source = source;
	rp.ssline = ssline;
	rp.sxsize = sxsize;
	rp.sysize = sysize;
	rp.format = format;
	rp.degree = degree;
	return gx_call(handle, GX_CALL_ROTATEPIXELS, &rp);
}

/******************************************************************************/
/** Mirrors pixels to a specified mode.
 * @param handle Handle of the module.
 * @param target Pointer to an allocated area where the mirror function places
 *               the mirrored image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param flags  Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL.
 *               (see \ref GX_MIRRORFLAGS)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorpixels(gxHANDLE handle,
						void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format, gxi32 flags) {

	struct GX_PARM_MIRRORPIXELS mp;
	assert(target);
	assert(source);
	mp.target = target;
	mp.tsline = tsline;
	mp.txsize = txsize;
	mp.tysize = tysize;
	mp.source = source;
	mp.ssline = ssline;
	mp.sxsize = sxsize;
	mp.sysize = sysize;
	mp.format = format;
	mp.flags = flags;
	return gx_call(handle, GX_CALL_MIRRORPIXELS, &mp);
}

#ifdef __cplusplus
/******************************************************************************/
/** Mirrors pixels to a specified mode.
 * @param handle Handle of the module.
 * @param pixels Pointer to pixels of the pixel area.
 * @param sline  Size of a row of the pixel area.
 * @param xsize  Horizontal size of the pixel area.
 * @param ysize  Vertical size of the pixel area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param flags  Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL.
 *               (see \ref GX_MIRRORFLAGS)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorpixels(gxHANDLE handle,
						void *pixels, gxi32 sline, gxi32 xsize, gxi32 ysize,
						gxi32 format, gxi32 flags) {
	return gx_mirrorpixels(handle, pixels, sline, xsize, ysize,
						pixels, sline, xsize, ysize,
						format, flags);
}
#endif

/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Initialization of an image located on the heap or stack.
 *
 * This function fills the structure identifier and the reference counter
 * properly. The other data members are set to zero value.
 * \warning Do not call it for a dynamic allocated image (gx_allocimage)!
 * @param handle Handle of the module.
 * @param pimage Pointer to the not initialized image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_initimage(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_INITIMAGE, (void *)pimage);
}

/******************************************************************************/
/** This function allocates a blank image.
 *
 * The structure identifier and the reference counter will be properly filled.
 * The other data members are set to zero value.
 * @param handle Handle of the module.
 * @param pimage Pointer to a \a gxIMAGE structure pointer where the function
 *               returns the pointer of the allocated image area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_allocimage(gxHANDLE handle, gxIMAGE **pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_ALLOCIMAGE, (void *)pimage);
}

/******************************************************************************/
/** Frees an image structure including the allocated pixel data.
 *
 * If the value of the reference counter is not properly set the function returns an
 * error. In case of dynamically allocated images it is advised to use
 * \a gx_unrefimage.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_freeimage(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_FREEIMAGE, (void *)pimage);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_reference
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Increases the image reference counter.
 *
 * The counter indicates the number of processes using the image. The counter
 * can rise to positive or negative direction as well depending on whether the image
 * is static or dynamic.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_refimage(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_REFIMAGE, (void *)pimage);
}

/******************************************************************************/
/** Decreases the image reference counter.
 *
 * The counter indicates the number of processes using the image. If the
 * counter value becomes zero after the function call the structure will be
 * freed depending on whether the image was allocated statically or dynamically.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_unrefimage(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_UNREFIMAGE, (void *)pimage);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Makes an image with proper size and format running on an initialized image
 * structure.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image structure.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param xsize Horizontal size of image in pixels.
 * @param ysize Vertical size of image in pixels.
 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
 *         bytes). If zero the system computes the correct value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_createimage(gxHANDLE handle, gxIMAGE* pimage, gxi32 format,
							gxi32 xsize, gxi32 ysize, gxi32 sline) {
	struct GX_PARM_CREATEIMAGE ci;
	assert(pimage);
	assert(xsize > 0);
	assert(ysize > 0);
	ci.pimage = pimage;
	ci.format = format;
	ci.xsize = xsize;
	ci.ysize = ysize;
	ci.sline = sline;
	return gx_call(handle, GX_CALL_CREATEIMAGE, (void *)&ci);
}

/******************************************************************************/
/** Converts an image to a specific format and size.
 *
 * The destination image must be initialized.
 * @param handle Handle of the module.
 * @param pdest Pointer to an initialized image where the function places the
 *              converted image.
 * @param psrc Pointer to the source image.
 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
 * @param xsize Horizontal size of the destination image in pixels.
 * @param ysize Vertical size of the destination image in pixels.
 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
 *         bytes). If zero the system computes the correct value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_convertimage(gxHANDLE handle, gxIMAGE* pdest,
						gxIMAGE* psrc, gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline) {

	struct GX_PARM_CONVERTIMAGE ci;
	assert(pdest);
	assert(psrc);
	assert(xsize > 0);
	assert(ysize > 0);
	ci.pdest = pdest;
	ci.psrc = psrc;
	ci.format = format;
	ci.xsize = xsize;
	ci.ysize = ysize;
	ci.sline = sline;
	return gx_call(handle, GX_CALL_CONVERTIMAGE, (void *)&ci);
}

/******************************************************************************/
/** Zooms an image to a specified size.
 * @param handle Handle of the module.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param xsize Horizontal size of the destination area.
 * @param ysize Vertical size of the destination area.
 * @param sline Size of a row of the destination area.
 * @param psrc  Pointer to the source image.
 * @param sx1_8 Left coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sy1_8 Top coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sx2_8 Right coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sy2_8 Bottom coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_zoomimage(gxHANDLE handle, gxIMAGE *pdest,
					gxi32 xsize, gxi32 ysize, gxi32 sline,
					gxIMAGE *psrc,
					gxi32 sx1_8 GX_DEFARG(0), gxi32 sy1_8 GX_DEFARG(0),
					gxi32 sx2_8 GX_DEFARG(0), gxi32 sy2_8 GX_DEFARG(0)) {

	struct GX_PARM_ZOOMIMAGE zi;
	assert(pdest);
	assert(psrc);
	assert(xsize > 0);
	assert(ysize > 0);
	zi.pdest = pdest;
	zi.xsize = xsize;
	zi.ysize = ysize;
	zi.sline = sline;
	zi.psrc  = psrc;
	zi.sx1_8 = sx1_8;
	zi.sy1_8 = sy1_8;
	zi.sx2_8 = sx2_8;
	zi.sy2_8 = sy2_8;
	return gx_call(handle, GX_CALL_ZOOMIMAGE, (void *)&zi);
}

/******************************************************************************/
/** Rotates an image to a specified degree.
 * @param handle Handle of the module.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param psrc  Pointer to the source image.
 * @param degree Degree (Must be 0, 90, 180, 270).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_rotateimage(gxHANDLE handle, gxIMAGE *pdest,
						gxIMAGE *psrc, gxi32 degree) {

	struct GX_PARM_ROTATEIMAGE ri;
	assert(pdest);
	assert(psrc);
	ri.pdest = pdest;
	ri.psrc = psrc;
	ri.degree = degree;
	return gx_call(handle, GX_CALL_ROTATEIMAGE, &ri);
}

/******************************************************************************/
/** Mirrors an image to a specified mode.
 * @param handle Handle of the module.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param psrc  Pointer to the source image.
 * @param flags Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and
 *              GX_MIRROR_VERTICAL (see \ref GX_MIRRORFLAGS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorimage(gxHANDLE handle, gxIMAGE *pdest,
						gxIMAGE *psrc, gxi32 flags) {

	struct GX_PARM_MIRRORIMAGE mi;
	assert(pdest);
	assert(psrc);
	mi.pdest = pdest;
	mi.psrc = psrc;
	mi.flags = flags;
	return gx_call(handle, GX_CALL_MIRRORIMAGE, &mi);
}

#ifdef __cplusplus
/******************************************************************************/
/** Mirrors an image to a specified mode.
 * @param handle Handle of the module.
 * @param pimage Pointer to an image.
 * @param flags Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and
 *              GX_MIRROR_VERTICAL (see \ref GX_MIRRORFLAGS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorimage(gxHANDLE handle, gxIMAGE *pimage, gxi32 flags) {
	return gx_mirrorimage(handle, pimage, pimage, flags);
}
#endif

/******************************************************************************/
/** Loads an image from a mass storage device and converts it to a specific
 * pixel format (Unicode version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included). The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param handle Handle of the module.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimage(gxHANDLE handle, gxIMAGE* pimage,
					const wchar_t* filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {

	struct GX_PARM_LOADIMAGE li;
	assert(pimage);
	assert(filename);
	li.pimage = pimage;
	li.filename = filename;
	li.format = pixelformat;
	return gx_call(handle, GX_CALL_LOADIMAGE, (void *)&li);
}

/******************************************************************************/
/** Loads an image from a mass storage device and converts it to a specific
 * pixel format (ASCII version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included). The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimagea(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param handle Handle of the module.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimagea(gxHANDLE handle, gxIMAGE* pimage,
						const char* filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {
	struct GX_PARM_LOADIMAGEA li;
	assert(pimage);
	assert(filename);
	li.pimage = pimage;
	li.filename = filename;
	li.format = pixelformat;
	return gx_call(handle, GX_CALL_LOADIMAGEA, (void *)&li);
}

#ifdef __cplusplus
/******************************************************************************/
/** Loads an image from a mass storage device and converts it to a specific
 * pixel format (ASCII version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included). The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param handle Handle of the module.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimage(gxHANDLE handle, gxIMAGE* pimage,
					const char* filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {

	return gx_loadimagea(handle, pimage, filename, pixelformat);
}
#endif

/******************************************************************************/
/** Saves an image to a mass storage device in the specific file format
 * (Unicode version).
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimage(gxHANDLE handle, gxIMAGE* pimage,
						const wchar_t* filename, gxi32 fileformat) {

	struct GX_PARM_SAVEIMAGE si;
	assert(pimage);
	assert(filename);
	si.pimage = pimage;
	si.filename = filename;
	si.fileformat = fileformat;
	return gx_call(handle, GX_CALL_SAVEIMAGE, (void *)&si);
}

/******************************************************************************/
/** Saves an image to a mass storage device in the specific file format
 * (ASCII version).
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagea(gxHANDLE handle, gxIMAGE* pimage,
						const char* filename, gxi32 fileformat) {

	struct GX_PARM_SAVEIMAGEA si;
	assert(pimage);
	assert(filename);
	si.pimage = pimage;
	si.filename = filename;
	si.fileformat = fileformat;
	return gx_call(handle, GX_CALL_SAVEIMAGEA, (void *)&si);
}

#ifdef __cplusplus
/******************************************************************************/
/** Saves an image to a mass storage device in the specific file format
 * (ASCII version).
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimage(gxHANDLE handle, gxIMAGE *pimage,
						const char *filename, gxi32 fileformat) {

	return gx_saveimagea(handle, pimage, filename, fileformat);
}
#endif

/******************************************************************************/
/** Loads an image from the memory and converts it to a specific pixel format.
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included). The format parameter of the
 * gx_loadfrommem() must be -1 for RAW images.
 *
 * @param handle Handle of the module.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param buffer Pointer to the image data.
 * @param buflen Length of image data in bytes.
 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadfrommem(gxHANDLE handle, gxIMAGE* pimage,
					const void *buffer,	gxi32 buflen, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {
	struct GX_PARM_LOADFROMMEM lm;
	assert(pimage);
	assert(buffer);
	assert(buflen > 0);
	lm.pimage = pimage;
	lm.buffer = buffer;
	lm.buflen = buflen;
	lm.format = pixelformat;
	return gx_call(handle, GX_CALL_LOADFROMMEM, (void *)&lm);
}

/******************************************************************************/
/** Saves an image in a specific file format to a specific memory area.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen Size of the memory area.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_savetomem(gxHANDLE handle, gxIMAGE* pimage,
					void **buffer, gxi32 *buflen, gxi32 fileformat) {
	struct GX_PARM_SAVETOMEM sm;
	assert(pimage);
	assert(buffer);
	assert(buflen);
	assert(*buflen >= 0);
	sm.pimage = pimage;
	sm.buffer = buffer;
	sm.buflen = buflen;
	sm.fileformat = fileformat;
	return gx_call(handle, GX_CALL_SAVETOMEM, (void *)&sm);
}

/******************************************************************************/
/** Checks if image structure is valid.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @return In case of valid image the return value is non-zero. */
inline gxi32 gx_isvalidimage(gxHANDLE handle, const gxIMAGE *pimage) {
	return gx_call(handle, GX_CALL_ISVALIDIMAGE, (void *)pimage);
}

/******************************************************************************/
#ifdef WIN32	/*(*/
/** Displays an image.
 * @param handle Handle of the module.
 * @param hdc Handle of device context.
 * @param x   X1 coordinate of display.
 * @param y   Y1 coordinate of display.
 * @param xsize Displayed horizontal size of image.
 * @param ysize Displayed vertical size of image.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_displayimage(gxHANDLE handle, HDC hdc, gxi32 x, gxi32 y,
							gxi32 xsize, gxi32 ysize, gxIMAGE *pimage) {

	struct GX_PARM_DISPLAYIMAGE di;
	assert(pimage);
	di.hdc = hdc;
	di.x = x;
	di.y = y;
	di.xsize = xsize;
	di.ysize = ysize;
	di.pimage = pimage;
	return gx_call(handle, GX_CALL_DISPLAYIMAGE, (void *)&di);
}

/******************************************************************************/
/** Copies an image to the clipboard.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imgtoclipboard(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_IMGTOCLIPBOARD, (void *)pimage);
}

/******************************************************************************/
/** Inserts an image from the clipboard.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_pasteimage(gxHANDLE handle, gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(handle, GX_CALL_PASTEIMAGE, (void *)pimage);
}
#endif	/*)*/

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Copies an image to another.
 * @param handle Handle of the module.
 * @param target Pointer to the initialized destination image.
 * @param source Pointer to the source image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_copyimage(gxHANDLE handle, gxIMAGE *target, gxIMAGE *source) {
	struct GX_PARM_COPYIMAGE cp;
	assert(target);
	assert(source);
	cp.target = target;
	cp.source = source;
	return gx_call(handle, GX_CALL_COPYIMAGE, (void *)&cp);
}

/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param handle Handle of the module.
 * @param filename Name of the file to test.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(gxHANDLE handle, const wchar_t *filename,
									gxi32 *fileformat) {

	struct GX_PARM_TESTIMAGEFILEFORMAT ti;
	assert(fileformat);
	ti.filename = filename;
	if(!gx_call(handle, GX_CALL_TESTIMAGEFILEFORMAT, (void *)&ti)) return false;
	*fileformat = ti.fileformat;
	return true;
}

/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param handle Handle of the module.
 * @param filename Name of the file to test.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformata(gxHANDLE handle, const char *filename,
									gxi32 *fileformat) {

	struct GX_PARM_TESTIMAGEFILEFORMATA ti;
	assert(fileformat);
	ti.filename = filename;
	if(!gx_call(handle, GX_CALL_TESTIMAGEFILEFORMATA, (void *)&ti)) return false;
	*fileformat = ti.fileformat;
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param handle Handle of the module.
 * @param filename Name of the file to test.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(gxHANDLE handle, const char *filename,
									gxi32 *fileformat) {
	return gx_testimagefileformata(handle, filename, fileformat);
}
#endif

/******************************************************************************/
/** Tests if a memory area contains an image file.
 *
 * @param handle Handle of the module.
 * @param buffer Pointer to the memory area.
 * @param buflen Size of the memory area.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformatmem(gxHANDLE handle, const void *buffer, gxi32 buflen,
									gxi32 *fileformat) {

	struct GX_PARM_TESTIMAGEFILEFORMATMEM ti;
	assert(fileformat);
	ti.buffer = buffer;
	ti.buflen = buflen;
	if(!gx_call(handle, GX_CALL_TESTIMAGEFILEFORMATMEM, (void *)&ti)) return false;
	*fileformat = ti.fileformat;
	return true;
}

/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param handle Handle of the module.
 * @param filename Name of the file to test.
 * @param formatid Buffer for the formatid. "" is returned for unknown file type.
 * @param slen Buffer length for formatid.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformatid(gxHANDLE handle, const wchar_t *filename,
									wchar_t *formatid, gxi32 slen) {

	struct GX_PARM_TESTIMAGEFILEFORMATID ti;
	assert(formatid);
	ti.filename = filename;
	ti.formatid = formatid;
	ti.slen = slen;
	if(!gx_call(handle, GX_CALL_TESTIMAGEFILEFORMATID, (void *)&ti)) return false;
	return true;
}

/******************************************************************************/
/** Tests if a memory area contains an image file.
 *
 * @param handle Handle of the module.
 * @param buffer Pointer to the memory area.
 * @param buflen Size of the memory area.
 * @param formatid Buffer for the formatid. "" is returned for unknown file type.
 * @param slen Buffer length for formatid.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformatidmem(gxHANDLE handle, const void *buffer, gxi32 buflen,
									wchar_t *formatid, gxi32 slen) {

	struct GX_PARM_TESTIMAGEFILEFORMATIDMEM ti;
	assert(formatid);
	ti.buffer = buffer;
	ti.buflen = buflen;
	ti.formatid = formatid;
	ti.slen = slen;
	if(!gx_call(handle, GX_CALL_TESTIMAGEFILEFORMATIDMEM, (void *)&ti)) return false;
	return true;
}

#ifdef __cplusplus
/******************************************************************************/
/** Tests if a memory area contains an image file.
 *
 * @param handle Handle of the module.
 * @param buffer Pointer to the memory area.
 * @param buflen Size of the memory area.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(gxHANDLE handle, const void *buffer, gxi32 buflen,
									gxi32 *fileformat) {
	return gx_testimagefileformatmem(handle, buffer, buflen, fileformat);
}
#endif

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_variant
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Embedds an image into a variant.
 * @param handle	Handle of the module.
 * @param source	Pointer to the source image.
 * @param varid		The id for the created variant.
 * @param target	Pointer to the initialized destination variant.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imagetovariant(gxHANDLE handle, gxIMAGE *source, gxi32 varid, gxVARIANT *target) {
	struct GX_PARM_IMAGETOVARIANT itv;
	gxi32 ret;
	assert(target);
	assert(source);
	itv.pimage = source;
	itv.varid = varid;
	ret = gx_call(handle, GX_CALL_IMAGETOVARIANT, &itv);
	if(ret && target) *target = itv.variant;
	return ret;
}

/******************************************************************************/
/** Loads an embedded image from a variant.
 * @param handle	Handle of the module.
 * @param target	Pointer to the initialized destination image.
 * @param source	Variant with an embedded image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imagefromvariant(gxHANDLE handle, gxIMAGE **target, gxVARIANT source) {
	struct GX_PARM_IMAGEFROMVARIANT ifv;
	gxi32 ret;
	assert(target);
	assert(source);
	ifv.variant = source;
	ret = gx_call(handle, GX_CALL_IMAGEFROMVARIANT, &ifv);
	if(ret && target) *target = ifv.pimage;
	return ret;
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/******************************************************************************/
/** Returns the pointer of the pixel.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param x Horizontal position of the pixel.
 * @param y Vertical position of the pixel.
 * @return The pointer of the pixel or NULL if an error occurred
 * or the pixel is not found. */
inline void *gx_getpixelptr(gxHANDLE handle, gxIMAGE *pimage, gxi32 x, gxi32 y) {
	struct GX_PARM_GETPIXELPTR gp;
	assert(pimage);
	gp.pimage = pimage;
	gp.x = x;
	gp.y = y;
	if(!gx_call(handle, GX_CALL_GETPIXELPTR, (void *)&gp)) return (void *)0;
	return gp.ptr;
}

/******************************************************************************/
#ifdef __cplusplus	/*(*/
/******************************************************************************/
/** Gets size of a pixel in bytes.
 * @param size Size of the pixel format.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_getpixelsize(gxi32 *size, gxi32 format) {
	return gx_getpixelsize(gx_direct(GX_CALL_GROUP_GX_IMAGE), size, format);
}

/******************************************************************************/
/** Converts pixels to a specified format and size.
 * @param target Pointer to a pixel data to where the function stores the data.
 * @param tformat Pixel format of the target area (see \ref GX_PIXELFORMATS).
 * @param tsline Size of a row of the target area in bytes.
 * @param source Pointer to a pixel data.
 * @param sformat Pixel format of the source area (see \ref GX_PIXELFORMATS).
 * @param ssline Size of a row of the source area in bytes.
 * @param xsize Horizontal size of the pixel area.
 * @param ysize Vertical size of the pixel area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_convertpixels(void *target, gxi32 tformat, gxi32 tsline,
					const void *source, gxi32 sformat, gxi32 ssline,
					gxi32 xsize, gxi32 ysize) {

	return gx_convertpixels(gx_direct(GX_CALL_GROUP_GX_IMAGE),
					target, tformat, tsline,
					source, sformat, ssline, xsize, ysize);
}

/******************************************************************************/
/** Fast converts pixels to a specified format and size.
 *
 * The function is the same as gx_convertpixels(), only it works same memory area.
 * \par
 * The fast reconvert function can be used for converting:
 * - RGB555,BGR555,RGB565,BGR565 \<-\> RGB555,BGR555,RGB565,BGR565
 * - RGB,BGR \<-\> RGB,BGR
 * - RGBA,BGRA \<-\> RGBA,BGRA
 * - RGB12,BGR12 \<-\> RGB12,BGR12
 * @param pixels Pointer to a pixel data.
 * @param tformat Pixel format of the destination image (see \ref GX_PIXELFORMATS).
 * @param sformat Pixel format of the source image (see \ref GX_PIXELFORMATS).
 * @param sline Size of a row of the pixel area in bytes.
 * @param xsize Horizontal size of the pixel area.
 * @param ysize Vertical size of the pixel area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_fastreconvert(void *pixels, gxi32 tformat, gxi32 sformat,
						gxi32 sline, gxi32 xsize, gxi32 ysize) {

	return gx_fastreconvert(gx_direct(GX_CALL_GROUP_GX_IMAGE),
					pixels, tformat, sformat,
					sline, xsize, ysize);
}

/******************************************************************************/
/** Zooms pixels to a specified size.
 * @param target Pointer to an allocated area where the zoom function places the
 *               converted image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param sx1_8  Left coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sy1_8  Top coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sx2_8  Right coordinate of zoom area (shifted left with 8 bit = 256)
 * @param sy2_8  Bottom coordinate of zoom area (shifted left with 8 bit = 256)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_zoompixels(void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format,
						gxi32 sx1_8 = 0, gxi32 sy1_8 = 0,
						gxi32 sx2_8 = 0, gxi32 sy2_8 = 0) {

	return gx_zoompixels(gx_direct(GX_CALL_GROUP_GX_IMAGE),
					target, tsline, txsize, tysize,
					source, ssline, sxsize, sysize, format,
					sx1_8, sy1_8, sx2_8, sy2_8);
}

/******************************************************************************/
/** Rotates pixels to a specified degree.
 * @param target Pointer to an allocated area where the rotate function places
 *               the rotated image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param degree Degree (Must be 0, 90, 180, 270).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_rotatepixels(void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format, gxi32 degree) {

	return gx_rotatepixels(gx_direct(GX_CALL_GROUP_GX_IMAGE),
						target, tsline, txsize, tysize,
						source, ssline, sxsize, sysize,
						format, degree);
}

/******************************************************************************/
/** Mirrors pixels to a specified mode.
 * @param target Pointer to an allocated area where the mirror function places
 *               the mirrored image.
 * @param tsline Size of a row of the destination area.
 * @param txsize Horizontal size of the destination area.
 * @param tysize Vertical size of the destination area.
 * @param source Pointer to pixels of source area.
 * @param ssline Size of a row of the source area.
 * @param sxsize Horizontal size of the source area.
 * @param sysize Vertical size of the source area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param flags  Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL.
 *               (see \ref GX_MIRRORFLAGS)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorpixels(void *target, gxi32 tsline, gxi32 txsize, gxi32 tysize,
						const void *source, gxi32 ssline, gxi32 sxsize, gxi32 sysize,
						gxi32 format, gxi32 flags) {

	return gx_mirrorpixels(gx_direct(GX_CALL_GROUP_GX_IMAGE),
						target, tsline, txsize, tysize,
						source, ssline, sxsize, sysize,
						format, flags);
}

/******************************************************************************/
/** Mirrors pixels to a specified mode.
 * @param pixels Pointer to pixels of the pixel area.
 * @param sline  Size of a row of the pixel area.
 * @param xsize  Horizontal size of the pixel area.
 * @param ysize  Vertical size of the pixel area.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param flags  Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and GX_MIRROR_VERTICAL.
 *               (see \ref GX_MIRRORFLAGS)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorpixels(void *pixels, gxi32 sline, gxi32 xsize, gxi32 ysize,
						gxi32 format, gxi32 flags) {

	return gx_mirrorpixels(pixels, sline, xsize, ysize,
						pixels, sline, xsize, ysize,
						format, flags);
}

/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Initialization of an image located on a heap or a stack.
 *
 * This function fills the structure identifier and the reference
 * counter properly. The other data members are set to zero value.
 * \warning Do not call it for a dynamic allocated image (gx_allocimage)!
 * @param pimage Pointer to the ininitialized image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_initimage(gxIMAGE *pimage) {
	return gx_initimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
/** This function allocates a blank image.
 *
 * The structure identifier and the reference counter will be properly filled.
 * The other data members are set zero value.
 * @param pimage Pointer to a \a gxIMAGE structure pointer where the function
 *               returns the pointer of the allocated image area.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_allocimage(gxIMAGE **pimage) {
	return gx_allocimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
/** Frees an image structure including the allocated pixel data.
 *
 * If the value of the reference counter is not properly set the function returns an
 * error. In case of dynamically allocated images it is advised to use
 * \a gx_unrefimage.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_freeimage(gxIMAGE *pimage) {
	return gx_freeimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_reference
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Increases the image reference counter.
 *
 * The counter indicates the number of processes using the image. The counter
 * can rise to positive or negative direction as well depending on whether the image
 * is static or dynamic.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_refimage(gxIMAGE *pimage) {
	return gx_refimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
/** Decreases the image reference counter.
 *
 * The counter indicates the number of processes using the image. In case of
 * the counter value becomes zero after the function call the structure will be
 * freed depending on whether the image was allocated statically or dynamically.
 * @param pimage Pointer to the image structure.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_unrefimage(gxIMAGE *pimage) {
	return gx_unrefimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Makes an image with proper size and format running on an initialized image
 * structure.
 * @param pimage Pointer to the image structure.
 * @param format Pixel format (see \ref GX_PIXELFORMATS).
 * @param xsize Horizontal size of image in pixels.
 * @param ysize Vertical size of image in pixels.
 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
 *         bytes). If zero the system computes the correct value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_createimage(gxIMAGE* pimage, gxi32 format,
							gxi32 xsize, gxi32 ysize, gxi32 sline) {
	return gx_createimage(gx_direct(GX_CALL_GROUP_GX_IMAGE),
						  pimage, format, xsize, ysize, sline);
}

/******************************************************************************/
/** Converts an image to a specific format and size. The destination image must
 * be initialized.
 * @param pdest Pointer to an initialized image where the function places the
 *              converted image.
 * @param psrc Pointer to the source image.
 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
 * @param xsize Horizontal size of the destination image in pixels.
 * @param ysize Vertical size of the destination image in pixels.
 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
 *         bytes). If zero the system computes the correct value.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_convertimage(gxIMAGE* pdest, gxIMAGE* psrc,
						gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline) {

	return gx_convertimage(gx_direct(GX_CALL_GROUP_GX_IMAGE),
						pdest, psrc, format, xsize, ysize, sline);
}

/******************************************************************************/
/** Zooms an image to a specified size.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param xsize Horizontal size of the destination area.
 * @param ysize Vertical size of the destination area.
 * @param sline Size of a row of the destination area.
 * @param psrc  Pointer to the source image.
 * @param sx1_8 Left coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sy1_8 Top coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sx2_8 Right coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @param sy2_8 Bottom coordinate of the zoomed area (shifted left with 8 bit = 256)
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_zoomimage(gxIMAGE *pdest,
					gxi32 xsize, gxi32 ysize, gxi32 sline,
					gxIMAGE *psrc,
					gxi32 sx1_8 = 0, gxi32 sy1_8 = 0,
					gxi32 sx2_8 = 0, gxi32 sy2_8 = 0) {

	return gx_zoomimage(gx_direct(GX_CALL_GROUP_GX_IMAGE),
					pdest, xsize, ysize, sline,
					psrc, sx1_8, sy1_8, sx2_8, sy2_8);
}

/******************************************************************************/
/** Rotates an image to a specified degree.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param psrc  Pointer to the source image.
 * @param degree Degree (Must be 0, 90, 180, 270).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_rotateimage(gxIMAGE *pdest, gxIMAGE *psrc, gxi32 degree) {
	return gx_rotateimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pdest, psrc, degree);
}

/******************************************************************************/
/** Mirrors an image to a specified mode.
 * @param pdest Pointer to an initialized image where the function places the
 *              zoomed image.
 * @param psrc  Pointer to the source image.
 * @param flags Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and
 *              GX_MIRROR_VERTICAL (see \ref GX_MIRRORFLAGS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorimage(gxIMAGE *pdest, gxIMAGE *psrc, gxi32 flags) {
	return gx_mirrorimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pdest, psrc, flags);
}

/******************************************************************************/
/** Mirrors an image to a specified mode.
 * @param pimage Pointer to an image.
 * @param flags Mirror flags. It can be GX_MIRROR_HORIZONTAL or/and
 *              GX_MIRROR_VERTICAL (see \ref GX_MIRRORFLAGS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_mirrorimage(gxIMAGE *pimage, gxi32 flags) {
	return gx_mirrorimage(pimage, pimage, flags);
}

/******************************************************************************/
/** Loads an image from a mass storage device and converts it to a specific
 * pixel format (Unicode version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimage(gxIMAGE* pimage, const wchar_t* filename,
						gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {

	return gx_loadimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage,
					filename, pixelformat);
}

/******************************************************************************/
/** Loads an image from a mass storage device and converts it to a specific
 * pixel format (ASCII version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimage(gxIMAGE* pimage, const char* filename,
						gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {

	return gx_loadimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage,
					filename, pixelformat);
}

/******************************************************************************/
/** Saves an image to a mass storage device in the specific file format
 * (Unicode version).
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimage(gxIMAGE* pimage,
						const wchar_t* filename, gxi32 fileformat) {

	return gx_saveimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage, filename, fileformat);
}

/******************************************************************************/
/** Saves an image to a mass storage device in the specific file format
 * (ASCII version).
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimage(gxIMAGE* pimage,
						const char* filename, gxi32 fileformat) {

	return gx_saveimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage, filename, fileformat);
}

/******************************************************************************/
/** Loads an image from the memory and converts it to a specific pixel format.
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadfrommem() must be -1 for RAW images.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param buffer Pointer to the image data.
 * @param buflen Length of image data in bytes.
 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadfrommem(gxIMAGE* pimage,
					const void *buffer,	gxi32 buflen, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) {

	return gx_loadfrommem(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage, buffer,
						buflen, pixelformat);
}

/******************************************************************************/
/** Saves an image in a specific file format to a specific memory area.
 * @param pimage Pointer to the image.
 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen Size of the memory area.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_savetomem(gxIMAGE* pimage,
					void **buffer, gxi32 *buflen, gxi32 fileformat) {

	return gx_savetomem(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage, buffer, buflen, fileformat);
}

/******************************************************************************/
/** Checks if image structure is valid.
 * @param pimage Pointer to the image.
 * @return In case of valid image the return value is non-zero. */
inline gxi32 gx_isvalidimage(const gxIMAGE *pimage) {

	return gx_isvalidimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage);
}

/******************************************************************************/
#ifdef WIN32	/*(*/
/** Displays an image.
 * @param hdc Handle of device context.
 * @param x   X1 coordinate of display.
 * @param y   Y1 coordinate of display.
 * @param xsize Displayed horizontal size of image.
 * @param ysize Displayed vertical size of image.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_displayimage(HDC hdc, gxi32 x, gxi32 y,
							gxi32 xsize, gxi32 ysize, gxIMAGE *pimage) {

	return gx_displayimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), hdc, x, y, xsize, ysize, pimage);
}

/******************************************************************************/
/** Copies an image to the clipboard.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imgtoclipboard(gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_IMGTOCLIPBOARD, (void *)pimage);
}

/******************************************************************************/
/** Inserts an image from the clipboard.
 * @param pimage Pointer to the image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_pasteimage(gxIMAGE *pimage) {
	assert(pimage);
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_PASTEIMAGE, (void *)pimage);
}
#endif	/*)*/

/******************************************************************************/
/** Copies an image to another.
 * @param target Pointer to the initialized destination image.
 * @param source Pointer to the source image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_copyimage(gxIMAGE *target, gxIMAGE *source) {
	return gx_copyimage(gx_direct(GX_CALL_GROUP_GX_IMAGE), target, source);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_variant
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Embedds an image into a variant.
 * @param source	Pointer to the source image.
 * @param varid		The id for the created variant.
 * @param target	Pointer to the initialized destination variant.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imagetovariant(gxIMAGE *source, gxi32 varid, gxVARIANT *target) {
	return gx_imagetovariant(gx_direct(GX_CALL_GROUP_GX_IMAGE), source, varid, target);
}

/******************************************************************************/
/** Loads an embedded image from a variant.
 * @param target	Pointer to the initialized destination image.
 * @param source	Variant with an embedded image.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_imagefromvariant(gxIMAGE **target, gxVARIANT source) {
	return gx_imagefromvariant(gx_direct(GX_CALL_GROUP_GX_IMAGE), target, source);
}

/******************************************************************************/
/** @} */
/******************************************************************************/
/** \addtogroup gx_group_image
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Loads an image with comments from a mass storage device and converts it to
 * a specific pixel format (Unicode version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @param properties Properties for the image loader. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimagefromfile(gxIMAGE* pimage, const wchar_t* filename,
						gxi32 pixelformat GX_DEFARG(GX_UNDEF),
						gxVARIANT properties GX_DEFARG(0),
						gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_LOADIMAGEFROMFILE li;
	assert(pimage);
	assert(filename);
	li.pimage = pimage;
	li.filename = filename;
	li.format = pixelformat;
	li.properties = properties;
	li.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_LOADIMAGEFROMFILE, (void *)&li);
}

/******************************************************************************/
/** Loads an image with comments from a mass storage device and converts it to
 * a specific pixel format (ASCII version).
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 *
 * \code
   gxIMAGE image;
   gx_initimage(&image);
   gx_createimage(&image, GX_GRAY, 1024, 768, 1024);
   gx_loadimage(&image, "test.raw", -1);
   ...
   \endcode
 *
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param filename Name of the image file.
 * @param pixelformat The specific pixel format.  Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @param properties Properties for the image loader. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimagefromfile(gxIMAGE* pimage, const char* filename,
						gxi32 pixelformat GX_DEFARG(GX_UNDEF),
						gxVARIANT properties GX_DEFARG(0),
						gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_LOADIMAGEFROMFILEA li;
	assert(pimage);
	assert(filename);
	li.pimage = pimage;
	li.filename = filename;
	li.format = pixelformat;
	li.properties = properties;
	li.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_LOADIMAGEFROMFILEA, (void *)&li);
}

/******************************************************************************/
/** Saves an image with comments to a mass storage device in the specific file
 * format (Unicode version).
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @param properties Properties for the image writer. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagetofile(gxIMAGE* pimage,
						const wchar_t* filename, gxi32 fileformat,
						gxVARIANT properties GX_DEFARG(0),
						gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_SAVEIMAGETOFILE si;
	assert(pimage);
	assert(filename);
	si.pimage = pimage;
	si.filename = filename;
	si.fileformat = fileformat;
	si.properties = properties;
	si.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_SAVEIMAGETOFILE, (void *)&si);
}

/******************************************************************************/
/** Saves an image with comments to a mass storage device in the specific file
 * format (ASCII version).
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @param properties Properties for the image writer. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagetofile(gxIMAGE* pimage,
						const char* filename, gxi32 fileformat,
						gxVARIANT properties GX_DEFARG(0),
						gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_SAVEIMAGETOFILEA si;
	assert(pimage);
	assert(filename);
	si.pimage = pimage;
	si.filename = filename;
	si.fileformat = fileformat;
	si.properties = properties;
	si.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_SAVEIMAGETOFILEA, (void *)&si);
}

/******************************************************************************/
/** Saves an image with comments to a mass storage device in the specific file
 * format (Unicode version).
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param filename Name of the image file.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @param properties Properties for the image writer. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagetofile2(gxHANDLE handle, gxIMAGE* pimage,
						const wchar_t* filename, const wchar_t* fileformat,
						gxVARIANT properties GX_DEFARG(0),
						gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_SAVEIMAGETOFILE2 si;
	assert(pimage);
	assert(filename);
	si.pimage = pimage;
	si.filename = filename;
	si.fileformat = fileformat;
	si.properties = properties;
	si.comments = comments;
	return gx_call(handle, GX_CALL_SAVEIMAGETOFILE2, (void *)&si);
}

/******************************************************************************/
/** Loads an image with comments from the memory and converts it to a specific
 * pixel format.
 *
 * On loading a RAW image, the gxIMAGE must be created with correct
 * parameters (sline parameter also included).  The format parameter of the
 * gx_loadimage() must be -1 for RAW images.
 * @param pimage Pointer to an initialized image structure where the function
 *               loads the data.
 * @param buffer Pointer to the image data.
 * @param buflen Length of image data in bytes.
 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
 *               image to grayscale (see \ref GX_PIXELFORMATS).
 * @param properties Properties for the image loader. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_loadimagefrommem(gxIMAGE* pimage,
					const void *buffer,	gxi32 buflen, gxi32 pixelformat GX_DEFARG(GX_UNDEF),
					gxVARIANT properties GX_DEFARG(0),
					gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_LOADIMAGEFROMMEM li;
	assert(pimage);
	li.pimage = pimage;
	li.buffer = buffer;
	li.buflen = buflen;
	li.format = pixelformat;
	li.properties = properties;
	li.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_LOADIMAGEFROMMEM, (void *)&li);
}

/******************************************************************************/
/** Saves an image with comments in a specific file format to a specific memory
 * area.
 * @param pimage Pointer to the image.
 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen Size of the memory area.
 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
 * @param properties Properties for the image writer. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagetomem(gxIMAGE* pimage,
					void **buffer, gxi32 *buflen, gxi32 fileformat,
					gxVARIANT properties GX_DEFARG(0),
					gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_SAVEIMAGETOMEM si;
	assert(pimage);
	si.pimage = pimage;
	si.buffer = buffer;
	si.buflen = buflen;
	si.fileformat = fileformat;
	si.properties = properties;
	si.comments = comments;
	return gx_call(gx_direct(GX_CALL_GROUP_GX_IMAGE), GX_CALL_SAVEIMAGETOMEM, (void *)&si);
}

/******************************************************************************/
/** Saves an image with comments in a specific file format to a specific memory
 * area.
 * @param handle Handle of the module.
 * @param pimage Pointer to the image.
 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
 * @param buflen Size of the memory area.
 * @param fileformat Format of the image file.
 * @param properties Properties for the image writer. It can be NULL.
 * @param comments Comments of the image. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_saveimagetomem2(gxHANDLE handle, gxIMAGE* pimage,
					void **buffer, gxi32 *buflen, wchar_t* fileformat,
					gxVARIANT properties GX_DEFARG(0),
					gxVARIANT comments GX_DEFARG(0)) {

	struct GX_PARM_SAVEIMAGETOMEM2 si;
	assert(pimage);
	si.pimage = pimage;
	si.buffer = buffer;
	si.buflen = buflen;
	si.fileformat = fileformat;
	si.properties = properties;
	si.comments = comments;
	return gx_call(handle, GX_CALL_SAVEIMAGETOMEM2, (void *)&si);
}

/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param filename Name of the file to test.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(const wchar_t *filename, gxi32 *fileformat) {

	return gx_testimagefileformat(gx_direct(GX_CALL_GROUP_GX_IMAGE), filename, fileformat);
}

/******************************************************************************/
/** Tests if a file is an image file.
 *
 * @param filename Name of the file to test.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(const char *filename, gxi32 *fileformat) {

	return gx_testimagefileformat(gx_direct(GX_CALL_GROUP_GX_IMAGE), filename, fileformat);
}

/******************************************************************************/
/** Tests if a memory area contains an image file.
 *
 * @param buffer Pointer to the memory area.
 * @param buflen Size of the memory area.
 * @param fileformat Buffer for the fileformat. -1 is returned for unknown file type.
 * @return On error false is returned and the error code/string in the GX system
 *         is set appropriately ( see gx_geterror() ). */
inline gxi32 gx_testimagefileformat(const void *buffer, gxi32 buflen, gxi32 *fileformat) {

	return gx_testimagefileformat(gx_direct(GX_CALL_GROUP_GX_IMAGE), buffer, buflen, fileformat);
}

/******************************************************************************/
/** @} */
/******************************************************************************/

/******************************************************************************/
/** Returns the pointer of the pixel.
 * @param pimage Pointer to the image.
 * @param x Horizontal position of the pixel.
 * @param y Vertical position of the pixel.
 * @return The pointer of the pixel or NULL if an error occurred
 * or the pixel is not found. */
inline void *gx_getpixelptr(gxIMAGE *pimage, gxi32 x, gxi32 y) {
	return gx_getpixelptr(gx_direct(GX_CALL_GROUP_GX_IMAGE), pimage, x, y);
}

/******************************************************************************/
#endif	/*)*/
#endif	/*)*/

#ifdef GX_DOTNET
  #pragma managed
#endif

/******************************************************************************/
#if !defined(NO_GX_CLASSES)	/*(*/

#ifndef GX_EXT_MODULE	/*(*/

/******************************************************************************/
/** Class for the IMAGE data and some low-level functions.
 * \see gxImage
 */
GX_CLASS gxImageData
#ifdef GX_DOTNET
: public System::IDisposable
#endif
{

#if !defined(GX_SWIGIF) /*(*/

#if !defined(GX_DOTNET) && !defined(GX_MANUAL)
public:
	GX_INDIRECTION_NOGC(gxIMAGE) _image;
#endif

#if defined(GX_DOTNET)
#if !defined(GX_MANUAL)
private:
	GX_INDIRECTION_NOGC(gxIMAGE) _image;	/* Pointer to the allocated gxIMAGE structure. */
#endif

public:
	/** Returns the local image data pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxOutPtr _get_image(void) GX_CONST {
		return GX_PUTPTR(_image);
	}
	/** Modifies the local image data pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
	inline void _set_image(gxInPtr ptr) {
		_image = (GX_INDIRECTION_NOGC(gxIMAGE))ptr.ToPointer();
	}
#endif

#endif	/*)*/

public:
	/** Class initialization. */
	inline gxImageData() {
		_image = (GX_INDIRECTION_NOGC(gxIMAGE))GX_NULLPTR;
	}
	/** Class termination. */
	inline ~gxImageData() gxFuncThrowsError {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxImageData() gxFuncThrowsError {
		_Dispose();
	}
#else
	/** It disposes the class. */
	inline void Dispose(void) gxFuncThrowsError {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);//do not call it from a destructor explicitly!
#endif
		_Dispose();
		/** no base class */
	}
#endif

private:
	inline void _Dispose(void) {
		gxassert(!_image || (_image->ref == 0));
	}
public:


	/** It returns the reference pointer. @see gxIMAGE, gx_refimage, gx_unrefimage
	 * @return Reference pointer of the gxIMAGE structure */
	inline gxi32 ref(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->ref;
	}
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** It returns the pointer to the image pixels. @see gxIMAGE
	 * @return Pointer to the image pixels. */
	inline void *image(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->image;
	}
#endif
	/** It returns the size of the image in bytes. @see gxIMAGE
	 * @return Size of the image in bytes. */
	inline gxi32 simage(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->simage;
	}
	/** It returns the pixel format of the image. @see gxIMAGE
	 * @return Pixel format of the image (see \ref GX_PIXELFORMATS). */
	inline gxi32 format(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->format;
	}
	/** It returns the horizontal size of the image in pixels. @see gxIMAGE
	 * @return Horizontal size of the image in pixels. */
	inline gxi32 xsize(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->xsize;
	}
	/** It returns the vertical size of the image in pixels. @see gxIMAGE
	 * @return Vertical size of the image in pixels. */
	inline gxi32 ysize(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->ysize;
	}
	/** It returns the size of a row in bytes. @see gxIMAGE
	 * @return Size of a row in bytes. */
	inline gxi32 sline(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->sline;
	}
	/** It returns the horizontal resolution of the image. @see gxIMAGE
	 * @return Horizontal resolution of the image. */
	inline gxi32 xres(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->xres;
	}
	/** It returns the vertical resolution of the image. @see gxIMAGE
	 * @return Vertical resolution of the image. */
	inline gxi32 yres(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->yres;
	}
	/** The function sets the horizontal resolution of the image. @see gxIMAGE
	 *
	 * @param _xres	Value to set. */
	inline void xres(gxi32 _xres) gxFuncThrowsError {
		gxassert(_image);
		_image->xres = _xres;
	}
	/** The function sets the vertical resolution of the image. @see gxIMAGE
	 *
	 * @param _yres	Value to set. */
	inline void yres(gxi32 _yres) gxFuncThrowsError {
		gxassert(_image);
		_image->yres = _yres;
	}

	/** It returns the reference pointer. @see gxIMAGE, gx_refimage, gx_unrefimage
	 * @return Reference pointer of the gxIMAGE structure */
	inline gxi32 GetRef(void) GX_CONST gxFuncThrowsError {
		return ref();
	}

	/** It returns the pointer to the image pixels. @see gxIMAGE
	 * @return Pointer to the image pixels. */
#if defined(GX_DOTNET)
	inline gxOutData GetPixels(void) GX_CONST gxFuncThrowsError {
		return GX_PUTDATA(_image->image, _image->simage);
	}
#elif defined(GX_SWIG)
	inline gxOutData GetPixels(void) GX_CONST gxFuncThrowsError {
		return GX_PUTDATA(image(), simage());
	}
#else
	inline void *GetPixels(void) GX_CONST gxFuncThrowsError {
		return image();
	}
#endif

	/** It returns size of the image in bytes. @see gxIMAGE
	 * @return Size of the image in bytes. */
	inline gxi32 GetSImage(void) GX_CONST gxFuncThrowsError {
		return simage();
	}
	/** It returns the pixel format of the image. @see gxIMAGE
	 * @return Pixel format of the image (see \ref GX_PIXELFORMATS). */
	inline gxi32 GetPixelFormat(void) GX_CONST gxFuncThrowsError {
		return format();
	}
	/** It returns the horizontal size of the image in pixels. @see gxIMAGE
	 * @return Horizontal size of the image in pixels. */
	inline gxi32 GetXSize(void) GX_CONST gxFuncThrowsError {
		return xsize();
	}
	/** It returns the vertical size of the image in pixels. @see gxIMAGE
	 * @return Vertical size of the image in pixels. */
	inline gxi32 GetYSize(void) GX_CONST gxFuncThrowsError {
		return ysize();
	}
	/** It returns the size of a row in bytes. @see gxIMAGE
	 * @return Size of a row in bytes. */
	inline gxi32 GetSLine(void) GX_CONST gxFuncThrowsError {
		return sline();
	}
	/** It returns the horizontal resolution of the image. @see gxIMAGE
	 * @return Horizontal resolution of the image. */
	inline gxi32 GetXRes(void) GX_CONST gxFuncThrowsError {
		return xres();
	}
	/** It returns the vertical resolution of the image. @see gxIMAGE
	 * @return Vertical resolution of the image. */
	inline gxi32 GetYRes(void) GX_CONST gxFuncThrowsError {
		return yres();
	}
	/** The function sets the horizontal resolution of the image. @see gxIMAGE
	 *
	 * @param _xres	Value to set.
	 * @return The function always returns true. */
	inline bool SetXRes(gxi32 _xres) gxFuncThrowsError {
		xres(_xres);
		return true;
	}
	/** The function sets the vertical resolution of the image. @see gxIMAGE
	 *
	 * @param _yres	Value to set.
	 * @return The function always returns true. */
	inline bool SetYRes(gxi32 _yres) gxFuncThrowsError {
		yres(_yres);
		return true;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Returns a pointer to the gxIMAGE structure.
     * @return Pointer to the gxIMAGE structure. */
	inline operator gxIMAGE *() GX_CONST {
		return _image;
	}
	/** Returns a reference to the gxIMAGE structure.
     * @return Reference to the gxIMAGE structure. */
	inline operator gxIMAGE &() GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return *_image;
	}
#endif
};

/******************************************************************************/
/** Class for the IMAGE functions. */
GX_CLASS gxImageHandler : public gxHandle
{
public:
	/** Class initialization with default properties. */
	inline gxImageHandler() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gximage", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gximage", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Class initialization with another image handler.
	 * @param src Pointer to another image handler. The reference of
	 *		this image handle will be increased. */
	inline gxImageHandler(const gxHANDLE *src) gxFuncThrowsError : gxHandle() {
		if(src) {
			handle = src->handle;
			if(!gx_refhandle(*this)) gxthrow;
		}
	}
	/** Class initialization with another image handle.
	 * @param src Source image handle. The reference of this
	 *		image handle will be increased. */
	inline gxImageHandler(const gxHANDLE &src) gxFuncThrowsError : gxHandle() {
		handle = src.handle;
		if(!gx_refhandle(*this)) gxthrow;
	}

	/** Class initialization with the place of the properties and name of the module
	 * (Unicode version).
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImageHandler(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError {

		if(!gx_openmodule(this, modname ? modname : L"gximage", propname)) gxthrow;
	}

	/** Class initialization with the place of the properties and name of the module
	 * (ASCII version).
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImageHandler(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError {

		if(!gx_openmodulea(this, modname ? modname : "gximage", propname)) gxthrow;
	}
#endif	/* GX_SWIGIF GX_DOTNET )*/

#ifdef GX_UNICODE	/*(*/
	/** Class initialization with place of the properties and name of the module.
	 * (Unicode version)
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImageHandler(gxInStr propname, gxInStr modname) gxFuncThrowsError {
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
	/** Class initialization with place of the properties.
	 * (Unicode version)
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxImageHandler(gxInStr propname) gxFuncThrowsError {
		GX_GETSTRING(_propname, propname);
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gximage", _propname)) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gximage", _propname)) gxthrow;
		_set_handle(h.handle);
#endif
	}
#endif	/* GX_UNICODE )*/

#ifdef GX_ASCII
	/** Class initialization with place of the properties and name of the module.
	 * (ASCII version)
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImageHandler(gxInAStr propname, gxInAStr modname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		GX_GETASTRING(_modname, modname);
		if(!gx_openmodulea(this, _modname, _propname)) gxthrow;
	}
	/** Class initialization with place of the properties (ASCII version).
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxImageHandler(gxInAStr propname) gxFuncThrowsError {
		GX_GETASTRING(_propname, propname);
		if(!gx_openmodulea(this, "gximage", _propname)) gxthrow;
	}
#endif

	/** Class initalization with another image handle.
	 * @param src Source image handle. The reference of this
	 *		image handle will be increased. */
	inline gxImageHandler(GX_CONST gxImageHandler GX_REF_CLASS(src)) gxFuncThrowsError : gxHandle() {
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

#endif	/* GX_EXT_MODULE )*/
/******************************************************************************/
#if !defined(GX_MANUAL)
#if !defined(GX_DOTNET)
  #define GX_GETIMAGE(name)			gxIMAGE *name = _image
  #define GX_GETIMAGE2(name,src)	gxIMAGE *name = (src)._image
#else
  #define GX_GETIMAGE(name)			gxIMAGE *name = (gxIMAGE *)_get_image().ToPointer()
  #define GX_GETIMAGE2(name,src)	gxIMAGE *name = (gxIMAGE *)((src) GX_M _get_image().ToPointer())
#endif
#endif

/******************************************************************************/

#ifndef GX_EXT_MODULE	/*(*/
/******************************************************************************/
/******************************************************************************/
/** Class for the IMAGE functions. */
#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
class gxImage : public gxImageHandler, public gxImageData {
#else	/*)(*/
GX_CLASS gxImage : public gxImageHandler
#ifdef GX_DOTNET
, public System::IDisposable
#endif
{

#if !defined(GX_SWIGIF) /*(*/

#if !defined(GX_DOTNET) && !defined(GX_MANUAL)
public:
	GX_INDIRECTION_NOGC(gxIMAGE) _image;	/* Pointer to the allocated gxIMAGE structure. */
#endif

#if defined(GX_DOTNET)
#if !defined(GX_MANUAL)
private:
	GX_INDIRECTION_NOGC(gxIMAGE) _image;	/* Pointer to the allocated gxIMAGE structure. */
#endif

public:
	/** Returns the local image pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxOutPtr _get_image(void) GX_CONST {
		return GX_PUTPTR(_image);
	}
	/** Modifies the local image pointer.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
	inline void _set_image(gxInPtr ptr) {
		_image = (GX_INDIRECTION_NOGC(gxIMAGE))GX_GETPTR(ptr);
	}
	/** Modifies the local image pointer.
		 * @param ptr	New value. */
private:
	inline void _set_image(GX_INDIRECTION_NOGC(gxIMAGE) ptr) {
		_image = ptr;
	}
public:
#endif
#endif /*)*/

public:
	/** Returns the reference pointer. @see gxIMAGE, gx_refimage, gx_unrefimage
	 * @return Reference pointer of the gxIMAGE structure */
	inline gxi32 ref(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->ref;
	}

	/** Returns the size of the image in bytes. @see gxIMAGE
	 * @return Size of the image in bytes. */
	inline gxi32 simage(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->simage;
	}
	/** Returns the pixel format of the image. @see gxIMAGE
	 * @return Pixel format of the image (see \ref GX_PIXELFORMATS). */
	inline gxi32 format(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->format;
	}
	/** Returns the horizontal size of the image in pixels. @see gxIMAGE
	 * @return Horizontal size of the image in pixels. */
	inline gxi32 xsize(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->xsize;
	}
	/** Returns the vertical size of the image in pixels. @see gxIMAGE
	 * @return Vertical size of the image in pixels. */
	inline gxi32 ysize(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->ysize;
	}
	/** Returns the size of a row in bytes. @see gxIMAGE
	 * @return Size of a row in bytes. */
	inline gxi32 sline(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->sline;
	}
	/** Returns the horizontal resolution of the image. @see gxIMAGE
	 * @return Horizontal resolution of the image. */
	inline gxi32 xres(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->xres;
	}
	/** Returns the vertical resolution of the image. @see gxIMAGE
	 * @return Vertical resolution of the image. */
	inline gxi32 yres(void) GX_CONST gxFuncThrowsError {
		gxassert(_image);
		return _image->yres;
	}
	/** Sets the horizontal resolution of the image. @see gxIMAGE
	 * @param _xres Horizontal resolution to set.*/
	inline void xres(gxi32 _xres) gxFuncThrowsError {
		gxassert(_image);
		_image->xres = _xres;
	}
	/** Sets the vertical resolution of the image. @see gxIMAGE
	 * @param _yres Vertical resolution to set.*/
	inline void yres(gxi32 _yres) gxFuncThrowsError {
		gxassert(_image);
		_image->yres = _yres;
	}

	/** Returns the reference pointer. @see gxIMAGE, gx_refimage, gx_unrefimage
	 * @return Reference pointer of the gxIMAGE structure */
	inline gxi32 GetRef(void) GX_CONST gxFuncThrowsError {
		return ref();
	}

	/** Returns the pointer to the image pixels. @see gxIMAGE
	 * @return Pointer to the image pixels. */
#if defined(GX_DOTNET)
	inline gxOutData GetPixels(void) GX_CONST gxFuncThrowsError {
		return GX_PUTDATA(_image->image, _image->simage);
	}
#elif defined(GX_SWIG)
	inline gxOutData GetPixels(void) GX_CONST gxFuncThrowsError {
		return GX_PUTDATA(image(), simage());
	}
#else
	inline void *GetPixels(void) GX_CONST gxFuncThrowsError {
		return image();
	}
#endif

	/** Returns size of the image in bytes. @see gxIMAGE
	 * @return Size of the image in bytes. */
	inline gxi32 GetSImage(void) GX_CONST gxFuncThrowsError {
		return simage();
	}
	/** Returns the pixel format of the image. @see gxIMAGE
	 * @return Pixel format of the image (see \ref GX_PIXELFORMATS). */
	inline gxi32 GetPixelFormat(void) GX_CONST gxFuncThrowsError {
		return format();
	}
	/** Returns the horizontal size of the image in pixels. @see gxIMAGE
	 * @return Horizontal size of the image in pixels. */
	inline gxi32 GetXSize(void) GX_CONST gxFuncThrowsError {
		return xsize();
	}
	/** Returns the vertical size of the image in pixels. @see gxIMAGE
	 * @return Vertical size of the image in pixels. */
	inline gxi32 GetYSize(void) GX_CONST gxFuncThrowsError {
		return ysize();
	}
	/** Returns the size of a row in bytes. @see gxIMAGE
	 * @return Size of a row in bytes. */
	inline gxi32 GetSLine(void) GX_CONST gxFuncThrowsError {
		return sline();
	}
	/** Returns the horizontal resolution of the image. @see gxIMAGE
	 * @return Horizontal resolution of the image. */
	inline gxi32 GetXRes(void) GX_CONST gxFuncThrowsError {
		return xres();
	}
	/** Returns the vertical resolution of the image. @see gxIMAGE
	 * @return Vertical resolution of the image. */
	inline gxi32 GetYRes(void) GX_CONST gxFuncThrowsError {
		return yres();
	}
	/** Sets the horizontal resolution of the image. @see gxIMAGE
	 * @param _xres Horizontal resolution to set.
	 * @return The function always returns true. */
	inline bool SetXRes(gxi32 _xres) gxFuncThrowsError {
		xres(_xres);
		return true;
	}
	/** Sets the vertical resolution of the image. @see gxIMAGE
	 * @param _yres Vertical resolution to set.
	 * @return The function always returns true. */
	inline bool SetYRes(gxi32 _yres) gxFuncThrowsError {
		yres(_yres);
		return true;
	}
#endif	/*)*/
public:
#if defined(GX_DOTNET) || defined(GX_SWIGIF)	/*(*/
	/** Class initialization with default properties. */
	inline gxImage() gxFuncThrowsError : gxImageHandler() {
		_image = 0;
		if(gxHandle::IsValid()) {
#ifndef GX_DOTNET
			if(!gx_allocimage(*this, &_image)) gxthrow;
#else
			GX_GETHANDLE(h);
			GX_GETIMAGE(i);
			if(!gx_allocimage(h, &i)) gxthrow;
			_set_image(i);
#endif
		}
	}
#endif	/*)*/

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Class initialization with default properties. */
	inline gxImage() gxFuncThrowsError : gxImageHandler(), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}

	/** Class initialization with a source image handle.
	 * @param h Source image handle. The reference of this
	 *		image handle will be increased. */
	inline gxImage(const gxHANDLE &h) gxFuncThrowsError : gxImageHandler(h), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
	/** Class initialization with a source image handle.
	 * @param h Source image handle. The reference of this
	 *		image handle will be increased. */
	inline gxImage(const gxHANDLE *h) gxFuncThrowsError : gxImageHandler(h), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}

	/** Class initialization with the place of the properties and name of the module
	 * (Unicode version).
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}

	/** Class initialization with the place of the properties and name of the module
	 * (ASCII version).
	 * @param propname Place of properties in property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}

	/** Class initialization with another image structure.
	 * @param src Source image. */
	inline gxImage(gxIMAGE &src) gxFuncThrowsError : gxImageHandler(), gxImageData() {
		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another image structure, the place of the properties
	 * and name of the module (Unicode version).
	 * @param src Source image.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(gxIMAGE &src, const wchar_t *propname,
				const wchar_t *modname = (const wchar_t *)0) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another image structure, the place of the properties
	 * and name of the module (ASCII version).
	 * @param src Source image.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(gxIMAGE &src, const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another image class, the place of the properties
	 * and name of the module (Unicode version).
	 * @param src Source image.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(gxImage &src, const wchar_t *propname, const wchar_t *modname = (const wchar_t *)0)
				gxFuncThrowsError : gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}

	/** Class initialization with another image class, the place of the properties
	 * and name of the module (ASCII version).
	 * @param src Source image.
	 * @param propname Place of the properties in the property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(gxImage &src, const char *propname,
				const char *modname = (const char *)0) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#endif	/*)*/

#ifdef GX_UNICODE	/*(*/
	/** Class initialization with the place of the properties (Unicode version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
#ifndef GX_DOTNET
	inline gxImage(gxInStr propname) gxFuncThrowsError
				: gxImageHandler(propname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
#else
	inline gxImage(gxInStr propname) gxFuncThrowsError
				: gxImageHandler(propname) {

		_set_image(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETIMAGE(i);
			if(!gx_allocimage(h, &i)) gxthrow;
			_set_image(i);
		}
	}
#endif

	/** Class initialization with the place of the properties and name of the module (Unicode version).
	 *
	 * @param propname Place of properties in property tree (Name of a property group).
	 * @param modname Name of the module. */
#ifndef GX_DOTNET
	inline gxImage(gxInStr propname, gxInStr modname) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
#else
	inline gxImage(gxInStr propname, gxInStr modname) gxFuncThrowsError
				: gxImageHandler(propname, modname) {

		_set_image(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETIMAGE(i);
			if(!gx_allocimage(h, &i)) gxthrow;
			_set_image(i);
		}
	}
#endif

#endif	/*)*/

#ifdef GX_ASCII
	/** Class initialization with the place of the properties (ASCII version).
	 *
	 * @param propname Place of the properties in the property tree (Name of a property group). */
	inline gxImage(gxInAStr propname) gxFuncThrowsError
				: gxImageHandler(propname), gxImageData() {

		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
	/** Class initialization with the place of the properties and name of the module (ASCII version).
	 *
	 * @param propname Place of properties in property tree (Name of a property group).
	 * @param modname Name of the module. */
	inline gxImage(gxInAStr propname, gxInAStr modname) gxFuncThrowsError
				: gxImageHandler(propname, modname), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
#endif

	/** Class initialization with previously initialized image handler.
	 *
	 * @param ih Previously intialized image handler. */
#ifndef GX_DOTNET
	inline gxImage(gxImageHandler &ih) gxFuncThrowsError : gxImageHandler(ih), gxImageData() {
		if(gxHandle::IsValid()) {
			if(!gx_allocimage(*this, &_image)) gxthrow;
		}
	}
#else

	inline gxImage(gxImageHandler GX_REF_CLASS(ih)) gxFuncThrowsError : gxImageHandler(ih) {

		_set_image(GX_NULLPTR);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETIMAGE(i);
			if(!gx_allocimage(h, &i)) gxthrow;
			_set_image(i);

		}
	}
#endif

	/** Class initialization with previously initialized image.
	 *
	 * @param src Previously intialized image. */
#ifndef GX_DOTNET
	inline gxImage(gxImage &src) gxFuncThrowsError : gxImageHandler((const gxHANDLE &)src), gxImageData() {
		if(gxHandle::IsValid()) {
			if(gx_allocimage(*this, &_image)) {
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#else
	inline gxImage(gxImage GX_REF_CLASS(src)) gxFuncThrowsError : gxImageHandler(src) {
		_set_image(0);
		if(gxHandle::IsValid()) {
			GX_GETHANDLE(h);
			GX_GETIMAGE(i);
			if(gx_allocimage(h, &i)) {
				_set_image(i);
				Copy(src);
			} else {
				gxthrow;
			}
		}
	}
#endif

	/** Class termination. */
	inline ~gxImage() gxFuncThrowsError {
		_Dispose();
	}

#ifdef GX_DOTNET_20
	inline !gxImage() gxFuncThrowsError {
		_Dispose();
	}
#else
	/** It disposes the class. */
	inline void Dispose(void) gxFuncThrowsError {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);//do not call it from a destructor explicitly!
#endif
		_Dispose();
		/** call the base class */
		gxHandle::Dispose();
	}
#endif

private:
inline void _Dispose(void) gxFuncThrowsError {
#ifndef GX_DOTNET
		if(_image) {
			if(!gx_unrefimage(*this, _image)) gxthrow;
		}
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		if(i) {
			if(!gx_unrefimage(h, i)) gxthrow;
		}
#endif
		_image=0;
	}

public:

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)	/*(*/
	/** Copies an image to the class.
	 *
	 * @param src	Source image structure.
	 * @return Returns a reference to the image class. */
	inline gxImage &operator = (gxIMAGE &src) gxFuncThrowsError {
		Copy(src);
		return *this;
	}

	/** Copies an image to the class.
	 *
	 * @param src	Source image class.
	 * @return Returns a reference to the image class. */
	inline gxImage &operator = (gxImage &src) gxFuncThrowsError {
		Copy(src);
		return *this;
	}

	/** Returns a reference to the gxIMAGE structure.
     * @return Reference to the gxIMAGE structure. */
	inline operator gxIMAGE & () gxFuncThrowsError {
		gxassert(_image);
		return *_image;
	}
	/** Returns a pointer to the gxIMAGE structure.
     * @return Pointer to the gxIMAGE structure. */
	inline operator gxIMAGE * () gxFuncThrowsError {
		gxassert(_image);
		return _image;
	}
	/** Returns a pointer to the gxIMAGE structure.
     * @return Pointer to the gxIMAGE structure. */
	inline operator const gxIMAGE * () const gxFuncThrowsError {
		gxassert(_image);
		return _image;
	}

	/** Attaches to an allocated image.
	 * @param src An allocated gxIMAGE structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Attach(gxIMAGE *src) gxFuncThrowsError {
		gxassert(_image && src);
		if(src->ref >= 0) {
			gx_seterror(GX_EINVAL, L"(src->ref < 0)");
			gxthrow;
			return false;
		}
		if(!gx_refimage(*this, src)) {
			gxthrow;
			return false;
		}
		if(!gx_unrefimage(*this, _image)) {
			gx_unrefimage(*this, src);
			gxthrow;
			return false;
		}
		_image = src;
		return true;
	}

	/** Detaches the image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Detach(void) gxFuncThrowsError {
		if(!gx_unrefimage(*this, _image)) {
			gxthrow;
			return false;
		}
		if(!gx_allocimage(*this, &_image)) {
			gxthrow;
			return false;
		}
		return true;
	}

	/** Gets the size of a pixel in bytes.
	 * @param size Size of the pixel format.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetPixelSize(gxi32 *size) const gxFuncThrowsError {
		if(!gx_getpixelsize(*this, size, format())) {
			throw gxError();
			return false;
		}
		return true;
	}

	/** Returns the pointer of the pixel.
	 * @param x Horizontal position of the pixel.
	 * @param y Vertical position of the pixel.
	 * @return The pointer of the pixel or NULL if an error occurred
	 * or the pixel is not found. */
	inline void *GetPixelPtr(gxi32 x, gxi32 y) gxFuncThrowsError {
		gxassert(_image);
		void *ret = gx_getpixelptr(*this, _image, x, y);
		gxcondthrow(!ret);
		return ret;
	}
#endif	/*)*/
	/** Returns the size of a current format pixel in bytes.
	 * @return Size of the pixel in bytes. */
	inline gxi32 GetPixelSize(void) GX_CONST gxFuncThrowsError {
		gxi32 size = -1;
		GX_GETHANDLE(h);
		if(!gx_getpixelsize(h, &size, format())) gxthrow;
		return size;
	}

	/** Makes an image with proper size and format.
	 * @param format Pixel format (see \ref GX_PIXELFORMATS).
	 * @param xsize Horizontal size of image in pixels.
	 * @param ysize Vertical size of image in pixels.
	 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
	 *         bytes). If zero the system computes the correct value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		bool st = gx_createimage(h, _image, format, xsize, ysize, sline) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Converts an image to a specific format and size.
	 * @param src Pointer to the source image.
	 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
	 * @param xsize Horizontal size of the destination image in pixels.
	 * @param ysize Vertical size of the destination image in pixels.
	 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
	 *         bytes). If zero the system computes the correct value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Convert(gxIMAGE *src, gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_convertimage(*this, _image, src, format, xsize, ysize, sline) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
	/** Converts an image to a specific format and size.
	 * @param src Reference to the source image data.
	 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
	 * @param xsize Horizontal size of the destination image in pixels.
	 * @param ysize Vertical size of the destination image in pixels.
	 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
	 *         bytes). If zero the system computes the correct value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Convert(gxImageData GX_REF_CLASS(src), gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
#ifndef GX_DOTNET
		bool st = gx_convertimage(h, _image, src._image, format, xsize, ysize, sline) ? true : false;
#else
		bool st = gx_convertimage(h, _image, (gxIMAGE *)src GX_M _get_image().ToPointer(), format, xsize, ysize, sline) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Converts an image to a specific format and size.
	 * @param src Pointer to the source image.
	 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
	 * @param xsize Horizontal size of the destination image in pixels.
	 * @param ysize Vertical size of the destination image in pixels.
	 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
	 *         bytes). If zero the system computes the correct value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Convert(gxImage GX_REF_CLASS(src), gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		bool st = gx_convertimage(h, _image, src GX_M _image, format, xsize, ysize, sline) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Converts an image to a specific format and size.
	 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
	 * @param xsize Horizontal size of the destination image in pixels.
	 * @param ysize Vertical size of the destination image in pixels.
	 * @param sline Length of a row in bytes (min.: xsize * size of a pixel in
	 *         bytes). If zero the system computes the correct value.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Convert(gxi32 format, gxi32 xsize, gxi32 ysize, gxi32 sline GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		bool st = gx_convertimage(h, _image, _image, format, xsize, ysize, sline) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Converts an image to a specific format.
	 * @param format Pixel format of the destination image (see \ref GX_PIXELFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Convert(gxi32 format) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		bool st = gx_convertimage(h, _image, _image, format, xsize(), ysize(), 0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Copies an image to the class.
	 * @param src Pointer of the source image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(gxIMAGE *src) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_copyimage(*this, _image, src) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Copies an image to the class.
	 * @param src Pointer of the source image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(gxIMAGE &src) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_copyimage(*this, _image, &src) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Copies an image to the class.
	 * @param src Pointer of the source image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(gxImage *src) gxFuncThrowsError {
		gxassert(src);
		return Copy((gxIMAGE *)(*src));
	}
#endif

	/** Copies an image to the class.
	 * @param src Reference of the source image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(gxImageData GX_REF_CLASS(src)) gxFuncThrowsError {
#ifndef GX_DOTNET
		return Copy((gxIMAGE &)src);
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_copyimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer()) ? true : false;
		gxcondthrow(!st);
		return st;
#endif
	}

	/** Copies an image to the class.
	 * @param src Pointer of the source image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(gxImage GX_REF_CLASS(src)) gxFuncThrowsError {
#ifndef GX_DOTNET
		return Copy((gxIMAGE &)src);
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_copyimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer()) ? true : false;
		gxcondthrow(!st);
		return st;
#endif
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Zooms an image to a specified size.
	 * @param src   Pointer to the source image.
	 * @param xsize Horizontal size of the destination area.
	 * @param ysize Vertical size of the destination area.
	 * @param sline Size of a row of the destination area.
	 * @param sx1_8 Left coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy1_8 Top coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sx2_8 Right coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy2_8 Bottom coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Zoom(gxIMAGE *src, gxi32 xsize, gxi32 ysize, gxi32 sline,
					gxi32 sx1_8 GX_DEFARG(0), gxi32 sy1_8 GX_DEFARG(0),
					gxi32 sx2_8 GX_DEFARG(0), gxi32 sy2_8 GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_zoomimage(*this, _image, xsize, ysize, sline, src,
					sx1_8, sy1_8, sx2_8, sy2_8) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Zooms an image to a specified size.
	 * @param src   Reference to the source image data.
	 * @param xsize Horizontal size of the destination area.
	 * @param ysize Vertical size of the destination area.
	 * @param sline Size of a row of the destination area.
	 * @param sx1_8 Left coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy1_8 Top coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sx2_8 Right coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy2_8 Bottom coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Zoom(gxImageData GX_REF_CLASS(src), gxi32 xsize, gxi32 ysize, gxi32 sline,
					gxi32 sx1_8 GX_DEFARG(0), gxi32 sy1_8 GX_DEFARG(0),
					gxi32 sx2_8 GX_DEFARG(0), gxi32 sy2_8 GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_zoomimage(*this, _image, xsize, ysize, sline, src,
					sx1_8, sy1_8, sx2_8, sy2_8) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_zoomimage(h, i, xsize, ysize, sline,
					(gxIMAGE *)src GX_M _get_image().ToPointer(),
					sx1_8, sy1_8, sx2_8, sy2_8) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#ifdef GX_DOTNET
	/** Zooms an image to a specified size.
	 * @param src   Reference to the source image data.
	 * @param xsize Horizontal size of the destination area.
	 * @param ysize Vertical size of the destination area.
	 * @param sline Size of a row of the destination area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Zoom(gxImageData GX_REF_CLASS(src), gxi32 xsize, gxi32 ysize, gxi32 sline) gxFuncThrowsError {
			return false;
		//return Zoom(src, xsize, ysize, sline, 0,0,0,0);
	}
#endif

	/** Zooms an image to a specified size.
	 * @param src   Reference to the source image.
	 * @param xsize Horizontal size of the destination area.
	 * @param ysize Vertical size of the destination area.
	 * @param sline Size of a row of the destination area.
	 * @param sx1_8 Left coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy1_8 Top coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sx2_8 Right coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @param sy2_8 Bottom coordinate of the zoomed area (shifted left with 8 bit = 256)
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Zoom(gxImage GX_REF_CLASS(src), gxi32 xsize, gxi32 ysize, gxi32 sline,
					gxi32 sx1_8 GX_DEFARG(0), gxi32 sy1_8 GX_DEFARG(0),
					gxi32 sx2_8 GX_DEFARG(0), gxi32 sy2_8 GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_zoomimage(*this, _image, xsize, ysize, sline, src,
					sx1_8, sy1_8, sx2_8, sy2_8) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_zoomimage(h, i, xsize, ysize, sline,
					(gxIMAGE *)src GX_M _get_image().ToPointer(),
					sx1_8, sy1_8, sx2_8, sy2_8) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}
#ifdef GX_DOTNET
	/** Zooms an image to a specified size.
	 * @param src   Reference to the source image.
	 * @param xsize Horizontal size of the destination area.
	 * @param ysize Vertical size of the destination area.
	 * @param sline Size of a row of the destination area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Zoom(gxImage GX_REF_CLASS(src), gxi32 xsize, gxi32 ysize, gxi32 sline) gxFuncThrowsError {
		return Zoom(src, xsize, ysize, sline, 0,0,0,0);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Rotates an image to a specified degree.
	 * @param src  Pointer to the source image.
	 * @param degree Degree (Must be 0, 90, 180, 270).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Rotate(gxIMAGE *src, gxi32 degree) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_rotateimage(*this, _image, src, degree) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Rotates an image to a specified degree.
	 * @param src  Reference to the source image data.
	 * @param degree Degree (Must be 0, 90, 180, 270).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Rotate(gxImageData GX_REF_CLASS(src), gxi32 degree) gxFuncThrowsError {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_rotateimage(*this, _image, src, degree) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_rotateimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer(), degree) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Rotates an image to a specified degree.
	 * @param src  Reference to the source image.
	 * @param degree Degree (Must be 0, 90, 180, 270).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Rotate(gxImage GX_REF_CLASS(src), gxi32 degree) gxFuncThrowsError {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_rotateimage(*this, _image, src, degree) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_rotateimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer(), degree) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Mirrors an image to a specified mode.
	 * @param src Pointer to an image.
	 * @param flags Mirror flags. It can be \ref GX_MIRROR_HORIZONTAL or/and \ref GX_MIRROR_VERTICAL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Mirror(gxIMAGE *src, gxi32 flags) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_mirrorimage(*this, _image, src, flags) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
	/** Mirrors an image to a specified mode.
	 * @param src Reference to an image data.
	 * @param flags Mirror flags. It can be \ref GX_MIRROR_HORIZONTAL or/and \ref GX_MIRROR_VERTICAL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Mirror(gxImageData GX_REF_CLASS(src), gxi32 flags) {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_mirrorimage(*this, _image, src, flags) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_mirrorimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer(), flags) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Mirrors an image to a specified mode.
	 * @param src Reference to an image.
	 * @param flags Mirror flags. It can be \ref GX_MIRROR_HORIZONTAL or/and \ref GX_MIRROR_VERTICAL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Mirror(gxImage GX_REF_CLASS(src), gxi32 flags) {
		gxassert(_image);
#ifndef GX_DOTNET
		bool st = gx_mirrorimage(*this, _image, src, flags) ? true : false;
#else
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_mirrorimage(h, i, (gxIMAGE *)src GX_M _get_image().ToPointer(), flags) ? true : false;
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Mirrors an image to a specified mode.
	 * @param flags Mirror flags. It can be \ref GX_MIRROR_HORIZONTAL or/and \ref GX_MIRROR_VERTICAL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Mirror(gxi32 flags) {
		gxassert(_image);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_mirrorimage(h, i, flags) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Loads an image from a mass storage device and converts it to a specific pixel
	 * format (Unicode version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(const wchar_t *filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF),
					gxVARIANT properties GX_DEFARG(0),
					gxVARIANT comments GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_loadimagefromfile(_image, filename, pixelformat,
						properties, comments) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads an image from a mass storage device and converts it to a specific pixel
	 * format (ASCII version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(const char *filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF),
					gxVARIANT properties GX_DEFARG(0),
					gxVARIANT comments GX_DEFARG(0)) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_loadimagefromfile(_image, filename, pixelformat,
						properties, comments) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_UNICODE
	/** Loads an image with comments from a mass storage device and converts it
	 * to a specific pixel format (Unicode version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \ifnot NET
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 * \endif
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader.
	 * @param comments Comments of the image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInStr filename, gxi32 pixelformat,
#ifndef GX_DOTNET
					gxVariant &properties, gxVariant &comments
#else
	#ifndef GX_DOTNET_20
					gxVariant *properties, gxVariant *comments
	#else
					gxVariant ^properties, gxVariant ^comments
	#endif
#endif
					) gxFuncThrowsError {

		GX_GETSTRING(_filename, filename);
		GX_GETIMAGE(i);
		bool st = gx_loadimagefromfile(i, _filename, pixelformat,
#ifndef GX_DOTNET
					properties._variant, comments._variant
#else
					properties ? properties->_variant : 0,
					comments ? comments->_variant : 0
#endif
					) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads an image from a mass storage device and converts it
	 * to a specific pixel format (Unicode version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \ifnot NET
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 * \endif
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInStr filename, gxi32 pixelformat) gxFuncThrowsError {

		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_loadimage(h, i, _filename, pixelformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads an image from a mass storage device (Unicode version).
	 * @param filename Name of the image file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInStr filename) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_loadimage(h, i, _filename, (int)GX_ENUM_PATH(GX_PIXELFORMATS) GX_UNDEF) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Loads an image with comments from a mass storage device and converts it
	 * to a specific pixel format (ASCII version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader.
	 * @param comments Comments of the image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInAStr filename, gxi32 pixelformat,
				gxVariant &properties, gxVariant &comments) gxFuncThrowsError {

		GX_GETASTRING(_filename, filename);
		bool st = gx_loadimagefromfile(_image, _filename, pixelformat,
					properties._variant, comments._variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads an image from a mass storage device and converts it to a specific pixel
	 * format (ASCII version).
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::Load() must be -1 for RAW images.
	 *
	 * \code
	   gxImage image;
	   image.Create(GX_GRAY, 1024, 768, 1024);
	   image.Load("test.raw", -1);
	   ...
	   \endcode
	 *
	 * @param filename Name of the image file.
	 * @param pixelformat The specific pixel format. Giving \ref GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Load(gxInAStr filename, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		bool st = gx_loadimage(*this, _image, _filename, pixelformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Saves an image to a mass storage device in the specific file format
	 * (Unicode version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const wchar_t *filename, gxi32 fileformat) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_saveimage(*this, _image, filename, fileformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image to a mass storage device in the specific file format
	 * (ASCII version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const char *filename, gxi32 fileformat) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_saveimage(*this, _image, filename, fileformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image with comments to a mass storage device in the specific
	 * file format (Unicode version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const wchar_t *filename, gxi32 fileformat,
					gxVariant &properties, gxVariant &comments) gxFuncThrowsError {

		gxassert(_image);
		bool st = gx_saveimagetofile(_image, filename, fileformat,
						properties._variant, comments._variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image with comments to a mass storage device in the specific
	 * file format (ASCII version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(const char *filename, gxi32 fileformat,
					gxVariant &properties, gxVariant &comments) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_saveimagetofile(_image, filename, fileformat,
					properties._variant, comments._variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_UNICODE
	/** Saves an image to a mass storage device in the specific file format
	 * (Unicode version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInStr filename, gxi32 fileformat,
				gxVariant GX_REF_CLASS(properties), gxVariant GX_REF_CLASS(comments)
				) gxFuncThrowsError {

		GX_GETSTRING(_filename, filename);
		GX_GETIMAGE(i);
		bool st = gx_saveimagetofile(i, _filename, fileformat,
#ifndef GX_DOTNET
				properties._variant, comments._variant
#else
				properties ? properties->_variant : 0,
				comments ? comments->_variant : 0
#endif
				) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image to a mass storage device in the specific file format
	 * (Unicode version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInStr filename, gxi32 fileformat) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_saveimage(h, i, _filename, fileformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Saves an image with comments to a mass storage device in the specific
	 * file format (ASCII version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInAStr filename, gxi32 fileformat,
				gxVariant &properties, gxVariant &comments) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		return Save(_filename, fileformat, properties, comments);
	}

	/** Saves an image to a mass storage device in the specific file format
	 * (ASCII version).
	 * @param filename Name of the image file.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Save(gxInAStr filename, gxi32 fileformat) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		return Save(_filename, fileformat);
	}
#endif

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Loads an image with comments from the memory and converts it to
	 * a specific pixel format.
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::LoadFromMem() must be -1 for RAW images.
	 *
	 * @param buffer Pointer to the image data.
	 * @param buflen Length of image data in bytes.
	 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader.
	 * @param comments Comments of the image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool LoadFromMem(const void *buffer, gxi32 buflen, gxi32 pixelformat,
					gxVariant &properties, gxVariant &comments) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_loadimagefrommem(_image, buffer, buflen, pixelformat,
					properties._variant, comments._variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image with comments in a specific file format to a
	 * specific memory area.
	 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
	 * @param buflen Size of the memory area.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveToMem(void **buffer, gxi32 *buflen, gxi32 fileformat,
					gxVariant &properties, gxVariant &comments) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_saveimagetomem(_image, buffer, buflen, fileformat,
					properties._variant, comments._variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Loads an image from the memory and converts it to a specific pixel format.
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::LoadFromMem() must be -1 for RAW images.
	 *
	 * @param buffer Pointer to the image data.
	 * @param buflen Length of image data in bytes.
	 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool LoadFromMem(const void *buffer, gxi32 buflen, gxi32 pixelformat GX_DEFARG(GX_UNDEF)) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_loadfrommem(*this, _image, buffer, buflen, pixelformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Saves an image in a specific file format to a specific memory area.
	 * @param buffer Pointer to the memory area pointer that is large enough or NULL.
	 * @param buflen Size of the memory area.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool SaveToMem(void **buffer, gxi32 *buflen, gxi32 fileformat) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_savetomem(*this, _image, buffer, buflen, fileformat) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if defined(GX_SWIG) || defined(GX_DOTNET)	/*(*/
	/** Loads an image with comments from the memory and converts it to
	 * a specific pixel format.
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::LoadFromMem() must be -1 for RAW images.
	 *
	 * @param buffer The image data.
	 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @param properties Properties for the image loader.
	 * @param comments Comments of the image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool LoadFromMem(gxInData buffer, gxi32 pixelformat,
				gxVariant GX_REF_CLASS(properties), gxVariant GX_REF_CLASS(comments)
				) gxFuncThrowsError {

		GX_GETDATA(buffer);
		GX_GETIMAGE(i);
		bool st = gx_loadimagefrommem(i, GX_DATAPTR(buffer), GX_DATALEN(buffer), pixelformat,
#ifndef GX_DOTNET
					properties._variant, comments._variant
#else
					properties ? properties->_variant : 0,
					comments ? comments->_variant : 0
#endif
					) ? true : false;
		GX_FREEDATA(buffer);
		if(!st) gxthrow;
		return st;
	}

	/** Saves an image with comments in a specific file format to a specific memory area.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @param properties Properties for the image writer. It can be empty.
	 * @param comments Comments of the image. It can be empty.
	 * @return Image data. An exception is thrown or null is returned in case of error. */
	inline gxOutData SaveToMem(gxi32 fileformat,
					gxVariant GX_REF_CLASS(properties), gxVariant GX_REF_CLASS(comments)
					) gxFuncThrowsError {

		void *buffer = (void *)0;
		gxi32 buflen = 0;
		GX_GETIMAGE(i);
		if(!gx_saveimagetomem(i, &buffer, &buflen, fileformat,
#ifndef GX_DOTNET
					properties._variant, comments._variant
#else
					properties ? properties->_variant : 0,
					comments ? comments->_variant : 0
#endif
					)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(buffer, buflen);
		if(buffer) gx_globalfree(buffer);
		return ret;
	}

	/** Loads an image from the memory and converts it to a specific pixel format.
	 *
	 * On loading a RAW image, the image must be created with correct
	 * parameters (sline parameter also included). The format parameter of the
	 * gxImage::LoadFromMem() must be -1 for RAW images.
	 *
	 * @param buffer The image data.
	 * @param pixelformat The specific pixel format. Giving GX_GRAY converts a color
	 *               image to grayscale (see \ref GX_PIXELFORMATS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool LoadFromMem(gxInData buffer, gxi32 pixelformat) gxFuncThrowsError {
		GX_GETDATA(buffer);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_loadfrommem(h, i, GX_DATAPTR(buffer), GX_DATALEN(buffer), pixelformat) ? true : false;
		GX_FREEDATA(buffer);
		if(!st) gxthrow;
		return st;
	}

	/** Saves an image in a specific file format to a specific memory area.
	 * @param fileformat Format of the image file (see \ref GX_IMGFILEFORMATS).
	 * @return Image data. An exception is thrown or null is returned in case of error. */
	inline gxOutData SaveToMem(gxi32 fileformat) gxFuncThrowsError
	{
		void *buffer = (void *)0;
		gxi32 buflen = 0;
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		if(!gx_savetomem(h, i, &buffer, &buflen, fileformat)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(buffer, buflen);
		if(buffer) gx_globalfree(buffer);
		return ret;
	}
#endif	/*)*/

	/** Checks if the image structure and the handle are valid.
	 * @return In case of valid image the return value is non-zero. */
	inline bool IsValid(void) GX_CONST {
		if(!gxHandle::IsValid()) return false;
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		return gx_isvalidimage(h, i) ? true : false;
	}

#ifdef WIN32	/*(*/
#if !defined(GX_SWIGIF)
	/** Displays an image.
	 * @param hdc Handle of device context.
	 * @param x   X1 coordinate of display.
	 * @param y   Y1 coordinate of display.
	 * @param xsize Displayed horizontal size of image.
	 * @param ysize Displayed vertical size of image.
	 * @return An exception is thrown or false is returned in case of error. */
#ifndef GX_DOTNET
	inline bool DisplayImage(HDC hdc, gxi32 x, gxi32 y, gxi32 xsize, gxi32 ysize) gxFuncThrowsError {
		gxassert(_image);
		bool st = gx_displayimage(*this, hdc, x, y, xsize, ysize, _image) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	inline bool DisplayImage(gxInPtr hdc, gxi32 x, gxi32 y, gxi32 xsize, gxi32 ysize) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		bool st = gx_displayimage(h, hdc.ToPointer(), x, y, xsize, ysize, _image) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#endif

	/** Copies the image to the clipboard.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Copy(void) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_imgtoclipboard(h, i) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inserts an image from the clipboard.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Paste(void) gxFuncThrowsError {
		gxassert(_image);
		GX_GETHANDLE(h);
		GX_GETIMAGE(i);
		bool st = gx_pasteimage(h, i) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif	/*)*/

	/** Loads an embedded image from a variant.
	 *
	 * @param variant	Variant with an embedded image.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool FromVariant(
		gxVariant GX_REF_CLASS(variant)
		) gxFuncThrowsError {

		GX_GETIMAGE(i);
#ifndef GX_DOTNET
		bool st = gx_imagefromvariant(&i, variant._variant) ? true : false;
		if(st) {
			gx_unrefimage(_image);
			_image=i;
		}
#else
		bool st = gx_imagefromvariant(&i,
			variant ? variant->_variant : 0 ) ? true : false;
		if(st) {
			gx_unrefimage(_image);
			_set_image(i);
		}
#endif
		gxcondthrow(!st);
		return st;
	}

	/** Embedds an image into a variant.
	 *
	 * @param varid		The id for the created variant.
	 * @return An exception is thrown or false is returned in case of error. */
	inline GX_INDIRECTION1(gxVariant) ToVariant(gxi32 varid) gxFuncThrowsError {

		GX_GETIMAGE(i);
		gxVARIANT vari;
		bool st = gx_imagetovariant(i, varid, &vari) != 0;
		gxcondthrow(!st);
		if(!st) return GX_NULLPTR;
		GX_INDIRECTION(gxVariant,vr) = gxnew gxVariant(vari);
		gx_unrefvariant(vari);
		if(!vr){gxSystem::SetError((int)GX_ENUM_PATH(GX_ERROR_CODES) GX_ENOMEM);gxthrow;}
		return vr;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Tests if a file is an image file.
	 *
	 * @param filename Name of the file to test.

	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(const wchar_t *filename) gxFuncThrowsError {
		gxassert(filename);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(filename, &fileformat) ? true : false;
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}

	/** Tests if a file is an image file.
	 *
	 * @param filename Name of the file to test.

	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(const char *filename) gxFuncThrowsError {
		gxassert(filename);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(filename, &fileformat) ? true : false;
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}

	/** Tests if a memory area contains an image file.
	 *
	 * @param buffer Pointer to the memory area.
	 * @param buflen Size of the memory area.
	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(const void *buffer, gxi32 buflen) gxFuncThrowsError {
		gxassert(buffer && buflen>0);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(buffer, buflen, &fileformat) ? true : false;
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}
#else
	/** Tests if a memory area contains an image file.
	 *
	 * @param buffer The file data.
	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(gxInData buffer) gxFuncThrowsError {
		GX_GETDATA(buffer);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(GX_DATAPTR(buffer), GX_DATALEN(buffer), &fileformat) ? true : false;
		GX_FREEDATA(buffer);
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}
#endif

#ifdef GX_UNICODE
	/** Tests if a file is an image file.
	 *
	 * @param filename Name of the file to test.

	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(gxInStr filename) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(_filename, &fileformat) ? true : false;
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}
#endif

#ifdef GX_ASCII
	/** Tests if a file is an image file.
	 *
	 * @param filename Name of the file to test.

	 * @return An exception is thrown or 0 is returned in case of error, -1 is returned
	 * for unknown file type. */
	inline gxi32 TestImageFileFormat(gxInAStr filename) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		gxi32 fileformat;
		bool st = gx_testimagefileformat(_filename, &fileformat) ? true : false;
		if(!st) { gxthrow; return 0; }
		return fileformat;
	}
#endif

};

#endif	/* GX_EXT_MODULE )*/

#endif /* NO_GX_CLASSES )*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
/******************************************************************************/
#endif /* GX_IMAGE_INCL */
/******************************************************************************/
