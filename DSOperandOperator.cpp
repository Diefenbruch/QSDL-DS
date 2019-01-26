/****************************************************************************
 *                 Modul: $RCSfile: DSOperandOperator.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Operator-
 *          Operanden
 *
 * Funktionen: GetOperatorRef() liefert einen Zeiger auf den Operator
 *             SetOperatorRef() setzt den Zeiger auf den Operator
 *             Save()          speichert einen Operator-Operanden
 ****************************************************************************/

/****************************************************************************
 * Konstanten
 ****************************************************************************/

/****************************************************************************
 * Include-Anweisungen
 ****************************************************************************/

#include "DSOperandOperator.h"
#include "DSOperator.h"
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

DSOperandOperator::DSOperandOperator(DSObject          *father,
                                     DSOperatorRef      op,
                                     DSActualParamList *param_list) :
  DSOperand(father, DS_OPN_OPERATOR),
  DSActualParamComponent(NULL, param_list),
  operator_ref(op)
{
  DSActualParamComponent::SetComponentParent(this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandOperator::~DSOperandOperator(void)
{
}

DSObject *DSOperandOperator::New(DSObject *father) const
{
  return new DSOperandOperator(father);
}

/****************************************************************************
 * GetOperatorRef(): liefert Zeiger auf den Operator
 *                   Ergebnis: Zeiger auf DSOperator
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSOperatorRef DSOperandOperator::GetOperatorRef(void) const
{
  return operator_ref;
}

/****************************************************************************
 * SetOperatorRef(): setzt Zeiger auf den Operator
 *                   ->exp: Zeiger auf DSOperator
 *                   Ergebnis: DS_OK
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandOperator::SetOperatorRef(DSOperatorRef op)
{
  operator_ref = op;
  return DS_OK;
}

DSObject *DSOperandOperator::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandOperator *new_operand_operator;

  if (fill_this == NULL)
  {
    new_operand_operator = (DSOperandOperator *)New(father); // virtueller Konstruktor
    assert(new_operand_operator);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_operator = (DSOperandOperator *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_operator);

  if (GetActualParamList())
  {
    new_operand_operator->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_operand_operator));
  }
  
  new_operand_operator->SetOperatorRef(GetOperatorRef());

  return new_operand_operator;
}

DSResult DSOperandOperator::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (operator_ref) operator_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);

  return DS_OK;
}

DSResult DSOperandOperator::Run(DSWriter *writer, DSType object_type,
                                DSCardinal what) const
{
  DSResult       result;
  DSActualParam *actual_param;

  switch(object_type)
  {
    case DS_ACTUALPARAM:
      for (actual_param = GetFirstActualParam();
           actual_param;
           actual_param = GetNextActualParam())
      {
        result = actual_param->Write(writer, what);
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
