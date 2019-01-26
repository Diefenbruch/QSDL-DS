/****************************************************************************
 *                 Modul: $RCSfile: DSSortRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 *
 * Funktionen: GetSortList(): Liefert Zeiger auf Liste zurueck
 *             SetSortList(): Speichert die SortRefnliste des SortRefComponents
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

#include "DSSortRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

#include "DSSort.h"

/****************************************************************************
 * Externe SortRefn
 ****************************************************************************/

/****************************************************************************
 * Globale SortRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSortRefComponent::DSSortRefComponent(DSSortRefList *sort_list) :
  sort_ref_list(sort_list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSortRefComponent::~DSSortRefComponent(void)
{
  if (sort_ref_list) delete sort_ref_list;
}

/****************************************************************************
 * GetSortList(): Liefert den Zeiger auf die SortRefnliste zurueck
 *                Ergebnis: Zeiger auf eine Liste
 *                Seiteneffekte: keine
 ****************************************************************************/

DSSortRefList* DSSortRefComponent::GetSortRefList(void) const
{
  return sort_ref_list;
}

DSSortRef DSSortRefComponent::GetFirstSortRef(void) const
{
  if (sort_ref_list == NULL)
  {
    return NULL;
  }

  if (sort_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return sort_ref_list->GetCurrentData();
}

DSSortRef DSSortRefComponent::GetNextSortRef(void) const
{
  if (sort_ref_list == NULL)
  {
    return NULL;
  }

  if (sort_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return sort_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetSortRefList(): Speichert den uebergebenen Zeiger
 *                   -> sort_ref: Zeiger auf einen DSString
 *                   Ergebnis: TRUE
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSortRefComponent::SetSortRefList(DSSortRefList* ref_list)
{
  if (sort_ref_list == ref_list) return DS_OK;

  if (sort_ref_list) delete sort_ref_list;
  sort_ref_list = ref_list;
  return DS_OK;
}

DSResult DSSortRefComponent::InsertSortRef(DSSortRef sort_ref)
{
  assert(sort_ref != NULL);
  if (sort_ref_list == NULL)
  {
    sort_ref_list = new DSSortRefList;
    assert(sort_ref_list != NULL);
  }
  return sort_ref_list->Append(sort_ref);
}

