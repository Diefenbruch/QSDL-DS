/****************************************************************************
 *                 Modul: $RCSfile: DSSave.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul stellt die Funktionen fuer das SDL-Save-Konstrukt
 *          zur Verfuegung
 *
 * Funktionen:
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

#include "DSSave.h"
#include "DSState.h"  // wegen parent
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

DSSave::DSSave(DSObject         *father,
               DSBoolean         asterisk,
               DSSignalItemList *save_list) :
  DSObject(DS_SAVE, father),
  is_asterisk(asterisk),
  signal_list(save_list)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_STATE:
        ((DSState*)father)->InsertSave(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSave::~DSSave(void)
{
  if (signal_list) delete signal_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSave::New(DSObject *father) const
{
  return new DSSave(father);
}

/****************************************************************************
 * GetIsAsterisk(): Liefert Flagwert zurueck
 *                  Ergebnis: Boolscher Typ
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSSave::GetIsAsterisk(void) const
{
  return is_asterisk;
}

/****************************************************************************
 * GetInputSignalList(): Liefert den Zeiger auf Signalliste zurueck
 *                       Ergebnis: Zeiger auf eine Liste
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSSignalItemList *DSSave::GetSignalList(void) const
{
  return signal_list;
}

/****************************************************************************
 * SetIsAsterisk(): Setzt das Flag
 *                  -> accepts: Boolscher Typ
 *                  Ergebnis: TRUE
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSave::SetIsAsterisk(DSBoolean asterisk)
{
  is_asterisk = asterisk;
  return DS_OK;
}

/****************************************************************************
 * SetSignalList(): Speichert den uebergebenen Zeiger
 *                  -> sig_ref: Zeiger auf eine Liste
 *                  Ergebnis: TRUE
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSave::SetSignalList(DSSignalItemList *save_list)
{
  if (signal_list == save_list) return DS_OK;

  if (signal_list) delete signal_list;
  signal_list = save_list;
  return DS_OK;
}

DSObject *DSSave::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSave *new_save;

  if (fill_this == NULL)
  {
    new_save = (DSSave *)New(father);
    assert(new_save);
  }
  else
  {
    assert(fill_this->GetType() == DS_SAVE);
    new_save = (DSSave *)fill_this;
  }

  if (GetSignalList())
  {
    new_save->SetSignalList((DSSignalItemList *)GetSignalList()->Clone((DSObject *)new_save));
  }

  new_save->SetIsAsterisk(GetIsAsterisk());

  return new_save;
}

DSResult DSSave::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (signal_list) signal_list->Write(writer, what);

  return DS_OK;
}
