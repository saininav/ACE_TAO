// -*- C++ -*-

// ===================================================================
/**
 *  @file   Protocols_Hooks.h
 *
 *  $Id$
 *
 *  @author Priyanka Gontla <pgontla@ece.uci.edu>
 */
// ===================================================================

#ifndef TAO_PROTOCOLS_HOOKS_H
#define TAO_PROTOCOLS_HOOKS_H

#include /**/ "ace/pre.h"
#include "ace/CORBA_macros.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Service_Object.h"

#include "TAO_Export.h"
#include "Basic_Types.h"

namespace CORBA
{
  class Policy;
  class Environment;
}

class TAO_ORB_Core;
class TAO_GIOP_Invocation;
class TAO_Resource_Factory;
class TAO_Service_Context;
class TAO_Acceptor_Registry;
class TAO_Connection_Handler;
class TAO_Transport;
class TAO_Stub;

class TAO_Export TAO_Protocols_Hooks : public ACE_Service_Object
{
public:
  /// destructor
  virtual ~TAO_Protocols_Hooks (void);

  /// Initialize the protocols hooks instance.
  virtual void init_hooks (TAO_ORB_Core *orb_core
                           ACE_ENV_ARG_DECL) = 0;

  virtual int call_client_protocols_hook (int &send_buffer_size,
                                          int &recv_buffer_size,
                                          int &no_delay,
                                          int &enable_network_priority,
                                          const char *protocol_type) = 0;

  virtual int call_server_protocols_hook (int &send_buffer_size,
                                          int &recv_buffer_size,
                                          int &no_delay,
                                          int &enable_network_priority,
                                          const char *protocol_type) = 0;

  virtual int update_client_protocol_properties (
    TAO_Stub *stub,
    TAO_Transport *t,
    const char *protocol_type) = 0;


  virtual int update_server_protocol_properties (
    CORBA::Policy *policy,
    TAO_Transport *t,
    const char *protocol_type) = 0;


  virtual CORBA::Long get_dscp_codepoint (void) = 0;

  virtual void rt_service_context (TAO_Stub *stub,
                                   TAO_Service_Context &service_context,
                                   CORBA::Boolean restart
                                   ACE_ENV_ARG_DECL) = 0;

  virtual void add_rt_service_context_hook (
    TAO_Service_Context &service_context,
    CORBA::Policy *model_policy,
    CORBA::Short &client_priority
    ACE_ENV_ARG_DECL) = 0;

  virtual void get_selector_hook (CORBA::Policy *model_policy,
                                  CORBA::Boolean
                                  &is_client_propagated,
                                  CORBA::Short &server_priority) = 0;

  virtual void get_selector_bands_policy_hook (CORBA::Policy *bands_policy,
                                               CORBA::Short priority,
                                               CORBA::Short &min_priority,
                                               CORBA::Short &max_priority,
                                               int &in_range) = 0;

  /**
   * Accessor and modifier to the current thread priority, used to
   * implement the RTCORBA::Current interface, but it is faster for
   * some critical components.  If the RTCORBA library isn't used,
   * these operations are no-ops.
   */
  //@{
  virtual int get_thread_CORBA_priority (CORBA::Short &
                                         ACE_ENV_ARG_DECL_NOT_USED) = 0;

  virtual int get_thread_native_priority (CORBA::Short &
                                          ACE_ENV_ARG_DECL_NOT_USED) = 0;

  virtual int get_thread_CORBA_and_native_priority (
    CORBA::Short &,
    CORBA::Short &
    ACE_ENV_ARG_DECL_NOT_USED) = 0;

  virtual int set_thread_CORBA_priority (CORBA::Short
                                         ACE_ENV_ARG_DECL_NOT_USED) = 0;

  virtual int set_thread_native_priority (CORBA::Short
                                          ACE_ENV_ARG_DECL_NOT_USED) = 0;

  //@}

  /// Sets the default_policies for ORB.
  /// 1. Sets ORB-level policy defaults for this ORB.  Currently sets
  /// default RTCORBA policies: ClientProtocolPolicy.
  virtual int set_default_policies (ACE_ENV_SINGLE_ARG_DECL) = 0;

  /// Sets the default ServerProtocolPolicy.
  virtual int set_default_server_protocol_policy (
    TAO_Acceptor_Registry &acceptor_registry
    ACE_ENV_ARG_DECL) = 0;

};

#include /**/ "ace/post.h"

#endif /* TAO_PROTOCOLS_HOOKS_H */
