#ifndef _DSPROCESSCOMPONENT_H_
#define _DSPROCESSCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSProcessList.h"

/************************************************************************
 * Classname: DSProcessComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozesse
 *            definiert werden koennen.
 ************************************************************************/

class DSProcessComponent
{
  protected:
    DSProcessComponent(class DSObject * = NULL);

  public:
   ~DSProcessComponent(void);

    DSProcessKeyList *GetProcessList(void) const;
    class DSProcess  *GetProcess(class DSString*) const;
    class DSProcess  *GetProcess(class DSString&) const;
    class DSProcess  *GetProcess(const char *) const;
    class DSProcess  *GetFirstProcess(void) const;
    class DSProcess  *GetNextProcess(void) const;

    DSResult          SetProcessList(DSProcessKeyList*);
    DSResult          InsertProcess(class DSProcess*);

    DSBoolean         HasFormalParams(void) const;
    DSBoolean         HasTimer(DSBoolean) const;

  protected:
    DSObject         *GetComponentParent(void) const;  // Vaterobject
    DSResult          SetComponentParent(const DSObject*);

  private:
    DSProcessKeyList *process_definition_list;
    class DSObject   *parent;
};

#endif
