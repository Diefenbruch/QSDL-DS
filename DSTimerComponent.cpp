/****************************************************************************
 *                 Modul: $RCSfile: DSTimerComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/14 10:59:24 $
 * $Revision: 1.3 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Timer
 *            definiert werden koennen.
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

#include "DSTimerComponent.h"
#include "DSTimer.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Timern
 ****************************************************************************/
 
/****************************************************************************
 * Globale Timern
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSTimerComponent::DSTimerComponent(DSObject *father) :
  parent(father)
{
  timer_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSTimerComponent::~DSTimerComponent(void)
{
  if (timer_definition_list) delete timer_definition_list;
}

DSTimerKeyList* DSTimerComponent::GetTimerList(void) const
{
  return timer_definition_list;
}

DSTimer *DSTimerComponent::GetTimer(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (timer_definition_list == NULL)
  {
    return NULL;
  }

  if (timer_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return timer_definition_list->GetCurrentData();
}

DSTimer *DSTimerComponent::GetTimer(DSString& n) const
{
  return GetTimer(&n);
}

DSTimer *DSTimerComponent::GetTimer(const char * n) const
{
  DSTimer *timer;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  timer = GetTimer(str);
  delete str;

  return timer;
}

DSTimer *DSTimerComponent::GetFirstTimer(void) const
{
  if (timer_definition_list == NULL)
  {
    return NULL;
  }

  if (timer_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return timer_definition_list->GetCurrentData();
}

DSTimer *DSTimerComponent::GetNextTimer(void) const
{
  if (timer_definition_list == NULL)
  {
    return NULL;
  }

  if (timer_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return timer_definition_list->GetCurrentData();
}

DSResult DSTimerComponent::SetTimerList(DSTimerKeyList *list)
{
  DSTimer *timer;

  if (timer_definition_list == list) return DS_OK;

  if (timer_definition_list != NULL)
  {
    delete timer_definition_list;
  }
  timer_definition_list = list;

  for (timer = GetFirstTimer();
       timer;
       timer = GetNextTimer())
  {
    timer->SetParent(parent);
  }

  return DS_OK;
}

DSResult DSTimerComponent::InsertTimer(DSTimer* timer)
{
  assert(timer != NULL);
  assert(timer->GetName() != NULL);

  if (timer_definition_list == NULL)
  {
    timer_definition_list = new DSTimerKeyList;
    assert(timer_definition_list != NULL);
  }
  if (timer->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    timer->SetParent(parent);
  }
  return timer_definition_list->Append(timer,
                                       new DSString(*timer->GetName()));
}

DSBoolean DSTimerComponent::HasTimerParams(void) const
{
  DSTimer *timer;

  for (timer = GetFirstTimer();
       timer;
       timer = GetNextTimer())
  {
    if (timer->GetSortRefList()) return DS_TRUE;
  }
  return DS_FALSE;
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSTimerComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSTimerComponent::SetComponentParent(const DSObject *par)
{
  DSTimer *timer;

  parent = (DSObject *)par;

  for (timer = GetFirstTimer();
       timer;
       timer = GetNextTimer())
  {
    timer->SetParent(parent);
  }

  return DS_OK;
}
