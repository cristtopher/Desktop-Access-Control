/*******************************************************************************
 * GX DOTNET file - V7.2.9.0
 *
 * 2004-2011 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/******************************************************************************/
/** \file
 * <b> GX LIBSD header file </b>
 *
 * The GX is the base system for the majority of the ARH Inc. products.
 * It is a collection of loadable modules and library functions and gives an easy
 *  to program interface to the hardware devices.
 *
 * This file contains definitions for exception and data handling and type
 * definitions for .NET and STL (Standard Template Library) type conversions and
 * utility functions.
 */
/******************************************************************************/
#ifndef GX_LIBSD_INCL
#define GX_LIBSD_INCL
/******************************************************************************/
#include "gxtypes.h"
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4786)		/* truncated debug info */
#endif
#if defined(_MSC_VER) && _MSC_VER>=1300
	#define GX_SILENT_ALWAYS				\
		__pragma(warning(push))				\
		__pragma(warning(disable: 4127))	\
					if(1)					\
		__pragma(warning(pop))
	#define GX_SILENT_NEVER					\
		__pragma(warning(push))				\
		__pragma(warning(disable: 4127))	\
					if(0)					\
		__pragma(warning(pop))
	#define GX_SILENT_FOREVER				\
		__pragma(warning(push))				\
		__pragma(warning(disable: 4127))	\
					while(1)				\
		__pragma(warning(pop))
#else
	#define GX_SILENT_ALWAYS	if(1)
	#define GX_SILENT_NEVER		if(0)
	#define GX_SILENT_FOREVER	while(1)
#endif
/******************************************************************************/

#if defined(NO_GX_EXCEPTIONS)
	#define gxtry			GX_SILENT_ALWAYS
	#define gxcatch(x)		;GX_SILENT_NEVER
	#define __gxthrow
	#define gxthrow			{}
	#define gxcondthrow(x)
	#define gxassert(x)		assert(x)
	#define gxnew			new
#else
	#define gxtry			try
	#define gxcatch(x)		catch(x)
	#define __gxthrow		throw

	#ifdef GX_DOTNET

		#if !defined(GX_DOTNET_20)
			#define gxnew		__gc new
			#define gxassert(x)		if(!(x)) { gx_seterror(GX_ERROR_CODES::GX_EASSERT, L"(%hs in %hs at %hs:%i)",#x,_GX_FUNCTION_,__FILE__,__LINE__); throw gxnew gxException(); }
		#else
			#define gxnew		gcnew
			#define gxassert(x)		if(!(x)) { gx_seterror((int)GX_ERROR_CODES::GX_EASSERT, L"(%hs in %hs at %hs:%i)",#x,_GX_FUNCTION_,__FILE__,__LINE__); throw gxnew gxException(); }
		#endif

		#define gxthrow			throw gxnew gxException()
		#define gxcondthrow(x)	if(x) throw gxnew gxException()

	#else
		#define gxnew		new
		#ifndef GX_SWIG
			#define gxthrow		throw gxError()
		#endif
		#define gxcondthrow(x)	if(x) throw gxError()
		#define gxassert(x)		if(!(x)) { gx_seterror(GX_EASSERT, L"(%hs in %hs at %hs:%i)",#x,_GX_FUNCTION_,__FILE__,__LINE__); throw gxError(); }
	#endif
#endif

/******************************************************************************/

#if defined(_MSC_VER) && !defined(strdup)
	#define strdup _strdup
#endif
#if (defined(_MSC_VER) || defined(__BORLANDC__)) && !defined(wcsdup)
	#define wcsdup _wcsdup
#endif

#if !defined(NO_GX_CLASSES)	/* ( */

/** Helper function for the string _array operations. */
template <class _T>
inline int _gx_getstringarraynelements(const _T *str) {
	int eols = 0;
	int nlast = 0;
	while(*str) {
		if(*str == (_T)0xd) str++;
		if(*str++ == (_T)0xa) {
			eols++;
			nlast = 0;
			continue;
		}
		nlast = 1;
	}

	return eols+nlast;
}

