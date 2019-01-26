/****************************************************************************
 *                 Modul: $RCSfile: DSOperandVariableAccess.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Variablenzugriffs-
 *          operanden
 *
 * Funktionen: GetVariableAccess(): liefert Zeiger auf die Variable
 *             SetVariableAccess(): setzt den Zeiger auf die Variable
 *             Save(): Abspeicherung in eine Datei
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

#include "DSOperandVariableAccess.h"
#include "DSVariableAccess.h"

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

DSOperandVariableAccess::DSOperandVariableAccess(DSObject         *father,
                                                 DSVariableAccess *access) :
  DSOperand(father, DS_OPN_VARIABLE_ACCESS),
  variable_access(access)
{
  if (variable_access)
  {
    if (variable_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      variable_access->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandVariableAccess::~DSOperandVariableAccess(void)
{
  if (variable_access) delete variable_access;
}

DSObject *DSOperandVariableAccess::New(DSObject *father) const
{
  return new DSOperandVariableAccess(father);
}

/****************************************************************************
 * GetVariableAccess(): liefert Zeiger auf Variablenzugriff
 *                      Ergebnis: Zeiger auf DSVariable
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSVariableAccess *DSOperandVariableAccess::GetVariableAccess(void) const
{
  return variable_access;
}

/****************************************************************************
 * SetVariableAccess(): setzt Zeiger auf Variablenzugriff
 *                      -> elem: Zeiger auf DSVariable
 *                      Ergebnis: DS_OK
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandVariableAccess::SetVariableAccess(DSVariableAccess *access)
{
  if (variable_access == access) return DS_OK;

  if (variable_access) delete variable_access;
  variable_access = access;

  if (variable_access != NULL)
  {
    if (variable_access->GetParent() == NULL)
    {
      variable_access->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSOperandVariableAccess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandVariableAccess *new_operand_variable;

  if (fill_this == NULL)
  {
    new_operand_variable = (DSOperandVariableAccess *)New(father); // virtueller Konstruktor
    assert(new_operand_variable);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_variable = (DSOperandVariableAccess *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_variable);

  if (GetVariableAccess())
  {
    new_operand_variable->SetVariableAccess((DSVariableAccess *)GetVariableAccess()->Clone((DSObject *)new_operand_variable));
  }

  return new_operand_variable;
}

DSResult DSOperandVariableAccess::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (variable_access) variable_access->Write(writer, what);

  return DS_OK;
}
