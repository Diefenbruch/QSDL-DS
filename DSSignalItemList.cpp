/****************************************************************************
 *                 Modul: $RCSfile: DSSignalItemList.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von Signalen, Signallisten und Timerlisten in Verbindung mit
 *          der Definition der Signalliste eines Kanals/Signalroute
 *
 * Funktionen: GetSignalRefList(): Gibt einen Zeiger auf Liste zurueck
 *             GetSignalListRefList(): Liefert Zeiger auf Liste zurueck
 *             GetTimerRefList(): Liefert Listenzeiger
 *             SetSignalRefList(): Speichert Liste einzelner Signale
 *             SetSignalListRefList(): Speichert die Signallistenzeiger
 *             SetTimerRefList(): Speichert Listenzeiger
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

#include "DSSignalItemList.h"
#include "DSSave.h"  // wegen parent
#include "DSProcess.h"  // wegen parent
#include "DSSignalslist.h"  // wegen parent
#include "DSSignalRoute.h"  // wegen parent
#include "DSChannel.h"  // wegen parent
#include "DSSignal.h"
#include "DSTimer.h"
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

DSSignalItemList::DSSignalItemList (DSObject            *father,
                                    DSSignalRefList     *sig_ref,
                                    DSSignalslistRefList *sig_list_ref,
                                    DSTimerRefList      *timer_ref) :
  DSObject(DS_SIGNALITEMLIST, father),
  signal_ref_list(sig_ref),
  signallist_ref_list(sig_list_ref),
  timer_ref_list(timer_ref)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->SetValidSignalSet(this);
        break;
      case DS_SAVE:
        ((DSSave*)father)->SetSignalList(this);
        break;
      case DS_SIGNALLIST:
        ((DSSignalslist*)father)->SetSignalItemList(this);
        break;
      case DS_SIGNALROUTE:
        if (((DSSignalRoute*)father)->GetSignalList12() == NULL)
        {
          ((DSSignalRoute*)father)->SetSignalList12(this);
        }
        else if (((DSSignalRoute*)father)->GetSignalList21() == NULL)
        {
          ((DSSignalRoute*)father)->SetSignalList21(this);
        }
        break;
      case DS_CHANNEL:
        if (((DSChannel*)father)->GetSignalList12() == NULL)
        {
          ((DSChannel*)father)->SetSignalList12(this);
        }
        else if (((DSChannel*)father)->GetSignalList21() == NULL)
        {
          ((DSChannel*)father)->SetSignalList21(this);
        }
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

DSSignalItemList::~DSSignalItemList(void)
{
  if (signal_ref_list) delete signal_ref_list;
  if (signallist_ref_list) delete signallist_ref_list;
  if (timer_ref_list) delete timer_ref_list;
}

DSObject *DSSignalItemList::New(DSObject *father) const
{
  return new DSSignalItemList(father);
}

/****************************************************************************
 * GetSignals(): Hilfsprozedur zum "Linearisieren" der
 *                                 Signale in einer DSSignalItemList
 *             <- Linearisierte Liste aller Signalnamen
 *                Ergebnis: DS_OK, falls alles geklappt hat,sonst enthaelt
 *                          den aufgetretenen Fehler
 *                Seiteneffekte: Anlegen und Fuellen des .h-Files
 ****************************************************************************/

