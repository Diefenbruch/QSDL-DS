/****************************************************************************
 *                 Modul: $RCSfile: DSTransition.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von allen Angaben, die in Verbindung mit einer TRANSITION-
 *          Anweisung abgespeichert werden muessen
 *
 * Funktionen: GetInputSignalList(): Gibt einen Zeiger Signalliste zurueck
 *             GetInputTimerSignalList(): Liefert Zeiger auf Liste zurueck
 *             GetActions(): Liefert Zeiger auf Instruktionsbaum
 *             SetInputSignalList(): Speichert Signalliste
 *             SetInputTimerSignalList(): Speichert die Timerliste
 *             SetActionsList(): Speichert Baumzeiger
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

#include "DSTransition.h"
#include "DSProcess.h"  // wegen parent
#include "DSProcedure.h"  // wegen parent
#include "DSInput.h"  // wegen parent
#include "DSDecision.h"  // wegen parent
#include "DSNextState.h"
#include "DSOperandExpression.h"
#include "DSOutput.h"
#include "DSCall.h"
#include "DSRange.h"
#include "DSState.h"
#include "DSExpression.h"

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

DSTransition::DSTransition(DSObject     *father,
                           DSActionList *a_list) :
  DSObject(DS_TRANSITION, father),
  action_list(a_list)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_INPUT:
        ((DSInput*)father)->SetTransition(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->SetStartTransition(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->SetStartTransition(this);
        break;
      case DS_ACTION:
        ((DSDecision*)father)->InsertTransition(this);
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

DSTransition::~DSTransition(void)
{
  if (action_list) delete action_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSTransition::New(DSObject *father) const
{
  return new DSTransition(father);
}

/****************************************************************************
 * GetActionList(): Liefert Zeiger auf die Datenstruktur des
 *                  Instruktionsliste zurueck
 *                  Ergebnis: Zeiger auf Kopf einer Liste
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSActionList *DSTransition::GetActionList(void) const
{
  return action_list;
}

DSAction *DSTransition::GetFirstAction(void) const
{
  if (action_list == NULL)
  {
    return NULL;
  }

  if (action_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return action_list->GetCurrentData();
}

DSAction *DSTransition::GetNextAction(void) const
{
  if (action_list == NULL)
  {
    return NULL;
  }

  if (action_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return action_list->GetCurrentData();
}

/****************************************************************************
 * SetActionList(): Speichert den uebergebenen Zeiger
 *                    -> act_list: Zeiger auf einen Baumstrukturkopf
 *                    Ergebnis: TRUE
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSTransition::SetActionList(DSActionList *act_list)
{
  if (action_list == act_list) return DS_OK;

  if (action_list) delete action_list;
  action_list = act_list;
  return DS_OK;
}

DSResult DSTransition::InsertAction(DSAction* action)
{
  assert(action != NULL);

  if (action_list == NULL)
  {
    action_list = new DSActionList;
    assert(action_list != NULL);
  }
  if (action->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    action->SetParent(this);
  }

  return action_list->Append(action);
}

/*
DSBoolean DSTransition::HasOutputs(void) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_OUTPUT) return DS_TRUE;
    // Bei Decision rekursiv weitersuchen...
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;
      for (trans = decision->GetFirstTransition();
           trans;
           trans = decision->GetNextTransition())
      {
        if (trans->HasOutputs()) return DS_TRUE;
      }
      trans = decision->GetElseTransition();
      if (trans)
      {
        if (trans->HasOutputs()) return DS_TRUE;
      }
    }
  }
  return DS_FALSE;
}

DSBoolean DSTransition::HasCalls(void) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_CALL) return DS_TRUE;
    // Bei Decision rekursiv weitersuchen...
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;
      for (trans = decision->GetFirstTransition();
           trans;
           trans = decision->GetNextTransition())
      {
        if (trans->HasCalls()) return DS_TRUE;
      }
      trans = decision->GetElseTransition();
      if (trans)
      {
        if (trans->HasCalls()) return DS_TRUE;
      }
    }
  }
  return DS_FALSE;
}
*/

