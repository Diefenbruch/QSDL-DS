/****************************************************************************
 *                 Modul: $RCSfile: DSPipe2LinkBinding.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein QSDL-Bind bereit.
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
 
#include "DSPipe2LinkBinding.h"
#include "DSBlock.h"  // wegen parent
#include "DSPipe.h"
#include "DSLink.h"
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

DSPipe2LinkBinding::
DSPipe2LinkBinding(DSObject      *father,
                   DSPipeRefList *pipes,
                   DSLinkRefList *links):
  DSObject(DS_PIPE2LINKBINDING, father),
  DSPipeRefComponent(pipes),
  DSLinkRefComponent(links)
{
  if (father)
  {
    ((DSBlock*)father)->InsertPipe2LinkBinding(this);
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSPipe2LinkBinding::~DSPipe2LinkBinding(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSPipe2LinkBinding::New(DSObject *father) const
{
  return new DSPipe2LinkBinding(father);
}

DSBoolean DSPipe2LinkBinding::IsPipeBound(DSPipeRef search_pipe) const
{
  DSPipeRef pipe;

  for (pipe = GetFirstPipeRef();
       pipe != NULL;
       pipe = GetNextPipeRef())
  {
    if (pipe == search_pipe)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSBoolean DSPipe2LinkBinding::IsLinkBound(DSLinkRef search_link) const
{
  DSLinkRef link;

  for (link = GetFirstLinkRef();
       link != NULL;
       link = GetNextLinkRef())
  {
    if (link == search_link)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSObject *DSPipe2LinkBinding::Clone(DSObject *father,
                                    DSObject *fill_this) const
{
  DSPipe2LinkBinding *new_p2l_binding;

  if (fill_this == NULL)
  {
    new_p2l_binding = (DSPipe2LinkBinding *)New(father);
    assert(new_p2l_binding);
  }
  else
  {
    assert(fill_this->GetType() == DS_PIPE2LINKBINDING);
    new_p2l_binding = (DSPipe2LinkBinding *)fill_this;
  }

  if (GetPipeRefList())
  {
    new_p2l_binding->SetPipeRefList((DSPipeRefList *)GetPipeRefList()->Clone((DSObject *)new_p2l_binding));
  }
  
  if (GetLinkRefList())
  {
    new_p2l_binding->SetLinkRefList((DSLinkRefList *)GetLinkRefList()->Clone((DSObject *)new_p2l_binding));
  }
  
  return new_p2l_binding;
}

DSResult DSPipe2LinkBinding::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSPipe2LinkBinding::Run(DSWriter *writer, DSType object_type,
                                 DSCardinal what) const
{
  DSResult  result;
  DSLinkRef link;
  DSPipeRef pipe;

  switch(object_type)
  {
    case DS_LINK:
      for (link = GetFirstLinkRef();
           link;
           link = GetNextLinkRef())
      {
        result = link->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PIPE:
      for (pipe = GetFirstPipeRef();
           pipe;
           pipe = GetNextPipeRef())
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
