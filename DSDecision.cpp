/****************************************************************************
 *                 Modul: $RCSfile: DSDecision.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter des SDL-Decision-Konstruktes
 *
 * Funktionen: GetDecisionRef(): Gibt eine Referenz auf den entsprechenden
 *                                Folgezustand zurueck
 *             SetDecisionRef(): Speichert den uebergebenen Folgezustand
 *             Save(): Abspeichern in eine Datei
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
 
#include "DSDecision.h"
#include "DSExpression.h"
#include "DSTransition.h"
#include "DSRange.h"

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

DSDecision::DSDecision(DSObject *father,
                       DSString *label_name,
                       DSExpression *quest,
                       DSRangeList *answers,
                       DSTransitionList *transitions,
                       DSTransition *else_t) :
  DSAction(father, DS_DECISION, label_name),
  question(quest),
  answer_list(answers),
  transition_list(transitions),
  else_transition(else_t)
{
}

DSDecision::DSDecision(DSObject *father,
                       DSString &label_name,
                       DSExpression *quest,
                       DSRangeList *answers,
                       DSTransitionList *transitions,
                       DSTransition *else_t) :
  DSAction(father, DS_DECISION, &label_name),
  question(quest),
  answer_list(answers),
  transition_list(transitions),
  else_transition(else_t)
{
}

DSDecision::DSDecision(DSObject *father,
                       const char *label_name,
                       DSExpression *quest,
                       DSRangeList *answers,
                       DSTransitionList *transitions,
                       DSTransition *else_t) :
  DSAction(father, DS_DECISION, label_name),
  question(quest),
  answer_list(answers),
  transition_list(transitions),
  else_transition(else_t)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSDecision::~DSDecision(void)
{
  if (question) delete question;
  if (transition_list) delete transition_list;
  if (answer_list) delete answer_list;
  if (else_transition) delete else_transition;
}

DSExpression* DSDecision::GetQuestion(void) const
{
  return question;
}

DSRangeList *DSDecision::GetAnswerList(void) const
{
  return answer_list;
}

DSRange *DSDecision::GetFirstAnswer(void) const
{
  if (answer_list == NULL)
  {
    return NULL;
	}

  if (answer_list->MoveFirst() != DS_OK)
  {
    return NULL;
	}
  return answer_list->GetCurrentData();
}

DSRange *DSDecision::GetNextAnswer(void) const
{
  if (answer_list == NULL)
  {
    return NULL;
	}

  if (answer_list->MoveNext() != DS_OK)
  {
    return NULL;
	}
  return answer_list->GetCurrentData();
}

DSTransitionList *DSDecision::GetTransitionList(void) const
{
  return transition_list;
}

DSTransition *DSDecision::GetFirstTransition(void) const
{
  if (transition_list == NULL)
  {
    return NULL;
	}

  if (transition_list->MoveFirst() != DS_OK)
  {
    return NULL;
	}
  return transition_list->GetCurrentData();
}

DSTransition *DSDecision::GetNextTransition(void) const
{
  if (transition_list == NULL)
  {
    return NULL;
	}

  if (transition_list->MoveNext() != DS_OK)
  {
    return NULL;
	}
  return transition_list->GetCurrentData();
}

DSTransition *DSDecision::GetElseTransition(void) const
{
  return else_transition;
}

DSResult DSDecision::SetQuestion(DSExpression *quest)
{
  if (question == quest) return DS_OK;

  if (question) delete question;
  question = quest;

  if (question != NULL)
  {
    if (question->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      question->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSDecision::SetTransitionList(DSTransitionList* list)
{
  if (transition_list == list) return DS_OK;

  if (transition_list) delete transition_list;
  transition_list = list;

  return DS_OK;
}

DSResult DSDecision::InsertTransition(DSTransition *transition)
{
  assert(transition != NULL);

  if (transition_list == NULL)
  {
    transition_list = new DSTransitionList;
    assert(transition_list != NULL);
  }

  if (transition->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    transition->SetParent(this);
  }

  return transition_list->Append(transition);
}

DSResult DSDecision::SetAnswerList(DSRangeList* list)
{
  if (answer_list == list) return DS_OK;

  if (answer_list) delete answer_list;
  answer_list = list;

  return DS_OK;
}

DSResult DSDecision::InsertAnswer(DSRange *answer)
{
  assert(answer != NULL);

  if (answer_list == NULL)
  {
    answer_list = new DSRangeList;
    assert(answer_list != NULL);
  }
  if (answer->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    answer->SetParent(this);
  }
  return answer_list->Append(answer);
}

DSResult DSDecision::SetElseTransition(DSTransition* transition)
{
  if (else_transition == transition) return DS_OK;

//  if (else_transition) delete else_transition;
  else_transition = transition;

  if (transition != NULL)
  {
    if (transition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      transition->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSDecision::Clone(DSObject *father, DSObject *fill_this) const
{
  DSDecision *new_decision;

  if (fill_this == NULL)
  {
    new_decision = (DSDecision *)New(father); // virtueller Konstruktor
    assert(new_decision);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_decision = (DSDecision *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_decision);

  if (GetQuestion())
  {
    new_decision->SetQuestion((DSExpression *)GetQuestion()->Clone((DSObject *)new_decision));
  }

  if (GetAnswerList())
  {
    new_decision->SetAnswerList((DSRangeList *)GetAnswerList()->Clone((DSObject *)new_decision));
  }

  if (GetTransitionList())
  {
    new_decision->SetTransitionList(GetTransitionList()->Clone((DSObject *)new_decision));
  }

  if (GetElseTransition())
  {
    new_decision->SetElseTransition((DSTransition *)GetElseTransition()->Clone((DSObject *)new_decision));
  }

  return new_decision;
}

DSResult DSDecision::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (question) question->Write(writer, what);
  Run(writer, DS_RANGE, what);
  Run(writer, DS_TRANSITION, what);
  if (else_transition) else_transition->Write(writer, what);

  return DS_OK;
}

DSResult DSDecision::Run(DSWriter *writer, DSType object_type,
                         DSCardinal what) const
{
  DSResult        result;
  DSRangeRef      range;
  DSTransitionRef transition;

  switch(object_type)
  {
    case DS_RANGE:
      for (range = GetFirstAnswer();
           range;
           range = GetNextAnswer())
      {
        result = range->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_TRANSITION:
      for (transition = GetFirstTransition();
           transition;
           transition = GetNextTransition())
      {
        result = transition->Write(writer, what);
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
