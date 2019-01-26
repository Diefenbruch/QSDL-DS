/****************************************************************************
 *           Modul: $RCSfile: DSChannel2ChannelConnectionComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            mit Signalchanneln verbunden werden koennen.
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

#include "DSChannel2ChannelConnectionComponent.h"
#include "DSChannel2ChannelConnection.h"

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

DSChannel2ChannelConnectionComponent::DSChannel2ChannelConnectionComponent(DSObject *father) :
  parent(father)
{
  channel2channel_connection_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannel2ChannelConnectionComponent::~DSChannel2ChannelConnectionComponent(void)
{
  if (channel2channel_connection_list) delete channel2channel_connection_list;
}

DSChannel2ChannelConnectionList* DSChannel2ChannelConnectionComponent::GetChannel2ChannelConnectionList(void) const
{
  return channel2channel_connection_list;
}

DSChannel2ChannelConnection *DSChannel2ChannelConnectionComponent::GetFirstChannel2ChannelConnection(void) const
{
  if (channel2channel_connection_list == NULL)
  {
    return NULL;
  }

  if (channel2channel_connection_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return channel2channel_connection_list->GetCurrentData();
}

DSChannel2ChannelConnection *DSChannel2ChannelConnectionComponent::GetNextChannel2ChannelConnection(void) const
{
  if (channel2channel_connection_list == NULL)
  {
    return NULL;
  }

  if (channel2channel_connection_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return channel2channel_connection_list->GetCurrentData();
}

DSResult DSChannel2ChannelConnectionComponent::SetChannel2ChannelConnectionList(DSChannel2ChannelConnectionList *list)
{
  if (channel2channel_connection_list == list) return DS_OK;

  if (channel2channel_connection_list != NULL)
  {
    delete channel2channel_connection_list;
  }
  channel2channel_connection_list = list;
  return DS_OK;
}

DSResult DSChannel2ChannelConnectionComponent::InsertChannel2ChannelConnection(DSChannel2ChannelConnection* c2c)
{
  assert(c2c);
  if (channel2channel_connection_list == NULL)
  {
    channel2channel_connection_list = new DSChannel2ChannelConnectionList;
    assert(channel2channel_connection_list != NULL);
  }
  if (c2c->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    c2c->SetParent(DSChannel2ChannelConnectionComponent::parent);
  }
  return channel2channel_connection_list->Append(c2c);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSChannel2ChannelConnectionComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSChannel2ChannelConnectionComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
