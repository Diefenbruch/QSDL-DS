/****************************************************************************
 *           Modul: $RCSfile: DSPipe2PipeBindingComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle QSDL-Strukturen in denen QSDL-Pipes
 *            verbunden werden koennen.
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

#include "DSPipe2PipeBindingComponent.h"
#include "DSPipe2PipeBinding.h"

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

DSPipe2PipeBindingComponent::DSPipe2PipeBindingComponent(DSObject *father) :
  parent(father)
{
  pipe2pipe_binding_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipe2PipeBindingComponent::~DSPipe2PipeBindingComponent(void)
{
  if (pipe2pipe_binding_list) delete pipe2pipe_binding_list;
}


DSPipe2PipeBindingList* DSPipe2PipeBindingComponent::GetPipe2PipeBindingList(void) const
{
  return pipe2pipe_binding_list;
}


DSPipe2PipeBinding *DSPipe2PipeBindingComponent::GetFirstPipe2PipeBinding(void) const
{
  if (pipe2pipe_binding_list == NULL)
  {
    return NULL;
  }

  if (pipe2pipe_binding_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return pipe2pipe_binding_list->GetCurrentData();
}


DSPipe2PipeBinding *DSPipe2PipeBindingComponent::GetNextPipe2PipeBinding(void) const
{
  if (pipe2pipe_binding_list == NULL)
  {
    return NULL;
  }

  if (pipe2pipe_binding_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return pipe2pipe_binding_list->GetCurrentData();
}


DSResult DSPipe2PipeBindingComponent::SetPipe2PipeBindingList(DSPipe2PipeBindingList *list)
{
  if (pipe2pipe_binding_list == list) return DS_OK;

  if (pipe2pipe_binding_list != NULL)
  {
    delete pipe2pipe_binding_list;
  }
  pipe2pipe_binding_list = list;
  return DS_OK;
}


DSResult DSPipe2PipeBindingComponent::InsertPipe2PipeBinding(DSPipe2PipeBinding* p2p)
{
  assert(p2p);
  if (pipe2pipe_binding_list == NULL)
  {
    pipe2pipe_binding_list = new DSPipe2PipeBindingList;
    assert(pipe2pipe_binding_list != NULL);
  }
  if (p2p->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    p2p->SetParent(DSPipe2PipeBindingComponent::parent);
  }
  return pipe2pipe_binding_list->Append(p2p);
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSPipe2PipeBindingComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSPipe2PipeBindingComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
