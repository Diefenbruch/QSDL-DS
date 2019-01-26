/****************************************************************************
 *                 Modul: $RCSfile: DSExpression.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          einer SDL-Expression
 *
 * Funktionen: GetOperand1() liefert den 1. Operanden
 *             GetOperand2() liefert den 2. Operanden
 *             GetOperator() liefert den Operator
 *             SetOperand1() setzt den 1. Operanden
 *             SetOperand2() setzt den 2. Operanden
 *             SetOperator() setzt den Operator
 *             Save()        speichert eine SDL-Expression
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

#include "DSExpression.h"
#include "DSInput.h" // wegen parent
#include "DSVariable.h" // wegen parent
#include "DSAction.h" // wegen parent
#include "DSCall.h" // wegen parent
#include "DSCreate.h" // wegen parent
#include "DSDecision.h" // wegen parent
#include "DSReset.h" // wegen parent
#include "DSTask.h" // wegen parent
#include "DSVariableAccessIndex.h"
#include "DSOperandExpression.h"
#include "DSOperandOperator.h"
#include "DSOperandConstant.h"
#include "DSOutput.h"
#include "DSRequest.h"
#include "DSUpdate.h"
#include "DSSensor.h"
#include "DSAssert.h"
#include "DSRange.h"
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

DSExpression::DSExpression(DSObject  *father,
                           DSOperand *new_operand1,
                           DSExpressionOperator new_operator,
                           DSOperand *new_operand2,
                           DSSortRef  s_ref) :
  DSObject(DS_EXPRESSION, father),
  operand1(new_operand1),
  op(new_operator),
  operand2(new_operand2),
  sort_ref(s_ref)
{
  if (operand1 && operand2)
  {
    assert(new_operator != DS_OPT_NONE);
    assert(operand1 != operand2);
  }

  if (father)
  {
    switch(father->GetType())
    {
      case DS_INPUT:
        ((DSInput*)father)->SetEnablingCondition(this);
        break;
      case DS_VARIABLE:
        ((DSVariable*)father)->SetInit(this);
        break;
      case DS_SENSOR:
        ((DSSensor*)father)->SetInterval(this);
        break;
      case DS_VARIABLEACCESSELEM:
        switch(((DSVariableAccessElem *)father)->GetTag())
        {
          case DS_ACCESS_INDEX:
            ((DSVariableAccessIndex *)father)->SetIndex(this);
            break;
          case DS_ACCESS_FIELD:
            std::cerr << "Illegal parent for expression (variable access field).\n";
            assert(DS_FALSE);
            break;
          default:
            std::cerr << "Illegal parent for expression (unknown variable access).\n";
            assert(DS_FALSE);
            break;
        }
        break;
      case DS_OPERAND:
        switch(((DSOperand *)father)->GetTag())
        {
          case DS_OPN_EXPRESSION:
            ((DSOperandExpression*)father)->SetExpression(this);
            break;
          case DS_OPN_OPERATOR:
            ((DSOperandOperator*)father)->InsertActualParam((DSActualParam*)this);
            break;
          default:
            std::cerr << "Illegal parent for expression (illegal operand).\n";
            assert(DS_FALSE);
            break;
        }
        break;

      case DS_RANGE:
        if (((DSRange *)father)->GetUpperBound() == NULL)   // Reihenfolge wichtig (siehe DSRange.h)
          ((DSRange *)father)->SetUpperBound(this);
        else if (((DSRange *)father)->GetLowerBound() == NULL)
          ((DSRange *)father)->SetLowerBound(this);
        break;

      case DS_ACTION:
        switch(((DSAction*)father)->GetTag())
        {
          case DS_ASSERT:
            ((DSAssert*)father)->SetExpression(this);
            break;
          case DS_CALL:
            ((DSCall*)father)->InsertActualParam((DSActualParam*)this);
            break;
          case DS_DECISION:
            ((DSDecision*)father)->SetQuestion(this);
            break;
          case DS_NEXTSTATE:
            std::cerr << "Illegal parent for expression (nextstate).\n";
            assert(DS_FALSE);
            break;
          case DS_OUTPUT:
            if (((DSOutput *)father)->GetProcessID() == NULL)
            {
              ((DSOutput *)father)->SetProcessID(this);
              break;
            }
            ((DSOutput *)father)->SetDelay(this);
            break;
          case DS_SET:
            break;
          case DS_RESET:
            ((DSReset*)father)->InsertActualParam(this);
            break;
          case DS_TASK:
            ((DSTask*)father)->SetExpression(this);
            break;
          case DS_CREATE:
            ((DSCreate*)father)->InsertActualParam((DSActualParam*)this);
            break;
          case DS_RETURN:
            std::cerr << "Illegal parent for expression (return).\n";
            assert(DS_FALSE);
            break;
          case DS_STOP:
            std::cerr << "Illegal parent for expression (stop).\n";
            assert(DS_FALSE);
            break;
          case DS_JOIN:
            std::cerr << "Illegal parent for expression (join).\n";
            assert(DS_FALSE);
            break;
          case DS_REQUEST:
            if (((DSRequest *)father)->GetMachineServiceAmount() == NULL)
            {
              ((DSRequest *)father)->SetMachineServiceAmount(this);
              break;
            }
            ((DSRequest *)father)->SetPriority(this);
            break;
          case DS_UPDATE:
            ((DSUpdate*)father)->SetSample(this);
            break;
          default:
            break;
        }
        break;

      default:
        std::cerr << "Illegal parent for expression.\n";
        assert(DS_FALSE);
        break;
    }
  }
  if (operand1)
  {
    if (operand1->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      operand1->SetParent(this);
    }
  }
  if (operand2)
  {
    if (operand2->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      operand2->SetParent(this);
    }
  }
}

DSExpression::DSExpression(DSExpression &orig) :
  DSObject(DS_EXPRESSION)
{
  operand1 = NULL;
  operand2 = NULL;
  sort_ref = NULL;

  orig.Clone(NULL, this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSExpression::~DSExpression(void)
{
  if (operand1) delete operand1;
  if (operand2) delete operand2;
}

DSObject *DSExpression::New(DSObject *father) const
{
  return new DSExpression(father);
}

/****************************************************************************
 * GetOperand1(): liefert Zeiger auf den 1. Operanden
 *                Ergebnis: Zeiger auf DSOperand
 *                Seiteneffekte: keine
 ****************************************************************************/

