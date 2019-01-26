/****************************************************************************
 *                 Modul: $RCSfile: DSLinkRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Link-Referenzen
 *            enthalten.
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

#include "DSLinkRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe LinkRefn
 ****************************************************************************/

/****************************************************************************
 * Globale LinkRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSLinkRefComponent::DSLinkRefComponent(DSLinkRefList *links) :
  link_ref_list(links)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSLinkRefComponent::~DSLinkRefComponent(void)
{
  if (link_ref_list) delete link_ref_list;
}

/****************************************************************************
 * GetLinkRefList(): Liefert die Liste der Links, ueber welche die Dienst-
 *                   anforderung geroutet werden kann.
 *                   Ergebnis: Zeiger auf die Liste der Links
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSLinkRefList *DSLinkRefComponent::GetLinkRefList(void) const
{
  return link_ref_list;
}

DSLinkRef DSLinkRefComponent::GetFirstLinkRef(void) const
{
  if (link_ref_list == NULL)
  {
    return NULL;
  }

  if (link_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return link_ref_list->GetCurrentData();
}

DSLinkRef DSLinkRefComponent::GetNextLinkRef(void) const
{
  if (link_ref_list == NULL)
  {
    return NULL;
  }

  if (link_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return link_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetLinkRefList(): Speichert die Liste der Links, ueber die die Dienstanfor-
 *                   derung geroutet werden darf.
 *                   -> via_links: Liste von Links
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSLinkRefComponent::SetLinkRefList(DSLinkRefList* links)
{
  if (link_ref_list == links) return DS_OK;

  if (link_ref_list) delete link_ref_list;
  link_ref_list = links;
  return DS_OK;
}

DSResult DSLinkRefComponent::InsertLinkRef(DSLinkRef link_ref)
{
  assert(link_ref);
  if (link_ref_list == NULL)
  {
    link_ref_list = new DSLinkRefList;
    assert(link_ref_list != NULL);
  }
  return link_ref_list->Append(link_ref);
}

