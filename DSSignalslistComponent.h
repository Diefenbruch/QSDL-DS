#ifndef _DSSIGNALLISTCOMPONENT_H_
#define _DSSIGNALLISTCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSSignalslistList.h"

/************************************************************************
 * Classname: DSSignalslistComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Signallisten
 *            definiert werden koennen.
 ************************************************************************/

class DSSignalslistComponent
{
  protected:
    DSSignalslistComponent(class DSObject * = NULL);

  public:
   ~DSSignalslistComponent(void);

    DSSignalslistKeyList *GetSignallistList(void) const;
    class DSSignalslist  *GetSignallist(class DSString*) const;
    class DSSignalslist  *GetSignallist(class DSString&) const;
    class DSSignalslist  *GetSignallist(const char *) const;
    class DSSignalslist  *GetFirstSignallist(void) const;
    class DSSignalslist  *GetNextSignallist(void) const;

    DSResult             SetSignallistList(DSSignalslistKeyList*);
    DSResult             InsertSignallist(class DSSignalslist*);

  protected:
    DSObject            *GetComponentParent(void) const;  // Vaterobject
    DSResult             SetComponentParent(const DSObject*);

  private:
    DSSignalslistKeyList *signallist_definition_list;
    class DSObject      *parent;
};

#endif
