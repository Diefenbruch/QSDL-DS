/****************************************************************************
 *                 Modul: $RCSfile: DSOperand.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von SDL-Operanden
 *
 * Funktionen: GetTag() : Gibt den Typ des Operanden zurueck
 *             SetTag() : Setzt den Typ des Operanden
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

#include "DSOperand.h"
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

DSOperand::DSOperand(DSObject              *father,
                     DSExpressionOperandTag t) :
  DSObject(DS_OPERAND, father),
  tag(t)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperand::~DSOperand(void)
{
}

/****************************************************************************
 * GetTag(): Liefert den Typ des Operanden zurueck
 *           Ergebnis: Enum-Wert
 *           Seiteneffekte: keine
 ****************************************************************************/

DSExpressionOperandTag DSOperand::GetTag(void) const
{
  return tag;
}

/****************************************************************************
 * SetTag(): Speichert den uebergebenen Typ
 *            -> tag_type: Enum-Typ
 *            Ergebnis: TRUE
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperand::SetTag(DSExpressionOperandTag tag_type)
{
  tag = tag_type;
  return DS_OK;
}

DSObject *DSOperand::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperand *new_operand;

  if (fill_this == NULL)
  {
    new_operand = (DSOperand *)New(father);
    assert(new_operand);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand = (DSOperand *)fill_this;
  }

  new_operand->SetTag(GetTag());

  return new_operand;
}

DSResult DSOperand::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;
  assert(writer);

  return DS_OK;
}
