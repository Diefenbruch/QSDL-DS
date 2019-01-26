#ifndef _DSSIGNALCOMPONENT_H_
#define _DSSIGNALCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSSignalList.h"

/************************************************************************
 * Classname: DSSignalComponent
 * Purpose:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Signale
 *            definiert werden koennen.
 * Z100:
 ************************************************************************/

class DSSignalComponent
{
  public:
    DSSignalComponent(class DSObject * = NULL);
   ~DSSignalComponent(void);

    DSSignalKeyList *GetSignalList(void) const;
    class DSSignal  *GetSignal(class DSString*) const;
    class DSSignal  *GetSignal(class DSString&) const;
    class DSSignal  *GetSignal(const char *) const;
    class DSSignal  *GetFirstSignal(void) const;
    class DSSignal  *GetNextSignal(void) const;

    DSResult         SetSignalList(DSSignalKeyList*);
    DSResult         InsertSignal(class DSSignal*);

    DSBoolean        HasSignalParams(void) const;

  protected:
    DSObject        *GetComponentParent(void) const;  // Vaterobject
    DSResult         SetComponentParent(const DSObject*);

  private:
    DSSignalKeyList *signal_definition_list;
    class DSObject  *parent;
};

#endif
