/****************************************************************************
 *                 Modul: $RCSfile: DSChannelComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            definiert werden koennen.
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

#include "DSChannelComponent.h"
#include "DSChannel.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Channeln
 ****************************************************************************/

/****************************************************************************
 * Globale Channeln
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSChannelComponent::DSChannelComponent(DSObject *father) :
  parent(father)
{
  channel_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannelComponent::~DSChannelComponent(void)
{
  if (channel_definition_list) delete channel_definition_list;
}

DSChannelKeyList* DSChannelComponent::GetChannelList(void) const
{
  return channel_definition_list;
}

DSChannel *DSChannelComponent::GetChannel(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (channel_definition_list == NULL)
  {
    return NULL;
  }

  if (channel_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return channel_definition_list->GetCurrentData();
}

DSChannel *DSChannelComponent::GetChannel(DSString& n) const
{
  return GetChannel(&n);
}

DSChannel *DSChannelComponent::GetChannel(const char *n) const
{
  DSChannel *channel;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  channel = GetChannel(str);
  delete str;

  return channel;
}

DSChannel *DSChannelComponent::GetFirstChannel(void) const
{
  if (channel_definition_list == NULL)
  {
    return NULL;
  }

  if (channel_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return channel_definition_list->GetCurrentData();
}

DSChannel *DSChannelComponent::GetNextChannel(void) const
{
  if (channel_definition_list == NULL)
  {
    return NULL;
  }

  if (channel_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return channel_definition_list->GetCurrentData();
}

DSResult DSChannelComponent::SetChannelList(DSChannelKeyList *list)
{
  if (channel_definition_list == list) return DS_OK;

  if (channel_definition_list) delete channel_definition_list;
  channel_definition_list = list;
  return DS_OK;
}

DSResult DSChannelComponent::InsertChannel(DSChannel* channel)
{
  assert(channel != NULL);
  assert(channel->GetName() != NULL);

  if (channel_definition_list == NULL)
  {
    channel_definition_list = new DSChannelKeyList;
    assert(channel_definition_list != NULL);
  }
  if (channel->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    channel->SetParent(parent);
  }
  return channel_definition_list->Append(channel, new DSString(*channel->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSChannelComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSChannelComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
