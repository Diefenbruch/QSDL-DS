/****************************************************************************
 *                 Modul: $RCSfile: DSChannelRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Kanalreferenzen
 *            enthalten.
 *
 * Funktionen: GetChannelRefList(): Liefert Kanalliste (VIA)
 *             SetChannelRefList(): s. o.
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

#include "DSChannel.h"
#include "DSChannelRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe ChannelRefn
 ****************************************************************************/

/****************************************************************************
 * Globale ChannelRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSChannelRefComponent::DSChannelRefComponent(DSChannelRefList *channels) :
  channel_ref_list(channels)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannelRefComponent::~DSChannelRefComponent(void)
{
  if (channel_ref_list) delete channel_ref_list;
}

/****************************************************************************
 * GetChannelRefList(): Liefert den Kanal des OUTPUT-Befehls zurueck
 *                      Ergebnis: Zeiger auf eine Kanalliste
 *                      Seiteneffekte: keine
 ****************************************************************************/
 
DSChannelRefList* DSChannelRefComponent::GetChannelRefList(void) const
{
  return channel_ref_list;
}

DSChannelRef DSChannelRefComponent::GetFirstChannelRef(void) const
{
  assert(channel_ref_list != NULL);
  if (channel_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return channel_ref_list->GetCurrentData();
}

DSChannelRef DSChannelRefComponent::GetNextChannelRef(void) const
{
  assert(channel_ref_list != NULL);
  if (channel_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return channel_ref_list->GetCurrentData();
}


/****************************************************************************
 * SetChannelRefList(): Speichert den uebergebenen Zeiger
 *                      -> chan_list: Zeiger auf eine Kanalliste
 *                      Ergebnis: DS_OK
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSResult DSChannelRefComponent::SetChannelRefList(DSChannelRefList *chan_list)
{
  if (channel_ref_list == chan_list) return DS_OK;

  if (channel_ref_list) delete channel_ref_list;
  channel_ref_list = chan_list;
  return DS_OK;
}

DSResult DSChannelRefComponent::InsertChannelRef(DSChannelRef channel_ref)
{
  assert(channel_ref);
  if (channel_ref_list == NULL)
  {
    channel_ref_list = new DSChannelRefList;
    assert(channel_ref_list != NULL);
  }
  return channel_ref_list->Append(channel_ref);
}

