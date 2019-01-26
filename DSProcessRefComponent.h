#ifndef _DSPROCESSREFCOMPONENT_H_
#define _DSPROCESSREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSProcessRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen Verweise auf
 *            Prozesse definiert werden koennen.
 ************************************************************************/

class DSProcessRefComponent
{
  public:
    DSProcessRefComponent(DSProcessRefList * = NULL);
   ~DSProcessRefComponent(void);

    DSProcessRefList *GetProcessRefList(void) const;
    DSProcessRef      GetFirstProcessRef(void) const;
    DSProcessRef      GetNextProcessRef(void) const;

    DSResult          SetProcessRefList(DSProcessRefList*);
    DSResult          InsertProcessRef(DSProcessRef);

  private:
    DSProcessRefList *process_ref_list;     
};

#endif
