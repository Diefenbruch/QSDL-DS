/****************************************************************************
 *                 Modul: $RCSfile: DSSignalRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 *
 * Funktionen: GetSignalList(): Liefert Zeiger auf Liste zurueck
 *             SetSignalList(): Speichert die SignalRefnliste des SignalRefComponents
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

#include "DSSignalRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

#include "DSSignal.h"

/****************************************************************************
 * Externe SignalRefn
 ****************************************************************************/

/****************************************************************************
 * Globale SignalRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalRefComponent::DSSignalRefComponent(DSSignalRefList *signal_list) :
  signal_ref_list(signal_list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalRefComponent::~DSSignalRefComponent(void)
{
  if (signal_ref_list) delete signal_ref_list;
}

/****************************************************************************
 * GetSignalList(): Liefert den Zeiger auf die SignalRefnliste zurueck
 *                Ergebnis: Zeiger auf eine Liste
 *                Seiteneffekte: keine
 ****************************************************************************/

DSSignalRefList* DSSignalRefComponent::GetSignalRefList(void) const
{
  return signal_ref_list;
}

DSSignalRef DSSignalRefComponent::GetFirstSignalRef(void) const
{
  if (signal_ref_list == NULL)
  {
    return NULL;
  }

  if (signal_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signal_ref_list->GetCurrentData();
}

DSSignalRef DSSignalRefComponent::GetNextSignalRef(void) const
{
  if (signal_ref_list == NULL)
  {
    return NULL;
  }

  if (signal_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signal_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetSignalRefList(): Speichert den uebergebenen Zeiger
 *                   -> signal_ref: Zeiger auf einen DSString
 *                   Ergebnis: TRUE
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalRefComponent::SetSignalRefList(DSSignalRefList* ref_list)
{
  if (signal_ref_list == ref_list) return DS_OK;

  if (signal_ref_list) delete signal_ref_list;
  signal_ref_list = ref_list;
  return DS_OK;
}

DSResult DSSignalRefComponent::InsertSignalRef(DSSignalRef signal_ref)
{
  assert(signal_ref != NULL);
  if (signal_ref_list == NULL)
  {
    signal_ref_list = new DSSignalRefList;
    assert(signal_ref_list != NULL);
  }
  return signal_ref_list->Append(signal_ref);
}

