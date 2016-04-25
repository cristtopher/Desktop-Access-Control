/*******************************************************************************
 * GX TYPES file - V7.2.9
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/******************************************************************************/
/** \file
 * <b> GX system type definitions </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * This file contains the type definitions of the GX system.
 */
/******************************************************************************/
#ifndef GX_TYPES_INCL
#define GX_TYPES_INCL
/******************************************************************************/
#ifdef GX_SHOW_HEADER
	#pragma message(__FILE__"(1): Show header")
#endif
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(disable : 4505)		/* unreferenced local function */
	#pragma warning(disable : 4290)		/* exception specification ignored */
	#pragma warning(push)
	#pragma warning(disable : 4786)		/* truncated debug info */
#endif
/******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -use					/* never used function */
#endif
/******************************************************************************/
#if !defined(LINUX) && (defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__))
	#define LINUX
#endif
#if !defined(WIN64) && defined(_WIN64)
	#define WIN64
#endif
#if !defined(WIN32) && (defined(_WIN32) || defined(__WIN32__) || defined(WIN64))
	#define WIN32
#endif

#ifdef LINUX
	#ifndef __KERNEL__
		#include <stdint.h>

		#if __BYTE_ORDER == __LITTLE_ENDIAN
			/** Little endian format on Intel compatible CPUs */
			#define GX_LITTLE_ENDIAN 1
		#elif __BYTE_ORDER == __BIG_ENDIAN
			/** Big endian format on PowerPC */
			#define GX_BIG_ENDIAN 1
		#else
			#error "Please fix it!"
		#endif

		#if __WORDSIZE == 64
			#define LINUX64
			#define GX64
		#else
			#define LINUX32
			#define GX32
		#endif
	#else
		#define GX_LITTLE_ENDIAN 1
	#endif
#else
	#ifdef WIN64
		#ifndef GX64
			#define GX64
		#endif
	#else
		#ifndef GX32
			#define GX32
		#endif
	#endif

	/** Only supports Intel-format on MS-Windows */
	#define GX_LITTLE_ENDIAN 1
#endif
/******************************************************************************/
#if defined(__GNUC__) || (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 910))
	#define _GX_FUNCTION_	__PRETTY_FUNCTION__
#elif defined (__FUNCSIG__)
	#define _GX_FUNCTION_	__FUNCSIG__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define _GX_FUNCTION_	__FUNC__
#else
	#define _GX_FUNCTION_	"(unknown)"
#endif
/******************************************************************************/
typedef		signed char			gxi8;	/**< 8 bit signed integer.    */
typedef		unsigned char		gxu8;	/**< 8 bit unsigned integer.  */
typedef		signed short		gxi16;	/**< 16 bit signed integer.   */
typedef		unsigned short		gxu16;	/**< 16 bit unsigned integer. */
typedef		signed int			gxi32;	/**< 32 bit signed integer.   */
typedef		unsigned int		gxu32;	/**< 32 bit unsigned integer. */

#if defined(__GNUC__) || defined(GX_SWIGIF)
	typedef signed long long gxi64;		/**< 64 bit signed integer.   */
	typedef unsigned long long gxu64;	/**< 64 bit unsigned integer. */
	#define GXI64CONST(X) X ## LL
	#define GXU64CONST(X) X ## UL
#else
	typedef	signed __int64		gxi64;	/**< 64 bit signed integer.   */
	typedef	unsigned __int64	gxu64;	/**< 64 bit unsigned integer. */
	#define GXI64CONST(X) X ## i64
	#define GXU64CONST(X) X ## ui64
#endif

typedef		float				gxf32;	/**< 32 bit floating-point number. */
typedef		double				gxf64;	/**< 64 bit floating-point number. */
/******************************************************************************/
#ifdef GX_LITTLE_ENDIAN
/* CPU to FILE */
	/** Converts an 8 bit signed integer from CPU to file.	 */
	#define GX_C2F_I8(x)	(x)
	/** Converts an 8 bit unsigned integer from CPU to file. */
	#define GX_C2F_U8(x)	(x)
	/** Converts a 16 bit signed integer from CPU to file.   */
	#define GX_C2F_I16(x)	(x)
	/** Converts a 16 bit unsigned integer from CPU to file. */
	#define GX_C2F_U16(x)	(x)
	/** Converts a 32 bit signed integer from CPU to file.   */
	#define GX_C2F_I32(x)	(x)
	/** Converts a 32 bit unsigned integer from CPU to file. */
	#define GX_C2F_U32(x)	(x)
	/** Converts a 64 bit signed integer from CPU to file.   */
	#define GX_C2F_I64(x)	(x)
	/** Converts a 64 bit unsigned integer from CPU to file. */
	#define GX_C2F_U64(x)	(x)

