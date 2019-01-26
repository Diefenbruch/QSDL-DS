/****************************************************************************
 *                 Modul: $RCSfile: DSSignalComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 10:59:24 $
 * $Revision: 1.3 $
 * Aufgabe: Basisklasse fuer alle SDL-Strukturen in denen SDL-Signale
 *          definiert werden koennen.
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

#include "DSSignalComponent.h"
#include "DSSignal.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Signaln
 ****************************************************************************/
 
/****************************************************************************
 * Globale Signaln
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalComponent::DSSignalComponent(DSObject *father) :
  parent(father)
{
  signal_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalComponent::~DSSignalComponent(void)
{
  if (signal_definition_list) delete signal_definition_list;
}

DSSignalKeyList* DSSignalComponent::GetSignalList(void) const
{
  return signal_definition_list;
}

DSSignal *DSSignalComponent::GetSignal(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (signal_definition_list == NULL)
  {
    return NULL;
  }

  if (signal_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return signal_definition_list->GetCurrentData();
}

DSSignal *DSSignalComponent::GetSignal(DSString& n) const
{
  return GetSignal(&n);
}

DSSignal *DSSignalComponent::GetSignal(const char * n) const
{
  DSSignal *signal;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  signal = GetSignal(str);
  delete str;

  return signal;
}

DSSignal *DSSignalComponent::GetFirstSignal(void) const
{
  if (signal_definition_list == NULL)
  {
    return NULL;
  }

  if (signal_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signal_definition_list->GetCurrentData();
}

DSSignal *DSSignalComponent::GetNextSignal(void) const
{
  if (signal_definition_list == NULL)
  {
    return NULL;
  }

  if (signal_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signal_definition_list->GetCurrentData();
}

DSResult DSSignalComponent::SetSignalList(DSSignalKeyList *list)
{
  if (signal_definition_list == list) return DS_OK;

  if (signal_definition_list != NULL)
  {
    delete signal_definition_list;
  }
  signal_definition_list = list;
  return DS_OK;
}

DSResult DSSignalComponent::InsertSignal(DSSignal* signal)
{
  assert(signal != NULL);
  assert(signal->GetName() != NULL);

  if (signal_definition_list == NULL)
  {
    signal_definition_list = new DSSignalKeyList;
    assert(signal_definition_list != NULL);
  }
  if (signal->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    signal->SetParent(parent);
  }
  return signal_definition_list->Append(signal,
                                        new DSString(*signal->GetName()));
}

DSBoolean DSSignalComponent::HasSignalParams(void) const
{
  DSSignal *signal;

  for (signal = GetFirstSignal();
       signal;
       signal = GetNextSignal())
  {
    if (signal->GetSortRefList()) return DS_TRUE;
  }
  return DS_FALSE;
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSSignalComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSSignalComponent::SetComponentParent(const DSObject *par)
{
  DSSignal *signal;

  parent = (DSObject *)par;

  for (signal = GetFirstSignal();
       signal;
       signal = GetNextSignal())
  {
    signal->SetParent(parent);
  }

  return DS_OK;
}
