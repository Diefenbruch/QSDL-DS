/****************************************************************************
 *           Modul: $RCSfile: DSChannel2RouteConnectionComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            mit Signalrouten verbunden werden koennen.
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

#include "DSChannel2RouteConnectionComponent.h"
#include "DSChannel2RouteConnection.h"

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

DSChannel2RouteConnectionComponent::DSChannel2RouteConnectionComponent(DSObject *father) :
  parent(father)
{
  channel2route_connection_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannel2RouteConnectionComponent::~DSChannel2RouteConnectionComponent(void)
{
  if (channel2route_connection_list) delete channel2route_connection_list;
}

DSChannel2RouteConnectionList* DSChannel2RouteConnectionComponent::GetChannel2RouteConnectionList(void) const
{
  return channel2route_connection_list;
}

DSChannel2RouteConnection *DSChannel2RouteConnectionComponent::GetFirstChannel2RouteConnection(void) const
{
  if (channel2route_connection_list == NULL)
  {
    return NULL;
  }

  if (channel2route_connection_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return channel2route_connection_list->GetCurrentData();
}

DSChannel2RouteConnection *DSChannel2RouteConnectionComponent::GetNextChannel2RouteConnection(void) const
{
  if (channel2route_connection_list == NULL)
  {
    return NULL;
  }

  if (channel2route_connection_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return channel2route_connection_list->GetCurrentData();
}

DSResult DSChannel2RouteConnectionComponent::SetChannel2RouteConnectionList(DSChannel2RouteConnectionList *list)
{
  if (channel2route_connection_list == list) return DS_OK;

  if (channel2route_connection_list != NULL)
  {
    delete channel2route_connection_list;
  }
  channel2route_connection_list = list;
  return DS_OK;
}

DSResult DSChannel2RouteConnectionComponent::InsertChannel2RouteConnection(DSChannel2RouteConnection* c2r)
{
  assert(c2r);
  if (channel2route_connection_list == NULL)
  {
    channel2route_connection_list = new DSChannel2RouteConnectionList;
    assert(channel2route_connection_list != NULL);
  }
  if (c2r->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    c2r->SetParent(DSChannel2RouteConnectionComponent::parent);
  }
  return channel2route_connection_list->Append(c2r);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSChannel2RouteConnectionComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSChannel2RouteConnectionComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
