/****************************************************************************
 *                 Modul: $RCSfile: DSOperandState.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/09/30 16:08:45 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Statenoperanden
 *
 * Funktionen: GetStateRef(): liefert Zeiger auf die State
 *             SetStateRef(): setzt den Zeiger auf die State
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

#include "DSOperandState.h"
#include "DSState.h"
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

DSOperandState::DSOperandState(DSObject *father,
                               DSStateRef sig_ref) :
  DSOperand(father, DS_OPN_STATE),
  state_ref(sig_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandState::~DSOperandState(void)
{
}

DSObject *DSOperandState::New(DSObject *father) const
{
  return new DSOperandState(father);
}

/****************************************************************************
 * GetStateRef(): liefert Zeiger auf die State
 *                   Ergebnis: Zeiger auf DSState
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSStateRef DSOperandState::GetStateRef(void) const
{
  return state_ref;
}

/****************************************************************************
 * SetStateRef(): setzt Zeiger auf die State
 *                   ->elem: Zeiger auf DSState
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandState::SetStateRef(DSStateRef sig_ref)
{
  state_ref = sig_ref;
  return DS_OK;
}

DSObject *DSOperandState::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandState *new_operand_state;

  if (fill_this == NULL)
  {
    new_operand_state = (DSOperandState *)New(father); // virtueller Konstruktor
    assert(new_operand_state);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_state = (DSOperandState *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_state);

  new_operand_state->SetStateRef(GetStateRef());

  return new_operand_state;
}

DSResult DSOperandState::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (state_ref) state_ref->Write(writer, what);

  return DS_OK;
}
