#ifndef _DSPIPE2LINKBINDINGCOMPONENT_H_
#define _DSPIPE2LINKBINDINGCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSPipe2LinkBindingList.h"

/************************************************************************
 * Classname:  DSPipe2LinkBindingComponent
 * Purpose:    Basisklasse fuer alle SDL-Strukturen in denen Verbindungen
 *             zwischen Pipes und Links definiert werden koennen
 ************************************************************************/

class DSPipe2LinkBindingComponent
{
  public:
    DSPipe2LinkBindingComponent(class DSObject * = NULL);     // parent
   ~DSPipe2LinkBindingComponent(void);       

    DSPipe2LinkBindingList   *GetPipe2LinkBindingList(void) const;
    class DSPipe2LinkBinding *GetFirstPipe2LinkBinding(void) const;
    class DSPipe2LinkBinding *GetNextPipe2LinkBinding(void) const;

    DSResult                  SetPipe2LinkBindingList(DSPipe2LinkBindingList*);
    DSResult                  InsertPipe2LinkBinding(class DSPipe2LinkBinding*);

  protected:
    DSObject                 *GetComponentParent(void) const;  // Vaterobject
    DSResult                  SetComponentParent(const DSObject*);

  private:
    DSPipe2LinkBindingList   *pipe2link_binding_list;
    class DSObject           *parent;
};

#endif
