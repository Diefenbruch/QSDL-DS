/****************************************************************************
 *                 Modul: $RCSfile: DSSignalRouteRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Referenzen
 *            auf Signalrouten enthalten.
 *
 * Funktionen: GetSignalRouteRefList(): Liefert Signalroutenliste (VIA)
 *             SetSignalRouteRefList(): s. o.
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

#include "DSSignalRouteRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe SignalRouteRefn
 ****************************************************************************/

/****************************************************************************
 * Globale SignalRouteRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalRouteRefComponent::DSSignalRouteRefComponent(DSSignalRouteRefList *routes) :
  signalroute_ref_list(routes)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalRouteRefComponent::~DSSignalRouteRefComponent(void)
{
  if (signalroute_ref_list) delete signalroute_ref_list;
}

/****************************************************************************
 * GetSignalRouteRefList(): Liefert die Route des OUTPUT-Befehls zurueck
 *                          Ergebnis: Zeiger auf eine Signalroutenliste
 *                          Seiteneffekte: keine
 ****************************************************************************/
 
DSSignalRouteRefList* DSSignalRouteRefComponent::GetSignalRouteRefList(void) const
{
  return signalroute_ref_list;
}

DSSignalRouteRef DSSignalRouteRefComponent::GetFirstSignalRouteRef(void) const
{
  assert(signalroute_ref_list != NULL);
  if (signalroute_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signalroute_ref_list->GetCurrentData();
}

DSSignalRouteRef DSSignalRouteRefComponent::GetNextSignalRouteRef(void) const
{
  assert(signalroute_ref_list != NULL);
  if (signalroute_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signalroute_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetSignalRouteRefList(): Speichert den uebergebenen Zeiger
 *                          -> route_list: Zeiger auf eine Routenliste
 *                          Ergebnis: DS_OK
 *                          Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalRouteRefComponent::SetSignalRouteRefList(DSSignalRouteRefList *route_list)
{
  if (signalroute_ref_list == route_list) return DS_OK;

  if (signalroute_ref_list) delete signalroute_ref_list;
  signalroute_ref_list = route_list;
  return DS_OK;
}

DSResult DSSignalRouteRefComponent::InsertSignalRouteRef(DSSignalRouteRef route_ref)
{
  assert(route_ref);
  if (signalroute_ref_list == NULL)
  {
    signalroute_ref_list = new DSSignalRouteRefList;
    assert(signalroute_ref_list != NULL);
  }
  return signalroute_ref_list->Append(route_ref);
}

