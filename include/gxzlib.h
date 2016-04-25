/******************************************************************************
 * GX ZLIB header file - V7.2.10
 *
 * 2005-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
/** \file
 * <b> Compression handling interface </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy to program
 * interface to the hardware devices.
 *
 * This file contains the descriptions of classes and functions of the compression handling module.
 */
/******************************************************************************/
#ifndef GXZLIB_INCL
#define GXZLIB_INCL
/******************************************************************************/
#include "gxsd.h"
#if defined(WIN32) && !defined(GX_DOTNET)
#include <windows.h>
#endif
#include <assert.h>
/******************************************************************************/
#ifdef GX_NAMESPACES
namespace gx {
#endif

#ifdef GX_DOTNET
#pragma unmanaged
#endif

/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL) /*(*/
/******************************************************************************/
/** Call codes for ZLIB and MiniZIP operations. */
enum {
	GX_CALL_GZCOMPRESS	= GX_CALL_GROUP_GX_ZLIB,	/**< Compress a memory area. */
	GX_CALL_GZUNCOMPRESS,			/**< Uncompress the compressed memory area. */

	GX_CALL_CREATEGZ,				/**< Create a .gz file. */
	GX_CALL_OPENGZ,					/**< Open a .gz file. */
	GX_CALL_CLOSEGZ,				/**< Close an opened or created .gz file. */
	GX_CALL_READGZ,					/**< Read data from an opened .gz file. */
	GX_CALL_WRITEGZ,				/**< Write data to a created .gz file. */

	GX_CALL_CREATEZIP,				/**< Create a .zip file. */
	GX_CALL_OPENZIP,				/**< Open a .zip file. */
	GX_CALL_CLOSEZIP,				/**< Close an opened or created .zip file. */
	GX_CALL_GETZIPINFO,				/**< Give information about an opened .zip file. */
	GX_CALL_GETZIPCOMMENT,			/**< Query the global comment of the .zip file. */

	GX_CALL_FIRSTFILEINZIP,			/**< Set marker to the first file in the ZIP. */
	GX_CALL_NEXTFILEINZIP,			/**< Set marker to the next file in the ZIP. */
	GX_CALL_LOCATEFILEINZIP,		/**< Set marker to the specified file in the ZIP. */
	GX_CALL_FILEINFOINZIP,			/**< Give information about a marked file in the ZIP. */

	GX_CALL_OPENFILEINZIP,			/**< Open the marked file in the ZIP for reading. */
	GX_CALL_READFROMFILEINZIP,		/**< Read data from the opened file in the ZIP. */
	GX_CALL_READLEXFIELDZIP,		/**< Read the local extra field of the marked file in the ZIP. */

	GX_CALL_CREATEFILEINZIP,		/**< Create a new file in the archive for writing. */
	GX_CALL_WRITETOFILEINZIP,		/**< Write data to the created file in the archive. */
	GX_CALL_CLOSEFILEINZIP,			/**< Close (and flush) an opened or created file in the archive. */
	GX_CALL_GETINITIALZIPCRC,		/**< Return the value of the initial CRC. */
	GX_CALL_CALCULATEZIPCRC,		/**< Calculate the CRC32 for encrypted files. */

	// Unicode extensions
	GX_CALL_CREATEGZW	= GX_CALL_GROUP_GX_ZLIB + 0x100, /**< Create a .gz file. */
	GX_CALL_OPENGZW,				/**< Open a .gz file. */
	GX_CALL_CREATEZIPW,				/**< Create a .zip file. */
	GX_CALL_OPENZIPW,				/**< Open a .zip file. */
	GX_CALL_CLOSEZIPW,				/**< Close an opened or created .zip file. */
	GX_CALL_GETZIPCOMMENTW,			/**< Query the global comment of the .zip file. */

	GX_CALL_FIRSTFILEINZIPW,		/**< Set marker to the first file in the ZIP. */
	GX_CALL_NEXTFILEINZIPW,			/**< Set marker to the next file in the ZIP. */
	GX_CALL_LOCATEFILEINZIPW,		/**< Set marker to the specified file in the ZIP. */
	GX_CALL_FILEINFOINZIPW,			/**< Give information about a marked file in the ZIP. */

	GX_CALL_OPENFILEINZIPW,			/**< Open the marked file in the ZIP for reading. */
	GX_CALL_CREATEFILEINZIPW,		/**< Create a new file in the archive for writing. */

	GX_CALL_CREATEZIPINMEMORY,		/**< Create a .zip file in memory. */
	GX_CALL_GETZIPINMEMORY,			/**< Get the created .zip file in memory. */
	GX_CALL_OPENZIPINMEMORY,		/**< Open a .zip file in memory. */
};
#endif /* GX_SWIGIF GX_MANUAL )*/

#ifdef GX_DOTNET
#pragma managed
#endif

/** Compression levels (0-9). */
GX_ENUM GX_ZLEVELS {
	GX_Z_NO_COMPRESSION	=	0,		/**< No compression (0). */
	GX_Z_BEST_SPEED		=	1,		/**< Best speed (1). */
	GX_Z_BEST_COMPRESSION	=	9,	/**< Best compression (9). */
	GX_Z_DEFAULT_COMPRESSION = -1	/**< Default compression level. */
};

/** Compression strategies. */
GX_ENUM GX_ZSTRATEGIES {
	GX_Z_FILTERED		= 1,		/**< Force more Huffman coding and less string matching. */
	GX_Z_HUFFMAN_ONLY	= 2,		/**< Force Huffman encoding only (no string match). */
	GX_Z_RLE			= 3,		/**< RLE is fast as Huffman, but give better compression for PNG image data. */
	GX_Z_FIXED			= 4,		/**< Prevents the use of dynamic Huffman codes, allowing for a simpler decoder. */
	GX_Z_DEFAULT_STRATEGY = 0		/**< Use for normal data. */
};

/** Compression methods. */
GX_ENUM GX_ZMETHODS {
	GX_Z_DEFLATED	=	8			/**< The deflate compression method (the only one supported). */
};

/** Create modes for gx_createzip() function. */
GX_ENUM GX_CREATEZIPMODES {
	GX_ZIP_CREATE	= 0,	/**< Create a new ZIP file. */
	GX_ZIP_CREATEAFTER,		/**< The ZIP will be created at the end of the file. */
	GX_ZIP_ADDINZIP			/**< Add files to an existing archive. */
};
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)	/*(*/
/** Parameter structure for the gx_gzcompress() function. */
struct GX_PARM_GZCOMPRESS {
	void *target;			/**< Pointer to an allocated area where the function writes the compressed data. */
	int tgtlen;				/**< Length of the allocated area. The function updates it with the compressed length. */
	const void *source;		/**< Pointer to an uncompressed data. */
	int srclen;				/**< Length of the uncompressed data. */
	int level;				/**< Compression level 0-9 (GX_ZLEVELS). */
};

/** Parameter structure for the gx_gzuncompress() function. */
struct GX_PARM_GZUNCOMPRESS {
	void *target;			/**< Pointer to an allocated area where the function writes the uncompressed data. */
	int tgtlen;				/**< Length of the allocated area. The function updates it with the uncompressed length. */
	const void *source;		/**< Pointer to a compressed data. */
	int srclen;				/**< Length of the compressed data. */
};

/** Parameter structure for the gx_creategz() function. */
struct GX_PARM_CREATEGZ {
	const char *filename;	/**< Path and name of the .gz file. */
	int level;				/**< Compression level. */
	int strategy;			/**< Compression strategy. */
};

/** Parameter structure for the gx_creategz() function. */
struct GX_PARM_CREATEGZW {
	const wchar_t *filename;/**< Path and name of the .gz file. */
	int level;				/**< Compression level. */
	int strategy;			/**< Compression strategy. */
};

/** Parameter structure for the gx_opengz() function. */
struct GX_PARM_OPENGZ {
	const char *filename;	/**< Path and name of the .gz file. */
};

/** Parameter structure for the gx_opengz() function. */
struct GX_PARM_OPENGZW {
	const wchar_t *filename;	/**< Path and name of the .gz file. */
};

/** Parameter structure for the gx_readgz() function. */
struct GX_PARM_READGZ {
	void *buffer;			/**< Pointer to an allocated area. */
	int buflen;				/**< Length of the allocated area. The function updates it with the read data. */
};

/** Parameter structure for the gx_writegz() function. */
struct GX_PARM_WRITEGZ {
	const void *buffer;		/**< Pointer to source data. */
	int buflen;				/**< Length of area. The function updates it with the written data. */
};

/** Parameter structure for the gx_createzip() function. */
struct GX_PARM_CREATEZIP {
	const char *filename;	/**< Path and name of the ZIP file. */
	int mode;				/**< Create modes (see \ref GX_CREATEZIPMODES). */
};

/** Parameter structure for the gx_createzip() function. */
struct GX_PARM_CREATEZIPW {
	const wchar_t *filename;/**< Path and name of the ZIP file. */
	int mode;				/**< Create modes (see \ref GX_CREATEZIPMODES). */
};

/** Parameter structure for the gx_openzip() function. */
struct GX_PARM_OPENZIP {
	const char *filename;	/**< Path and name of the ZIP file. */
};

/** Parameter structure for the gx_openzipw() function. */
struct GX_PARM_OPENZIPW {
	const wchar_t *filename;	/**< Path and name of the ZIP file. */
};

/** Parameter structure for the gx_createzipinmemory() function. */
struct GX_PARM_CREATEZIPINMEMORY {
	int mode;					/**< Create modes (see \ref GX_CREATEZIPMODES). */
};

/** Parameter structure for the gx_getzipinmemory() function. */
struct GX_PARM_GETZIPINMEMORY {
	void **pbuffer;				/**< Pointer to the zip file in memory. */
	int* pbuflen;				/**< Pointer to the length of the zip file. */
};

/** Parameter structure for the gx_openzipinmemory() function. */
struct GX_PARM_OPENZIPINMEMORY {
	void *buffer;				/**< The zip file in memory. */
	int buflen;					/**< The length of the zip file. */
};

/** Parameter structure for the gx_closezip() function. */
struct GX_PARM_CLOSEZIP {
	const char *comment;	/**< Comment for the archive in write mode. */
};

/** Parameter structure for the gx_closezip() function. */
struct GX_PARM_CLOSEZIPW {
	const wchar_t *comment;	/**< Comment for the archive in write mode. */
};

/** Information structure for gx_getzipinfo() function. */
struct GX_PARM_GETZIPINFO {
	int nentries;			/**< Number of file entries in the archive. */
	int commentlen;			/**< Length of comment in bytes. */
};

/** Parameter structure for gx_getzipcomment() function. */
struct GX_PARM_GETZIPCOMMENT {
	char *target;			/**< Pointer to an allocated space where the functions writes the comment of the archive. */
	int tlen;				/**< Length of allocated space in bytes. */
};

/** Parameter structure for gx_getzipcomment() function. */
struct GX_PARM_GETZIPCOMMENTW {
	wchar_t *target;		/**< Pointer to an allocated space where the functions writes the comment of the archive. */
	int tlen;				/**< Length of allocated space in bytes. */
};

