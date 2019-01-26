/****************************************************************************
 *                 Modul: $RCSfile: DSPipeRefComponent.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Pipe-Referenzen
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

#include "DSPipeRefComponent.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe PipeRefn
 ****************************************************************************/

/****************************************************************************
 * Globale PipeRefn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSPipeRefComponent::DSPipeRefComponent(DSPipeRefList *pipes) :
  pipe_ref_list(pipes)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipeRefComponent::~DSPipeRefComponent(void)
{
  if (pipe_ref_list) delete pipe_ref_list;
}

/****************************************************************************
 * GetPipeRefList(): Liefert die Liste der Pipes, ueber welche die Dienst-
 *                   anforderung geroutet werden kann.
 *                   Ergebnis: Zeiger auf die Liste der Pipes
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSPipeRefList *DSPipeRefComponent::GetPipeRefList(void) const
{
  return pipe_ref_list;
}

DSPipeRef DSPipeRefComponent::GetFirstPipeRef(void) const
{
  if (pipe_ref_list == NULL)
  {
    return NULL;
  }

  if (pipe_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return pipe_ref_list->GetCurrentData();
}

DSPipeRef DSPipeRefComponent::GetNextPipeRef(void) const
{
  if (pipe_ref_list == NULL)
  {
    return NULL;
  }

  if (pipe_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return pipe_ref_list->GetCurrentData();
}

/****************************************************************************
 * SetPipeRefList(): Speichert die Liste der Pipes, ueber die die Dienstanfor-
 *                   derung geroutet werden darf.
 *                   -> via_pipes: Liste von Pipes
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSPipeRefComponent::SetPipeRefList(DSPipeRefList* pipes)
{
  if (pipe_ref_list == pipes) return DS_OK;

  if (pipe_ref_list) delete pipe_ref_list;
  pipe_ref_list = pipes;
  return DS_OK;
}

DSResult DSPipeRefComponent::InsertPipeRef(DSPipeRef pipe_ref)
{
  assert(pipe_ref);
  if (pipe_ref_list == NULL)
  {
    pipe_ref_list = new DSPipeRefList;
    assert(pipe_ref_list != NULL);
  }
  return pipe_ref_list->Append(pipe_ref);
}