DSOperand* DSExpression::GetOperand1(void) const
{
  return operand1;
}

/****************************************************************************
 * GetOperand2(): liefert Zeiger auf den 2. Operanden
 *                Ergebnis: Zeiger auf DSOperand
 *                Seiteneffekte: keine
 ****************************************************************************/

DSOperand* DSExpression::GetOperand2(void) const
{
  return operand2;
}

/****************************************************************************
 * GetOperator(): liefert den Operatoren 
 *                Ergebnis: DSOperator Operator (siehe DSBasicTypes.h)
 *                Seiteneffekte: keine
 ****************************************************************************/

DSExpressionOperator DSExpression::GetOperator(void) const
{
  return op;
}

/****************************************************************************
 * GetSortRef(): liefert den Typ (Interger, Bollean, etc.) des Ausdrucks.
 *               Ergebnis: Typ (DSSortRef)
 *               Seiteneffekte: keine
 ****************************************************************************/

DSSortRef DSExpression::GetSortRef(void) const
{
  return sort_ref;
}

DSBoolean DSExpression::IsConstant(void) const
{
  if (operand2 != NULL ||
      operand1->GetTag() != DS_OPN_CONSTANT) return DS_FALSE;
  return DS_TRUE;
}

DSBoolean DSExpression::IsZero(void) const
{
  DSOperandConstant *opn_const;
  
  if (!IsConstant())
    return DS_FALSE;
    
  opn_const = (DSOperandConstant *)operand1;
  assert(opn_const);
  
  if (!opn_const->GetIsNumeric())
    return DS_FALSE;
    
  if (*opn_const->GetConstant() == "0" ||
      *opn_const->GetConstant() == "0.0")
    return DS_TRUE;
    
  return DS_FALSE;
}

/****************************************************************************
 * SetOperand1(): setzt Zeiger auf den 1. Operanden
 *                Ergebnis: DS_OK = alles OK
 *                          DS_ERROR = Fehler aufgetreten
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSExpression::SetOperand1(DSOperand* op1)
{
  if (operand1 == op1) return DS_OK;

  if (operand1) delete operand1;

  operand1 = op1;

  if (operand1 != NULL)
  {
    if (operand1->GetParent() == NULL)
    {
      operand1->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetOperand2(): setzt Zeiger auf den 2. Operanden
 *                Ergebnis: DS_OK = alles OK
 *                          DS_ERROR = Fehler aufgetreten
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSExpression::SetOperand2(DSOperand* op2)
{
  if (operand2 == op2) return DS_OK;

  if (operand2) delete operand2;

  operand2 = op2;

  if (operand2 != NULL)
  {
    if (operand2->GetParent() == NULL)
    {
      operand2->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetOperator(): setzt den Operatortyp
 *                Ergebnis: DS_OK = alles OK
 *                          DS_ERROR = Fehler aufgetreten
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSExpression::SetOperator(DSExpressionOperator oprtr)
{
  op = oprtr;
  return DS_OK;
}

/****************************************************************************
 * SetSortRef(): setzt Zeiger auf den Typ des Ausdrucks
 *               Ergebnis: DS_OK = alles OK
 *                         DS_FALSE = Fehler aufgetreten
 *               Seiteneffekte: keine
 ****************************************************************************/

DSResult DSExpression::SetSortRef(DSSortRef s_ref)
{
  sort_ref = s_ref;
  return DS_OK;
}

DSObject *DSExpression::Clone(DSObject *father, DSObject *fill_this) const
{
  DSExpression *new_expression;

  if (fill_this == NULL)
  {
    new_expression = (DSExpression *)New(father); // virtueller Konstruktor
    assert(new_expression);
  }
  else
  {
    assert(fill_this->GetType() == DS_EXPRESSION);
    new_expression = (DSExpression *)fill_this;
  }

  if (GetOperand1())
  {
    new_expression->SetOperand1((DSOperand *)GetOperand1()->Clone((DSObject *)new_expression));
  }

  if (GetOperand2())
  {
    new_expression->SetOperand2((DSOperand *)GetOperand2()->Clone((DSObject *)new_expression));
  }

  new_expression->SetOperator(GetOperator());
  new_expression->SetSortRef(GetSortRef());

  return new_expression;
}

DSResult DSExpression::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (operand1) operand1->Write(writer, what);
  if (operand2) operand2->Write(writer, what);

  return DS_OK;
}