/** Helper function for the string _array operations. */
template <class _T>
inline int _gx_getstringarrayelementlength(const _T *str) {
	int ix = 0;
	while(str[ix] && (str[ix] != (_T)0xd) && (str[ix] != (_T)0xa)) ix++;
	return ix;
}

/** Helper function for the string _array operations. */
template <class _T>
inline _T *_gx_getstringarraynextelement(_T *str) {
	while(*str) {
		if(*str == (_T)0xd) str++;
		if(*str++ == (_T)0xa) break;
	}
	return str;
}

#if !defined(GX_DOTNET)	/* ( */

typedef void *gxOutPtr;
#define GX_PUTPTR(ptr) ((void *)(ptr))
#define GX_PUTPTR_NONE ((void *)0)

#define __gx_func_strarray(_ret, _type, _array, _pname, _lenfunc, _func) \
	GX_SILENT_FOREVER { \
		_type _buffer[GX_MAXLEN_STRING]; \
		_ret = _func(*this, _pname, _buffer, GX_MAXLEN_STRING)!=0; \
		if(!_ret) { \
			gxthrow; \
			break; \
		} \
		_buffer[GX_MAXLEN_STRING-1] = 0; \
		_type *_str = _buffer; \
		if(_lenfunc(_buffer) == GX_MAXLEN_STRING-1) { \
			_str = (_type *)malloc(64*1024*sizeof(_type)); \
			if(!_str) { \
				gxSystem::SetError(GX_ENOMEM); \
				gxthrow; \
				_ret = false; \
				break; \
			} \
			_ret = _func(*this, _pname, _str, 64*1024)!=0; \
			if(!_ret) { \
				free(_str); \
				gxthrow; \
				_ret = false; \
				break; \
			} \
			_str[(64*1024)-1] = 0; \
		} \
		\
		int _maxlen = _gx_getstringarraynelements<_type>(_str); \
		gxtry { \
			_array.resize(_maxlen); \
			_type *_s = _str; \
			for(int _ix = 0; _ix < _maxlen; _ix++) { \
				int _slen = _gx_getstringarrayelementlength<_type>(_s); \
				_array[_ix].append(_s, _slen); \
				_s = _gx_getstringarraynextelement<_type>(_s); \
			} \
		} gxcatch(...) { \
			if(_str != _buffer) free(_str); \
			__gxthrow; \
			_ret = false; \
			break; \
		} \
		if(_str != _buffer) free(_str); \
		break; \
	}

#endif	/* ) */
/******************************************************************************/
#if defined(GX_DOTNET)	/* ( */

	#define GX_PUTPTR(ptr) System::IntPtr((void *)(ptr))
	#define GX_GETPTR(source)	(source).ToPointer()
	typedef GX_INDIRECTION_GC(System::String,gxString);

#ifndef GX_DOTNET_20
	#define GX_STRINGREF System::String *
	#define GX_STRINGREF_GC System::String __gc*
	#define GX_STRINGARRAY(_nitems) System::String* [_nitems]
	typedef System::String *gxInStr;
	typedef System::String *gxOutStr;
	typedef System::String *gxOutStrArray __gc [];
	typedef System::Byte gxData __gc [];
	#define gxInData gxData
	#define gxOutData __value gxData
	#define GX_BYTEARRAY(_nitems) System::Byte [_nitems]
	typedef System::String *gxInStrArray __gc [];
	typedef int gxInIntArray __gc [];
	typedef System::Int32 gxIntData __gc [];
	#define gxOutIntArray __value gxIntData
	#define GX_INTARRAY_NONE GX_NULLPTR
	#define GX_INTARRAY(_nitems) System::Int32 [_nitems]
	typedef System::IntPtr gxInPtr;
	typedef System::IntPtr gxOutPtr;
	#define GX_PUTPTR_NONE	System::IntPtr((void *)0)
	typedef System::Array __gc *gxSysArray;
	#define GX_MARSHALPTRTOSTRING1(_ptr) System::Runtime::InteropServices::Marshal::PtrToStringUni(_ptr)
	#define GX_MARSHALPTRTOSTRING2(_ptr, _len) System::Runtime::InteropServices::Marshal::PtrToStringUni(_ptr, _len)
	#define GX_PIN_PTR(_type, _var) _type __pin * _var
