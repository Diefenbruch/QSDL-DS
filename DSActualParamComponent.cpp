/****************************************************************************
 *                 Modul: $RCSfile: DSActualParamComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 10:59:24 $
 * $Revision: 1.3 $
 *
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die aktuelle SDL-
 *            Parameter erwarten.
 *
 * Funktionen: GetActualParamList(): Liefert Referenz auf die Parameterliste
 *             SetActualParamList(): s. o.
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

#include "DSActualParamComponent.h"
#include "DSExpression.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe ActualParamn
 ****************************************************************************/

/****************************************************************************
 * Globale ActualParamn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSActualParamComponent::DSActualParamComponent(DSObject *father,
                                               DSActualParamList *p_list) :
  actual_param_list(p_list),
  parent(father)
{
  DSActualParam *actual_param;

  if (actual_param_list && parent)
  {
    for (actual_param = GetFirstActualParam();
         actual_param;
         actual_param = GetNextActualParam())
    {
      actual_param->SetParent(parent);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSActualParamComponent::~DSActualParamComponent(void)
{
  if (actual_param_list) delete actual_param_list;
}

/****************************************************************************
 * GetActualParamList(): Liefert Zeiger auf die aktuellen Parameter zurueck
 *                       Ergebnis: Ziger auf eine formale Parameterliste
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSActualParamList* DSActualParamComponent::GetActualParamList(void) const
{
  return actual_param_list;
}

DSActualParam *DSActualParamComponent::GetFirstActualParam(void) const
{
  if (actual_param_list == NULL)
  {
    return NULL;
  }

  if (actual_param_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return actual_param_list->GetCurrentData();
}

DSActualParam *DSActualParamComponent::GetNextActualParam(void) const
{
  if (actual_param_list == NULL)
  {
    return NULL;
  }

  if (actual_param_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return actual_param_list->GetCurrentData();
}

/****************************************************************************
 * SetActualParamList(): Speichert den uebergebenen Zeiger
 *                       -> p_list: Zeiger auf eine Parameterliste
 *                       Ergebnis: DS_OK
 *                       Seiteneffekte: keine
 ****************************************************************************/

DSResult DSActualParamComponent::SetActualParamList(DSActualParamList *list)
{
  DSActualParam *actual_param;

  if (actual_param_list == list) return DS_OK;

  if (actual_param_list) delete actual_param_list;
  actual_param_list = list;
  if (actual_param_list)
  {
    for (actual_param = GetFirstActualParam();
         actual_param;
         actual_param = GetNextActualParam())
    {
      if (actual_param->GetParent() == NULL) // Vater noch nicht gesetzt ?
      {
        actual_param->SetParent(parent);
      }
    }
  }
  return DS_OK;
}

DSResult DSActualParamComponent::InsertActualParam(DSActualParam* actual_param)
{
  assert(actual_param);
  if (actual_param_list == NULL)
  {
    actual_param_list = new DSActualParamList;
    assert(actual_param_list != NULL);
  }
  if (actual_param->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    actual_param->SetParent(parent);
  }
  return actual_param_list->Append(actual_param);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSActualParamComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSActualParamComponent::SetComponentParent(const DSObject *par)
{
  DSActualParam *actual_param;

  parent = (DSObject *)par;

  for (actual_param = GetFirstActualParam();
       actual_param;
       actual_param = GetNextActualParam())
  {
    actual_param->SetParent(parent);
  }

  return DS_OK;
}