DSBoolean DSTransition::HasDelayedOutputs(void) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_OUTPUT)
    {
      if (((DSOutput *)action)->GetDelay() != NULL) return DS_TRUE;
    }
    // Bei Decision rekursiv weitersuchen...
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;
      for (trans = decision->GetFirstTransition();
           trans;
           trans = decision->GetNextTransition())
      {
        if (trans->HasDelayedOutputs()) return DS_TRUE;
      }
      trans = decision->GetElseTransition();
      if (trans)
      {
        if (trans->HasDelayedOutputs()) return DS_TRUE;
      }
    }
  }
  return DS_FALSE;
}

/*
DSBoolean DSTransition::HasRequests(void) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_REQUEST) return DS_TRUE;
    // Bei Decision rekursiv weitersuchen...
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;
      for (trans = decision->GetFirstTransition();
           trans;
           trans = decision->GetNextTransition())
      {
        if (trans->HasRequests()) return DS_TRUE;
      }
      trans = decision->GetElseTransition();
      if (trans)
      {
        if (trans->HasRequests()) return DS_TRUE;
      }
    }
	}
  return DS_FALSE;
}
*/

DSBoolean DSTransition::HasAction(DSActionTag action_type) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;
  DSCall     *call;
  
  if (GetActionList())
  {
    GetActionList()->StorePosition();
    
    for (action = GetFirstAction();
         action;
         action = GetNextAction())
    {
      if (action->GetTag() == action_type)
      {
        switch (action_type)
        {
          case DS_CALL:
            call = (DSCall *)action;
            assert(call->GetProcedureRef());
            
            if (call->GetProcedureRef()->GetIsComplex())
            {
              GetActionList()->RestorePosition();
              return DS_TRUE;
            }
            break;
            
          default:
            GetActionList()->RestorePosition();
            return DS_TRUE;
            
        }
      }

      // Bei Decision rekursiv weitersuchen...
      if (action->GetTag() == DS_DECISION)
      {
        decision = (DSDecision *)action;
        
        if (decision->GetTransitionList())
        {
          decision->GetTransitionList()->StorePosition();
          
          for (trans = decision->GetFirstTransition();
               trans;
               trans = decision->GetNextTransition())
          {
            if (trans->HasAction(action_type))
            {
              decision->GetTransitionList()->RestorePosition();
              GetActionList()->RestorePosition();
              
              return DS_TRUE;
            }
          }
          decision->GetTransitionList()->RestorePosition();
        }
        trans = decision->GetElseTransition();
        if (trans)
        {
          if (trans->HasAction(action_type))
          {
            return DS_TRUE;
          }
        }
      }
    }
    GetActionList()->RestorePosition();
  }
  return DS_FALSE;
}


DSCardinal DSTransition::NumOfActions(DSActionTag action_type) const
{
  DSAction *action;
  DSTransition *trans;
  DSDecision *decision;
  DSCardinal num_of_actions = 0;

  if (GetActionList())
  {
    GetActionList()->StorePosition();
    
    for (action = GetFirstAction();
         action;
         action = GetNextAction())
    {
      if (action->GetTag() == action_type)
      {
        switch (action_type)
        {
          case DS_CALL: // dirty hack: nur Aufrufe von
                        // komplexen Prozeduren zaehlen:
            if (((DSCall *)action)->GetProcedureRef()->GetIsComplex())
            {
              num_of_actions++;
            }
            break;

          default:
            num_of_actions++;
            break;
        }
      }
      
      // Bei Decision rekursiv weitersuchen...
      if (action->GetTag() == DS_DECISION)
      {
        decision = (DSDecision *)action;
        
        if (decision->GetTransitionList())
        {
          decision->GetTransitionList()->StorePosition();
          
          for (trans = decision->GetFirstTransition();
               trans;
               trans = decision->GetNextTransition())
          {
            num_of_actions += trans->NumOfActions(action_type);
          }
          decision->GetTransitionList()->RestorePosition();
        }
        trans = decision->GetElseTransition();
        if (trans)
        {
          num_of_actions += trans->NumOfActions(action_type);
        }
      }
    }
    GetActionList()->RestorePosition();
	}
	
  return num_of_actions;
}


