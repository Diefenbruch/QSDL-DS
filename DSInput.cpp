/****************************************************************************
 *                 Modul: $RCSfile: DSInput.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/30 11:06:45 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul stellt die Funktionen fuer das SDL-Input-Konstrukt
 *          zur Verfuegung
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

#include "DSInput.h"
#include "DSState.h" // wegen parent
#include "DSProcess.h" // wegen valid input set
#include "DSTransition.h"
#include "DSInputSignal.h"
#include "DSInputTimerSignal.h"
#include "DSExpression.h"
#include "DSString.h"
#include "DSTimer.h"
#include "DSSignal.h"

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

DSInput::DSInput(DSObject               *father,
                 DSBoolean               has_prio,
                 DSBoolean               asterisk,
                 DSBoolean               spontanous,
                 DSInputSignalList      *s_list,
                 DSInputTimerSignalList *t_list,
                 DSExpression           *enabling,
                 DSTransition           *trans) :
  DSObject(DS_INPUT, father),
  has_priority(has_prio),
  is_asterisk(asterisk),
  is_spontanous(spontanous),
  signal_list(s_list),
  timer_list(t_list),
  enabling_condition(enabling),
  transition(trans)
{
//  probability = NULL;
  priority = NULL;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_STATE:
        ((DSState*)father)->InsertInput(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (enabling_condition)
  {
    if (enabling_condition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      enabling_condition->SetParent(this);
    }
  }
  if (transition)
  {
    if (transition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      transition->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSInput::~DSInput(void)
{
  if (signal_list)  delete signal_list;
  if (timer_list)  delete timer_list;
  if (enabling_condition)  delete enabling_condition;
  if (transition)  delete transition;
//  if (probability) delete probability;
  if (priority) delete priority;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSInput::New(DSObject *father) const
{
  return new DSInput(father);
}

DSBoolean DSInput::GetHasPriority(void) const
{
  return has_priority;
}

/****************************************************************************
 * GetIsAsterisk(): Liefert Flagwert zurueck
 *                  Ergebnis: Boolscher Typ
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSInput::GetIsAsterisk(void) const
{
  return is_asterisk;
}

/****************************************************************************
 * GetIsSpontanous(): Liefert Flagwert zurueck
 *                    Ergebnis: Boolscher Typ
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSInput::GetIsSpontanous(void) const
{
  return is_spontanous;
}

/****************************************************************************
 * GetPriority(): Liefert Prioritaet von continuous signals
 *                Ergebnis: String (Integer Literal)
 *                Seiteneffekte: keine
 ****************************************************************************/

DSString *DSInput::GetPriority(void) const
{
  return priority;
}

/****************************************************************************
 * GetInputSignalList(): Liefert den Zeiger auf Signalliste zurueck
 *                       Ergebnis: Zeiger auf eine Liste
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSInputSignalList *DSInput::GetInputSignalList(void) const
{
  return signal_list;
}

DSInputSignal *DSInput::GetFirstInputSignal(void) const
{
  if (signal_list == NULL)
  {
    return NULL;
  }

  if (signal_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signal_list->GetCurrentData();
}

DSInputSignal *DSInput::GetNextInputSignal(void) const
{
  if (signal_list == NULL)
  {
    return NULL;
  }

  if (signal_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signal_list->GetCurrentData();
}

/****************************************************************************
 * GetInputTimerSignalList(): Liefert Zeiger auf Timerliste zurueck
 *                            Ergebnis: Zeiger auf eine Liste
 *                            Seiteneffekte: keine
 ****************************************************************************/

DSInputTimerSignalList *DSInput::GetInputTimerSignalList(void) const
{
  return timer_list;
}

