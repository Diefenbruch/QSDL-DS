/****************************************************************************
 *                 Modul: $RCSfile: DSPipeComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Pipes
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

#include "DSPipeComponent.h"
#include "DSPipe.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Pipen
 ****************************************************************************/

/****************************************************************************
 * Globale Pipen
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSPipeComponent::DSPipeComponent(DSObject *father) :
  parent(father)
{
  pipe_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipeComponent::~DSPipeComponent(void)
{
  if (pipe_definition_list) delete pipe_definition_list;
}

DSPipeKeyList* DSPipeComponent::GetPipeList(void) const
{
  return pipe_definition_list;
}

DSPipe *DSPipeComponent::GetPipe(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (pipe_definition_list == NULL)
  {
    return NULL;
  }

  if (pipe_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return pipe_definition_list->GetCurrentData();
}

DSPipe *DSPipeComponent::GetPipe(DSString& pipe_name) const
{
  return GetPipe(&pipe_name);
}

DSPipe *DSPipeComponent::GetPipe(const char * pipe_name) const
{
  DSPipe *pipe;
  DSString *str;

  assert(pipe_name);
  str = new DSString(pipe_name);
  assert(str);
  pipe = GetPipe(str);
  delete str;
  return pipe;
}

DSPipe *DSPipeComponent::GetFirstPipe(void) const
{
  if (pipe_definition_list == NULL)
  {
    return NULL;
  }

  if (pipe_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return pipe_definition_list->GetCurrentData();
}

DSPipe *DSPipeComponent::GetNextPipe(void) const
{
  if (pipe_definition_list == NULL)
  {
    return NULL;
  }

  if (pipe_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return pipe_definition_list->GetCurrentData();
}

DSResult DSPipeComponent::SetPipeList(DSPipeKeyList *list)
{
  if (pipe_definition_list == list) return DS_OK;

  if (pipe_definition_list) delete pipe_definition_list;
  pipe_definition_list = list;
  return DS_OK;
}

DSResult DSPipeComponent::InsertPipe(DSPipe* pipe)
{
  assert(pipe != NULL);
  assert(pipe->GetName() != NULL);

  if (pipe_definition_list == NULL)
  {
    pipe_definition_list = new DSPipeKeyList;
    assert(pipe_definition_list != NULL);
  }
  if (pipe->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    pipe->SetParent(parent);
  }
  return pipe_definition_list->Append(pipe, new DSString(*pipe->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSPipeComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSPipeComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