DSDecision *DSTransition::FindDecision(DSBoolean all) const
{
  DSAction   *action;
  DSDecision *decision;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;

      if (all ||
          decision->GetQuestion() == NULL) // decision any ?
      {
        return decision;
      }
    }
  }
  return NULL;
}

DSResult DSTransition::BuildSpontaneousInput(DSState *state1,
                                             DSState *state2,
                                             DSTransition *transition)
{
  DSInput *input;
  DSNextState *nextstate;

  input = new DSInput(state1,   // parent
                      DS_FALSE, // no priority
                      DS_FALSE, // no asterisk input
                      DS_TRUE); // spontaneous input!
  assert(input);
  input->SetTransition(transition);
  transition->SetParent(input);

  nextstate = new DSNextState(transition, (DSString *)NULL, state2);
  assert(nextstate);

  return DS_OK;
}

DSResult DSTransition::BuildContinuousSignal(DSState *state1,
                                             DSState *state2,
                                             DSTransition *transition,
                                             DSExpression *question,
                                             DSRange *answer)
{
  DSInput *input;
  DSExpression *expression1, *expression2, *expression3;
  DSOperandExpression *operand1, *operand2, *operand3;
  DSNextState *nextstate;
  
  input = new DSInput(state1,   // parent
                      DS_FALSE, // no priority
                      DS_FALSE, // no asterisk input
                      DS_FALSE); // no spontaneous input
  assert(input);
  input->SetTransition(transition);
  transition->SetParent(input);

  // Zwei Operanden existieren auf jeden Fall:
   
  operand1 = new DSOperandExpression(NULL, question);
  assert(operand1);
  
  assert(answer->GetUpperBound());
  operand2 = new DSOperandExpression(NULL, answer->GetUpperBound());
  assert(operand2);
  
  switch (answer->GetRangeOperator())
  {
    case DS_RANGE_OPT_NONE:
      if (answer->GetLowerBound()) // Intervall ? (dann 3 Operanden!)
      {
        operand3 = new DSOperandExpression(NULL, answer->GetLowerBound());
        assert(operand3);
        
        // operand1: Question
        // operand2: Answer (Kein Intervall oder obere Intervallgrenze)
        // operand3: Answer (untere Intervallgrenze)
        // Falls Intervall: operand3 <= operand1 <= operand2
        
        // Teilbedingungen bilden:
        expression1 = new DSExpression(NULL, operand1, DS_OPT_GREATER_EQUAL, operand3);
        assert(expression1);
        expression2 = new DSExpression(NULL, operand1, DS_OPT_LESS_EQUAL, operand2);
        assert(expression2);
        
        // Teilbedingungen zu Operanden machen:
        operand1 = new DSOperandExpression(NULL, expression1);
        assert(operand1);
        operand2 = new DSOperandExpression(NULL, expression2);
        assert(operand2);
       
        // Teilbedingungen mit AND verknuepfen:
        expression3 = new DSExpression(input, operand1, DS_OPT_AND, operand2);
        assert(expression3);
      }
      else
      {
        expression1 = new DSExpression(input, operand1, DS_OPT_EQUAL, operand2);
      }
      break;
    case DS_RANGE_OPT_EQUAL:
      expression1 = new DSExpression(input, operand1, DS_OPT_EQUAL, operand2);
      break;
    case DS_RANGE_OPT_NOT_EQUAL:
      expression1 = new DSExpression(input, operand1, DS_OPT_NOT_EQUAL, operand2);
      break;
    case DS_RANGE_OPT_GREATER:
      expression1 = new DSExpression(input, operand1, DS_OPT_GREATER, operand2);
      break;
    case DS_RANGE_OPT_GREATER_EQUAL:
      expression1 = new DSExpression(input, operand1, DS_OPT_GREATER_EQUAL, operand2);
      break;
    case DS_RANGE_OPT_LESS:
      expression1 = new DSExpression(input, operand1, DS_OPT_LESS, operand2);
      break;
    case DS_RANGE_OPT_LESS_EQUAL:
      expression1 = new DSExpression(input, operand1, DS_OPT_LESS_EQUAL, operand2);
      break;
   default:
      assert(DS_FALSE);
      return DS_ERROR;
  } // switch Range-Operator

  nextstate = new DSNextState(transition, (DSString *)NULL, state2);
  assert(nextstate);

  return DS_OK;
}