#else
#pragma message("GXDOTNET_20")
	#define GX_STRINGREF System::String ^
	#define GX_STRINGREF_GC GX_STRINGREF
	#define GX_STRINGARRAY(_nitems) array<System::String^>(_nitems)
	typedef System::String ^gxInStr;
	typedef System::String ^gxOutStr;
	typedef array<System::String^> ^gxOutStrArray;
	typedef array<System::String^> ^gxInStrArray;
	typedef array<System::Byte> ^gxData;
	#define gxInData gxData
	#define gxOutData gxData
	#define GX_BYTEARRAY(_nitems) array<System::Byte>(_nitems)
	typedef array<int>^ gxInIntArray;
	typedef array<System::Int32>^ gxInIntArray gxIntData;
	#define gxOutIntArray gxIntData
	#define GX_INTARRAY_NONE GX_NULLPTR
	#define GX_INTARRAY(_nitems) array<System::Int32> [_nitems]
	typedef System::IntPtr gxInPtr;
	typedef System::IntPtr gxOutPtr;
	#define GX_PUTPTR_NONE	System::IntPtr::Zero
	typedef System::Array ^gxSysArray;
	#define GX_MARSHALPTRTOSTRING1(_ptr) System::Runtime::InteropServices::Marshal::PtrToStringUni(GX_PUTPTR(_ptr))
	#define GX_MARSHALPTRTOSTRING2(_ptr, _len) System::Runtime::InteropServices::Marshal::PtrToStringUni(GX_PUTPTR(_ptr), _len)
	#define GX_PIN_PTR(_type, _var) pin_ptr<_type> _var
#endif


#define GX_GETSTRING(outname, argname)	\
	wchar_t outname[1024]; \
	outname[0] = 0; \
	{ \
		System::IntPtr wname = System::Runtime::InteropServices::Marshal::StringToBSTR(argname); \
		if(wname.ToPointer()) { \
			gx_wcsncpy(outname, (const wchar_t *)wname.ToPointer(), sizeof(outname)/sizeof(wchar_t)); \
			outname[(sizeof(outname)/sizeof(wchar_t))-1] = 0; \
		} \
		System::Runtime::InteropServices::Marshal::FreeBSTR(wname); \
	}

	#define GX_PUTSTRING(name) GX_MARSHALPTRTOSTRING1(name)


#define GX_PUTSTRING_NONE	(GX_STRINGREF)GX_NULLPTR

#define GX_PUTSTRINGARRAY_NONE	System::Array::CreateInstance(GX_TYPEID(System::String), 0)

gxSysArray GX_MAKESTRINGARRAY(const wchar_t *str) {
	const wchar_t *s = str;
	int nitems = 0;
	if(*s) {
		while(*s) {
			if(*s == 0xa) nitems++;
			s++;
		}
		if(s[-1] != 0xa) nitems++;
	}

	gxSysArray a = System::Array::CreateInstance(GX_TYPEID(System::String), nitems);

	int ix = 0;
	s = str;
	while(ix < nitems) {
		while(*s && (*s != 0xd) && (*s != 0xa)) s++;
		size_t mlen = s-str;
		if(mlen > 1023) mlen = 1023;
		a->SetValue(GX_MARSHALPTRTOSTRING2((System::IntPtr)(wchar_t *)str, (int)mlen), ix);
		if(*s == 0xd) s++;
		if(*s == 0xa) s++;
		str = s;
		ix++;
	}
	return a;
}

namespace gx {

inline int gx_globalfree(void *ptr);

}

