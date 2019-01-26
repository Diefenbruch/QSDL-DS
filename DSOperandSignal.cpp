/****************************************************************************
 *                 Modul: $RCSfile: DSOperandSignal.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Signalnoperanden
 *
 * Funktionen: GetSignalRef(): liefert Zeiger auf die Signal
 *             SetSignalRef(): setzt den Zeiger auf die Signal
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

#include "DSOperandSignal.h"
#include "DSSignal.h"
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

DSOperandSignal::DSOperandSignal(DSObject *father,
                                   DSSignalRef sig_ref) :
  DSOperand(father, DS_OPN_SIGNAL),
  signal_ref(sig_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandSignal::~DSOperandSignal(void)
{
}

DSObject *DSOperandSignal::New(DSObject *father) const
{
  return new DSOperandSignal(father);
}

/****************************************************************************
 * GetSignalRef(): liefert Zeiger auf die Signal
 *                   Ergebnis: Zeiger auf DSSignal
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSSignalRef DSOperandSignal::GetSignalRef(void) const
{
  return signal_ref;
}

/****************************************************************************
 * SetSignalRef(): setzt Zeiger auf die Signal
 *                   ->elem: Zeiger auf DSSignal
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandSignal::SetSignalRef(DSSignalRef sig_ref)
{
  signal_ref = sig_ref;
  return DS_OK;
}

DSObject *DSOperandSignal::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandSignal *new_operand_signal;

  if (fill_this == NULL)
  {
    new_operand_signal = (DSOperandSignal *)New(father); // virtueller Konstruktor
    assert(new_operand_signal);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_signal = (DSOperandSignal *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_signal);

  new_operand_signal->SetSignalRef(GetSignalRef());

  return new_operand_signal;
}

DSResult DSOperandSignal::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (signal_ref) signal_ref->Write(writer, what);

  return DS_OK;
}
