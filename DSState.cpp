/****************************************************************************
 *                 Modul: $RCSfile: DSState.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von Namen, Transitionslisten und SignalItemliste in Verbindung
 *          mit einem Zustand (STATE)
 *
 * Funktionen: GetNameList(): Gibt einen Zeiger auf die Namensliste zurueck
 *             GetTransitionList(): Liefert Zeiger auf Liste zurueck
 *             GetSaveSignalItemList(): Liefert Listenzeiger
 *             SetName(): Speichert Zustandsnamen
 *             SetTransitionList(): Speichert die Transitionsliste
 *             SetSaveSignalList(): Speichert Listenzeiger
 *             Save(): Abspeicherung der Infos in einer Datei
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

#include "DSState.h"
#include "DSProcess.h" // wegen parent
#include "DSProcedure.h" // wegen parent
#include "DSInput.h"
#include "DSSave.h"
#include "DSTransition.h"
#include "DSExpression.h"
#include "DSString.h"
#include "DSTimer.h" // for CC template instantiation!
#include "DSSignal.h" // for CC template instantiation!

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/

/****************************************************************************
 * Globale Variablen
 ****************************************************************************/

DSBoolean first_asterisk_input;

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSState::DSState (DSObject        *father,
                  DSStringKeyList *n,
                  DSBoolean inter_state) :
  DSObject(DS_STATE, father),
  name_list(n),
  intermediate(inter_state)
{
  input_list = NULL;
  save_list = NULL;
  is_asterisk = DS_FALSE;
  awake_time = NULL;

  if (father)
  {
    if (!name_list)
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertState(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertState(this);
        break;
      default:
        std::cerr << "Illegal parent for state.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSState::DSState (DSObject *father,
                  DSString *n,
                  DSBoolean inter_state) :
  DSObject(DS_STATE, father),
  intermediate(inter_state)
{
  input_list = NULL;
  save_list = NULL;
  is_asterisk = DS_FALSE;
  awake_time = NULL;

  name_list = new DSStringKeyList;
  assert(name_list);

  if (n)
  {
    assert(name_list->Append(n, new DSString(this, n->GetString())) == DS_OK);
  }
  if (father)
  {
    if (!name_list)
    {
      std::cerr << "State has a parent but no name!\n";
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertState(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertState(this);
        break;
      default:
        std::cerr << "Illegal parent for state.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSState::DSState (DSObject *father,
                  DSString &n,
                  DSBoolean inter_state) :
  DSObject(DS_STATE, father),
  intermediate(inter_state)
{
  input_list = NULL;
  save_list = NULL;
  is_asterisk = DS_FALSE;
  awake_time = NULL;

  name_list = new DSStringKeyList;
  assert(name_list);

  assert(name_list->Append(&n, new DSString(this, n)) == DS_OK);

  if (father)
  {
    if (!name_list)
    {
      std::cerr << "State has a parent but no name!\n";
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertState(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertState(this);
        break;
      default:
        std::cerr << "Illegal parent for state.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSState::DSState (DSObject *father,
                  const char *n,
                  DSBoolean inter_state) :
  DSObject(DS_STATE, father),
  intermediate(inter_state)
{
  input_list = NULL;
  save_list = NULL;
  is_asterisk = DS_FALSE;
  awake_time = NULL;

  name_list = new DSStringKeyList;
  assert(name_list);

  if (n)
  {
    assert(name_list->Append(new DSString(this, n), new DSString(this, n)) == DS_OK);
  }
  if (father)
  {
    if (!name_list)
    {
      std::cerr << "State has a parent but no name!\n";
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertState(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertState(this);
        break;
      default:
        std::cerr << "Illegal parent for state.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSState::~DSState(void)
{
  if (name_list)  delete name_list;      /* Destruktor der Liste      */
  if (input_list) delete input_list;
  if (save_list)  delete save_list;
  if (awake_time) delete awake_time;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSState::New(DSObject *father) const
{
  return new DSState(father);
}

/****************************************************************************
 * GetIsAsterisk(): Liefert Flagwert zurueck
 *                  Ergebnis: Boolscher Typ
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSState::GetIsAsterisk(void) const
{
  return is_asterisk;
}

/****************************************************************************
 * GetIsIntermediate(): Liefert Flagwert zurueck, ob dieser Zustand ein
 *                      Zwischenzustand ist, der durch die Linearisierung
 *                      von Decisions entstanden ist
 *                  Ergebnis: Boolscher Typ
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSState::GetIsIntermediate(void) const
{
  return intermediate;
}

/****************************************************************************
 * GetNameList(): Liefert den Zeiger auf die Namensliste zurueck
 *                Ergebnis: Zeiger auf einen DSString
 *                Seiteneffekte: keine
 ****************************************************************************/

DSStringKeyList *DSState::GetNameList(void) const
{
  return name_list;
}

DSString *DSState::GetFirstName(void) const
{
  if (name_list == NULL)
  {
    return NULL;
  }

  if (name_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return name_list->GetCurrentData();
}

DSString *DSState::GetNextName(void) const
{
  if (name_list == NULL)
  {
    return NULL;
  }

  if (name_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return name_list->GetCurrentData();
}

/****************************************************************************
 * GetInputList(): Liefert den Zeiger auf die Input-Liste zurueck
 *                 Ergebnis: Zeiger auf eine Liste
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSInputList *DSState::GetInputList(void) const
{
  return input_list;
}

DSInput *DSState::GetFirstInput(void) const
{
  first_asterisk_input = DS_TRUE;
  
  if (input_list == NULL)
  {
    return NULL;
  }

  if (input_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }

  return input_list->GetCurrentData();
}

DSInput *DSState::GetNextInput(void) const
{
  if (input_list == NULL)
  {
    return NULL;
  }

  if (input_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return input_list->GetCurrentData();
}

/****************************************************************************
 * GetSaveList(): Liefert Zeiger auf die Liste der Save-Statements zurueck
 *                Ergebnis: Zeiger auf eine Liste
 *                Seiteneffekte: keine
 ****************************************************************************/

DSSaveList *DSState::GetSaveList(void) const
{
  return save_list;
}

DSSave *DSState::GetFirstSave(void) const
{
  if (save_list == NULL)
  {
    return NULL;
  }

  if (save_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }

  return save_list->GetCurrentData();
}

DSSave *DSState::GetNextSave(void) const
{
  if (save_list == NULL)
  {
    return NULL;
  }

  if (save_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return save_list->GetCurrentData();
}


DSResult DSState::Append(DSState *new_state)
{
  DSString *name;
  DSInput *input;
  DSSave *save;

  assert(new_state);

  for (name = new_state->GetFirstName();
       name;
       name = new_state->GetNextName())
  {
    if (name_list->IsKeyInList(name) == DS_FALSE) InsertName(name);
  }
  for (input = new_state->GetFirstInput();
       input;
       input = new_state->GetNextInput())
  {
    InsertInput(input);
  }
  for (save = new_state->GetFirstSave();
       save;
       save = new_state->GetNextSave())
  {
    InsertSave(save);
  }
  return DS_OK;
}

DSExpression *DSState::GetAwakeTime(void) const
{
  return awake_time;
}

DSResult DSState::GetInputSet(DSSignalRefList *signal_ref_list,
                              DSTimerRefList *timer_ref_list) const
{
  DSInput *input;
  DSResult result;

  if (!signal_ref_list)
  {
    signal_ref_list = new DSSignalRefList;
    assert(signal_ref_list);
  }
  if (!timer_ref_list)
  {
    timer_ref_list = new DSTimerRefList;
    assert(timer_ref_list);
  }

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->GetIsAsterisk())     // 'input *' ?
    {
      result = input->GetAsteriskSet(signal_ref_list,
                                     timer_ref_list);
      if (result != DS_OK) return DS_ERROR;
    }
    else                            // kein 'input *' !
    {
      result = input->GetSignalSet(signal_ref_list);
      if (result != DS_OK) return DS_ERROR;
      result = input->GetTimerSet(timer_ref_list);
      if (result != DS_OK) return DS_ERROR;
    }
  } // for input-list of state

  return DS_OK;
}

/****************************************************************************
 * GetSpontanousTransitionList: legt eine Liste mit allen spontanen Transitionen
 *                an, die in einem SDL-State enthalten sind
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSState::GetSpontanousTransitionList(DSTransitionRefList *transition_list) const
{
  DSInput *input;

  assert(transition_list);

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->GetIsSpontanous())
    {
      assert(transition_list->Append(input->GetTransition()) == DS_OK);
    }
  }
  return DS_OK;
}

/****************************************************************************
 * SetIsAsterisk(): Setzt das Flag
 *                  -> asterisk: Boolscher Typ
 *                  Ergebnis: TRUE
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSState::SetIsAsterisk(DSBoolean asterisk)
{
  is_asterisk = asterisk;
  return DS_OK;
}

/****************************************************************************
 * SetNameList(): Speichert den uebergebenen Zeiger
 *                -> list: Zeiger auf eine DSStringKeyList
 *                Ergebnis: TRUE
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSState::SetNameList(DSStringKeyList* list)
{
  if (name_list == list) return DS_OK;

  if (name_list) delete name_list;
  name_list = list;
  return DS_OK;
}

DSResult DSState::InsertName(DSString* name)
{
  assert(name);
  if (name_list == NULL)
  {
    name_list = new DSStringKeyList;
    assert(name_list != NULL);
  }
  return name_list->Append(name, new DSString(name->GetString()));
}

DSResult DSState::InsertName(DSString& name)
{
  if (name_list == NULL)
  {
    name_list = new DSStringKeyList;
    assert(name_list != NULL);
  }
  return name_list->Append(&name, new DSString(name));
}

DSResult DSState::InsertName(const char* name)
{
  if (name_list == NULL)
  {
    name_list = new DSStringKeyList;
    assert(name_list != NULL);
  }
  return name_list->Append(new DSString(name), new DSString(name));
}

/****************************************************************************
 * SetInputList(): Speichert den uebergebenen Zeiger
 *                 -> tran_list: Zeiger auf einen DSString
 *                 Ergebnis: TRUE
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSState::SetInputList(DSInputList* list)
{
  if (input_list == list) return DS_OK;

  if (input_list) delete input_list;
  input_list = list;
  return DS_OK;
}

DSResult DSState::InsertInput(DSInput* input)
{
  assert(input);
  if (input_list == NULL)
  {
    input_list = new DSInputList;
    assert(input_list != NULL);
  }
  input->SetParent(this);
  return input_list->Append(input);
}

/****************************************************************************
 * SetAsteriskStateInputList(): Speichert den uebergebenen Zeiger
 *                 -> tran_list: Zeiger auf einen DSString
 *                 Ergebnis: TRUE
 *                 Seiteneffekte: keine
 ****************************************************************************/
/*
DSResult DSState::SetAsteriskStateInputList(DSInputRefList* list)
{
  if (asterisk_input_list == list) return DS_OK;

  if (asterisk_input_list) delete asterisk_input_list;
  asterisk_input_list = list;
  return DS_OK;
}

DSResult DSState::InsertAsteriskStateInput(DSInputRef input)
{
  assert(input);
  if (asterisk_input_list == NULL)
  {
    asterisk_input_list = new DSInputRefList;
    assert(asterisk_input_list != NULL);
  }
  return asterisk_input_list->Append(input);
}
*/

/****************************************************************************
 * SetSaveList(): Speichert den uebergebenen Zeiger
 *                -> sig_list: Zeiger auf einen DSString
 *                Ergebnis: TRUE
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSState::SetSaveList(DSSaveList* list)
{
  if (save_list == list) return DS_OK;

  if (save_list) delete save_list;
  save_list = list;
  return DS_OK;
}

DSResult DSState::InsertSave(DSSave *save)
{
  assert(save);
  if (save_list == NULL)
  {
    save_list = new DSSaveList;
    assert(save_list != NULL);
  }
  save->SetParent(this);
  return save_list->Append(save);
}

/****************************************************************************
 * SetAsteriskStateSaveList(): Speichert den uebergebenen Zeiger
 *                -> sig_list: Zeiger auf einen DSString
 *                Ergebnis: TRUE
 *                Seiteneffekte: keine
 ****************************************************************************/
/*
DSResult DSState::SetAsteriskStateSaveList(DSSaveRefList* list)
{
  if (asterisk_save_list == list) return DS_OK;

  if (asterisk_save_list) delete asterisk_save_list;
  asterisk_save_list = list;
  return DS_OK;
}

DSResult DSState::InsertAsteriskStateSave(DSSaveRef save)
{
  assert(save);
  if (asterisk_save_list == NULL)
  {
    asterisk_save_list = new DSSaveRefList;
    assert(asterisk_save_list != NULL);
  }
  return asterisk_save_list->Append(save);
}
*/

DSResult DSState::SetAwakeTime(DSExpression *time)
{
  if (awake_time == time) return DS_OK;

  if (awake_time) delete awake_time;
  awake_time = time;

  if (awake_time != NULL)
  {
    if (awake_time->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      awake_time->SetParent(this);
    }
  }

  return DS_OK;
}

/*
DSBoolean DSState::HasRequests(void) const
{
  DSTransition *transition;
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    if (!transition) // kann bei Environment-Prozessen passieren!
    {
      continue;
    }
    if (transition->HasRequests()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSState::HasCalls(void) const
{
  DSTransition *transition;
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    if (!transition) // kann bei Environment-Prozessen passieren!
    {
      continue;
    }
    if (transition->HasCalls()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSState::HasOutputs(void) const
{
  DSTransition *transition;
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    if (!transition) // kann bei Environment-Prozessen passieren!
    {
      continue;
    }
    if (transition->HasOutputs()) return DS_TRUE;
  }
  return DS_FALSE;
}
*/

DSBoolean DSState::HasAction(DSActionTag action_type) const
{
  DSTransition *transition;
  DSInput *input;

  if (GetInputList())
  {
    GetInputList()->StorePosition();
    
    for (input = GetFirstInput();
         input;
         input = GetNextInput())
    {
      transition = input->GetTransition();
      if (!transition) // kann bei Environment-Prozessen passieren!
      {
        continue;
      }
      if (transition->HasAction(action_type))
      {
        GetInputList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetInputList()->RestorePosition();
  }
  
  return DS_FALSE;
}

DSBoolean DSState::HasDelayedOutputs(void) const
{
  DSTransition *transition;
  DSInput *input;

  if (GetInputList())
  {
    GetInputList()->StorePosition();
    
    for (input = GetFirstInput();
         input;
         input = GetNextInput())
    {
      transition = input->GetTransition();
      if (!transition) // kann bei Environment-Prozessen passieren!
      {
        continue;
      }
      if (transition->HasDelayedOutputs())
      {
        GetInputList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetInputList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSState::HasInputAsterisk(void) const
{
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->GetIsAsterisk()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSState::HasInputData(void) const
{
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->HasInputData()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSState::HasInputSignalData(void) const
{
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->HasInputSignalData()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSState::HasInputTimerSignalData(void) const
{
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->HasInputTimerSignalData()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSCardinal DSState::HasEnablingConditions(void) const
{
  DSCardinal num = 0;
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->GetEnablingCondition() &&
        (input->GetInputSignalList() != NULL ||
         input->GetInputTimerSignalList() != NULL))
    {
      num++;
    }
  }
  return num;
}

DSCardinal DSState::HasContinuousSignals(void) const
{
  DSCardinal num = 0;
  DSInput *input;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    if (input->GetEnablingCondition() &&
        input->GetInputSignalList() == NULL &&
        input->GetInputTimerSignalList() == NULL)
    {
      num++;
    }
  }
  return num;
}

DSCardinal DSState::NumOfActions(DSActionTag action_type) const
{
  DSTransition *transition;
  DSInput      *input;
  DSCardinal    num_of_actions = 0;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    if (!transition) // kann bei Environment-Prozessen passieren!
    {
      continue;
    }
    num_of_actions += transition->NumOfActions(action_type);
  }
  return num_of_actions;
}

/****************************************************************************
 * GetSaveType: Stellt fest welche Art(en) von Sicherungsmengen existieren
 *              Ergebnis: (siehe DSSaveType in DSBasicTypes.h)
 *              Seiteneffekte: keine
 ****************************************************************************/

DSSaveType DSState::GetSaveType(void) const
{
  DSSave *save;
  DSSaveType save_signals = DS_SAVE_NONE;
  DSSaveType save_asterisk = DS_SAVE_NONE;
  DSSaveType save_result;

  for (save = GetFirstSave();
       save;
       save = GetNextSave())
  { 
    if (save->GetSignalList())
    {
      if (save->GetSignalList()->GetFirstSignalRef()) save_signals = DS_SAVE_SIGNALS;
    }
    if (save->GetIsAsterisk())
    {
      save_asterisk = DS_SAVE_ALL;
    }
  }
  save_result = (DSSaveType)(save_signals + save_asterisk);

  return save_result;
}    

DSResult DSState::DissolveNextStateDash(void)
{
  DSResult      result;
  DSInput      *input;
  DSTransition *transition;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    assert(transition);
    result = transition->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }

  return DS_OK;
}

DSResult DSState::DissolveDecisions(DSBoolean all)
{
  DSResult      result;
  DSInput      *input;
  DSTransition *transition;
  DSCardinal    counter = 1;

  for (input = GetFirstInput();
       input;
       input = GetNextInput())
  {
    transition = input->GetTransition();
    assert(transition);
    result = transition->DissolveDecisions(counter, all);
    if (result != DS_OK) return result;
  }

  return DS_OK;
}

DSObject *DSState::Clone(DSObject *father, DSObject *fill_this) const
{
  DSState *new_state;

  if (fill_this == NULL)
  {
    new_state = (DSState *)New(father);
    assert(new_state);
  }
  else
  {
    assert(fill_this->GetType() == DS_STATE);
    new_state = (DSState *)fill_this;
  }

  new_state->is_asterisk = is_asterisk;

  if (GetNameList())
  {
    new_state->SetNameList((DSStringKeyList *)GetNameList()->Clone((DSObject *)new_state));
  }

  if (GetInputList())
  {
    new_state->SetInputList(GetInputList()->Clone((DSObject *)new_state));
  }

  if (GetSaveList())
  {
    new_state->SetSaveList(GetSaveList()->Clone((DSObject *)new_state));
  }

  if (GetAwakeTime())
  {
    new_state->SetAwakeTime((DSExpression *)GetAwakeTime()->Clone((DSObject *)new_state));
  }

  return new_state;
}

DSResult DSState::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_STRING, what);
  Run(writer, DS_INPUT, what);
  Run(writer, DS_SAVE, what);
  return DS_OK;
}

DSResult DSState::Run(DSWriter *writer, DSType object_type,
                      DSCardinal what) const
{
  DSResult    result;
  DSStringRef name;
  DSInputRef  input;
  DSSaveRef   save;

  assert(writer);

  switch(object_type)
  {
    case DS_STRING:
      for (name = GetFirstName();
           name;
           name = GetNextName())
      {
        result = name->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_INPUT:
      for (input = GetFirstInput();
           input;
           input = GetNextInput())
      {
        result = input->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_TRANSITION:
      for (input = GetFirstInput();
           input;
           input = GetNextInput())
      {
        if (input->GetTransition())
        {
          result = input->GetTransition()->Write(writer, what);
          if (result != DS_OK)
          {
            return DS_ERROR;
          }
        }
      }
      break;

    case DS_SAVE:
      for (save = GetFirstSave();
           save;
           save = GetNextSave())
      {
        result = save->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      std::cerr << "Illegal Run on state!" << std::endl;
      assert(DS_FALSE);
      break;
  }
  return DS_OK;
}

