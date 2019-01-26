/****************************************************************************
 *                 Modul: $RCSfile: DSMachineServiceComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Dienste
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

#include "DSMachineServiceComponent.h"
#include "DSMachineService.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe MachineServicen
 ****************************************************************************/
 
/****************************************************************************
 * Globale MachineServicen
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSMachineServiceComponent::DSMachineServiceComponent(DSObject *father) :
  parent(father)
{
  machineservice_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachineServiceComponent::~DSMachineServiceComponent(void)
{
  if (machineservice_definition_list) delete machineservice_definition_list;
}

DSMachineServiceKeyList* DSMachineServiceComponent::GetMachineServiceList(void) const
{
  return machineservice_definition_list;
}

DSMachineService *DSMachineServiceComponent::GetMachineService(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (machineservice_definition_list == NULL)
  {
    return NULL;
  }

  if (machineservice_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return machineservice_definition_list->GetCurrentData();
}

DSMachineService *DSMachineServiceComponent::GetMachineService(DSString& n) const
{
  return GetMachineService(&n);
}

DSMachineService *DSMachineServiceComponent::GetMachineService(const char * n) const
{
  DSMachineService *machineservice;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  machineservice = GetMachineService(str);
  delete str;

  return machineservice;
}

DSMachineService *DSMachineServiceComponent::GetFirstMachineService(void) const
{
  if (machineservice_definition_list == NULL)
  {
    return NULL;
  }

  if (machineservice_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return machineservice_definition_list->GetCurrentData();
}

DSMachineService *DSMachineServiceComponent::GetNextMachineService(void) const
{
  if (machineservice_definition_list == NULL)
  {
    return NULL;
  }

  if (machineservice_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return machineservice_definition_list->GetCurrentData();
}

DSResult DSMachineServiceComponent::SetMachineServiceList(DSMachineServiceKeyList *list)
{
  if (machineservice_definition_list == list) return DS_OK;

  if (machineservice_definition_list != NULL)
  {
    delete machineservice_definition_list;
  }
  machineservice_definition_list = list;
  return DS_OK;
}

DSResult DSMachineServiceComponent::InsertMachineService(DSMachineService* machineservice)
{
  assert(machineservice != NULL);
  assert(machineservice->GetName() != NULL);

  if (machineservice_definition_list == NULL)
  {
    machineservice_definition_list = new DSMachineServiceKeyList;
    assert(machineservice_definition_list != NULL);
  }
  if (machineservice->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    machineservice->SetParent(parent);
  }
  return machineservice_definition_list->Append(machineservice,
                                                new DSString(*machineservice->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSMachineServiceComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSMachineServiceComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
