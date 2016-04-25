/******************************************************************************
 * GX variants - V7.2.10.1
 *
 * 2006-2013 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/
#if defined(__cplusplus) || defined(USE_COMPAT_VARIANT_1)
	#include "gxvariant_compat.h"
	#if defined(GX_SWIG) || defined(GX_DOTNET) || defined(USE_COMPAT_VARIANT_1)
		#define GX_VARIANT_INCL
	#endif
#endif
/******************************************************************************/
#ifndef GX_VARIANT_INCL
#define GX_VARIANT_INCL
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
#endif
/******************************************************************************/
#ifndef GX_VARIANT_CPT_INCL
/******************************************************************************/
/** Empty structure type to map the variant type. */
struct GX_VARIANT;

/** Defining the variant type as a pointer to an empty structure (no automatic typecasts). */
typedef struct GX_VARIANT* gxVARIANT;

/** Available variant types.
 * \note The values with \e \b _AC_ tag are usable in creation operation only. For
 * these types the value is automatically converted to the proper data type.
 * \note The values with \e \b _AS_ tag are usable in creation operation only. For
 * these types the value is automatically converted to the proper string type.
 */
enum GX_VARIANT_TYPES
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

#ifndef GX_MANUAL

#ifndef __cplusplus
typedef enum GX_VARIANT_TYPES GX_VARIANT_TYPES;
#endif

/******************************************************************************
 * General variant handling													  *
 ******************************************************************************/

/* Increases a variant's reference counter. It signs the intention of usage in a multithreading environment. */
inline int gx_refvariant(gxVARIANT variant);

/* Decreases a variant's reference counter. It signs the end of usage in a multithreading environment. */
inline int gx_unrefvariant(gxVARIANT variant);

/* Decreases a variant's reference counter and clears the variant variable. */
inline int gx_leavevariant(gxVARIANT *variant);

/* Duplicates, copies a variant and all of its descendants into a newly allocated memory area. */
inline int gx_duplicatevariant(gxVARIANT *target, gxVARIANT source);

/******************************************************************************
 * Create, modify, read variants											  *
 ******************************************************************************/

/* Creates a new variant. */
inline int gx_createvariant(gxVARIANT *variant, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
							const void *data, int nitems);

/* Modifies a variant. */
inline int gx_updatevariant(gxVARIANT variant, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
							const void *data, int nitems);

/* Modifies the data of a variant. */
inline int gx_updatevariantdata(gxVARIANT variant, GX_VARIANT_TYPES type, int size, const void *data,
								int nitems);

/* Changes the id of a variant. */
inline int gx_changevariantid(gxVARIANT variant, int id);

/* Changes the name of a variant. */
inline int gx_changevariantname(gxVARIANT variant, const wchar_t *name);

/* Gives information about a variant. */
inline int gx_getvariantinfo(gxVARIANT variant, int *id, wchar_t *namebuff, int namebuffsize,
							 GX_VARIANT_TYPES *type, int *size, int *nitems, int *nchildren);

/* Returns a variant's data converted to a specified type. */
inline int gx_convertvariant(gxVARIANT variant, GX_VARIANT_TYPES type, void *target, int tgtlen,
							 int *size, int *nitems);

/******************************************************************************
 * Work with list type variants												  *
 ******************************************************************************/

/* Returns an item from a list type variant. */
inline int gx_getvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int *ix, gxVARIANT *target);
#ifdef __cplusplus
inline int gx_getvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target);
#endif

/* Cuts and returns an item from a list type variant. */
inline int gx_cutvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target);

/* Returns the index of a variant element located in a list type variant. */
inline int gx_findvariantitem(gxVARIANT list, gxVARIANT item, int flags, int *ix);

/* Adds an item to a list type variant. */
inline int gx_addvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT item);

/* Creates a new variant and appends to a list type variant. */
inline int gx_createvariantitem(gxVARIANT list, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
								const void *data, int nitems, gxVARIANT *item);

