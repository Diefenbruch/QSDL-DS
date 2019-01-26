/****************************************************************************
 *                 Modul: $RCSfile: DSSyntype.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-SYNTYPE-Konstruktes
 *
 * Funktionen: SetParentSortRef(): speichert Zeiger auf "Basissorte"
 *             SetRangeList(): setzt die Wertebereichsliste
 *             InsertRange(): fuegt neuen Wertebereich in die Liste ein
 *             GetParentSortRef(): liefert die Basissorte
 *             GetRangeList(): liefert Liste der Wertebereiche
 *             GetFirstRange(): liefert ersten Wertebereich
 *             GetNextRange(): liefert naechsten Wertebereich
 *             Save(): Abspeicherung in Datei
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

#include "DSSyntype.h"
#include "DSRange.h"

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

DSSyntype::DSSyntype(DSObject    *father,
                     DSString    *sort_name,
                     DSSortRef    father_sort,
                     DSRangeList *r_list) :
  DSSort(father, sort_name, DS_SORT_SYNTYPE, DS_FALSE, DS_TRUE),
  range_list(r_list),
  parent_sort_ref(father_sort)
{
}

DSSyntype::DSSyntype(DSObject    *father,
                     DSString&    sort_name,
                     DSSortRef    father_sort,
                     DSRangeList *r_list) :
  DSSort(father, &sort_name, DS_SORT_SYNTYPE, DS_FALSE, DS_TRUE),
  range_list(r_list),
  parent_sort_ref(father_sort)
{
}

DSSyntype::DSSyntype(DSObject    *father,
                     const char  *sort_name,
                     DSSortRef    father_sort,
                     DSRangeList *r_list) :
  DSSort(father, sort_name, DS_SORT_SYNTYPE, DS_FALSE, DS_TRUE),
  range_list(r_list),
  parent_sort_ref(father_sort)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSyntype::~DSSyntype(void)
{
  if (range_list) delete range_list;
}

/****************************************************************************
 * GetParentSortRef(): liefert Zeiger auf "Basissorte"
 *                     Ergebnis: Zeiger auf DSSort
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSSortRef DSSyntype::GetParentSortRef(void) const
{
  return parent_sort_ref;
}

/****************************************************************************
 * GetRangeList(): liefert Zeiger auf die Wertebereichsliste
 *                 Ergebnis: Zeiger auf DSRangeList-Objekt
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSRangeList *DSSyntype::GetRangeList(void) const
{
  return range_list;
}

DSRange *DSSyntype::GetFirstRange(void) const
{
  if (range_list == NULL)
  {
    return NULL;
  }

  if (range_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return range_list->GetCurrentData();
}

DSRange *DSSyntype::GetNextRange(void) const
{
  if (range_list == NULL)
  {
    return NULL;
  }

  if (range_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return range_list->GetCurrentData();
}

/****************************************************************************
 * SetParentSortRef(): speichert Zeiger auf Index
 *                    ->parent: Zeiger auf DSSort
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSyntype::SetParentSortRef(DSSortRef parent_sort)
{
  parent_sort_ref = parent_sort;
  return DS_OK;
}

/****************************************************************************
 * SetRangeList(): speichert Zeiger auf DSRangeList-Objekt
 *                 ->r_list: Zeiger auf DSRange
 *                 Ergebnis: DS_OK
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSyntype::SetRangeList(DSRangeList *r_list)
{
  if (range_list == r_list) return DS_OK;

  if (range_list) delete range_list;
  range_list = r_list;
  return DS_OK;
}

DSResult DSSyntype::InsertRange(DSRange* range)
{
  assert(range != NULL);

  if (range_list == NULL)
  {
    range_list = new DSRangeList;
    assert(range_list != NULL);
  }
  if (range->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    range->SetParent(this);
  }
  return range_list->Append(range);
}

DSObject *DSSyntype::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSyntype *new_syntype;

  if (fill_this == NULL)
  {
    new_syntype = (DSSyntype *)New(father);
    assert(new_syntype);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_syntype = (DSSyntype *)fill_this;
  }

  // Basisklassen clonen:
  DSSort::Clone(father, new_syntype);

  if (GetRangeList())
  {
    new_syntype->SetRangeList(GetRangeList()->Clone((DSObject *)new_syntype));
  }

  new_syntype->SetParentSortRef(GetParentSortRef());

  return new_syntype;
}

DSResult DSSyntype::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_RANGE, what);
  if (parent_sort_ref) parent_sort_ref->Write(writer, what);

  return DS_OK;
}

DSResult DSSyntype::Run(DSWriter *writer, DSType object_type,
                       DSCardinal what) const
{
  DSResult        result;
  DSRangeRef      range;

  switch(object_type)
  {
    case DS_RANGE:
      for (range = GetFirstRange();
           range;
           range = GetNextRange())
      {
        result = range->Write(writer, what);
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
