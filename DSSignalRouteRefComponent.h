#ifndef _DSSIGNALROUTEREFCOMPONENT_H_
#define _DSSIGNALROUTEREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSSignalRoute.h"
 
/*******************************************************************************
 * Klasse DSSignalRouteRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Referenzen
 *            auf Signalrouten enthalten.
 ******************************************************************************/

class DSSignalRouteRefComponent
{
  public:
    DSSignalRouteRefComponent(DSSignalRouteRefList * = NULL);
   ~DSSignalRouteRefComponent(void);

    DSSignalRouteRefList *GetSignalRouteRefList(void) const;
    DSSignalRouteRef      GetFirstSignalRouteRef(void) const;
    DSSignalRouteRef      GetNextSignalRouteRef(void) const;

    DSResult              SetSignalRouteRefList(DSSignalRouteRefList*);
    DSResult              InsertSignalRouteRef(DSSignalRouteRef);

  private:
    DSSignalRouteRefList *signalroute_ref_list;
};

#endif  // ifndef