DSResult DSSignalItemList::GetSignals(DSSignalRefList *sig_ref_list) const
{
  DSResult result;
  DSSignalRef signal;
  DSSignalslistRef siglistref;
  
  assert(sig_ref_list);

  for (signal = GetFirstSignalRef();
       signal;
       signal = GetNextSignalRef())
  {
    if (!sig_ref_list->IsInList(signal))
    {
      assert(sig_ref_list->Append(signal) == DS_OK);
    }
  } 
  
  /************** jetzt die Signallisten durchlaufen ************************/
  
  for(siglistref = GetFirstSignallistRef();
      siglistref;
      siglistref = GetNextSignallistRef())
  {
    result = siglistref->GetSignalItemList()->GetSignals(sig_ref_list);
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

/****************************************************************************
 * GetTimers(): Hilfsprozedur zum "Linearisieren" der Timer in einer
 *              DSSignalItemList
 *             <- Linearisierte Liste aller Signalnamen
 *                Ergebnis: DS_OK, falls alles geklappt hat,sonst enthaelt
 *                CG_RESULT den aufgetretenen Fehler
 *                Seiteneffekte: Anlegen und Fuellen des .h-Files
 ****************************************************************************/

DSResult DSSignalItemList::GetTimers(DSTimerRefList *tim_ref_list) const
{
  DSResult result;
  DSTimerRef timer;
  DSSignalslistRef siglistref;

  assert(tim_ref_list);

  for (timer = GetFirstTimerRef();
       timer;
       timer = GetNextTimerRef())
  {
    if (!tim_ref_list->IsInList(timer))
    {
      assert(tim_ref_list->Append(timer) == DS_OK);
    }
  } 
  
  /************** jetzt die Signallisten durchlaufen ************************/
  
  for(siglistref = GetFirstSignallistRef();
      siglistref;
      siglistref = GetNextSignallistRef())
  {
    result = siglistref->GetSignalItemList()->GetTimers(tim_ref_list);
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

/****************************************************************************
 * GetSignalRefList(): Liefert den Zeiger auf Liste einzelner Signale
 *                     Ergebnis: Zeiger auf eine Liste
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSSignalRefList *DSSignalItemList::GetSignalRefList(void) const
{
  return signal_ref_list;
}

DSSignalRef DSSignalItemList::GetFirstSignalRef(void) const
{
  DSSignalRef signal_ref;

  if (signal_ref_list == NULL)
  {
    return NULL;
  }

  if (signal_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  signal_ref = signal_ref_list->GetCurrentData();
  return signal_ref;
}

DSSignalRef DSSignalItemList::GetNextSignalRef(void) const
{
  DSSignalRef signal_ref;

  if (signal_ref_list == NULL)
  {
    return NULL;
  }

  if (signal_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  signal_ref = signal_ref_list->GetCurrentData();
  return signal_ref;
}

/****************************************************************************
 * FindSignal(): Hilfsfunktion fuer GetSignalRef
 *               Ergebnis: Zeiger auf eine Signal oder NULL (nicht gefunden)
 *               Seiteneffekte: keine
 ****************************************************************************/

DSSignalRef DSSignalItemList::FindSignal(DSSignalItemListRef list,
                                         DSString *name) const
{
  DSSignalRef     signal;
  DSSignalslistRef signal_list;

  assert(list != NULL);
  assert(name != NULL);

  /****************************************************/
  /* zunaechst unter den "einfachen" Signalen suchen: */
  /****************************************************/

  for (signal = list->GetFirstSignalRef();
       signal != NULL;
       signal = list->GetNextSignalRef())
  {
    if (signal->GetName() == name)
    {
      return signal;
    }
  }

  /****************************************************/
  /* danach (Unter-)Signallisten durchsuchen:         */
  /****************************************************/

  for (signal_list = list->GetFirstSignallistRef();
       signal_list != NULL;
       signal_list = list->GetNextSignallistRef())
  {
    assert(signal_list->GetSignalItemList());
    signal = FindSignal(signal_list->GetSignalItemList(),
                        name);      // Suche rekursiv fortsetzen...
    if (signal != NULL)             // Signal gefunden?
    {
      return signal;
    }
  }
  return NULL;
}

/****************************************************************************
 * GetSignalRef(): Funktion sucht nach einem Signal in allen Unterstrukturen
 *                 von DSSignalItemList.
 *                 Ergebnis: Zeiger auf eine Signal oder NULL (nicht gefunden)
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSSignalRef DSSignalItemList::GetSignalRef(DSString *name) const
{
  assert(name != NULL);
  return FindSignal(this, name);
}

DSSignalRef DSSignalItemList::GetSignalRef(DSString &name) const
{
  return FindSignal(this, &name);
}

DSSignalRef DSSignalItemList::GetSignalRef(const char *name) const
{
  assert(name != NULL);
  DSString str(name);

  return FindSignal(this, &str);
}

DSBoolean DSSignalItemList::IsSignalRefInList(DSSignalRef ref) const
{
  if (FindSignal(this, ref->GetName()) != NULL)
  {
    return DS_TRUE;
	}
  return DS_FALSE;
}

/****************************************************************************
 * GetSignalListRefListList(): Liefert den Zeiger Liste von Signallisten
 *                             Ergebnis: Zeiger auf eine Liste
 *                             Seiteneffekte: keine
 ****************************************************************************/

DSSignalslistRefList *DSSignalItemList::GetSignallistRefList(void) const
{
  return signallist_ref_list;
}

DSSignalslistRef DSSignalItemList::GetFirstSignallistRef(void) const
{
  if (signallist_ref_list == NULL)
  {
    return NULL;
  }

  if (signallist_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signallist_ref_list->GetCurrentData();
}

DSSignalslistRef DSSignalItemList::GetNextSignallistRef(void) const
{
  if (signallist_ref_list == NULL)
  {
    return NULL;
  }

  if (signallist_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signallist_ref_list->GetCurrentData();
}

/****************************************************************************
 * GetTimerRefList(): Liefert Zeiger auf die Timerliste zurueck
 *                    Ergebnis: Zeiger auf eine Liste
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSTimerRefList *DSSignalItemList::GetTimerRefList(void) const
{
  return timer_ref_list;
}

DSTimerRef DSSignalItemList::GetFirstTimerRef(void) const
{
  if (timer_ref_list == NULL)
  {
    return NULL;
  }

  if (timer_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return timer_ref_list->GetCurrentData();
}

DSTimerRef DSSignalItemList::GetNextTimerRef(void) const
{
  if (timer_ref_list == NULL)
  {
    return NULL;
  }

  if (timer_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return timer_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetSignalRefList(): Speichert den uebergebenen Zeiger
 *                     -> sig_ref: Zeiger auf eine Signalliste
 *                     Ergebnis: TRUE
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalItemList::SetSignalRefList(DSSignalRefList *ref_list)
{
  if (signal_ref_list == ref_list) return DS_OK;

  if (signal_ref_list) delete signal_ref_list;
  signal_ref_list = ref_list;
  return DS_OK;
}

DSResult DSSignalItemList::InsertSignalRef(DSSignalRef signal_ref)
{
  assert(signal_ref != NULL);
  if (signal_ref_list == NULL)
  {
    signal_ref_list = new DSSignalRefList;
    assert(signal_ref_list != NULL);
  }
  return signal_ref_list->Append(signal_ref);
}

/****************************************************************************
 * SetSignalListRefList(): Speichert den uebergebenen Zeiger
 *                         -> list_ref: Zeiger auf einen DSString
 *                         Ergebnis: TRUE
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalItemList::SetSignallistRefList(DSSignalslistRefList *ref_list)
{
  if (signallist_ref_list == ref_list) return DS_OK;

  if (signallist_ref_list) delete signallist_ref_list;
  signallist_ref_list = ref_list;
  return DS_OK;
}

DSResult DSSignalItemList::InsertSignallistRef(DSSignalslistRef signallist_ref)
{
  assert(signallist_ref != NULL);
  if (signallist_ref_list == NULL)
  {
    signallist_ref_list = new DSSignalslistRefList;
    assert(signallist_ref_list != NULL);
  }
  return signallist_ref_list->Append(signallist_ref);
}

/****************************************************************************
 * SetTimerRefList(): Speichert den uebergebenen Zeiger
 *                    -> timer_ref: Zeiger auf eine Liste
 *                    Ergebnis: TRUE
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSignalItemList::SetTimerRefList(DSTimerRefList *ref_list)
{
  if (timer_ref_list == ref_list) return DS_OK;

  if (timer_ref_list) delete timer_ref_list;
  timer_ref_list = ref_list;
  return DS_OK;
}

DSResult DSSignalItemList::InsertTimerRef(DSTimerRef timer_ref)
{
  assert(timer_ref != NULL);
  if (timer_ref_list == NULL)
  {
    timer_ref_list = new DSTimerRefList;
    assert(timer_ref_list != NULL);
  }
  return timer_ref_list->Append(timer_ref);
}

DSObject *DSSignalItemList::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSignalItemList *new_signal_item_list;

  if (fill_this == NULL)
  {
    new_signal_item_list = (DSSignalItemList *)New(father);
    assert(new_signal_item_list);
  }
  else
  {
    assert(fill_this->GetType() == DS_SIGNALITEMLIST);
    new_signal_item_list = (DSSignalItemList *)fill_this;
  }

  if (GetSignalRefList())
  {
    new_signal_item_list->SetSignalRefList((DSSignalRefList *)GetSignalRefList()->Clone((DSObject *)new_signal_item_list));
  }

  if (GetSignallistRefList())
  {
    new_signal_item_list->SetSignallistRefList((DSSignalslistRefList *)GetSignallistRefList()->Clone((DSObject *)new_signal_item_list));
  }

  if (GetTimerRefList())
  {
    new_signal_item_list->SetTimerRefList((DSTimerRefList *)GetTimerRefList()->Clone((DSObject *)new_signal_item_list));
  }

  return new_signal_item_list;
}

DSResult DSSignalItemList::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_SIGNAL, what);
  Run(writer, DS_SIGNALLIST, what);
  Run(writer, DS_TIMER, what);

  return DS_OK;
}

DSResult DSSignalItemList::Run(DSWriter *writer, DSType object_type,
                               DSCardinal what) const
{
  DSResult        result;
  DSSignalRef     signal;
  DSTimerRef      timer;
  DSSignalslistRef signallist;

  switch(object_type)
  {
    case DS_SIGNAL:
      for (signal = GetFirstSignalRef();
           signal;
           signal = GetNextSignalRef())
      {
        result = signal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_TIMER:
      for (timer = GetFirstTimerRef();
           timer;
           timer = GetNextTimerRef())
      {
        result = timer->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNALLIST:
      for (signallist = GetFirstSignallistRef();
           signallist;
           signallist = GetNextSignallistRef())
      {
        result = signallist->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      std::cerr << "Illegal Run on signal item list!" << std::endl;
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
