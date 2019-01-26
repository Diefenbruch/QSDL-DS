/****************************************************************************
 *                 Modul: $RCSfile: DSStop.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Rueckgabewertes, der in Verbindung mit einem
 *          STOP-Befehl angegeben ist
 *
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

#include "DSStop.h"
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

DSStop::DSStop(DSObject *father,
               DSString *label_name) :
  DSAction (father, DS_STOP, label_name)
{
}

DSStop::DSStop(DSObject *father,
               DSString& label_name) :
  DSAction(father, DS_STOP, &label_name)
{
}

DSStop::DSStop(DSObject *father,
               const char *label_name) :
  DSAction(father, DS_STOP, label_name)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSStop::~DSStop(void)
{
}

DSObject *DSStop::Clone(DSObject *father, DSObject *fill_this) const
{
  DSStop *new_stop;

  if (fill_this == NULL)
  {
    new_stop = (DSStop *)New(father);
    assert(new_stop);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_stop = (DSStop *)fill_this;
  }

  DSAction::Clone(father, new_stop);

  return new_stop;
}

DSResult DSStop::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;
  
  assert(writer);

  return DS_OK;
}
