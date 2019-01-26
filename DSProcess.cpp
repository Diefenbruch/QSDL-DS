/****************************************************************************
 *                 Modul: $RCSfile: DSProcess.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.3 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer einen SDL-Process bereit.
 *
 * Funktionen: GetInitInstances()    liefert die Anzahl der Initialinstanzen
 *             GetMaxInstances()     liefert die max. Anzahl der Instanzen
 *             GetValidSignalSet()   liefert die Liste der gueltigen Signale
 *             SetInitInstances()    setzt die Anzahl der Initialinstanzen
 *             SetMaxInstances()     setzt die max. Anzahl der Instanzen
 *             SetValidSignalSet()   setzt die Liste der gueltigen Signale
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

#include "DSProcess.h"
#include "DSBlock.h"   // wegen parent
#include "DSSystem.h"
#include "DSProcedure.h"
#include "DSExpression.h"
#include "DSState.h"
#include "DSTransition.h"
#include "DSVariable.h"
#include "DSSignalRoute.h"
#include "DSSort.h"
#include "DSTimer.h"
#include "DSSignal.h"
#include "DSSignalslist.h"
#include "DSSensor.h"
#include "DSSynonym.h"
#include "DSOperandConstant.h"
#include "DSString.h"

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

DSProcess::DSProcess(DSObject *father,
                     DSString *n,
                     DSExpression *init,
                     DSExpression *max,
                     DSExpression *length) :
  DSNamedObject(DS_PROCESS, n, father),
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSTimerComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent (this), */
  number_of_init_instances(init),
  number_of_max_instances(max),
  queue_length(length)
{
  valid_signalset = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSTimerComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcess(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (number_of_init_instances)
  {
    if (number_of_init_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_init_instances->SetParent(this);
    }
  }
  if (number_of_max_instances)
  {
    if (number_of_max_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_max_instances->SetParent(this);
    }
  }
  if (queue_length)
  {
    if (queue_length->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      queue_length->SetParent(this);
    }
  }
}

DSProcess::DSProcess(DSObject *father,
                     DSString &n,
                     DSExpression *init,
                     DSExpression *max,
                     DSExpression *length) :
  DSNamedObject(DS_PROCESS, n, father),
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSTimerComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent (this), */
  number_of_init_instances(init),
  number_of_max_instances(max),
  queue_length(length)
{
  valid_signalset = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSTimerComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcess(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (number_of_init_instances)
  {
    if (number_of_init_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_init_instances->SetParent(this);
    }
  }
  if (number_of_max_instances)
  {
    if (number_of_max_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_max_instances->SetParent(this);
    }
  }
  if (queue_length)
  {
    if (queue_length->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      queue_length->SetParent(this);
    }
  }
}

DSProcess::DSProcess(DSObject     *father,
                     const char   *n,
                     DSExpression *init,
                     DSExpression *max,
                     DSExpression *length) :
  DSNamedObject(DS_PROCESS, n, father),
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSTimerComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent (this), */
  number_of_init_instances(init),
  number_of_max_instances(max),
  queue_length(length)
{
  valid_signalset = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSTimerComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcess(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (number_of_init_instances)
  {
    if (number_of_init_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_init_instances->SetParent(this);
    }
  }
  if (number_of_max_instances)
  {
    if (number_of_max_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_max_instances->SetParent(this);
    }
  }
  if (queue_length)
  {
    if (queue_length->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      queue_length->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSProcess::~DSProcess(void)
{
  if (number_of_init_instances) delete number_of_init_instances;
  if (number_of_max_instances) delete number_of_max_instances;
  if (queue_length) delete queue_length;
  if (valid_signalset) delete valid_signalset;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSProcess::New(DSObject *father) const
{
  return new DSProcess(father);
}

DSExpression* DSProcess::GetInitInstances(void) const
{
  return number_of_init_instances;
}

DSExpression* DSProcess::GetMaxInstances(void) const
{
  return number_of_max_instances;
}

DSExpression* DSProcess::GetQueueLength(void) const
{
  return queue_length;
}

DSSignalItemList* DSProcess::GetValidSignalSet(void)
{
  DSSystem *system;
  DSBlock *block;
  DSSignal *signal;
  DSTimer *timer;
  DSSignalRoute *signal_route;
  DSSignalItemList *signal_item_list;
  DSBoolean found_signal = DS_FALSE;

  // Wenn Valid-Input-Set direkt spezifiziert ist
  // dann direkt zurueckgeben:
  if (valid_signalset != NULL)
  {
    return valid_signalset;
  }

  // Nun wird das Valid-Input-Set berechnet:

  valid_signalset = new DSSignalItemList(this);
  assert(valid_signalset);

  // 1. Alle Prozesssignale aufnehmen:
  for (signal = GetFirstSignal();
       signal;
       signal = GetNextSignal())
  {
    assert(valid_signalset->InsertSignalRef(signal) == DS_OK);
    found_signal = DS_TRUE;
    break;
  }

  // 2. Alle Prozesstimer aufnehmen:
  for (timer = GetFirstTimer();
       timer;
       timer = GetNextTimer())
  {
    assert(valid_signalset->InsertTimerRef(timer) == DS_OK);
    found_signal = DS_TRUE;
    break;
  }

  // 3. Alle Blocksignale auf Eignung testen:
  block = (DSBlock*)this->GetParent();
  assert(block);

  for (signal = block->GetFirstSignal();
       signal;
       signal = block->GetNextSignal())
  {
    // Nur Signale verwenden, die in mindestens
    // einer Signalroute vorkommen, mit der der
    // Prozess auch verbunden ist:
    for (signal_route =  block->GetFirstSignalRoute();
         signal_route;
         signal_route =  block->GetNextSignalRoute())
    {
      if (signal_route->GetProcess1Ref() == this)
      {
        signal_item_list = signal_route->GetSignalList21();
			}
      else if (signal_route->GetProcess2Ref() == this)
      {
        signal_item_list = signal_route->GetSignalList12();
      }
      else
      {
        signal_item_list = NULL;
      }
      if (signal_item_list)
      {
        // Testen ob Signal vorkommt:
        if (signal_item_list->GetSignalRef(signal->GetName()) != NULL)
        {
          assert(valid_signalset->InsertSignalRef(signal) == DS_OK);
          found_signal = DS_TRUE;
          break;
        }
      }
    }
  }

  // 4. Alle Systemsignale auf Eignung testen:
  system = (DSSystem*)block->GetParent();
  assert(system);
  for (signal = system->GetFirstSignal();
       signal;
       signal = system->GetNextSignal())
  {
    // Signal noch nicht im Block gewesen?
    if (valid_signalset->GetSignalRef(signal->GetName()) != NULL) 
    {
      continue;
    }
    // Nur Signale verwenden, die in mindestens
    // einer Signalroute vorkommen, mit der der
    // Prozess auch verbunden ist:
    for (signal_route =  block->GetFirstSignalRoute();
         signal_route;
         signal_route =  block->GetNextSignalRoute())
    {
      if (signal_route->GetProcess1Ref() == this)
      {
        signal_item_list = signal_route->GetSignalList21();
      }
      else if (signal_route->GetProcess2Ref() == this)
      {
        signal_item_list = signal_route->GetSignalList12();
      }
      else
      {
        signal_item_list = NULL;
      }
      if (signal_item_list)
      {
        // Testen ob Signal vorkommt:
        if (signal_item_list->GetSignalRef(signal->GetName()) != NULL)
        {
          assert(valid_signalset->InsertSignalRef(signal) == DS_OK);
          found_signal = DS_TRUE;
          break;
        }
      }
    }
  }
  // wurden Signale gefunden?
  if (found_signal)
  {
    return valid_signalset;
  }

  // Prozess kann ueberhaupt keine Signale empfangen:
  delete valid_signalset;
  valid_signalset = NULL;
  return NULL;
}

DSResult DSProcess::SetInitInstances(DSExpression *init)
{
  if (number_of_init_instances == init) return DS_OK;

  if (number_of_init_instances) delete number_of_init_instances;
  number_of_init_instances = init;

  if (number_of_init_instances != NULL)
  {
    if (number_of_init_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_init_instances->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSProcess::SetMaxInstances(DSExpression *max)
{
  if (number_of_max_instances == max) return DS_OK;

  if (number_of_max_instances) delete number_of_max_instances;
  number_of_max_instances = max;

  if (number_of_max_instances != NULL)
  {
    if (number_of_max_instances->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_max_instances->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSProcess::SetValidSignalSet(DSSignalItemList *list)
{
  if (valid_signalset == list) return DS_OK;

  if (valid_signalset != NULL)
  {
    delete valid_signalset;
  }
  valid_signalset = list;

  if (valid_signalset != NULL)
  {
    if (valid_signalset->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      valid_signalset->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSProcess::SetQueueLength(DSExpression *length)
{
  if (queue_length == length) return DS_OK;

  if (queue_length) delete queue_length;
  queue_length = length;

  if (queue_length != NULL)
  {
    if (queue_length->GetParent() == NULL) // Vater noch nicht geset!
    {
      queue_length->SetParent(this);
    }
  }
  return DS_OK;
}


DSBoolean DSProcess::HasAction(DSActionTag action_type,
                               DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  if (GetStartTransition())
  {
    if (GetStartTransition()->HasAction(action_type))
    {
      return DS_TRUE;
    }
  }

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasAction(action_type))
      {
        GetStateList()->RestorePosition();

        return DS_TRUE;
      }
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {  
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasAction(action_type, recursive))
      {
        GetProcedureList()->RestorePosition();

        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasDelayedOutputs(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  if (GetStartTransition())
  {
    if (GetStartTransition()->HasDelayedOutputs())
    {
      return DS_TRUE;
    }
  }

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasDelayedOutputs()) return DS_TRUE;
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasDelayedOutputs(recursive)) return DS_TRUE;
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}


DSBoolean DSProcess::HasSaves(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;
  
  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->GetSaveList()) return DS_TRUE;
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasSaves(recursive)) return DS_TRUE;
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasAsteriskStates(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;
  
  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->GetIsAsterisk()) return DS_TRUE;
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasAsteriskStates(recursive)) return DS_TRUE;
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasComplexProcedures(DSBoolean recursive) const
{
  DSProcedure *procedure;

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->GetIsComplex())
      {
        GetProcedureList()->RestorePosition();

        return DS_TRUE;
      }
    }

    if (recursive)
    {
      for (procedure = GetFirstProcedure();
           procedure;
           procedure = GetNextProcedure())
      {
        if (procedure->HasComplexProcedures(recursive))
        {
          GetProcedureList()->RestorePosition();

          return DS_TRUE;
        }
      }
    }    

    GetProcedureList()->RestorePosition();
  }
  
  return DS_FALSE;
}


DSBoolean DSProcess::HasExternalSynonyms(DSBoolean recursive) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSExpression *expression;
  DSOperandConstant *operand;

  (void)recursive;
    
  if (GetSortList())
  {
    GetSortList()->StorePosition();
    
    for (sort = GetFirstSort();
         sort;
         sort = GetNextSort())
    {
      if (sort->GetTag() == DS_SORT_SYNONYM)
      {
        synonym = (DSSynonym *)sort;
        
        expression = synonym->GetValue();
        assert(expression);
        
        if (expression->IsConstant())
        {
          operand = (DSOperandConstant *)expression->GetOperand1();
          assert(operand->GetConstant());
          
          if (*operand->GetConstant() == DS_NAME_EXTERNAL)
          {
            GetSortList()->RestorePosition();
            return DS_TRUE;
          }
        }
      }
    }

    GetSortList()->RestorePosition();
  }
  
  return DS_FALSE;
}


DSBoolean DSProcess::HasInputData(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasInputData())
      {
        GetStateList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasInputData(recursive))
      {
        GetProcedureList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasInputSignalData(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasInputSignalData())
      {
        GetStateList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasInputSignalData(recursive)) return DS_TRUE;
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasInputTimerSignalData(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasInputTimerSignalData()) return DS_TRUE;
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasInputTimerSignalData(recursive)) return DS_TRUE;
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcess::HasSensors(DSBoolean recursive) const
{
  (void)recursive;
  
  if (GetSensorList())
  {
    return DS_TRUE;
  }
  
  return DS_FALSE;
}

DSCardinal DSProcess::NumOfActions(DSActionTag action_type,
                                   DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;
  DSCardinal   num_of_actions = 0;

  if (GetStartTransition())
  {
    num_of_actions += GetStartTransition()->NumOfActions(action_type);
  }

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      num_of_actions += state->NumOfActions(action_type);
    }

    GetStateList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      num_of_actions += procedure->NumOfActions(action_type, recursive);
    }

    GetProcedureList()->RestorePosition();
  }
  
  return num_of_actions;
}

void DSProcess::CheckForComplexProcedures(DSBoolean recursive)
{
  DSProcedure *procedure;

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      procedure->CheckForComplexProcedures(recursive);
    }
    
    GetProcedureList()->RestorePosition();
  }
}


DSResult DSProcess::DissolveAsteriskStates(void)
{
  DSProcedure *procedure;
  DSResult     result;

  if (!HasAsteriskStates(DS_TRUE)) return DS_OK;

  result = DSStateComponent::DissolveAsteriskStates();
  if (result != DS_OK) return result;

  for (procedure = GetFirstProcedure();
       procedure;
       procedure = GetNextProcedure())
  {
    result = procedure->DissolveAsteriskStates();
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSResult DSProcess::DissolveNextStateDash(void)
{
  DSProcedure *procedure;
  DSResult     result;
  DSState     *state;

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    result = state->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }

  for (procedure = GetFirstProcedure();
       procedure;
       procedure = GetNextProcedure())
  {
    result = procedure->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSResult DSProcess::DissolveDecisions(DSBoolean all)
{
  DSProcedure  *procedure;
  DSResult      result;
  DSState      *state;
  DSCardinal    counter = 1;

  assert(GetStartTransition());

  GetStartTransition()->DissolveDecisions(counter, all);

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    result = state->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }

  for (procedure = GetFirstProcedure();
       procedure;
       procedure = GetNextProcedure())
  {
    result = procedure->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }

  return DS_OK;
}

DSResult DSProcess::GetExternalSynonyms(DSSynonymRefList *result_list) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSExpression *expression;
  DSOperandConstant *operand;
  
  assert(result_list);
      
  if (GetSortList())
  {
    GetSortList()->StorePosition();
    
    for (sort = GetFirstSort();
         sort;
         sort = GetNextSort())
    {
      if (sort->GetTag() == DS_SORT_SYNONYM)
      {
        synonym = (DSSynonym *)sort;
        
        expression = synonym->GetValue();
        assert(expression);
        
        if (expression->IsConstant())
        {
          operand = (DSOperandConstant *)expression->GetOperand1();
          assert(operand->GetConstant());
          
          if (*operand->GetConstant() == DS_NAME_EXTERNAL)
          {
            result_list->Append(synonym);
          }
        }
      }
    }

    GetSortList()->RestorePosition();
  }
  
  return DS_OK;
}

DSObject *DSProcess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSProcess *new_process;

  if (fill_this == NULL)
  {
    new_process = (DSProcess *)New(father);
    assert(new_process);
  }
  else
  {
    assert(fill_this->GetType() == DS_PROCESS);
    new_process = (DSProcess *)fill_this;
  }

  // Basisklasse clonen:
  DSNamedObject::Clone(father, new_process);
 
  if (GetFormalParamList())
  {
    new_process->SetFormalParamList((DSFormalParamKeyList *)GetFormalParamList()->Clone((DSObject *)new_process));
  }

  if (GetSortList())
  {
    new_process->SetSortList((DSSortKeyList *)GetSortList()->Clone((DSObject *)new_process));
  }

  if (GetProcedureList())
  {
    new_process->SetProcedureList((DSProcedureKeyList *)GetProcedureList()->Clone((DSObject *)new_process));
  }

  if (DSSignalComponent::GetSignalList())
  {
    new_process->SetSignalList((DSSignalKeyList *)DSSignalComponent::GetSignalList()->Clone((DSObject *)new_process));
  }

  if (GetSignallistList())
  {
    new_process->SetSignallistList((DSSignalslistKeyList *)GetSignallistList()->Clone((DSObject *)new_process));
  }

  if (GetTimerList())
  {
    new_process->SetTimerList((DSTimerKeyList *)GetTimerList()->Clone((DSObject *)new_process));
  }

  if (GetStateList())
  {
    new_process->SetStateList(GetStateList()->Clone((DSObject *)new_process));
  }

  if (GetVariableList())
  {
    new_process->SetVariableList((DSVariableKeyList *)GetVariableList()->Clone((DSObject *)new_process));
  }

  if (GetInitInstances())
  {
    new_process->SetInitInstances((DSExpression *)GetInitInstances()->Clone((DSObject *)new_process));
  }

  if (GetMaxInstances())
  {
    new_process->SetMaxInstances((DSExpression *)GetMaxInstances()->Clone((DSObject *)new_process));
  }

  if (GetQueueLength())
  {
    new_process->SetQueueLength((DSExpression *)GetQueueLength()->Clone((DSObject *)new_process));
  }

  if (GetSensorList())
  {
    new_process->SetSensorList((DSSensorKeyList *)GetSensorList()->Clone((DSObject *)new_process));
  }

  return new_process;
}

DSResult DSProcess::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSProcess::Run(DSWriter *writer, DSType object_type,
                        DSCardinal what) const
{
  DSResult            result;
  DSFormalParamRef    formal_param;
  DSProcedureRef      procedure;
  DSSortRef           sort;
  DSSignalRef         signal;
  DSSignalslistRef     signallist;
  DSTimerRef          timer;
  DSVariableRef       variable;
  DSStateRef          state;
  DSSensorRef         sensor;
  
  assert(writer);

  switch(object_type)
  {
    case DS_FORMALPARAM:
      for (formal_param = GetFirstFormalParam();
           formal_param;
           formal_param = GetNextFormalParam())
      {
        result = formal_param->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PROCEDURE:
      for (procedure = GetFirstProcedure();
           procedure;
           procedure = GetNextProcedure())
      {
        result = procedure->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SORT:
      for (sort = GetFirstSort();
           sort;
           sort = GetNextSort())
      {
        result = sort->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNAL:
      for (signal = GetFirstSignal();
           signal;
           signal = GetNextSignal())
      {
        result = signal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNALLIST:
      for (signallist = GetFirstSignallist();
           signallist;
           signallist = GetNextSignallist())
      {
        result = signallist->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_TIMER:
      for (timer = GetFirstTimer();
           timer;
           timer = GetNextTimer())
      {
        result = timer->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_VARIABLE:
      for (variable = GetFirstVariable();
           variable;
           variable = GetNextVariable())
      {
        result = variable->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_STATE:
      for (state = GetFirstState();
           state;
           state = GetNextState())
      {
        result = state->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SENSOR:
      for (sensor = GetFirstSensor();
           sensor;
           sensor = GetNextSensor())
      {
        result = sensor->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }
  return DS_OK;
}
