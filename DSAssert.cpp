/****************************************************************************
 *                 Modul: $RCSfile: DSAssert.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/09 10:59:05 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einer QSDL-Assert-Aktion
 *          angegeben sind
 *
 * Funktionen: GetExpression(): Gibt einen Zeiger auf den entsprechenden
 *                              Ausdruck zurueck
 *             SetExpression(): Speichert den uebergebenen Sensorzeiger
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

#include "DSAssert.h"
#include "DSSensor.h"
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

DSAssert::DSAssert(DSObject     *father,
                   DSString     *label_name, 
                   DSExpression *exp) :
  DSAction(father, DS_ASSERT, label_name),
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

DSAssert::DSAssert(DSObject     *father,
                   DSString     &label_name, 
                   DSExpression *exp) :
  DSAction(father, DS_ASSERT, &label_name),
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

DSAssert::DSAssert(DSObject     *father,
                   const char   *label_name, 
                   DSExpression *exp) :
  DSAction(father, DS_ASSERT, label_name),
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

DSAssert::~DSAssert(void)
{
  if (expression)
    delete expression;
}

/****************************************************************************
 * GetExpression(): Liefert Zeiger auf den zurueckgesetzten Sensor
 *                 Ergebnis: Zeiger auf einen Sensor
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSAssert::GetExpression(void) const
{
  return expression;
}

/****************************************************************************
 * SetExpression(): Speichert den uebergebenen Zeiger
 *                -> sensor : Zeiger auf einen Sensor
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSAssert::SetExpression(DSExpression *exp)
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

DSObject *DSAssert::Clone(DSObject *father, DSObject *fill_this) const
{
  DSAssert *new_assert;

  if (fill_this == NULL)
  {
    new_assert = (DSAssert *)New(father);
    assert(new_assert);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_assert = (DSAssert *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_assert);

  if (GetExpression())
  {
    new_assert->SetExpression((DSExpression *)GetExpression()->Clone((DSObject *)new_assert));
  }

  return new_assert;
}

DSResult DSAssert::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  (void)what;

  return DS_OK;
}

DSResult DSAssert::Run(DSWriter *writer, DSType object_type,
                       DSCardinal what) const
{
  assert(writer);
  
  (void)what;
  (void)object_type;

  return DS_OK;
}
