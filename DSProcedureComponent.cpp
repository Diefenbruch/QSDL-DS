/****************************************************************************
 *                 Modul: $RCSfile: DSProcedureComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
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

#include "DSProcedureComponent.h"
#include "DSProcedure.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Proceduren
 ****************************************************************************/
 
/****************************************************************************
 * Globale Proceduren
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSProcedureComponent::DSProcedureComponent(DSObject *father) :
  parent(father)
{
  procedure_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSProcedureComponent::~DSProcedureComponent(void)
{
  if (procedure_definition_list) delete procedure_definition_list;
}

DSProcedureKeyList* DSProcedureComponent::GetProcedureList(void) const
{
  return procedure_definition_list;
}

DSProcedure *DSProcedureComponent::GetProcedure(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (procedure_definition_list == NULL)
  {
    return NULL;
  }

  if (procedure_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return procedure_definition_list->GetCurrentData();
}

DSProcedure *DSProcedureComponent::GetProcedure(DSString& n) const
{
  return GetProcedure(&n);
}

DSProcedure *DSProcedureComponent::GetProcedure(const char * n) const
{
  DSProcedure *procedure;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);

  procedure = GetProcedure(str);
  delete str;

  return procedure;
}

DSProcedure *DSProcedureComponent::GetFirstProcedure(void) const
{
  if (procedure_definition_list == NULL)
  {
    return NULL;
  }

  if (procedure_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return procedure_definition_list->GetCurrentData();
}

DSProcedure *DSProcedureComponent::GetNextProcedure(void) const
{
  if (procedure_definition_list == NULL)
  {
    return NULL;
  }

  if (procedure_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return procedure_definition_list->GetCurrentData();
}

DSResult DSProcedureComponent::SetProcedureList(DSProcedureKeyList *list)
{
  if (procedure_definition_list == list) return DS_OK;

  if (procedure_definition_list != NULL)
  {
    delete procedure_definition_list;
  }
  procedure_definition_list = list;
  return DS_OK;
}

DSResult DSProcedureComponent::InsertProcedure(DSProcedure* procedure)
{
  assert(procedure != NULL);
  assert(procedure->GetName() != NULL);

  if (procedure_definition_list == NULL)
  {
    procedure_definition_list = new DSProcedureKeyList;
    assert(procedure_definition_list != NULL);
  }
  if (procedure->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    procedure->SetParent(DSProcedureComponent::parent);
  }
  return procedure_definition_list->Append(procedure,
                                           new DSString(*procedure->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSProcedureComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSProcedureComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
