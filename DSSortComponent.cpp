/****************************************************************************
 *                 Modul: $RCSfile: DSSortComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe: 
 *
 * Funktionen:
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

#include "DSSortComponent.h"
#include "DSSortExtended.h"
#include "DSOperator.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Sortn
 ****************************************************************************/
 
/****************************************************************************
 * Globale Sortn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSortComponent::DSSortComponent(DSObject *father) :
  parent(father)
{
  sort_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSortComponent::~DSSortComponent(void)
{
  if (sort_definition_list) delete sort_definition_list;
}

DSSortKeyList* DSSortComponent::GetSortList(void) const
{
  return sort_definition_list;
}

DSSort *DSSortComponent::GetSort(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (sort_definition_list == NULL)
  {
    return NULL;
  }

  if (sort_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return sort_definition_list->GetCurrentData();
}

DSSort *DSSortComponent::GetSort(DSString& n) const
{
  return GetSort(&n);
}

DSSort *DSSortComponent::GetSort(const char * n) const
{
  DSSort *sort;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  sort = GetSort(str);
  delete str;

  return sort;
}

DSSort *DSSortComponent::GetFirstSort(void) const
{
  if (sort_definition_list == NULL)
  {
    return NULL;
  }

  if (sort_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return sort_definition_list->GetCurrentData();
}

DSSort *DSSortComponent::GetNextSort(void) const
{
  if (sort_definition_list == NULL)
  {
    return NULL;
  }

  if (sort_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return sort_definition_list->GetCurrentData();
}

DSSort *DSSortComponent::GetLiteralSort(DSString* n) const
{
  DSResult        status, status2;
  DSSort         *sort;
  DSSortExtended *sort_extended;
  DSString       *literal;
  DSStringList   *literal_list;

  if (n == NULL)
  {
    return NULL;
  }

  if (sort_definition_list == NULL)
  {
    return NULL;
  }

  for (status = sort_definition_list->MoveFirst();
       status == DS_OK;
       status = sort_definition_list->MoveNext())
  {
    sort = sort_definition_list->GetCurrentData();
    assert(sort);
    if (sort->GetTag() != DS_SORT_EXTENDED &&   // keine Sorte mit Literalen?
        sort->GetTag() != DS_SORT_GENERATOR &&
        sort->GetTag() != DS_SORT_STRUCT)
    {
      continue;                                 // dann naechste Sorte!
    }
    sort_extended = (DSSortExtended*)sort;
    literal_list = sort_extended->GetLiteralList();
    if (!literal_list)                          // Literalliste leer?
    {
      continue;                                 // dann naechste Sorte!
    }
    for (status2 = literal_list->MoveFirst();
         status2 == DS_OK;
         status2 = literal_list->MoveNext())
    {
      literal = literal_list->GetCurrentData();
      if (*literal == *n)                       // Stringinhalte gleich?
      {
        return sort;
      }
    } // end for
  }  // end for
  return NULL;
}

DSSort *DSSortComponent::GetLiteralSort(DSString& n) const
{
  return GetLiteralSort(&n);
}

DSSort *DSSortComponent::GetLiteralSort(const char * n) const
{
  DSSort *sort;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  sort = GetLiteralSort(str);
  delete str;

  return sort;
}

DSSort *DSSortComponent::GetOperatorSort(DSString* n,
                                         DSSortRefList *parameter_sort_ref_list) const
{
  DSResult           status;
  DSSort            *sort;
  DSSortRef          sort_ref_1, sort_ref_2;
  DSSortExtended    *sort_extended;
  DSOperatorKeyList *operator_list;
  DSBoolean          not_found;
  DSOperator        *current_operator;

  if (n == NULL)
  {
    return NULL;
  }

  if (sort_definition_list == NULL)
  {
    return NULL;
  }

  for (status = sort_definition_list->MoveFirst();
       status == DS_OK;
       status = sort_definition_list->MoveNext())
  {
    sort = sort_definition_list->GetCurrentData();
    assert(sort);
    if (sort->GetTag() != DS_SORT_EXTENDED &&   // keine Sorte mit Operatoren?
        sort->GetTag() != DS_SORT_GENERATOR &&
        sort->GetTag() != DS_SORT_STRUCT)
    {
      continue;                                 // dann naechste Sorte!
    }
    sort_extended = (DSSortExtended*)sort;
    operator_list = sort_extended->GetOperatorList();
    if (!operator_list)                         // Operatorliste leer?
    {
      continue;                                 // nein, dann naechste Sorte!
    }
    if (operator_list->GotoKeyElement(n) !=     // existiert ueberhaupt ein
        DS_OK)                                  // Operator mit diesem Namen?
    {
      continue;                                 // nein, dann naechste Sorte!
    }

    if (!parameter_sort_ref_list)             // Parametertypen nicht
    {                                         // Interessant?
      return sort;
    }

    current_operator = operator_list->GetCurrentData();
    if (!current_operator->GetSortRefList())
    {
      continue;  // weitersuchen
    }

    // Wenn die Anzahl der Parameter nicht uebereinstimmen,
    // kann es nicht der richtige Operator sein:
    if (current_operator->GetSortRefList()->NumberOfElements() !=
        parameter_sort_ref_list->NumberOfElements())
    {
      continue;  // weitersuchen
    }
    not_found = DS_FALSE;
    // Jetzt ueberpruefen ob die Typen der Parameter auch
    // uebereinstimmen:
    for (sort_ref_1 = current_operator->GetFirstSortRef(),
         status = parameter_sort_ref_list->MoveFirst();
         sort_ref_1 != NULL && status == DS_OK;
         sort_ref_1 = current_operator->GetNextSortRef(),
         status = parameter_sort_ref_list->MoveNext())
    {
      sort_ref_2 = parameter_sort_ref_list->GetCurrentData();
      if (!sort_ref_2) // Konstante?
      {
        continue;  // dann OK!
      }
      if (*(sort_ref_1->GetName()) == *(sort_ref_2->GetName()))
      {
        continue;  // noch keine "Nichtuebereinstimmung" gefunden
      }
      not_found = DS_TRUE;   // muss weitersuchen
      break;                 // Nichtuebereinstimmung! (weiter mit naechstem
                             //                         Operator)
      
    }
    if (not_found == DS_FALSE)  // richtige Sorte gefunden?
    {
      return sort;
    }
  }  // end for (alle Sorten des SortComponents)
  return NULL;
}

DSSort *DSSortComponent::GetOperatorSort(DSString& n,
                                         DSSortRefList *parameter_sort_ref_list) const
{
  return GetOperatorSort(&n, parameter_sort_ref_list);
}

DSSort *DSSortComponent::GetOperatorSort(const char * n,
                                         DSSortRefList *parameter_sort_ref_list) const
{
  DSSort *sort;
  DSString *str;

  assert(n);
  str = new DSString(n);
  sort = GetOperatorSort(str, parameter_sort_ref_list);
  delete str;

  return sort;
}

DSResult DSSortComponent::SetSortList(DSSortKeyList *list)
{
  if (sort_definition_list == list) return DS_OK;

  if (sort_definition_list != NULL)
  {
    delete sort_definition_list;
  }
  sort_definition_list = list;
  return DS_OK;
}

DSResult DSSortComponent::InsertSort(DSSort* sort)
{
  assert(sort != NULL);
  assert(sort->GetName() != NULL);

  if (sort_definition_list == NULL)
  {
    sort_definition_list = new DSSortKeyList;
    assert(sort_definition_list != NULL);
  }
  if (sort->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    sort->SetParent(parent);
  }
  return sort_definition_list->Append(sort,
                                      new DSString(*sort->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSSortComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSSortComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