/* FILE to CPU */
	/** Converts an 8 bit signed integer from file to CPU.   */
	#define GX_F2C_I8(x)	(x)
	/** Converts an 8 bit unsigned integer from file to CPU. */
	#define GX_F2C_U8(x)	(x)
	/** Converts a 16 bit signed integer from file to CPU.   */
	#define GX_F2C_I16(x)	(x)
	/** Converts a 16 bit unsigned integer from file to CPU. */
	#define GX_F2C_U16(x)	(x)
	/** Converts a 32 bit signed integer from file to CPU.   */
	#define GX_F2C_I32(x)	(x)
	/** Converts a 32 bit unsigned integer from file to CPU. */
	#define GX_F2C_U32(x)	(x)
	/** Converts a 64 bit signed integer from file to CPU.   */
	#define GX_F2C_I64(x)	(x)
	/** Converts a 64 bit unsigned integer from file to CPU. */
	#define GX_F2C_U64(x)	(x)
#endif
/******************************************************************************/
/* General byte swap */
#ifdef __cplusplus
	/** Swaps bytes of a 16 bit unsigned integer. */
	inline gxu16 GX_BSWAP_U16(gxu16 x) { return gxu16((x >> 8) | (x << 8)); }
	/** Swaps bytes of a 32 bit unsigned integer. */
	inline gxu32 GX_BSWAP_U32(gxu32 x) { return (x >> 24) | ((x >> 8)&0xFF00) | ((x & 0xFF00) << 8) | (x << 24); }
	/** Swaps bytes of a 64 bit unsigned integer. */
	inline gxu64 GX_BSWAP_U64(gxu64 x) { return (gxu64)GX_BSWAP_U32((gxu32)(x >> 32)) | ((gxu64)GX_BSWAP_U32((gxu32)x) << 32); }

	/** Swaps bytes of a 16 bit signed integer. */
	#define GX_BSWAP_I16(x)	((gxi16)GX_BSWAP_U16(x))
	/** Swaps bytes of a 32 bit signed integer. */
	#define GX_BSWAP_I32(x)	((gxi32)GX_BSWAP_U32(x))
	/** Swaps bytes of a 64 bit signed integer. */
	#define GX_BSWAP_I64(x)	((gxi64)GX_BSWAP_U64(x))


	#ifdef GX_BIG_ENDIAN
	/* CPU to FILE */
		/** Converts an 8 bit signed integer from CPU to file.   */
		#define GX_C2F_I8(x)	(x)
		/** Converts an 8 bit unsigned integer from CPU to file. */
		#define GX_C2F_U8(x)	(x)
		/** Converts a 16 bit signed integer from CPU to file.   */
		#define GX_C2F_I16(x)	GX_BSWAP_I16(x)
		/** Converts a 16 bit unsigned integer from CPU to file. */
		#define GX_C2F_U16(x)	GX_BSWAP_U16(x)
		/** Converts a 32 bit signed integer from CPU to file.   */
		#define GX_C2F_I32(x)	GX_BSWAP_I32(x)
		/** Converts a 32 bit unsigned integer from CPU to file. */
		#define GX_C2F_U32(x)	GX_BSWAP_U32(x)
		/** Converts a 64 bit signed integer from CPU to file.   */
		#define GX_C2F_I64(x)	GX_BSWAP_I64(x)
		/** Converts a 64 bit unsigned integer from CPU to file. */
		#define GX_C2F_U64(x)	GX_BSWAP_U64(x)

	/* FILE to CPU */
		/** Converts an 8 bit signed integer from file to CPU.   */
		#define GX_F2C_I8(x)	(x)
		/** Converts an 8 bit unsigned integer from file to CPU. */
		#define GX_F2C_U8(x)	(x)
		/** Converts a 16 bit signed integer from file to CPU.   */
		#define GX_F2C_I16(x)	GX_BSWAP_I16(x)
		/** Converts a 16 bit unsigned integer from file to CPU. */
		#define GX_F2C_U16(x)	GX_BSWAP_U16(x)
		/** Converts a 32 bit signed integer from file to CPU.   */
		#define GX_F2C_I32(x)	GX_BSWAP_I32(x)
		/** Converts a 32 bit unsigned integer from file to CPU. */
		#define GX_F2C_U32(x)	GX_BSWAP_U32(x)
		/** Converts a 64 bit signed integer from file to CPU.   */
		#define GX_F2C_I64(x)	GX_BSWAP_I64(x)
		/** Converts a 64 bit unsigned integer from file to CPU. */
		#define GX_F2C_U64(x)	GX_BSWAP_U64(x)
	#endif
#endif
/******************************************************************************/
#if defined(GX_DOTNET)	/*(*/

#if defined(GX_DOTNET_20_OLDSYNTAX) || defined(GX_DOTNET_20)
			#define gxFuncThrowsError		
		#else
			#define gxFuncThrowsError	throw(gxError)			
#endif

