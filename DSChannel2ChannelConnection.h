#ifndef _DSCHANNEL2CHANNELCONNECTION_H_
#define _DSCHANNEL2CHANNELCONNECTION_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSChannelRefComponent.h"
#include "DSChannelComponent.h"

/************************************************************************
 * Classname:  DSChannel2ChannelConnection
 * Purpose:    Speicherung der Verbindung zwischen einem Kanal und
 *             mehreren Signalrouten (Umsetzung des SDL-connects)
 * Z100:       Seite 47
 ************************************************************************/

class DSChannel2ChannelConnection : public DSObject
{
  public:
    DSChannel2ChannelConnection(DSObject* = NULL,              // Vaterobjekt
                                DSChannelRefComponent * = NULL,   // first list
                                DSChannelRefComponent * = NULL);  // second list
    virtual ~DSChannel2ChannelConnection(void);       

    DSObject *            New(DSObject * = NULL) const;  // virtueller Konstruktor

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob ein Kanal bzw. eine Signalroute in der   */
    /* Verbindung vorkommt:                        */
    /***********************************************/

    DSChannelRefComponent *  GetFirstChannelComponent(void) const;
    DSChannelRefComponent *  GetSecondChannelComponent(void) const;
    DSResult              SetFirstChannelComponent(DSChannelRefComponent *);
    DSResult              SetSecondChannelComponent(DSChannelRefComponent *);
    
    DSBoolean             IsChannelConnectedInFirst(DSChannelRef) const;
    DSBoolean             IsChannelConnectedInSecond(DSChannelRef) const;

    DSObject             *Clone(DSObject * = NULL,
                                DSObject * = NULL) const;
                                                  // erzeugt eine identische
                                                  // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult      Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult      Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSChannelRefComponent *    first_channel_component;
    DSChannelRefComponent *    second_channel_component;
};

typedef DSList<DSChannel2ChannelConnection>  DSChannel2ChannelConnectionList;

#endif
