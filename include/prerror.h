#ifndef PRERROR_INCL
#define PRERROR_INCL
/*******************************************************************************
 * PR ERROR 2006-2013 (c) ARH Inc.
 * 2013.07.05 v2.1.5.14
 ******************************************************************************/
#include "gxtypes.h"
/******************************************************************************/
/**
  \file prerror.h
  <b>Passport Reader error constants</b>

  The  Passport Reader  is a  travel  document  reader  and  analyser  system by
  <b>ARH Inc.</b>,  which bases  on the GX system.  The  prerror.h  contains the
  descriptions of error code constants.
 */
/******************************************************************************/
#ifdef GX_NAMESPACES
  namespace pr {
#endif

/******************************************************************************/
/** Passport Reader specific error codes. */
GX_ENUM PR_ERROR_CODES {
	PR_ECAPTURE			= 0x20088001,		/**< Image capture error */
	PR_EWEAKDEV			= 0x20088005,		/**< Error code for inadequate hardware e.g. USB1 interface for USB2 device */
	PR_CERT_EXPIRED		= 0x20088030,		/**< Certificate is expired error */
	PR_CERT_REVOKED		= 0x20088031,		/**< Certificate is revoked error */
	PR_ECHECK			= 0x20088032,		/**< Validation checking failed */
};
/******************************************************************************/
#ifdef GX_NAMESPACES
  }
#endif
/******************************************************************************/
#endif/* PRERROR_INCL */
