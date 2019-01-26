/****************************************************************************
 *                 Modul: $RCSfile: DSSignalslist.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von Namen und Signalen/-listen in einer SIGNALLIST-Definition
 *
 * Funktionen: GetSignallist(): Liefert Zeiger auf Indexsorte zurueck
 *             SetSignallist(): Speichert die uebergebene Liste
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

#include "DSSignalslist.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlock.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSProcess.h"  // wegen parent
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

DSSignalslist::DSSignalslist(DSObject         *father,
                           DSString         *n,
                           DSSignalItemList *sig_list) :
  DSNamedObject(DS_SIGNALLIST, n, father),
  signal_item_list(sig_list)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignallist(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignallist(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignallist(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignallist(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignalslist::DSSignalslist(DSObject   *father,
                           DSString&   n,
                           DSSignalItemList *sig_list) :
  DSNamedObject(DS_SIGNALLIST, n, father),
  signal_item_list(sig_list)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignallist(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignallist(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignallist(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignallist(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignalslist::DSSignalslist(DSObject    *father,
                           const char  *n,
                           DSSignalItemList *sig_list) :
  DSNamedObject(DS_SIGNALLIST, n, father),
  signal_item_list(sig_list)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignallist(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignallist(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignallist(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignallist(this);
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

DSSignalslist::~DSSignalslist(void)
{
  if (signal_item_list) delete signal_item_list;                     
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSignalslist::New(DSObject *father) const
{
  return new DSSignalslist(father);
}

/****************************************************************************
 * GetSignalItemList(): Liefert den Zeiger auf die Liste zurueck
 *                      Ergebnis: Zeiger auf ein DSSignalItemList
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSSignalItemList* DSSignalslist::GetSignalItemList(void) const
{
  return signal_item_list;
}

/****************************************************************************
 * SetSignalItemList(): Speichert den uebergebenen Zeiger
 *                      -> sig_list: Zeiger auf eine DSSignalItemList
 *                      Ergebnis: DS_OK
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalslist::SetSignalItemList(DSSignalItemList *sig_list)
{
  if (signal_item_list == sig_list) return DS_OK;

  if (signal_item_list) delete signal_item_list;
  signal_item_list = sig_list;
  return DS_OK;
}

DSObject *DSSignalslist::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSignalslist *new_signal_list;

  if (fill_this == NULL)
  {
    new_signal_list = (DSSignalslist *)New(father);
    assert(new_signal_list);
  }
  else
  {
    assert(fill_this->GetType() == DS_SIGNALLIST);
    new_signal_list = (DSSignalslist *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_signal_list);

  if (GetSignalItemList())
  {
    new_signal_list->SetSignalItemList((DSSignalItemList *)GetSignalItemList()->Clone((DSObject *)new_signal_list));
  }

  return new_signal_list;
}

DSResult DSSignalslist::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
