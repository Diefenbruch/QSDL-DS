/****************************************************************************
 *                 Modul: $RCSfile: DSSignalRouteComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Signalrouten
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

#include "DSSignalRouteComponent.h"
#include "DSSignalRoute.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe SignalRouten
 ****************************************************************************/
 
/****************************************************************************
 * Globale SignalRouten
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalRouteComponent::DSSignalRouteComponent(DSObject *father) :
  parent(father)
{
  signalroute_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalRouteComponent::~DSSignalRouteComponent(void)
{
  if (signalroute_definition_list) delete signalroute_definition_list;
}

DSSignalRouteKeyList* DSSignalRouteComponent::GetSignalRouteList(void) const
{
  return signalroute_definition_list;
}

DSSignalRoute *DSSignalRouteComponent::GetSignalRoute(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (signalroute_definition_list == NULL)
  {
    return NULL;
  }

  if (signalroute_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return signalroute_definition_list->GetCurrentData();
}

DSSignalRoute *DSSignalRouteComponent::GetSignalRoute(DSString& n) const
{
  return GetSignalRoute(&n);
}

DSSignalRoute *DSSignalRouteComponent::GetSignalRoute(const char * n) const
{
  DSSignalRoute *signalroute;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  signalroute = GetSignalRoute(str);
  delete str;

  return signalroute;
}

DSSignalRoute *DSSignalRouteComponent::GetFirstSignalRoute(void) const
{
  if (signalroute_definition_list == NULL)
  {
    return NULL;
  }

  if (signalroute_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signalroute_definition_list->GetCurrentData();
}

DSSignalRoute *DSSignalRouteComponent::GetNextSignalRoute(void) const
{
  if (signalroute_definition_list == NULL)
  {
    return NULL;
  }

  if (signalroute_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signalroute_definition_list->GetCurrentData();
}

DSResult DSSignalRouteComponent::SetSignalRouteList(DSSignalRouteKeyList *list)
{
  if (signalroute_definition_list == list) return DS_OK;

  if (signalroute_definition_list != NULL)
  {
    delete signalroute_definition_list;
  }
  signalroute_definition_list = list;
  return DS_OK;
}

DSResult DSSignalRouteComponent::InsertSignalRoute(DSSignalRoute* signalroute)
{
  assert(signalroute != NULL);
  assert(signalroute->GetName() != NULL);

  if (signalroute_definition_list == NULL)
  {
    signalroute_definition_list = new DSSignalRouteKeyList;
    assert(signalroute_definition_list != NULL);
  }
  if (signalroute->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    signalroute->SetParent(parent);
  }
  return signalroute_definition_list->Append(signalroute,
                                             new DSString(*signalroute->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSSignalRouteComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSSignalRouteComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
