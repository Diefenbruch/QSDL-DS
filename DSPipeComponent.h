#ifndef _DSPIPECOMPONENT_H_
#define _DSPIPECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSPipeList.h"

/************************************************************************
 * Classname: DSPipeComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Pipe
 *            definiert werden koennen.
 ************************************************************************/

class DSPipeComponent
{
  public:
    DSPipeComponent(class DSObject * = NULL);
   ~DSPipeComponent(void);

    DSPipeKeyList *GetPipeList(void) const;
    class DSPipe  *GetPipe(class DSString*) const;
    class DSPipe  *GetPipe(class DSString&) const;
    class DSPipe  *GetPipe(const char *) const;
    class DSPipe  *GetFirstPipe(void) const;
    class DSPipe  *GetNextPipe(void) const;

    DSResult       SetPipeList(DSPipeKeyList*);
    DSResult       InsertPipe(class DSPipe*);

  protected:
    DSObject      *GetComponentParent(void) const;  // Vaterobject
    DSResult       SetComponentParent(const DSObject*);

  private:
    DSPipeKeyList  *pipe_definition_list;
    class DSObject *parent;
};

#endif
