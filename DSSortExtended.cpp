/****************************************************************************
 *                 Modul: $RCSfile: DSSortExtended.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-SortExtended-Konstruktes <generator transformation>
 *
 * Funktionen: GetIndexSortRef(): liefert Zeiger auf Indexart (char,..)
 *             GetElemSortRef():  liefert Zeiger auf Elementsorte (char,..)
 *             SetIndexSortRef(): speichert Indexart
 *             SetElemSortRef():  speichert Elementsorte
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

#include "DSSortExtended.h"
#include "DSOperator.h"
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

DSSortExtended::DSSortExtended(DSObject          *father,
                               DSString          *sort_name,
                               DSSortTag          t,
                               DSStringList      *l_list,
                               DSOperatorKeyList *o_list,
                               DSBoolean          pre,
                               DSBoolean          comp) :
  DSSort(father, sort_name, t, pre, comp),
  literal_list(l_list),
  operator_list(o_list)
{
}

DSSortExtended::DSSortExtended(DSObject          *father,
                               DSString&          sort_name,
                               DSSortTag          t,
                               DSStringList      *l_list,
                               DSOperatorKeyList *o_list,
                               DSBoolean          pre,
                               DSBoolean          comp) :
  DSSort(father, &sort_name, t, pre, comp),
  literal_list(l_list),
  operator_list(o_list)
{
}

DSSortExtended::DSSortExtended(DSObject          *father,
                               const char        *sort_name,
                               DSSortTag          t,
                               DSStringList      *l_list,
                               DSOperatorKeyList *o_list,
                               DSBoolean          pre,
                               DSBoolean          comp) :
  DSSort(father, sort_name, t, pre, comp),
  literal_list(l_list),
  operator_list(o_list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSortExtended::~DSSortExtended(void)
{
  if (literal_list) delete literal_list;
  if (operator_list) delete operator_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSortExtended::New(DSObject *father) const
{
  return new DSSortExtended(father);
}

/****************************************************************************
 * GetLiteralList(): Liefert den Zeiger auf den Literal-Liste zurueck
 *                   Ergebnis: Zeiger auf einen DSStringList
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSStringList *DSSortExtended::GetLiteralList(void) const
{
  return literal_list;
}

DSString *DSSortExtended::GetFirstLiteral(void) const
{
  if (literal_list == NULL)
  {
    return NULL;
  }

  if (literal_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return literal_list->GetCurrentData();
}

DSString *DSSortExtended::GetNextLiteral(void) const
{
  if (literal_list == NULL)
  {
    return NULL;
  }

  if (literal_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return literal_list->GetCurrentData();
}

DSOperatorKeyList *DSSortExtended::GetOperatorList(void) const
{
  return operator_list;
}

DSOperator *DSSortExtended::GetFirstOperator(void) const
{
  if (operator_list == NULL)
  {
    return NULL;
  }

  if (operator_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return operator_list->GetCurrentData();
}

DSOperator *DSSortExtended::GetNextOperator(void) const
{
  if (operator_list == NULL)
  {
    return NULL;
  }

  if (operator_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return operator_list->GetCurrentData();
}

DSOperator *DSSortExtended::GetOperator(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
	}

  if (operator_list == NULL)
  {
    return NULL;
	}

  if (operator_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
	}
  return operator_list->GetCurrentData();
}

DSOperator *DSSortExtended::GetOperator(DSString& n) const
{
  return GetOperator(&n);
}

DSOperator *DSSortExtended::GetOperator(const char * n) const
{
  DSOperator *op;
  DSString *str = new DSString(n);
  op = GetOperator(str);
  delete str;
  return op;
}

/****************************************************************************
 * SetLiteralList(): Speichert den uebergebenen Zeiger
 *                   -> list: Zeiger auf eine DSStringList
 *                   Ergebnis: TRUE
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSortExtended::SetLiteralList(DSStringList* list)
{
  if (literal_list == list) return DS_OK;

  if (literal_list) delete literal_list;
  literal_list = list;
  return DS_OK;
}

DSResult DSSortExtended::InsertLiteral(DSString* literal)
{
  assert(literal);
  if (literal_list == NULL)
  {
    literal_list = new DSStringList;
    assert(literal_list != NULL);
  }
  return literal_list->Append(literal);
}

DSResult DSSortExtended::InsertLiteral(DSString& literal)
{
  if (literal_list == NULL)
  {
    literal_list = new DSStringList;
    assert(literal_list != NULL);
  }
  return literal_list->Append(&literal);
}

DSResult DSSortExtended::InsertLiteral(const char *literal)
{
  assert(literal);
  if (literal_list == NULL)
  {
    literal_list = new DSStringList;
    assert(literal_list != NULL);
  }
  return literal_list->Append(new DSString(literal));
}

DSResult DSSortExtended::SetOperatorList(DSOperatorKeyList* list)
{
  if (operator_list == list) return DS_OK;

  if (operator_list) delete operator_list;
  operator_list = list;
  return DS_OK;
}

DSResult DSSortExtended::InsertOperator(DSOperator* op)
{
  assert(op);
  assert(op->GetName() != NULL);

  if (operator_list == NULL)
  {
    operator_list = new DSOperatorKeyList;
    assert(operator_list != NULL);
  }
  return operator_list->Append(op,
                               new DSString(*op->GetName()));
}

DSObject *DSSortExtended::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSortExtended *new_sort_extended;

  if (fill_this == NULL)
  {
    new_sort_extended = (DSSortExtended *)New(father);
    assert(new_sort_extended);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_sort_extended = (DSSortExtended *)fill_this;
  }

  // Basisklassen clonen:
  DSSort::Clone(father, new_sort_extended);
 
  if (GetLiteralList())
  {
    new_sort_extended->SetLiteralList(GetLiteralList()->Clone((DSObject *)new_sort_extended));
  }

  if (GetOperatorList())
  {
    new_sort_extended->SetOperatorList((DSOperatorKeyList *)GetOperatorList()->Clone((DSObject *)new_sort_extended));
  }

  return new_sort_extended;
}

DSResult DSSortExtended::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSSortExtended::Run(DSWriter *writer, DSType object_type,
                             DSCardinal what) const
{
  DSResult        result;
  DSStringRef     literal;
  DSOperatorRef   optr;

  switch(object_type)
  {
    case DS_STRING:
      for (literal = GetFirstLiteral();
           literal;
           literal = GetNextLiteral())
      {
        result = literal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_OPERATOR:
      for (optr = GetFirstOperator();
           optr;
           optr = GetNextOperator())
      {
        result = optr->Write(writer, what);
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