/** Information structure for file creator function. */
struct GX_ZIPFILEINFO {
	int tm_sec;				/**< Seconds after the minute [0-59] */
	int tm_min;				/**< Minutes after the hour [0-59] */
	int tm_hour;			/**< Hours since midnight [0-23] */
	int tm_mday;			/**< Day of the month [1-31] */
	int tm_mon;				/**< Months since January [0-11] */
	int tm_year;			/**< Years [1980-2044] */

	int dosdate;			/**< If it is 0, tm_xxx fields are used. */
	int internal_fa;		/**< Internal file attributes. */
	int external_fa;		/**< External file attributes. */
};

#ifndef __cplusplus
	/** ANSI C workaround. */
	typedef struct GX_ZIPFILEINFO GX_ZIPFILEINFO;
#endif

/** Parameter structure for gx_createfileinzip() function. */
struct GX_PARM_CREATEFILEINZIP {
	const char *filename;			/**< Name of the ZIP file. */
	const GX_ZIPFILEINFO *info;		/**< Information structure for file. It can be NULL. */
	const char *comment;			/**< Comment for the file in the ZIP. It can be NULL. */
	int level;						/**< Compression level (see \ref GX_ZLEVELS). */
	int strategy;					/**< Compression strategy (see \ref GX_ZSTRATEGIES). */
	const char *password;			/**< Password for file. It can be NULL. */
	unsigned int crc;				/**< CRC-32 value for the encrypted file. Set it to 0, if the files are not encrypted. */
	const void *exflocal;			/**< Local extra field. It can be NULL. */
	int exflocal_len;				/**< Length of local extra field in bytes. */
	const void *exfglobal;			/**< Global extra field. It can be NULL. */
	int exfglobal_len;				/**< Length of global extra field in bytes. */
};

/** Parameter structure for gx_createfileinzip() function. */
struct GX_PARM_CREATEFILEINZIPW {
	const wchar_t *filename;		/**< Name of the ZIP file. */
	const GX_ZIPFILEINFO *info;		/**< Information structure for file. It can be NULL. */
	const wchar_t *comment;			/**< Comment for the file in the ZIP. It can be NULL. */
	int level;						/**< Compression level (see \ref GX_ZLEVELS). */
	int strategy;					/**< Compression strategy (see \ref GX_ZSTRATEGIES). */
	const wchar_t *password;		/**< Password for file. It can be NULL. */
	unsigned int crc;				/**< CRC-32 value for the encrypted file. Set it to 0, if the files are not encrypted. */
	const void *exflocal;			/**< Local extra field. It can be NULL. */
	int exflocal_len;				/**< Length of local extra field in bytes. */
	const void *exfglobal;			/**< Global extra field. It can be NULL. */
	int exfglobal_len;				/**< Length of global extra field in bytes. */
};

/** Parameter structure for gx_writetofileinzip() function. */
struct GX_PARM_WRITETOFILEINZIP {
	const void *buffer;				/**< Pointer to memory area. */
	int buflen;						/**< Length of memory area in bytes. */
};

/** Detailed information structure. */
struct GX_ZIPFILEDETINFO {
	// in
	char *filename;			/**< Pointer to an allocated area where the function writes the name of the file. It can be NULL. */
	int filename_len;		/**< Length of filename in bytes. */
	void *gextrafield;		/**< Pointer to an allocated area where the function writes the global extra field. It can be NULL. */
	int gextrafield_len;	/**< Length of the gextrafield area in bytes. */
	char *comment;			/**< Pointer to an allocated area where the function writes the comment of the file. It can be NULL. */
	int comment_len;		/**< Length of comment in bytes. */
	// out
	int version;			/**< Version. */
	int version_needed;		/**< Version needed to extract. */
	int flag;				/**< General purpose bit flag. */
	int method;				/**< Compression method. */
	int dosdate;			/**< Last modified file date in DOS format. */
	unsigned int crc;		/**< CRC-32 value. */
	int compressed_size;	/**< Compressed size in bytes. */
	int uncompressed_size;	/**< Uncompressed size in bytes. */
	int size_filename;		/**< Filename length in bytes. */
	int size_file_extra;	/**< Global extra field length in bytes. */
	int size_file_comment;	/**< File comment length in bytes. */
	int disk_num_start;		/**< Disk number start. */
	int internal_fa;		/**< Internal file attributes. */
	int external_fa;		/**< External file attributes. */
	int tm_sec;				/**< Seconds after the minute [0-59] */
	int tm_min;				/**< Minutes after the hour [0-59] */
	int tm_hour;			/**< Hours since midnight [0-23] */
	int tm_mday;			/**< Day of the month [1-31] */
	int tm_mon;				/**< Months since January [0-11] */
	int tm_year;			/**< Years [1980-2044] */
};

#ifndef __cplusplus
	/** ANSI C workaround. */
	typedef struct GX_ZIPFILEDETINFO GX_ZIPFILEDETINFO;
#endif

/** Detailed information structure. */
struct GX_ZIPFILEDETINFOW {
	// in
	wchar_t *filename;		/**< Pointer to an allocated area where the function writes the name of the file. It can be NULL. */
	int filename_len;		/**< Length of filename in characters. */
	void *gextrafield;		/**< Pointer to an allocated area where the function writes the global extra field. It can be NULL. */
	int gextrafield_len;	/**< Length of the gextrafield area in bytes. */
	wchar_t *comment;		/**< Pointer to an allocated area where the function writes the comment of the file. It can be NULL. */
	int comment_len;		/**< Length of comment in characters. */
	// out
	int version;			/**< Version. */
	int version_needed;		/**< Version needed to extract. */
	int flag;				/**< General purpose bit flag. */
	int method;				/**< Compression method. */
	int dosdate;			/**< Last modified file date in DOS format. */
	unsigned int crc;		/**< CRC-32 value. */
	int compressed_size;	/**< Compressed size in bytes. */
	int uncompressed_size;	/**< Uncompressed size in bytes. */
	int size_filename;		/**< Filename length in characters. */
	int size_file_extra;	/**< Global extra field length in bytes. */
	int size_file_comment;	/**< File comment length in characters. */
	int disk_num_start;		/**< Disk number start. */
	int internal_fa;		/**< Internal file attributes. */
	int external_fa;		/**< External file attributes. */
	int tm_sec;				/**< Seconds after the minute [0-59] */
	int tm_min;				/**< Minutes after the hour [0-59] */
	int tm_hour;			/**< Hours since midnight [0-23] */
	int tm_mday;			/**< Day of the month [1-31] */
	int tm_mon;				/**< Months since January [0-11] */
	int tm_year;			/**< Years [1980-2044] */
};

#ifndef __cplusplus
	/** ANSI C workaround. */
	typedef struct GX_ZIPFILEDETINFOW GX_ZIPFILEDETINFOW;
#endif

/** Parameter structure for gx_locatefileinzip() function. */
struct GX_PARM_LOCATEFILEINZIP {
	GX_ZIPFILEDETINFO *finfo;	/**< Pointer to the information structure. */
	const char *filename;		/**< Name of the file in the ZIP. */
	int casesensitivity;		/**< 1: case sensitivity, 2: case insensitivity, 0: default (like 1 on Unix, 2 on Windows) */
};

/** Parameter structure for gx_locatefileinzip() function. */
struct GX_PARM_LOCATEFILEINZIPW {
	GX_ZIPFILEDETINFOW *finfo;	/**< Pointer to the information structure. */
	const wchar_t *filename;	/**< Name of the file in the ZIP. */
	int casesensitivity;		/**< 1: case sensitivity, 2: case insensitivity, 0: default (like 1 on Unix, 2 on Windows) */
};

/** Parameter structure for gx_openfileinzip() function. */
struct GX_PARM_OPENFILEINZIP {
	int method;					/**< Compression method (see \ref GX_ZMETHODS). */
	int level;					/**< Compression level (see \ref GX_ZLEVELS). */
	const char *password;		/**< Password for the archive if needed. */
};

/** Parameter structure for gx_openfileinzip() function. */
struct GX_PARM_OPENFILEINZIPW {
	int method;					/**< Compression method (see \ref GX_ZMETHODS). */
	int level;					/**< Compression level (see \ref GX_ZLEVELS). */
	const wchar_t *password;	/**< Password for the archive if needed. */
};

/** Parameter structure for gx_readfromfileinzip() function. */
struct GX_PARM_READFROMFILEINZIP {
	void *buffer;				/**< Pointer to the target buffer. */
	int buflen;					/**< Length of the target buffer in bytes. */
};

/** Parameter structure for gx_calculatezipcrc() function. */
struct GX_PARM_CALCULATEZIPCRC {
	unsigned int crc;			/**< The initial CRC-32 value. */
	const void *buffer;			/**< Pointer to the buffer. */
	int buflen;					/**< Length of the buffer in bytes. */
};

/** Parameter structure for gx_getinitialzipcrc() function. */
struct GX_PARM_GETINITIALZIPCRC {
	unsigned int crc;			/**< The initial CRC-32 value. */
};

/** Parameter structure for gx_readlexfieldzip() function. */
struct GX_PARM_READLEXFIELDZIP {
	void *buffer;				/**< Pointer to an allocated area. */
	int buflen;					/**< Length of the buffer in bytes. */
};

#endif /* GX_SWIGIF GX_MANUAL )*/

/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/******************************************************************************/
/** \addtogroup gx_group_zlib
 * @{
 */
/******************************************************************************/