gxOutStrArray GX_PUTGSTRINGARRAY(wchar_t **_array, int nitems, bool free) {
	gxOutStrArray a = gxnew GX_STRINGARRAY(nitems);
	for(int ix = 0; ix < nitems; ix++) {
		size_t mlen = _array[ix] ? wcslen(_array[ix]) : 0;
		a[ix] = GX_MARSHALPTRTOSTRING2((System::IntPtr)_array[ix], (int)mlen);
	}
	if(free && _array) gx::gx_globalfree((void *)_array);
	return a;
}


#define GX_PUTGSTRINGARRAY_NONE	GX_NULLPTR

#define __gx_func_strarray(_ret, _type, _array, _pname, _lenfunc, _func) \
	GX_SILENT_FOREVER { \
		_type _buffer[GX_MAXLEN_STRING]; \
		_ret = _func(h, _pname, _buffer, GX_MAXLEN_STRING)!=0; \
		if(!_ret) { \
			gxthrow; \
			break; \
		} \
		_buffer[GX_MAXLEN_STRING-1] = 0; \
		_type *_str = _buffer; \
		if(_lenfunc(_buffer) == GX_MAXLEN_STRING-1) { \
			_str = (_type *)malloc(64*1024*sizeof(_type)); \
			if(!_str) { \
			gxSystem::SetError((int)GX_ERROR_CODES::GX_ENOMEM); \
				gxthrow; \
				_ret = false; \
				break; \
			} \
			_ret = _func(h, _pname, _str, 64*1024)!=0; \
			if(!_ret) { \
				free(_str); \
				gxthrow; \
				_ret = false; \
				break; \
			} \
			_str[(64*1024)-1] = 0; \
		} \
		\
		_array = GX_NULLPTR; \
		int _maxlen = _gx_getstringarraynelements<_type>(_str); \
		gxtry { \
			if(_maxlen > 0) { \
				_array = gxnew GX_STRINGARRAY(_maxlen); \
				_type *_s = _str; \
				for(int _ix = 0; _ix < _maxlen; _ix++) { \
					int _slen = _gx_getstringarrayelementlength<_type>(_s); \
					_array[_ix] = GX_MARSHALPTRTOSTRING2((System::IntPtr)(wchar_t *)_s, _slen); \
					_s = _gx_getstringarraynextelement<_type>(_s); \
				} \
			} \
		} gxcatch(...) { \
			if(_str != _buffer) free(_str); \
			__gxthrow; \
			_ret = false; \
			break; \
		} \
		if(_str != _buffer) free(_str); \
		break; \
	}

#define __gx_func_outstrarray(_st, _array, _name, _func) \
	__gx_func_strarray(_st, wchar_t, _array, _name, wcslen, _func)

inline gxOutData GX_PUTDATA(const void *ptr, int len) {
	gxData _array = GX_NULLPTR;

	if(ptr && (len > 0)) {
		_array = gxnew GX_BYTEARRAY(len);
		System::IntPtr iptr((void *)ptr);
		System::Runtime::InteropServices::Marshal::Copy(iptr, _array, 0, len);
	}
	return _array;
}

inline gxOutData GX_PUTDATA_NONE_FUNC(void) {
	gxOutData _array = GX_NULLPTR;
	return _array;
}
#define GX_PUTDATA_NONE GX_PUTDATA_NONE_FUNC()

