#ifndef _DSSORTREFCOMPONENT_H_
#define _DSSORTREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSortRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 ************************************************************************/

class DSSortRefComponent
{
  public:
    DSSortRefComponent(DSSortRefList * = NULL);
   ~DSSortRefComponent(void);

    DSSortRefList *GetSortRefList(void) const;
    DSSortRef      GetFirstSortRef(void) const;
    DSSortRef      GetNextSortRef(void) const;

    DSResult       SetSortRefList(DSSortRefList*);
    DSResult       InsertSortRef(DSSortRef);

  private:
    DSSortRefList *sort_ref_list;     
};

#endif