/******************************************************************************/
/** Compresses a memory area.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area where the function writes the
 *				compressed data.
 * @param tgtlen Length of the allocated area.  The function updates it with
 *				the length of the compressed data.
 * @param source Pointer to an uncompressed data.
 * @param srclen Length of the uncompressed data.
 * @param level Compression level 0-9 (see \ref GX_ZLEVELS).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzcompress(gxHANDLE handle, void *target, int *tgtlen,
					const void *source, int srclen, int level) {

	struct GX_PARM_GZCOMPRESS gzc;
	int st;

	assert(target && tgtlen && (*tgtlen > 0) && source && (srclen > 0));

	gzc.target = target;
	gzc.tgtlen = *tgtlen;
	gzc.source = source;
	gzc.srclen = srclen;
	gzc.level = level;
	st = gx_call(handle, GX_CALL_GZCOMPRESS, &gzc);
	if(st) *tgtlen = gzc.tgtlen;
	return st;
}
/******************************************************************************/
/** Compresses a memory area.
 *
 * @param target Pointer to an allocated area where the function writes the
 *				compressed data.
 * @param tgtlen Length of the allocated area.  The function updates it with
 *				the length of the compressed data.
 * @param source Pointer to an uncompressed data.
 * @param srclen Length of the uncompressed data.
 * @param level Compression level 0-9 (see \ref GX_ZLEVELS).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzcompressd(void *target, int *tgtlen,
					const void *source, int srclen, int level) {

	return gx_gzcompress(gx_direct(GX_CALL_GROUP_GX_ZLIB),
								target, tgtlen, source, srclen, level);
}

#ifdef __cplusplus
/******************************************************************************/
/** Compresses a memory area.
 *
 * @param target Pointer to an allocated area where the function writes the
 *				compressed data.
 * @param tgtlen Length of the allocated area.  The function updates it with
 *				the length of the compressed data.
 * @param source Pointer to an uncompressed data.
 * @param srclen Length of the uncompressed data.
 * @param level Compression level 0-9 (see \ref GX_ZLEVELS).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzcompress(void *target, int *tgtlen,
					const void *source, int srclen, int level) {

	return gx_gzcompressd(target, tgtlen, source, srclen, level);
}
#endif

/******************************************************************************/
/** Decompresses a compressed data from memory.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area where the function writes the
 *				uncompressed data.
 * @param tgtlen Length of the allocated area. The function updates it with
 *				the length of the uncompressed data.
 * @param source Pointer to a compressed data.
 * @param srclen Length of the compressed data.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzuncompress(gxHANDLE handle, void *target, int *tgtlen,
					const void *source, int srclen) {

	struct GX_PARM_GZUNCOMPRESS gzu;
	int st;

	assert(target && tgtlen && (*tgtlen > 0) && source && (srclen > 0));

	gzu.target = target;
	gzu.tgtlen = *tgtlen;
	gzu.source = source;
	gzu.srclen = srclen;
	st = gx_call(handle, GX_CALL_GZUNCOMPRESS, &gzu);
	if(st) *tgtlen = gzu.tgtlen;
	return st;
}
/******************************************************************************/
/** Decompresses a compressed data from memory.
 *
 * @param target Pointer to an allocated area where the function writes the
 *				uncompressed data.
 * @param tgtlen Length of the allocated area. The function updates it with
 *				the length of the uncompressed data.
 * @param source Pointer to a compressed data.
 * @param srclen Length of the compressed data.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzuncompressd(void *target, int *tgtlen,
					const void *source, int srclen) {

	return gx_gzuncompress(gx_direct(GX_CALL_GROUP_GX_ZLIB),
								target, tgtlen, source, srclen);
}

#ifdef __cplusplus
/******************************************************************************/
/** Decompresses a compressed data from memory.
 *
 * @param target Pointer to an allocated area where the function writes the
 *				uncompressed data.
 * @param tgtlen Length of the allocated area. The function updates it with
 *				the length of the uncompressed data.
 * @param source Pointer to a compressed data.
 * @param srclen Length of the compressed data.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_gzuncompress(void *target, int *tgtlen,
					const void *source, int srclen) {
	return gx_gzuncompressd(target, tgtlen, source, srclen);
}
#endif

/******************************************************************************/
/** Creates a .gz file (Unicode version).
 *
 * Use it when you can compress data into a single file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @param level Compression level (see \ref GX_ZLEVELS).
 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_creategz(gxHANDLE handle, const wchar_t *filename, int level, int strategy) {
	struct GX_PARM_CREATEGZW cgz;
	assert(filename);
	cgz.filename = filename;
	cgz.level = level;
	cgz.strategy = strategy;
	return gx_call(handle, GX_CALL_CREATEGZW, &cgz);
}

/******************************************************************************/
/** Creates a .gz file (ASCII version).
 *
 * Use it when you can compress data into a single file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @param level Compression level (see \ref GX_ZLEVELS).
 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_creategza(gxHANDLE handle, const char *filename, int level, int strategy) {
	struct GX_PARM_CREATEGZ cgz;
	assert(filename);
	cgz.filename = filename;
	cgz.level = level;
	cgz.strategy = strategy;
	return gx_call(handle, GX_CALL_CREATEGZ, &cgz);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a .gz file (ASCII version).
 *
 * Use it when you can compress data into a single file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @param level Compression level (see \ref GX_ZLEVELS).
 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_creategz(gxHANDLE handle, const char *filename, int level, int strategy) {
	return gx_creategza(handle, filename, level, strategy);
}
#endif

/******************************************************************************/
/** Opens the .gz file (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_opengz(gxHANDLE handle, const wchar_t *filename) {
	struct GX_PARM_OPENGZW ogz;
	assert(filename);
	ogz.filename = filename;
	return gx_call(handle, GX_CALL_OPENGZW, &ogz);
}

/******************************************************************************/
/** Opens the .gz file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_opengza(gxHANDLE handle, const char *filename) {
	struct GX_PARM_OPENGZ ogz;
	assert(filename);
	ogz.filename = filename;
	return gx_call(handle, GX_CALL_OPENGZ, &ogz);
}

#ifdef __cplusplus
/******************************************************************************/
/** Opens the .gz file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the .gz file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_opengz(gxHANDLE handle, const char *filename) {
	return gx_opengza(handle, filename);
}
#endif

/******************************************************************************/
/** Closes an opened or created .gz file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_closegz(gxHANDLE handle) {
	return gx_call(handle, GX_CALL_CLOSEGZ, (void *)0);
}

/******************************************************************************/
/** Reads data from an opened .gz file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param buffer Pointer to an allocated area where the function reads data.
 * @param buflen Length of the allocated area, the function updates it with
 *			length of unpacked data.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_readgz(gxHANDLE handle, void *buffer, int *buflen) {
	struct GX_PARM_READGZ rgz;
	int st;
	assert(buffer && buflen);
	rgz.buffer = buffer;
	rgz.buflen = *buflen;
	st = gx_call(handle, GX_CALL_READGZ, &rgz);
	if(st) *buflen = rgz.buflen;
	return st;
}

/******************************************************************************/
/** Writes data to a created .gz file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param buffer Pointer to an unpacked data.
 * @param buflen Length of the unpacked data.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_writegz(gxHANDLE handle, const void *buffer, int buflen) {
	struct GX_PARM_WRITEGZ wgz;
	assert(buffer && buflen);
	wgz.buffer = buffer;
	wgz.buflen = buflen;
	return gx_call(handle, GX_CALL_WRITEGZ, &wgz);
}

/******************************************************************************/
/** Creates a ZIP file (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createzip(gxHANDLE handle, const wchar_t *filename, int mode) {
	struct GX_PARM_CREATEZIPW czip;
	assert(filename);
	czip.filename = filename;
	czip.mode = mode;
	return gx_call(handle, GX_CALL_CREATEZIPW, &czip);
}

/******************************************************************************/
/** Creates a ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createzipa(gxHANDLE handle, const char *filename, int mode) {
	struct GX_PARM_CREATEZIP czip;
	assert(filename);
	czip.filename = filename;
	czip.mode = mode;
	return gx_call(handle, GX_CALL_CREATEZIP, &czip);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createzip(gxHANDLE handle, const char *filename, int mode) {
	return gx_createzipa(handle, filename, mode);
}
#endif

/******************************************************************************/
/** Opens a ZIP file (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openzip(gxHANDLE handle, const wchar_t *filename) {
	struct GX_PARM_OPENZIPW ozip;
	assert(filename);
	ozip.filename = filename;
	return gx_call(handle, GX_CALL_OPENZIPW, &ozip);
}

/******************************************************************************/
/** Opens a ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openzipa(gxHANDLE handle, const char *filename) {
	struct GX_PARM_OPENZIP ozip;
	assert(filename);
	ozip.filename = filename;
	return gx_call(handle, GX_CALL_OPENZIP, &ozip);
}

#ifdef __cplusplus
/******************************************************************************/
/** Opens a ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param filename Path and name of the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openzip(gxHANDLE handle, const char *filename) {
	return gx_openzipa(handle, filename);
}
#endif

/******************************************************************************/
/** Creates a ZIP file in memory.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createzipinmemory(gxHANDLE handle, int mode) {
	struct GX_PARM_CREATEZIPINMEMORY czip;
	czip.mode = mode;
	return gx_call(handle, GX_CALL_CREATEZIPINMEMORY, &czip);
}

/******************************************************************************/
/** Get the created ZIP file in memory.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param pbuffer Pointer to the ZIP file in memory.
 * @param pbuflen Pointer to the length of the ZIP file in memory.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getzipinmemory(gxHANDLE handle, void** pbuffer, int* pbuflen) {
	struct GX_PARM_GETZIPINMEMORY zip;
	assert(pbuffer);
	assert(pbuflen);
	zip.pbuffer = pbuffer;
	zip.pbuflen = pbuflen;
	return gx_call(handle, GX_CALL_GETZIPINMEMORY, &zip);
}

/******************************************************************************/
/** Opens a ZIP file in memory.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param buffer The ZIP file in memory.
 * @param buflen The length of the ZIP file in memory.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openzipinmemory(gxHANDLE handle, void* buffer, int buflen) {
	struct GX_PARM_OPENZIPINMEMORY ozip;
	assert(buffer);
	assert(buflen);
	ozip.buffer = buffer;
	ozip.buflen = buflen;
	return gx_call(handle, GX_CALL_OPENZIPINMEMORY, &ozip);
}


/******************************************************************************/
/** It closes an opened/created ZIP file (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param comment Comment string for the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_closezip(gxHANDLE handle, const wchar_t *comment) {
	struct GX_PARM_CLOSEZIPW czip;
	czip.comment = comment;
	return gx_call(handle, GX_CALL_CLOSEZIPW, &czip);
}

/******************************************************************************/
/** It closes an opened/created ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param comment Comment string for the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_closezipa(gxHANDLE handle, const char *comment) {
	struct GX_PARM_CLOSEZIP czip;
	czip.comment = comment;
	return gx_call(handle, GX_CALL_CLOSEZIP, &czip);
}

#ifdef __cplusplus
/******************************************************************************/
/** It closes an opened/created ZIP file (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param comment Comment string for the ZIP file.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_closezip(gxHANDLE handle, const char *comment = (const char *)0) {
	return gx_closezipa(handle, comment);
}
#endif

/******************************************************************************/
/** Gives informations about the opened ZIP file.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param info Pointer to an information structure where the function fills it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getzipinfo(gxHANDLE handle, struct GX_PARM_GETZIPINFO *info) {
	assert(info);
	return gx_call(handle, GX_CALL_GETZIPINFO, info);
}

/******************************************************************************/
/** Reads the comment from the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area where the function writes the
 *			comment string.
 * @param tlen Length of the allocated area in characters.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getzipcomment(gxHANDLE handle, wchar_t *target, int *tlen) {
	struct GX_PARM_GETZIPCOMMENTW gzc;
	int st;
	assert(target && tlen && (*tlen > 0));
	gzc.target = target;
	gzc.tlen = *tlen;
	st = gx_call(handle, GX_CALL_GETZIPCOMMENTW, &gzc);
	if(st) *tlen = gzc.tlen;
	return st;
}

/******************************************************************************/
/** Reads the comment from the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area where the function writes the
 *			comment string.
 * @param tlen Length of the allocated area.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getzipcommenta(gxHANDLE handle, char *target, int *tlen) {
	struct GX_PARM_GETZIPCOMMENT gzc;
	int st;
	assert(target && tlen && (*tlen > 0));
	gzc.target = target;
	gzc.tlen = *tlen;
	st = gx_call(handle, GX_CALL_GETZIPCOMMENT, &gzc);
	if(st) *tlen = gzc.tlen;
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Reads the comment from the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area where the function writes the
 *			comment string.
 * @param tlen Length of the allocated area.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getzipcomment(gxHANDLE handle, char *target, int *tlen) {
	return gx_getzipcommenta(handle, target, tlen);
}
#endif

/******************************************************************************/
/** Creates a file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param cfz Pointer to the description structure.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createfileinzip(gxHANDLE handle, struct GX_PARM_CREATEFILEINZIPW *cfz) {
	assert(cfz);
	return gx_call(handle, GX_CALL_CREATEFILEINZIPW, cfz);
}

/******************************************************************************/
/** Creates a file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param cfz Pointer to the description structure.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createfileinzipa(gxHANDLE handle, struct GX_PARM_CREATEFILEINZIP *cfz) {
	assert(cfz);
	return gx_call(handle, GX_CALL_CREATEFILEINZIP, cfz);
}

#ifdef __cplusplus
/******************************************************************************/
/** Creates a file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param cfz Pointer to the description structure.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_createfileinzip(gxHANDLE handle, struct GX_PARM_CREATEFILEINZIP *cfz) {
	return gx_createfileinzipa(handle, cfz);
}
#endif

/******************************************************************************/
/** Writes data to the current file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param buffer Pointer to data.
 * @param buflen Length of data in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_writetofileinzip(gxHANDLE handle, const void *buffer, int buflen) {
	struct GX_PARM_WRITETOFILEINZIP wfz;
	assert(buffer && (buflen > 0));
	wfz.buffer = buffer;
	wfz.buflen = buflen;
	return gx_call(handle, GX_CALL_WRITETOFILEINZIP, &wfz);
}

/******************************************************************************/
/** Closes the current file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_closefileinzip(gxHANDLE handle) {
	return gx_call(handle, GX_CALL_CLOSEFILEINZIP, (void *)0);
}

/******************************************************************************/
/** Sets marker to the first file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_firstfileinzip(gxHANDLE handle, GX_ZIPFILEDETINFOW *finfo) {
	assert(finfo);
	return gx_call(handle, GX_CALL_FIRSTFILEINZIPW, finfo);
}

/******************************************************************************/
/** Sets marker to the first file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_firstfileinzipa(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	return gx_call(handle, GX_CALL_FIRSTFILEINZIP, finfo);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets marker to the first file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_firstfileinzip(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	return gx_firstfileinzipa(handle, finfo);
}
#endif

/******************************************************************************/
/** Sets marker to the next file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_nextfileinzip(gxHANDLE handle, GX_ZIPFILEDETINFOW *finfo) {
	return gx_call(handle, GX_CALL_NEXTFILEINZIPW, finfo);
}

/******************************************************************************/
/** Sets marker to the next file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_nextfileinzipa(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	return gx_call(handle, GX_CALL_NEXTFILEINZIP, finfo);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets marker to the next file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_nextfileinzip(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	return gx_nextfileinzipa(handle, finfo);
}
#endif

/******************************************************************************/
/** Sets marker to the specified file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @param filename Name of the file in the archive.
 * @param casesensitivity Case sensitivity signification.
 *			It can be:
 *			 - 1: comparision is case sensitive (like wcscmp)
 *			 - 2: comparision is not case sensitive (like wcscmpi/wcscasecmp)
 *			 - 0: the default case sensitivity of the operation system
 *				  (like 1 on Unix, 2 on Windows)
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_locatefileinzip(gxHANDLE handle, GX_ZIPFILEDETINFOW *finfo,
							const wchar_t *filename, int casesensitivity) {
	struct GX_PARM_LOCATEFILEINZIPW lfz;
	assert(filename);
	lfz.finfo = finfo;
	lfz.filename = filename;
	lfz.casesensitivity = casesensitivity;
	return gx_call(handle, GX_CALL_LOCATEFILEINZIPW, &lfz);
}

/******************************************************************************/
/** Sets marker to the specified file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @param filename Name of the file in the archive.
 * @param casesensitivity Case sensitivity signification.
 *			It can be:
 *			 - 1: comparision is case sensitive (like strcmp)
 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
 *			 - 0: the default case sensitivity of the operation system
 *				  (like 1 on Unix, 2 on Windows)
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_locatefileinzipa(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo,
							const char *filename, int casesensitivity) {
	struct GX_PARM_LOCATEFILEINZIP lfz;
	assert(filename);
	lfz.finfo = finfo;
	lfz.filename = filename;
	lfz.casesensitivity = casesensitivity;
	return gx_call(handle, GX_CALL_LOCATEFILEINZIP, &lfz);
}

#ifdef __cplusplus
/******************************************************************************/
/** Sets marker to the specified file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @param filename Name of the file in the archive.
 * @param casesensitivity Case sensitivity signification.
 *			It can be:
 *			 - 1: comparision is case sensitive (like strcmp)
 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
 *			 - 0: the default case sensitivity of the operation system
 *				  (like 1 on Unix, 2 on Windows)
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_locatefileinzip(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo,
							const char *filename, int casesensitivity) {
	return gx_locatefileinzipa(handle, finfo, filename, casesensitivity);
}
#endif

/******************************************************************************/
/** Gives information about a marked file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_fileinfoinzip(gxHANDLE handle, GX_ZIPFILEDETINFOW *finfo) {
	assert(finfo);
	return gx_call(handle, GX_CALL_FILEINFOINZIPW, finfo);
}

/******************************************************************************/
/** Gives information about a marked file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_fileinfoinzipa(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	assert(finfo);
	return gx_call(handle, GX_CALL_FILEINFOINZIP, finfo);
}

#ifdef __cplusplus
/******************************************************************************/
/** Gives information about a marked file in the archive (ASCII version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param finfo Pointer to the information structure. The function will fill it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_fileinfoinzip(gxHANDLE handle, GX_ZIPFILEDETINFO *finfo) {
	return gx_fileinfoinzipa(handle, finfo);
}
#endif

/******************************************************************************/
/** Opens a marked file in the archive (Unicode version).
 *
 * @param handle Handle of an opened ZLIB module.
 * @param method Pointer to an integer. The function will update it to the compression method.
 * @param level Pointer to an integer. The function will update it to the compression level.
 * @param password Password string if the file is encoded. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openfileinzip(gxHANDLE handle, int *method, int *level, const wchar_t *password) {
	struct GX_PARM_OPENFILEINZIPW ofz;
	int st;
	ofz.method = ofz.level = 0;
	ofz.password = password;
	st = gx_call(handle, GX_CALL_OPENFILEINZIPW, &ofz);
	if(st) {
		if(method) *method = ofz.method;
		if(level) *level = ofz.level;
	}
	return st;
}

/******************************************************************************/
/** Opens a marked file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param method Pointer to an integer. The function will update it to the compression method.
 * @param level Pointer to an integer. The function will update it to the compression level.
 * @param password Password string if the file is encoded. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openfileinzipa(gxHANDLE handle, int *method, int *level, const char *password) {
	struct GX_PARM_OPENFILEINZIP ofz;
	int st;
	ofz.method = ofz.level = 0;
	ofz.password = password;
	st = gx_call(handle, GX_CALL_OPENFILEINZIP, &ofz);
	if(st) {
		if(method) *method = ofz.method;
		if(level) *level = ofz.level;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Opens a marked file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param method Pointer to an integer. The function will update it to the compression method.
 * @param level Pointer to an integer. The function will update it to the compression level.
 * @param password Password string if the file is encoded. It can be NULL.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_openfileinzip(gxHANDLE handle, int *method, int *level,
				const char *password = (const char *)0) {
	return gx_openfileinzipa(handle, method, level, password);
}
#endif

/******************************************************************************/
/** It reads a content from a marked file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param target Pointer to an allocated area.
 * @param tlen Length of the allocated area in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_readfromfileinzip(gxHANDLE handle, void *target, int *tlen) {
	struct GX_PARM_READFROMFILEINZIP rfz;
	int st;
	assert(target && tlen && (*tlen > 0));
	rfz.buffer = target;
	rfz.buflen = *tlen;
	st = gx_call(handle, GX_CALL_READFROMFILEINZIP, &rfz);
	if(st) *tlen = rfz.buflen;
	return st;
}

/******************************************************************************/
/** Calculates CRC-32 value from the specified buffer.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param crc The initial CRC-32 value (gx_getinitialzipcrc()), the function
 *            will be updated it.
 * @param buffer Pointer to data.
 * @param buflen Length of the data in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_calculatezipcrc(gxHANDLE handle, unsigned int *crc, const void *buffer, int buflen) {
	struct GX_PARM_CALCULATEZIPCRC czc;
	int st;
	assert(crc && buffer && (buflen > 0));
	czc.crc = *crc;
	czc.buffer = buffer;
	czc.buflen = buflen;
	st = gx_call(handle, GX_CALL_CALCULATEZIPCRC, &czc);
	if(st) *crc = czc.crc;
	return st;
}

/******************************************************************************/
/** Calculates CRC-32 value from the specified buffer.
 *
 * @param crc The initial CRC-32 value (gx_getinitialzipcrc()), the function
 *            will be updated it.
 * @param buffer Pointer to data.
 * @param buflen Length of the data in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_calculatezipcrcd(unsigned int *crc, const void *buffer, int buflen) {
	return gx_calculatezipcrc(gx_direct(GX_CALL_GROUP_GX_ZLIB), crc, buffer, buflen);
}

#ifdef __cplusplus
/******************************************************************************/
/** Calculates CRC-32 value from the specified buffer.
 *
 * @param crc The initial CRC-32 value (gx_getinitialzipcrc()), the function
 *            will be updated it.
 * @param buffer Pointer to data.
 * @param buflen Length of the data in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_calculatezipcrc(unsigned int *crc, const void *buffer, int buflen) {
	return gx_calculatezipcrcd(crc, buffer, buflen);
}
#endif

/******************************************************************************/
/** Returns the initial CRC.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param crc Pointer to an area, the function will be updated it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getinitialzipcrc(gxHANDLE handle, unsigned int *crc) {
	struct GX_PARM_GETINITIALZIPCRC gzc;
	int st;
	assert(crc);
	st = gx_call(handle, GX_CALL_GETINITIALZIPCRC, &gzc);
	if(st && crc) *crc = gzc.crc;
	return st;
}

/******************************************************************************/
/** Returns the initial CRC.
 *
 * @param crc Pointer to an area, the function will be updated it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getinitialzipcrcd(unsigned int *crc) {
	return gx_getinitialzipcrc(gx_direct(GX_CALL_GROUP_GX_ZLIB), crc);
}

#ifdef __cplusplus
/******************************************************************************/
/** Returns the initial CRC.
 *
 * @param crc Pointer to an area, the function will be updated it.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_getinitialzipcrc(unsigned int *crc) {
	return gx_getinitialzipcrcd(crc);
}
#endif

/******************************************************************************/
/** Reads the local extra field of the marked file in the archive.
 *
 * @param handle Handle of an opened ZLIB module.
 * @param buffer Pointer to data.
 * @param buflen Length of the data in bytes.
 * @return On error false is returned and the error code/string in the GX system
 *		  is set appropriately ( see gx_geterror() ). */