DSResult DSTransition::DissolveNextStateDash(void)
{
  DSAction     *action;
  DSTransition *trans;
  DSDecision   *decision;
  DSNextState  *nextstate;
  DSStateRef    state;

  for (action = GetFirstAction();
       action;
       action = GetNextAction())
  {
    if (action->GetTag() == DS_NEXTSTATE)
    {
      nextstate = (DSNextState *)action;

      if (nextstate->GetNextStateRef() == NULL) // 'Nextstate -' ?
      {
        state = GetThisState();
        assert (state);

        nextstate->SetNextStateRef(state);
      }
    }

    // Bei Decision rekursiv weitersuchen...
    if (action->GetTag() == DS_DECISION)
    {
      decision = (DSDecision *)action;
      for (trans = decision->GetFirstTransition();
           trans;
           trans = decision->GetNextTransition())
      {
        trans->DissolveNextStateDash();
      }
      trans = decision->GetElseTransition();
      if (trans)
      {
        trans->DissolveNextStateDash();
      }
    }
	}
  return DS_OK;
}

DSResult DSTransition::DissolveDecision(DSDecision *decision,
                                        DSObject   *father,
                                        DSString   *state_name,
                                        DSCardinal &counter)
{
  (void)decision;
  (void)father;
  (void)state_name;
  (void)counter;
  
  return DS_OK;  // see codegenerator, this method is virtual!
}

DSResult DSTransition::DissolveDecisions(DSCardinal &counter,
                                         DSBoolean all)
{
  DSObject   *father;
  DSDecision *decision;
  DSString   *state_name = NULL;
  DSState    *state;

  // 1. Zustandsliste feststellen:
  
  father = GetParent();
  assert(father);

  if (father->GetType() == DS_INPUT)
  {
    father = father->GetParent();
    assert(father);
    assert(father->GetType() == DS_STATE);

    state = (DSState *)father;
    if (state->GetIsAsterisk()) // die sollten schon aufgeloest sein !
    {
      return DS_ERROR;
    }

    state_name = state->GetFirstName();
    assert(state_name);

    father = father->GetParent();
    assert(father);
  }

  assert(father->GetType() == DS_PROCESS ||
         father->GetType() == DS_PROCEDURE);
 
  decision = FindDecision(all);
  
  if (decision != NULL)
  {
    DissolveDecision(decision, father, state_name, counter);
    delete decision;
  }
  
  return DS_OK;
}

DSObject *DSTransition::Clone(DSObject *father, DSObject *fill_this) const
{
  DSTransition *new_transition;

  if (fill_this == NULL)
  {
    new_transition = (DSTransition *)New(father);
    assert(new_transition);
  }
  else
  {
    assert(fill_this->GetType() == DS_TRANSITION);
    new_transition = (DSTransition *)fill_this;
  }

  if (GetActionList())
  {
    new_transition->SetActionList(GetActionList()->Clone((DSObject *)new_transition));
  }

  return new_transition;
}

DSResult DSTransition::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_ACTION, what);

  return DS_OK;
}

DSResult DSTransition::Run(DSWriter *writer, DSType object_type,
                           DSCardinal what) const
{
  DSAction *action;
  DSResult  result;

  switch(object_type)
  {
    case DS_ACTION:
      for (action = GetFirstAction();
           action;
           action = GetNextAction())
      {
        result = action->Write(writer, what);
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
