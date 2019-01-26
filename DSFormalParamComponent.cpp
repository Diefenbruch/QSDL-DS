/****************************************************************************
 *                 Modul: $RCSfile: DSFormalParamComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die formale SDL-Parameter
 *            erwarten.
 *
 * Funktionen: GetFormalParamList()  liefert die Liste der formalen Parameter
 *             SetFormalParamList()  setzt die Liste der formalen Parameter
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

#include "DSFormalParamComponent.h"
#include "DSVariable.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe FormalParamn
 ****************************************************************************/
 
/****************************************************************************
 * Globale FormalParamn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSFormalParamComponent::DSFormalParamComponent(DSObject *father) :
  parent(father)
{
  formal_param_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSFormalParamComponent::~DSFormalParamComponent(void)
{
  if (formal_param_list) delete formal_param_list;
}

DSFormalParamKeyList* DSFormalParamComponent::GetFormalParamList(void) const
{
  return formal_param_list;
}

DSFormalParam *DSFormalParamComponent::GetFormalParam(DSString *n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (formal_param_list == NULL)
  {
    return NULL;
  }

  if (formal_param_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return formal_param_list->GetCurrentData();
}

DSFormalParam *DSFormalParamComponent::GetFormalParam(DSString &n) const
{
  return GetFormalParam(&n);
}

DSFormalParam *DSFormalParamComponent::GetFormalParam(const char *n) const
{
  DSFormalParam *param;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  param = GetFormalParam(str);
  delete str;

  return param;
}

DSFormalParam *DSFormalParamComponent::GetFirstFormalParam(void) const
{
  if (formal_param_list == NULL)
  {
    return NULL;
  }

  if (formal_param_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return formal_param_list->GetCurrentData();
}

DSFormalParam *DSFormalParamComponent::GetNextFormalParam(void) const
{
  if (formal_param_list == NULL)
  {
    return NULL;
  }

  if (formal_param_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return formal_param_list->GetCurrentData();
}

DSResult DSFormalParamComponent::SetFormalParamList(DSFormalParamKeyList *list)
{
  if (formal_param_list == list) return DS_OK;

  if (formal_param_list != NULL)
  {
    delete formal_param_list;
  }
  formal_param_list = list;
  return DS_OK;
}

DSResult DSFormalParamComponent::InsertFormalParam(DSFormalParam* param)
{
  assert(param != NULL);
  assert(param->GetName() != NULL);

  if (formal_param_list == NULL)
  {
    formal_param_list = new DSFormalParamKeyList;
    assert (formal_param_list != NULL);
  }
  if (param->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    param->SetParent(parent);
  }

  return formal_param_list->Append(param,
                                   new DSString(*param->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSFormalParamComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSFormalParamComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
