/****************************************************************************
 *                 Modul: $RCSfile: DSOperandExpression.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Expression-
 *          Operanden
 *
 * Funktionen: GetExpression() liefert einen Zeiger auf die Expression
 *             SetExpression() setzt den Zeiger auf eine Expression
 *             Save()          speichert einen Expression-Operanden
 ****************************************************************************/

/****************************************************************************
 * Konstanten
 ****************************************************************************/

/****************************************************************************
 * Include-Anweisungen
 ****************************************************************************/

#include "DSOperandExpression.h"
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

DSOperandExpression::DSOperandExpression(DSObject *father,
                                         DSExpression *exp) :
  DSOperand(father, DS_OPN_EXPRESSION),
  expression(exp)
{
  if (expression)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandExpression::~DSOperandExpression(void)
{
  if (expression) delete expression;
}

DSObject *DSOperandExpression::New(DSObject *father) const
{
  return new DSOperandExpression(father);
}

/****************************************************************************
 * GetExpression(): liefert Zeiger auf die Expression
 *                  Ergebnis: Zeiger auf DSExpression
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSOperandExpression::GetExpression(void) const
{
  return expression;
}

/****************************************************************************
 * SetExpression(): setzt Zeiger auf die Expression
 *                  ->exp: Zeiger auf DSExpression
 *                  Ergebnis: DS_OK
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandExpression::SetExpression(DSExpression *exp)
{
  if (expression == exp) return DS_OK;

  if (expression) delete expression;
  expression = exp;

  if (expression != NULL)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSOperandExpression::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandExpression *new_operand_expression;

  if (fill_this == NULL)
  {
    new_operand_expression = (DSOperandExpression *)New(father); // virtueller Konstruktor
    assert(new_operand_expression);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_expression = (DSOperandExpression *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_expression);

  if (GetExpression())
  {
    new_operand_expression->SetExpression((DSExpression *)GetExpression()->Clone((DSObject *)new_operand_expression));
  }

  return new_operand_expression;
}

DSResult DSOperandExpression::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (expression) expression->Write(writer, what);

  return DS_OK;
}
