#ifndef _DSOUTPUT_H_
#define _DSOUTPUT_H_

#include "DSBasicTypes.h"
#include "DSAction.h"
#include "DSChannelRefComponent.h"
#include "DSSignalRouteRefComponent.h"
#include "DSActualParamComponent.h"
 
/*******************************************************************************
 * Klasse DSOutput
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine OUTPUT-
 *        Instruktion.
 * Z100:  Seite 65
 ******************************************************************************/

class DSOutput : public DSAction,
                 public DSActualParamComponent,
                 public DSSignalRouteRefComponent, // via Signalroutes
                 public DSChannelRefComponent      // via Channels
{
  public:
    DSOutput(DSObject*,                    // Vaterobjekt
             DSString*          = NULL,    // Label
             DSSignalRef        = NULL,    // Output-Signal
             DSActualParamList* = NULL);   // Output-Parameter
    DSOutput(DSObject*,
             DSString&,
             DSSignalRef        = NULL,
             DSActualParamList* = NULL);
    DSOutput(DSObject*,
             const char *,
             DSSignalRef        = NULL,
             DSActualParamList* = NULL);
    ~DSOutput(void);

    DSSignalRef         GetSignalRef(void) const;
    class DSExpression *GetProcessID(void) const;
    class DSExpression *GetDelay(void) const;

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob ein Kanal bzw. eine Signalroute im       */
    /* Routing erlaubt ist:                        */
    /***********************************************/

    DSBoolean           IsChannelAllowed(DSChannelRef) const;
    DSBoolean           IsSignalRouteAllowed(DSSignalRouteRef) const;

    /******************************/
    /* Routingfunktion (statisch) */
    /******************************/
    DSProcessRefList   *GetSignalDestination(void) const;

    DSResult            SetSignalRef(DSSignalRef);
    DSResult            SetProcessID(class DSExpression *);
    DSResult            SetDelay(class DSExpression *);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const; // erzeugt eine identische
                                                        // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSSignalRef         signal_ref;
    class DSExpression *to_pid;  // Keine DSProcessRef, weil Runtime-
                                 // System evtl. routen musz!
    class DSExpression *delay;   // QSDL-Signal-Delay
};

#endif  // ifndef