#define GX_GETDATA(_array) \
	System::IntPtr _array ## _ptr = System::Runtime::InteropServices::Marshal::AllocHGlobal(_array->Length); \
	if(_array ## _ptr.ToPointer()) { \
		System::Runtime::InteropServices::Marshal::Copy(_array, 0, _array ## _ptr, _array->Length); \
	} \
	int _array ## _len = _array->Length;

#define GX_FREEDATA(_array) \
	System::Runtime::InteropServices::Marshal::FreeHGlobal(_array ## _ptr);

#define GX_DATAPTR(data)	data ## _ptr.ToPointer()
#define GX_DATALEN(data)	data ## _len

#define GX_GETINSTRARRAY(_array) \
	int _array ## _len = (_array)->Length; \
	wchar_t **_array ## _ptr = (wchar_t **)malloc(sizeof(wchar_t *)*_array ## _len); \
	if(_array ## _ptr) { \
		for(int ix = 0; ix < _array ## _len; ix++) { \
		System::IntPtr wname = System::Runtime::InteropServices::Marshal::StringToBSTR(dynamic_cast<GX_STRINGREF_GC>((_array)->GetValue(ix))); \
			wchar_t *s = (wchar_t *)wname.ToPointer(); \
			_array ## _ptr[ix] = s ? wcsdup(s) : (wchar_t *)0; \
			System::Runtime::InteropServices::Marshal::FreeBSTR(wname); \
		} \
	} else { \
		_array ## _len = -1; \
	}


#define GX_FREEINSTRARRAY(_array) \
	{ \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			if(_array ## _ptr[ix]) free(_array ## _ptr[ix]); \
		} \
		free(_array ## _ptr); \
		_array ## _ptr = 0; \
		_array ## _len = 0; \
	}

#define GX_GETINSTRARRAY_PTR(_array)	_array ## _ptr
#define GX_GETINSTRARRAY_LEN(_array) _array ## _len


#define GX_GETININTARRAY(_array) \
	int _array ## _len = (_array)->Length; \
	int *_array ## _ptr = (int *)malloc(sizeof(int)*_array ## _len); \
	if(_array ## _ptr) { \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			_array ## _ptr[ix] = _array[ix]; \
		} \
	} else { \
		_array ## _len = -1; \
	}

#define GX_FREEININTARRAY(_array) \
	{ \
		if(_array ## _ptr) { \
			free(_array ## _ptr); \
			_array ## _ptr = 0; \
		} \
		_array ## _len = 0; \
	}

#define GX_GETININTARRAY_PTR(_array)	_array ## _ptr
#define GX_GETININTARRAY_LEN(_array) _array ## _len

inline gxOutIntArray GX_PUTINTARRAY(const int *ptr, int len) {
	gxOutIntArray _array = GX_NULLPTR;
	if(ptr && (len > 0)) {
		_array = gxnew GX_INTARRAY(len);
		System::IntPtr iptr((int *)ptr);
		System::Runtime::InteropServices::Marshal::Copy(iptr, _array, 0, len);
	}
	return _array;
}
/******************************************************************************/
#elif !defined(NO_GX_STL) && !defined(GX_SWIG) /* )( */
/******************************************************************************/

typedef const std::string gxInAStr;
typedef const std::wstring gxInStr;
typedef std::string gxOutAStr;
typedef std::wstring gxOutStr;
typedef std::vector<std::string> gxOutAStrArray;
typedef std::vector<std::wstring> gxOutStrArray;
typedef std::vector<std::string> gxInAStrArray;
typedef std::vector<std::wstring> gxInStrArray;
typedef std::vector<int> gxInIntArray;

#define GX_GETSTRING(outname, argname)	\
		const wchar_t *outname = argname.c_str()

#define GX_GETASTRING(outname, argname) \
		const char *outname = argname.c_str()

#define GX_PUTSTRING(name) \
		std::wstring(name)

#define GX_PUTASTRING(name) \
		std::string(name)

#define GX_PUTSTRING_NONE	std::wstring()
#define GX_PUTASTRING_NONE	std::string()

#define __gx_func_outstrarray(_st, _array, _name, _func) \
	__gx_func_strarray(_st, wchar_t, _array, _name, wcslen, _func)

#define __gx_func_outastrarray(_st, _array, _name, _func) \
	__gx_func_strarray(_st, char, _array, _name, strlen, _func)

#ifdef GX_NAMESPACES
namespace gx {
#endif

inline int gx_globalfree(void *ptr);

#ifdef GX_NAMESPACES
}
#endif

inline std::vector<std::wstring> GX_PUTGSTRINGARRAY(wchar_t **_array, int nitems, bool free) {
	std::vector<std::wstring> a;
	a.resize(nitems);
	for(int ix = 0; ix < nitems; ix++) {
		if(_array[ix]) a[ix] = _array[ix];
	}
#ifdef GX_NAMESPACES
	if(free && _array) gx::gx_globalfree((void *)_array);
#else
	if(free && _array) gx_globalfree((void *)_array);
#endif
	return a;
}

#define GX_PUTGSTRINGARRAY_NONE	std::vector<std::wstring>()

inline std::vector<std::string> GX_PUTGASTRINGARRAY(char **_array, int nitems, bool free) {
	std::vector<std::string> a;
	a.resize(nitems);
	for(int ix = 0; ix < nitems; ix++) {
		if(_array[ix]) a[ix] = _array[ix];
	}
#ifdef GX_NAMESPACES
	if(free && _array) gx::gx_globalfree((void *)_array);
#else
	if(free && _array) gx_globalfree((void *)_array);
#endif
	return a;
}

#define GX_PUTGASTRINGARRAY_NONE	std::vector<std::string>()

#define GX_GETINSTRARRAY(_array) \
	int _array ## _len = (int)(_array).size(); \
	wchar_t **_array ## _ptr = (wchar_t **)malloc(sizeof(wchar_t *)*_array ## _len); \
	if(_array ## _ptr) { \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			_array ## _ptr[ix] = _array[ix].c_str() ? wcsdup(_array[ix].c_str()) : (wchar_t *)0; \
		} \
	} else { \
		_array ## _len = -1; \
	}

#define GX_FREEINSTRARRAY(_array) \
	{ \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			if(_array ## _ptr[ix]) free(_array ## _ptr[ix]); \
		} \
		free(_array ## _ptr); \
		_array ## _ptr = 0; \
		_array ## _len = 0; \
	}

#define GX_GETINSTRARRAY_PTR(_array)	_array ## _ptr
#define GX_GETINSTRARRAY_LEN(_array) _array ## _len


#define GX_GETINASTRARRAY(_array) \
	int _array ## _len = (int)(_array).size(); \
	char **_array ## _ptr = (char **)malloc(sizeof(char*)*_array ## _len); \
	if(_array ## _ptr) { \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			_array ## _ptr[ix] = _array[ix].c_str() ? strdup(_array[ix].c_str()) : (char *)0; \
		} \
	} else { \
		_array ## _len = -1; \
	}

#define GX_FREEINASTRARRAY(_array) \
	{ \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			if(_array ## _ptr[ix]) free(_array ## _ptr[ix]); \
		} \
		free(_array ## _ptr); \
		_array ## _ptr = 0; \
		_array ## _len = 0; \
	}

#define GX_GETINASTRARRAY_PTR(_array)	_array ## _ptr
#define GX_GETINASTRARRAY_LEN(_array) _array ## _len


#define GX_GETININTARRAY(_array) \
	int _array ## _len = (int)(_array).size(); \
	int *_array ## _ptr = (int *)malloc(sizeof(int)*_array ## _len); \
	if(_array ## _ptr) { \
		for(int ix = 0; ix < _array ## _len; ix++) { \
			_array ## _ptr[ix] = _array[ix]; \
		} \
	} else { \
		_array ## _len = -1; \
	}

#define GX_FREEININTARRAY(_array) \
	{ \
		if(_array ## _ptr) { \
			free(_array ## _ptr); \
			_array ## _ptr = 0; \
		} \
		_array ## _len = 0; \
	}

#define GX_GETININTARRAY_PTR(_array)	_array ## _ptr
#define GX_GETININTARRAY_LEN(_array) _array ## _len


#endif	/* !GX_DOTNET && !GX_SWIG && !NO_GX_STL ) */

/******************************************************************************/
#endif	/* !NO_GX_CLASSES ) */
/******************************************************************************/
#ifdef _MSC_VER
	#pragma warning(pop)
#endif
/******************************************************************************/
#endif	/* GX_LIBGXDOTNET_INCL */
/******************************************************************************/
