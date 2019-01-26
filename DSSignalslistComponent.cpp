/****************************************************************************
 *                 Modul: $RCSfile: DSSignalslistComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.1 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Signallisten
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

#include "DSSignalslistComponent.h"
#include "DSSignalslist.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe SignalListn
 ****************************************************************************/
 
/****************************************************************************
 * Globale SignalListn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalslistComponent::DSSignalslistComponent(DSObject *father) :
  parent(father)
{
  signallist_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalslistComponent::~DSSignalslistComponent(void)
{
  if (signallist_definition_list) delete signallist_definition_list;
}

DSSignalslistKeyList* DSSignalslistComponent::GetSignallistList(void) const
{
  return signallist_definition_list;
}

DSSignalslist *DSSignalslistComponent::GetSignallist(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (signallist_definition_list == NULL)
  {
    return NULL;
  }

  if (signallist_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return signallist_definition_list->GetCurrentData();
}

DSSignalslist *DSSignalslistComponent::GetSignallist(DSString& n) const
{
  return GetSignallist(&n);
}

DSSignalslist *DSSignalslistComponent::GetSignallist(const char * n) const
{
  DSSignalslist *signallist;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  signallist = GetSignallist(str);
  delete str;

  return signallist;
}

DSSignalslist *DSSignalslistComponent::GetFirstSignallist(void) const
{
  if (signallist_definition_list == NULL)
  {
    return NULL;
  }

  if (signallist_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return signallist_definition_list->GetCurrentData();
}

DSSignalslist *DSSignalslistComponent::GetNextSignallist(void) const
{
  if (signallist_definition_list == NULL)
  {
    return NULL;
  }

  if (signallist_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return signallist_definition_list->GetCurrentData();
}

DSResult DSSignalslistComponent::SetSignallistList(DSSignalslistKeyList *list)
{
  if (signallist_definition_list == list) return DS_OK;

  if (signallist_definition_list != NULL)
  {
    delete signallist_definition_list;
  }
  signallist_definition_list = list;
  return DS_OK;
}

DSResult DSSignalslistComponent::InsertSignallist(DSSignalslist* signallist)
{
  assert(signallist != NULL);
  assert(signallist->GetName() != NULL);

  if (signallist_definition_list == NULL)
  {
    signallist_definition_list = new DSSignalslistKeyList;
    assert(signallist_definition_list != NULL);
  }
  if (signallist->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    signallist->SetParent(parent);
  }
  return signallist_definition_list->Append(signallist,
                                            new DSString(*signallist->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSSignalslistComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSSignalslistComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