inline int gx_readlexfieldzip(gxHANDLE handle, void *buffer, int *buflen) {
	struct GX_PARM_READLEXFIELDZIP rlfz;
	int st;
	assert(buffer && buflen && (buflen > 0));
	rlfz.buffer = buffer;
	rlfz.buflen = *buflen;
	st = gx_call(handle, GX_CALL_READLEXFIELDZIP, &rlfz);
	if(st) *buflen = rlfz.buflen;
	return st;
};

/******************************************************************************/
/** @} */
/******************************************************************************/

#endif

/******************************************************************************/

#ifdef GX_DOTNET
#pragma managed
#endif

#ifndef NO_GX_CLASSES

/******************************************************************************/
/** Class for the GZip functions.
 *
 * The gxGZip class does not use properties.
 */
GX_CLASS gxGZip : public gxHandle {
public:
	/** Class initialization. */
	inline gxGZip() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxzlib", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxzlib", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
	}

	/** Checks if the handler of a module is valid.
	 *
	 * @return In case of existing handler the return value is non-zero. */
	inline bool IsValid(void) GX_CONST {
		return gxHandle::IsValid();
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Compresses a memory area.
	 *
	 * @param target Pointer to an allocated area where the function writes the
	 *				compressed data.
	 * @param tgtlen Length of the allocated area.  The function updates it with
	 *				the length of the compressed data.
	 * @param source Pointer to an uncompressed data.
	 * @param srclen Length of the uncompressed data.
	 * @param level Compression level 0-9 (see \ref GX_ZLEVELS).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Compress(void *target, int *tgtlen,
					const void *source, int srclen, int level) gxFuncThrowsError {
		assert(target && tgtlen && (*tgtlen > 0) && source && (srclen > 0));
		bool st = gx_gzcompress(*this, target, tgtlen,
					source, srclen,	level) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Compresses a memory area.
	 *
	 * @param source Pointer to an uncompressed data.
	 * @param maxlen Length of the allocated area. If the value is zero,
	 *		the size of the allocated memory will be length(source)*2+1024.
	 * @param level Compression level 0-9 (see \ref GX_ZLEVELS).
	 * @return The compressed data. If an error occurred the function will
	 *			thrown an exception. */
	inline gxOutData Compress(gxInData source, int maxlen, int level) gxFuncThrowsError {
		GX_GETDATA(source);
		GX_GETHANDLE(h);
		int targetlen = maxlen ? maxlen : (GX_DATALEN(source)*2+1024);
		void *target;
		if(!gx_globalalloc(&target, targetlen)) {
			GX_FREEDATA(source);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		if(!gx_gzcompress(h, target, &targetlen, GX_DATAPTR(source), GX_DATALEN(source), level)) {
			gx_globalfree(target);
			GX_FREEDATA(source);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(target, targetlen);
		gx_globalfree(target);
		GX_FREEDATA(source);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Uncompresses a compressed memory area.
	 *
	 * @param target Pointer to an allocated area where the function writes the
	 *				uncompressed data.
	 * @param tgtlen Length of the allocated area.  The function updates it with
	 *				the length of the uncompressed data.
	 * @param source Pointer to a compressed data.
	 * @param srclen Length of the compressed data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Uncompress(void *target, int *tgtlen,
					const void *source, int srclen) gxFuncThrowsError {
		assert(target && tgtlen && (*tgtlen > 0) && source && (srclen > 0));
		bool st = gx_gzuncompress(*this, target, tgtlen, source, srclen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else

	/** Uncompresses a compressed memory area.
	 *
	 * @param source Pointer to a compressed data.
	 * @param maxlen Length of the uncompressed data.
	 * @return The uncompressed data. If an error occurred the function will
	 *			thrown an exception. */
	inline gxOutData Uncompress(gxInData source, int maxlen) gxFuncThrowsError {
		GX_GETDATA(source);
		GX_GETHANDLE(h);
		int targetlen = maxlen;
		void *target;
		if(!gx_globalalloc(&target, targetlen)) {
			GX_FREEDATA(source);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		if(!gx_gzuncompress(h, target, &targetlen, GX_DATAPTR(source), GX_DATALEN(source))) {
			gx_globalfree(target);
			GX_FREEDATA(source);
			gxthrow;
			return GX_PUTDATA_NONE;
		}

		gxOutData ret = GX_PUTDATA(target, targetlen);
		gx_globalfree(target);
		GX_FREEDATA(source);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a .gz file (Unicode version).
	 *
	 * Use it when you can compress data to a single file.
	 *
	 * @param filename Path and name of the .gz file.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy. (see \ref GX_ZSTRATEGIES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(const wchar_t *filename, int level, int strategy) gxFuncThrowsError {
		assert(filename);
		bool st = gx_creategz(*this, filename, level, strategy) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a .gz file.
	 *
	 * Use it when you can compress data to a single file.
	 *
	 * @param filename Path and name of the .gz file.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy. (see \ref GX_ZSTRATEGIES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(const char *filename, int level, int strategy) gxFuncThrowsError {
		assert(filename);
		bool st = gx_creategz(*this, filename, level, strategy) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Creates a .gz file (Unicode version).
	 *
	 * Use it when you can compress data to a single file.
	 *
	 * @param filename Path and name of the .gz file.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(gxInStr filename, int level, int strategy) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_creategz(h, _filename, level, strategy) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Creates a .gz file (ASCII version).
	 *
	 * Use it when you can compress data to a single file.
	 *
	 * @param filename Path and name of the .gz file.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(gxInAStr filename, int level, int strategy) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_creategza(h, _filename, level, strategy) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Opens a .gz file (Unicode version).
	 *
	 * @param filename Path and name of the .gz file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const wchar_t *filename) gxFuncThrowsError {
		assert(filename);
		GX_GETHANDLE(h);
		bool st = gx_opengz(h, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Opens a .gz file (ASCII version).
	 *
	 * @param filename Path and name of the .gz file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const char *filename) gxFuncThrowsError {
		assert(filename);
		GX_GETHANDLE(h);
		bool st = gx_opengza(h, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Opens a .gz file (Unicode version).
	 *
	 * @param filename Path and name of the .gz file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInStr filename) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_opengz(h, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Opens a .gz file (ASCII version).
	 *
	 * @param filename Path and name of the .gz file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInAStr filename) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_opengza(h, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Closes an opened or created .gz file.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_closegz(h) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Reads data from an opened .gz file.
	 *
	 * @param buffer Pointer to an allocated area where the function reads data.
	 * @param buflen Length of the allocated area, the function updates it with
	 *			length of unpacked data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Read(void *buffer, int *buflen) gxFuncThrowsError {
		assert(buffer && buflen);
		bool st = gx_readgz(*this, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Reads data from an opened .gz file.
	 *
	 * @param len Length of the allocated area.
	 * @return It returns the uncompressed data.  If an error occurred the
	 *		function will thrown an exception. */
	inline gxOutData Read(int len) gxFuncThrowsError {
		int buflen = len;
		void *buffer;
		if(!gx_globalalloc(&buffer, buflen)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		GX_GETHANDLE(h);
		if(!gx_readgz(h, buffer, &buflen)) {
			gx_globalfree(buffer);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(buffer, buflen);
		gx_globalfree(buffer);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Writes data to a created .gz file.
	 *
	 * @param buffer Pointer to an unpacked data.
	 * @param buflen Length of the unpacked data, the function updates it with
	 *			length of written data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Write(const void *buffer, int buflen) gxFuncThrowsError {
		assert(buffer && buflen);
		GX_GETHANDLE(h);
		bool st = gx_writegz(h, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Writes data to a created .gz file.
	 *
	 * @param buffer The unpacked data. The function will write it.
	 * @return An exception is thrown or false is returned in case of error. */
	inline int Write(gxInData buffer) gxFuncThrowsError {
		GX_GETDATA(buffer);
		GX_GETHANDLE(h);
		int l = GX_DATALEN(buffer);
		bool st = gx_writegz(h, GX_DATAPTR(buffer), l) ? true : false;
		GX_FREEDATA(buffer);
		gxcondthrow(!st);
		return st ? l : 0;
	}
#endif
};

/******************************************************************************/
/** Information structure for a file in the ZIP. */
GX_STRUCT gxZipFileInfo {
public:
	int tm_sec;				/**< Seconds after the minute [0-59] */
	int tm_min;				/**< Minutes after the hour [0-59] */
	int tm_hour;			/**< Hours since midnight [0-23] */
	int tm_mday;			/**< Day of the month [1-31] */
	int tm_mon;				/**< Months since January [0-11] */
	int tm_year;			/**< Years [1980-2044] */

	int dosdate;			/**< If it is 0, tm_xxx fields are used. */
	int internal_fa;		/**< Internal file attributes. */
	int external_fa;		/**< External file attributes. */
};

/** Detailed information structure for a file in the ZIP. */
GX_STRUCT gxZipFileDetInfo {
public:
	int version;			/**< Version. */
	int version_needed;		/**< Version needed to extract. */
	int flag;				/**< General purpose bit flag. */
	int method;				/**< Compression method. */
	unsigned int crc;		/**< CRC-32 value. */
	int compressed_size;	/**< Compressed size in bytes. */
	int uncompressed_size;	/**< Uncompressed size in bytes. */
	int size_filename;		/**< Filename length in bytes. */
	int size_file_extra;	/**< Global extra field length in bytes. */
	int size_file_comment;	/**< File comment length in bytes. */
	int disk_num_start;		/**< Disk number start. */
};

/******************************************************************************/
#ifdef GX_DOTNET
	#define CreateFileOld CreateFile
	#undef CreateFile
#endif
/** Class for the Zip functions.
 *
 * The gxZip class does not use properties.
 */
GX_CLASS gxZip : public gxHandle {
private:
	int _file_method;	/**< Compression method. */
	int _file_level;	/**< Compression level. */

public:
	/** Class initialization. */
	inline gxZip() gxFuncThrowsError {
#ifndef GX_DOTNET
		if(!gx_openmodule(this, L"gxzlib", L"default")) gxthrow;
#else
		GX_GETHANDLE(h);
		if(!gx_openmodule(&h, L"gxzlib", L"default")) gxthrow;
		_set_handle(h.handle);
#endif
		_file_method = -1;
		_file_level = -1;
	}

	/** Checks if the handler of a module is valid.
	 *
	 * @return In case of existing handler the return value is non-zero. */
	inline bool IsValid(void) GX_CONST {
		return gxHandle::IsValid();
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a ZIP file (Unicode version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(const wchar_t *filename, int mode) gxFuncThrowsError {
		assert(filename);
		GX_GETHANDLE(h);
		bool st = gx_createzip(h, filename, mode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a ZIP file (ASCII version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(const char *filename, int mode) gxFuncThrowsError {
		assert(filename);
		GX_GETHANDLE(h);
		bool st = gx_createzipa(h, filename, mode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#endif
#ifdef GX_UNICODE
	/** Creates a ZIP file (Unicode version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(gxInStr filename, int mode) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_createzip(h, _filename, mode) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Creates a ZIP file (ASCII version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Create(gxInAStr filename, int mode) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		GX_GETHANDLE(h);
		bool st = gx_createzipa(h, _filename, mode) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Opens a ZIP file (Unicode version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const wchar_t *filename) gxFuncThrowsError {
		assert(filename);
		bool st = gx_openzip(*this, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Opens a ZIP file (ASCII version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(const char *filename) gxFuncThrowsError {
		assert(filename);
		bool st = gx_openzipa(*this, filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#endif
#ifdef GX_UNICODE
	/** Opens a ZIP file (Unicode version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInStr filename) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETSTRING(_filename, filename);
		bool st = gx_openzip(h, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Opens a ZIP file (ASCII version).
	 *
	 * @param filename Path and name of the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Open(gxInAStr filename) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETASTRING(_filename, filename);
		bool st = gx_openzipa(h, _filename) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif


#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a ZIP file in memory.
	 *
	 * @param mode Create mode (see \ref GX_CREATEZIPMODES).
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateZipInMemory(int mode) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_createzipinmemory(h, mode) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Get the created ZIP file in memory.
	 *
	 * @param pbuffer Pointer to the ZIP file in memory.
	 * @param pbuflen Pointer to the length of the ZIP file in memory.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetZipInMemory(void** pbuffer, int* pbuflen) gxFuncThrowsError {
		assert(pbuffer);
		assert(pbuflen);
		GX_GETHANDLE(h);
		bool st = gx_getzipinmemory(h, pbuffer, pbuflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Opens a ZIP file in memory.
	 *
	 * @param buffer The ZIP file in memory.
	 * @param buflen The length of the ZIP file in memory.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenZipInMemory(void* buffer, int buflen) gxFuncThrowsError {
		assert(buffer);
		assert(buflen);
		bool st = gx_openzipinmemory(*this, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Closes an opened/created ZIP file (Unicode version).
	 *
	 * @param comment Comment string for the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(const wchar_t *comment) gxFuncThrowsError {
		bool st = gx_closezip(*this, comment) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Closes an opened/created ZIP file (ASCII version).
	 *
	 * @param comment Comment string for the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(const char *comment) gxFuncThrowsError {
		bool st = gx_closezip(*this, comment) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Closes an opened/created ZIP file (Unicode version).
	 *
	 * @param comment Comment string for the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(gxInStr comment) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETSTRING(_comment, comment);
		bool st = gx_closezip(h, _comment) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Closes an opened/created ZIP file (ASCII version).
	 *
	 * @param comment Comment string for the ZIP file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(gxInAStr comment) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_GETASTRING(_comment, comment);
		bool st = gx_closezipa(h, _comment) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Closes an opened/created ZIP file.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool Close(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_closezipa(h, (const char *)0) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Gives informations about the opened ZIP file.
	 *
	 * @param info Pointer to an information structure where the function fills it.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetInfo(GX_PARM_GETZIPINFO *info) gxFuncThrowsError {
		assert(info);
		bool st = gx_getzipinfo(*this, info) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Gives the number of file entries in the archive.
	 *
	 * @return Number of file entries in the archive. If an error occurred
	 *			the function will thrown an exception. */
	inline int GetNEntries(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_PARM_GETZIPINFO info;
		info.nentries = -1;
		if(!gx_getzipinfo(h, &info)) gxthrow;
		return info.nentries;
	}

	/** Gives the length of the comment field in bytes.
	 *
	 * @return Length of comment in bytes. If an error occurred
	 *			the function will thrown an exception. */
	inline int GetCommentLength(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		GX_PARM_GETZIPINFO info;
		info.commentlen = -1;
		if(!gx_getzipinfo(h, &info)) gxthrow;
		return info.commentlen;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Reads the comment from the archive (Unicode version).
	 *
	 * @param target Pointer to an allocated area where the function writes the
	 *			comment string.
	 * @param tlen Length of the allocated area in characters.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetComment(wchar_t *target, int *tlen) gxFuncThrowsError {
		assert(target && tlen && (*tlen >= 0));
		bool st = gx_getzipcomment(*this, target, tlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Reads the comment from the archive.
	 *
	 * @param target Pointer to an allocated area where the function writes the
	 *			comment string.
	 * @param tlen Length of the allocated area.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetComment(char *target, int *tlen) gxFuncThrowsError {
		assert(target && tlen && (*tlen >= 0));
		bool st = gx_getzipcomment(*this, target, tlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Reads the comment from the archive (Unicode version).
	 *
	 * @return The comment string. If an error occurred the function will
	 *			thrown an exception. */
	inline gxOutStr GetComment(void) gxFuncThrowsError {
		int buflen = GetCommentLength();
		if(buflen <= 0) return GX_PUTSTRING_NONE;
		wchar_t *buffer;
		if(!gx_globalalloc((void **)(void *)&buffer, sizeof(wchar_t)*(buflen+1))) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		GX_GETHANDLE(h);
		buflen++;
		if(!gx_getzipcomment(h, buffer, &buflen)) {
			gx_globalfree(buffer);
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		buffer[buflen-1] = 0;
		gxOutStr ret = GX_PUTSTRING(buffer);
		gx_globalfree(buffer);
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Reads the comment from the archive (ASCII version).
	 *
	 * @return The comment string. If an error occurred the function will
	 *			thrown an exception. */
	inline gxOutAStr GetCommentA(void) gxFuncThrowsError {
		int buflen = GetCommentLength();
		if(buflen <= 0) return GX_PUTASTRING_NONE;
		char *buffer;
		if(!gx_globalalloc((void **)(void *)&buffer, buflen+1)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		GX_GETHANDLE(h);
		if(!gx_getzipcommenta(h, buffer, &buflen)) {
			gx_globalfree(buffer);
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		buffer[buflen] = 0;
		gxOutAStr ret = GX_PUTASTRING(buffer);
		gx_globalfree(buffer);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a file in the archive (Unicode version).
	 *
	 * @param cfz Pointer to the description structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(GX_PARM_CREATEFILEINZIPW *cfz) gxFuncThrowsError {
		assert(cfz);
		bool st = gx_createfileinzip(*this, cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a file in the archive.
	 *
	 * @param cfz Pointer to the description structure.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(GX_PARM_CREATEFILEINZIP *cfz) gxFuncThrowsError {
		assert(cfz);
		GX_GETHANDLE(h);
		bool st = gx_createfileinzipa(h, cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#if defined(GX_DOTNET) || defined(GX_SWIG)

#ifdef GX_UNICODE
	/** Creates file in ZIP (Unicode version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @param info Detailed information for the file.
	 * @param password Password for the file. If you use encrypted file,
	 *			fill the crc field also!
	 * @param crc CRC-32 value for the encrypted file. Set it to 0, if
	 *			the file is not encryipted.
	 * @param localexf Local extra field.
	 * @param globalexf Global extra field.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInStr filename, int level, int strategy, gxInStr comment,
		gxZipFileInfo GX_REF_STRUCT(info), gxInStr password, unsigned int crc,
						gxInData localexf, gxInData globalexf)
	{

		GX_ZIPFILEINFO _info;
		GX_PARM_CREATEFILEINZIPW cfz;
		memset(&cfz, 0, sizeof(cfz));

		_info.tm_sec = info GX_MS tm_sec;
		_info.tm_min = info GX_MS tm_min;
		_info.tm_hour = info GX_MS tm_hour;
		_info.tm_mday = info GX_MS tm_mday;
		_info.tm_mon = info GX_MS tm_mon;
		_info.tm_year = info GX_MS tm_year;
		_info.dosdate = info GX_MS dosdate;
		_info.internal_fa = info GX_MS internal_fa;
		_info.external_fa = info GX_MS external_fa;
		cfz.info = &_info;

		GX_GETSTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETSTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETSTRING(_password, password);
		cfz.password = (_password && *_password) ? _password : 0;
		cfz.crc = crc;
		GX_GETDATA(localexf);
		GX_GETDATA(globalexf);
		cfz.exflocal = GX_DATAPTR(localexf);
		cfz.exflocal_len = GX_DATALEN(localexf);
		cfz.exfglobal = GX_DATAPTR(globalexf);
		cfz.exfglobal_len = GX_DATALEN(globalexf);
		GX_GETHANDLE(h);
		bool st = gx_createfileinzip(h, &cfz) ? true : false;
		GX_FREEDATA(localexf);
		GX_FREEDATA(globalexf);
		gxcondthrow(!st);
		return st;
	}
#endif // GX_UNICODE

#ifdef GX_ASCII
	/** Creates file in ZIP (ASCII version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @param info Detailed information for the file.
	 * @param password Password for the file. If you use encrypted file,
	 *			fill the crc field also!
	 * @param crc CRC-32 value for the encrypted file. Set it to 0, if
	 *			the file is not encryipted.
	 * @param localexf Local extra field.
	 * @param globalext Global extra field.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInAStr filename, int level, int strategy,
						gxInAStr comment, gxZipFileInfo GX_REF_STRUCT(info),
						gxInAStr password, unsigned int crc,
						gxInData localexf, gxInData globalexf) {
		GX_ZIPFILEINFO _info;
		GX_PARM_CREATEFILEINZIP cfz;
		memset(&cfz, 0, sizeof(cfz));
		_info.tm_sec = info.tm_sec;
		_info.tm_min = info.tm_min;
		_info.tm_hour = info.tm_hour;
		_info.tm_mday = info.tm_mday;
		_info.tm_mon = info.tm_mon;
		_info.tm_year = info.tm_year;
		_info.dosdate = info.dosdate;
		_info.internal_fa = info.internal_fa;
		_info.external_fa = info.external_fa;
		cfz.info = &_info;
		GX_GETASTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETASTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETASTRING(_password, password);
		cfz.password = (_password && *_password) ? _password : 0;
		cfz.crc = crc;
		GX_GETDATA(localexf);
		GX_GETDATA(globalexf);
		cfz.exflocal = GX_DATAPTR(localexf);
		cfz.exflocal_len = GX_DATALEN(localexf);
		cfz.exfglobal = GX_DATAPTR(globalexf);
		cfz.exfglobal_len = GX_DATALEN(globalexf);
		GX_GETHANDLE(h);
		bool st = gx_createfileinzipa(h, &cfz) ? true : false;
		GX_FREEDATA(localexf);
		GX_FREEDATA(globalexf);
		gxcondthrow(!st);
		return st;
	}
#endif // GX_ASCII

#endif // defined(GX_DOTNET) && defined(GX_SWIG)

#ifdef GX_UNICODE
	/** Creates file in ZIP (Unicode version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @param info Detailed information for the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInStr filename, int level, int strategy,
						gxInStr comment, gxZipFileInfo GX_REF_STRUCT(info)) {

		GX_ZIPFILEINFO _info;
		GX_PARM_CREATEFILEINZIPW cfz;
		memset(&cfz, 0, sizeof(cfz));

		_info.tm_sec = info GX_MS tm_sec;
		_info.tm_min = info GX_MS tm_min;
		_info.tm_hour = info GX_MS tm_hour;
		_info.tm_mday = info GX_MS tm_mday;
		_info.tm_mon = info GX_MS tm_mon;
		_info.tm_year = info GX_MS tm_year;
		_info.dosdate = info GX_MS dosdate;
		_info.internal_fa = info GX_MS internal_fa;
		_info.external_fa = info GX_MS external_fa;
		cfz.info = &_info;

		GX_GETSTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETSTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETHANDLE(h);
		bool st = gx_createfileinzip(h, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif // GX_UNICODE

#ifdef GX_ASCII
	/** Creates file in ZIP (ASCII version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @param info Detailed information for the file.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInAStr filename, int level, int strategy,
						gxInAStr comment, gxZipFileInfo GX_REF_STRUCT(info)) {
		GX_ZIPFILEINFO _info;
		GX_PARM_CREATEFILEINZIP cfz;
		memset(&cfz, 0, sizeof(cfz));
		_info.tm_sec = info.tm_sec;
		_info.tm_min = info.tm_min;
		_info.tm_hour = info.tm_hour;
		_info.tm_mday = info.tm_mday;
		_info.tm_mon = info.tm_mon;
		_info.tm_year = info.tm_year;
		_info.dosdate = info.dosdate;
		_info.internal_fa = info.internal_fa;
		_info.external_fa = info.external_fa;
		cfz.info = &_info;
		GX_GETASTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETASTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETHANDLE(h);
		bool st = gx_createfileinzipa(h, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif // GX_ASCII

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Creates file in ZIP (Unicode version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(const wchar_t *filename, int level, int strategy,
						const wchar_t *comment) {

		GX_PARM_CREATEFILEINZIPW cfz;
		memset(&cfz, 0, sizeof(cfz));
		cfz.filename = filename;
		cfz.level = level;
		cfz.strategy = strategy;
		cfz.comment = comment;
		bool st = gx_createfileinzip(*this, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates file in ZIP (ASCII version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(const char *filename, int level, int strategy,
						const char *comment) {

		GX_PARM_CREATEFILEINZIP cfz;
		memset(&cfz, 0, sizeof(cfz));
		cfz.filename = filename;
		cfz.level = level;
		cfz.strategy = strategy;
		cfz.comment = comment;
		bool st = gx_createfileinzipa(*this, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif


#ifdef GX_UNICODE
	/** Creates file in ZIP (Unicode version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInStr filename, int level, int strategy,
						gxInStr comment) {

		GX_PARM_CREATEFILEINZIPW cfz;
		memset(&cfz, 0, sizeof(cfz));
		GX_GETSTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETSTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETHANDLE(h);
		bool st = gx_createfileinzip(h, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif // GX_UNICODE

#ifdef GX_ASCII
	/** Creates file in ZIP (ASCII version).
	 *
	 * @param filename The name of the file in ZIP.
	 * @param level Compression level (see \ref GX_ZLEVELS).
	 * @param strategy Compression strategy (see \ref GX_ZSTRATEGIES).
	 * @param comment Comment for the file in the ZIP.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CreateFile(gxInAStr filename, int level, int strategy,
						gxInAStr comment) {

		GX_PARM_CREATEFILEINZIP cfz;
		memset(&cfz, 0, sizeof(cfz));
		GX_GETASTRING(_filename, filename);
		cfz.filename = _filename;
		cfz.level = level;
		cfz.strategy = strategy;
		GX_GETASTRING(_comment, comment);
		cfz.comment = _comment;
		GX_GETHANDLE(h);
		bool st = gx_createfileinzipa(h, &cfz) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif // GX_ASCII

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Writes data to the current file in the archive.
	 *
	 * @param buffer Pointer to data.
	 * @param buflen Length of data in bytes.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteToFile(const void *buffer, int buflen) gxFuncThrowsError {
		assert(buffer && (buflen >= 0));
		bool st = gx_writetofileinzip(*this, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Writes data to the current file in the archive.
	 *
	 * @param data The source data.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool WriteToFile(gxInData data) gxFuncThrowsError {
		GX_GETDATA(data);
		GX_GETHANDLE(h);
		bool st = gx_writetofileinzip(h, GX_DATAPTR(data), GX_DATALEN(data)) ?
						true : false;
		GX_FREEDATA(data);
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Closes the current file in the archive.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CloseFile(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		bool st = gx_closefileinzip(h) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Sets marker to the first file in the archive (Unicode version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return The function returns true if no error. */
	inline bool FirstFile(GX_ZIPFILEDETINFOW *finfo) {
		assert(finfo);
		return gx_firstfileinzip(*this, finfo) ? true : false;
	}

	/** Sets marker to the first file in the archive (ASCII version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return The function returns true if no error. */
	inline bool FirstFile(GX_ZIPFILEDETINFO *finfo) {
		assert(finfo);
		return gx_firstfileinzip(*this, finfo) ? true : false;
	}
#endif

	/** Sets marker to the first file in the archive.
	 *
	 * @return Returns true if no error. */
	inline bool FirstFile(void) {
		GX_GETHANDLE(h);
		return gx_firstfileinzip(h, (GX_ZIPFILEDETINFO *)0) ? true : false;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Sets marker to the next file in the archive (Unicode version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return The function returns true if no error. */
	inline bool NextFile(GX_ZIPFILEDETINFOW *finfo) {
		assert(finfo);
		return gx_nextfileinzip(*this, finfo) ? true : false;
	}

	/** Sets marker to the next file in the archive (ASCII version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return The function returns true if no error. */
	inline bool NextFile(GX_ZIPFILEDETINFO *finfo) {
		assert(finfo);
		return gx_nextfileinzip(*this, finfo) ? true : false;
	}
#endif

	/** Sets marker to the next file in the archive.
	 *
	 * @return Returns true if no error. */
	inline bool NextFile(void) {
		GX_GETHANDLE(h);
		return gx_nextfileinzip(h, (GX_ZIPFILEDETINFO *)0) ? true : false;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Sets marker to the specified file in the archive (Unicode version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @param filename Name of the file in the archive.
	 * @param casesensitivity Case sensitivity signification.
	 *			It can be:
	 *			 - 1: comparision is case sensitive (like strcmp)
	 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
	 *			 - 0: case sensitivity is the default of your operation system
	 *				  (like 1 on Unix, 2 on Windows)
	 * @return Returns true if no error. */
	inline bool LocateFile(GX_ZIPFILEDETINFOW *finfo, const wchar_t *filename,
							int casesensitivity = 0) gxFuncThrowsError {
		assert(finfo);
		assert(filename);
		return gx_locatefileinzip(*this, finfo, filename, casesensitivity) ?
						true : false;
	}

	/** Sets marker to the specified file in the archive (ASCII version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @param filename Name of the file in the archive.
	 * @param casesensitivity Case sensitivity signification.
	 *			It can be:
	 *			 - 1: comparision is case sensitive (like strcmp)
	 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
	 *			 - 0: case sensitivity is the default of your operation system
	 *				  (like 1 on Unix, 2 on Windows)
	 * @return Returns true if no error. */
	inline bool LocateFile(GX_ZIPFILEDETINFO *finfo, const char *filename,
							int casesensitivity = 0) gxFuncThrowsError {
		assert(finfo);
		assert(filename);
		return gx_locatefileinzipa(*this, finfo, filename, casesensitivity) ?
						true : false;
	}
#endif

#ifdef GX_UNICODE
	/** Sets marker to the specified file in the archive (Unicode version).
	 *
	 * @param filename Name of the file in the archive.
	 * @param casesensitivity Case sensitivity signification.
	 *			It can be:
	 *			 - 1: comparision is case sensitive (like strcmp)
	 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
	 *			 - 0: case sensitivity is the default of your operation system
	 *				  (like 1 on Unix, 2 on Windows)
	 * @return Returns true if no error. */
	inline bool LocateFile(gxInStr filename, int casesensitivity GX_DEFARG(0)) gxFuncThrowsError {
		GX_GETSTRING(_filename, filename);
		GX_GETHANDLE(h);
		return gx_locatefileinzip(h, (GX_ZIPFILEDETINFOW *)0, _filename,
						casesensitivity) ? true : false;
	}
#endif
#ifdef GX_ASCII
	/** Sets marker to the specified file in the archive (ASCII version).
	 *
	 * @param filename Name of the file in the archive.
	 * @param casesensitivity Case sensitivity signification.
	 *			It can be:
	 *			 - 1: comparision is case sensitive (like strcmp)
	 *			 - 2: comparision is not case sensitive (like strcmpi/strcasecmp)
	 *			 - 0: case sensitivity is the default of your operation system
	 *				  (like 1 on Unix, 2 on Windows)
	 * @return Returns true if no error. */
	inline bool LocateFile(gxInAStr filename, int casesensitivity = 0) gxFuncThrowsError {
		GX_GETASTRING(_filename, filename);
		GX_GETHANDLE(h);
		return gx_locatefileinzipa(h, (GX_ZIPFILEDETINFO *)0, _filename,
						casesensitivity) ? true : false;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Gives information about a marked file in the archive.
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool FileInfo(GX_ZIPFILEDETINFO *finfo) gxFuncThrowsError {
		assert(finfo);
		bool st = gx_fileinfoinzip(*this, finfo) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Gives information about a marked file in the archive (Unicode version).
	 *
	 * @param finfo Pointer to the information structure. The function will fill it.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool FileInfo(GX_ZIPFILEDETINFOW *finfo) gxFuncThrowsError {
		assert(finfo);
		bool st = gx_fileinfoinzip(*this, finfo) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Gives the information of the marked file.
	 *
	 * @return The information structure. If an error occurred the function
	 *			will thrown an exception. */
	inline gxZipFileInfo GetFileInfo(void) gxFuncThrowsError {
		GX_ZIPFILEDETINFO info;
		memset(&info, 0, sizeof(info));
		gxZipFileInfo ret;
		memset(&ret, 0, sizeof(ret));
		GX_GETHANDLE(h);
		if(gx_fileinfoinzip(h, &info)) {
			ret.tm_sec = info.tm_sec;
			ret.tm_min = info.tm_min;
			ret.tm_hour = info.tm_hour;
			ret.tm_mday = info.tm_mday;
			ret.tm_mon = info.tm_mon;
			ret.tm_year = info.tm_year;
			ret.dosdate = info.dosdate;
			ret.internal_fa = info.internal_fa;
			ret.external_fa = info.external_fa;
		} else {
			gxthrow;
		}
		return ret;
	}

	/** Gives the detailed information of the marked file.
	 *
	 * @return The information structure. If an error occurred the function
	 *			will thrown an exception. */
	inline gxZipFileDetInfo GetFileDetInfo(void) gxFuncThrowsError {
		GX_ZIPFILEDETINFO info;
		memset(&info, 0, sizeof(info));
		gxZipFileDetInfo ret;
		memset(&ret, 0, sizeof(ret));
		GX_GETHANDLE(h);
		if(gx_fileinfoinzip(h, &info)) {
			ret.version = info.version;
			ret.version_needed = info.version_needed;
			ret.flag = info.flag;
			ret.method = info.method;
			ret.crc = info.crc;
			ret.compressed_size = info.compressed_size;
			ret.uncompressed_size = info.uncompressed_size;
			ret.size_filename = info.size_filename;
			ret.size_file_extra = info.size_file_extra;
			ret.size_file_comment = info.size_file_comment;
			ret.disk_num_start = info.disk_num_start;
		} else {
			gxthrow;
		}
		return ret;
	}

#ifdef GX_UNICODE
	/** Retrieves the name of the file in the ZIP.
	 *
	 * @return Name of the file. If an error occurred the function will
	 *				thrown an error. */
	inline gxOutStr GetFileName(void) {
		GX_ZIPFILEDETINFOW info;
		memset(&info, 0, sizeof(info));
		GX_GETHANDLE(h);
		if(!gx_fileinfoinzip(h, &info)) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		wchar_t *filename;
		if(!gx_globalalloc((void **)(void *)&filename, sizeof(wchar_t)*(info.size_filename+1))) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		info.filename = filename;
		info.filename_len = info.size_filename+1;
		if(!gx_fileinfoinzip(h, &info)) {
			gx_globalfree(filename);
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		filename[info.size_filename] = 0;
		gxOutStr ret = GX_PUTSTRING(filename);
		gx_globalfree(filename);
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Retrieves the name of the file in the ZIP (ASCII version).
	 *
	 * @return Name of the file. If an error occurred the function will
	 *				thrown an error. */
	inline gxOutAStr GetFileNameA(void) {
		GX_ZIPFILEDETINFO info;
		memset(&info, 0, sizeof(info));
		GX_GETHANDLE(h);
		if(!gx_fileinfoinzipa(h, &info)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		char *filename;
		if(!gx_globalalloc((void **)(void *)&filename, info.size_filename+1)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		info.filename = filename;
		info.filename_len = info.size_filename+1;
		if(!gx_fileinfoinzipa(h, &info)) {
			gx_globalfree(filename);
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		filename[info.size_filename] = 0;
		gxOutAStr ret = GX_PUTASTRING(filename);
		gx_globalfree(filename);
		return ret;
	}
#endif

#ifdef GX_UNICODE
	/** Retrieves the comment of the file in the ZIP.
	 *
	 * @return Comment of the file. If an error occurred the function will
	 *				thrown an error. */
	inline gxOutStr GetFileComment(void) {
		GX_ZIPFILEDETINFOW info;
		memset(&info, 0, sizeof(info));
		GX_GETHANDLE(h);
		if(!gx_fileinfoinzip(h, &info)) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		wchar_t *comment;
		if(!gx_globalalloc((void **)(void *)&comment, sizeof(wchar_t)*(info.size_file_comment+1))) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		info.comment = comment;
		info.comment_len = info.size_file_comment+1;
		if(!gx_fileinfoinzip(h, &info)) {
			gx_globalfree(comment);
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		comment[info.size_file_comment] = 0;
		gxOutStr ret = GX_PUTSTRING(comment);
		gx_globalfree(comment);
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Retrieves the comment of the file in the ZIP (ASCII version).
	 *
	 * @return Comment of the file. If an error occurred the function will
	 *				thrown an error. */
	inline gxOutAStr GetFileCommentA(void) {
		GX_ZIPFILEDETINFO info;
		memset(&info, 0, sizeof(info));
		GX_GETHANDLE(h);
		if(!gx_fileinfoinzipa(h, &info)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		char *comment;
		if(!gx_globalalloc((void **)(void *)&comment, info.size_file_comment+1)) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		info.comment = comment;
		info.comment_len = info.size_file_comment+1;
		if(!gx_fileinfoinzipa(h, &info)) {
			gx_globalfree(comment);
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		comment[info.size_file_comment] = 0;
		gxOutAStr ret = GX_PUTASTRING(comment);
		gx_globalfree(comment);
		return ret;
	}
#endif

#if defined(GX_DOTNET) || defined(GX_SWIG)
	/** Retrieves the global extra field of the file in the ZIP.
	 *
	 * @return The global extra field of the file.
	 *			 If an error occurred the function will thrown an error. */
	inline gxOutData GetFileGlobalExtraField(void) {
		GX_ZIPFILEDETINFO info;
		memset(&info, 0, sizeof(info));
		GX_GETHANDLE(h);
		if(!gx_fileinfoinzipa(h, &info)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		void *gextrafield;
		if(!gx_globalalloc(&gextrafield, info.size_file_extra)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		info.gextrafield = gextrafield;
		info.gextrafield_len = info.size_file_extra;
		if(!gx_fileinfoinzipa(h, &info)) {
			gx_globalfree(gextrafield);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(gextrafield, info.gextrafield_len);
		gx_globalfree(gextrafield);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Opens a marked file in the archive (Unicode version).
	 *
	 * @param method Pointer to an integer. The function will update it to the compression method.
	 * @param level Pointer to an integer. The function will update it to the compression level.
	 * @param password Password string if the file is encoded. It can be NULL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenFile(int *method, int *level, const wchar_t *password) gxFuncThrowsError {
		bool st = gx_openfileinzip(*this, &_file_method, &_file_level, password) ? true : false;
		gxcondthrow(!st);
		if(st) {
			if(method) *method = _file_method;
			if(level) *level = _file_level;
		}
		return st;
	}

	/** Opens a marked file in the archive (ASCII version).
	 *
	 * @param method Pointer to an integer. The function will update it to the compression method.
	 * @param level Pointer to an integer. The function will update it to the compression level.
	 * @param password Password string if the file is encoded. It can be NULL.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenFile(int *method, int *level = (int *)0, const char *password = (const char *)0) gxFuncThrowsError {
		bool st = gx_openfileinzipa(*this, &_file_method, &_file_level, password) ? true : false;
		gxcondthrow(!st);
		if(st) {
			if(method) *method = _file_method;
			if(level) *level = _file_level;
		}
		return st;
	}
#endif
	/** Opens a marked file in the archive.
	 *
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenFile(void) gxFuncThrowsError {
		GX_GETHANDLE(h);
		int _fm = _file_method;
		int _fl = _file_level;
		bool st = gx_openfileinzipa(h, &_fm, &_fl, (const char *)0) ? true : false;
		_file_method = _fm;
		_file_level = _fl;
		gxcondthrow(!st);
		return st;
	}

#ifdef GX_UNICODE
	/** Opens a marked file in the archive (Unicode version).
	 *
	 * @param password	Password for authentication.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenFile(gxInStr password) gxFuncThrowsError {
		GX_GETSTRING(_password, password);
		GX_GETHANDLE(h);
		int _fm = _file_method;
		int _fl = _file_level;
		bool st = gx_openfileinzip(h, &_fm, &_fl, _password) ? true : false;
		gxcondthrow(!st);
		_file_method = _fm;
		_file_level = _fl;
		return st;
	}
#endif
#ifdef GX_ASCII
	/** Opens a marked file in the archive (ASCII version).
	 *
	 * @param password	Password for authentication.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool OpenFile(gxInAStr password) gxFuncThrowsError {
		GX_GETASTRING(_password, password);
		bool st = gx_openfileinzipa(*this, &_file_method, &_file_level, _password) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Retrieves the method of the last opened file in the ZIP.
	 *
	 * @return Compression method of the last opened file. */
	inline int GetFileMethod(void) gxFuncThrowsError {
		return _file_method;
	}

	/** Retrieves the compression level of the last opened file in the ZIP.
	 *
	 * @return Compression level of the last opened file. */
	inline int GetFileLevel(void) gxFuncThrowsError {
		return _file_level;
	}

#if !defined (GX_SWIG) && !defined(GX_DOTNET)
	/** Reads the content of an opened file in the ZIP archive.
	 *
	 * @param target Pointer to an allocated area.
	 * @param tlen Length of the allocated area in bytes.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool ReadFromFile(void *target, int *tlen) gxFuncThrowsError {
		assert(target && tlen && (*tlen >= 0));
		bool st = gx_readfromfileinzip(*this, target, tlen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Reads the content of an opened file in the ZIP archive.
	 *
	 * @param len Length of the allocated area in bytes.
	 * @return The unpacked data.  If an error occurred the function will
	 *			thrown an exception. */
	inline gxOutData ReadFromFile(int len) gxFuncThrowsError {
		void *target;
		if(!gx_globalalloc(&target, len)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		int tlen = len;
		GX_GETHANDLE(h);
		bool st = gx_readfromfileinzip(h, target, &tlen) ? true : false;
		if(!st) {
			gx_globalfree(target);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(target, tlen);
		gx_globalfree(target);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Calculates CRC-32 value from the specified buffer for the encrypted archive.
	 *
	 * @param crc The initial CRC-32 value. The function will update it with the calculated CRC.
	 * @param buffer Pointer to data.
	 * @param buflen Length of the data in bytes.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool CalculateCRC(unsigned int *crc, const void *buffer, int buflen) gxFuncThrowsError {
		assert(crc && buffer && (buflen >= 0));
		bool st = gx_calculatezipcrc(*this, crc, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Calculates CRC-32 value from the specified buffer for the encrypted archive.
	 *
	 * @param initialcrc The initial CRC-32 value.
	 * @param buffer The source data.
	 * @return The calculated CRC value. If an error occurred the function
	 *			throws an exception. */
	inline unsigned int CalculateCRC(unsigned int initialcrc, gxInData buffer) gxFuncThrowsError {
		unsigned int ret = initialcrc;
		GX_GETHANDLE(h);
		GX_GETDATA(buffer);
		bool st = gx_calculatezipcrc(h, &ret, GX_DATAPTR(buffer), GX_DATALEN(buffer)) ? true : false;
		GX_FREEDATA(buffer);
		gxcondthrow(!st);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Retrieves the initial CRC for the gxZip::CalculateCRC().
	 *
	 * @param crc Pointer to an area, the function will be updated it with the initial CRC.
	 * @return An exception is thrown or false is returned in case of error. */
	inline bool GetInitialCRC(unsigned int *crc) gxFuncThrowsError {
		assert(crc);
		bool st = gx_getinitialzipcrc(*this, crc) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Returns the initial CRC for the gxZip::CalculateCRC().
	 *
	 * @return The initial CRC. If an error occurred the function throws an
	 *			exception. */
	inline unsigned int GetInitialCRC(void) gxFuncThrowsError {
		unsigned int ret = 0;
		GX_GETHANDLE(h);
		if(!gx_getinitialzipcrc(h, &ret)) gxthrow;
		return ret;
	}

#if !defined(GX_DOTNET) && !defined(GX_SWIG)
	/** Reads the local extra field of the marked file in the archive.
	 *
	 * @param buffer Pointer to data.
	 * @param buflen Length of the data in bytes.
	 * @return On success: non-zero ( see gx_geterror() ) */
	inline bool ReadLocalExtraField(void *buffer, int *buflen) gxFuncThrowsError {
		assert(buffer && buflen && (*buflen >= 0));
		bool st = gx_readlexfieldzip(*this, buffer, buflen) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Retrieves the local extra field of the marked file in the archive.
	 *
	 * @param maxlen The maximal length of the allocated area.
	 * @return Local extra field of the file. If an error occurred
	 *				the function will thrown an error. */
	inline gxOutData ReadLocalExtraField(int maxlen) {
		GX_GETHANDLE(h);
		void *lextrafield;
		if(!gx_globalalloc(&lextrafield, maxlen)) {
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		int lextrafield_len = maxlen;
		if(!gx_readlexfieldzip(h, lextrafield, &lextrafield_len)) {
			gx_globalfree(lextrafield);
			gxthrow;
			return GX_PUTDATA_NONE;
		}
		gxOutData ret = GX_PUTDATA(lextrafield, lextrafield_len);
		gx_globalfree(lextrafield);
		return ret;
	}
#endif

};
#ifdef GX_DOTNET
	#define CreateFile CreateFileOld
	#undef CreateFileOld
#endif
/******************************************************************************/
#endif // NO_GX_CLASSES
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif // GXZLIB_INCL
/******************************************************************************/