#ifndef GX_DOTNET_20
	#define GX_TYPEID(_type) __typeof(_type)	
	#define GX_REF_CLASS(_var) *_var	
	#define GX_REF_STRUCT(_var) *_var
	#define GX_REF_UNMANAGED_STRUCT(_var) &_var
	#define GX_NULLPTR 0	
	#define GX_M ->
	#define GX_MS ->
	#define GX_INDIRECTION_GC(_type, _var) _type __gc *_var	
	#define GX_INDIRECTION GX_INDIRECTION_GC	
	#define GX_INDIRECTION_NOGC(_type) _type __nogc *	
	#define GX_RETVAL_CLASS(_type) _type __gc *
	#define GX_INDIRECTION1(_type) _type __gc *
	#define GX_DELEGATE __delegate
#else
	#define GX_TYPEID(_type) _type::typeid	
	#define GX_REF_CLASS(_var) ^_var
	#define GX_REF_STRUCT(_var) %_var
	#define GX_REF_UNMANAGED_STRUCT(_var) &_var
	#define GX_NULLPTR nullptr
	#define GX_M -> 
	#define GX_MS .
	#define GX_INDIRECTION_GC(_type, _var) _type ^_var	
	#define GX_INDIRECTION GX_INDIRECTION_GC	
	#define GX_INDIRECTION_NOGC(_type) _type*	
	#define GX_RETVAL_CLASS(_type) _type^
	#define GX_INDIRECTION1(_type) _type^
	#define GX_DELEGATE delegate
#endif
	#define GX_ENUM_PATH(e)	e:: 

	#if !defined(GX_NAMESPACES) && !defined(GX_MANUAL)
		/* .net requires namespaces */
		#define GX_NAMESPACES
	#endif

	#if defined(GX_MANUAL)
		#define NO_GX_FUNCTIONS
	#endif

	#using <mscorlib.dll>
	#include <wchar.h>

	#undef  GX_ASCII
	#define GX_UNICODE			1
	#define GXINDATA			1
	#define GXOUTDATA			1

	#define GX_DEFARG(a)

#ifdef GX_DOTNET_20	
	#define GX_STRUCT			public value struct
	#define GX_ENUM				public enum class
	#define GX_CLASS			public ref class
	#define GX_CLASS_DECL		ref class
	#define GX_STRUCT_DECL		value struct
	#define GX_CONST
	#define GX_PSTRUCT			private struct
	#define GX_PCLASS			private ref class
#else 
	#define GX_STRUCT			public __value struct
	#define GX_ENUM				public __value enum
	#define GX_CLASS			public __gc class
#ifdef GX_DOTNET_20_OLDSYNTAX
	#define GX_CLASS_DECL		__gc class
	#define GX_STRUCT_DECL		__value struct
#else
	#define GX_CLASS_DECL		GX_CLASS
	#define GX_STRUCT_DECL		GX_STRUCT
#endif
	#define GX_CONST
	#define GX_PSTRUCT			private __value struct
	#define GX_PCLASS			private __gc class
#endif

#else	/*)( !GX_DOTNET */

	#if defined(__cplusplus)
		#define GX_DEFARG(a)	= a
	#else
		#define GX_DEFARG(a)
		#ifndef __KERNEL__
			#define inline			static
			#ifndef bool
				#define bool		int
			#endif
			#ifndef true
				#define true		1
			#endif
			#ifndef false
				#define false		0
			#endif
		#endif
		#ifndef NO_GX_CLASSES
			#define NO_GX_CLASSES
		#endif
		#ifndef NO_GXLIB_CLASSES
			#define NO_GXLIB_CLASSES
		#endif
		#ifndef NO_GX_EXCEPTIONS
			#define NO_GX_EXCEPTIONS
		#endif
	#endif

	#define __nogc
	
	#define GX_STRUCT			struct
	#define GX_ENUM				enum
	#define GX_CLASS			class
	#define GX_CLASS_DECL		class
	#define GX_STRUCT_DECL		struct
	#define GX_CONST			const
	#define GX_PSTRUCT			struct
	#define GX_PCLASS			class
	#define GX_REF_CLASS(_var) &_var	
	#define GX_REF_STRUCT(_var) &_var
	#define GX_INDIRECTION GX_INDIRECTION_GC	
	#define GX_INDIRECTION_GC(_type, _var) _type *_var	
	#define GX_INDIRECTION_NOGC(_type) _type*	
	#define GX_RETVAL_CLASS(_type) _type
	#define GX_INDIRECTION1(_type) _type*
	#define GX_NULLPTR 0
	#define GX_M .
	#define GX_MS .
	#define gxFuncThrowsError	throw(gxError)
	#define GX_ENUM_PATH(e)	

	#if defined(NO_GX_CLASSES) || defined(NO_GX_STL) || defined(__KERNEL__)

		#undef GX_ASCII
		#undef GX_UNICODE
		#undef GXINDATA
		#undef GXOUTDATA

	#elif !defined(GX_SWIG)

		#include <iostream>
		#include <string>
		#include <vector>

		#define GX_ASCII		1
		#define GX_UNICODE		1
		#undef  GXINDATA
		#undef  GXOUTDATA

	#endif

#endif	/*)*/
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(pop)
#endif
/******************************************************************************/
#endif	/* GX_TYPES_INCL */
/******************************************************************************/
