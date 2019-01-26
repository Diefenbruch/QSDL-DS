/****************************************************************************
 *                 Modul: $RCSfile: DSSignal.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Variablen in Verbindung mit einer Signaldefinition
 *
 * Funktionen: GetSortList(): Liefert Zeiger auf Liste zurueck
 *             SetSortList(): Speichert die Variablenliste des Signals
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

#include "DSSignal.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlock.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
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

DSSignal::DSSignal(DSObject      *father,
                   DSString      *n, 
                   DSSortRefList *sort_list) :
  DSNamedObject(DS_SIGNAL, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignal(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignal(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignal(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignal(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignal::DSSignal(DSObject      *father,
                   DSString      &n, 
                   DSSortRefList *sort_list) :
  DSNamedObject(DS_SIGNAL, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignal(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignal(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignal(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignal(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignal::DSSignal(DSObject      *father,
                   const char    *n, 
                   DSSortRefList *sort_list) :
  DSNamedObject(DS_SIGNAL, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSignal(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignal(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSignal(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSignal(this);
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

DSSignal::~DSSignal(void)
{
}

DSObject *DSSignal::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSignal *new_signal;

  if (fill_this == NULL)
  {
    new_signal = (DSSignal *)New(father);
    assert(new_signal);
  }
  else
  {
    assert(fill_this->GetType() == DS_SIGNAL);
    new_signal = (DSSignal *)fill_this;
  }

  // Basisklasse clonen:
  DSNamedObject::Clone(father, new_signal);

  if (GetSortRefList())
  {
    new_signal->SetSortRefList((DSSortRefList *)GetSortRefList()->Clone((DSObject *)new_signal));
  }

  return new_signal;
}

DSResult DSSignal::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSSignal::Run(DSWriter *writer, DSType object_type,
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
