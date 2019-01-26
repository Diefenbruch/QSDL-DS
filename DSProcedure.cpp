/****************************************************************************
 *                 Modul: $RCSfile: DSProcedure.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 06:07:11 $
 * $Revision: 1.4 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer eine SDL-Prozedur bereit.
 *
 * Funktionen: GetReturnParamRef()       Name + Datentyp des Procedur-Ergebnisses
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
 
#include "DSProcedure.h"
#include "DSProcess.h" // wegen parent
#include "DSBlock.h" // wegen parent
#include "DSBlockSubstructure.h" // wegen parent
#include "DSSystem.h" // wegen parent
#include "DSTransition.h"
#include "DSState.h"
#include "DSVariable.h"
#include "DSSort.h"
#include "DSString.h" // MS VC++ needs this !?

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

DSProcedure::DSProcedure(DSObject *father,
                         DSString *n) :
  DSNamedObject(DS_PROCEDURE, n, father)
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent(this) */
{
  return_param_ref = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertProcedure(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertProcedure(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcedure(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertProcedure(this);
        break;
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertProcedure(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSProcedure::DSProcedure(DSObject *father,
                         DSString& n) :
  DSNamedObject(DS_PROCEDURE, n, father)
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent(this) */
{
  return_param_ref = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertProcedure(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertProcedure(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcedure(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertProcedure(this);
        break;
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertProcedure(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSProcedure::DSProcedure(DSObject *father,
                         const char *n) :
  DSNamedObject(DS_PROCEDURE, n, father)
/*  DSFormalParamComponent(this),
  DSSortComponent(this),
  DSProcedureComponent(this),
  DSStateComponent(this),
  DSVariableComponent(this),
  DSSensorComponent(this) */
{
  return_param_ref = NULL;

  DSFormalParamComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSStateComponent::SetComponentParent(this);
  DSVariableComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertProcedure(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertProcedure(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertProcedure(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertProcedure(this);
        break;
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertProcedure(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSProcedure::~DSProcedure(void)
{
}

DSFormalParamRef DSProcedure::GetReturnParamRef(void) const
{
  return return_param_ref;
}

DSBoolean DSProcedure::GetIsComplex(void) const
{
  return is_complex;
}

DSResult DSProcedure::SetReturnParamRef(DSFormalParamRef param_ref)
{
  return_param_ref = param_ref;

  return DS_OK;
}

DSResult DSProcedure::SetIsComplex(DSBoolean new_value)
{
  is_complex = new_value;

  return DS_OK;
}

DSBoolean DSProcedure::HasAction(DSActionTag action_type,
                                 DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  assert (GetStartTransition());

  if (GetStartTransition()->HasAction(action_type))
  {
    return DS_TRUE;
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

DSBoolean DSProcedure::HasDelayedOutputs(DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;

  assert (GetStartTransition());

  if (GetStartTransition()->HasDelayedOutputs())
  {
    return DS_TRUE;
  }

  if (GetStateList())
  {
    GetStateList()->StorePosition();
    
    for (state = GetFirstState();
         state;
         state = GetNextState())
    {
      if (state->HasDelayedOutputs())
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
      if (procedure->HasDelayedOutputs(recursive))
      {
        GetProcedureList()->RestorePosition();

        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSProcedure::HasSaves(DSBoolean recursive) const
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

DSBoolean DSProcedure::HasAsteriskStates(DSBoolean recursive) const
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

DSBoolean DSProcedure::HasInputData(DSBoolean recursive) const
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

DSBoolean DSProcedure::HasInputSignalData(DSBoolean recursive) const
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

DSBoolean DSProcedure::HasInputTimerSignalData(DSBoolean recursive) const
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

DSBoolean DSProcedure::HasComplexProcedures(DSBoolean recursive) const
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

DSCardinal DSProcedure::NumOfActions(DSActionTag action_type,
                                     DSBoolean recursive) const
{
  DSState     *state;
  DSProcedure *procedure;
  DSCardinal   num_of_actions = 0;

  assert (GetStartTransition());

  num_of_actions += GetStartTransition()->NumOfActions(action_type);

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

void DSProcedure::CheckForComplexProcedures(DSBoolean recursive)
{
  DSProcedure *procedure;
  
  if (recursive && GetProcedureList())
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

  if (GetStateList())
  {
    is_complex = DS_TRUE;
    
    return;
  }

  if (HasAction(DS_CALL, DS_TRUE) ||
      HasAction(DS_REQUEST, DS_TRUE))
  {
    is_complex = DS_TRUE;
    
    return;
  }

  is_complex = DS_FALSE;
}

DSResult DSProcedure::DissolveAsteriskStates(void)
{
  DSProcedure *procedure;
  DSResult result;

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

DSResult DSProcedure::DissolveNextStateDash(void)
{
  DSProcedure  *procedure;
  DSResult      result;
  DSState      *state;

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    result = state->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }

  // Sub-Procedures:
  for (procedure = GetFirstProcedure();
       procedure;
       procedure = GetNextProcedure())
  {
    result = procedure->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSResult DSProcedure::DissolveDecisions(DSBoolean all)
{
  DSProcedure  *procedure;
  DSResult      result;
  DSState      *state;
  DSCardinal    counter;

  assert (GetStartTransition());

  GetStartTransition()->DissolveDecisions(counter, all);

  for (state = GetFirstState();
       state;
       state = GetNextState())
  {
    result = state->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }

  // Sub-Procedures:
  for (procedure = GetFirstProcedure();
       procedure;
       procedure = GetNextProcedure())
  {
    result = procedure->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSObject *DSProcedure::Clone(DSObject *father, DSObject *fill_this) const
{
  DSProcedure *new_procedure;

  if (fill_this == NULL)
  {
    new_procedure = (DSProcedure *)New(father); // virtueller Konstruktor
    assert(new_procedure);
  }
  else
  {
    assert(fill_this->GetType() == DS_PROCEDURE);
    new_procedure = (DSProcedure *)fill_this;
  }

  // Basisklasse clonen:
  DSNamedObject::Clone(father, new_procedure);
 
  if (GetFormalParamList())
  {
    new_procedure->SetFormalParamList((DSFormalParamKeyList *)GetFormalParamList()->Clone((DSObject *)new_procedure));
  }

  if (GetSortList())
  {
    new_procedure->SetSortList((DSSortKeyList *)GetSortList()->Clone((DSObject *)new_procedure));
  }

  if (GetProcedureList())
  {
    new_procedure->SetProcedureList((DSProcedureKeyList *)GetProcedureList()->Clone((DSObject *)new_procedure));
  }

  if (GetStateList())
  {
    new_procedure->SetStateList(GetStateList()->Clone((DSObject *)new_procedure));
  }

  if (GetVariableList())
  {
    new_procedure->SetVariableList((DSVariableKeyList *)GetVariableList()->Clone((DSObject *)new_procedure));
  }

  return new_procedure;
}

DSResult DSProcedure::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSProcedure::Run(DSWriter *writer, DSType object_type,
                          DSCardinal what) const
{
  DSResult            result;
  DSFormalParamRef    formal_param;
  DSProcedureRef      procedure;
  DSSortRef           sort;
  DSVariableRef       variable;
  DSStateRef          state;

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

    default:
      assert(DS_FALSE);
      break;
  }
  return DS_OK;
}