/* Returns the data of an item in a list type variant converted to a specified type. */
inline int gx_convertvariantitem(gxVARIANT list, int id, const wchar_t *name, int ix, GX_VARIANT_TYPES type,
								 void *target, int tgtlen, int *size, int *nitems);

/******************************************************************************
 * Work with children														  *
 ******************************************************************************/

/* Returns a child of a variant. */
inline int gx_getvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int *ix, gxVARIANT *target);
#ifdef __cplusplus
inline int gx_getvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target);
#endif

/* Cuts and returns a child of a variant. */
inline int gx_cutvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target);

/* Returns the index of a child element located in a variant's children list. */
inline int gx_findvariantchild(gxVARIANT parent, gxVARIANT child, int flags, int *ix);

/* Adds a child element to a variant. */
inline int gx_addvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT child);

/* Creates a new variant and appends it to a variant as a child. */
inline int gx_createvariantchild(gxVARIANT parent, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
								 const void *data, int nitems, gxVARIANT *child);

/* Returns the data of a variant's child converted to a specified type. */
inline int gx_convertvariantchild(gxVARIANT parent, int id, const wchar_t *name, int ix, GX_VARIANT_TYPES type,
								  void *target, int tgtlen, int *size, int *nitems);

/******************************************************************************
 * Work with arrays															  *
 ******************************************************************************/

/* Returns a part of an array variant's data. */
inline int gx_getvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  void *target, int tgtlen);

/* Cuts and returns a part of an array variant's data. */
inline int gx_cutvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  void *target, int tgtlen);

/* Inserts one or more values into an array variant's data. */
inline int gx_addvariantvalue(gxVARIANT varray, int size, GX_VARIANT_TYPES type, int ix, int nitems,
							  const void *data);

/******************************************************************************
 * Work with descendant variants											  *
 ******************************************************************************/

/* Returns a variant from a variant tree. */
inline int gx_getvariantbypath(gxVARIANT root, const wchar_t *path, gxVARIANT *item);

/* Returns the data of a variant located in a variant tree converted to a specified type. */
inline int gx_convertvariantbypath(gxVARIANT root, const wchar_t *path, GX_VARIANT_TYPES type, void *target,
								   int tgtlen, int *size, int *nitems);

#endif /* GX_MANUAL */

/** Flags for list item and child indexing functions. */
enum GX_VARIANT_FLAGS
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

/******************************************************************************
 * This is the end of the gxvariant interface. Now the implementation follows *
 ******************************************************************************/
#ifdef __BORLANDC__
	#pragma warn -rch
#endif
/******************************************************************************/
#endif /* GX_VARIANT_CPT_INCL */

#ifndef GX_MANUAL

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

/* create/updatedata/changeid/changename */
struct GX_PARM_UPDATEVARIANTN
{
	gxVARIANT			 variant;
	int					 id;
	const wchar_t		*name;
	GX_VARIANT_TYPES	 type;
	int					 size;
	int					 nitems;
	const void			*data;
};

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

struct GX_PARM_GETVARIANTINFO
{
	gxVARIANT			 variant;
	int					 id;
	wchar_t				*namebuff;
	int					 namebuffsize;
	GX_VARIANT_TYPES	 type;
	int					 size;
	int					 nitems;
	int					 nchildren;
};

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

/* add/get/cut/find item/child */
struct GX_PARM_VARIANTITEM
{
	gxVARIANT		 parent;
	int				 flags;
	int				 id;
	int				 ix;
	const wchar_t	*name;
	gxVARIANT		 item;
};

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

#endif /* GX_MANUAL */

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

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
 * @param name		The name of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param data		The data of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariant(gxVARIANT *variant, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
							const void *data, int nitems GX_DEFARG(1))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTN cv;
	int st;
	assert(variant);
	cv.variant = (gxVARIANT)0;
	cv.id = id;
	cv.name = name;
	cv.type = type;
	cv.size = size;
	cv.nitems = nitems;
	cv.data = data;
	st = gx_call(nullhandle, GX_CALL_CREATEVARIANTN, &cv);
	if(st) {
		*variant = cv.variant;
	}
	return st;
}

