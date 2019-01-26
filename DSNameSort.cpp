/****************************************************************************
 *                 Modul: $RCSfile: DSNameSort.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines Namens in Verbindung mit einem Zeiger auf ein DSSort-Objekt
 *          um ein SDL-STRUCT aufbauen zu koennen
 *
 * Funktionen: GetSortRef(): Zeiger auf den Variablentyp (int, STRUCT,..)
 *             SetSortRef(): speichert einen Variablentyp
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

#include "DSNameSort.h"
#include "DSStruct.h"   // wegen parent
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

DSNameSort::DSNameSort(DSObject *father,
                       DSString *n,
                       DSSortRef sort) :
  DSNamedObject(DS_NAMESORT, n, father),
  sort_ref(sort)
{
  if (father)
  {
    if (!GetName())
    {
      std::cerr << "Field has a parent but no name!\n";
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SORT:
        if (((DSSort*)father)->GetTag() == DS_SORT_STRUCT)
        {
          ((DSStruct*)father)->InsertField(this);
        }
        else
        {
          std::cerr << "Illegal parent for field.\n";
          assert(DS_FALSE);
        }
        break;
      default:
        std::cerr << "Illegal parent for field.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSNameSort::DSNameSort(DSObject *father,
                       DSString &n,
                       DSSortRef sort) :
  DSNamedObject(DS_NAMESORT, n, father),
  sort_ref(sort)
{
  if (father)
  {
    if (!GetName())
    {
      std::cerr << "Field has a parent but no name!\n";
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SORT:
        if (((DSSort*)father)->GetTag() == DS_SORT_STRUCT)
        {
          ((DSStruct*)father)->InsertField(this);
        }
        else
        {
          std::cerr << "Illegal parent for field.\n";
          assert(DS_FALSE);
        }
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSNameSort::DSNameSort(DSObject *father,
                       const char *n,
                       DSSortRef sort) :
  DSNamedObject(DS_NAMESORT, n, father),
  sort_ref(sort)
{
  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SORT:
        if (((DSSort*)father)->GetTag() == DS_SORT_STRUCT)
        {
          ((DSStruct*)father)->InsertField(this);
        }
        else
        {
          assert(DS_FALSE);
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

DSNameSort::~DSNameSort(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSNameSort::New(DSObject *father) const
{
  return new DSNameSort(father);
}

/****************************************************************************
 * GetSortRef(): liefert Zeiger auf Basissorte
 *               Ergebnis: Zeiger auf DSSort-Objekt (bzw. abgeleitetes! )
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSSortRef DSNameSort::GetSortRef(void) const
{
  return sort_ref;
}

/****************************************************************************
 * SetSortRef(): speichert Zeiger auf Basissorte
 *              ->sort: Zeiger auf DSSort
 *              Ergebnis: DS_OK
 *              Seiteneffekte: keine
 ****************************************************************************/

DSResult DSNameSort::SetSortRef(DSSortRef sort)
{
  sort_ref = sort;
  return DS_OK;
}

DSObject *DSNameSort::Clone(DSObject *father, DSObject *fill_this) const
{
  DSNameSort *new_namesort;

  if (fill_this == NULL)
  {
    new_namesort = (DSNameSort *)New(father);
    assert(new_namesort);
  }
  else
  {
    assert(fill_this->GetType() == DS_NAMESORT);
    new_namesort = (DSNameSort *)fill_this;
    assert(new_namesort);
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_namesort);

  new_namesort->SetSortRef(GetSortRef());

  return new_namesort;
}

DSResult DSNameSort::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
