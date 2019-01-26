/****************************************************************************
 *                 Modul: $RCSfile: DSStruct.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-Struct-Konstruktes
 *
 * Funktionen: InsertField(): Einfuegen eines Elementes in die Liste der
 *                            Komponenten der Structure
 *             DeleteField(): Loeschen eines Listenelementes
 *             GetFieldSort(): Liefert den Elementtyp
 *             Save(): Abspeicherung in eine Datei 
 *
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

#include "DSStruct.h"
#include "DSNameSort.h"
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

DSStruct::DSStruct(DSObject *father,
                   DSString *sort_name,
                   DSNameSortKeyList *list) :
  DSSortExtended(father, sort_name, DS_SORT_STRUCT, NULL, NULL, DS_FALSE, DS_TRUE),
  field_list(list)
{
}

DSStruct::DSStruct(DSObject *father,
                   DSString& sort_name,
                   DSNameSortKeyList *list) :
  DSSortExtended(father, &sort_name, DS_SORT_STRUCT, NULL, NULL, DS_FALSE, DS_TRUE),
  field_list(list)
{
}

DSStruct::DSStruct(DSObject *father,
                   const char* sort_name,
                   DSNameSortKeyList *list) :
  DSSortExtended(father, sort_name, DS_SORT_STRUCT, NULL, NULL, DS_FALSE, DS_TRUE),
  field_list(list)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSStruct::~DSStruct(void)
{
  if (field_list) delete field_list;           /* Destruktor der Liste      */
}

/****************************************************************************
 * GetFieldList(): Liefert die List der Felder
 *                 Ergebnis: Feldlist (DSNameSortKeyList)
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSNameSortKeyList *DSStruct::GetFieldList(void) const
{
  return field_list;
}

DSNameSort *DSStruct::GetFirstField(void) const
{
  if (field_list == NULL)
  {
    return NULL;
  }

  if (field_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return field_list->GetCurrentData();
}

DSNameSort *DSStruct::GetNextField(void) const
{
  if (field_list == NULL)
  {
    return NULL;
  }

  if (field_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return field_list->GetCurrentData();
}

/****************************************************************************
 * GetField(): Liefert den NameSort-Element zu einem Feldnamen
 *             -> field_name: Name des Feldes
 *             Ergebnis: DSNameSort (Name + Datentyp) 
 *             Seiteneffekte: keine
 ****************************************************************************/

DSNameSort *DSStruct::GetField(DSString *field_name) const
{
  DSNameSort *field;

  assert(field_name);

  if (field_list == NULL)
  {
    return NULL;
  }

  if (field_list->GotoKeyElement(field_name) != DS_OK)
  {
    return NULL;
  }
  field = field_list->GetCurrentData();
  return field;
}

DSNameSort *DSStruct::GetField(DSString& n) const
{
  return GetField(&n);
}

DSNameSort *DSStruct::GetField(const char * n) const
{
  DSNameSort *field;
  DSString *str = new DSString(n);
  field = GetField(str);
  delete str;
  return field;
}

DSResult DSStruct::SetFieldList(DSNameSortKeyList *list)
{
  if (field_list == list) return DS_OK;

  if (field_list) delete field_list;
  field_list = list;
  return DS_OK;
}

/****************************************************************************
 * InsertField(): Einfuegen eines neuen Struct-Elementes in Liste
 *                ->new_elem: Neues Element
 *                Ergebnis: DS_OK, wenn erfolgreich, DS_FALSE sonst
 *                Seiteneffekte: Schluesselliste waechst um ein element
 ****************************************************************************/

DSResult DSStruct::InsertField(DSNameSort *new_elem)
{
  assert(new_elem != NULL);
  assert(new_elem->GetName() != NULL);

  if (field_list == NULL)      // 1. Element?
  {
    field_list = new DSNameSortKeyList;
    assert(field_list != NULL);
  }
  return field_list->Append(new_elem,
                            new DSString(*new_elem->GetName()));
}

DSObject *DSStruct::Clone(DSObject *father, DSObject *fill_this) const
{
  DSStruct *new_struct;

  if (fill_this == NULL)
  {
    new_struct = (DSStruct *)New(father);
    assert(new_struct);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_struct = (DSStruct *)fill_this;
  }

  // Basisklassen clonen
  DSSortExtended::Clone(father, new_struct);

  if (GetFieldList())
  {
    new_struct->SetFieldList((DSNameSortKeyList *)GetFieldList()->Clone((DSObject *)new_struct));
  }

  return new_struct;
}

DSResult DSStruct::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  Run(writer, DS_NAMESORT, what);

  return DS_OK;
}

DSResult DSStruct::Run(DSWriter *writer, DSType object_type,
                       DSCardinal what) const
{
  DSResult        result;
  DSNameSortRef   namesort;

  switch(object_type)
  {
    case DS_NAMESORT:
      for (namesort = GetFirstField();
           namesort;
           namesort = GetNextField())
      {
        result = namesort->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_OPERATOR:
      return DSSortExtended::Run(writer, object_type, what);
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
