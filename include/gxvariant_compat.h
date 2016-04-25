/******************************************************************************
 * GX variants - V7.2.10.1
 *
 * 2006-2013 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
#ifndef GX_VARIANT_CPT_INCL
#define GX_VARIANT_CPT_INCL
/******************************************************************************/
/** \file
 * <b> Gx variant - a complex data structure </b>
 *
 * The \ref gxVARIANT type was introduced to easily form dynamically expandable
 * complex data structures which are usable in different programming languages
 * under various operational environments.
 * The \ref gxVARIANT is the basic unit of these complex data structures, and it
 * has the following important features:
 * \li Stores basic data types as well as arrays or strings.
 * \li Uses run-time type information for automatic data conversion on user request.
 * \li Stores id or name which can be used to identify data in a complex structure.
 * \li Stores children. The variants can be connected together in a way that they
 * form a tree through parent-child relationships.
 * \li Uses reference counting to save memory and to form a closed tree.
 * \li It can be a list, in which the items are connected according to parent-children
 * hierarchy. The list and list items can have children too.
 */
/******************************************************************************/
#include "gxsd.h"
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace gx {
	#ifdef GX_DOTNET
		/* Unmanaged code for .NET. */
		#pragma unmanaged
	#endif
#endif
/******************************************************************************/
/** Empty structure type to map the variant type. */
#ifndef GX_DOTNET
struct GX_VARIANT;
#else
struct GX_VARIANT{};
#endif
/** Defining the variant type as a pointer to an empty structure (no automatic typecasts). */
typedef struct GX_VARIANT* gxVARIANT;

#ifdef GX_DOTNET
	#pragma managed
#endif

#ifndef GX_EXT_MODULE

/** Available variant types.
 * \note The values with \e \b _AC_ tag are usable in creation operation only. For
 * these types the value is automatically converted to the proper data type.
 * \note The values with \e \b _AS_ tag are usable in creation operation only. For
 * these types the value is automatically converted to the proper string type.
 */
GX_ENUM GX_VARIANT_TYPES
{
	/* Basic types (size = size of one element in bytes, nitems = number of items) */
	GX_VARIANT_NULL			= 0x00,		/**< NULL type (size: 0; nitems: 1) */
	GX_VARIANT_INT			= 0x01,		/**< Integer type (size: 0, 1, 2, 4, 8; nitems: 1) */
	GX_VARIANT_UINT			= 0x02,		/**< Unsigned integer type (size: 0, 1, 2, 4, 8; nitems: 1) */
	GX_VARIANT_FLOAT		= 0x03,		/**< Floating-point type (size: 0, 4, 8; nitems: 1) */
	GX_VARIANT_DATETIME		= 0x04,		/**< Datetime type (size: 0, 8; nitems: 1). */

	/* Array types, bit 6 set defines the array type.
	 * (size = size of the element in bytes, nitems = number of items) */
	GX_VARIANT_ARRAY		= 0x40,		/**< NULL type array /NULL array/ (size: 0; nitems: x) */
	GX_VARIANT_INTARRAY		= 0x41,		/**< Integer type array (size: 0, 1, 2, 4, 8; nitems: x) */
	GX_VARIANT_UINTARRAY	= 0x42,		/**< Unsigned integer type array (size: 0, 1, 2, 4, 8; nitems: x) */
	GX_VARIANT_FLOATARRAY	= 0x43,		/**< Float type array (size: 0, 4, 8; nitems: x) */
	GX_VARIANT_DATETIMEARRAY= 0x44,		/**< Datetime type array (size: 0, 8; nitems: x). */

	/* Other dynamically sized types */
	GX_VARIANT_LIST			= 0x80,		/**< List type (size=nitems: number of items) */
	GX_VARIANT_BINARY		= 0x81,		/**< Binary (size=number of bytes; nitems: 1) */
	GX_VARIANT_ASCII		= 0x82,		/**< String in ASCII format (size=number of characters; nitems: 1) */
	GX_VARIANT_UNICODE		= 0x83,		/**< String in unicode format (size=number of characters; nitems: 1) */
	GX_VARIANT_CONTAINER	= 0x84,		/**< Internally used binary structure (size=number of codes; nitems: 1). */

	/* Types for creation operation only */
	GX_VARIANT_AC_ASCII		= 0x1082,	/**< String in ASCII format (size=number of characters; nitems: 1) (see note above) */
	GX_VARIANT_AC_UNICODE	= 0x1083,	/**< String in unicode format (size=number of characters; nitems: 1) (see note above) */
	GX_VARIANT_AS_ASCII		= 0x2082,	/**< String in ASCII format (size=number of characters; nitems: 1) (see note above) */
	GX_VARIANT_AS_UNICODE	= 0x2083,	/**< String in unicode format (size=number of characters; nitems: 1) (see note above). */
};

#endif

#ifndef GX_MANUAL

#ifndef __cplusplus
typedef enum GX_VARIANT_TYPES GX_VARIANT_TYPES;
#endif

#endif /* GX_MANUAL */

#ifndef GX_EXT_MODULE

/** Flags for list item and child indexing functions. */
GX_ENUM GX_VARIANT_FLAGS
{
	GX_VARIANT_BY_INDEX				= 0x0002,	/**< Select the \a \b ix -th item. */

	GX_VARIANT_BY_ID				= 0x0001,	/**< Search by \a \b id */
	GX_VARIANT_BY_INDEX_AND_ID		= 0x0003,	/**< Search for an item with \a \b id, starting from the \a \b ix -th item */
	GX_VARIANT_BY_ORDER_AND_ID		= 0x0004,	/**< Search for the \a \b ix -th item with the specified \a \b id. */

	GX_VARIANT_BY_NAME				= 0x0008,	/**< Search by \a \b name */
	GX_VARIANT_BY_INDEX_AND_NAME	= 0x000a,	/**< Search for an item with \a \b name, starting from the \a \b ix -th item */
	GX_VARIANT_BY_ORDER_AND_NAME	= 0x0010,	/**< Search for the \a \b ix -th item with the specified \a \b name. */

	GX_VARIANT_APPEND				= 0x0100,	/**< Appending after the index position instead of inserting */
	GX_VARIANT_LAST					= 0x0200,	/**< Select the last item */
};

#endif
/******************************************************************************/
#ifndef GX_MANUAL
#ifdef __BORLANDC__
	#pragma warn -rch
#endif

/* .NET Workarounds */
#ifdef GX_DOTNET
	#pragma unmanaged
	#define _GX_VARIANT_LAST 0x0200
	#define _GX_VARIANT_BY_ORDER_AND_ID 4
#else
	#define _GX_VARIANT_LAST GX_VARIANT_LAST
	#define _GX_VARIANT_BY_ORDER_AND_ID GX_VARIANT_BY_ORDER_AND_ID
#endif
#endif/* GX_MANUAL */

/******************************************************************************/
#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)
/* GX call codes */
enum GX_CALL_VARIANT_CODES
{
	GX_CALL_REFVARIANT			= GX_CALL_GROUP_VARIANT,
	GX_CALL_UNREFVARIANT		= GX_CALL_GROUP_VARIANT+1,
	GX_CALL_CREATEVARIANT		= GX_CALL_GROUP_VARIANT+3,
	GX_CALL_DUPLICATEVARIANT	= GX_CALL_GROUP_VARIANT+4,
	GX_CALL_UPDATEVARIANT		= GX_CALL_GROUP_VARIANT+5,
	GX_CALL_UPDATEVARIANTDATA	= GX_CALL_GROUP_VARIANT+6,
	GX_CALL_GETVARIANT			= GX_CALL_GROUP_VARIANT+7,
	GX_CALL_CONVERTVARIANT		= GX_CALL_GROUP_VARIANT+8,

	GX_CALL_GETVARIANTITEM		= GX_CALL_GROUP_VARIANT+9,
	GX_CALL_CUTVARIANTITEM		= GX_CALL_GROUP_VARIANT+10,
	GX_CALL_FINDVARIANTITEM		= GX_CALL_GROUP_VARIANT+11,
	GX_CALL_ADDVARIANTITEM		= GX_CALL_GROUP_VARIANT+12,
	GX_CALL_REMOVEVARIANTITEM	= GX_CALL_GROUP_VARIANT+13,

	GX_CALL_GETVARIANTCHILD		= GX_CALL_GROUP_VARIANT+14,
	GX_CALL_CUTVARIANTCHILD		= GX_CALL_GROUP_VARIANT+15,
	GX_CALL_FINDVARIANTCHILD	= GX_CALL_GROUP_VARIANT+16,
	GX_CALL_ADDVARIANTCHILD		= GX_CALL_GROUP_VARIANT+17,
	GX_CALL_REMOVEVARIANTCHILD	= GX_CALL_GROUP_VARIANT+18,

	GX_CALL_GETVARIANTVALUE		= GX_CALL_GROUP_VARIANT+19,
	GX_CALL_CUTVARIANTVALUE		= GX_CALL_GROUP_VARIANT+20,
	GX_CALL_ADDVARIANTVALUE		= GX_CALL_GROUP_VARIANT+22,
	GX_CALL_REMOVEVARIANTVALUE	= GX_CALL_GROUP_VARIANT+23,

	GX_CALL_GETVARIANTBYPATH		= GX_CALL_GROUP_VARIANT+24,
	GX_CALL_GETVARIANTBYPATHA		= GX_CALL_GROUP_VARIANT+25,
	GX_CALL_CONVERTVARIANTBYPATH	= GX_CALL_GROUP_VARIANT+26,
	GX_CALL_CONVERTVARIANTBYPATHA	= GX_CALL_GROUP_VARIANT+27,

	GX_CALL_UPDATEVARIANTID		= GX_CALL_GROUP_VARIANT+29,

	GX_CALL_CREATEVARIANTN		= GX_CALL_GROUP_VARIANT+30,
	GX_CALL_UPDATEVARIANTN		= GX_CALL_GROUP_VARIANT+31,
	GX_CALL_UPDATEVARIANTDATAN	= GX_CALL_GROUP_VARIANT+32,
	GX_CALL_CHANGEVARIANTNAME	= GX_CALL_GROUP_VARIANT+33,
	GX_CALL_GETVARIANTINFO		= GX_CALL_GROUP_VARIANT+34,

	GX_CALL_GETVARIANTITEMN		= GX_CALL_GROUP_VARIANT+35,
	GX_CALL_CUTVARIANTITEMN		= GX_CALL_GROUP_VARIANT+36,
	GX_CALL_FINDVARIANTITEMN	= GX_CALL_GROUP_VARIANT+37,
	GX_CALL_ADDVARIANTITEMN		= GX_CALL_GROUP_VARIANT+38,

	GX_CALL_GETVARIANTCHILDN	= GX_CALL_GROUP_VARIANT+39,
	GX_CALL_CUTVARIANTCHILDN	= GX_CALL_GROUP_VARIANT+40,
	GX_CALL_FINDVARIANTCHILDN	= GX_CALL_GROUP_VARIANT+41,
	GX_CALL_ADDVARIANTCHILDN	= GX_CALL_GROUP_VARIANT+42,
};

/******************************************************************************/

/* GX call parameter structures. */

struct GX_PARM_DUPLICATEVARIANT
{
	gxVARIANT	 source;
	gxVARIANT	 target;
};

#define GX_PARM_CREATEVARIANT GX_PARM_UPDATEVARIANT

struct GX_PARM_UPDATEVARIANT
{
	gxVARIANT	 variant;
	int			 id;
	int			 type;
	int			 size;
	int			 nitems;
	const void	*data;
};

#define GX_PARM_UPDATEVARIANTDATA GX_PARM_UPDATEVARIANT

struct GX_PARM_UPDATEVARIANTID
{
	gxVARIANT	 variant;
	int			 id;
};

struct GX_PARM_GETVARIANT
{
	gxVARIANT	 variant;
	int			 id;
	int			 type;
	int			 size;
	int			 nitems;
	int			 nchildren;
};

struct GX_PARM_CONVERTVARIANT
{
	gxVARIANT	 variant;
	int			 id;
	int			 type;
	int			 size;
	int			 nitems;
	void		*target;
	int			 tgtlen;
};

struct GX_PARM_GETVARIANTITEM
{
	gxVARIANT	 list;
	int			 flags;
	int			 id;
	int			 ix;
	gxVARIANT	 target;
};

#define GX_PARM_CUTVARIANTITEM GX_PARM_GETVARIANTITEM

struct GX_PARM_FINDVARIANTITEM
{
	gxVARIANT	 list;
	gxVARIANT	 item;
	int			 id;
	int			 ix;
};

struct GX_PARM_ADDVARIANTITEM
{
	gxVARIANT	 list;
	int			 flags;
	int			 id;
	int			 ix;
	gxVARIANT	 item;
};

struct GX_PARM_REMOVEVARIANTITEM
{
	gxVARIANT	 list;
	int			 flags;
	int			 id;
	int			 ix;
};

struct GX_PARM_GETVARIANTCHILD
{
	gxVARIANT	 parent;
	int			 flags;
	int			 id;
	int			 ix;
	gxVARIANT	 target;
};

#define GX_PARM_CUTVARIANTCHILD GX_PARM_GETVARIANTCHILD

struct GX_PARM_FINDVARIANTCHILD
{
	gxVARIANT	 parent;
	gxVARIANT	 child;
	int			 id;
	int			 ix;
};

struct GX_PARM_ADDVARIANTCHILD
{
	gxVARIANT	 parent;
	int			 flags;
	int			 id;
	int			 ix;
	gxVARIANT	 child;
};

struct GX_PARM_REMOVEVARIANTCHILD
{
	gxVARIANT	 parent;
	int			 flags;
	int			 id;
	int			 ix;
};

struct GX_PARM_GETVARIANTVALUE
{
	gxVARIANT	 array;
	int			 size;
	int			 type;
	int			 ix;
	int			 nitems;
	void		*target;
	int			 tgtlen;
};

#define GX_PARM_CUTVARIANTVALUE GX_PARM_GETVARIANTVALUE

struct GX_PARM_ADDVARIANTVALUE
{
	gxVARIANT	 array;
	int			 size;
	int			 type;
	int			 ix;
	int			 nitems;
	const void	*data;
};

struct GX_PARM_REMOVEVARIANTVALUE
{
	gxVARIANT	 array;
	int			 ix;
	int			 nitems;
};

struct GX_PARM_GETVARIANTBYPATH
{
	gxVARIANT		root;
	const wchar_t  *path;
	gxVARIANT		item;
};

struct GX_PARM_GETVARIANTBYPATHA
{
	gxVARIANT	root;
	const char *path;
	gxVARIANT	item;
};

struct GX_PARM_CONVERTVARIANTBYPATH
{
	gxVARIANT		root;
	const wchar_t  *path;
	int				id;
	int				type;
	int				size;
	int				nitems;
	void		   *target;
	int				tgtlen;
};

struct GX_PARM_CONVERTVARIANTBYPATHA
{
	gxVARIANT	root;
	const char *path;
	int			id;
	int			type;
	int			size;
	int			nitems;
	void	   *target;
	int			tgtlen;
};

#endif	/* GX_SWIGIF GX_MANUAL */
/******************************************************************************/
#ifdef GX_DOTNET
	#pragma unmanaged
#endif
/******************************************************************************/
#if !defined(NO_GX_FUNCTIONS) && !defined(GX_SWIGIF)
/******************************************************************************/

/** @name General variant handling
 * @{
 */

/******************************************************************************/
/** Increases a variant's reference counter.
 *
 * The counter indicates the number of threads/entities using the variant. Referencing
 * the variant signs that two or more independent variables share the same memory area.
 * In this case modifying the data structure of a variant affects all the variables.
 * Referencing is useful when the same data is used in different contexts and no
 * independent modifications are required in these contexts.
 *
 * @param variant	Variant to reference.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_refvariant(gxVARIANT variant)
{
	gxHANDLE nullhandle = { 0 };
	assert(variant);
	return gx_call(nullhandle, GX_CALL_REFVARIANT, variant);
}

/******************************************************************************/
/** Decreases a variant's reference counter.
 *
 * The counter indicates the number of threads/entities using the variant. When the
 * counter value becomes zero that means that no one is using the variant so its
 * internally allocated memory is freed. In this case all of its children and list
 * items will be unreferenced too.
 *
 * @param variant	Variant to unreference.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_unrefvariant(gxVARIANT variant)
{
	gxHANDLE nullhandle = { 0 };
	return gx_call(nullhandle, GX_CALL_UNREFVARIANT, variant);
}

/******************************************************************************/
/** Decreases a variant's reference counter and clears the variant variable.
 *
 * The counter indicates the number of threads/entities using the variant. When the
 * counter value becomes zero that means that no one is using the variant so its
 * internally allocated memory is freed. In this case all of its children and list
 * items will be unreferenced too.
 *
 * @param variant	Variant to leave.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_leavevariant(gxVARIANT *variant)
{
	gxHANDLE nullhandle = { 0 };
	int st;
	assert(variant);
	st = gx_call(nullhandle, GX_CALL_UNREFVARIANT, *variant);
	if(st) {
		*variant = (gxVARIANT)0;
	}
	return st;
}

#define gx_disposevariant gx_leavevariant

/******************************************************************************/
/** Duplicates, copies a variant and all of its descendants into a newly allocated memory
 * area.
 *
 * The variants use refernce counter to track the number of threads/entities using them.
 * Modifying the data structure of a variant affects all the variables that references the
 * same memory area. To avoid this behaviour it is possible to duplicate the variant
 * before modification.
 *
 * @param target	Buffer for the result. To free up the used memory call the
 *					gx_unrefvariant() or the gx_leavevariant() function.
 * @param source	Variant to duplicate.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_duplicatevariant(gxVARIANT *target, gxVARIANT source)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_DUPLICATEVARIANT dv;
	int st;
	assert(target);
	dv.source = source;
	st = gx_call(nullhandle, GX_CALL_DUPLICATEVARIANT, &dv);
	if(st) {
		*target = dv.target;
	}
	return st;
}

/** @} */
/** @name Create, modify, read variants
 * @{
 */

/******************************************************************************/
/** Creates a new variant.
 *
 * \note For creating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param variant	Buffer for the result. To free up the used memory call the
 *					gx_unrefvariant() or the gx_leavevariant() function.
 * @param id		The id of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @param data		The data of the new variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariant(gxVARIANT *variant, int id, int type, int size, int nitems, const void *data)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CREATEVARIANT cv;
	int st;
	assert(variant);
	cv.variant = (gxVARIANT)0;
	cv.id = id;
	cv.type = type;
	cv.size = size;
	cv.nitems = nitems;
	cv.data = data;
	st = gx_call(nullhandle, GX_CALL_CREATEVARIANT, &cv);
	if(st) {
		*variant = cv.variant;
	}
	return st;
}

/******************************************************************************/
/** Unreferences the memory area pointed by the variant and creates a new data structure.
 *
 * \note The new variant will have no children after update.
 *
 * @param variant	Buffer for the result.
 * @param id		The new id of the variant.
 * @param type		The new type of the variant.
 * @param size		The new size of the variant.
 * @param nitems	The new number of items of the variant. This value is usually
 *					1, except for list and array types.
 * @param data		The new data of the variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_updatevariant(gxVARIANT *variant, int id, int type, int size, int nitems, const void *data)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANT uv;
	int st;
	uv.variant = *variant;
	uv.id = id;
	uv.type = type;
	uv.size = size;
	uv.nitems = nitems;
	uv.data = data;
	st = gx_call(nullhandle, GX_CALL_UPDATEVARIANT, &uv);
	*variant = uv.variant;
	return st;
}

/******************************************************************************/
/** Modifies the data of a variant.
 *
 * Modifying the data structure of a variant affects all the variables that references the
 * same memory area. Therefore all the modifications are automatically reflected in the data
 * structure of those variants.
 *
 * \note Updating the data structure does not affect the children of the variant.
 * \note For generating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param variant	Variant to modify.
 * @param id		The new id of the variant.
 * @param type		The new type of the variant.
 * @param size		The new size of the variant.
 * @param nitems	The new number of items of the variant. This value is usually
 *					1, except for list and array types.
 * @param data		The new data of the variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_updatevariantdata(gxVARIANT variant, int id, int type, int size, int nitems, const void *data)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTDATA uv;
	assert(variant);
	uv.variant = variant;
	uv.id = id;
	uv.type = type;
	uv.size = size;
	uv.nitems = nitems;
	uv.data = data;
	return gx_call(nullhandle, GX_CALL_UPDATEVARIANTDATA, &uv);
}

/******************************************************************************/
/** Changes the id of a variant.
 *
 * Changing the id of a variant affects all the variables that references the
 * same memory area. Therefore all the modifications are automatically reflected in the data
 * structure of those variants.
 *
 * @param variant	Variant to modify.
 * @param id		The new id of the variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_changevariantid(gxVARIANT variant, int id)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTID uv;
	assert(variant);
	uv.variant = variant;
	uv.id = id;
	return gx_call(nullhandle, GX_CALL_UPDATEVARIANTID, &uv);
}

#define gx_updatevariantid gx_changevariantid

/******************************************************************************/
/** Gives information about a variant.
 *
 * \note Uninterested buffers can be NULL.
 *
 * @param variant	Variant to process.
 * @param id		Buffer for the id.
 * @param type		Buffer for the type.
 * @param size		Buffer for the size.
 * @param nitems	Buffer for the number of items.
 * @param nchildren	Buffer for the number of children.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariant(gxVARIANT variant, int *id, int *type, int *size,
						int *nitems, int *nchildren)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANT gv;
	int st;
	gv.variant = variant;
	st = gx_call(nullhandle, GX_CALL_GETVARIANT, &gv);
	if(st) {
		if(id) *id = gv.id;
		if(type) *type = gv.type;
		if(size) *size = gv.size;
		if(nitems) *nitems = gv.nitems;
		if(nchildren) *nchildren = gv.nchildren;
	}
	return st;
}

/******************************************************************************/
/** Returns a variant's data converted to a specified type.
 *
 * @param variant	Variant to process.
 * @param id		Buffer for the returned id.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariant(gxVARIANT variant, int *id, int type, int *size, int *nitems,
							void *target, int tgtlen)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CONVERTVARIANT cv;
	int st;
	assert(variant);
	cv.variant = variant;
	cv.type = type;
	cv.size = size ? *size : tgtlen;
	cv.nitems = nitems ? *nitems : 1;
	cv.target = target;
	cv.tgtlen = tgtlen;
	st = gx_call(nullhandle, GX_CALL_CONVERTVARIANT, &cv);
	if(st) {
		if(id) *id = cv.id;
		if(size) *size = cv.size;
		if(nitems) *nitems = cv.nitems;
	}
	return st;
}

/** @} */
/** @name Work with list type variants
 * @{
 */

/******************************************************************************/
/** Returns an item from a list type variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested item. On success the variant id is returned.
 * @param ix		Pointer to the index of the requested item. On success the item index is
 *					returned.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantitem(gxVARIANT list, int flags, int *id, int *ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTITEM gi;
	int st;
	assert(list && target);
	gi.list = list;
	gi.flags = flags;
	gi.id = id ? *id : 0;
	gi.ix = ix ? *ix : 0;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTITEM, &gi);
	if(st) {
		if(id) *id = gi.id;
		if(ix) *ix = gi.ix;
		*target = gi.target;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Returns an item from a list type variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested item.
 * @param ix		Index of the requested item.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantitem(gxVARIANT list, int flags, int id, int ix, gxVARIANT *target)
{
	return gx_getvariantitem(list, flags, &id, &ix, target);
}
#endif

/******************************************************************************/
/** Cuts and returns an item from a list type variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the requested item to cut.
 * @param ix		The index of the requested item to cut.
 * @param target	Buffer for the result. To sign the end of usage call the gx_unrefvariant()
 *					or the gx_leavevariant() function. This parameter can be NULL to simply
 *					remove the variant item. In this case the function calls the
 *					\b gx_leavevariant function automatically.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_cutvariantitem(gxVARIANT list, int flags, int id, int ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CUTVARIANTITEM ci;
	int st;
	assert(list);
	ci.list = list;
	ci.flags = flags;
	ci.id = id;
	ci.ix = ix;
	st = gx_call(nullhandle, GX_CALL_CUTVARIANTITEM, &ci);
	if(st) {
		if(target) *target = ci.target;
		else gx_leavevariant(&ci.target);
	}
	return st;
}

/******************************************************************************/
/** Returns the id and the index of a variant element located in a list type variant.
 *
 * @param list	List type variant.
 * @param item	Item of the list to search for.
 * @param id	Buffer for the id of the variant.
 * @param ix	Buffer for the index in the variant list.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_findvariantitem(gxVARIANT list, gxVARIANT item, int *id, int *ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_FINDVARIANTITEM fi;
	int st;
	assert(list && item);
	fi.list = list;
	fi.item = item;
	st = gx_call(nullhandle, GX_CALL_FINDVARIANTITEM, &fi);
	if(st) {
		if(id) *id = fi.id;
		if(ix) *ix = fi.ix;
	}
	return st;
}

/******************************************************************************/
/** Adds an item to a list type variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param list	List type variant.
 * @param flags Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id	The id of the item located on the position where to insert or append the new item.
 * @param ix	The index of the position where to insert or append the new item.
 * @param item	The new item to add to the list. The reference counter of this variant is increased
 *				internally.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_addvariantitem(gxVARIANT list, int flags, int id, int ix, gxVARIANT item)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_ADDVARIANTITEM iv;
	assert(list && item);
	iv.list = list;
	iv.flags = flags;
	iv.id = id;
	iv.ix = ix;
	iv.item = item;
	return gx_call(nullhandle, GX_CALL_ADDVARIANTITEM, &iv);
}

/******************************************************************************/
/** Unreferences and deletes an item from a list type variant.
 *
 * @param list	Variant list to process.
 * @param flags Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id	The id of the item to remove.
 * @param ix	The index of the item to remove.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_removevariantitem(gxVARIANT list, int flags, int id, int ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_REMOVEVARIANTITEM ri;
	ri.list = list;
	ri.flags = flags;
	ri.id = id;
	ri.ix = ix;
	return gx_call(nullhandle, GX_CALL_REMOVEVARIANTITEM, &ri);
}

/******************************************************************************/
/** Creates a new variant and appends to a list type variant.
 *
 * \note For creating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param variant	Buffer for the new variant. It can be NULL. The reference counter
 *					of the new variant will be set to 1 so it does not need unreferencing.
 * @param id		The id of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @param data		The data of the new variant.
 * @param list		List type variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariantitem(gxVARIANT *variant, int id, int type, int size,
								int nitems, const void *data, gxVARIANT list)
{
	gxVARIANT tmp;
	if(!variant) variant = &tmp;
	*variant = 0;
	if(!gx_createvariant(variant, id, type, size, nitems, data)) return 0;
	if(!gx_addvariantitem(list, _GX_VARIANT_LAST, 0, 0, *variant)) {
		gx_pusherror();
		gx_leavevariant(variant);
		gx_poperror();
		return 0;
	}
	return gx_unrefvariant(*variant);
}

/******************************************************************************/
/** Returns the data of an item in a list type variant converted to a specified type.
 *
 * @param variant	List type variant.
 * @param id		Id of the requested item.
 * @param ix		Index of the requested item.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantitem(gxVARIANT variant, int id, int ix, int type,
								 int *size, int *nitems, void *target, int tgtlen)
{
	gxVARIANT fval = 0;
	int st;
	assert(target && tgtlen>0);
	if(!gx_getvariantitem(variant, _GX_VARIANT_BY_ORDER_AND_ID, &id, &ix, &fval)) return 0;
	st = gx_convertvariant(fval, 0, type, size, nitems, target, tgtlen);
	if(!st) gx_pusherror();
	gx_leavevariant(&fval);
	if(!st) gx_poperror();
	return st;
}

/** @} */
/** @name Work with children
 * @{
 */

/******************************************************************************/
/** Returns a child of a variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested child. On success the child id is returned.
 * @param ix		Pointer to the index of the requested child. On success the child index is
 *					returned.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantchild(gxVARIANT parent, int flags, int *id, int *ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTCHILD gc;
	int st;
	assert(parent && target);
	gc.parent = parent;
	gc.flags = flags;
	gc.id = id ? *id : 0;
	gc.ix = ix ? *ix : 0;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTCHILD, &gc);
	if(st) {
		if(id) *id = gc.id;
		if(ix) *ix = gc.ix;
		*target = gc.target;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Returns a child of a variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested child.
 * @param ix		Index of the requested child.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantchild(gxVARIANT parent, int flags, int id, int ix, gxVARIANT *target)
{
	return gx_getvariantchild(parent, flags, &id, &ix, target);
}
#endif

/******************************************************************************/
/** Cuts and returns a child of a variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the requested child to cut.
 * @param ix		The index of the requested child to cut.
 * @param target 	Buffer for the result. To sign the end of usage call the gx_unrefvariant()
 *					or the gx_leavevariant() function. This parameter can be NULL to simply
 *					remove the child. In this case the function calls the \b gx_leavevariant
 *					function automatically.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_cutvariantchild(gxVARIANT parent, int flags, int id, int ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CUTVARIANTCHILD cc;
	int st;
	assert(parent);
	cc.parent = parent;
	cc.flags = flags;
	cc.id = id;
	cc.ix = ix;
	st = gx_call(nullhandle, GX_CALL_CUTVARIANTCHILD, &cc);
	if(st) {
		if(target) *target = cc.target;
		else gx_leavevariant(&cc.target);
	}
	return st;
}

/******************************************************************************/
/** Returns the id and the index of a child element located in a variant's children list.
 *
 * @param parent	Parent variant to process.
 * @param child		Child to search for.
 * @param id		Buffer for the id of the variant.
 * @param ix		Buffer for the index in the children list.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_findvariantchild(gxVARIANT parent, gxVARIANT child, int *id, int *ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_FINDVARIANTCHILD fc;
	int st;
	assert(parent && child);
	fc.parent = parent;
	fc.child = child;
	st = gx_call(nullhandle, GX_CALL_FINDVARIANTCHILD, &fc);
	if(st) {
		if(id) *id = fc.id;
		if(ix) *ix = fc.ix;
	}
	return st;
}

/******************************************************************************/
/** Adds a child element to a variant.
 *
 * \note The actual role of the id and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the child located on the position where to insert or append the new child.
 * @param ix		The index of the position where to insert or append the new child.
 * @param child		The new child to add to the children list. The reference counter of this variant is
 *					increased internally.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_addvariantchild(gxVARIANT parent, int flags, int id, int ix, gxVARIANT child)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_ADDVARIANTCHILD ic;
	assert(parent && child);
	ic.parent = parent;
	ic.flags = flags;
	ic.id = id;
	ic.ix = ix;
	ic.child = child;
	return gx_call(nullhandle, GX_CALL_ADDVARIANTCHILD, &ic);
}

/******************************************************************************/
/** Unreferences and deletes a child of a variant.
 *
 * @param parent	Variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the child to remove.
 * @param ix		The index of the child to remove.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_removevariantchild(gxVARIANT parent, int flags, int id, int ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_REMOVEVARIANTCHILD rc;
	rc.parent = parent;
	rc.flags = flags;
	rc.id = id;
	rc.ix = ix;
	return gx_call(nullhandle, GX_CALL_REMOVEVARIANTCHILD, &rc);
}

/******************************************************************************/
/** Creates a new variant and appends it to a variant as a child.
 *
 * \note For creating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param variant	Buffer for the new variant. It can be NULL. The reference counter
 *					of the new variant will be set to 1 so it does not need unreferencing.
 * @param id		The id of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @param data		The data of the new variant.
 * @param parent	Parent variant to process.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariantchild(gxVARIANT *variant, int id, int type, int size,
								 int nitems, const void *data, gxVARIANT parent)
{
	gxVARIANT tmp;
	if(!variant) variant = &tmp;
	*variant = 0;
	if(!gx_createvariant(variant, id, type, size, nitems, data)) return 0;
	if(!gx_addvariantchild(parent, _GX_VARIANT_LAST, 0, 0, *variant)) {
		gx_pusherror();
		gx_leavevariant(variant);
		gx_poperror();
		return 0;
	}
	return gx_unrefvariant(*variant);
}

/******************************************************************************/
/** Returns the data of a variant's child converted to a specified type.
 *
 * @param variant	Variant to process.
 * @param id		Id of the requested child.
 * @param ix		Index of the requested child.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantchild(gxVARIANT variant, int id, int ix, int type,
								  int *size, int *nitems, void *target, int tgtlen)
{
	gxVARIANT fval = 0;
	int st;
	assert(target && tgtlen>0);
	if(!gx_getvariantchild(variant, _GX_VARIANT_BY_ORDER_AND_ID, &id, &ix, &fval)) return 0;
	st = gx_convertvariant(fval, 0, type, size, nitems, target, tgtlen);
	if(!st) gx_pusherror();
	gx_leavevariant(&fval);
	if(!st) gx_poperror();
	return st;
}

/** @} */
/** @name Work with arrays
 * @{
 */

/******************************************************************************/
/** Returns a part of an array variant's data.
 *
 * @param varray	Array type variant to process.
 * @param size		The expected size of a value in bytes.
 * @param type		Type to convert to (\ref GX_VARIANT_INT, \ref GX_VARIANT_UINT, \ref GX_VARIANT_FLOAT,
					\ref GX_VARIANT_DATETIME, \ref GX_VARIANT_ASCII, \ref GX_VARIANT_UNICODE).
 * @param ix		Index of the first expected value.
 * @param nitems	Number of the expected values.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  void *target, int tgtlen)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTVALUE gv;
	assert(varray);
	gv.array = varray;
	gv.size = size;
	gv.type = type;
	gv.ix = ix;
	gv.nitems = nitems;
	gv.target = target;
	gv.tgtlen = tgtlen;
	return gx_call(nullhandle, GX_CALL_GETVARIANTVALUE, &gv);
}

/******************************************************************************/
/** Cuts and returns a part of an array variant's data.
 *
 * @param varray	Array type variant to process.
 * @param size		The expected size of a value in bytes.
 * @param type		Type to convert to (\ref GX_VARIANT_INT, \ref GX_VARIANT_UINT, \ref GX_VARIANT_FLOAT,
					\ref GX_VARIANT_DATETIME, \ref GX_VARIANT_ASCII, \ref GX_VARIANT_UNICODE).
 * @param ix		Index of the first expected value.
 * @param nitems	Number of the expected values.
 * @param target	Preallocated buffer for the resulted data. This buffer can be NULL
 *					to simply remove the data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_cutvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  void *target GX_DEFARG(0), int tgtlen GX_DEFARG(0))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CUTVARIANTVALUE gv;
	assert(varray);
	gv.array = varray;
	gv.size = size;
	gv.type = type;
	gv.ix = ix;
	gv.nitems = nitems;
	gv.target = target;
	gv.tgtlen = tgtlen;
	return gx_call(nullhandle, GX_CALL_CUTVARIANTVALUE, &gv);
}

/******************************************************************************/
/** Inserts one or more values into an array variant's data.
 *
 * @param varray	Array type variant to process.
 * @param size		Size of an input data value in bytes.
 * @param type		Type of the input data (\ref GX_VARIANT_INT, \ref GX_VARIANT_UINT, \ref GX_VARIANT_FLOAT, \ref GX_VARIANT_DATETIME).
 * @param ix		The index of the position where to insert the data.
 * @param nitems	Number of values to insert.
 * @param data		Pointer to the data to insert.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_addvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  const void *data)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_ADDVARIANTVALUE av;
	assert(varray);
	av.array = varray;
	av.size = size;
	av.type = type;
	av.ix = ix;
	av.nitems = nitems;
	av.data = data;
	return gx_call(nullhandle, GX_CALL_ADDVARIANTVALUE, &av);
}

/******************************************************************************/
/** Removes one or more values from the array.
 *
 * @param array		Array type variant to process.
 * @param ix		Index of the first value.
 * @param nitems	Number of values.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_removevariantvalue(gxVARIANT array, int ix, int nitems)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_REMOVEVARIANTVALUE rv;
	rv.array = array;
	rv.ix = ix;
	rv.nitems = nitems;
	return gx_call(nullhandle, GX_CALL_REMOVEVARIANTVALUE, &rv);
}

/** @} */
/** @name Work with descendant variants
 * @{
 */

/******************************************************************************/
/** Returns a variant from a variant tree.
 *
 * The variant data type can constitute a tree structure: every item in the tree is a variant,
 * and in turn can have child items. The trees can be traversed layer-by-layer with the help
 * of gx_getvariantchild() and gx_getvariantitem() functions. If there is a need to reach a
 * descendant variant located in a deep layer, this function should be used instead. The item
 * in the tree can be obtained by the path string, which defines the exact location of the
 * requested variant and has the following format:
 *
 * condition[=value] [,condition[=value]] [/condition[=value] [,condition[=value]]]
 *
 * The path contains separators:
 * \li the '/' separates the levels of the tree,
 * \li the ',' separates the search conditions of a node,
 * \li the '=' signs that a value follows,
 *
 * and identifiers:
 * \li the 'C' selects a child item,
 * \li the 'L' selects a list item,
 * \li the 'X' signs that the value defines the index of the item,
 * \li the 'D' signs that the value defines the id of the item,
 * \li the 'N' signs that the value defines the name of the item,
 * \li the 'V' signs that the value defines the value of the item.
 *
 * The values are used as integers except 'name' values which have to be quoted with " or ' character;
 * and 'value' values which may be quoted with " or ' character to sign that string comparison is
 * requested. Indexing is made by order. ( see \ref GX_VARIANT_FLAGS )
 *
 * for example:
 * \code
 * // select the 3-rd (started from 0-th) worker whose name is John from the variant
 * swprintf(path, L"C,D=%i/L,N='%s',V='%s',X=%i", ID_WORKERS, L"name", L"John", 3);
 * \endcode
 *
 * @param root	Root variant to process.
 * @param path	The path string.
 * @param item	Buffer for the result. The reference counter of this variant is increased
 *				internally. To sign the end of usage call the gx_unrefvariant() or the
 *				gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantbypath(gxVARIANT root, const wchar_t *path, gxVARIANT *item)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTBYPATH gp;
	int st;
	assert(root && item);
	gp.root = root;
	gp.path = path;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTBYPATH, &gp);
	if(st) {
		*item = gp.item;
	}
	return st;
}

/******************************************************************************/
/** Returns a variant from a variant tree.
 *
 * The variant data type can constitute a tree structure: every item in the tree is a variant,
 * and in turn can have child items. The trees can be traversed layer-by-layer with the help
 * of gx_getvariantchild() and gx_getvariantitem() functions. If there is a need to reach a
 * descendant variant located in a deep layer, this function should be used instead. The item
 * in the tree can be obtained by the path string, which defines the exact location of the
 * requested variant and has the following format:
 *
 * condition[=value] [,condition[=value]] [/condition[=value] [,condition[=value]]]
 *
 * The path contains separators:
 * \li the '/' separates the levels of the tree,
 * \li the ',' separates the search conditions of a node,
 * \li the '=' signs that a value follows,
 *
 * and identifiers:
 * \li the 'C' selects a child item,
 * \li the 'L' selects a list item,
 * \li the 'X' signs that the value defines the index of the item,
 * \li the 'D' signs that the value defines the id of the item,
 * \li the 'N' signs that the value defines the name of the item,
 * \li the 'V' signs that the value defines the value of the item.
 *
 * The values are used as integers except 'name' values which have to be quoted with " or ' character;
 * and 'value' values which may be quoted with " or ' character to sign that string comparison is
 * requested. Indexing is made by order. ( see \ref GX_VARIANT_FLAGS )
 *
 * for example:
 * \code
 * // select the 3-rd (started from 0-th) worker whose name is John from the variant
 * swprintf(path, L"C,D=%i/L,N='%s',V='%s',X=%i", ID_WORKERS, L"name", L"John", 3);
 * \endcode
 *
 * @param root	Root variant to process.
 * @param path	The path string.
 * @param item	Buffer for the result. The reference counter of this variant is increased
 *				internally. To sign the end of usage call the gx_unrefvariant() or the
 *				gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantbypatha(gxVARIANT root, const char *path, gxVARIANT *item)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTBYPATHA gp;
	int st;
	assert(root && item);
	gp.root = root;
	gp.path = path;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTBYPATHA, &gp);
	if(st) {
		*item = gp.item;
	}
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the \ref gx_getvariantbypatha.
 *
 * @param root	Root variant to process.
 * @param path	The path string.
 * @param item	Buffer for the result. The reference counter of this variant is increased
 *				internally. To sign the end of usage call the gx_unrefvariant() or the
 *				gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantbypath(gxVARIANT root, const char *path, gxVARIANT *item)
{
	return gx_getvariantbypatha(root, path, item);
}
#endif

/******************************************************************************/
/** Returns the data of a variant located in a variant tree converted to a specified type.
 *
 * The variant data type can constitute a tree structure: every item in the tree is a variant,
 * and in turn can have child items. The trees can be traversed layer-by-layer with the help
 * of gx_getvariantchild() and gx_getvariantitem() functions and then conversion can be made
 * on some data with the gx_convertvariant() function. If there is a need to reach a
 * descendant variant located in a deep layer for converting just one variant item, this
 * function should be used instead. The item in the tree can be obtained by the path string,
 * which defines the exact location of the requested variant and has the following format:
 *
 * condition[=value] [,condition[=value]] [/condition[=value] [,condition[=value]]]
 *
 * The path contains separators:
 * \li the '/' separates the levels of the tree,
 * \li the ',' separates the search conditions of a node,
 * \li the '=' signs that a value follows,
 *
 * and identifiers:
 * \li the 'C' selects a child item,
 * \li the 'L' selects a list item,
 * \li the 'X' signs that the value defines the index of the item,
 * \li the 'D' signs that the value defines the id of the item,
 * \li the 'N' signs that the value defines the name of the item,
 * \li the 'V' signs that the value defines the value of the item.
 *
 * The values are used as integers except 'name' values which have to be quoted with " or ' character;
 * and 'value' values which may be quoted with " or ' character to sign that string comparison is
 * requested. Indexing is made by order. ( see \ref GX_VARIANT_FLAGS )
 *
 * for example:
 * \code
 * // select the 3-rd (started from 0-th) worker whose name is John from the variant
 * swprintf(path, L"C,D=%i/L,N='%s',V='%s',X=%i", ID_WORKERS, L"name", L"John", 3);
 * \endcode
 *
 * @param root		Root variant to process.
 * @param path		The path string.
 * @param id		Buffer for the returned id.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantbypath(gxVARIANT root, const wchar_t *path, int *id,
						int type, int *size, int *nitems, void *target, int tgtlen)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CONVERTVARIANTBYPATH cp;
	int st;
	assert(root && target && tgtlen>0);
	cp.root = root;
	cp.path = path;
	cp.type = type;
	cp.size = size ? *size : tgtlen;
	cp.nitems = nitems ? *nitems : 1;
	cp.target = target;
	cp.tgtlen = tgtlen;
	st = gx_call(nullhandle, GX_CALL_CONVERTVARIANTBYPATH, &cp);
	if(st) {
		if(id) *id = cp.id;
		if(size) *size = cp.size;
		if(nitems) *nitems = cp.nitems;
	}
	return st;
}

/******************************************************************************/
/** Returns the data of a variant located in a variant tree converted to a specified type.
 *
 * The variant data type can constitute a tree structure: every item in the tree is a variant,
 * and in turn can have child items. The trees can be traversed layer-by-layer with the help
 * of gx_getvariantchild() and gx_getvariantitem() functions and then conversion can be made
 * on some data with the gx_convertvariant() function. If there is a need to reach a
 * descendant variant located in a deep layer for converting just one variant item, this
 * function should be used instead. The item in the tree can be obtained by the path string,
 * which defines the exact location of the requested variant and has the following format:
 *
 * condition[=value] [,condition[=value]] [/condition[=value] [,condition[=value]]]
 *
 * The path contains separators:
 * \li the '/' separates the levels of the tree,
 * \li the ',' separates the search conditions of a node,
 * \li the '=' signs that a value follows,
 *
 * and identifiers:
 * \li the 'C' selects a child item,
 * \li the 'L' selects a list item,
 * \li the 'X' signs that the value defines the index of the item,
 * \li the 'D' signs that the value defines the id of the item,
 * \li the 'N' signs that the value defines the name of the item,
 * \li the 'V' signs that the value defines the value of the item.
 *
 * The values are used as integers except 'name' values which have to be quoted with " or ' character;
 * and 'value' values which may be quoted with " or ' character to sign that string comparison is
 * requested. Indexing is made by order. ( see \ref GX_VARIANT_FLAGS )
 *
 * for example:
 * \code
 * // select the 3-rd (started from 0-th) worker whose name is John from the variant
 * swprintf(path, L"C,D=%i/L,N='%s',V='%s',X=%i", ID_WORKERS, L"name", L"John", 3);
 * \endcode
 *
 * @param root		Root variant to process.
 * @param path		The path string.
 * @param id		Buffer for the returned id.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantbypatha(gxVARIANT root, const char *path, int *id,
						int type, int *size, int *nitems, void *target, int tgtlen)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_CONVERTVARIANTBYPATHA cp;
	int st;
	assert(root && target && tgtlen>0);
	cp.root = root;
	cp.path = path;
	cp.type = type;
	cp.size = size ? *size : tgtlen;
	cp.nitems = nitems ? *nitems : 1;
	cp.target = target;
	cp.tgtlen = tgtlen;
	st = gx_call(nullhandle, GX_CALL_CONVERTVARIANTBYPATHA, &cp);
	if(st) {
		if(id) *id = cp.id;
		if(size) *size = cp.size;
		if(nitems) *nitems = cp.nitems;
	}
	return st;
}

#ifdef __cplusplus
/** Usable in C++. It is the same function as the \ref gx_convertvariantbypatha.
 *
 * @param root		Root variant to process.
 * @param path		The path string.
 * @param id		Buffer for the returned id.
 * @param type		Type to convert to.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantbypath(gxVARIANT root, const char *path, int *id,
						int type, int *size, int *nitems, void *target, int tgtlen)
{
	return gx_convertvariantbypatha(root, path, id, type, size, nitems, target, tgtlen);
}
#endif

/** @} */

#endif

/******************************************************************************/
#ifdef GX_DOTNET
	#pragma managed
#endif
/******************************************************************************/

/******************************************************************************/
#if !defined(NO_GX_CLASSES) && !defined(ANDROID)
/******************************************************************************/
#ifndef GX_EXT_MODULE
/******************************************************************************/
/** Class for the VARIANT functions. */
GX_CLASS gxVariant
#ifdef GX_DOTNET
: public System::IDisposable
#endif
{
public:

#if !defined(GX_SWIGIF) && !defined(GX_MANUAL)

#ifdef GX_DOTNET
	#ifndef GX_DOTNET_20
	private public:
	#else
	internal:
	#endif
#endif
	gxVARIANT	_variant;	/**< Internal variable to store class data. */
#endif /* GX_SWIGIF */
#ifndef GX_SWIGIF
	/** Copy constructor from variant structure.
	 *
	 * @param source	Source variant. */
	inline explicit gxVariant(gxVARIANT source) {
		if(!gx_refvariant(source)) gxthrow;
		_variant = source;
	}
#endif

#ifdef GX_DOTNET
public:
	/** Returns the local variant data.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @return Current value. */
	inline gxOutPtr _get_variant(void) GX_CONST {
		return GX_PUTPTR(_variant);
	}
	/** Modifies the local variant data.
	 *
	 * \attention Do not use this function directly.
	 *
	 * @param ptr	New value. */
	inline void _set_variant(gxInPtr ptr) {
		_variant = (gxVARIANT)GX_GETPTR(ptr);
	}
#endif

public:
	/** Constructor. */
	inline gxVariant() {
		_variant = (gxVARIANT)0;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Copy constructor.
	 *
	 * @param source	Source variant. */
	inline gxVariant(gxVariant &source) {
		if(!gx_refvariant(source)) gxthrow;
		_variant = source._variant;
	}
#endif
	/** Destructor. */
	inline ~gxVariant() gxFuncThrowsError {
		_Dispose();
	}
#ifdef GX_DOTNET_20
	inline !gxVariant() gxFuncThrowsError {
		_Dispose();
	}
#else
		/** It disposes the class. */
	inline void Dispose(void) {
#ifdef GX_DOTNET
		System::GC::SuppressFinalize(this);
#endif
		_Dispose();
	 /** no base class. */
	}
#endif

private:

	/** Deletes the variant. */
	inline void _Dispose(void) {
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) gxthrow;
		_variant = 0;
	}

public:

	/** References the variant.
	 *
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Ref(void) gxFuncThrowsError {
		bool st = gx_refvariant(_variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Unreferences the variant.
	 *
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Unref(void) gxFuncThrowsError {
		bool st = gx_unrefvariant(_variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Copy operator.
	 *
	 * @param source	Source variant to copy from.
	 * @return	Returns a reference to the variant class. */
	gxVariant& operator = (gxVariant source) gxFuncThrowsError {
		if(!gx_refvariant(source)) gxthrow;
		if(_variant && !gx_unrefvariant(_variant)) {
			gx_pusherror();
			gx_unrefvariant(source);
			gx_poperror();
			gxthrow;
		}
		_variant = source._variant;
		return *this;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param type		Type of the new variant.
	 * @param size		Size of the new variant.
	 * @param nitems	Number of items in the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, int type, int size, int nitems, const void *data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, type, size, nitems, data) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxInData data) gxFuncThrowsError {
		GX_GETDATA(data);
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_UINTARRAY, 1, GX_DATALEN(data), GX_DATAPTR(data)) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}
#endif

	/** Creates an empty variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param type		Type of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateEmpty(int id, int type) gxFuncThrowsError {
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, type, 0, 0, (const void *)0) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param size		Size of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, const void *data, int size) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_BINARY, size, 1, data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxi8 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxi16 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxi32 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxi64 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxu8 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxu16 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxu32 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxu64 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxf32 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_FLOAT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxf64 data) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_FLOAT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#else
	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, int data) gxFuncThrowsError {
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_INT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}
	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param data		Binary data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, double data) gxFuncThrowsError {
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_FLOAT, sizeof(data), 1, &data) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a new variant structure (ASCII version).
	 *
	 * @param id		Id of the new variant.
	 * @param ascii		String data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, const char *ascii) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		int l = ascii ? 1+(int)(int)strlen(ascii) : 0;
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_ASCII, l, 1, ascii) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant structure (Unicode version).
	 *
	 * @param id		Id of the new variant.
	 * @param unicode	String data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, const wchar_t *unicode) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		int l = unicode ? 1+(int)(int)wcslen(unicode) : 0;
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UNICODE, l, 1, unicode) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Creates a new variant structure (ASCII version).
	 *
	 * @param id		Id of the new variant.
	 * @param ascii		String data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxInAStr ascii) gxFuncThrowsError {
		GX_GETASTRING(_ascii, ascii);
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		int l = _ascii ? 1+(int)strlen(_ascii) : 0;
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_ASCII, l, 1, _ascii) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#ifdef GX_UNICODE
	/** Creates a new variant structure (Unicode version).
	 *
	 * @param id		Id of the new variant.
	 * @param unicode	String data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxInStr unicode) gxFuncThrowsError {
		GX_GETSTRING(_unicode, unicode);
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		int l = _unicode ? 1+(int)wcslen(_unicode) : 0;
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_UNICODE, l, 1, _unicode) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}
#endif

	/** Creates a new variant structure.
	 *
	 * @param id		Id of the new variant.
	 * @param frame		Frame data of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(int id, gxPG4 frame) gxFuncThrowsError {
		int nitems = 8;
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_INTARRAY, sizeof(int), nitems, &frame) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxi8 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INTARRAY, sizeof(gxi8), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxi16 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INTARRAY, sizeof(gxi16), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxi32 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INTARRAY, sizeof(gxi32), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxi64 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_INTARRAY, sizeof(gxi64), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxu8 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINTARRAY, sizeof(gxu8), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxu16 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINTARRAY, sizeof(gxu16), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxu32 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINTARRAY, sizeof(gxu32), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxu64 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_UINTARRAY, sizeof(gxu64), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}


	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxf32 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_FLOATARRAY, sizeof(gxf32), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Creates a new variant array structure.
	 *
	 * @param id		Id of the new variant array.
	 * @param array		Binary data of the new variant array.
	 * @param nitems	Number of items in the new variant array.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateArray(int id, const gxf64 *array, int nitems) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&_variant, id, GX_VARIANT_FLOATARRAY, sizeof(gxf64), nitems, array) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Creates an empty variant list structure.
	 *
	 * @param id		Id of the new variant list.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateEmptyList(int id) gxFuncThrowsError {
		gxVARIANT t = _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_createvariant(&t, id, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_LIST, 0, 0, 0) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Creates a new variant structure from an existing variant.
	 *
	 * @param source	Source variant structure to duplicate.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(gxVARIANT source) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}
		bool st = gx_duplicatevariant(&_variant, source) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif

	/** Creates a new variant structure from an existing variant.
	 *
	 * @param source	Source variant structure to duplicate.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool Create(gxVariant GX_REF_CLASS(source)) gxFuncThrowsError {
		gxVARIANT t = _variant;
		gxVARIANT s = source GX_M _variant;
		if(t && !gx_disposevariant(&t)) {
			gxthrow;
			return false;
		}
		bool st = gx_duplicatevariant(&t, s) ? true : false;
		gxcondthrow(!st);
		_variant = t;
		return st;
	}

	/******************************************************************************/

