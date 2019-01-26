#ifndef _DSPIPE2PIPEBINDINGCOMPONENT_H_
#define _DSPIPE2PIPEBINDINGCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSPipe2PipeBindingList.h"

/************************************************************************
 * Classname: DSPipe2PipeBindingComponent
 * Aufgabe:   Basisklasse fuer alle QSDL-Strukturen in denen QSDL-Pipes
 *            verbunden werden koennen.
 ************************************************************************/

class DSPipe2PipeBindingComponent
{
  public:
    DSPipe2PipeBindingComponent(class DSObject * = NULL); // parent
   ~DSPipe2PipeBindingComponent(void);

    DSPipe2PipeBindingList   *GetPipe2PipeBindingList(void) const;
    class DSPipe2PipeBinding *GetFirstPipe2PipeBinding(void) const;
    class DSPipe2PipeBinding *GetNextPipe2PipeBinding(void) const;

    DSResult                  SetPipe2PipeBindingList
                               (DSPipe2PipeBindingList*);
    DSResult                  InsertPipe2PipeBinding
                               (class DSPipe2PipeBinding*);

  protected:
    DSObject                 *GetComponentParent(void) const;  // Vaterobject
    DSResult                  SetComponentParent(const DSObject*);

  private:
    DSPipe2PipeBindingList *pipe2pipe_binding_list;
    class DSObject         *parent;
};

#endif
