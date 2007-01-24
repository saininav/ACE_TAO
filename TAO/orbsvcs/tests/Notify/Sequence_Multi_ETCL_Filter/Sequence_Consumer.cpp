// $Id$

// ******************************************************************
// Include Section
// ******************************************************************

#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"

#include "orbsvcs/CosNotifyCommC.h"
#include "orbsvcs/CosNamingC.h"
#include "Notify_Sequence_Push_Consumer.h"
#include "goC.h"

#include "Notify_Test_Client.h"

// ******************************************************************
// Data Section
// ******************************************************************

static const char* ior = "file://supplier.ior";
static unsigned int low = 32;
static unsigned int high = 32;

// ******************************************************************
// Subroutine Section
// ******************************************************************

class Consumer_Client : public Notify_Test_Client
{
public:
  virtual int parse_args (int argc, char* argv[]);
};


int
Consumer_Client::parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "k:l:h:d:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.optarg;
        break;

      case 'l':
        low = ACE_OS::atoi (get_opts.optarg);
        break;

      case 'h':
        high = ACE_OS::atoi (get_opts.optarg);
        break;

      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-k <ior> "
                           "-l <low expected events> "
                           "-h <high expected events> "
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates sucessful parsing of the command line
  return 0;
}


static CosNotifyChannelAdmin::ConsumerAdmin_ptr
create_consumeradmin (CosNotifyChannelAdmin::EventChannel_ptr ec
                      ACE_ENV_ARG_DECL)
{
  CosNotifyChannelAdmin::AdminID adminid = 0;
  CosNotifyChannelAdmin::ConsumerAdmin_var admin =
    ec->new_for_consumers (CosNotifyChannelAdmin::AND_OP,
                           adminid
                           ACE_ENV_ARG_PARAMETER);


  CosNotifyFilter::FilterFactory_var ffact =
    ec->default_filter_factory ();

  CosNotifyFilter::Filter_var filter =
    ffact->create_filter ("EXTENDED_TCL" ACE_ENV_ARG_PARAMETER);

  if(CORBA::is_nil(filter.in()))
    {
      ACE_ERROR ((LM_ERROR,
                  " (%P|%t) Consumer unable to initialize filter.\n"));
      return CosNotifyChannelAdmin::ConsumerAdmin::_nil ();
    }

  CosNotifyFilter::ConstraintExpSeq constraint_list (1);
  constraint_list.length(1);

  constraint_list[0].event_types.length (0);
  constraint_list[0].constraint_expr = CORBA::string_dup (
   "$.enum < 0");

  filter->add_constraints (constraint_list ACE_ENV_ARG_PARAMETER);

  // apply filter
  admin->add_filter (filter.in ());

  return CosNotifyChannelAdmin::ConsumerAdmin::_duplicate (admin.in ());
}


static void
create_consumers (CosNotifyChannelAdmin::ConsumerAdmin_ptr admin,
                  Notify_Test_Client* client
                  ACE_ENV_ARG_DECL)
{
  // startup the consumer
  Notify_Sequence_Push_Consumer* consumer_1;
  ACE_NEW_THROW_EX (consumer_1,
                    Notify_Sequence_Push_Consumer ("consumer1",
                                                   low,
                                                   high,
                                                   *client),
                    CORBA::NO_MEMORY ());

  consumer_1->init (client->root_poa () ACE_ENV_ARG_PARAMETER);

  consumer_1->_connect (admin ACE_ENV_ARG_PARAMETER);
}

// ******************************************************************
// Main Section
// ******************************************************************

int main (int argc, char* argv[])
{
  int status = 0;
  ACE_TRY_NEW_ENV
    {
      Consumer_Client client;

      status = client.init (argc, argv ACE_ENV_ARG_PARAMETER);

      if (status == 0)
        {
          CosNotifyChannelAdmin::EventChannel_var ec =
            client.create_event_channel ("MyEventChannel", 1 ACE_ENV_ARG_PARAMETER);

          CORBA::ORB_ptr orb = client.orb ();
          CORBA::Object_var object =
                              orb->string_to_object (ior ACE_ENV_ARG_PARAMETER);

          sig_var sig = sig::_narrow (object.in () ACE_ENV_ARG_PARAMETER);

          if (CORBA::is_nil (sig.in ()))
            {
              ACE_ERROR_RETURN ((LM_ERROR,
                                 "Object reference <%s> is nil\n",
                                 ior),
                                1);
            }

          CosNotifyChannelAdmin::ConsumerAdmin_var admin =
            create_consumeradmin (ec.in () ACE_ENV_ARG_PARAMETER);

          if (!CORBA::is_nil (admin.in ()))
            {
              create_consumers (admin.in (), &client ACE_ENV_ARG_PARAMETER);

              // Tell the supplier to go
              sig->go ();

              client.ORB_run( ACE_ENV_SINGLE_ARG_PARAMETER );
              ACE_DEBUG((LM_DEBUG, "Consumer done.\n"));

              sig->done ();
            }
        }
    }
  ACE_CATCH (CORBA::Exception, e)
    {
      ACE_PRINT_EXCEPTION (e, "Error: Consumer exception: ");
      status = 1;
    }
  ACE_ENDTRY;

  return status;
}
