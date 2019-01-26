/****************************************************************************
 *                 Modul: $RCSfile: DSChannel2ChannelConnection.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.2 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-Connect bereit.
 *
 * Funktionen:
 ****************************************************************************/

#ifdef USE_PRAGMA
#pragma interface
#endif

/****************************************************************************
 * Konstanten
 ****************************************************************************/
 
/****************************************************************************
 * Include-Anweisungen
 ****************************************************************************/
 
#include "DSChannel2ChannelConnection.h"
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSChannel.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/
 
/****************************************************************************
 * Globale Variablen
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSChannel2ChannelConnection::
DSChannel2ChannelConnection(DSObject           * father,
                            DSChannelRefComponent * first_channels,
                            DSChannelRefComponent * second_channels):
  DSObject(DS_CHANNEL2CHANNELCONNECTION, father),
  first_channel_component(first_channels),
  second_channel_component(second_channels)
{
  if (father)
  {
    assert(father->GetType() == DS_BLOCKSUBSTRUCTURE);
    ((DSBlockSubstructure*)father)->InsertChannel2ChannelConnection(this);
  }

  if (first_channel_component == NULL)
  {
    first_channel_component = new DSChannelRefComponent;
  }
  if (second_channel_component == NULL)
  {
    second_channel_component = new DSChannelRefComponent;
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannel2ChannelConnection::~DSChannel2ChannelConnection(void)
{
  if (first_channel_component) delete first_channel_component;
  if (second_channel_component) delete second_channel_component;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSChannel2ChannelConnection::New(DSObject *father) const
{
  return new DSChannel2ChannelConnection(father);
}

DSBoolean DSChannel2ChannelConnection::
IsChannelConnectedInFirst(DSChannelRef search_channel) const
{
  DSChannelRef channel;

  if (!first_channel_component)
    return DS_FALSE;

  for (channel = first_channel_component->GetFirstChannelRef();
       channel != NULL;
       channel = first_channel_component->GetNextChannelRef())
  {
    if (channel == search_channel)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}


DSBoolean DSChannel2ChannelConnection::
IsChannelConnectedInSecond(DSChannelRef search_channel) const
{
  DSChannelRef channel;

  if (!second_channel_component)
    return DS_FALSE;

  for (channel = second_channel_component->GetFirstChannelRef();
       channel != NULL;
       channel = second_channel_component->GetNextChannelRef())
  {
    if (channel == search_channel)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}


DSChannelRefComponent * DSChannel2ChannelConnection::
GetFirstChannelComponent(void) const
{
  return first_channel_component;
}


DSChannelRefComponent *  DSChannel2ChannelConnection::
GetSecondChannelComponent(void) const
{
  return second_channel_component;
}


DSResult DSChannel2ChannelConnection::
SetFirstChannelComponent(DSChannelRefComponent *first_component)
{
  if (first_channel_component == first_component) return DS_OK;

  if (first_channel_component) delete first_channel_component;

  first_channel_component = first_component;

  return DS_OK;
}


DSResult DSChannel2ChannelConnection::
SetSecondChannelComponent(DSChannelRefComponent *second_component)
{
  if (second_channel_component == second_component) return DS_OK;

  if (second_channel_component) delete second_channel_component;

  second_channel_component = second_component;

  return DS_OK;
}


DSObject *DSChannel2ChannelConnection::Clone(DSObject *father, DSObject *fill_this) const
{
  DSChannel2ChannelConnection *new_c2c_connection;

  if (fill_this == NULL)
  {
    new_c2c_connection = (DSChannel2ChannelConnection *)New(father);
    assert(new_c2c_connection);
  }
  else
  {
    assert(fill_this->GetType() == DS_CHANNEL2CHANNELCONNECTION);
    new_c2c_connection = (DSChannel2ChannelConnection *)fill_this;
  }

  if (first_channel_component->GetChannelRefList())
  {
    new_c2c_connection->GetFirstChannelComponent()->SetChannelRefList((DSChannelRefList *)(GetFirstChannelComponent()->GetChannelRefList())->Clone((DSObject *)new_c2c_connection));
  }

  if (second_channel_component->GetChannelRefList())
  {
    new_c2c_connection->GetSecondChannelComponent()->SetChannelRefList((DSChannelRefList *)(GetSecondChannelComponent()->GetChannelRefList())->Clone((DSObject *)new_c2c_connection));
  }

  return new_c2c_connection;
}

DSResult DSChannel2ChannelConnection::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;
  assert(writer);

  return DS_OK;
}

DSResult DSChannel2ChannelConnection::Run(DSWriter *writer, DSType object_type,
                                          DSCardinal what) const
{
  DSResult  result;
  DSChannelRef channel;

  switch(object_type)
  {
    case DS_CHANNEL:
      for (channel = first_channel_component->GetFirstChannelRef();
           channel;
           channel = first_channel_component->GetNextChannelRef())
      {
        result = channel->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
