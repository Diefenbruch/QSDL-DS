/****************************************************************************
 *           Modul: $RCSfile: DSPipe2LinkBindingComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Pipes
 *            mit Links verbunden werden koennen.
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

#include "DSPipe2LinkBindingComponent.h"
#include "DSPipe2LinkBinding.h"

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

DSPipe2LinkBindingComponent::DSPipe2LinkBindingComponent(DSObject *father) :
  parent(father)
{
  pipe2link_binding_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipe2LinkBindingComponent::~DSPipe2LinkBindingComponent(void)
{
  if (pipe2link_binding_list) delete pipe2link_binding_list;
}

DSPipe2LinkBindingList* DSPipe2LinkBindingComponent::GetPipe2LinkBindingList(void) const
{
  return pipe2link_binding_list;
}

DSPipe2LinkBinding *DSPipe2LinkBindingComponent::GetFirstPipe2LinkBinding(void) const
{
  if (pipe2link_binding_list == NULL)
  {
    return NULL;
  }

  if (pipe2link_binding_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return pipe2link_binding_list->GetCurrentData();
}

DSPipe2LinkBinding *DSPipe2LinkBindingComponent::GetNextPipe2LinkBinding(void) const
{
  if (pipe2link_binding_list == NULL)
  {
    return NULL;
  }

  if (pipe2link_binding_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return pipe2link_binding_list->GetCurrentData();
}

DSResult DSPipe2LinkBindingComponent::SetPipe2LinkBindingList(DSPipe2LinkBindingList *list)
{
  if (pipe2link_binding_list == list) return DS_OK;

  if (pipe2link_binding_list != NULL)
  {
    delete pipe2link_binding_list;
  }
  pipe2link_binding_list = list;
  return DS_OK;
}

DSResult DSPipe2LinkBindingComponent::InsertPipe2LinkBinding(DSPipe2LinkBinding* p2l)
{
  assert(p2l);
  if (pipe2link_binding_list == NULL)
  {
    pipe2link_binding_list = new DSPipe2LinkBindingList;
    assert(pipe2link_binding_list != NULL);
  }
  if (p2l->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    p2l->SetParent(DSPipe2LinkBindingComponent::parent);
  }
  return pipe2link_binding_list->Append(p2l);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSPipe2LinkBindingComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSPipe2LinkBindingComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
