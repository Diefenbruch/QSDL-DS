/****************************************************************************
 *                 Modul: $RCSfile: DSMachineComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Datentypen
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

#include "DSMachineComponent.h"
#include "DSMachine.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Machinen
 ****************************************************************************/
 
/****************************************************************************
 * Globale Machinen
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSMachineComponent::DSMachineComponent(DSObject *father) :
  parent(father)
{
  machine_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachineComponent::~DSMachineComponent(void)
{
  if (machine_definition_list) delete machine_definition_list;
}

DSMachineKeyList* DSMachineComponent::GetMachineList(void) const
{
  return machine_definition_list;
}

DSMachine *DSMachineComponent::GetMachine(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (machine_definition_list == NULL)
  {
    return NULL;
  }

  if (machine_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return machine_definition_list->GetCurrentData();
}

DSMachine *DSMachineComponent::GetMachine(DSString& n) const
{
  return GetMachine(&n);
}

DSMachine *DSMachineComponent::GetMachine(const char * n) const
{
  DSMachine *machine;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  machine = GetMachine(str);
  delete str;

  return machine;
}

DSMachine *DSMachineComponent::GetFirstMachine(void) const
{
  if (machine_definition_list == NULL)
  {
    return NULL;
  }

  if (machine_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return machine_definition_list->GetCurrentData();
}

DSMachine *DSMachineComponent::GetNextMachine(void) const
{
  if (machine_definition_list == NULL)
  {
    return NULL;
  }

  if (machine_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return machine_definition_list->GetCurrentData();
}

DSResult DSMachineComponent::SetMachineList(DSMachineKeyList *list)
{
  if (machine_definition_list == list) return DS_OK;

  if (machine_definition_list != NULL)
  {
    delete machine_definition_list;
  }
  machine_definition_list = list;
  return DS_OK;
}

DSResult DSMachineComponent::InsertMachine(DSMachine* machine)
{
  assert(machine != NULL);
  assert(machine->GetName() != NULL);

  if (machine_definition_list == NULL)
  {
    machine_definition_list = new DSMachineKeyList;
    assert(machine_definition_list != NULL);
  }
  if (machine->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    machine->SetParent(DSMachineComponent::parent);
  }
  return machine_definition_list->Append(machine,
                                         new DSString(*machine->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSMachineComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSMachineComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
