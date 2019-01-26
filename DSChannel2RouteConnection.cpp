/****************************************************************************
 *                 Modul: $RCSfile: DSChannel2RouteConnection.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
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
 
#include "DSChannel2RouteConnection.h"
#include "DSBlock.h"  // wegen parent
#include "DSChannel.h"
#include "DSSignalRoute.h"
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

DSChannel2RouteConnection::
DSChannel2RouteConnection(DSObject             *father,
                          DSChannelRefList     *channels,
                          DSSignalRouteRefList *routes):
  DSObject(DS_CHANNEL2ROUTECONNECTION, father),
  DSChannelRefComponent(channels),
  DSSignalRouteRefComponent(routes)
{
  if (father)
  {
    ((DSBlock*)father)->InsertChannel2RouteConnection(this);
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannel2RouteConnection::~DSChannel2RouteConnection(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSChannel2RouteConnection::New(DSObject *father) const
{
  return new DSChannel2RouteConnection(father);
}

DSBoolean DSChannel2RouteConnection::
IsChannelConnected(DSChannelRef search_channel) const
{
  DSChannelRef channel;

  for (channel = GetFirstChannelRef();
       channel != NULL;
       channel = GetNextChannelRef())
  {
    if (channel == search_channel)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSBoolean DSChannel2RouteConnection::
IsSignalRouteConnected(DSSignalRouteRef search_route) const
{
  DSSignalRouteRef route;

  for (route = GetFirstSignalRouteRef();
       route != NULL;
       route = GetNextSignalRouteRef())
  {
    if (route == search_route)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSObject *DSChannel2RouteConnection::Clone(DSObject *father, DSObject *fill_this) const
{
  DSChannel2RouteConnection *new_c2r_connection;

  if (fill_this == NULL)
  {
    new_c2r_connection = (DSChannel2RouteConnection *)New(father);
    assert(new_c2r_connection);
  }
  else
  {
    assert(fill_this->GetType() == DS_CHANNEL2ROUTECONNECTION);
    new_c2r_connection = (DSChannel2RouteConnection *)fill_this;
  }

  if (GetChannelRefList())
  {
    new_c2r_connection->SetChannelRefList((DSChannelRefList *)GetChannelRefList()->Clone((DSObject *)new_c2r_connection));
  }

  if (GetSignalRouteRefList())
  {
    new_c2r_connection->SetSignalRouteRefList((DSSignalRouteRefList *)GetSignalRouteRefList()->Clone((DSObject *)new_c2r_connection));
  }

  return new_c2r_connection;
}

DSResult DSChannel2RouteConnection::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;
  assert(writer);

  return DS_OK;
}

DSResult DSChannel2RouteConnection::Run(DSWriter *writer, DSType object_type,
                                        DSCardinal what) const
{
  DSResult  result;
  DSSignalRouteRef signal_route;
  DSChannelRef channel;

  switch(object_type)
  {
    case DS_SIGNALROUTE:
      for (signal_route = GetFirstSignalRouteRef();
           signal_route;
           signal_route = GetNextSignalRouteRef())
      {
        result = signal_route->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_CHANNEL:
      for (channel = GetFirstChannelRef();
           channel;
           channel = GetNextChannelRef())
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