#if !defined(GX_MANUAL)
#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	inline bool _Get(int *id, int *type, int *size, int *nitems, int *nchildren) gxFuncThrowsError {
		bool st = gx_getvariant(_variant, id, type, size, nitems, nchildren) ? true : false;
		gxcondthrow(!st);
		return st;
	}
#endif
#endif

	/** Returns the variant's id. */
	inline int GetID(void) gxFuncThrowsError {
		int ret = -1;
		if(!gx_getvariant(_variant, &ret, 0, 0, 0, 0)) gxthrow;
		return ret;
	}

	/** Returns the variant's type. */
	inline int GetType(void) gxFuncThrowsError {
		int ret = 0;
		if(!gx_getvariant(_variant, 0, &ret, 0, 0, 0)) gxthrow;
		return ret;
	}

	/** Returns the variant's size. */
	inline int GetSize(void) gxFuncThrowsError {
		int ret = 0;
		if(!gx_getvariant(_variant, 0, 0, &ret, 0, 0)) gxthrow;
		return ret;
	}

	/** Returns the variant's number of items. */
	inline int GetNItems(void) gxFuncThrowsError {
		int ret = 0;
		if(!gx_getvariant(_variant, 0, 0, 0, &ret, 0)) gxthrow;
		return ret;
	}

	/** Returns the variant's number of children. */
	inline int GetNChildren(void) gxFuncThrowsError {
		int ret = 0;
		if(!gx_getvariant(_variant, 0, 0, 0, 0, &ret)) gxthrow;
		return ret;
	}

	/** Returns the variant's data as an integer number. */
	inline int GetInt(void) gxFuncThrowsError {
		int size = sizeof(int), nitems = 1, ret = 0;
		if(!gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_INT, &size, &nitems, &ret, sizeof(ret))) gxthrow;
		return ret;
	}

	/** Returns the variant's data as an unsigned integer number. */
	inline unsigned int GetUInt(void) gxFuncThrowsError {
		int size = sizeof(int), nitems = 1;
		unsigned int ret = 0;
		if(!gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_UINT, &size, &nitems, &ret, sizeof(ret))) gxthrow;
		return ret;
	}

	/** Returns the variant's data as an unsigned integer number. */
	inline gxu64 GetULInt(void) gxFuncThrowsError {
		int size = sizeof(gxu64), nitems = 1;
		gxu64 ret = 0;
		if(!gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_UINT, &size, &nitems, &ret, sizeof(ret))) gxthrow;
		return ret;
	}


	/** Returns the variant's data as a float number. */
	inline double GetFloat(void) gxFuncThrowsError {
		int size = sizeof(double), nitems = 1;
		double ret = 0;
		if(!gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_FLOAT, &size, &nitems, &ret, sizeof(ret))) gxthrow;
		return ret;
	}

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Gets the variant's data as a string (ASCII version).
	 *
	 * @param target	Preallocated buffer for the result.
	 * @param tgtlen	Size of the preallocated buffer.
	 * @return	Returns the number of characters in the string. */
	inline int GetASCII(char *target, int tgtlen) gxFuncThrowsError {
		int size = tgtlen, nitems = 1;
		if(!gx_convertvariant(_variant, 0, GX_VARIANT_ASCII, &size, &nitems, target, tgtlen)) gxthrow;
		return size;
	}

	/** Gets the variant's data as a string (Unicode version).
	 *
	 * @param target	Preallocated buffer for the result.
	 * @param tgtlen	Size of the preallocated buffer.
	 * @return	Returns the number of characters in the string. */
	inline int GetUnicode(wchar_t *target, int tgtlen) gxFuncThrowsError {
		int size = tgtlen, nitems = 1;
		if(!gx_convertvariant(_variant, 0, GX_VARIANT_UNICODE, &size, &nitems, target, tgtlen*sizeof(wchar_t))) gxthrow;
		return size;
	}