DSInputTimerSignal *DSInput::GetFirstInputTimerSignal(void) const
{
  if (timer_list == NULL)
  {
    return NULL;
  }

  if (timer_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return timer_list->GetCurrentData();
}

DSInputTimerSignal *DSInput::GetNextInputTimerSignal(void) const
{
  if (timer_list == NULL)
  {
    return NULL;
  }

  if (timer_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return timer_list->GetCurrentData();
}

DSExpression *DSInput::GetEnablingCondition(void) const
{
  return enabling_condition;
}

DSTransition *DSInput::GetTransition(void) const
{
  return transition;
}

DSResult DSInput::GetSignalSet(DSSignalRefList *signal_ref_list) const
{
  DSInputSignal *input_signal;
  DSSignalRef signal;

  assert(signal_ref_list);

  for (input_signal = GetFirstInputSignal(); 
       input_signal;
       input_signal = GetNextInputSignal())
  {
    signal = input_signal->GetSignalRef();

    if (!signal_ref_list->IsInList(signal))
    {
      assert(signal_ref_list->Append(signal) == DS_OK);
    }
  }

  return DS_OK;
}

DSResult DSInput::GetTimerSet(DSTimerRefList *timer_ref_list) const
{
  DSInputTimerSignal *input_timer;
  DSTimerRef timer;

  assert(timer_ref_list);

  for (input_timer = GetFirstInputTimerSignal(); 
       input_timer;
       input_timer = GetNextInputTimerSignal())
  {
    timer = input_timer->GetTimerRef();

    if (!timer_ref_list->IsInList(timer))
    {
      assert(timer_ref_list->Append(timer) == DS_OK);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * GetAsteriskSet(): Liefert input-Set fuer ein 'input *'
 *                        Ergebnis: DS_OK,falls Aktion erfolgreich
 *                                  war, sonst enthaelt DSResult
 *                                  das Ergebnis
 *                        Seiteneffekte: Zieldatei wird gefuellt
 ****************************************************************************/

DSResult DSInput::GetAsteriskSet(DSSignalRefList *signal_ref_list,
                                 DSTimerRefList *timer_ref_list) const
{
  DSResult result, status;
  DSProcess *process;
  DSSignalItemList *valid_input_set;
  DSSignalRefList *signal_set;
  DSTimerRefList *timer_set;
  DSState *state;
  DSInput *input;
  DSSignalRef signal_ref;
  DSTimerRef timer_ref;

  assert(GetIsAsterisk());

  assert(signal_ref_list);
  assert(timer_ref_list);

  state = (DSState *)GetParent();
  assert(state);

  process = (DSProcess *)GetThisProcess();
  assert(process);

  valid_input_set = process->GetValidSignalSet();
  if (!valid_input_set)   // Prozess nur aktiv, d.h.
  {                       // er kann keine Signale
                          // empfangen?
    return DS_OK;
  }

  signal_set = new DSSignalRefList;
  assert(signal_set);
  timer_set = new DSTimerRefList;
  assert(timer_set);

  // Stimuli die in anderen Inputs vorkommen duerfen
  // nicht in 'input *' verwendet werden:
  for (input = state->GetFirstInput();
       input;
       input = state->GetNextInput())
  {
    if (input->GetIsAsterisk() || input->GetIsSpontanous() ||
        (input->GetInputSignalList() == NULL &&
         input->GetInputTimerSignalList() == NULL))
    {
      continue;
    }
    input->GetSignalSet(signal_set);
    input->GetTimerSet(timer_set);
  }

  result = valid_input_set->GetSignals(signal_ref_list);
  if (result != DS_OK) return result;
  status = signal_ref_list->MoveFirst();
  while (status == DS_OK)
  {
    signal_ref = signal_ref_list->GetCurrentData();
    assert(signal_ref);
    if (signal_set->IsInList(signal_ref))
    {
      status = signal_ref_list->DeleteElement(); // bewegt Zeiger weiter!
    }
    else
    {
      status = signal_ref_list->MoveNext();
    }
  }

  result = valid_input_set->GetTimers(timer_ref_list);
  if (result != DS_OK) return result;
  status = timer_ref_list->MoveFirst();
  while (status == DS_OK)
  {
    timer_ref = timer_ref_list->GetCurrentData();
    assert(timer_ref);
    if (timer_set->IsInList(timer_ref))
    {
      status = timer_ref_list->DeleteElement(); // bewegt Zeiger weiter!
    }
    else
    {
      status = timer_ref_list->MoveNext();
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetIsAsterisk(): Setzt das Flag
 *                  -> accepts: Boolscher Typ
 *                  Ergebnis: TRUE
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInput::SetIsAsterisk(DSBoolean asterisk)
{
  is_asterisk = asterisk;
  return DS_OK;
}

/****************************************************************************
 * SetIsSpontanous(): Setzt das Flag
 *                    -> spontanous: Boolscher Typ
 *                    Ergebnis: TRUE
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInput::SetIsSpontanous(DSBoolean spontanous)
{
  is_spontanous = spontanous;
  return DS_OK;
}

DSResult DSInput::SetPriority(DSString *new_priority)
{
  if (priority == new_priority) return DS_OK;

  if (priority) delete priority;
  priority = new_priority;

  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSInput::SetPriority(DSString &new_priority)
{
  if (priority == &new_priority) return DS_OK;

  if (priority) delete priority;
  priority = &new_priority;

  if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    priority->SetParent(this);
  }
  return DS_OK;
}

DSResult DSInput::SetPriority(const char *new_priority)
{
  if (priority) delete priority;
  priority = new DSString(this, new_priority);
  assert(priority);

  return DS_OK;
}

/****************************************************************************
 * SetInputSignalList(): Speichert den uebergebenen Zeiger
 *                       -> sig_ref: Zeiger auf eine Liste
 *                       Ergebnis: TRUE
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInput::SetInputSignalList(DSInputSignalList *list)
{
  if (signal_list == list) return DS_OK;

  if (signal_list) delete signal_list;
  signal_list = list;
  return DS_OK;
}

DSResult DSInput::InsertInputSignal(DSInputSignal* signal)
{
  assert(signal != NULL);
  if (signal_list == NULL)
  {
    signal_list = new DSInputSignalList;
    assert(signal_list != NULL);
  }
  if (signal->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    signal->SetParent(this);
  }
  return signal_list->Append(signal);
}

/****************************************************************************
 * SetInputTimerSignalList(): Speichert den uebergebenen Zeiger
 *                            -> timer_ref: Zeiger auf eine Liste
 *                            Ergebnis: TRUE
 *                            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInput::SetInputTimerSignalList(DSInputTimerSignalList *list)
{
  if (timer_list == list) return DS_OK;

  if (timer_list) delete timer_list;
  timer_list = list;
  return DS_OK;
}

DSResult DSInput::InsertInputTimerSignal(DSInputTimerSignal* timer)
{
  assert(timer != NULL);
  if (timer_list == NULL)
  {
    timer_list = new DSInputTimerSignalList;
    assert(timer_list != NULL);
  }
  if (timer->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    timer->SetParent(this);
  }
  return timer_list->Append(timer);
}

DSResult DSInput::SetEnablingCondition(DSExpression *condition)
{
  if (enabling_condition == condition) return DS_OK;

  if (enabling_condition) delete enabling_condition;
  enabling_condition = condition;

  if (enabling_condition != NULL)
  {
    if (enabling_condition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      enabling_condition->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSInput::SetHasPriority(DSBoolean has_prio)
{
  has_priority = has_prio;
  return DS_OK;
}

DSResult DSInput::SetTransition(DSTransition *trans)
{
  if (transition == trans) return DS_OK;

  if (transition) delete transition;
  transition = trans;

  if (transition != NULL)
  {
    if (transition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      transition->SetParent(this);
    }
  }

  return DS_OK;
}

DSBoolean DSInput::HasInputData(void) const
{
  if (HasInputSignalData() || HasInputTimerSignalData())
  {
    return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSInput::HasInputSignalData(void) const
{
  DSInputSignal *input_signal;

  for (input_signal = GetFirstInputSignal();
       input_signal;
       input_signal = GetNextInputSignal())
  {
    if (input_signal->GetVariableAccessList() != NULL) return DS_TRUE;
  }

  return DS_FALSE;
}

DSBoolean DSInput::HasInputTimerSignalData(void) const
{
  DSInputTimerSignal *input_timer_signal;

  for (input_timer_signal = GetFirstInputTimerSignal();
       input_timer_signal;
       input_timer_signal = GetNextInputTimerSignal())
  {
    if (input_timer_signal->GetVariableAccessList() != NULL) return DS_TRUE;
  }

  return DS_FALSE;
}

DSObject *DSInput::Clone(DSObject *father, DSObject *fill_this) const
{
  DSInput *new_input;

  if (fill_this == NULL)
  {
    new_input = (DSInput *)New(father);
    assert(new_input);
  }
  else
  {
    assert(fill_this->GetType() == DS_INPUT);
    new_input = (DSInput *)fill_this;
  }

  new_input->SetHasPriority(GetHasPriority());
  new_input->SetIsAsterisk(GetIsAsterisk());
  new_input->SetIsSpontanous(GetIsSpontanous());

  if (GetInputSignalList())
  {
    new_input->SetInputSignalList(GetInputSignalList()->Clone((DSObject *)new_input));
  }

  if (GetInputTimerSignalList())
  {
    new_input->SetInputTimerSignalList(GetInputTimerSignalList()->Clone((DSObject *)new_input));
  }

  if (GetEnablingCondition())
  {
    new_input->SetEnablingCondition((DSExpression *)GetEnablingCondition()->Clone((DSObject *)new_input));
  }

  if (GetTransition())
  {
    new_input->SetTransition((DSTransition *)GetTransition()->Clone((DSObject *)new_input));
  }

/*  if (GetProbability())
  {
    new_input->SetProbability((DSExpression *)GetProbability()->Clone((DSObject *)new_input));
  }
*/
  if (GetPriority())
  {
    new_input->SetPriority((DSString *)GetPriority()->Clone((DSObject *)new_input));
  }

  return new_input;
}

DSResult DSInput::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_INPUTSIGNAL);
  Run(writer, DS_INPUTTIMERSIGNAL);
  if (enabling_condition) enabling_condition->Write(writer, what);

  return DS_OK;
}

DSResult DSInput::Run(DSWriter *writer, DSType object_type,
                      DSCardinal what) const
{
  DSResult              result;
  DSInputSignalRef      input_signal;
  DSInputTimerSignalRef input_timer_signal;

  assert(writer);

  switch(object_type)
  {
    case DS_INPUTSIGNAL:
      for (input_signal = GetFirstInputSignal();
           input_signal;
           input_signal = GetNextInputSignal())
      {
        result = input_signal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_INPUTTIMERSIGNAL:
      for (input_timer_signal = GetFirstInputTimerSignal();
           input_timer_signal;
           input_timer_signal = GetNextInputTimerSignal())
      {
        result = input_timer_signal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      std::cerr << "Illegal Run on input!" << std::endl;
      assert(DS_FALSE);
      break;
  }
  return DS_OK;
}
