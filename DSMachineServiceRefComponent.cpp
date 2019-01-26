/****************************************************************************
 *                 Modul: $RCSfile: DSMachineServiceRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 *
 * Funktionen: GetMachineServiceList(): Liefert Zeiger auf Liste zurueck
 *             SetMachineServiceList(): Speichert die MachineServiceRefnliste des MachineServiceRefComponents
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

#include "DSMachineServiceRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

#include "DSMachineService.h"

/****************************************************************************
 * Externe MachineServiceRefn
 ****************************************************************************/

/****************************************************************************
 * Globale MachineServiceRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSMachineServiceRefComponent::DSMachineServiceRefComponent(DSMachineServiceRefList *machine_service_list) :
  machine_service_ref_list(machine_service_list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachineServiceRefComponent::~DSMachineServiceRefComponent(void)
{
  if (machine_service_ref_list) delete machine_service_ref_list;
}

/****************************************************************************
 * GetMachineServiceList(): Liefert den Zeiger auf die MachineServiceRefnliste zurueck
 *                Ergebnis: Zeiger auf eine Liste
 *                Seiteneffekte: keine
 ****************************************************************************/

DSMachineServiceRefList* DSMachineServiceRefComponent::GetMachineServiceRefList(void) const
{
  return machine_service_ref_list;
}

DSMachineServiceRef DSMachineServiceRefComponent::GetFirstMachineServiceRef(void) const
{
  if (machine_service_ref_list == NULL)
  {
    return NULL;
  }

  if (machine_service_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return machine_service_ref_list->GetCurrentData();
}

DSMachineServiceRef DSMachineServiceRefComponent::GetNextMachineServiceRef(void) const
{
  if (machine_service_ref_list == NULL)
  {
    return NULL;
  }

  if (machine_service_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return machine_service_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetMachineServiceRefList(): Speichert den uebergebenen Zeiger
 *                   -> machine_service_ref: Zeiger auf einen DSString
 *                   Ergebnis: TRUE
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSMachineServiceRefComponent::SetMachineServiceRefList(DSMachineServiceRefList* ref_list)
{
  if (machine_service_ref_list == ref_list) return DS_OK;

  if (machine_service_ref_list) delete machine_service_ref_list;
  machine_service_ref_list = ref_list;
  return DS_OK;
}

DSResult DSMachineServiceRefComponent::InsertMachineServiceRef(DSMachineServiceRef machine_service_ref)
{
  assert(machine_service_ref != NULL);
  if (machine_service_ref_list == NULL)
  {
    machine_service_ref_list = new DSMachineServiceRefList;
    assert(machine_service_ref_list != NULL);
  }
  return machine_service_ref_list->Append(machine_service_ref);
}

