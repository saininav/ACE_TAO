/* -*- C++ -*- */
// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//    InconsistentTypeCode.h
//
// = AUTHOR
//
// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO ORB and the TAO IDL Compiler have been developed by Washington
// University Computer Science's Distributed Object Computing Group.
//
// Information on TAO is available at
//                 http://www.cs.wustl.edu/~schmidt/TAO.html
//
// Modified by Jeff Parsons <jp4@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_IDL_INCONSISTENTTYPECODEC_H
#define TAO_IDL_INCONSISTENTTYPECODEC_H

#include "tao/Exception.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO
#if defined(_MSC_VER)
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if !defined (_CORBA_ORB_INCONSISTENTTYPECODE_CH_)
#define _CORBA_ORB_INCONSISTENTTYPECODE_CH_

class TAO_Export CORBA_ORB_InconsistentTypeCode : public CORBA::UserException
{
  // = TITLE
  //   @@ Jeff, please fill in here.
  //
  // = DESCRIPTION
  //   @@ Jeff, please fill in here.
public:
  CORBA_ORB_InconsistentTypeCode (void); 
  // default ctor
  CORBA_ORB_InconsistentTypeCode (const CORBA_ORB_InconsistentTypeCode &); 
  // copy ctor
  ~CORBA_ORB_InconsistentTypeCode (void); 
  // dtor

  CORBA_ORB_InconsistentTypeCode &operator= (const CORBA_ORB_InconsistentTypeCode &);

  virtual void _raise (void);

  static CORBA_ORB_InconsistentTypeCode *_narrow (CORBA::Exception *);

  // = TAO extension
  static CORBA::Exception *_alloc (void);

};

#endif /* end #if !defined */

#if defined(_MSC_VER)
#pragma warning(default:4250)
#endif /* _MSC_VER */

#endif /* TAO_IDL_INCONSISTENTTYPECODEC_H */
