/****************************************************************************
 *                 Modul: $RCSfile: DSProcessRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 *
 * Funktionen: GetProcessList(): Liefert Zeiger auf Liste zurueck
 *             SetProcessList(): Speichert die ProcessRefnliste des ProcessRefComponents
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

#include "DSProcessRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

#include "DSProcess.h"

/****************************************************************************
 * Externe ProcessRefn
 ****************************************************************************/

/****************************************************************************
 * Globale ProcessRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSProcessRefComponent::DSProcessRefComponent(DSProcessRefList *process_list) :
  process_ref_list(process_list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSProcessRefComponent::~DSProcessRefComponent(void)
{
  if (process_ref_list) delete process_ref_list;
}

/****************************************************************************
 * GetProcessList(): Liefert den Zeiger auf die ProcessRef-Liste zurueck
 *                   Ergebnis: Zeiger auf eine Liste
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSProcessRefList* DSProcessRefComponent::GetProcessRefList(void) const
{
  return process_ref_list;
}

DSProcessRef DSProcessRefComponent::GetFirstProcessRef(void) const
{
  if (process_ref_list == NULL)
  {
    return NULL;
  }

  if (process_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return process_ref_list->GetCurrentData();
}

DSProcessRef DSProcessRefComponent::GetNextProcessRef(void) const
{
  if (process_ref_list == NULL)
  {
    return NULL;
  }

  if (process_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return process_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetProcessRefList(): Speichert den uebergebenen Zeiger
 *                   -> process_ref: Zeiger auf einen DSString
 *                   Ergebnis: TRUE
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSProcessRefComponent::SetProcessRefList(DSProcessRefList* ref_list)
{
  if (process_ref_list == ref_list) return DS_OK;

  if (process_ref_list) delete process_ref_list;
  process_ref_list = ref_list;
  return DS_OK;
}

DSResult DSProcessRefComponent::InsertProcessRef(DSProcessRef process_ref)
{
  assert(process_ref != NULL);
  if (process_ref_list == NULL)
  {
    process_ref_list = new DSProcessRefList;
    assert(process_ref_list != NULL);
  }
  return process_ref_list->Append(process_ref);
}

