#ifndef _DSCHANNEL2ROUTECONNECTIONCOMPONENT_H_
#define _DSCHANNEL2ROUTECONNECTIONCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSChannel2RouteConnectionList.h"

/************************************************************************
 * Classname: DSChannel2RouteConnectionComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            mit Signalrouten verbunden werden koennen.
 ************************************************************************/

class DSChannel2RouteConnectionComponent
{
  public:
    DSChannel2RouteConnectionComponent(class DSObject * = NULL); // parent
   ~DSChannel2RouteConnectionComponent(void);

    DSChannel2RouteConnectionList   *GetChannel2RouteConnectionList(void) const;
    class DSChannel2RouteConnection *GetFirstChannel2RouteConnection(void) const;
    class DSChannel2RouteConnection *GetNextChannel2RouteConnection(void) const;

    DSResult                       SetChannel2RouteConnectionList
                                    (DSChannel2RouteConnectionList*);
    DSResult                       InsertChannel2RouteConnection
                                    (class DSChannel2RouteConnection*);

  protected:
    DSObject           *GetComponentParent(void) const;  // Vaterobject
    DSResult            SetComponentParent(const DSObject*);

  private:
    DSChannel2RouteConnectionList *channel2route_connection_list;
    class DSObject                *parent;
};

#endif
