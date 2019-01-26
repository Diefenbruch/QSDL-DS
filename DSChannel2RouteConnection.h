#ifndef _DSCHANNEL2ROUTECONNECTION_H_
#define _DSCHANNEL2ROUTECONNECTION_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSChannelRefComponent.h"
#include "DSSignalRouteRefComponent.h"

/************************************************************************
 * Classname:  DSChannel2RouteConnection
 * Purpose:    Speicherung der Verbindung zwischen einem Kanal und
 *             mehreren Signalrouten (Umsetzung des SDL-connects)
 * Z100:       Seite 47
 ************************************************************************/

class DSChannel2RouteConnection : public DSObject,
                                  public DSChannelRefComponent,
                                  public DSSignalRouteRefComponent
{
  public:
    DSChannel2RouteConnection(DSObject* = NULL,           // Vaterobjekt
                              DSChannelRefList*     = NULL,
                              DSSignalRouteRefList* = NULL);
    virtual ~DSChannel2RouteConnection(void);       

    DSObject     *New(DSObject * = NULL) const;  // virtueller Konstruktor

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob ein Kanal bzw. eine Signalroute in der   */
    /* Verbindung vorkommt:                        */
    /***********************************************/

    DSBoolean             IsChannelConnected(DSChannelRef) const;
    DSBoolean             IsSignalRouteConnected(DSSignalRouteRef) const;

    DSObject             *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                                  // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult      Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult      Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
};

typedef DSList<DSChannel2RouteConnection>  DSChannel2RouteConnectionList;

#endif
