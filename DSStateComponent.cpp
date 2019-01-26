/****************************************************************************
 *                 Modul: $RCSfile: DSStateComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/02/13 07:45:06 $
 * $Revision: 1.4 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Zustaende
 *            definiert werden koennen.
 *
 * Funktionen: GetStartTransition()  liefert die Starttransition
 *             GetStateList()        liefert die Zustandsliste
 *             SetStartTransition()  setzt die Starttransition
 *             SetStateList()        setzt die Zustandsliste
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

#include "DSStateComponent.h"
#include "DSState.h"
#include "DSTransition.h"
#include "DSString.h"
#include "DSInput.h"
#include "DSSave.h"

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

DSStateComponent::DSStateComponent(DSObject *father) :
  parent(father)
{
  start_transition = NULL;
  state_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSStateComponent::~DSStateComponent(void)
{
  if (start_transition) delete start_transition;
  if (state_definition_list) delete state_definition_list;
}

DSTransition *DSStateComponent::GetStartTransition(void) const
{
  return start_transition;
}

DSStateList* DSStateComponent::GetStateList(void) const
{
  return state_definition_list;
}

DSState *DSStateComponent::GetState(DSString* n) const
{
  DSState *state;
  DSStringKeyList *statename_list;

  if (n == NULL)
  {
    return NULL;
  }

  if (state_definition_list == NULL)
  {
    return NULL;
  }

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    statename_list = state->GetNameList();
    if (!statename_list) continue;
    if (statename_list->GotoKeyElement(n) != DS_OK) continue;
    return state;
  }
  return NULL;
}

DSState *DSStateComponent::GetState(DSString& n) const
{
  return GetState(&n);
}

DSState *DSStateComponent::GetState(const char * n) const
{
  DSState *state;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  state = GetState(str);
  delete str;

  return state;
}

DSState *DSStateComponent::GetFirstState(void) const
{
  if (state_definition_list == NULL)
  {
    return NULL;
  }

  if (state_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return state_definition_list->GetCurrentData();
}

DSState *DSStateComponent::GetNextState(void) const
{
  if (state_definition_list == NULL)
  {
    return NULL;
  }

  if (state_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return state_definition_list->GetCurrentData();
}

DSResult DSStateComponent::SetStartTransition(DSTransition *start_trans)
{
  if (start_transition == start_trans) return DS_OK;

  if (start_transition) delete start_transition;
  start_transition = start_trans;

  return DS_OK;
}

DSResult DSStateComponent::SetStateList(DSStateList *list)
{
  if (state_definition_list == list) return DS_OK;

  if (state_definition_list != NULL)
  {
    delete state_definition_list;
  }
  state_definition_list = list;
  return DS_OK;
}

DSResult DSStateComponent::InsertState(DSState* state)
{
  assert(state != NULL);

  if (state_definition_list == NULL)
  {
    state_definition_list = new DSStateList;
    assert(state_definition_list != NULL);
  }
  if (state->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    state->SetParent(parent);
  }
  return state_definition_list->Append(state);
}

DSCardinal DSStateComponent::NumberOfRealStates(void) const
{
  DSState * state;
  DSCardinal counter = 0;

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    if (!state->GetIsIntermediate())
    {
      counter++;
    }
  }
  return counter;
}

DSResult DSStateComponent::DissolveAsteriskStates(void)
{
  DSState *state;
  DSResult result;

loop:
  for (state = GetFirstState();
       state != NULL;
       state = GetNextState())
  {
    if (!state->GetIsAsterisk()) // nur 'State *' interessiert hier!
    {
      continue;
    }
    result = DissolveAsteriskState(state);
    if (result != DS_OK) return result;

    // Listenzeiger restaurieren:
    assert(state_definition_list->GotoElement(state) == DS_OK);

    // 'State *' loeschen:
    state_definition_list->DeleteElement();
    
    goto loop; // we can't trust the current list position!
  }
  return DS_OK;
}

DSResult DSStateComponent::DissolveAsteriskState(DSState *asterisk_state)
{
  DSState *state;
  DSInput *input;
  DSSave  *save;
  
  for (state = GetFirstState();
       state != NULL;
       state = GetNextState())
  {
    if (state->GetIsAsterisk()) // nur normale Zustaende interessieren hier!
    {
      continue;
    }
    if (asterisk_state->GetNameList()) // Ausnahmeliste vorhanden?
    {
      // Feststellen ob der aktuelle Zustand in der Ausnahmeliste des 'State *' ist:
      if (asterisk_state->GetNameList()->GotoKeyElement(state->GetFirstName()) == DS_OK)
      {
        continue;
      }
    }
    for (input = asterisk_state->GetFirstInput();
         input;
         input = asterisk_state->GetNextInput())
    {
      input->Clone(state); // state wird als parent verwendet
    }
    for (save = asterisk_state->GetFirstSave();
         save;
         save = asterisk_state->GetNextSave())
    {
      save->Clone(state);  // state wird als parent verwendet
    }
  }
  return DS_OK;
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSStateComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSStateComponent::SetComponentParent(const DSObject *par)
{
  DSState *state;

  parent = (DSObject *)par;

  for (state = GetFirstState();
       state != NULL;
       state = GetNextState())
  {
    state->SetParent(parent);
  }
  
  return DS_OK;
}
