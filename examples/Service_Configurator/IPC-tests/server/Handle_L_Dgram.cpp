// $Id$

#include "Handle_L_Dgram.h"

ACE_RCSID(server, Handle_L_Dgram, "$Id$")

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)

const char *Handle_L_Dgram::DEFAULT_RENDEZVOUS = "/tmp/foo_dgram";

#if !defined (__ACE_INLINE__)
#include "Handle_L_Dgram.i"
#endif /* __ACE_INLINE__ */

Handle_L_Dgram local_dgram;
ACE_Service_Object_Type ld (&local_dgram, "Local_Dgram");
#endif /* ACE_LACKS_UNIX_DOMAIN_SOCKETS */