/******************************************************************************/
/** Modifies a variant.
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
 * @param name		The new name of the variant.
 * @param type		The new type of the variant.
 * @param size		The new size of the variant.
 * @param data		The new data of the variant.
 * @param nitems	The new number of items of the variant. This value is usually
 *					1, except for list and array types.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_updatevariant(gxVARIANT variant, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
							const void *data, int nitems GX_DEFARG(1))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTN uv;
	assert(variant);
	uv.variant = variant;
	uv.id = id;
	uv.name = name;
	uv.type = type;
	uv.size = size;
	uv.nitems = nitems;
	uv.data = data;
	return gx_call(nullhandle, GX_CALL_UPDATEVARIANTN, &uv);
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
 * @param type		The new type of the variant.
 * @param size		The new size of the variant.
 * @param data		The new data of the variant.
 * @param nitems	The new number of items of the variant. This value is usually
 *					1, except for list and array types.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_updatevariantdata(gxVARIANT variant, GX_VARIANT_TYPES type, int size, const void *data,
								int nitems GX_DEFARG(1))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTN uv;
	assert(variant);
	uv.variant = variant;
	uv.type = type;
	uv.size = size;
	uv.nitems = nitems;
	uv.data = data;
	return gx_call(nullhandle, GX_CALL_UPDATEVARIANTDATAN, &uv);
}

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

/******************************************************************************/
/** Changes the name of a variant.
 *
 * Changing the name of a variant affects all the variables that references the
 * same memory area. Therefore all the modifications are automatically reflected in the data
 * structure of those variants.
 *
 * @param variant	Variant to modify.
 * @param name		The new name of the variant.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_changevariantname(gxVARIANT variant, const wchar_t *name)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_UPDATEVARIANTN uv;
	assert(variant);
	uv.variant = variant;
	uv.name = name;
	return gx_call(nullhandle, GX_CALL_CHANGEVARIANTNAME, &uv);
}

/******************************************************************************/
/** Gives information about a variant.
 *
 * \note Uninterested buffers can be NULL.
 *
 * @param variant		Variant to process.
 * @param id			Buffer for the id.
 * @param namebuff		Buffer for the name.
 * @param namebuffsize	The size of the name buffer.
 * @param type			Buffer for the type.
 * @param size			Buffer for the size.
 * @param nitems		Buffer for the number of items.
 * @param nchildren		Buffer for the number of children.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantinfo(gxVARIANT variant, int *id, wchar_t *namebuff, int namebuffsize,
							 GX_VARIANT_TYPES *type, int *size, int *nitems, int *nchildren)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_GETVARIANTINFO gv;
	int st;
	gv.variant = variant;
	gv.namebuff = namebuff;
	gv.namebuffsize = namebuffsize;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTINFO, &gv);
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
 * @param type		Type to convert to.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariant(gxVARIANT variant, GX_VARIANT_TYPES type, void *target, int tgtlen,
							  int *size GX_DEFARG(0), int *nitems GX_DEFARG(0))
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
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested item.
 * @param name		Name of the requested item.
 * @param ix		Pointer to the index of the requested item. On success the item index is
 *					returned.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int *ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM gi;
	int st;
	assert(list && target);
	gi.parent = list;
	gi.flags = flags;
	gi.id = id;
	gi.name = name;
	gi.ix = ix ? *ix : 0;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTITEMN, &gi);
	if(st) {
		if(ix) *ix = gi.ix;
		*target = gi.item;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Returns an item from a list type variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested item.
 * @param name		Name of the requested item.
 * @param ix		Index of the requested item.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target)
{
	return gx_getvariantitem(list, flags, id, name, &ix, target);
}
#endif

/******************************************************************************/
/** Cuts and returns an item from a list type variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param list		List type variant.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the requested item to cut.
 * @param name		The name of the requested item to cut.
 * @param ix		The index of the requested item to cut.
 * @param target	Buffer for the result. To sign the end of usage call the gx_unrefvariant()
 *					or the gx_leavevariant() function. This parameter can be NULL to simply
 *					remove the variant item. In this case the function calls the
 *					\b gx_leavevariant function automatically.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_cutvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target GX_DEFARG(0))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM ci;
	int st;
	assert(list);
	ci.parent = list;
	ci.flags = flags;
	ci.id = id;
	ci.name = name;
	ci.ix = ix;
	st = gx_call(nullhandle, GX_CALL_CUTVARIANTITEMN, &ci);
	if(st) {
		if(target) *target = ci.item;
		else gx_leavevariant(&ci.item);
	}
	return st;
}

/******************************************************************************/
/** Returns the index of a variant element located in a list type variant.
 *
 * @param list		List type variant.
 * @param item		Item of the list to search for.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param ix		Buffer for the list index according to the flags parameter.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_findvariantitem(gxVARIANT list, gxVARIANT item, int flags, int *ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM fi;
	int st;
	assert(list && item && ix);
	fi.parent = list;
	fi.item = item;
	fi.flags = flags;
	st = gx_call(nullhandle, GX_CALL_FINDVARIANTITEMN, &fi);
	if(st) {
		*ix = fi.ix;
	}
	return st;
}

/******************************************************************************/
/** Adds an item to a list type variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param list	List type variant.
 * @param flags Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id	The id of the item located on the position where to insert or append the new item.
 * @param name	The name of the item located on the position where to insert or append the new item.
 * @param ix	The index of the position where to insert or append the new item.
 * @param item	The new item to add to the list. The reference counter of this variant is increased
 *				internally.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_addvariantitem(gxVARIANT list, int flags, int id, const wchar_t *name, int ix, gxVARIANT item)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM iv;
	assert(list && item);
	iv.parent = list;
	iv.flags = flags;
	iv.id = id;
	iv.name = name;
	iv.ix = ix;
	iv.item = item;
	return gx_call(nullhandle, GX_CALL_ADDVARIANTITEMN, &iv);
}

/******************************************************************************/
/** Creates a new variant and appends to a list type variant.
 *
 * \note For creating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param list		List type variant.
 * @param id		The id of the new variant.
 * @param name		The name of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param data		The data of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @param item		Buffer for the new variant. It can be NULL. The reference counter
 *					of the new variant will be set to 1 so it does not need unreferencing.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariantitem(gxVARIANT list, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
								const void *data, int nitems GX_DEFARG(1), gxVARIANT *item GX_DEFARG(0))
{
	gxVARIANT tmp;
	if(!item) item = &tmp;
	*item = 0;
	if(!gx_createvariant(item, id, name, type, size, data, nitems)) return 0;
	if(!gx_addvariantitem(list, GX_VARIANT_LAST, 0, 0, 0, *item)) {
		gx_pusherror();
		gx_leavevariant(item);
		gx_poperror();
		return 0;
	}
	return gx_unrefvariant(*item);
}

/******************************************************************************/
/** Returns the data of an item in a list type variant converted to a specified type.
 *
 * \note The actual role of the id, name and ix parameters depends on the name parameter.
 * If it is present the search is made \ref GX_VARIANT_BY_ORDER_AND_NAME "by order and name",
 * if it is NULL the system use the \ref GX_VARIANT_BY_ORDER_AND_ID "'by order and id'" algorithm.
 *
 * @param list		List type variant.
 * @param id		Id of the requested item.
 * @param name		Name of the requested item.
 * @param ix		Index of the requested item.
 * @param type		Type to convert to.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantitem(gxVARIANT list, int id, const wchar_t *name, int ix, GX_VARIANT_TYPES type,
								  void *target, int tgtlen, int *size GX_DEFARG(0), int *nitems GX_DEFARG(0))
{
	gxVARIANT fval = 0;
	int st;
	assert(target && tgtlen>0);
	if(!gx_getvariantitem(list, name ? GX_VARIANT_BY_ORDER_AND_NAME : GX_VARIANT_BY_ORDER_AND_ID,
		id, name, &ix, &fval)) return 0;
	st = gx_convertvariant(fval, type, target, tgtlen, size, nitems);
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
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested child.
 * @param name		Name of the requested child.
 * @param ix		Pointer to the index of the requested child. On success the child index is
 *					returned.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int *ix, gxVARIANT *target)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM gc;
	int st;
	assert(parent && target);
	gc.parent = parent;
	gc.flags = flags;
	gc.id = id;
	gc.name = name;
	gc.ix = ix ? *ix : 0;
	st = gx_call(nullhandle, GX_CALL_GETVARIANTCHILDN, &gc);
	if(st) {
		if(ix) *ix = gc.ix;
		*target = gc.item;
	}
	return st;
}

#ifdef __cplusplus
/******************************************************************************/
/** Returns a child of a variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		Id of the requested child.
 * @param name		Name of the requested child.
 * @param ix		Index of the requested child.
 * @param target	Buffer for the result. The reference counter of this variant is increased
 *					internally. To sign the end of usage call the gx_unrefvariant() or the
 *					gx_leavevariant() function.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_getvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target)
{
	return gx_getvariantchild(parent, flags, id, name, &ix, target);
}
#endif

/******************************************************************************/
/** Cuts and returns a child of a variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the requested child to cut.
 * @param name		The name of the requested child to cut.
 * @param ix		The index of the requested child to cut.
 * @param target 	Buffer for the result. To sign the end of usage call the gx_unrefvariant()
 *					or the gx_leavevariant() function. This parameter can be NULL to simply
 *					remove the child. In this case the function calls the \b gx_leavevariant
 *					function automatically.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_cutvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT *target GX_DEFARG(0))
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM cc;
	int st;
	assert(parent);
	cc.parent = parent;
	cc.flags = flags;
	cc.id = id;
	cc.name = name;
	cc.ix = ix;
	st = gx_call(nullhandle, GX_CALL_CUTVARIANTCHILDN, &cc);
	if(st) {
		if(target) *target = cc.item;
		else gx_leavevariant(&cc.item);
	}
	return st;
}

/******************************************************************************/
/** Returns the index of a child element located in a variant's children list.
 *
 * @param parent	Parent variant to process.
 * @param child		Child to search for.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param ix		Buffer for the child index according to the flags parameter.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_findvariantchild(gxVARIANT parent, gxVARIANT child, int flags, int *ix)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM fc;
	int st;
	assert(parent && child && ix);
	fc.parent = parent;
	fc.item = child;
	fc.flags = flags;
	st = gx_call(nullhandle, GX_CALL_FINDVARIANTCHILDN, &fc);
	if(st) {
		*ix = fc.ix;
	}
	return st;
}

/******************************************************************************/
/** Adds a child element to a variant.
 *
 * \note The actual role of the id, name and ix parameters depends on the flags parameter.
 *
 * @param parent	Parent variant to process.
 * @param flags		Indexing flag ( see \ref GX_VARIANT_FLAGS )
 * @param id		The id of the child located on the position where to insert or append the new child.
 * @param name		The name of the child located on the position where to insert or append the new child.
 * @param ix		The index of the position where to insert or append the new child.
 * @param child		The new child to add to the children list. The reference counter of this variant is
 *					increased internally.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_addvariantchild(gxVARIANT parent, int flags, int id, const wchar_t *name, int ix, gxVARIANT child)
{
	gxHANDLE nullhandle = { 0 };
	struct GX_PARM_VARIANTITEM ic;
	assert(parent && child);
	ic.parent = parent;
	ic.flags = flags;
	ic.id = id;
	ic.name = name;
	ic.ix = ix;
	ic.item = child;
	return gx_call(nullhandle, GX_CALL_ADDVARIANTCHILDN, &ic);
}

/******************************************************************************/
/** Creates a new variant and appends it to a variant as a child.
 *
 * \note For creating a list type variant the size, the data and the nitems
 * parameters have to be 0.
 *
 * @param parent	Parent variant to process.
 * @param id		The id of the new variant.
 * @param name		The name of the new variant.
 * @param type		The type of the new variant.
 * @param size		The size of the new variant.
 * @param data		The data of the new variant.
 * @param nitems	The number of items of the new variant. This value is usually
 *					1, except for list and array types.
 * @param child		Buffer for the new variant. It can be NULL. The reference counter
 *					of the new variant will be set to 1 so it does not need unreferencing.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_createvariantchild(gxVARIANT parent, int id, const wchar_t *name, GX_VARIANT_TYPES type, int size,
								  const void *data, int nitems GX_DEFARG(1), gxVARIANT *child GX_DEFARG(0))
{
	gxVARIANT tmp;
	if(!child) child = &tmp;
	*child = 0;
	if(!gx_createvariant(child, id, name, type, size, data, nitems)) return 0;
	if(!gx_addvariantchild(parent, GX_VARIANT_LAST, 0, 0, 0, *child)) {
		gx_pusherror();
		gx_leavevariant(child);
		gx_poperror();
		return 0;
	}
	return gx_unrefvariant(*child);
}

/******************************************************************************/
/** Returns the data of a variant's child converted to a specified type.
 *
 * \note The actual role of the id, name and ix parameters depends on the name parameter.
 * If it is present the search is made \ref GX_VARIANT_BY_ORDER_AND_NAME "by order and name",
 * if it is NULL the system use the \ref GX_VARIANT_BY_ORDER_AND_ID "'by order and id'" algorithm.
 *
 * @param parent	Parent variant to process.
 * @param id		Id of the requested child.
 * @param name		Name of the requested child.
 * @param ix		Index of the requested child.
 * @param type		Type to convert to.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantchild(gxVARIANT parent, int id, const wchar_t *name, int ix, GX_VARIANT_TYPES type,
								  void *target, int tgtlen, int *size GX_DEFARG(0), int *nitems GX_DEFARG(0))
{
	gxVARIANT fval = 0;
	int st;
	assert(target && tgtlen>0);
	if(!gx_getvariantchild(parent, name ? GX_VARIANT_BY_ORDER_AND_NAME : GX_VARIANT_BY_ORDER_AND_ID,
		id, name, &ix, &fval)) return 0;
	st = gx_convertvariant(fval, type, target, tgtlen, size, nitems);
	if(!st) gx_pusherror();
	gx_leavevariant(&fval);
	if(!st) gx_poperror();
	return st;
}

/** @} */

