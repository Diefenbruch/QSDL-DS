/****************************************************************************
 *                 Modul: $RCSfile: DSVariableAccessComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 10:59:24 $
 * $Revision: 1.3 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen Variablen-
 *            zugriffe vorkommen.
 *
 * Funktionen: GetVariableAccessList(): Liefert Zeiger auf Liste zurueck
 *             SetVariableAccessList(): Speichert den Timerindex
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

#include "DSVariableAccessComponent.h"
#include "DSVariableAccess.h"

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

DSVariableAccessComponent::DSVariableAccessComponent(DSObject             *father,
                                                     DSVariableAccessList *access_list) :
  variable_access_list(access_list),
  parent(father)
{
  DSVariableAccess *variable_access;
  
  if (variable_access_list && parent)
  {
    for (variable_access = GetFirstVariableAccess();
         variable_access;
         variable_access = GetNextVariableAccess())
    {
      if (variable_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
      {
        variable_access->SetParent(parent);
      }
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariableAccessComponent::~DSVariableAccessComponent(void)
{
  if (variable_access_list) delete variable_access_list;
}

/****************************************************************************
 * GetVariableAccessList(): Liefert den Zeiger auf die Variablenliste zurueck
 *                       Ergebnis: Zeiger auf eine Liste
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSVariableAccessList* DSVariableAccessComponent::GetVariableAccessList(void) const
{
  return variable_access_list;
}

DSVariableAccess *DSVariableAccessComponent::GetFirstVariableAccess(void) const
{
  if (variable_access_list == NULL)
  {
    return NULL;
  }

  if (variable_access_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return variable_access_list->GetCurrentData();
}

DSVariableAccess *DSVariableAccessComponent::GetNextVariableAccess(void) const
{
  if (variable_access_list == NULL)
  {
    return NULL;
  }

  if (variable_access_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return variable_access_list->GetCurrentData();
}

/****************************************************************************
 * SetVariableAccessList(): Speichert den uebergebenen Zeiger
 *                          -> access_list: Zeiger auf eine Variablezugriffsliste
 *                          Ergebnis: TRUE
 *                          Seiteneffekte: keine
 ****************************************************************************/

DSResult DSVariableAccessComponent::SetVariableAccessList(DSVariableAccessList* access_list)
{
  DSVariableAccess *variable_access;
  
  if (variable_access_list == access_list) return DS_OK;

  if (variable_access_list) delete variable_access_list;
  variable_access_list = access_list;

  if (variable_access_list && parent)
  {
    for (variable_access = GetFirstVariableAccess();
         variable_access;
         variable_access = GetNextVariableAccess())
    {
      if (variable_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
      {
        variable_access->SetParent(parent);
      }
    }
  }
  return DS_OK;
}

DSResult DSVariableAccessComponent::InsertVariableAccess(DSVariableAccess *access)
{
  assert(access);
  if (variable_access_list == NULL)
  {
    variable_access_list = new DSVariableAccessList;
    assert(variable_access_list != NULL);
  }
  if (access->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    access->SetParent(parent);
  }
  return variable_access_list->Append(access);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSVariableAccessComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSVariableAccessComponent::SetComponentParent(const DSObject *par)
{
  DSVariableAccess *variable_access;
  
  parent = (DSObject *)par;

  if (variable_access_list)
  {
    for (variable_access = GetFirstVariableAccess();
         variable_access;
         variable_access = GetNextVariableAccess())
    {
      assert(variable_access->GetParent() == NULL);
      variable_access->SetParent(parent);
    }
  }

  return DS_OK;
}
