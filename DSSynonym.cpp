/****************************************************************************
 *                 Modul: $RCSfile: DSSynonym.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-SYNONYM-Konstruktes
 *
 * Funktionen: GetValue(): liefert den konstanten Wert
 *             GetSortRef(): liefert den Typ der Konstanten
 *             SetValue(): speichert den konstanten Wert
 *             SetSortRef(): speichert den Typ der Konstanten
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

#include "DSSynonym.h"
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
 * Konstruktor
 ****************************************************************************/

DSSynonym::DSSynonym(DSObject     *father,
                     DSString     *sort_name,
                     DSExpression *default_ref,
                     DSSortRef     sort_ref) :
  DSSort(father, sort_name, DS_SORT_SYNONYM),
  default_value(default_ref),
  sort(sort_ref)
{
  if (default_value)
  {
    if (default_value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      default_value->SetParent(this);
    }
  }
}

DSSynonym::DSSynonym(DSObject     *father,
                     DSString&    sort_name,
                     DSExpression *default_ref,
                     DSSortRef     sort_ref) :
  DSSort(father, &sort_name, DS_SORT_SYNONYM),
  default_value(default_ref),
  sort(sort_ref)
{
  if (default_value)
  {
    if (default_value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      default_value->SetParent(this);
    }
  }
}

DSSynonym::DSSynonym(DSObject     *father,
                     const char   *sort_name,
                     DSExpression *default_ref,
                     DSSortRef     sort_ref) :
  DSSort(father, sort_name, DS_SORT_SYNONYM),
  default_value(default_ref),
  sort(sort_ref)
{
  if (default_value)
  {
    if (default_value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      default_value->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSynonym::~DSSynonym(void)
{
  delete default_value;                      /* Destruktor von DSExpression */
}

/****************************************************************************
 * GetValue(): liefert Zeiger auf konstanten Wert
 *             Ergebnis: Zeiger auf DSExpression
 *             Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSSynonym::GetValue(void) const
{
  return default_value;
}

/****************************************************************************
 * GetSortRef(): liefert Zeiger auf Basissorte
 *               Ergebnis: Zeiger auf DSSort-Objekt
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSSortRef DSSynonym::GetSortRef(void) const
{
  return sort;
}

/****************************************************************************
 * SetValue(): speichert Zeiger auf Konstante
 *             ->new_value: Zeiger auf DSString
 *             Ergebnis: DS_OK
 *             Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSynonym::SetValue(DSExpression *new_value)
{
  if (default_value == new_value) return DS_OK;

  if (default_value) delete default_value;
  default_value = new_value;

  if (default_value != NULL)
  {
    if (default_value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      default_value->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetSortRef(): speichert Zeiger auf DSSort-Objekt
 *              ->sort_ref: Zeiger auf DSSort
 *              Ergebnis: DS_OK
 *              Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSynonym::SetSortRef(DSSortRef sort_ref)
{
  sort = sort_ref;
  return DS_OK;
}

DSObject *DSSynonym::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSynonym *new_synonym;

  if (fill_this == NULL)
  {
    new_synonym = (DSSynonym *)New(father);
    assert(new_synonym);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_synonym = (DSSynonym *)fill_this;
  }

  // Basisklassen clonen:
  DSSort::Clone(father, new_synonym);

  if (GetValue())
  {
    new_synonym->SetValue((DSExpression *)GetValue()->Clone((DSObject *)new_synonym));
  }

  new_synonym->SetSortRef(GetSortRef());

  return new_synonym;
}

DSResult DSSynonym::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (default_value) default_value->Write(writer, what);
  if (sort) sort->Write(writer, what);

  return DS_OK;
}
