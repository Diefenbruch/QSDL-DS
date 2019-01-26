/****************************************************************************
 *                 Modul: $RCSfile: DSOperandConstant.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung einer SDL-Konstanten
 *
 * Funktionen: GetConstant(): liefert die Konstante als String
 *             SetConstant(): setzt die Konstant
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

DSOperandConstant::DSOperandConstant(DSObject *father,
                                     DSString *cons, DSBoolean num) :
  DSOperand(father, DS_OPN_CONSTANT),
  constant(cons),
  numeric(num)
{
}

DSOperandConstant::DSOperandConstant(DSObject *father,
                                     DSString &cons, DSBoolean num) :
  DSOperand(father, DS_OPN_CONSTANT),
  constant(&cons),
  numeric(num)
{
}

DSOperandConstant::DSOperandConstant(DSObject *father,
                                     const char *cons, DSBoolean num) :
  DSOperand(father, DS_OPN_CONSTANT),
  numeric(num)
{
  constant = new DSString(cons);
  assert(constant);
}

DSObject *DSOperandConstant::New(DSObject *father) const
{
  return new DSOperandConstant(father);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandConstant::~DSOperandConstant(void)
{
  if (constant) delete constant;
}

/****************************************************************************
 * GetConstant(): liefert Konstante als String
 *                Ergebnis: Zeiger auf DSString
 *                Seiteneffekte: keine
 ****************************************************************************/

DSString *DSOperandConstant::GetConstant(void) const
{
  return constant;
}

DSBoolean DSOperandConstant::GetIsNumeric(void) const
{
  return numeric;
}

/****************************************************************************
 * SetConstant(): setzt Wert der Konstanten
 *                ->elem: Zeiger auf DSString
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandConstant::SetConstant(DSString *cons)
{
  if (constant == cons) return DS_OK;

  if (constant) delete constant;
  constant = cons;

  if (constant != NULL)
  {
    if (constant->GetParent() == NULL)
    {
      constant->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSOperandConstant::SetConstant(DSString &cons)
{
  if (constant == &cons) return DS_OK;

  if (constant) delete constant;
  constant = &cons;

  if (constant->GetParent() == NULL)
  {
    constant->SetParent(this);
  }

  return DS_OK;
}

DSResult DSOperandConstant::SetConstant(const char *cons)
{
  if (constant) delete constant;
  constant = new DSString(cons);
  assert(constant);
  return DS_OK;
}

DSResult DSOperandConstant::SetIsNumeric(DSBoolean is_num)
{
  numeric = is_num;

  return DS_OK;
}

DSObject *DSOperandConstant::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandConstant *new_operand_constant;

  if (fill_this == NULL)
  {
    new_operand_constant = (DSOperandConstant *)New(father);  // virtueller Konstruktor
    assert(new_operand_constant);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_constant = (DSOperandConstant *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_constant);

  if (GetConstant())
  {
    new_operand_constant->SetConstant((DSString *)GetConstant()->Clone((DSObject *)new_operand_constant));
  }

  new_operand_constant->SetIsNumeric(GetIsNumeric());

  return new_operand_constant;
}

DSResult DSOperandConstant::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (constant) constant->Write(writer, what);

  return DS_OK;
}
