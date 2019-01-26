/****************************************************************************
 *                 Modul: $RCSfile: DSOperandProcessAccess.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/07 14:53:39 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines ProcessAccessnoperanden
 *
 * Funktionen: GetProcessAccess(): liefert Zeiger auf die ProcessAccess
 *             SetProcessAccess(): setzt den Zeiger auf die ProcessAccess
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

#include "DSOperandProcessAccess.h"
#include "DSProcessAccess.h"
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

DSOperandProcessAccess::DSOperandProcessAccess(DSObject *father,
                                               DSProcessAccess* p_access) :
  DSOperand(father, DS_OPN_PROCESS_ACCESS),
  process_access(p_access)
{
  if (process_access)
  {
    if (process_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      process_access->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandProcessAccess::~DSOperandProcessAccess(void)
{
  if (process_access) delete process_access;
}

DSObject *DSOperandProcessAccess::New(DSObject *father) const
{
  return new DSOperandProcessAccess(father);
}

/****************************************************************************
 * GetProcessAccess(): liefert Zeiger auf die ProcessAccess
 *                   Ergebnis: Zeiger auf DSProcessAccess
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSProcessAccess * DSOperandProcessAccess::GetProcessAccess(void) const
{
  return process_access;
}

/****************************************************************************
 * SetProcessAccess(): setzt Zeiger auf die ProcessAccess
 *                   ->elem: Zeiger auf DSProcessAccess
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandProcessAccess::SetProcessAccess(DSProcessAccess* p_access)
{
  process_access = p_access;
  return DS_OK;
}

DSObject *DSOperandProcessAccess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandProcessAccess *new_operand_process;

  if (fill_this == NULL)
  {
    new_operand_process = (DSOperandProcessAccess *)New(father); // virtueller Konstruktor
    assert(new_operand_process);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_process = (DSOperandProcessAccess *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_process);

  new_operand_process->SetProcessAccess(GetProcessAccess());

  return new_operand_process;
}

DSResult DSOperandProcessAccess::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);
  (void)what;

  return DS_OK;
}
