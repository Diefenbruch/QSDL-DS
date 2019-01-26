/****************************************************************************
 *                 Modul: $RCSfile: DSReturn.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Rueckgabewertes, der in Verbindung mit einem
 *          RETURN-Befehl angegeben ist
 *
 * Funktionen: GetResult(): Gibt einen Zeiger auf einen Ausdruck zurueck
 *             SetResult(): Speichert einen Ausdruck
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

#include "DSReturn.h"
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

DSReturn::DSReturn(DSObject *father,
                   DSExpression *return_value,
                   DSString *label_name) :
  DSAction (father, DS_RETURN, label_name),
  proc_result(return_value)
{
}

DSReturn::DSReturn(DSObject *father,
                   DSExpression *return_value,
                   DSString& label_name) :
  DSAction(father, DS_RETURN, &label_name),
  proc_result(return_value)
{
}

DSReturn::DSReturn(DSObject *father,
                   DSExpression *return_value,
                   const char *label_name) :
  DSAction(father, DS_RETURN, label_name),
  proc_result(return_value)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSReturn::~DSReturn(void)
{
  if (proc_result) delete proc_result;
}

/****************************************************************************
 * GetResult(): Liefert den Zeiger auf den Rueckgabewert zurueck
 *              Ergebnis: Zeiger auf einen Expression
 *              Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSReturn::GetResult(void) const
{
  return proc_result;
}

/****************************************************************************
 * SetResult(): Speichert den uebergebenen Zeiger
 *                    -> conn_ref: Zeiger auf einen Expression
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSReturn::SetResult(DSExpression* return_value)
{
  if (proc_result == return_value) return DS_OK;

  if (proc_result) delete proc_result;
  proc_result = return_value;

  if (proc_result != NULL)
  {
    if (proc_result->GetParent() == NULL)
    {
      proc_result->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSReturn::Clone(DSObject *father, DSObject *fill_this) const
{
  DSReturn *new_return;

  if (fill_this == NULL)
  {
    new_return = (DSReturn *)New(father);
    assert(new_return);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_return = (DSReturn *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_return);

  if (GetResult())
  {
    new_return->SetResult((DSExpression *)GetResult()->Clone((DSObject *)new_return));
  }

  return new_return;
}

DSResult DSReturn::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (proc_result) proc_result->Write(writer, what);

  return DS_OK;
}
