#ifndef _DSSIGNALREFCOMPONENT_H_
#define _DSSIGNALREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSignalRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen
 *            SDL-Signalreferenzen definiert werden koennen.
 ************************************************************************/

class DSSignalRefComponent
{
  public:
    DSSignalRefComponent(DSSignalRefList * = NULL);
   ~DSSignalRefComponent(void);

    DSSignalRefList *GetSignalRefList(void) const;
    DSSignalRef      GetFirstSignalRef(void) const;
    DSSignalRef      GetNextSignalRef(void) const;

    DSResult         SetSignalRefList(DSSignalRefList*);
    DSResult         InsertSignalRef(DSSignalRef);

  private:
    DSSignalRefList *signal_ref_list;     
};

#endif
