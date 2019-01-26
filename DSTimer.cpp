/****************************************************************************
 *                 Modul: $RCSfile: DSTimer.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von Namen und Index-Sorte eines Timers
 *
 * Funktionen: GetName(): Gibt einen Zeiger den Namen zurueck
 *             GetSortRef(): Liefert Zeiger auf Indexsorte zurueck
 *             SetName(): Speichert Timernamen
 *             SetSortRef(): Speichert die Indexsorte
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

#include "DSTimer.h"
#include "DSProcess.h"  // wegen parent
#include "DSSort.h"

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

DSTimer::DSTimer(DSObject      *father,
                 DSString      *n, 
                 DSSortRefList *sorts) :
  DSNamedObject(DS_TIMER, n, father),
  DSSortRefComponent(sorts)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertTimer(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSTimer::DSTimer(DSObject      *father,
                 DSString&      n, 
                 DSSortRefList *sorts) : 
  DSNamedObject(DS_TIMER, n, father),
  DSSortRefComponent(sorts)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertTimer(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSTimer::DSTimer(DSObject      *father,
                 const char    *n, 
                 DSSortRefList *sorts) : 
  DSNamedObject(DS_TIMER, n, father),
  DSSortRefComponent(sorts)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertTimer(this);
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

DSTimer::~DSTimer(void)
{
}

DSObject *DSTimer::Clone(DSObject *father, DSObject *fill_this) const
{
  DSTimer *new_timer;

  if (fill_this == NULL)
  {
    new_timer = (DSTimer *)New(father);
    assert(new_timer);
  }
  else
  {
    assert(fill_this->GetType() == DS_TIMER);
    new_timer = (DSTimer *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_timer);

  if (GetSortRefList())
  {
    new_timer->SetSortRefList((DSSortRefList *)GetSortRefList()->Clone((DSObject *)new_timer));
  }

  return new_timer;
}

DSResult DSTimer::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSTimer::Run(DSWriter *writer, DSType object_type,
                      DSCardinal what) const
{
  DSResult  result;
  DSSortRef sort;

  switch(object_type)
  {
    case DS_SORT:
      for (sort = GetFirstSortRef();
           sort;
           sort = GetNextSortRef())
      {
        result = sort->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