#ifndef GX_VARIANT_CPT_INCL

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

/** @} */

#endif /* GX_VARIANT_CPT_INCL */

/** @name Work with descendant variants
 * @{
 */

#ifndef GX_VARIANT_CPT_INCL

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

#endif /* GX_VARIANT_CPT_INCL */

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
 * @param type		Type to convert to.
 * @param target	Preallocated buffer for the resulted data.
 * @param tgtlen	Size of the target buffer.
 * @param size		Pointer to the item size. The function can modify this value. This value
 *					is useful in case of array handling or when the modified value is needed.
 *					Otherwise it can be NULL.
 * @param nitems	Pointer to the number of items. The function can modify this value. This
 *					value is useful in case of array handling. Otherwise it can be NULL.
 * @return		On error 0 is returned and the GX system error is set appropriately
 *				( see gx_geterror() ). */
inline int gx_convertvariantbypath(gxVARIANT root, const wchar_t *path, GX_VARIANT_TYPES type, void *target,
								   int tgtlen, int *size GX_DEFARG(0), int *nitems GX_DEFARG(0))
{
	gxVARIANT fval = 0;
	int st;
	assert(target && tgtlen>0);
	if(!gx_getvariantbypath(root, path, &fval)) return 0;
	st = gx_convertvariant(fval, type, target, tgtlen, size, nitems);
	if(!st) gx_pusherror();
	gx_leavevariant(&fval);
	if(!st) gx_poperror();
	return st;
}

/** @} */

/******************************************************************************/
#ifdef GX_NAMESPACES
	}	/* namespace */
#endif
#ifdef __BORLANDC__
	#pragma warn .rch
#endif
/******************************************************************************/
#endif /* GX_VARIANT_INCL */
