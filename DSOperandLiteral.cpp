/****************************************************************************
 *                 Modul: $RCSfile: DSOperandLiteral.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung einer SDL-Konstanten
 *
 * Funktionen: GetLiteral(): liefert die Konstante als String
 *             SetLiteral(): setzt die Konstant
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

#include "DSOperandLiteral.h"
#include "DSSort.h"
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

DSOperandLiteral::DSOperandLiteral(DSObject *father,
                                   DSString *n, DSSortRef s) :
  DSOperand(father, DS_OPN_LITERAL),
  name(n),
  sort_ref(s)
{
}

DSOperandLiteral::DSOperandLiteral(DSObject *father,
                                   DSString &n, DSSortRef s) :
  DSOperand(father, DS_OPN_LITERAL),
  name(&n),
  sort_ref(s)
{
}

DSOperandLiteral::DSOperandLiteral(DSObject *father,
                                   const char *n, DSSortRef s) :
  DSOperand(father, DS_OPN_LITERAL),
  sort_ref(s)
{
  name = new DSString(n);
  assert(name);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandLiteral::~DSOperandLiteral(void)
{
  if (name) delete name;
}

DSObject *DSOperandLiteral::New(DSObject *father) const
{
  return new DSOperandLiteral(father);
}

/****************************************************************************
 * GetName(): liefert Literalnamen als String
 *            Ergebnis: Zeiger auf DSString
 *            Seiteneffekte: keine
 ****************************************************************************/

DSString *DSOperandLiteral::GetName(void) const
{
  return name;
}

DSSortRef DSOperandLiteral::GetSortRef(void) const
{
  return sort_ref;
}

/****************************************************************************
 * SetLiteral(): setzt Wert der Konstanten
 *                ->elem: Zeiger auf DSString
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandLiteral::SetName(DSString *n)
{
  if (name == n) return DS_OK;

  if (name) delete name;
  name = n;

	if (name != NULL)
  {
    if (name->GetParent() == NULL)
    {
      name->SetParent(this);
    }
  }
	
  return DS_OK;
}

DSResult DSOperandLiteral::SetName(DSString &n)
{
  if (name == &n) return DS_OK;

  if (name) delete name;
  name = &n;

  if (name->GetParent() == NULL)
  {
    name->SetParent(this);
  }

	return DS_OK;
}

DSResult DSOperandLiteral::SetName(const char *n)
{
  if (name) delete name;
  name = new DSString(this, n);
  assert(name);

  return DS_OK;
}

DSResult DSOperandLiteral::SetSortRef(DSSortRef sort)
{
  sort_ref = sort;

  return DS_OK;
}

DSObject *DSOperandLiteral::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandLiteral *new_operand_literal;

  if (fill_this == NULL)
  {
    new_operand_literal = (DSOperandLiteral *)New(father); // virtueller Konstruktor
    assert(new_operand_literal);
    new_operand_literal->SetName(GetName()->GetString());
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_literal = (DSOperandLiteral *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_literal);

  if (GetName())
  {
    new_operand_literal->SetName((DSString *)GetName()->Clone((DSObject *)new_operand_literal));
  }

  new_operand_literal->SetSortRef(GetSortRef()); // don't clone Refs!

  return new_operand_literal;
}

DSResult DSOperandLiteral::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (name) name->Write(writer, what);
  if (sort_ref) sort_ref->Write(writer, what);

  return DS_OK;
}
