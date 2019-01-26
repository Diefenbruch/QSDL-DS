#ifndef _DSSIGNALROUTECOMPONENT_H_
#define _DSSIGNALROUTECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSSignalRouteList.h"

/************************************************************************
 * Classname: DSSignalRouteComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Signalrouten
 *            definiert werden koennen.
 ************************************************************************/

class DSSignalRouteComponent
{
  public:
    DSSignalRouteComponent(class DSObject * = NULL);
   ~DSSignalRouteComponent(void);

    DSSignalRouteKeyList *GetSignalRouteList(void) const;
    class DSSignalRoute  *GetSignalRoute(class DSString*) const;
    class DSSignalRoute  *GetSignalRoute(class DSString&) const;
    class DSSignalRoute  *GetSignalRoute(const char *) const;
    class DSSignalRoute  *GetFirstSignalRoute(void) const;
    class DSSignalRoute  *GetNextSignalRoute(void) const;

    DSResult              SetSignalRouteList(DSSignalRouteKeyList*);
    DSResult              InsertSignalRoute(class DSSignalRoute*);

  protected:
    DSObject             *GetComponentParent(void) const;  // Vaterobject
    DSResult              SetComponentParent(const DSObject*);

  private:
    DSSignalRouteKeyList *signalroute_definition_list;
    class DSObject       *parent;
};

#endif
