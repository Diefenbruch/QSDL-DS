/****************************************************************************
 *                 Modul: $RCSfile: DSLinkComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Links
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

#include "DSLinkComponent.h"
#include "DSLink.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Linkn
 ****************************************************************************/
 
/****************************************************************************
 * Globale Linkn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSLinkComponent::DSLinkComponent(DSObject *father) :
  parent(father)
{
  link_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSLinkComponent::~DSLinkComponent(void)
{
  if (link_definition_list) delete link_definition_list;
}

DSLinkKeyList* DSLinkComponent::GetLinkList(void) const
{
  return link_definition_list;
}

DSLink *DSLinkComponent::GetLink(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (link_definition_list == NULL)
  {
    return NULL;
  }

  if (link_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return link_definition_list->GetCurrentData();
}

DSLink *DSLinkComponent::GetLink(DSString& n) const
{
  return GetLink(&n);
}

DSLink *DSLinkComponent::GetLink(const char * n) const
{
  DSLink *link;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  link = GetLink(str);
  delete str;
  return link;
}

DSLink *DSLinkComponent::GetFirstLink(void) const
{
  if (link_definition_list == NULL)
  {
    return NULL;
  }

  if (link_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return link_definition_list->GetCurrentData();
}

DSLink *DSLinkComponent::GetNextLink(void) const
{
  if (link_definition_list == NULL)
  {
    return NULL;
  }

  if (link_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return link_definition_list->GetCurrentData();
}

DSResult DSLinkComponent::SetLinkList(DSLinkKeyList *list)
{
  if (link_definition_list == list) return DS_OK;

  if (link_definition_list != NULL)
  {
    delete link_definition_list;
  }
  link_definition_list = list;
  return DS_OK;
}

DSResult DSLinkComponent::InsertLink(DSLink* link)
{
  assert(link != NULL);
  assert(link->GetName() != NULL);

  if (link_definition_list == NULL)
  {
    link_definition_list = new DSLinkKeyList;
    assert(link_definition_list != NULL);
  }
  if (link->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    link->SetParent(parent);
  }
  return link_definition_list->Append(link,
                                      new DSString(*link->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSLinkComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSLinkComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
