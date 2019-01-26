/****************************************************************************
 *                 Modul: $RCSfile: DSPipe2PipeBinding.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.1 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-Connect bereit.
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
 
#include "DSPipe2PipeBinding.h"
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSPipe.h"
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

DSPipe2PipeBinding::
DSPipe2PipeBinding(DSObject           * father,
                   DSPipeRefComponent * first_pipes,
                   DSPipeRefComponent * second_pipes):
  DSObject(DS_PIPE2PIPEBINDING, father),
  first_pipe_component(first_pipes),
  second_pipe_component(second_pipes)
{
  if (father)
  {
    assert(father->GetType() == DS_BLOCKSUBSTRUCTURE);
    ((DSBlockSubstructure*)father)->InsertPipe2PipeBinding(this);
  }
  
  if (first_pipe_component == NULL)
  {
    first_pipe_component = new DSPipeRefComponent;
  }
  if (second_pipe_component == NULL)
  {
    second_pipe_component = new DSPipeRefComponent;
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipe2PipeBinding::~DSPipe2PipeBinding(void)
{
  if (first_pipe_component) delete first_pipe_component;
  if (second_pipe_component) delete second_pipe_component;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSPipe2PipeBinding::New(DSObject *father) const
{
  return new DSPipe2PipeBinding(father);
}

DSBoolean DSPipe2PipeBinding::
IsPipeConnectedInFirst(DSPipeRef search_pipe) const
{
  DSPipeRef pipe;

  if (!first_pipe_component)
    return DS_FALSE;

  for (pipe = first_pipe_component->GetFirstPipeRef();
       pipe != NULL;
       pipe = first_pipe_component->GetNextPipeRef())
  {
    if (pipe == search_pipe)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}


DSBoolean DSPipe2PipeBinding::
IsPipeConnectedInSecond(DSPipeRef search_pipe) const
{
  DSPipeRef pipe;

  if (!second_pipe_component)
    return DS_FALSE;

  for (pipe = second_pipe_component->GetFirstPipeRef();
       pipe != NULL;
       pipe = second_pipe_component->GetNextPipeRef())
  {
    if (pipe == search_pipe)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}


DSPipeRefComponent * DSPipe2PipeBinding::
GetFirstPipeComponent(void) const
{
  return first_pipe_component;
}


DSPipeRefComponent *  DSPipe2PipeBinding::
GetSecondPipeComponent(void) const
{
  return second_pipe_component;
}


DSResult DSPipe2PipeBinding::
SetFirstPipeComponent(DSPipeRefComponent *first_component)
{
  if (first_pipe_component == first_component) return DS_OK;

  if (first_pipe_component) delete first_pipe_component;

  first_pipe_component = first_component;

  return DS_OK;
}


DSResult DSPipe2PipeBinding::
SetSecondPipeComponent(DSPipeRefComponent *second_component)
{
  if (second_pipe_component == second_component) return DS_OK;

  if (second_pipe_component) delete second_pipe_component;

  second_pipe_component = second_component;

  return DS_OK;
}


DSObject *DSPipe2PipeBinding::Clone(DSObject *father, DSObject *fill_this) const
{
  DSPipe2PipeBinding *new_p2p_binding;

  if (fill_this == NULL)
  {
    new_p2p_binding = (DSPipe2PipeBinding *)New(father);
    assert(new_p2p_binding);
  }
  else
  {
    assert(fill_this->GetType() == DS_PIPE2PIPEBINDING);
    new_p2p_binding = (DSPipe2PipeBinding *)fill_this;
  }

  if (first_pipe_component->GetPipeRefList())
  {
    new_p2p_binding->GetFirstPipeComponent()->SetPipeRefList((DSPipeRefList *)(GetFirstPipeComponent()->GetPipeRefList())->Clone((DSObject *)new_p2p_binding));
  }

  if (second_pipe_component->GetPipeRefList())
  {
    new_p2p_binding->GetSecondPipeComponent()->SetPipeRefList((DSPipeRefList *)(GetSecondPipeComponent()->GetPipeRefList())->Clone((DSObject *)new_p2p_binding));
  }

  return new_p2p_binding;
}

DSResult DSPipe2PipeBinding::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;
  assert(writer);

  return DS_OK;
}

DSResult DSPipe2PipeBinding::Run(DSWriter *writer, DSType object_type,
                                    DSCardinal what) const
{
  DSResult  result;
  DSPipeRef pipe;

  switch(object_type)
  {
    case DS_PIPE:
      for (pipe = first_pipe_component->GetFirstPipeRef();
           pipe;
           pipe = first_pipe_component->GetNextPipeRef())
      {
        result = pipe->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
