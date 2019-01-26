/****************************************************************************
 *                 Modul: $RCSfile: DSVariableComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 10:59:24 $
 * $Revision: 1.4 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Variablen
 *            deklariert werden koennen.
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

#include "DSObject.h"
#include "DSVariableComponent.h"
#include "DSVariable.h"
#include "DSString.h"
#include "DSSort.h"
#include "DSGenerator.h"

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

DSVariableComponent::DSVariableComponent(DSObject *father) :
  parent(father)
{
  variable_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariableComponent::~DSVariableComponent(void)
{
  if (variable_definition_list) delete variable_definition_list;
}

DSVariableKeyList* DSVariableComponent::GetVariableList(void) const
{
  return variable_definition_list;
}

DSVariable *DSVariableComponent::GetVariable(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (variable_definition_list == NULL)
  {
    return NULL;
  }

  if (variable_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return variable_definition_list->GetCurrentData();
}

DSVariable *DSVariableComponent::GetVariable(DSString& n) const
{
  return GetVariable(&n);
}

DSVariable *DSVariableComponent::GetVariable(const char * n) const
{
  DSVariable *variable;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  variable = GetVariable(str);
  delete str;

  return variable;
}

DSVariable *DSVariableComponent::GetFirstVariable(void) const
{
  if (variable_definition_list == NULL)
  {
    return NULL;
  }

  if (variable_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return variable_definition_list->GetCurrentData();
}

DSVariable *DSVariableComponent::GetNextVariable(void) const
{
  if (variable_definition_list == NULL)
  {
    return NULL;
  }

  if (variable_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return variable_definition_list->GetCurrentData();
}

DSResult DSVariableComponent::SetVariableList(DSVariableKeyList *list)
{
  if (variable_definition_list == list) return DS_OK;

  if (variable_definition_list != NULL)
  {
    delete variable_definition_list;
  }
  variable_definition_list = list;
  return DS_OK;
}

DSResult DSVariableComponent::InsertVariable(DSVariable* variable)
{
  assert(variable != NULL);
  assert(variable->GetName() != NULL);

  if (variable_definition_list == NULL)
  {
    variable_definition_list = new DSVariableKeyList;
    assert(variable_definition_list != NULL);
  }
  if (variable->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    variable->SetParent(parent);
  }
  return variable_definition_list->Append(variable,
                                          new DSString(*variable->GetName()));
}

DSBoolean DSVariableComponent::HasNonConstantVariables(void) const
{
  DSResult status;
  DSVariable *variable;
  DSSortRef   charstring;
  DSGeneratorRef generator;
  
  charstring = parent->GetSortRefByName(DS_SORT_NAME_CHARSTRING);

  if (!variable_definition_list)
  {
    return DS_FALSE;
  }
  
  if (variable_definition_list->IsEmpty())
  {
    return DS_FALSE;
  }
  
  variable_definition_list->StorePosition();
  
  for (status = variable_definition_list->MoveFirst();
       status == DS_OK;
       status = variable_definition_list->MoveNext())
  {
    variable = variable_definition_list->GetCurrentData();
    assert(variable);
    
    assert(variable->GetSortRef());
    
    if (variable->GetSortRef() == charstring)
    {
      variable_definition_list->RestorePosition();

      return DS_TRUE;
    }
    
    if (variable->GetSortRef()->GetTag() == DS_SORT_GENERATOR)
    {
      generator = (DSGeneratorRef)variable->GetSortRef();
      
      if (*generator->GetGeneratorName() == DS_GENERATOR_NAME_STRING)
      {
        variable_definition_list->RestorePosition();

        return DS_TRUE;
      }
    }
  }
  
  variable_definition_list->RestorePosition();
  
  return DS_FALSE;
}


/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSVariableComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSVariableComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;

  return DS_OK;
}
