/****************************************************************************
 *                 Modul: $RCSfile: DSOperator.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Elemente einer Operatordefinition
 *
 * Funktionen: GetName(): Gibt einen Zeiger auf den Operatornamen zurueck
 *             GetParameterSortRefList(): Liefert Zeiger auf Liste zurueck
 *             SetName(): Speichert Operatornamen
 *             SetParameterSortRefList(): Speichert die Sortenliste des Operators
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

#include "DSOperator.h"
#include "DSSortExtended.h"  // wegen parent
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

DSOperator::DSOperator(DSObject      *father,
                       DSString      *n, 
                       DSSortRefList *sort_list,
                       DSSortRef      result) :
  DSNamedObject(DS_OPERATOR, n, father),
  DSSortRefComponent(sort_list),
  result_sort_ref(result)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SORT:
        switch (((DSSort*)father)->GetTag())
        {
          case DS_SORT_EXTENDED:
          case DS_SORT_STRUCT:
          case DS_SORT_GENERATOR:
            ((DSSortExtended*)father)->InsertOperator(this);
            break;
          case DS_SORT_BASIC:
          case DS_SORT_SYNONYM:
          case DS_SORT_SYNTYPE:
            assert(DS_FALSE);
            break;
          default:
            break;
        }
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSOperator::DSOperator(DSObject      *father,
                       const char    *n, 
                       DSSortRefList *sort_list,
                       DSSortRef      result) :
  DSNamedObject(DS_OPERATOR, n, father),
  DSSortRefComponent(sort_list),
  result_sort_ref(result)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SORT:
        switch (((DSSort*)father)->GetTag())
        {
          case DS_SORT_EXTENDED:
          case DS_SORT_STRUCT:
          case DS_SORT_GENERATOR:
            ((DSSortExtended*)father)->InsertOperator(this);
            break;
          case DS_SORT_BASIC:
          case DS_SORT_SYNONYM:
          case DS_SORT_SYNTYPE:
            assert(DS_FALSE);
            break;
          default:
            break;
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

DSOperator::~DSOperator(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSOperator::New(DSObject *father) const
{
  return new DSOperator(father);
}

DSSortRef DSOperator::GetResultSortRef(void) const
{
  return result_sort_ref;
}

DSResult DSOperator::SetResultSortRef(DSSortRef sort_ref)
{
  result_sort_ref = sort_ref;
  return DS_OK;
}

DSObject *DSOperator::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperator *new_operator;

  if (fill_this == NULL)
  {
    new_operator = (DSOperator *)New(father);
    assert(new_operator);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERATOR);
    new_operator = (DSOperator *)fill_this;
  }

  DSNamedObject::Clone(father, new_operator);

  if (GetSortRefList())
  {
    new_operator->SetSortRefList((DSSortRefList *)GetSortRefList()->Clone((DSObject *)new_operator));
  }
  
  new_operator->SetResultSortRef(GetResultSortRef());

  return new_operator;
}

DSResult DSOperator::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSOperator::Run(DSWriter *writer, DSType object_type,
                         DSCardinal what) const
{
  DSResult        result;
  DSSortRef       sort;

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
