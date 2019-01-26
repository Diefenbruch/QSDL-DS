/****************************************************************************
 *                 Modul: $RCSfile: DSProcessComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozesse
 *            definiert werden koennen.
 *
 * Funktionen: GetProcessList()
 *             SetProcessList()
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

#include "DSProcessComponent.h"
#include "DSProcess.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Processn
 ****************************************************************************/
 
/****************************************************************************
 * Globale Processn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSProcessComponent::DSProcessComponent(DSObject *father) :
  parent(father)
{
  process_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSProcessComponent::~DSProcessComponent(void)
{
  if (process_definition_list) delete process_definition_list;
}

DSProcessKeyList* DSProcessComponent::GetProcessList(void) const
{
  return process_definition_list;
}

DSProcess *DSProcessComponent::GetProcess(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (process_definition_list == NULL)
  {
    return NULL;
  }

  if (process_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return process_definition_list->GetCurrentData();
}

DSProcess *DSProcessComponent::GetProcess(DSString& n) const
{
  return GetProcess(&n);
}

DSProcess *DSProcessComponent::GetProcess(const char * n) const
{
  DSProcess *process;
  DSString *str = new DSString(n);
  process = GetProcess(str);
  delete str;
  return process;
}

DSProcess *DSProcessComponent::GetFirstProcess(void) const
{
  if (process_definition_list == NULL)
  {
    return NULL;
  }

  if (process_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return process_definition_list->GetCurrentData();
}

DSProcess *DSProcessComponent::GetNextProcess(void) const
{
  if (process_definition_list == NULL)
  {
    return NULL;
  }

  if (process_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return process_definition_list->GetCurrentData();
}

DSResult DSProcessComponent::SetProcessList(DSProcessKeyList *list)
{
  if (process_definition_list == list) return DS_OK;

  if (process_definition_list != NULL)
  {
    delete process_definition_list;
  }
  process_definition_list = list;
  return DS_OK;
}

DSResult DSProcessComponent::InsertProcess(DSProcess* process)
{
  assert(process != NULL);
  assert(process->GetName() != NULL);

  if (process_definition_list == NULL)
  {
    process_definition_list = new DSProcessKeyList;
    assert(process_definition_list != NULL);
  }
  if (process->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    process->SetParent(DSProcessComponent::parent);
  }
  return process_definition_list->Append(process,
                                         new DSString(*process->GetName()));
}

DSBoolean DSProcessComponent::HasFormalParams(void) const
{
  DSProcess *process;

  for (process = GetFirstProcess();
       process;
       process = GetNextProcess())
  {
    if (process->GetFormalParamList()) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSProcessComponent::HasTimer(DSBoolean recursive) const
{
  (void)recursive;

  DSProcess *process;

  for (process = GetFirstProcess();
       process;
       process = GetNextProcess())
  {
    if (process->GetTimerList()) return DS_TRUE;
  }
  return DS_FALSE;
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSProcessComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSProcessComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