#endif
#ifdef GX_UNICODE
	/** Returns the variant's data as a string (Unicode version).
	 *
	 * @param tgtlen	Maximum number of characters to return.
	 * @return	The variant's data as a string. */
	inline gxOutStr GetUnicode(int tgtlen) gxFuncThrowsError {
		wchar_t *buffer;
		int size = tgtlen, nitems = 1;
		if(tgtlen < 1) return GX_PUTSTRING_NONE;
		if(!gx_globalalloc((void **)(void *)&buffer, sizeof(wchar_t)*(tgtlen+1))) {
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		if(!gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_UNICODE, &size, &nitems, buffer, tgtlen*sizeof(wchar_t))) {
			gx_globalfree(buffer);
			gxthrow;
			return GX_PUTSTRING_NONE;
		}
		buffer[tgtlen] = 0;
		gxOutStr ret = GX_PUTSTRING(buffer);
		gx_globalfree(buffer);
		return ret;
	}
#endif
#ifdef GX_ASCII
	/** Returns the variant's data as a string (ASCII version).
	 *
	 * @param tgtlen	Maximum number of characters to return.
	 * @return	The variant's data as a string. */
	inline gxOutAStr GetASCII(int tgtlen) gxFuncThrowsError {
		char *buffer;
		int size = tgtlen, nitems = 1;
		if(tgtlen < 1) return GX_PUTASTRING_NONE;
		if(!gx_globalalloc((void **)(void *)&buffer, sizeof(char)*(tgtlen+1))) {
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		if(!gx_convertvariant(_variant, 0, GX_VARIANT_ASCII, &size, &nitems, buffer, tgtlen*sizeof(char))) {
			gx_globalfree(buffer);
			gxthrow;
			return GX_PUTASTRING_NONE;
		}
		buffer[tgtlen] = 0;
		gxOutAStr ret = GX_PUTASTRING(buffer);
		gx_globalfree(buffer);
		return ret;
	}
#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns the variant's data converted to the specified type.
	 *
	 * @param type		Type to convert to.
	 * @param size		Buffer for the size
	 * @param nitems	Buffer for the number of items.
	 * @param target	Preallocated buffer for the resulted data.
	 * @param tgtlen	Size of the preallocated buffer.
	 * @return	Returns the number of items of the variant. */
	inline int Convert(int type, int *size, int *nitems, void *target, int tgtlen) gxFuncThrowsError {
		int ret = 0;
		if(!gx_convertvariant(_variant, 0, type, size, nitems, target, tgtlen)) {
			gxthrow;
		} else {
			ret = nitems ? *nitems : 0;
		}
		return ret;
	}
#endif

	/******************************************************************************/

	/** Returns the requested item from the variant list.
	 *
	 * \note Depending on the flags the index specifies the index of the requested item itself or
	 * the starting index for searching for the item with the specified id.
	 *
	 * @param target	Buffer for the result.
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
	 * @param id		Id of the requested item.
	 * @param ix		Index of the requested item.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetItem(gxVariant GX_REF_CLASS(target), int flags, int id, int ix) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_getvariantitem(_variant, flags, &id, &ix, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target GX_M _variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target GX_M _variant = t2;
		}
		return st;
	}

	/** Cuts and returns the requested item from the variant list.
	 *
	 * \note Depending on the flags the index specifies the index of the requested item itself or
	 * the starting index for searching for the item with the specified id.
	 *
	 * @param target	Buffer for the result.
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
	 * @param id		The id of the requested to remove.
	 * @param ix		Thi index of the requested item in the variable list.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CutItem(gxVariant GX_REF_CLASS(target), int flags, int id, int ix) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_cutvariantitem(_variant, flags, id, ix, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target GX_M _variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target GX_M _variant = t2;
		}
		return st;
	}

	/** Searches for a variant in the items list.
	 *
	 * @param item	Variant item to search for.
	 * @return	The index of the item or -1 if not found. */
	inline int FindItem(gxVariant GX_REF_CLASS(item)) {
		int			ix,id;
		gxVARIANT t = item GX_M _variant;
		int st = gx_findvariantitem(_variant, t, &id, &ix);
		gxcondthrow(!st);
		return st ? ix : -1;
	}

	/** Adds a new item to the items list.
	 *
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id		The id of the item located on the position where to insert or append the new item.
	 * @param ix		The index of the position where to insert or append the new item.
	 * @param item		The new item to add to the list.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool AddItem(int flags, int id, int ix, gxVariant GX_REF_CLASS(item)) {
		bool st = gx_addvariantitem(_variant, flags, id, ix, item GX_M _variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Unreferences and deletes the item from the items list.
	 *
	 * @param flags Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id	The id of the item to remove.
	 * @param ix	The index of the item to remove.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool RemoveItem(int flags, int id, int ix) gxFuncThrowsError {
		bool st = gx_removevariantitem(_variant, flags, id, ix) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/

	/** Returns a child from the children list.
	 *
	 * @param target	Preinitialized variant structure to return the result.
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id		The id of the child.
	 * @param ix		The index of the child.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetChild(gxVariant GX_REF_CLASS(target), int flags, int id, int ix) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_getvariantchild(_variant, flags, id, ix, &t) ? true : false;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target GX_M _variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target GX_M _variant = t2;
		}
		return st;
	}

	/** Cuts a child from the children list.
	 *
	 * @param target	Preinitialized variant structure to return the result.
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id		The id of the child.
	 * @param ix		The index of the child.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CutChild(gxVariant GX_REF_CLASS(target), int flags, int id, int ix) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_cutvariantchild(_variant, flags, id, ix, &t) ? true : false;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target GX_M _variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target GX_M _variant = t2;
		}
		return st;
	}

	/** Searches for a child in the children list.
	 *
	 * @param item		The child to search for.
	 * @return	The index of the child in the children list or -1 if not found. */
	inline int FindChild(gxVariant GX_REF_CLASS(item)) {
		int			ix,id;
		gxVARIANT t = item GX_M _variant;
		int st = gx_findvariantchild(_variant, t, &id, &ix);
		gxcondthrow(!st);
		return st ? ix : -1;
	}

	/** Adds a child to the children list.
	 *
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id		The id of the item located on the position where to insert or append the new child.
	 * @param ix		The index of the position where to insert or append the new child.
	 * @param item		The new child to add to the children's list.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool AddChild(int flags, int id, int ix, gxVariant GX_REF_CLASS(item)) {
		bool st = gx_addvariantchild(_variant, flags, id, ix, item GX_M _variant) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Removes a child from the children list.
	 *
	 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS ).
	 * @param id		The id of the child.
	 * @param ix		The index of the position where the child is.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool RemoveChild(int flags, int id, int ix) gxFuncThrowsError {
		bool st = gx_removevariantitem(_variant, flags, id, ix) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
#ifndef GX_DOTNET
	/** Creates a list type variant.
	 *
	 * \note Usage: CreateList(id, [ itype, iid, isize, initems, idata ], -1)
	 *
	 * @param id		The id of the new variant.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool CreateList(int id, ...) gxFuncThrowsError {
		if(_variant && !gx_disposevariant(&_variant)) {
			gxthrow;
			return false;
		}

		bool st = gx_createvariant(&_variant, id, GX_VARIANT_LIST, 0, 0, 0) ? true : false;
		if(!st) {
			gxthrow;
			return false;
		}

		va_list(args);
		va_start(args, id);
		gxVARIANT val;
		int itype=0, iid, isize, initems;
		const void *idata;
		while(itype >= 0) {
			itype = va_arg(args, int);
			if(itype < 0) break;
			iid = va_arg(args, int);
			isize = va_arg(args, int);
			initems = va_arg(args, int);
			idata = va_arg(args, const void *);

			st = gx_createvariant(&val, iid, itype, isize, initems, idata) ? true : false;
			if(!st) {
				va_end(args);
				gxthrow;
				return false;
			}

			st = gx_addvariantitem(_variant, GX_VARIANT_LAST, 0, 0, val) ? true : false;
			gx_disposevariant(&val);
			if(!st) {
				va_end(args);
				gxthrow;
				return false;
			}
		}
		va_end(args);
		return true;
	}

#if !defined(GX_SWIGIF) && !defined(GX_DOTNET)
	/** Reference operator. */
	inline operator gxVARIANT & () gxFuncThrowsError {
		return _variant;
	}
#endif
/*
	inline operator gxVARIANT * () gxFuncThrowsError {
		return &_variant;
	}
	inline operator const gxVARIANT * () const gxFuncThrowsError {
		return &_variant;
	}
*/

#endif

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/******************************************************************************/
	/** Returns the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool GetIntValue(int ix, int nitems, int *target) gxFuncThrowsError {
		bool st = gx_getvariantvalue(_variant, sizeof(int), GX_VARIANT_INT, ix, nitems,
						target, sizeof(int)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Returns the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool GetUIntValue(int ix, int nitems, unsigned int *target) gxFuncThrowsError {
		bool st = gx_getvariantvalue(_variant, sizeof(unsigned int), GX_VARIANT_UINT, ix, nitems,
						target, sizeof(unsigned int)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Returns the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool GetFloatValue(int ix, int nitems, double *target) gxFuncThrowsError {
		bool st = gx_getvariantvalue(_variant, sizeof(double), GX_VARIANT_FLOAT, ix, nitems,
						target, sizeof(double)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Returns and removes the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool CutIntValue(int ix, int nitems, int *target) gxFuncThrowsError {
		bool st = gx_cutvariantvalue(_variant, sizeof(int), GX_VARIANT_INT, ix, nitems,
						target, sizeof(int)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Returns and removes the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool CutUIntValue(int ix, int nitems, unsigned int *target) gxFuncThrowsError {
		bool st = gx_cutvariantvalue(_variant, sizeof(unsigned int), GX_VARIANT_UINT, ix, nitems,
						target, sizeof(unsigned int)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Returns and removes the requested variant value from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param target	Preallocated buffer for the result. */
	inline bool CutFloatValue(int ix, int nitems, double *target) gxFuncThrowsError {
		bool st = gx_cutvariantvalue(_variant, sizeof(double), GX_VARIANT_FLOAT, ix, nitems,
						target, sizeof(double)*nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/******************************************************************************/
	/** Inserts one or more values into the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param data		Pointer to the source data. */
	inline bool AddIntValue(int ix, int nitems, const int *data) gxFuncThrowsError {
		bool st = gx_addvariantvalue(_variant, sizeof(int), GX_VARIANT_INT, ix, nitems, data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inserts one or more values into the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param data		Pointer to the source data. */
	inline bool AddUIntValue(int ix, int nitems, const unsigned int *data) gxFuncThrowsError {
		bool st = gx_addvariantvalue(_variant, sizeof(int), GX_VARIANT_UINT, ix, nitems, data) ? true : false;
		gxcondthrow(!st);
		return st;
	}

	/** Inserts one or more values into the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values.
	 * @param data		Pointer to the source data. */
	inline bool AddFloatValue(int ix, int nitems, const double *data) gxFuncThrowsError {
		bool st = gx_addvariantvalue(_variant, sizeof(double), GX_VARIANT_FLOAT, ix, nitems, data) ? true : false;
		gxcondthrow(!st);
		return st;
	}


	/** Removes one or more values from the array.
	 *
	 * @param ix		Index of the first value.
	 * @param nitems	Number of values. */
	inline bool RemoveValue(int ix, int nitems) gxFuncThrowsError {
		bool st = gx_removevariantvalue(_variant, ix, nitems) ? true : false;
		gxcondthrow(!st);
		return st;
	}

#endif

	/******************************************************************************/
	/** Returns the variant value as a \ref gxPG4 structure. */
	inline gxPG4 GetGxPG4() gxFuncThrowsError {
		int val[8];
		memset(val, 0, sizeof(val));
		int size = sizeof(int);
		int nitems = 8;
		bool st = gx_convertvariant(_variant, 0, (int)GX_ENUM_PATH(GX_VARIANT_TYPES) GX_VARIANT_INTARRAY, &size, &nitems,
						val, sizeof(val)) ? true : false;
		gxcondthrow(!st);
		if(!st) st = false;
		gxPG4 pg4;
		pg4.x1 = val[0];
		pg4.y1 = val[1];
		pg4.x2 = val[2];
		pg4.y2 = val[3];
		pg4.x3 = val[4];
		pg4.y3 = val[5];
		pg4.x4 = val[6];
		pg4.y4 = val[7];
		return pg4;
	}

	/******************************************************************************/

#if !defined(GX_SWIG) && !defined(GX_DOTNET)
	/** Returns a variant from a tree.
	 *
	 * The variant data type can constitute a tree structure: every item in the
	 * tree is also a variant, and in turn can have child items.  The item in the tree can be
	 * obtained by the path string, which has the following format:
	 *
	 * condition[=value][,condition[=value]][/condition[=value][,condition[=value]]]
	 *
	 * \li 1. the / character separates the levels of items in the tree
	 * \li 2. the , character separates the search conditions
	 * \li 3. the = character means the equality condition
	 * \li 4. the C character selects a child item
	 * \li 5. the L character selects a list item
	 * \li 6. the X character means the index of the item
	 * \li 7. the D character means the id of the item
	 * \li 8. the V character means the value of the item
	 *
	 * for example:
	 * \code
	 * // get MRZ_NAME field from passport reader document object
	 * swprintf(path,L"C,D=%i/L,D=%i,V=%i",PRV_FIELDLIST,PRV_FIELD,PR_DF_MRZ_NAME);
	 * \endcode
	 *
	 * @param target	Buffer for the result.
	 * @param path		The path string.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetItemByPath(gxVariant &target, const wchar_t *path) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_getvariantbypath(_variant, path, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target._variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target._variant = t2;
		}
		return st;
	}

	/** Returns a variant from a tree.
	 *
	 * The variant data type can constitute a tree structure: every item in the
	 * tree is also a variant, and in turn can have child items.  The item in the tree can be
	 * obtained by the path string, which has the following format:
	 *
	 * condition[=value][,condition[=value]][/condition[=value][,condition[=value]]]
	 *
	 * \li 1. the / character separates the levels of items in the tree
	 * \li 2. the , character separates the search conditions
	 * \li 3. the = character means the equality condition
	 * \li 4. the C character selects a child item
	 * \li 5. the L character selects a list item
	 * \li 6. the X character means the index of the item
	 * \li 7. the D character means the id of the item
	 * \li 8. the V character means the value of the item
	 *
	 * for example:
	 * \code
	 * // get MRZ_NAME field from passport reader document object
	 * sprintf(path,"C,D=%i/L,D=%i,V=%i",PRV_FIELDLIST,PRV_FIELD,PR_DF_MRZ_NAME);
	 * \endcode
	 *
	 * @param target	Buffer for the result.
	 * @param path		The path string.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetItemByPath(gxVariant &target, const char *path) gxFuncThrowsError {
		gxVARIANT t;
		bool st = gx_getvariantbypath(_variant, path, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target._variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target._variant = t2;
		}
		return st;
	}
#endif

#ifdef GX_UNICODE
	/** Returns a variant from a tree.
	 *
	 * The variant data type can constitute a tree structure: every item in the
	 * tree is also a variant, and in turn can have child items.  The item in the tree can be
	 * obtained by the path string, which has the following format:
	 *
	 * condition[=value][,condition[=value]][/condition[=value][,condition[=value]]]
	 *
	 * \li 1. the / character separates the levels of items in the tree
	 * \li 2. the , character separates the search conditions
	 * \li 3. the = character means the equality condition
	 * \li 4. the C character selects a child item
	 * \li 5. the L character selects a list item
	 * \li 6. the X character means the index of the item
	 * \li 7. the D character means the id of the item
	 * \li 8. the V character means the value of the item
	 *
	 * for example:
	 * \code
	 * // get MRZ_NAME field from passport reader document object
	 * path=String.Format("C,D=%i/L,D=%i,V=%i",PRV_FIELDLIST,PRV_FIELD,PR_DF_MRZ_NAME);
	 * \endcode
	 *
	 * @param target	Buffer for the result.
	 * @param path		The path string.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetItemByPath(gxVariant GX_REF_CLASS(target), gxInStr path) gxFuncThrowsError {
		gxVARIANT t;
		GX_GETSTRING(_path, path);
		bool st = gx_getvariantbypath(_variant, _path, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target GX_M _variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target GX_M _variant = t2;
		}
		return st;
	}
#endif

#ifdef GX_ASCII
	/** Returns a variant from a tree.
	 *
	 * The variant data type can constitute a tree structure: every item in the
	 * tree is also a variant, and in turn can have child items.  The item in the tree can be
	 * obtained by the path string, which has the following format:
	 *
	 * condition[=value][,condition[=value]][/condition[=value][,condition[=value]]]
	 *
	 * \li 1. the / character separates the levels of items in the tree
	 * \li 2. the , character separates the search conditions
	 * \li 3. the = character means the equality condition
	 * \li 4. the C character selects a child item
	 * \li 5. the L character selects a list item
	 * \li 6. the X character means the index of the item
	 * \li 7. the D character means the id of the item
	 * \li 8. the V character means the value of the item
	 *
	 * for example:
	 * \code
	 * // get MRZ_NAME field from passport reader document object
	 * path=String.Format("C,D=%i/L,D=%i,V=%i",PRV_FIELDLIST,PRV_FIELD,PR_DF_MRZ_NAME);
	 * \endcode
	 *
	 * @param target	Buffer for the result.
	 * @param path		The path string.
	 * @return	On error false is returned or an exception is thrown. */
	inline bool GetItemByPath(gxVariant &target, gxInAStr path) gxFuncThrowsError {
		gxVARIANT t;
		GX_GETASTRING(_path, path);
		bool st = gx_getvariantbypath(_variant, _path, &t)!=0;
		gxcondthrow(!st);
		if(st) {
			gxVARIANT t2 = target._variant;
			if(t2 && !gx_disposevariant(&t2)) {
				st = false;
			} else {
				st = gx_duplicatevariant(&t2, t) ? true : false;
			}
			if(st) {
				st = gx_disposevariant(&t) ? true : false;
			}
			gxcondthrow(!st);
			target._variant = t2;
		}
		return st;
	}
#endif

};
/******************************************************************************/
#endif	/* GX_EXT_MODULE */
/******************************************************************************/
#endif	/* NO_GX_CLASSES && !ANDROID */
/******************************************************************************/
#ifdef GX_NAMESPACES
	}	/* namespace */
#endif
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
/******************************************************************************/
#endif
/******************************************************************************/
